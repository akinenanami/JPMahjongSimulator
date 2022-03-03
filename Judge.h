//
// Created by tyl on 2022/1/6.
//

#ifndef JPMAHJONGSIMULATOR_JUDGE_H
#define JPMAHJONGSIMULATOR_JUDGE_H

#include "CommonHeaders.h"

class Judge
{
public:
    void                                           winCodeSetConstruct();                                                  //构造和了判定码集合
    std::vector<uint8_t>                           winStrExchange(std::vector<uint8_t> &cards);                            //由手牌变换为牌型字符串
    int                                            winCodeExchange(std::vector<uint8_t> str_type);                         //由牌型字符串变换为编码
    void                                           mahjongSort(std::vector<uint8_t> &cards);                               //手牌排序
    std::vector<std::vector<std::vector<uint8_t>>> handDivision(std::vector<uint8_t> hand_division, int exposure_size);    //手牌牌型分割

private:
    std::unordered_set<int> WinCodeSet;
};

class YakuJudge
{
public:
    bool tanyaoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                   //断幺
    bool menfonJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures, uint8_t menfon);                   //门风
    bool chanfonJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures, uint8_t chanfon);                 //场风
    bool hakuJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                     //白
    bool hatsuJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                    //发
    bool tyunJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                     //中
    bool pinhuJudge(std::vector<std::vector<uint8_t>> hand_divided, uint8_t chanfon, uint8_t menfon, uint8_t _card);                      //平胡
    bool ipekoJudge(std::vector<std::vector<uint8_t>> hand_divided);                                                                      //一杯口
    bool sansyokudoujunJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                           //三色同顺
    bool sansyokudoukoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                            //三色同刻
    bool sankantsuJudge(std::vector<Exposure> &exposures);                                                                                //三杠子
    bool toitoiJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                   //对对
    bool sanankoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures, uint8_t _card, int card_from);    //三暗刻
    bool syosangenJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                //小三元
    bool honrotoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                  //混老头
    bool ittsuJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                    //一气贯通
    bool chantaJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                   //混全
    bool junchanJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                  //纯全
    bool ryanpekoJudge(std::vector<std::vector<uint8_t>> hand_divided);                                                                   //两杯口
    bool honitsuJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                  //混一色
    bool chinitsuJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                 //清一色

    bool daisangenJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                               //大三元
    bool suankoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures, uint8_t _card, int card_from);    //四暗刻
    bool suankotankiJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures, uint8_t _card);              //四暗刻单骑
    bool tsuisouJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                 //字一色
    bool ryuisoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                  //绿一色
    bool chinrotoJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                //清老头
    bool sukantsuJudge(std::vector<Exposure> &exposures);                                                                                //四杠子
    bool tyurenpotoJudge(std::vector<std::vector<uint8_t>> hand_divided);                                                                //九莲
    bool tyunrenkyuuJudge(std::vector<std::vector<uint8_t>> hand_divided, uint8_t _card);                                                //纯九莲
    bool syosushiJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                //小四喜
    bool daisushiJudge(std::vector<std::vector<uint8_t>> hand_divided, std::vector<Exposure> &exposures);                                //大四喜
};

#endif    //JPMAHJONGSIMULATOR_JUDGE_H
