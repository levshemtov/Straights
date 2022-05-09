#include "human.h"
using namespace std;

bool Human::canGo(vector<vector<Card>> playedDeck) {
    for (auto handCard : handCards) {
        if (allowedMove(playedDeck, handCard)) {
            return true;
        }
    }
    return false;
}

Action Human::makeMove(vector<vector<Card>> playedDeck) {
    Action move;
    while (1) {
        string command;
        cin >> command;

        string cardIn;
        Card givenCard;
        if (command == "play") {
            cin >> cardIn;
            givenCard.setRank(cardIn[0]);
            givenCard.setSuit(cardIn[1]);
            if (allowedMove(playedDeck, givenCard)) {
                move.actionCard = givenCard;
                move.actionType = "play";
                break;
            } else {
                cout << "This is not a legal play." << endl;
                continue;
            }
        } else if (command == "discard") {
            cin >> cardIn;
            givenCard.setRank(cardIn[0]);
            givenCard.setSuit(cardIn[1]);
            if (!canGo(playedDeck)) {
                move.actionCard = givenCard;
                move.actionType = "discard";
                break;
            } else {
                cout << "You have a legal play. You may not discard." << endl;
                continue;
            }
        } else if (command == "deck") {
            move.actionType = "deck";
            break;
        } else if (command == "quit") {
            move.actionType = "quit";
            break;
        } else if (command == "ragequit") {
            move.actionType = "rageQuit";
            break;
        } else {
            cout << "You have provided an invalid command: " << command << ". Try again." << endl;
            cout << ">";
        }
    }
    return move;
}


