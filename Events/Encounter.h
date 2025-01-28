//
// Created by Daniel Agmon on 28/01/2025.
//

#pragma once

// #include "Event.h"
#include <string>

class Player;
class Monster;

class Encounter {
public:
    Encounter() = default;
    ~Encounter() = default;

    std::string applyBattle(Player& player, Monster& monster);
};
