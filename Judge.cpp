//
// Created by tyl on 2022/1/6.
//

#include "Judge.h"

template <class T> std::vector<std::vector<T>> combinationEnumeration(std::vector<T> nums) {
    int n = nums.size(), i, j, k;
    std::vector<std::vector<T>> result((T)pow(2, n), std::vector<T>());
    for (i = 0; i < pow(2, n); i++) {
        k = 1;
        for (j = 0; j < n; j++) {
            if ((k & i) == k)
                result[i].push_back(nums[j]);
            k = k << 1;
        }
    }
    return result;
}

std::vector<uint8_t> findPairs(std::vector<uint8_t> & cards) {
    std::vector<uint8_t> result;
    for (int i = 0; i < 37; i++)
        if (cards[i] >= 2)
            result.emplace_back(i);
    return result;
}

std::vector<uint8_t> findTriplets(std::vector<uint8_t> & cards) {
    std::vector<uint8_t> result;
    for (int i = 0; i < 37; i++)
        if (cards[i] >= 3)
            result.emplace_back(i);
    return result;
}

std::vector<std::vector<uint8_t>> findSequences(std::vector<uint8_t> cards) {
    std::vector<std::vector<uint8_t>> result;
    int i = 1;
    while (i < 28) {
        if ((cards[i] >= 1) && (cards[i + 1] >= 1) && (cards[i + 2] >= 1)) {
            result.emplace_back(
                    std::vector<uint8_t>{(uint8_t)i, (uint8_t)(i + 1), (uint8_t)(i + 2)});
            cards[i] -= 1;
            cards[i + 1] -= 1;
            cards[i + 2] -= 1;
        }
        else i++;
    }
    return result;
}

void Judge::mahjongSort(std::vector<uint8_t> & cards) {
    struct mps_cmp {
        bool operator()(uint8_t a, uint8_t b) {
            if ((a % 30) < (b % 30)) return true;
            else if (((a % 30) == (b % 30)) && (a < b)) return true;
            else return false;
        }
    };

    struct word_cmp {
        bool operator()(uint8_t a, uint8_t b) {
            return (a % 10) < (b % 10);
        }
    };

    int l = 0, r = cards.size() - 1;
    uint8_t exchange;
    while (l != r + 1)
        if (cards[l] >= 120) {
            exchange = cards[l];
            cards[l] = cards[r];
            cards[r] = exchange;
            r -= 1;
        }
        else l++;
    std::sort(cards.begin(), cards.begin() + l, mps_cmp());
    std::sort(cards.begin() + l, cards.end(), word_cmp());
}

std::vector<uint8_t> Judge::winStrExchange(std::vector<uint8_t> & cards) {
    this->mahjongSort(cards);

    //由牌型变换为编码字符串
    std::vector<uint8_t> str_type;
    int curr = 1, count = 1;
    //对于非字牌部分
    while (curr < cards.size() && cards[curr] < 120) {
        if (cards[curr - 1] % 30 == cards[curr] % 30)
            count += 1;
        else {
            str_type.push_back(count);
            count = 1;
            if (cards[curr - 1] % 30 != cards[curr] % 30 - 1)
                str_type.push_back(0);
        }
        curr += 1;
    }

    if (curr > 1) str_type.push_back(count);
    if (curr > 1) {
        if (curr < cards.size())
            str_type.push_back(0);
        curr += 1;
    }
    //对于字牌部分
    while (curr < cards.size()) {
        if (cards[curr - 1] % 10 == cards[curr] % 10)
            count += 1;
        else {
            str_type.push_back(count);
            count = 1;
            str_type.push_back(0);
        }
        curr += 1;
    }
    if (curr == cards.size())
        str_type.push_back(count);
    return str_type;
}

int Judge::winCodeExchange(std::vector<uint8_t> str_type) {
    //由编码字符串变换为int编码
    uint32_t code = 0;
    int i = 0, to_be_coded, bitsnum;
    while (i < str_type.size()) {
        switch (str_type[i]) {
            case 1:
                to_be_coded = 0;
                bitsnum = 0;
                break;
            case 2:
                to_be_coded = 3;
                bitsnum = 2;
                break;
            case 3:
                to_be_coded = 15;
                bitsnum = 4;
                break;
            case 4:
                to_be_coded = 63;
                bitsnum = 6;
        }
        code = code << bitsnum;
        code += to_be_coded;
        if ((i < str_type.size() - 1) && (str_type[i + 1] == 0)) {
            code = code << 2;
            code += 2;
            i += 2;
        }
        else {
            code = code << 1;
            i += 1;
        }
    }

    return code;
}

