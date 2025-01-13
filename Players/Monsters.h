//
// Created by Daniel Agmon on 13/01/2025.
//

#ifndef MONSTERS_H
#define MONSTERS_H
#include <vector>

#include "Player.h"


class Monster: public Player{

    protected:
    unsigned int CombatPower ;
    int Loot;
    int Damage;

    public:
    /** constructor & destructor **/
    Monster(unsigned int power, int loot, int damage): CombatPower(power), Loot(loot), Damage(damage){};
    Virtual ~Monster() = default;

    /** getters and setters **/
    unsigned int getCombatPower(){return CombatPower;};
    int getLoot(){return Loot;};
    int getDamage(){return Damage;};

};

class Snail: public Monster {
    public:
    Snail():Monster(5,2,10){}

};

class Slime: public Monster {
    public:
    Slime():Monster(12,5,25){}
};

class Balrog: public Monster {
    public:
    Balrog():Monster(15,100,9001){}

    void updateCombatPower() { // the balrog combat power updates in every encounter no matter the outcome.
        CombatPower =+ 2 ;
    }

};

class Pack: public Monster {
    private:
    std::vector<Monster*> monstersPack;

    public:
    Pack(){}
    //////////////////////your here !!!!!!!!//////////////////////

}
#endif //MONSTERS_H
