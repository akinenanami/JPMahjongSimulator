//
// Created by tyl on 2021/12/29.
//

#ifndef JPMAHJONGSIMULATOR_PLAYERRESOURCES_H
#define JPMAHJONGSIMULATOR_PLAYERRESOURCES_H

#include "CommonHeaders.h"

class PlayResource {
public:
    std::vector<uint8_t>        exposure;
    std::unordered_set<uint8_t> discards_river;
    uint8_t                     wind;

    PlayResource();
    void      newRound(std::vector<uint8_t> initial_hand, uint8_t wind);
    bool      winCheck(uint8_t card);
    int       scoring(uint8_t card);
    Operation whatToDo(uint8_t card);
    uint8_t   turn(Operation operation, uint8_t card);

private:
    std::vector<uint8_t> hand;
};

class Bot: PlayResource {
};

class Player: PlayResource {
};

class Board {
public:
    std::vector<uint8_t> dorasigns;
    uint8_t              wind;
    int                  heap_pointer;
    int                  ridge_pointer;
    int                  dora_pointer;

    Board();
    void                              newRound(uint8_t wind);
    std::vector<std::vector<uint8_t>> dealFirstHand();
    uint8_t                           deal();
    uint8_t                           ridgeDeal();

private:
    std::vector<uint8_t> heap;
};

#endif    //JPMAHJONGSIMULATOR_PLAYERRESOURCES_H
