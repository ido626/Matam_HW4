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

std::unique_ptr<Event> createEvent(const std::string & eventName) {
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

void playEvent(const Player & player,std::make_unique<monster>()) {
    if (player.getCombatPower() > )
}
////////////// your here //////////////////////