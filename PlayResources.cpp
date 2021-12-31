//
// Created by tyl on 2021/12/29.
//

#include "PlayerResources.h"

void mahjongSort(std::vector<uint8_t> &cards)
{
    struct mps_cmp {
        bool operator()(uint8_t a, uint8_t b)
        {
            if ((a % 30) < (b % 30)) return true;
            else if (((a % 30) == (b % 30)) && (a < b)) return true;
            else return false;
        }
    };

    struct word_cmp {
        bool operator()(uint8_t a, uint8_t b)
        {
            return (a % 10) < (b % 10);
        }
    };

    int     l = 0, r = cards.size() - 1;
    uint8_t exchange;
    while (l != r + 1)
        if (cards[l] >= 120) {
            exchange = cards[l];
            cards[l] = cards[r];
            cards[r] = exchange;
            r -= 1;
        } else l++;
    std::sort(cards.begin(), cards.begin() + l, mps_cmp());
    std::sort(cards.begin() + l, cards.end(), word_cmp());
}

uint32_t winTypeExchange(std::vector<uint8_t> &cards)
{
    mahjongSort(cards);

    //由牌型变换为编码字符串
    std::vector<uint8_t> str_type;
    int                  curr = 1, count = 1;
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

std::unordered_set<int> winCombinationSetConstruct()
{
}
