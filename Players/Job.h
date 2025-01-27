//
// Created by Ido Amit on 22/01/2025.
//
#pragma once

#include <string>
using namespace std;
class Player;


class Job {
public:
    virtual ~Job() = default;

    /**
    * Calculates the combat power of the player depends on his job
    *
    * @return - current combat power of the player
    */
    virtual unsigned int calculateCombatPower(const Player& player) const;

    /**
     * Gets the job of the player as a string
     *
     * @return - string that represents the job of the player
     */
    virtual string getType() = 0;

    /**
     * Applying 'Solar Eclipse' event
     */
    virtual string solarEclipse(Player& player);
};

class Warrior : public Job {
public:
    ~Warrior() override;
    unsigned int calculateCombatPower(const Player& player) const override;
    string getType() override;
};

class Magician : public Job {
public:
    ~Magician() override;
    string solarEclipse(Player& player) override;
    string getType() override;
};

class Archer : public Job {
public:
    ~Archer() override;
    string getType() override;
};

