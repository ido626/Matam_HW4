
#pragma once

#include <memory>
#include <vector>
#include <set>
#include <string>
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
    [[nodiscard]] virtual string getDescription() const;
    /**
     * a vector contains all events (input),ordered the same as in eventsStream file
     */
    static std::vector<std::string> events;
    /**
    * all known game events set
    */
    static std::set<std::string> allGameEvents;

    /** Special Events**/
    virtual void solarEclipse(Player& player);
    virtual void potionMerchant(Player& player);

    /**
    * creates an event from a string description
    */
    std::unique_ptr<Event> createEvent(const std::string & eventName);

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

    /** getters **/
    [[nodiscard]] virtual unsigned int getCombatPower() const {return CombatPower;};
    [[nodiscard]] virtual int getLoot() const {return Loot;};
    [[nodiscard]] virtual int getDamage() const {return Damage;};

    /** update combat power pure virtual (for balrog) */
    virtual void updateCombatPower(){}

    [[nodiscard]] string getDescription() const override {
        return monsterName +
            " (power " + std::to_string(CombatPower)+
                ", loot " + std::to_string(Loot) +
                    ", damage " + std::to_string(Damage) + ")";

    }

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
        int packSize = monstersPack.size();
        return "Pack of " + std::to_string(packSize) + " members"
            " (power " + std::to_string(getCombatPower())+
                ", loot " + std::to_string(getLoot()) +
                    ", damage " + std::to_string(getDamage()) + ")";

    }
};

    class SolarEclipse: public Event {

    public:
        void solarEclipse(Player& player)override {
            if (player.getJob().toString() == "Magician") {
                player.setForce(getForce()+1) ;
            }else {player.setForce(getForce()-1) ;}
        }
    };


    class PotionMerchant:public Event {
    public:
        void potionMerchant(Player& player) override{
            if (player.getCharacter().toString() == "Responsible") {
                while (player.getMaxHP() > player.getHealthPoints() && player.getCoins() >= 5 ) {
                    player.setHealthPoints(getHealthPoints()+ 10) ;
                    player.setCoins(getCoins()- 5);
                }
            }else if (player.getCharacter().toString() == "RiskTaking") {
                if (player.getHealthPoints() < 50 && player.getCoins()>=5) {
                    player.setHealthPoints(getHealthPoints() + 10) ;
                    player.setCoins(getCoins()- 5);
                }
            }
        }
    };

};
