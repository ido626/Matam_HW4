#include <iostream>
#include <fstream>
#include "MatamStory.h"
#include "Events\Event.h"
#include "Players\Player.h"
#include "Utilities.h"

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/
	std::string eventName;

    while (eventsStream >> eventName){
	if ( Event::allGameEvents.find(eventName) == Event::allGameEvents.end() ) { //if the event is not in the list of game known events
            throw std::runtime_error("Invalid Events File");
        }

    if (eventName == "Pack") {

        int packSize;
        if ( !(eventsStream >> packSize) || packSize <= 0) {
          throw std::runtime_error("Invalid Events File");
        }
		std::vector<std::string> packMembers ;
        for (int i = 0; i < packSize; i++) {
            if ( !(eventsStream >> eventName) || Event::allGameEvents.find(eventName) == Event::allGameEvents.end()) { //if the event is not in the list of game known events
                throw std::runtime_error("Invalid Events File");
            }

            packMembers.push_back(eventName);
        }
        Event::events.push_back("Pack");
    }else {Event::events.push_back(eventName);}
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
	const std::unique_ptr<Event> currentEvent = Event::createEvent(Event::events[this->m_turnIndex]);

     /** 2. Print the turn details with "printTurnDetails"*/
	printTurnDetails(m_turnIndex ,player,*currentEvent);

     /** 3. Play the event */
	std::string outcome = playEvent(player, *currentEvent, Event::events[this->m_turnIndex]);

     /** 4. Print the turn outcome with "printTurnOutcome"*/
    printTurnOutcome(outcome);



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