void Judge::winCodeSetConstruct() {
    int triplet;                  //刻子的个数
    int sequence;                 //顺子的个数
    int pair_pos;                 //雀头的位置
    int pos0, pos1, pos2, pos3;
    int* pos[4];                  //面子1、2、3、4的位置
    int i, j;

    std::unordered_set<int> pattern_set;
    pos[0] = &pos0;
    pos[1] = &pos1;
    pos[2] = &pos2;
    pos[3] = &pos3;
    std::vector<uint8_t> pattern;
    pattern.reserve(18);

    for (pair_pos = 0; pair_pos < 17; pair_pos++) {
        for (pos0 = 0; pos0 < 16; pos0++) {
            for (pos1 = 0; pos1 < 16; pos1++) {
                for (pos2 = 0; pos2 < 16; pos2++) {
                    for (pos3 = 0; pos3 < 16; pos3++) {
                        for (triplet = 0; triplet <= 4; triplet++) {
                            std::string pattern_proto(18, 0);
                            i = 0;
                            pattern_proto[pair_pos] += 2;
                            for (i; i < triplet; i++)
                                if (pattern_proto[*(pos[i])] <= 1)
                                    pattern_proto[*(pos[i])] += 3;
                                else
                                    i = 6;
                            for (i; i < 4; i++)
                                if ((pattern_proto[*(pos[i])] <= 3) &&
                                    (pattern_proto[*(pos[i]) + 1] <= 3) &&
                                    (pattern_proto[*(pos[i]) + 2] <= 3)) {
                                    pattern_proto[*(pos[i])] += 1;
                                    pattern_proto[*(pos[i]) + 1] += 1;
                                    pattern_proto[*(pos[i]) + 2] += 1;
                                } else
                                    i = 6;

                            if (i < 6) {
                                pattern.clear();
                                i = 0;
                                while (pattern_proto[i] == 0)
                                    i++;
                                pattern.push_back(pattern_proto[i]);
                                i++;
                                for (i; i < 18; i++)
                                    if ((pattern_proto[i] == 0) && (pattern[pattern.size() - 1] == 0)) continue;
                                    else pattern.push_back(pattern_proto[i]);
                                if (pattern[pattern.size() - 1] == 0) pattern.pop_back();
                                pattern_set.insert(this->winCodeExchange(pattern));
                            }
                        }
                    }
                }
            }
        }
    }

    std::vector<std::vector<int>> combinations = combinationEnumeration<int>({0,1,2,3,4,5});
    for (std::vector<int> combination : combinations) {
        pattern.clear();
        j = 0;
        for (i = 0; i < 7; i++) {
            pattern.push_back(2);
            if ((j < combination.size()) && (i == combination[j])) {
                pattern.push_back(0);
                j++;
            }
        }
        pattern_set.insert(this->winCodeExchange(pattern));
    }

    this->WinCodeSet = pattern_set;
}

std::vector<std::vector<std::vector<uint8_t>>> Judge::handDivision(std::vector<uint8_t> hand, int exposure_size) {
    //最外层的vector代表各分配方案，每个分配方案的第一个vector<int>为刻子数、顺子数，后面为雀头、刻子、顺子
    std::vector<std::vector<std::vector<uint8_t>>> result;
    std::vector<uint8_t> pairs = findPairs(hand);

    for (uint8_t pair : pairs) {
        std::vector<uint8_t> hand_without_pair = hand;
        hand_without_pair[pair] -= 2;
        std::vector<uint8_t> triplets = findTriplets(hand_without_pair);

        std::vector<std::vector<uint8_t>> combinations = combinationEnumeration<uint8_t>(triplets);

        for (std::vector<uint8_t> combination : combinations) {
            std::vector<uint8_t> hand_without_pair_or_triplet = hand_without_pair;
            for (uint8_t triplet : combination)
                hand_without_pair_or_triplet[triplet] -= 3;

            std::vector<std::vector<uint8_t>> sequences = findSequences(hand_without_pair_or_triplet);
            if ((sequences.size() + combination.size()) == (4 - exposure_size)) {
                std::vector<std::vector<uint8_t>> result_n{{(uint8_t)combination.size(), (uint8_t)sequences.size()}};
                result_n.emplace_back(std::vector<uint8_t>(2, pair));
                for (uint8_t triplet : combination)
                    result_n.emplace_back(std::vector<uint8_t>(3, triplet));
                for (std::vector<uint8_t> sequence : sequences)
                    result_n.emplace_back(sequence);
                result.push_back(result_n);
            }
        }
    }
    return result;
}

