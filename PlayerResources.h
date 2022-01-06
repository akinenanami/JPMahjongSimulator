//
// Created by tyl on 2021/12/29.
//

#ifndef JPMAHJONGSIMULATOR_PLAYERRESOURCES_H
#define JPMAHJONGSIMULATOR_PLAYERRESOURCES_H

#include "CommonHeaders.h"

struct Exposure {                   //副露面子
    std::vector<uint8_t> cards;
    int resonance_card;             //鸣牌获得的牌
    int card_from;                  //鸣牌来源
    Exposure(std::vector<uint8_t> cards, int resonance_card, int card_from) {
        this->cards = cards;
        this->resonance_card = resonance_card;
        this->card_from = card_from;
    }
};

class PlayResource {
public:
    std::vector<Exposure>       exposures;         //副露
    std::unordered_set<uint8_t> discards_river;    //牌河
    uint8_t                     wind;              //门风
    uint32_t                    score;             //分数
    uint8_t                     riichi;            //立直状态，0未立直，1立直，2两立直

    PlayResource();
    void      newRound(std::vector<uint8_t> initial_hand, uint8_t wind);    //开始新一轮游戏，获取第一手手牌
    bool      winCheck(uint8_t card);                                       //判断是否和了
    Operation whatToDo(uint8_t card);                                       //判断进行何种操作，如摸、吃、碰、杠、胡
    uint8_t   turn(Operation operation, uint8_t card);                      //进行当前回合

private:
    std::vector<uint8_t> hand;    //手牌
};

class Bot: PlayResource {
};

class Player: PlayResource {
};

class Board {
public:
    std::vector<uint8_t> dorasigns;        //所有宝牌指示牌
    uint8_t              wind;             //场风
    int                  heap_pointer;     //牌山指针，指向下一张待摸取的牌
    int                  ridge_pointer;    //岭上指针，指向下一张待摸取的岭上牌
    int                  dora_pointer;     //宝牌指针，指向下一张待翻开的宝牌

    Board();
    void                              newRound(uint8_t wind);    //开始新一轮游戏，洗牌并重新初始化盘面
    std::vector<std::vector<uint8_t>> dealFirstHand();           //发出所有玩家的第一手手牌
    uint8_t                           deal();                    //发出牌山上的下一张牌
    uint8_t                           ridgeDeal();               //发出岭上的下一张牌

private:
    std::vector<uint8_t> heap;    //牌堆
};

void mahjongSort(std::vector<uint8_t> &cards);    //对手牌排序

#endif    //JPMAHJONGSIMULATOR_PLAYERRESOURCES_H
