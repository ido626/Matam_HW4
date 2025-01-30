//
// Created by Ido Amit on 26/01/2025.
//
#include <string>
#include "Player.h"

unsigned int Warrior::calculateCombatPower(const Player& player) const {
    return player.getForce()*2 + player.getLevel();
}

std::string Warrior::getType(){
    return "Warrior";
}