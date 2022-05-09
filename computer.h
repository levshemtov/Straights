#ifndef COMPUTER
#define COMPUTER

#include "player.h"

class Computer: public Player {
    public:
        Action makeMove(vector<vector<Card>> playedDeck) override;
};
#endif
