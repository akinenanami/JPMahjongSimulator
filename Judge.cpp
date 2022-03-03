//
// Created by tyl on 2022/1/6.
//

#include "Judge.h"

template<class T>
std::vector<std::vector<T>> combinationEnumeration(std::vector<T> nums)
{
    int                         n = nums.size(), i, j, k;
    std::vector<std::vector<T>> result((T) pow(2, n), std::vector<T>());
    for (i = 0; i < pow(2, n); i++) {
        k = 1;
        for (j = 0; j < n; j++) {
            if ((k & i) == k) {
                result[i].push_back(nums[j]);
            }
            k = k << 1;
        }
    }
    return result;
}

std::vector<uint8_t> findPairs(std::vector<uint8_t> &cards)
{
    std::vector<uint8_t> result;
    for (int i = 0; i < 37; i++) {
        if (cards[i] >= 2) {
            result.emplace_back(i);
        }
    }
    return result;
}

std::vector<uint8_t> findTriplets(std::vector<uint8_t> &cards)
{
    std::vector<uint8_t> result;
    for (int i = 0; i < 37; i++) {
        if (cards[i] >= 3) {
            result.emplace_back(i);
        }
    }
    return result;
}

std::vector<std::vector<uint8_t>> findSequences(std::vector<uint8_t> cards)
{
    std::vector<std::vector<uint8_t>> result;
    int                               i = 1;
    while (i < 28) {
        if ((cards[i] >= 1) && (cards[i + 1] >= 1) && (cards[i + 2] >= 1)) {
            result.emplace_back(
                std::vector<uint8_t>{ (uint8_t) i, (uint8_t) (i + 1), (uint8_t) (i + 2) }
            );
            cards[i] -= 1;
            cards[i + 1] -= 1;
            cards[i + 2] -= 1;
        } else {
            i++;
        }
    }
    return result;
}

void Judge::mahjongSort(std::vector<uint8_t> &cards)
{
    struct mps_cmp
    {
        bool operator()(uint8_t a, uint8_t b)
        {
            if ((a % 30) < (b % 30)) {
                return true;
            } else if (((a % 30) == (b % 30)) && (a < b)) {
                return true;
            } else {
                return false;
            }
        }
    };

    struct word_cmp
    {
        bool operator()(uint8_t a, uint8_t b)
        {
            return (a % 10) < (b % 10);
        }
    };

    int     l = 0, r = cards.size() - 1;
    uint8_t exchange;
    while (l != r + 1) {
        if (cards[l] >= 120) {
            exchange = cards[l];
            cards[l] = cards[r];
            cards[r] = exchange;
            r -= 1;
        } else {
            l++;
        }
    }
    std::sort(cards.begin(), cards.begin() + l, mps_cmp());
    std::sort(cards.begin() + l, cards.end(), word_cmp());
}

std::vector<uint8_t> Judge::winStrExchange(std::vector<uint8_t> &cards)
{
    this->mahjongSort(cards);

    //由牌型变换为编码字符串
    std::vector<uint8_t> str_type;
    int                  curr = 1, count = 1;
    //对于非字牌部分
    while (curr < cards.size() && cards[curr] < 120) {
        if (cards[curr - 1] % 30 == cards[curr] % 30) {
            count += 1;
        } else {
            str_type.push_back(count);
            count = 1;
            if (cards[curr - 1] % 30 != cards[curr] % 30 - 1) {
                str_type.push_back(0);
            }
        }
        curr += 1;
    }

    if (curr > 1) { str_type.push_back(count); }
    if (curr > 1) {
        if (curr < cards.size()) {
            str_type.push_back(0);
        }
        curr += 1;
    }
    //对于字牌部分
    while (curr < cards.size()) {
        if (cards[curr - 1] % 10 == cards[curr] % 10) {
            count += 1;
        } else {
            str_type.push_back(count);
            count = 1;
            str_type.push_back(0);
        }
        curr += 1;
    }
    if (curr == cards.size()) {
        str_type.push_back(count);
    }
    return str_type;
}

