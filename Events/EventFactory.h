//
// Created by Ido Amit on 27/01/2025.
//
#pragma once
#include <functional>
#include "Monster.h"

/**************     factory   ********************/
/**
 *factory method - creates an event from a string description
 */

class EventFactory {
private:
    std::map<std::string, std::function<std::unique_ptr<Event>()>> eventFactoryMap;

public:
    ~EventFactory() = default;
    EventFactory() {
        eventFactoryMap["Snail"] = []() { return std::make_unique<Snail>(); };
        eventFactoryMap["Slime"] = [](){return std::make_unique<Slime>();};
        eventFactoryMap["Balrog"] = []() { return std::make_unique<Balrog>(); };
        eventFactoryMap["Pack"] = []() { return std::make_unique<Pack>(); };
        eventFactoryMap["SolarEclipse"] = []() { return std::make_unique<SolarEclipse>(); };
        eventFactoryMap["PotionsMerchant"] = []() { return std::make_unique<PotionMerchant>(); };
    }

    [[nodiscard]] std::unique_ptr<Event> createEvent(const std::string& eventName) const {
        auto it = eventFactoryMap.find(eventName);
        if (it == eventFactoryMap.end()) {
            throw std::runtime_error("Invalid Events File");
        }
        return it->second();
    }
};
