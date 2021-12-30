//
// Created by tyl on 2021/12/29.
//

#ifndef JPMAHJONGSIMULATOR_ROUND_H
#define JPMAHJONGSIMULATOR_ROUND_H

#include "CommonHeaders.h"
#include "PlayerResources.h"

class Round {
public:
    std::queue<PlayResource *> player_turn_queue;
};

#endif    //JPMAHJONGSIMULATOR_ROUND_H
