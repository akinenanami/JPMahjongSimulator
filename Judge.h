//
// Created by tyl on 2022/1/6.
//

#ifndef JPMAHJONGSIMULATOR_JUDGE_H
#define JPMAHJONGSIMULATOR_JUDGE_H

#include "CommonHeaders.h"

const int RIICHI = 0;               //立直
const int TANYAO = 1;               //断幺
const int ZUMA = 2;                 //门前自摸
const int MENFON = 3;               //门风
const int CHANFON = 4;              //场风
const int HAKU = 5;                 //白
const int HATSU = 6;                //发
const int TYUN = 7;                 //中
const int PINHU = 8;                //平胡
const int IPEKO = 9;                //一杯口
const int CHANGAN = 10;             //枪杠
const int RINSHAN = 11;             //岭上开花
const int HAIDE = 12;               //海底摸月
const int KOUDE = 13;                //河底捞鱼
const int IHATSU = 14;              //一发
const int WRIICHI = 15;             //两立直
const int SANSYOKUDOUJUN = 16;      //三色同顺
const int SANSYOKUDOUKO = 17;       //三色同刻
const int SANKANTSU = 18;           //三杠子
const int TOITOI = 19;              //对对和
const int SANANKO = 20;             //三暗刻
const int SYOSANGEN = 21;           //小三元
const int HONROTO = 22;             //混老头
const int CHITOI = 23;              //七对子
const int ITTSU = 24;               //一气贯通
const int CHANTA = 25;              //混全
const int JUNCHAN = 26;             //纯全
const int RYANPEKO = 27;            //两杯口
const int HONITSU = 28;             //混一色
const int CHINITSU = 29;            //清一色

const int TENHOO = 32;              //天和
const int CHIIHOO = 33;             //地和
const int DAISANGEN = 34;           //大三元
const int SUANKO = 35;              //四暗刻
const int TSUISOU = 36;             //字一色
const int RYUISO = 37;              //绿一色
const int CHINROTO = 38;            //清老头
const int KOKUSHI = 39;             //国士无双
const int SUKANTSU = 40;            //四杠子
const int TYURENPOTO = 41;          //九莲宝灯
const int SYOSUSHI = 42;            //小四喜
const int DAISUSHI = 43;            //大四喜
const int SUANKOTANKI = 44;         //四暗刻单骑
const int KOKUSHUJUUSAN = 45;        //国士十三面
const int TYURENKYUU = 46;          //纯九莲


class Judge {
public:
    void winCodeSetConstruct();                                                 //构造和了判定码集合
    std::vector<uint8_t> winStrExchange(std::vector<uint8_t> & cards);          //由手牌变换为牌型字符串
    int winCodeExchange(std::vector<uint8_t> str_type);                         //由牌型字符串变换为编码
    void mahjongSort(std::vector<uint8_t> & cards);                             //手牌排序
    std::vector<std::vector<std::vector<uint8_t>>> handDivision(
            std::vector<uint8_t> hand, int exposure_size);                      //手牌牌型分割

private:
    std::unordered_set<int> WinCodeSet;
};

#endif //JPMAHJONGSIMULATOR_JUDGE_H
