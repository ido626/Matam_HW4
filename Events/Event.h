
#pragma once


#include <vector>
#include <string>
#include "../Players/Player.h"



class Event {
protected:
    unsigned int CombatPower = 0 ;
    unsigned int Loot = 0 ;
    unsigned int Damage = 0 ;

public:

    virtual ~Event() = default;
    /**
     * Gets the Name of the event
     *
     * @return - the description of the event
    */
    [[nodiscard]] virtual string getDescription() const;
    /**
     * a vector contains all events (input),ordered the same as in eventsStream file
     */
    static std::vector<std::unique_ptr<Event>> eventList;

    virtual string applyEvent(Player& player) = 0;
};

class SolarEclipse : public Event {
public:
    SolarEclipse()= default;
	string applyEvent(Player& player) override {
        return player.getJob()->solarEclipse(player);
	}
    [[nodiscard]] string getDescription() const override {
	    return "SolarEclipse";

	}
};

class PotionMerchant : public Event {
public:
    PotionMerchant() = default;
 	string applyEvent(Player& player) override {
    	return player.getCharacter()->potionMerchant(player);
    }

    [[nodiscard]] string getDescription() const override {
 	    return "PotionsMerchant";

 	}
};