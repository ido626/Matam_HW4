//
// Created by Ido Amit on 27/01/2025.
//
#include "Monster.h"
#include "../Utilities.h"

string applyBattle(Player& player, Monster& monster) {
    unsigned int playerCP = player.getJob()->calculateCombatPower(player);
    if (playerCP > monster.getDamage()) { // Player wins the fight
        player.setLevel(player.getLevel() + 1);
        player.setCoins(player.getCoins() + monster.getLoot());
        if (player.getJob()->getType() == "Warrior") {
            player.setHealthPoints(player.getHealthPoints() - 10);
        }
        return getEncounterWonMessage(player, monster.getLoot());
    }
    else { // Player loses the battle
        player.setHealthPoints(player.getHealthPoints() - monster.getDamage());
        return getEncounterLostMessage(player, monster.getDamage());
    }
}