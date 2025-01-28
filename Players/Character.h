//
// Created by Ido Amit on 26/01/2025.
//

#pragma once


class Player;



class Character {
public:
    virtual ~Character() = default;
    /**
    * Gets the character as a string
    *
    * @return - string that represents the character of the player
    */
    virtual std::string getType();

    /**
    * Applying 'Potion Merchant' event
    */
    virtual std::string potionMerchant(Player& player);
};

class Responsible : public Character {
public:
    ~Responsible() override;
    std::string potionMerchant(Player& player) override; /* {

            unsigned int potionAmount = 0;
            if (player.getCharacter()->getType() == "Responsible") {
                while (static_cast<int>(player.getMaxHP()) > player.getHealthPoints() && player.getCoins() >= 5 ) {
                    player.setHealthPoints(player.getHealthPoints()+ 10) ;
                    player.setCoins(player.getCoins()- 5);
                    potionAmount++;
                }
            }
            return getPotionsPurchaseMessage(player, potionAmount);
        }
        */

    string getType() override ; /*{ return "Responsible";} */
};

class RiskTaking : public Character {
public:
    ~RiskTaking() override;

    std::string potionMerchant(Player& player) override ;/* {
        int potionAmount = 0;
        if (player.getHealthPoints() < 50 && player.getCoins()>=5) {
            player.setHealthPoints(player.getHealthPoints() + 10) ;
            player.setCoins(player.getCoins()- 5);
            potionAmount++;
        }
        return getPotionsPurchaseMessage(player, potionAmount);
    } */

    std::string getType() override;/* { return "RiskTaking";};*/
};

