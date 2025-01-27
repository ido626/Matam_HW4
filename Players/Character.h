//
// Created by Ido Amit on 26/01/2025.
//

#pragma once


class Character {
public:
    virtual ~Character() = default;
    /**
    * Gets the character as a string
    *
    * @return - string that represents the character of the player
    */
    virtual string getType();

    /**
    * Applying 'Potion Merchant' event
    */
    virtual string potionMerchant(Player& player);
};

class Responsible : public Character {
public:
    ~Responsible() override;
    string potionMerchant(Player& player) override;
    string getType() override;
};

class RiskTaking : public Character {
public:
    ~RiskTaking() override;
    string potionMerchant(Player& player) override;
    string getType() override;
};

