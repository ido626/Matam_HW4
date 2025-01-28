//
// Created by Ido Amit on 26/01/2025.
//

#include <string>
#include "Player.h"
#include "Job.h"
#include "../Utilities.h"


unsigned int Archer::calculateCombatPower(const Player& player) const {
    return player.getForce() + player.getLevel();
}

std::string Archer::solarEclipse(Player& player){
    unsigned int currForce = player.getForce();
    if (currForce <= 0) {
        return getSolarEclipseMessage(player, 0);
    }
    player.setForce(--currForce);
    return getSolarEclipseMessage(player, -1);
}
std::string Archer::getType(){
    return "Archer";
}