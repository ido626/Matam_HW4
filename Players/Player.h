
#pragma once

#include <string>
#include <iostream>

using namespace std;
using std::string;

class Character {
public:
 virtual string toString() const;
};

class Player {
protected:
  string name;
  unsigned int level;
  unsigned int force;
  unsigned int currentHP;
  unsigned int maxHP;
  unsigned int coins;
  std::unique_ptr<Character> character;

public:

     /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    virtual string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;

    /**
    * Gets the character of the player
    *
    * @return - character of the player
    */
    Character& getCharacter() const;

};

class Job : public Player {
  public:

    /**
    * Calculates the combate power of the player depends on his job
    *
    * @return - current combat power of the player
    */
    virtual int caculateCombatPower() const;

};

class Responsible : public Character {
  public:
      string toString() const override;

};

class RiskTaking : public Character {
  public:
      string toString() const override;

};