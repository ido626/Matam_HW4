
#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <stdexcept>
#include <sstream>
#include <memory> //this was missing
#include "Job.h"
#include "Character.h"

using namespace std;
using std::string;



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
    ~Player() = default;

  Player(std::string name, std::unique_ptr<Job> job, std::unique_ptr<Character> character)
    : name(std::move(name)), job(std::move(job)), character(std::move(character)) {
    if (this->job->getType() == "Warrior") {
        maxHP = 150;
        currentHP = maxHP;
    }
    else if (this->job->getType() == "Archer") {
        coins += 10;
    }
}

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
   * Sets the health points the player has
   */
   void setHealthPoints(int force);

   /**
   * Gets the maximum health points the player can have
   *
   * @return - the maximum health of the player
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
    const std::unique_ptr<Character>& getCharacter() const;

    /**
    * Gets the job of the player
    *
    * @return - job of the player
    */
    const std::unique_ptr<Job>& getJob() const;

     /**
    * Gets the description of the player
    *
    * @return - description of the player
    */
    string getDescription() const;

    /**
    * Overloaded version of the < operator
    *
    */


    bool operator<(const Player &other) const {
        if (this->level == other.level) {
            if (this->coins == other.coins) {
                return name < other.name;  // Lexicographically smallest name first
            }
            return coins > other.coins;  // Highest force first
        }
        return level > other.level;  // Highest level first
    }
};

class PlayerFactory {
private:
        // Maps for job and character creation
        map<string, function<unique_ptr<Job>()>> jobFactoryMap;
        map<string, function<unique_ptr<Character>()>> characterFactoryMap;
public:
        static std::vector<std::unique_ptr<Player>> playerList;

        ~PlayerFactory() = default;

        PlayerFactory(){
        // Register Jobs
        jobFactoryMap["Warrior"] = []() { return make_unique<Warrior>(); };
        jobFactoryMap["Magician"] = []() { return make_unique<Magician>(); };
        jobFactoryMap["Archer"] = []() { return make_unique<Archer>(); };

        // Register Characters
        characterFactoryMap["Responsible"] = []() { return make_unique<Responsible>(); };
        characterFactoryMap["RiskTaking"] = []() { return make_unique<RiskTaking>(); };
      	}

    	// Add a new job dynamically
        void registerJob(const string& jobName, const function<unique_ptr<Job>()> &jobCreator){
            jobFactoryMap[jobName] = jobCreator;
        }

        // Add a new character dynamically
        void registerCharacter(const string& characterName, const function<unique_ptr<Character>()> &characterCreator){
          characterFactoryMap[characterName] = characterCreator;
        }

        // Create Player
         unique_ptr<Player> createPlayer(const string& name, const string& job, const string& character) const{
			// Check if the job exists
            auto jobIt = jobFactoryMap.find(job);
            if (jobIt == jobFactoryMap.end()) {
                throw std::runtime_error("Invalid Players File.");
            }

            // Check if the character exists
            auto characterIt = characterFactoryMap.find(character);
            if (characterIt == characterFactoryMap.end()) {
                throw std::runtime_error("Invalid Players File.");
            }

            // Create the job and the character
            auto jobPtr = jobIt->second();
            auto characterPtr = characterIt->second();

            // Create the player with the generate job and character
            return make_unique<Player>(name, std::move(jobPtr), std::move(characterPtr));
        }

    static void readPlayers(std::istream& playersStream);
};

