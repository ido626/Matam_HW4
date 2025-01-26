//
// Created by Ido Amit on 22/01/2025.
//
#pragma once

class Player;

using namespace std;
using std::string;

class Job {
public:
    Job& operator=(const Job& other) { //לא סגור על זה איך לממש את זה והאם זה צריך להיות בפאבליק
        if (this->toString() != other.toString()) {

        }
        return *this;

    }
    /**
    * Calculates the combat power of the player depends on his job
    *
    * @return - current combat power of the player
    */
    virtual unsigned int calculateCombatPower(Player& player) const{
        return player.getForce() + player.getLevel();
    }

    /**
     * Gets the job of the player as a string
     *
     * @return - string that represents the job of the player
     */
    virtual string toString() const;
};

class Warrior : public Job {
public:
    unsigned int calculateCombatPower(Player& player) const override {
        return player.getForce()*2 + player.getLevel();
    }
    string toString() const override{
        return "Warrior";
    }
};

class Magician : public Job {
public:
    string toString() const override{
        return "Magician";
    }
};

class Archer : public Job {
public:
    string toString() const override{
        return "Archer";
    }
};

