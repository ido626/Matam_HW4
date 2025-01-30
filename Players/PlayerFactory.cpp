//
// Created by Ido Amit on 28/01/2025.
//
#include "Player.h"

std::vector<std::unique_ptr<Player>> PlayerFactory::playerList{};

string line;

    void PlayerFactory::readPlayers(std::istream& playersStream) {
        string name, job, character;
        PlayerFactory playerFactory;

        while (playersStream >> name >> job >> character) {
            // Check if name length is valid
            if (name.size() < 3 || name.size() > 15) {
                throw runtime_error("Invalid Players File");
            }

            for (char ch : name) {
                if (!((65 <= ch && ch <= 90) || ( 97 <= ch && ch <= 122))) {
                    // Check if every character is a letter
                    throw runtime_error("Invalid Players File");
                }
            }

            // Attempt to create a player using the players factory
            try {
                auto player = playerFactory.createPlayer(name, job, character);
                PlayerFactory::playerList.push_back(std::move(player));
            } catch (const runtime_error& e) {
                throw runtime_error("Invalid Players File");
            }

            // Check if the input stream ended in the middle of a player entry
            if (!playersStream.eof() && (playersStream.fail() || playersStream.bad())) {
                throw runtime_error("Invalid Players File");
            }
        }
    }