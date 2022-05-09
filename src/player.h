#ifndef PLAYER
#define PLAYER
#include <vector>
#include <iostream>
#include "action.h"
#include "card.h"
using namespace std;

class Player {
    protected:
        int discardSum;
        bool humanPlayer;
        vector<Card> handCards;
        bool allowedMove(vector<vector<Card>> playedDeck, Card givenCard);
    public:
        virtual ~Player() = 0;
        virtual Action makeMove(vector<vector<Card>> playedDeck) = 0;
        void setDiscardSum(int sum);
        void setHuman(bool type);
        void setHandCards(vector<Card> cards);
        void addHandCard(vector<Card> cards, int index);
        int getDiscardSum();
        int getPlayerType();
        bool emptyHandCards();
        void eraseHandCard(int index);
        vector<Card> getHandCards();
        void printHandCards();
        void printAllowedMoves(vector<vector<Card>> playedDeck);
        void printHumanTurn(vector<vector<Card>> playedDeck);
};


#endif
