#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <stdexcept>
#include "MatamStory.h"
#include "Events\Event.h"
#include "Players\Player.h"
#include "Utilities.h"

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/
	EventFactory eventFactory;// creating a map of events
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

            auto pack = Pack::createPack(packMembers);
            Event::events.push_back(pack->getDescription());
        } else {
            auto event = eventFactory.createEvent(eventName);
            Event::events.push_back(event->getDescription());
        }
    }
}







    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/

    /*============================================*/


    this->m_turnIndex = 1;
}

void MatamStory::playTurn(Player& player) {

    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list*/


     /** 2. Print the turn details with "printTurnDetails"*/


     /** 3. Play the event */


     /** 4. Print the turn outcome with "printTurnOutcome"*/




    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/

    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    return false; // Replace this line
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/

    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/

    /*========================================================================*/
}
