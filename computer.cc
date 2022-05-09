#include "computer.h"

Action Computer::makeMove(vector<vector<Card>> playedDeck) {
    Action move;
    for (auto card : handCards) {
        if (allowedMove(playedDeck, card)) {
            move.actionCard = card;
            move.actionType = "play";
            return move;
        }
    }
    for (int i = 0; i < playedDeck.size(); ++i) {
        if (handCards[i].getSuit() != '\0') {
            move.actionCard = handCards[i];
            break;
        }
    }
    move.actionType = "discard";
    return move;
}
