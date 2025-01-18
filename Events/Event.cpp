//
// Created by Daniel Agmon on 17/01/2025.
//
#include <vector>
#include <iostream>
#include "../Players/Player.h"
#include "Event.h"

string Event::getDescription() const{return""; }

std::vector<std::string> Event::events {}; // initialization of events vector
std::set<std::string> allGameEvents = {"Snail", "Balrog" ,"Slime", "Pack", "SolarEclipse", "PotionMerchant" };// initialization of all known game events set

/** Special Events**/
void SolarEclipse(Player& player) {
        if (player.getJob() == "Magician") {
            player.CombatPower() += 1;
        }else {player.CombatPower -= 1;}

}

void PotionMerchant(Player& player) {
    if (player.getBehavior == "Responsible") {
            while (player.getMaxHp() > player.getHealth() && player.getCoins() >= 5 ) {
                player.setHealth() += 10;
                player.setCoins() -= 5;
            }
    }else if (player.getBehavior == "RiskTaking") {
            if (player.getHealthPoints() < 50 && player.getCoins()>=5) {
                player.setHealth() += 10;
                player.setCoins() -= 5;
            }
    }
}