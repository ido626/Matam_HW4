#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <stdexcept>
#include "MatamStory.h"

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/
    std::string eventName; // the input

    while (eventsStream >> eventName) { // >> operator reads one word at a time

        if (eventName == "Pack") {

            int packSize;
            if (!(eventsStream >> packSize) || packSize <= 0) {
                throw std::runtime_error("Invalid Events File");
            }

            std::vector<std::unique_ptr<Monster>> packMembers; // the pack members vector
            for (int i = 0; i < packSize; i++) {
                if (!(eventsStream >> eventName)) {
                    throw std::runtime_error("Invalid Events File");
                }
                auto event = eventFactory.createEvent(eventName);
                if (auto monster = dynamic_cast<Monster*>(event.get())) {
                    packMembers.push_back(std::make_unique<Monster>(*monster));
                } else {
                    throw std::runtime_error("Invalid Events File");
                }
            }
            auto pack = Pack::createPack(std::move(packMembers));  // Move to avoid copying
            Event::eventList.push_back(std::move(pack)); // Move to avoid copy error
        } else {
            auto currEvent = eventFactory.createEvent(eventName);
            Event::eventList.push_back(std::move(currEvent)); // Move to avoid copy error
        }
    }
        /*==========================================*/

    /*===== TODO: Open and Read players file =====*/

    string line;

    while (getline(playersStream, line)) {
      	istringstream iss(line);
        string name, job, character;

    	// Check if the line has all three fields needed
        if (!(iss >> name >> job >> character)) {
          	throw runtime_error("Invalid Players File");
        }

        // Attempt to create a player using the players factory
        try {
            PlayerFactory playerFactory;
            auto player = playerFactory.createPlayer(name, job, character);
            PlayerFactory::playerList.push_back(std::move(player));
        } catch (const runtime_error& e) {
          	throw runtime_error("Invalid Players File");
        }
    }
	// Validate the number of players
    if (PlayerFactory::playerList.size() < 2 || PlayerFactory::playerList.size() > 6) {
      	throw runtime_error("Invalid Players File");
    }
    /*============================================*/
    this->m_turnIndex = 0;
}

// std::set<Player*> MatamStory::createLeaderBoard(const std::vector<std::unique_ptr<Player>>& players) {
//     std::set<Player*> leaderBoard;
//     for (const auto& player : players) {
//         leaderBoard.insert(player.get()); // Use the raw pointer from unique_ptr
//     }
//     return leaderBoard;
// }

std::vector<Player*> MatamStory::createLeaderBoard(const std::vector<std::unique_ptr<Player>>& players) {
    std::vector<Player*> leaderBoard;

    // Insert raw pointers into the leaderboard vector
    for (const auto& player : players) {
        leaderBoard.push_back(player.get());
    }

    // Sort the leaderboard using the < operator
    std::sort(leaderBoard.begin(), leaderBoard.end(), [](Player* lhs, Player* rhs) {
        return *lhs < *rhs;  // Compare players using the overloaded < operator
    });

    return leaderBoard;
}







void MatamStory::playTurn(Player& player) {
    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list*/
    int size = Event::eventList.size();
    int currEventIndex = m_turnIndex % size;
    unique_ptr<Event> currEvent = std::move(Event::eventList[currEventIndex]); // Taking ownership

     /** 2. Print the turn details with "printTurnDetails"*/
    printTurnDetails(m_turnIndex + 1 , player, *currEvent);

     /** 3. Play the event */
    string outcome = currEvent->applyEvent(player);
    Event::eventList[currEventIndex] = std::move(currEvent); // Returning ownership

     /** 4. Print the turn outcome with "printTurnOutcome"*/
    printTurnOutcome(outcome);
    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/
    for (auto& player : PlayerFactory::playerList) {
        if (player->getHealthPoints() > 0) {
        playTurn(*player);
        }
    }
    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
    // set<Player*> leaderBoard = createLeaderBoard(PlayerFactory::playerList);
    // int i = 1;
    // for (auto player : leaderBoard) {
    //     printLeaderBoardEntry(i, *player);
    //     i++;
    // }
    std::vector<Player*> leaderBoard = createLeaderBoard(PlayerFactory::playerList);
    int i = 1;
    for (auto* player : leaderBoard) {
        printLeaderBoardEntry(i, *player);
        i++;
    }


    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    // Check if someone is level 10 (if someone's level 10 he is surely alive)
    for (auto& player : PlayerFactory::playerList) {
        if (player->getLevel() == 10) {
            return true;
        }
    }
    // In case nobody is level 10, check if somebody is still alive
    for (auto& player : PlayerFactory::playerList) {
        if (player->getHealthPoints() > 10) {
            return false;
        }
    }
    // If no one is level 10 and no one is alive, the game is over.
    return true;
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/
    for (size_t i = 0; i < PlayerFactory::playerList.size(); i++) {
        printStartPlayerEntry(i + 1, *PlayerFactory::playerList[i]);
    }
    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/
    // Create a leaderboard
    //set<Player*> leaderBoard = createLeaderBoard(PlayerFactory::playerList);
    std::vector<Player*> leaderBoard = createLeaderBoard(PlayerFactory::playerList);
    // Check if there's a winner
    auto candidate = *leaderBoard.begin();
    if ((*leaderBoard.begin())->getLevel() == 10) {
        printWinner(*candidate);
    }
    else {
        printNoWinners();
    }
    /*========================================================================*/
}

