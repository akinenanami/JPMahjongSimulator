//
// Created by tyl on 2021/12/29.
//

#include "PlayerResources.h"



void mahjongSort(std::vector<uint8_t> & cards) {
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

std::vector<uint8_t> winTypeExchange(std::vector<uint8_t> & cards) {
    std::vector<uint8_t> result;
    int curr = 1, count = 1;
    while (curr < cards.size() && cards[curr] < 120) {
        if (cards[curr - 1] % 30 == cards[curr] % 30)
            count += 1;
        else {
            result.push_back(count);
            count = 1;
            if (cards[curr - 1] % 30 != cards[curr] % 30 - 1)
                result.push_back(0);
        }
        curr += 1;
    }

    if (curr > 1) result.push_back(count);
    if (curr > 1) {
        if (curr < cards.size())
            result.push_back(0);
        curr += 1;
    }

    while (curr < cards.size()) {
        if (cards[curr - 1] % 10 == cards[curr] % 10)
            count += 1;
        else {
            result.push_back(count);
            count = 1;
            result.push_back(0);
        }
        curr += 1;
    }
    if (curr == cards.size())
        result.push_back(count);
    return result;
}

std::unordered_set<int> winCombinationSetConstruct(){

}
