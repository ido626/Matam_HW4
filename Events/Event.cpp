//
// Created by Daniel Agmon on 17/01/2025.
//
#include <vector>
#include "Event.h"


std::string Event::getDescription() const{return""; }

std::vector<std::unique_ptr<Event>> Event::eventList{};
