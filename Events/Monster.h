//
// Created by Ido Amit on 27/01/2025.
//
#pragma once

#include "../Utilities.h"

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

    string applyEvent(Player &player) override {
        return applyBattle(player);
    }

    [[nodiscard]] string getDescription() const override {
        return monsterName +
            " (power " + std::to_string(CombatPower)+
                ", loot " + std::to_string(Loot) +
                    ", damage " + std::to_string(Damage) + ")";
    }

    /** getters **/
    [[nodiscard]] virtual string getName() const {return monsterName;};
    [[nodiscard]] virtual unsigned int getCombatPower() const {return CombatPower;};
    [[nodiscard]] virtual unsigned int getLoot() const {return Loot;};
    [[nodiscard]] virtual unsigned int getDamage() const {return Damage;};


    virtual void addCombatPower(int moreCP) {CombatPower += moreCP;};

    std::string applyBattle(Player& player) const {
        unsigned int playerCP = player.getJob()->calculateCombatPower(player);
        if (playerCP > getCombatPower()) { // Player wins the fight
            player.setLevel(player.getLevel() + 1);
            player.setCoins(player.getCoins() + getLoot());
            if (player.getJob()->getType() == "Warrior") {
                if (player.getHealthPoints() < 10) { // If the player is about to die from the close combat battle
                    player.setHealthPoints(0);
                } else { // If he stays alive
                    player.setHealthPoints(player.getHealthPoints() - 10);
                }
            }
            return getEncounterWonMessage(player, getLoot());
        }
        else { // Player loses the battle
            if (player.getHealthPoints() > getDamage()) {// player stays alive
                player.setHealthPoints(player.getHealthPoints() - getDamage());
            }else { player.setHealthPoints(0);}
            return getEncounterLostMessage(player, getDamage());
        }

    }

    virtual bool isPack() const { return false; }

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

    string applyEvent(Player &player) override {
        std::string outcome = applyBattle(player);
        CombatPower += 2;
        return outcome;
    }
};

class Pack: public Monster {
private:
    std::vector<std::unique_ptr<Monster>> monstersPack; // smart ptr vector for pack data structure


public:
    Pack():Monster("Pack",0,0,0){}

    void addMonster(std::unique_ptr<Monster> monster) {
        monstersPack.push_back(std::move(monster));
    }

    bool isPack() const override { return true; }


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

    int packSize() const {
        int count = 0;
        for (const auto &monster : monstersPack) {
            if (auto pack = dynamic_cast<const Pack*>(monster.get())) {
                count += pack->packSize();  // Recursive call for nested packs
            } else {count ++;}
        }
        return count;
    }

    [[nodiscard]] string getDescription() const override {
        return "Pack of " + std::to_string(packSize()) + " members (power "
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

    void applyBalrogCombatPower(std::vector<std::unique_ptr<Monster>>& monsters) {
        for (auto& monster : monsters) {
            // Check if it's a "Balrog" and increase its CombatPower
            if (monster->getName() == "Balrog") {
                monster->addCombatPower(2);
            }

            // If it's a pack, recursively check its members
            if (auto pack = dynamic_cast<Pack*>(monster.get())) {
                applyBalrogCombatPower(pack->monstersPack);
            }
        }
    }

    string applyEvent(Player &player) override {
        std::string outcome = applyBattle(player);

        // Apply combat power increase for Balrogs
        applyBalrogCombatPower(this->monstersPack);

        return outcome;
    }
};