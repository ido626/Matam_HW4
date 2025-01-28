//
// Created by Ido Amit on 26/01/2025.
//
#include <string>
#include "Player.h"

unsigned int Warrior::calculateCombatPower(const Player& player) const {
    return player.getForce()*2 + player.getLevel();
}


// std::string Warrior::solarEclipse(Player& player){
//     unsigned int currForce = player.getForce();
//     if (currForce <= 0) {
//         return getSolarEclipseMessage(player, 0);
//     }
//     player.setForce(--currForce);
//     return getSolarEclipseMessage(player, -1);
// }

std::string Warrior::getType(){
    return "Warrior";
}