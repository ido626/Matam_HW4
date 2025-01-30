#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "MatamStory.h"

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/
    // Check if the stream is valid before reading
    eventFactory.readEvents(eventsStream);

    // // Check if we have at least 2 events
    if (Event::eventList.size() < 2) {
        throw std::runtime_error("Invalid Events File");
    }

        /*==========================================*/

    /*===== TODO: Open and Read players file =====*/

	// Validate the number of players
    PlayerFactory::readPlayers(playersStream);

    if (PlayerFactory::playerList.size() < 2 || PlayerFactory::playerList.size() > 6) {
      	throw runtime_error("Invalid Players File");
    }
    /*============================================*/
    this->m_turnIndex = 0;
}

std::vector<Player*> MatamStory::createLeaderBoard(const std::vector<std::unique_ptr<Player>>& players) {
    std::vector<Player*> leaderBoard;

    // Insert raw pointers into the leaderboard vector
    for (const auto& player : players) {
        leaderBoard.push_back(player.get());
    }

    // Sort the leaderboard using the < operator
    std::sort(leaderBoard.begin(), leaderBoard.end(), [](const Player* lhs, const Player* rhs) {
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
        if (player->getHealthPoints() > 0) {
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

