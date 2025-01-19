//
// Created by Ido Amit on 19/01/2025.
//
#pragma once

#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

class Warrior : public Job {
  public:

    Warrior(string name, std::unique_ptr<Character> character){
      this->name = name;
      this->character = character;
      this->level = 1;
      this->force = 5;
      this->maxHP = 150;
      this->currentHP = this->maxHP;
      this->coins = 10; //should i just used player constructor?
    }

    string getDescription() const override;

    int caculateCombatPower() const override;
};