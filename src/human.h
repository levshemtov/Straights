#ifndef HUMAN
#define HUMAN

#include "player.h"

class Human: public Player {
    private:
        bool canGo(vector<vector<Card>> playedDeck);
        void printHandCards();
        void printAllowedMoves(vector<vector<Card>> playedDeck);
        void printHumanTurn(vector<vector<Card>> playedDeck);
    public:
        Action makeMove(vector<vector<Card>> playedDeck) override;
};

#endif
