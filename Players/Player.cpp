//
// Created by Ido Amit on 15/01/2025.
//

#include "Player.h"


    string Player::getName() const{
      return name;
      }


    unsigned int Player::getLevel() const{
      return level;
      }

    void Player::setLevel(int level){
      this->level = level;
    }

    unsigned int Player::getForce() const{
      return force;
      }

    void Player::setForce(int force){
          this->force = force;
        }

    int Player::getHealthPoints() const{
        return currentHP;
      }

    void Player::setHealthPoints(int healthPoints){
        this->currentHP = healthPoints;
        }


    unsigned int Player::getMaxHP() const{
        return maxHP;
      }


    unsigned int Player::getCoins() const{
        return coins;
      }

    void Player::setCoins(int coins){
        this->coins = coins;
      }

    const std::unique_ptr<Character>& Player::getCharacter() const{
        return character;
      }

    const std::unique_ptr<Job>& Player::getJob() const{
        return job;
    }


    string Player::getDescription() const {
          string playerName = getName();
          string playerJob = getJob()->getType();
          string playerCharacter = getCharacter()->getType();
          string playerLevel = std::to_string(getLevel());
          string playerForce = std::to_string(getForce());
          return playerName + ", " + playerJob + " with " + playerCharacter +
            " character (level " + playerLevel + ", force " + playerForce + ")";
        }