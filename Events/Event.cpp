//
// Created by Daniel Agmon on 17/01/2025.
//
#include <vector>
#include <iostream>

#include "Event.h"


string Event::getDescription() const{return""; }

std::vector<std::string> Event::events {}; // initialization of events vector
/*
std::unique_ptr<Event> Event::createEvent(const std::string &eventName) {
    if (eventName == "Snail") {
        return std::make_unique<Snail>();
    }
    else if (eventName == "Balrog") {
        return std::make_unique<Balrog>();
    }
    else if (eventName == "Slime") {
        return std::make_unique<Slime>();
    }
    else if (eventName == "Pack") {
        return std::make_unique<Pack>();
    }
    else if (eventName == "SolarEclipse") {
        return std::make_unique<SolarEclipse>();
    }
    else if (eventName == "PotionMerchant") {
        return std::make_unique<PotionMerchant>();
    }
    else {throw std::runtime_error("Invalid Events File");}
}
*/
/*
std::string playEvent(Player & player,const Event & currentEvent, const std::string & eventName) {
    if (encounterEvents.find(eventName) != encounterEvents.end()) // checks if the event is an encounter with a monster
        if (player.getJob().getCombatPower() > currentEvent.getCombatPower()) {
            player.setLevel(player.getLevel() + 1); // player level ++
            player.setCoins(player.getCoins() + currentEvent.getLoot()); //player coins after winning =  player coins + monster loot

            std::string outcome = getEncounterWonMessage(player, currentEvent.getLoot());
            return outcome;
        }else {
            player.setHealthPoints(player.getHealthPoints() - currentEvent.getDamage());// player hp after loosing = player current hp - monster damage

            std::string outcome = getEncounterLostMessage(player, currentEvent.getDamage());
            return outcome;
        }

     if (specialEvents.find(eventName) != specialEvents.end()) {
        if (eventName == "SolarEclipse") {
            std::string outcome = getSolarEclipseMessage(player,currentEvent.solarEclipse(player));
            return outcome;
        }
        else if (eventName == "PotionMerchant") {
            std::string outcome = getPotionsPurchaseMessage(player,currentEvent.potionMerchant(player));
            return outcome;
        }
    }
    return"";
}
*/