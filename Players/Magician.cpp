//
// Created by Ido Amit on 26/01/2025.
//

#include <string>
#include "../Utilities.h"


std::string Magician::solarEclipse(Player& player){
    unsigned int currForce = player.getForce();
    player.setForce(++currForce);
    return getSolarEclipseMessage(player, 1);
}

// unsigned int Magician::calculateCombatPower(const Player& player) const {
//     return player.getForce() + player.getLevel();
// }

std::string  Magician::getType(){
    return "Magician";
}