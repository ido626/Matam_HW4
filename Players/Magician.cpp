//
// Created by Ido Amit on 26/01/2025.
//

#include "Player.h"
#include "../Utilities.h"
#include <string>

string solarEclipse(Player& player){
    unsigned int currForce = player.getForce();
    player.setForce(++currForce);
    return getSolarEclipseMessage(player, 1);
}

string getType(){
    return "Magician";
}