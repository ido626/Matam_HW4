//
// Created by Ido Amit on 26/01/2025.
//
#include <string>
#include "../Utilities.h"
#include "Player.h"

string potionMerchant(Player& player) {
    int potionAmount = 0;
    if (player.getCharacter()->getType() == "Responsible") {
        while (player.getMaxHP() > player.getHealthPoints() && player.getCoins() >= 5 ) {
            player.setHealthPoints(player.getHealthPoints()+ 10) ;
            player.setCoins(player.getCoins()- 5);
            potionAmount++;
        }
    }
    return getPotionsPurchaseMessage(player, potionAmount);
}

string getType(){
    return "Responsible";
}