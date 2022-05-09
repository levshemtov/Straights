#ifndef GAME
#define GAME
#include "player.h"
#include "human.h"
#include "computer.h"
#include <algorithm>
#include <random>
#include <memory>

using namespace std;

class Game {
    protected:
        vector<shared_ptr<Player>> gamePlayers;
        vector<Card> shuffledDeck;
        vector<vector<Card>> playerDiscards;
        vector<vector<Card>> playedDeck;
        void clearTable();
        void createPlayers();
        void makeDeck();
        void shuffleDeck(unsigned seed);
        void dealDeck();
        int findStarter();
        int highestDiscard();
        void handleRage(int playerIdx);
        char converSuit(int suitVal);
        char convertRank(int rankVal);
    public:
        Game();
        ~Game() {}
        void start(unsigned seed);
};

#endif
