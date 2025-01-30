cmake_minimum_required(VERSION 3.29)
project(Matam_HW4)

set(CMAKE_CXX_STANDARD 17)

add_executable(Matam_HW4
        Player.h
        Player.cpp
        Job.h
        Job.cpp
        Warrior.cpp
        Magician.cpp
        Archer.cpp
        Character.h
        Responsible.cpp
        RiskTaking.cpp
        ../MatamStory.cpp
        ../MatamStory.h
        ../Utilities.cpp
        ../Utilities.h
        ../Events/Event.cpp
        ../Events/Event.h
        ../Events/Monster.h
        ../Events/EventFactory.h
        PlayerFactory.cpp
        ../main.cpp
)
