//
// Created by Ido Amit on 26/01/2025.
//
#include <string>

#include "Player.h"

unsigned int calculateCombatPower(const Player& player) {
    return player.getForce()*2 + player.getLevel();
}

string getType(){
    return "Warrior";
}