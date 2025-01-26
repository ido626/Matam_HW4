
#pragma once

#include <string>
#include <iostream>
#include "Job.h"


using namespace std;
using std::string;


class Character {
  public:

  Character& operator=(const Character& other) { //גם פה
   if (this->toString() != other.toString()) {
    cout << "Characters don't match" << endl;
   }
   return *this;
  }

    /**
    * Gets the character as a string
    *
    * @return - string that represents the character of the player
    */
    virtual string toString() const;
};


class Responsible : public Character {
  public:
     string toString() const override{
        return "Responsible";
 }
};

class RiskTaking : public Character {
   public:
      string toString() const override{
        return "RiskTaking";
 }
};

class Player {
private:
  string name;
  unsigned int level = 1;
  unsigned int force = 5;
  unsigned int currentHP = 100;
  unsigned int maxHP = 100;
  unsigned int coins = 10;
  std::unique_ptr<Job> job;
  std::unique_ptr<Character> character;

public:

    Player(string name, std::unique_ptr<Job> job, std::unique_ptr<Character> character)
         : name(std::move(name)), job(std::move(job)), character(std::move(character)) {
             // Check if the job is an Archer and apply a bonus of 10 coins
             if (job.toString() == "Archer") {
              coins += 10;  // Add 10 coins if the job is Archer
             }
             else if (job.toString() == "Warrior") {
              maxHP += 150;
              currentHP = maxHP;
             }
    }

    /**
    * Gets the description of the player
    *
    * @return - description of the player
    */
    string getDescription() const;

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
    unsigned int getLevel() const;

    /**
     * Sets the current level of the player
     */
    void setLevel(int level);

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    unsigned int getForce() const;

    /**
    * Sets the force the player has
    */
    void setForce(int force);

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    unsigned int getHealthPoints() const;

    /**
     * Gets the maximum of health points the player can has
     *
     * @return - max health points of the player
    */

    /**
    * Sets the health points the player has
    */
    void setHealthPoints(int force);

    /**
    * Gets the maxmimum health points the player can have
    *
    * @return - the maxmimum health of the player
    */
    unsigned int getMaxHP() const;

   /**
   * Gets the amount of coins the player has
   *
   * @return - coins of the player
   */
   unsigned int getCoins() const;

   /**
   * Sets the amount of coins the player has
   *
   * @return - coins of the player
   */
   void setCoins(int coins);

    /**
    * Gets the character of the player
    *
    * @return - character of the player
    */
    std::unique_ptr<Character>& getCharacter() const;

    /**
    * Gets the job of the player
    *
    * @return - job of the player
    */
    std::unique_ptr<Job>& getJob() const;
    };

