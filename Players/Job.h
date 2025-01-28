//
// Created by Ido Amit on 22/01/2025.
//
#pragma once

#include <string>

/*#include "../Utilities.h"*/

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
    virtual unsigned int calculateCombatPower(const Player& player) const ;

    /**
     * Gets the job of the player as a string
     *
     * @return - string that represents the job of the player
     */
    virtual std::string getType();

    /**
     * Applying 'Solar Eclipse' event
     */
    virtual std::string solarEclipse(Player& player);
};

class Warrior : public Job {
public:
    ~Warrior() override;
    unsigned int calculateCombatPower(const Player& player) const override ; /*{
        return player.getForce()*2 + player.getLevel();
    }*/
    std::string solarEclipse(Player& player) override;
    std::string getType() override ;/*{return "Warrior";}*/
};

class Magician : public Job {
public:
    ~Magician() override;

    std::string solarEclipse(Player& player) override;
    unsigned int calculateCombatPower(const Player& player) const override ;
    std::string getType() override; /*{ return "Magician";}*/
};

class Archer : public Job {
public:
    ~Archer() override;
    std::string solarEclipse(Player& player) override;
    unsigned int calculateCombatPower(const Player& player) const override ;
    std::string getType() override ;/*{return "Archer";}*/
};