int Judge::winCodeExchange(std::vector<uint8_t> str_type)
{
    //由编码字符串变换为int编码
    uint32_t code = 0;
    int      i    = 0, to_be_coded, bitsnum;
    while (i < str_type.size()) {
        switch (str_type[i]) {
            case 1:
                to_be_coded = 0;
                bitsnum     = 0;
                break;
            case 2:
                to_be_coded = 3;
                bitsnum     = 2;
                break;
            case 3:
                to_be_coded = 15;
                bitsnum     = 4;
                break;
            case 4:
                to_be_coded = 63;
                bitsnum     = 6;
        }
        code = code << bitsnum;
        code += to_be_coded;
        if ((i < str_type.size() - 1) && (str_type[i + 1] == 0)) {
            code = code << 2;
            code += 2;
            i += 2;
        } else {
            code = code << 1;
            i += 1;
        }
    }

    return code;
}

void Judge::winCodeSetConstruct()
{
    int  triplet;     //刻子的个数
    int  sequence;    //顺子的个数
    int  pair_pos;    //雀头的位置
    int  pos0, pos1, pos2, pos3;
    int *pos[4];    //面子1、2、3、4的位置
    int  i, j;

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
                            for (i; i < triplet; i++) {
                                if (pattern_proto[*(pos[i])] <= 1) {
                                    pattern_proto[*(pos[i])] += 3;
                                } else {
                                    i = 6;
                                }
                            }
                            for (i; i < 4; i++) {
                                if ((pattern_proto[*(pos[i])] <= 3) && (pattern_proto[*(pos[i]) + 1] <= 3) && (pattern_proto[*(pos[i]) + 2] <= 3)) {
                                    pattern_proto[*(pos[i])] += 1;
                                    pattern_proto[*(pos[i]) + 1] += 1;
                                    pattern_proto[*(pos[i]) + 2] += 1;
                                } else {
                                    i = 6;
                                }
                            }

                            if (i < 6) {
                                pattern.clear();
                                i = 0;
                                while (pattern_proto[i] == 0) {
                                    i++;
                                }
                                pattern.push_back(pattern_proto[i]);
                                i++;
                                for (i; i < 18; i++) {
                                    if ((pattern_proto[i] == 0) && (pattern[pattern.size() - 1] == 0)) {
                                        continue;
                                    } else {
                                        pattern.push_back(pattern_proto[i]);
                                    }
                                }
                                if (pattern[pattern.size() - 1] == 0) { pattern.pop_back(); }
                                pattern_set.insert(this->winCodeExchange(pattern));
                            }
                        }
                    }
                }
            }
        }
    }

    std::vector<std::vector<int>> combinations = combinationEnumeration<int>({ 0, 1, 2, 3, 4, 5 });
    for (std::vector<int> combination: combinations) {
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

std::vector<std::vector<std::vector<uint8_t>>> Judge::handDivision(std::vector<uint8_t> hand, int exposure_size)
{
    //将手牌hashmap化
    std::vector<uint8_t> hand_division(37, 0);
    for (uint8_t card: hand) {
        if (card < 120) {
            hand_division[card % 30] += 1;
        } else {
            hand_division[30 + card % 10] += 1;
        }
    }

    //result最外层的vector代表各分配方案，每个分配方案要求：{{刻子数, 顺子数}, {雀头}, {刻子1}, ..., {顺子1}, ...}
    std::vector<std::vector<std::vector<uint8_t>>> result;
    std::vector<uint8_t>                           pairs = findPairs(hand_division);

    //对于每个可能的雀头
    for (uint8_t pair: pairs) {
        std::vector<uint8_t> hand_without_pair = hand_division;
        hand_without_pair[pair] -= 2;

        //对于当前情况下找到可能的所有刻子组合
        std::vector<uint8_t>              triplets     = findTriplets(hand_without_pair);
        std::vector<std::vector<uint8_t>> combinations = combinationEnumeration<uint8_t>(triplets);

        //对于每种刻子组合
        for (std::vector<uint8_t> combination: combinations) {
            std::vector<uint8_t> hand_without_pair_or_triplet = hand_without_pair;
            for (uint8_t triplet: combination) {
                hand_without_pair_or_triplet[triplet] -= 3;
            }

            //找到所有顺子并判断是否符号胡牌条件，如果符合，按照要求构造并加入result
            std::vector<std::vector<uint8_t>> sequences = findSequences(hand_without_pair_or_triplet);
            if ((sequences.size() + combination.size()) == (4 - exposure_size)) {
                std::vector<std::vector<uint8_t>> result_n{
                    {(uint8_t) combination.size(), (uint8_t) sequences.size()}
                };
                result_n.emplace_back(std::vector<uint8_t>(2, pair));
                for (uint8_t triplet: combination) {
                    result_n.emplace_back(std::vector<uint8_t>(3, triplet));
                }
                for (std::vector<uint8_t> sequence: sequences) {
                    result_n.emplace_back(sequence);
                }
                result.push_back(result_n);
            }
        }
    }
    return result;
}

bool YakuJudge::tanyaoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int     i, j;
    uint8_t curr;
    for (i = 1; i < hand_divided.size(); i++) {
        for (j = 0; j < hand_divided[i].size(); j++) {
            curr = hand_divided[i][j];
            if ((curr % 10 == 1) || (curr % 10 == 9) || (curr >= 30)) {
                return false;
            }
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        for (j = 0; j < exposures[i].cards.size(); j++) {
            curr = (exposures[i].cards[j] < 120) ? (exposures[i].cards[j] % 30) : (exposures[i].cards[j] % 10 + 30);
            if ((curr % 10 == 1) || (curr % 10 == 9) || (curr >= 30)) {
                return false;
            }
        }
    }
    return true;
}

bool YakuJudge::menfonJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures, uint8_t menfon)
{
    int i;
    for (i = 2; i < hand_divided.size(); i++) {
        if ((hand_divided[i][0] >= 30) && (hand_divided[i][0] == menfon)) {
            return true;
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        if ((exposures[i].cards[0] >= 120) && ((exposures[i].cards[0] % 10) == (menfon % 10))) {
            return true;
        }
    }
    return false;
}

bool YakuJudge::chanfonJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures, uint8_t chanfon)
{
    int i;
    for (i = 2; i < hand_divided.size(); i++) {
        if (hand_divided[i][0] == chanfon) {
            return true;
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        if ((exposures[i].cards[0] >= 120) && ((exposures[i].cards[0] % 10) == (chanfon % 10))) {
            return true;
        }
    }
    return false;
}

bool YakuJudge::hakuJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int i;
    for (i = 2; i < hand_divided.size(); i++) {
        if (hand_divided[i][0] == 34) {
            return true;
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        if ((exposures[i].cards[0] >= 120) && ((exposures[i].cards[0] % 10) == 4)) {
            return true;
        }
    }
    return false;
}

bool YakuJudge::hatsuJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int i;
    for (i = 2; i < hand_divided.size(); i++) {
        if (hand_divided[i][0] == 35) {
            return true;
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        if ((exposures[i].cards[0] >= 120) && ((exposures[i].cards[0] % 10) == 5)) {
            return true;
        }
    }
    return false;
}

bool YakuJudge::tyunJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int i;
    for (i = 2; i < hand_divided.size(); i++) {
        if (hand_divided[i][0] == 36) {
            return true;
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        if ((exposures[i].cards[0] >= 120) && ((exposures[i].cards[0] % 10) == 6)) {
            return true;
        }
    }
    return false;
}

bool YakuJudge::pinhuJudge(std::vector<std::vector<uint8_t>> hand_divided, uint8_t chanfon, uint8_t menfon, uint8_t _card)
{
    if (hand_divided[0][1] != 4) {
        return false;
    }
    if ((hand_divided[1][0] == chanfon) || (hand_divided[1][0] == menfon) || (hand_divided[1][0] >= 34)) {
        return false;
    }
    _card = _card % 30;
    for (int i = hand_divided[0][0] + 2; i < hand_divided.size(); i++) {
        if ((hand_divided[i][0] == _card) || (hand_divided[i][2] == _card)) {
            return true;
        }
    }
    return false;
}

bool YakuJudge::ipekoJudge(std::vector<std::vector<uint8_t>> hand_divided)
{
    for (int i = 2; i < hand_divided.size(); i++) {
        for (int j = i + 1; j < hand_divided.size(); j++) {
            if (hand_divided[i] == hand_divided[j]) {
                return true;
            }
        }
    }
    return false;
}

bool YakuJudge::sansyokudoujunJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int i, j, k;
    for (auto exposure: exposures) {
        if (exposure.type == 1) {
            for (i = 0; i < 3; i++) {
                exposure.cards[i] = exposure.cards[i] % 30;
            }
            hand_divided.push_back(exposure.cards);
        }
    }
    for (i = (hand_divided[0][0] + 2); i < hand_divided.size(); i++) {
        for (j = i + 1; j < hand_divided.size(); j++) {
            for (k = j + 1; k < hand_divided.size(); k++) {
                std::vector<uint8_t> tmp{ hand_divided[i][0], hand_divided[j][0], hand_divided[k][0] };
                sort(tmp.begin(), tmp.end(), std::less<uint8_t>());
                if ((tmp[1] - tmp[0] == 10) && (tmp[2] - tmp[1] == 10)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool YakuJudge::sansyokudoukoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int                               i, j, k;
    std::vector<std::vector<uint8_t>> triplets;
    for (i = 2; i < 2 + hand_divided[0][0]; i++) {
        triplets.push_back(hand_divided[i]);
    }
    for (auto exposure: exposures) {
        if (exposure.type == 0) {
            if (exposure.cards[0] < 120) {
                for (i = 0; i < 3; i++) {
                    exposure.cards[i] = exposure.cards[i] % 30;
                }
                triplets.push_back(exposure.cards);
            }
        }
    }
    for (i = 0; i < triplets.size(); i++) {
        for (j = i + 1; j < triplets.size(); j++) {
            for (k = j + 1; k < triplets.size(); k++) {
                std::vector<uint8_t> tmp{ triplets[i][0], triplets[j][0], triplets[k][0] };
                sort(tmp.begin(), tmp.end(), std::less<uint8_t>());
                if ((tmp[1] - tmp[0] == 10) && (tmp[2] - tmp[1] == 10)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool YakuJudge::sankantsuJudge(std::vector<Exposure> &exposures)
{
    int count = 0, i;
    for (i = 0; i < exposures.size(); i++) {
        if (exposures[i].cards.size() == 4) {
            count += 1;
        }
    }
    return count == 3;
}

bool YakuJudge::toitoiJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int count = hand_divided[0][0], i;
    for (i = 0; i < exposures.size(); i++) {
        if (exposures[i].type == 0) {
            count += 1;
        }
    }
    return count == 4;
}

bool YakuJudge::sanankoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures, uint8_t _card, int card_from)
{
    int count = 0, i;
    _card     = (_card >= 120) ? (30 + _card % 10) : (_card % 30);
    for (i = 2; i < 2 + hand_divided[0][0]; i++) {
        if ((card_from == 0) || (hand_divided[i][0] != _card)) {
            count += 1;
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        if ((exposures[i].cards.size() == 4) && (exposures[i].card_from == 0)) {
            count += 1;
        }
    }
    return count == 3;
}

bool YakuJudge::syosangenJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int count = 0, i;
    if (hand_divided[1][0] >= 34) {
        count += 1;
    } else {
        return false;
    }
    for (i = 2; i < hand_divided[0][0] + 2; i++) {
        if (hand_divided[i][0] >= 34) {
            count += 1;
        }
    }
    for (auto exposure: exposures) {
        if (exposure.cards[0] >= 164) {
            count += 1;
        }
    }
    return count == 3;
}

bool YakuJudge::honrotoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int count = hand_divided[0][0], i;
    for (i = 0; i < exposures.size(); i++) {
        if (exposures[i].type == 0) {
            count += 1;
        }
    }
    if (count != 4) {
        return false;
    }
    for (i = 1; i < hand_divided.size(); i++) {
        if ((hand_divided[i][0] < 30) && (hand_divided[i][0] % 10 != 1) && (hand_divided[i][0] % 10 != 9)) {
            return false;
        }
    }
    for (auto exposure: exposures) {
        if ((exposure.cards[0] < 120) && (exposure.cards[0] % 10 != 1) && (exposure.cards[0] % 10 != 9)) {
            return false;
        }
    }
    return true;
}

bool YakuJudge::ittsuJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int i, j, k;
    for (auto exposure: exposures) {
        if (exposure.type == 1) {
            for (i = 0; i < 3; i++) {
                exposure.cards[i] = exposure.cards[i] % 30;
            }
            hand_divided.push_back(exposure.cards);
        }
    }
    for (i = (hand_divided[0][0] + 2); i < hand_divided.size(); i++) {
        for (j = i + 1; j < hand_divided.size(); j++) {
            for (k = j + 1; k < hand_divided.size(); k++) {
                std::vector<uint8_t> tmp{ hand_divided[i][0], hand_divided[j][0], hand_divided[k][0] };
                sort(tmp.begin(), tmp.end(), std::less<uint8_t>());
                if ((tmp[0] % 10 == 1) && (tmp[1] - tmp[0] == 3) && (tmp[2] - tmp[1] == 3)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool YakuJudge::chantaJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int  i;
    bool sign;
    int  count = hand_divided[0][1];
    for (i = 1; i < hand_divided.size(); i++) {
        sign = false;
        for (uint8_t card: hand_divided[i]) {
            if ((card % 10 == 1) || (card % 10 == 9) || (card >= 30)) {
                sign = true;
            }
        }
        if (!sign) {
            return false;
        }
    }
    for (auto exposure: exposures) {
        if (exposure.type == 1) { count += 1; }
        sign = false;
        for (uint8_t card: exposure.cards) {
            if ((card % 10 == 1) || (card % 10 == 9) || (card >= 120)) {
                sign = true;
            }
        }
        if (!sign) {
            return false;
        }
    }
    if (count == 0) {
        return false;
    }
    return true;
}

bool YakuJudge::junchanJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int  i;
    bool sign;
    int  count = hand_divided[0][1];
    for (i = 1; i < hand_divided.size(); i++) {
        sign = false;
        for (uint8_t card: hand_divided[i]) {
            if (((card % 10 == 1) || (card % 10 == 9)) && (card < 30)) {
                sign = true;
            }
        }
        if (!sign) {
            return false;
        }
    }
    for (auto exposure: exposures) {
        if (exposure.type == 1) { count += 1; }
        sign = false;
        for (uint8_t card: exposure.cards) {
            if (((card % 10 == 1) || (card % 10 == 9)) && (card < 120)) {
                sign = true;
            }
        }
        if (!sign) {
            return false;
        }
    }
    if (count == 0) {
        return false;
    }
    return true;
}

bool YakuJudge::ryanpekoJudge(std::vector<std::vector<uint8_t>> hand_divided)
{
    int i, j, k, count = 0;
    if (hand_divided[0][1] != 4) {
        return false;
    }
    for (i = 2; i < hand_divided.size(); i++) {
        for (j = i + 1; j < hand_divided.size(); j++) {
            if (hand_divided[i] == hand_divided[j]) {
                std::vector<int> tmp;
                for (k = 2; k < 6; k++) {
                    if ((k != i) && (k != j)) {
                        tmp.push_back(k);
                    }
                }
                if (hand_divided[tmp[0]] == hand_divided[tmp[1]]) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool YakuJudge::honitsuJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int cardmap[37]{ 0 }, i, j;
    for (i = 1; i < hand_divided.size(); i++) {
        for (j = 0; j < hand_divided[i].size(); j++) {
            cardmap[hand_divided[i][j]] += 1;
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        for (j = 0; j < exposures[i].cards.size(); j++) {
            if (exposures[i].cards[j] >= 120) {
                cardmap[30 + exposures[i].cards[j] % 10] += 1;
            } else {
                cardmap[exposures[i].cards[j] % 30] += 1;
            }
        }
    }
    j = 0;
    for (i = 0; i < 10; i++) {
        if (cardmap[i] != 0) {
            j += 1;
            break;
        }
    }
    for (i = 10; i < 20; i++) {
        if (cardmap[i] != 0) {
            j += 1;
            break;
        }
    }
    for (i = 20; i < 30; i++) {
        if (cardmap[i] != 0) {
            j += 1;
            break;
        }
    }
    if (j == 1) { return true; }
    return false;
}

bool YakuJudge::chinitsuJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int cardmap[37]{ 0 }, i, j;
    for (i = 1; i < hand_divided.size(); i++) {
        for (j = 0; j < hand_divided[i].size(); j++) {
            cardmap[hand_divided[i][j]] += 1;
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        for (j = 0; j < exposures[i].cards.size(); j++) {
            if (exposures[i].cards[j] >= 120) {
                cardmap[30 + exposures[i].cards[j] % 10] += 1;
            } else {
                cardmap[exposures[i].cards[j] % 30] += 1;
            }
        }
    }
    j = 0;
    for (i = 0; i < 10; i++) {
        if (cardmap[i] != 0) {
            j += 1;
            break;
        }
    }
    for (i = 10; i < 20; i++) {
        if (cardmap[i] != 0) {
            j += 1;
            break;
        }
    }
    for (i = 20; i < 30; i++) {
        if (cardmap[i] != 0) {
            j += 1;
            break;
        }
    }
    for (i = 30; i < 37; i++) {
        if (cardmap[i] != 0) {
            j += 1;
            break;
        }
    }
    if (j == 1) { return true; }
    return false;
}

bool YakuJudge::daisangenJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int count = 0, i;
    for (i = 2; i < hand_divided[0][0] + 2; i++) {
        if (hand_divided[i][0] >= 34) {
            count += 1;
        }
    }
    for (auto exposure: exposures) {
        if (exposure.cards[0] >= 164) {
            count += 1;
        }
    }
    return count == 3;
}

bool YakuJudge::suankoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures, uint8_t _card, int card_from)
{
    int count = 0, i;
    _card     = (_card >= 120) ? (30 + _card % 10) : (_card % 30);
    for (i = 2; i < 2 + hand_divided[0][0]; i++) {
        if ((card_from == 0) || (hand_divided[i][0] != _card)) {
            count += 1;
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        if ((exposures[i].cards.size() == 4) && (exposures[i].card_from == 0)) {
            count += 1;
        }
    }
    return count == 4;
}

bool YakuJudge::suankotankiJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures, uint8_t _card)
{
    int count = 0, i;
    _card     = (_card >= 120) ? (30 + _card % 10) : (_card % 30);
    if (_card != hand_divided[1][0]) {
        return false;
    }
    for (i = 2; i < 2 + hand_divided[0][0]; i++) {
        count += 1;
    }
    for (i = 0; i < exposures.size(); i++) {
        if ((exposures[i].cards.size() == 4) && (exposures[i].card_from == 0)) {
            count += 1;
        }
    }
    return count == 4;
}

bool YakuJudge::tsuisouJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int i;
    for (i = 1; i < hand_divided.size(); i++) {
        if (hand_divided[i][0] < 30) {
            return false;
        }
    }
    for (i = 1; i < exposures.size(); i++) {
        if (exposures[i].cards[0] < 120) {
            return false;
        }
    }
    return true;
}

bool YakuJudge::ryuisoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int     i, j;
    uint8_t tmp;
    for (i = 1; i < hand_divided.size(); i++) {
        for (j = 0; j < hand_divided[i].size(); j++) {
            if ((hand_divided[i][j] != 22) && (hand_divided[i][j] != 23) && (hand_divided[i][j] != 24)
                && (hand_divided[i][j] != 26) && (hand_divided[i][j] != 28) && (hand_divided[i][j] != 35)) {
                return false;
            }
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        for (j = 0; j < exposures[i].cards.size(); j++) {
            tmp = (exposures[i].cards[j] >= 120) ? (30 + exposures[i].cards[j] % 10) : (exposures[i].cards[j] % 30);
            if ((tmp != 22) && (tmp != 23) && (tmp != 24) && (tmp != 26) && (tmp != 28) && (tmp != 35)) {
                return false;
            }
        }
    }
    return true;
}

bool YakuJudge::chinrotoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int count = hand_divided[0][0], i;
    for (i = 0; i < exposures.size(); i++) {
        if (exposures[i].type == 0) {
            count += 1;
        }
    }
    if (count != 4) {
        return false;
    }
    for (i = 1; i < hand_divided.size(); i++) {
        if ((hand_divided[i][0] >= 30) || ((hand_divided[i][0] % 10 != 1) && (hand_divided[i][0] % 10 != 9))) {
            return false;
        }
    }
    for (auto exposure: exposures) {
        if ((exposure.cards[0] >= 120) || ((exposure.cards[0] % 10 != 1) && (exposure.cards[0] % 10 != 9))) {
            return false;
        }
    }
    return true;
}

bool YakuJudge::sukantsuJudge(std::vector<Exposure> &exposures)
{
    int count = 0, i;
    for (i = 0; i < exposures.size(); i++) {
        if (exposures[i].cards.size() == 4) {
            count += 1;
        }
    }
    return count == 4;
}

bool YakuJudge::tyurenpotoJudge(std::vector<std::vector<uint8_t>> hand_divided)
{
    int  cardmap[30]{ 0 }, i, j;
    bool sign;
    for (i = 1; i < hand_divided.size(); i++) {
        for (j = 0; j < hand_divided[i].size(); j++) {
            if (hand_divided[i][j] < 30) {
                cardmap[hand_divided[i][j]] += 1;
            }
        }
    }
    if ((cardmap[1] >= 3) && (cardmap[9] >= 3)) {
        bool sign = 1;
        for (i = 2; i < 9; i++) {
            if (cardmap[i] == 0) {
                sign = false;
                break;
            }
        }
        if (sign) { return true; }
    }
    if ((cardmap[11] >= 3) && (cardmap[19] >= 3)) {
        bool sign = 1;
        for (i = 12; i < 19; i++) {
            if (cardmap[i] == 0) {
                sign = false;
                break;
            }
        }
        if (sign) { return true; }
    }
    if ((cardmap[21] >= 3) && (cardmap[29] >= 3)) {
        bool sign = 1;
        for (i = 22; i < 29; i++) {
            if (cardmap[i] == 0) {
                sign = false;
                break;
            }
        }
        if (sign) { return true; }
    }
    return false;
}

bool YakuJudge::tyunrenkyuuJudge(std::vector<std::vector<uint8_t>> hand_divided, uint8_t _card)
{
    if (_card >= 120) { return false; }
    _card = (_card >= 120) ? (30 + _card % 10) : (_card % 30);
    int  cardmap[30]{ 0 }, i, j, r = _card / 10;
    bool sign;
    for (i = 1; i < hand_divided.size(); i++) {
        for (j = 0; j < hand_divided[i].size(); j++) {
            if (hand_divided[i][j] < 30) {
                cardmap[hand_divided[i][j]] += 1;
            }
        }
    }
    cardmap[_card] -= 1;
    if ((cardmap[r * 10 + 1] == 3) && (cardmap[r * 10 + 9] == 3)) {
        bool sign = 1;
        for (i = r * 10 + 2; i < r * 10 + 9; i++) {
            if (cardmap[i] != 1) {
                sign = false;
                break;
            }
        }
        if (sign) { return true; }
    }
    return false;
}

bool YakuJudge::syosushiJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int cardmap[4]{ 0 }, i, j, count = 0;
    if ((hand_divided[1][0] < 30) || (hand_divided[1][0] > 33)) {
        return false;
    }
    for (i = 2; i < hand_divided.size(); i++) {
        for (j = 0; j < hand_divided[i].size(); j++) {
            if ((hand_divided[i][j] >= 30) && (hand_divided[i][j] <= 33)) {
                cardmap[hand_divided[i][j] - 30] += 1;
            }
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        for (j = 0; j < exposures[i].cards.size(); j++) {
            if ((exposures[i].cards[j] >= 120) && (exposures[i].cards[j] < 160)) {
                cardmap[exposures[i].cards[j] % 10] += 1;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (cardmap[i] >= 3) {
            count += 1;
        }
    }
    return count == 3;
}

bool YakuJudge::daisushiJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures)
{
    int cardmap[4]{ 0 }, i, j, count = 0;
    for (i = 2; i < hand_divided.size(); i++) {
        for (j = 0; j < hand_divided[i].size(); j++) {
            if ((hand_divided[i][j] >= 30) && (hand_divided[i][j] <= 33)) {
                cardmap[hand_divided[i][j] - 30] += 1;
            }
        }
    }
    for (i = 0; i < exposures.size(); i++) {
        for (j = 0; j < exposures[i].cards.size(); j++) {
            if ((exposures[i].cards[j] >= 120) && (exposures[i].cards[j] < 160)) {
                cardmap[exposures[i].cards[j] % 10] += 1;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (cardmap[i] >= 3) {
            count += 1;
        }
    }
    return count == 4;
}
