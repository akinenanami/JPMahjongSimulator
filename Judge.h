//
// Created by tyl on 2022/1/6.
//

#ifndef JPMAHJONGSIMULATOR_JUDGE_H
#define JPMAHJONGSIMULATOR_JUDGE_H

#include "CommonHeaders.h"


class Judge {
public:
    void winCodeSetConstruct();                                                 //构造和了判定码集合
    std::vector<uint8_t> winStrExchange(std::vector<uint8_t> & cards);          //由手牌变换为牌型字符串
    int winCodeExchange(std::vector<uint8_t> str_type);                         //由牌型字符串变换为编码
    void mahjongSort(std::vector<uint8_t> & cards);                             //手牌排序
    std::vector<std::vector<std::vector<uint8_t>>> handDivision(
            std::vector<uint8_t> hand_division, int exposure_size);                      //手牌牌型分割

private:
    std::unordered_set<int> WinCodeSet;
};

#endif //JPMAHJONGSIMULATOR_JUDGE_H
