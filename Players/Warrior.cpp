//
// Created by Ido Amit on 19/01/2025.
//
#include "Warrior.h"

string Warrior::getDescription() const {
    return getName() + ", Warrior with " + getCharacter().toString() +
           " character (level " + std::to_string(getLevel()) + ", force " + std::to_string(getForce()) + ")/n";
}

int Warrior::caculateCombatPower() const {
      return 2*getForce() + getLevel();
}
