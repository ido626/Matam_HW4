//
// Created by Ido Amit on 27/01/2025.
//
#pragma once

#include "Event.h"
#include "../Players/Player.h"

/** Base class Monster **/

class Monster:public Event{ // the base class
    protected:
    string monsterName;

    public:
    /** constructor & destructor **/
    Monster(std::string  name ,unsigned int power, unsigned int loot, unsigned int damage)
        :monsterName(std::move(name)) {
        CombatPower = power;
        Loot = loot;
        Damage = damage;
    }

    ~Monster() override = default;

    /** update combat power pure virtual (for balrog) */
    virtual void updateCombatPower(){}

    string applyEvent(Player &player) override {
        unique_ptr encounter = make_unique<Encounter>();
        return encounter->applyBattle(player, *this);
    }

    [[nodiscard]] string getDescription() const override {
        return monsterName +
            " (power " + std::to_string(CombatPower)+
                ", loot " + std::to_string(Loot) +
                    ", damage " + std::to_string(Damage) + ")";
    }

    /** getters **/
    [[nodiscard]] virtual unsigned int getCombatPower() const {return CombatPower;};
    [[nodiscard]] virtual unsigned int getLoot() const {return Loot;};
    [[nodiscard]] virtual unsigned int getDamage() const {return Damage;};
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

    string applyEvent(Player &player) override {
        unique_ptr encounter = make_unique<Encounter>();
        string outcome = encounter->applyBattle(player, *this);
        updateCombatPower();
        return outcome;
    }
};

class Pack: public Monster {
private:
    std::vector<std::unique_ptr<Monster>> monstersPack; // smart ptr vector for pack data structure


public:
    Pack():Monster("",0,0,0){}

    void addMonster(std::unique_ptr<Monster> monster) {
        monstersPack.push_back(std::move(monster));
    }


    // for modularity, I split all kinds of getters for the pack

    [[nodiscard]] unsigned int getCombatPower() const override{
        unsigned int combinedPower = 0;

        for (const auto & i : monstersPack) {
            combinedPower += i->getCombatPower();
        }
        return combinedPower;
    }

    [[nodiscard]] unsigned int getLoot() const override {
        unsigned int combinedLoot = 0;

        for (const auto&i : monstersPack) {
            combinedLoot += i->getLoot();
        }
        return combinedLoot;
    }

    [[nodiscard]] unsigned int getDamage() const override {
        unsigned int combinedDamage = 0;

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
    static std::unique_ptr<Pack> createPack(std::vector<std::unique_ptr<Monster>> monsters) {
        auto pack = std::make_unique<Pack>();
        for (auto& monster : monsters) {
            pack->addMonster(std::move(monster));
        }
        return pack;
    }

};