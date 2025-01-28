//
// Created by Ido Amit on 26/01/2025.
//
#include <string>
#include "../Utilities.h"

std::string RiskTaking::potionMerchant(Player& player) {
    int potionAmount = 0;
    if (player.getHealthPoints() < 50 && player.getCoins()>=5) {
        player.setHealthPoints(player.getHealthPoints() + 10) ;
        player.setCoins(player.getCoins()- 5);
        potionAmount++;
    }
    return getPotionsPurchaseMessage(player, potionAmount);

}

std::string RiskTaking::getType(){
    return "RiskTaking";
}