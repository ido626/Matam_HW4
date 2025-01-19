//
// Created by Ido Amit on 15/01/2025.
//

#include "Player.h"


    string Player::getName() const{
      return name;
      }


    int Player::getLevel() const{
      return level;
      }


    int Player::getForce() const{
      return force;
      }


    int Player::getHealthPoints() const{
      return currentHP;
      }


    int Player::getCoins() const{
      return coins;
      }

    Character& Player::getCharacter() const{
      return *character;
      }