//
// Created by Ido Amit on 26/01/2025.
//
#include "Player.h"
#include "Job.h"
#include "../Utilities.h"


unsigned int calculateCombatPower(const Player& player){
    return player.getForce() + player.getLevel();
}

string solarEclipse(Player& player){
    unsigned int currForce = player.getForce();
    if (currForce <= 0) {
        return getSolarEclipseMessage(player, 0);
    }
    player.setForce(--currForce);
    return getSolarEclipseMessage(player, -1);
}
