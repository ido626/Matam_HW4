//
// Created by Ido Amit on 26/01/2025.
//
#include <string>
#include "../Utilities.h"
#include "Player.h"

std::string Responsible::potionMerchant(Player& player) {
    unsigned int potionAmount = 0;
    if (player.getCharacter()->getType() == "Responsible") {
        while (static_cast<int>(player.getMaxHP()) > player.getHealthPoints() && player.getCoins() >= 5 ) {
            player.setHealthPoints(player.getHealthPoints()+ 10) ;
            player.setCoins(player.getCoins()- 5);
            potionAmount++;
        }
    }
    return getPotionsPurchaseMessage(player, potionAmount);
}

std::string Responsible::getType(){
    return "Responsible";
}