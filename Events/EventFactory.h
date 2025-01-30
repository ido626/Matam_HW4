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

    void readEvents(std::istream& eventsStream) {
        if (!eventsStream) {
            throw std::runtime_error("Invalid Events File");
        }

        std::string eventName;
        while (eventsStream >> eventName) {
            if (eventName == "Pack") {
                auto pack = parsePack(eventsStream);
                Event::eventList.push_back(std::move(pack));
            } else {
                auto event = createEvent(eventName);
                Event::eventList.push_back(std::move(event));
            }
        }
    }

    std::unique_ptr<Pack> parsePack(std::istream& eventsStream) {
    int packSize;
    if (!(eventsStream >> packSize) || packSize <= 0) {
        throw std::runtime_error("Invalid Events File");
    }

    std::vector<std::unique_ptr<Monster>> packMembers;
    for (int i = 0; i < packSize; i++) {
        std::string eventName;
        if (!(eventsStream >> eventName)) {
            throw std::runtime_error("Invalid Events File");
        }

        if (eventName == "Pack") {
            auto nestedPack = parsePack(eventsStream); // Recursive call
            packMembers.push_back(std::move(nestedPack));
        } else {
            auto event = createEvent(eventName);
            if (auto monster = dynamic_cast<Monster*>(event.get())) {
                packMembers.push_back(std::make_unique<Monster>(*monster));
            } else {
                throw std::runtime_error("Invalid Events File");
            }
        }
    }

    return Pack::createPack(std::move(packMembers));
    }
};
