
#include <string>
#include <iostream>
#include <fstream>

#include "MatamStory.h"

using std::string;
using std::cout;
using std::endl;
using std::exception;
using std::ifstream;

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Invalid number of arguments" << endl;
        cout << "Usage: MatamStory <events_file_path> <players_file_path>" << endl;
    }

    cout<<"The Input Files Being Tested:"<<endl;
    cout << "Events File: " << argv[1] << endl;
    cout << "Players File: " << argv[2] << endl;

    ifstream eventsStream(argv[1]);
    if (!eventsStream.is_open()) {
        cout << "Invalid Events File" << endl;
        return 1;
    }

    cout << "\n--- Events File Content ---" << endl;
    string line;
    while (getline(eventsStream, line)) {
        cout << line << endl;
    }
    cout << "---------------------------\n" << endl;


    // Reset the file stream position to the beginning
    eventsStream.clear();
    eventsStream.seekg(0, std::ios::beg);

    ifstream playersStream(argv[2]);
    if (!playersStream.is_open()) {
        cout << "Invalid Players File" << endl;
        return 1;
    }
    cout << "\n--- Players File Content ---" << endl;
    string playerLine;
    while (getline(playersStream, playerLine)) {
        cout << playerLine << endl;
    }
    cout << "---------------------------\n" << endl;

    playersStream.clear();
    playersStream.seekg(0, std::ios::beg);


    try {
        MatamStory game(eventsStream, playersStream);
        game.play();
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return 1;
    }
}
