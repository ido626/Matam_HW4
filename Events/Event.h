
#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <stdexcept>
#include "../Utilities.h"
#include "../Players/Player.h"



class Event {
    protected:
    unsigned int CombatPower = 0 ;
    int Loot = 0 ;
    int Damage = 0 ;

public:
    virtual ~Event() = default;
    /**
     * Gets the Name of the event
     *
     * @return - the description of the event
    */
    [[nodiscard]] virtual string getDescription() const = 0;
    /**
     * a vector contains all events (input),ordered the same as in eventsStream file
     */
    static std::vector<std::string> events;

/*
    virtual int solarEclipse(Player& player)const;
    virtual int potionMerchant(Player& player)const;
*/
};

/** Base class Monster **/

class Monster:public Event{ // the base class
    protected:
    string monsterName;

    public:
    /** constructor & destructor **/
    Monster(const std::string& name ,unsigned int power, int loot, int damage)
        :monsterName(name) {
        CombatPower = power;
        Loot = loot;
        Damage = damage;
    }
    ~Monster() override = default;

    /** update combat power pure virtual (for balrog) */
    virtual void updateCombatPower(){}

    [[nodiscard]] string getDescription() const override {
        return monsterName +
            " (power " + std::to_string(CombatPower)+
                ", loot " + std::to_string(Loot) +
                    ", damage " + std::to_string(Damage) + ")";
    }

    /** getters **/
    [[nodiscard]] virtual unsigned int getCombatPower() const {return CombatPower;};
    [[nodiscard]] virtual int getLoot() const {return Loot;};
    [[nodiscard]] virtual int getDamage() const {return Damage;};
};

class Snail: public Monster {
    public:
    Snail():Monster("Snail",5,2,10){}
};

class Slime: public Monster {
    public:
    Slime():Monster("Slime",12,5,25){}
};

class Balrog: public Monster {
    public:
    Balrog():Monster("Balrog",15,100,9001){}

    void updateCombatPower() override { // the balrog combat power updates in every encounter no matter the outcome.
        CombatPower += 2 ;
    }
};

class Pack: public Monster {
private:
    std::vector<std::unique_ptr<Monster>> monstersPack; // smart ptr vector for pack data structure


public:
    Pack():Monster("",0,0,0){}

    void addMonster(const std::unique_ptr<Monster>& monster) {
        monstersPack.push_back(monster);
    }

    // for modularity I split all kinds of getters for the pack

    [[nodiscard]] unsigned int getCombatPower() const override{
        unsigned int combinedPower = 0;

        for (const auto & i : monstersPack) {
            combinedPower += i->getCombatPower();
        }
        return combinedPower;
    }

    [[nodiscard]] int getLoot() const override {
        int combinedLoot = 0;

        for (const auto&i : monstersPack) {
            combinedLoot += i->getLoot();
        }
        return combinedLoot;
    }

    [[nodiscard]] int getDamage() const override {
        int combinedDamage = 0;

        for (const auto&i : monstersPack) {
            combinedDamage += i->getDamage();

        }
        return combinedDamage;
    }
    [[nodiscard]] string getDescription() const override {
        return "Pack of " + std::to_string(monstersPack.size()) + " members (power "
              + std::to_string(getCombatPower())+
                ", loot " + std::to_string(getLoot()) +
                    ", damage " + std::to_string(getDamage()) + ")";

    }
    static std::unique_ptr<Pack> createPack(const std::vector<std::unique_ptr<Monster>>& monsters) {
        auto pack = std::make_unique<Pack>();
        for (const auto& monster : monsters) {
            pack->addMonster(monster);
        }
        return pack;
    }

};

/**************     factory   ********************/
/**
 *factory method - creates an event from a string description
 */
class EventFactory {
private:
    std::map<std::string, std::function<std::unique_ptr<Event>()>> eventFactoryMap;

public:
    EventFactory() {

        eventFactoryMap["Snail"] = []() { return std::make_unique<Snail>(); };
        eventFactoryMap["Slime"] = [](){return std::make_unique<Slime>();};
        eventFactoryMap["Balrog"] = []() { return std::make_unique<Balrog>(); };
        eventFactoryMap["Pack"] = []() { return std::make_unique<Pack>(); };
    }

    [[nodiscard]] std::unique_ptr<Event> createEvent(const std::string& eventName) const {
        auto it = eventFactoryMap.find(eventName);
        if (it == eventFactoryMap.end()) {
            throw std::runtime_error("Invalid Events File");
        }
        return it->second();
    }
};

/*
    class SolarEclipse: public Event {

    public:
        int solarEclipse(Player& player)const override {
            int affect =0;
            if (player.getJob().toString() == "Magician") {
                player.setForce(getForce()+1);
                affect = 1;
                return affect;
            }else {player.setForce(getForce()-1);
                affect = -1;
                return affect;}
        }
    };


    class PotionMerchant:public Event {
    public:
        int potionMerchant(Player& player)const override{
            int potionAmount = 0;
            if (player.getCharacter().toString() == "Responsible") {
                while (player.getMaxHP() > player.getHealthPoints() && player.getCoins() >= 5 ) {
                    player.setHealthPoints(player.getHealthPoints()+ 10) ;
                    player.setCoins(player.getCoins()- 5);
                    potionAmount++;
                }
            }else if (player.getCharacter().toString() == "RiskTaking") {
                if (player.getHealthPoints() < 50 && player.getCoins()>=5) {
                    player.setHealthPoints(player.getHealthPoints() + 10) ;
                    player.setCoins(player.getCoins()- 5);
                    potionAmount++;
                }
            }
            return potionAmount;
        }
    };

};

*/