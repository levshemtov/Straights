#include "game.h"
#include "player.h"
using namespace std;

Game::Game() : gamePlayers{vector<shared_ptr<Player>>()}, shuffledDeck{vector<Card>()}, playerDiscards{vector<vector<Card>>(4)}, playedDeck{vector<vector<Card>>(4)}  {
    clearTable();
    createPlayers();
}

void Game::clearTable() {
    playedDeck.clear();
    for (int i = 0; i < 4; ++i) {
        vector<Card> resetSuit;
        for (int j = 0; j < 13; ++j){
            resetSuit.push_back(Card());
        }
        playedDeck.push_back(resetSuit);
    }
}

void Game::createPlayers() {
    for (int i = 0; i < 4; ++i) {
        cout << "Is Player" << i + 1 << " a human (h) or a computer (c)?" << endl;
        cout << ">";
        string playerType;
        while (1) {
            cin >> playerType;
            if (cin.fail()) {
                break;
            }
            if (playerType == "h" || playerType == "c") {
                break;
            } else {
                cout << "You have provided an invalid player type: \"" << playerType << "\", please try again:" << endl;
                cout << ">";
            } 
        }
        shared_ptr<Player> createdPlayer;
        if (playerType == "c") {
            createdPlayer = make_shared<Computer>();
            createdPlayer->setHuman(false);
            
        } else if (playerType == "h") {
            createdPlayer = make_shared<Human>();
            createdPlayer->setHuman(true);
        }
        createdPlayer->setDiscardSum(0);
        gamePlayers.push_back(createdPlayer);
    } 
}

void Game::makeDeck() {
    for (int suitVal = 0; suitVal < 4; ++suitVal) {
        for (int rankVal = 1; rankVal <= 13; ++rankVal) {
            Card deckCard;
            deckCard.setRank(convertRank(rankVal));
            deckCard.setSuit(converSuit(suitVal));
            shuffledDeck.push_back(deckCard);
        }
    }
}

void Game::shuffleDeck(unsigned seed) {
    default_random_engine rng{seed};
    shuffle(shuffledDeck.begin(), shuffledDeck.end(), rng);
}

void Game::dealDeck() {
    for (int playerNum = 0; playerNum < 4; ++playerNum) {
        for (int cardNum = 0; cardNum < 13; ++cardNum) {
            gamePlayers[playerNum]->addHandCard(shuffledDeck, 13 * playerNum + cardNum);
        }
    }
}

int Game::findStarter() {
    int starter = 0;
    for (int i = 0; i < 4; ++i) {
        bool known = false;
        for (int j = 0; j < 13; ++j) {
            if (gamePlayers[i]->getHandCards()[j].getCardName() == "7S") {
                starter = i;
                known = true;
                break;
            }
        }
        if (known) {
            break;
        }
    } 
    return starter;
}

void Game::handleRage(int playerNum) {
    shared_ptr<Player> takeover;
    takeover = make_shared<Computer>();
    takeover->setHandCards(gamePlayers[playerNum]->getHandCards());
    takeover->setDiscardSum(gamePlayers[playerNum]->getDiscardSum());
    takeover->setHuman(false);
    gamePlayers[playerNum] = takeover;
}

int Game::highestDiscard() {
    int largestSum = gamePlayers[0]->getDiscardSum();
    for (int i = 1; i < 4; ++i) {
        if (gamePlayers[i]->getDiscardSum() > largestSum) {
            largestSum = gamePlayers[i]->getDiscardSum();
        }
    }
    return largestSum;
}

char Game::converSuit(int suitVal) {
    if (suitVal == 0) {
        return 'C';
    } else if (suitVal == 1) {
        return 'D';
    } else if (suitVal == 2) {
        return 'H';
    } else if (suitVal == 3) {
        return 'S';
    }
}

char Game::convertRank(int rankVal) {
    if (rankVal == 1) 
    {   return 'A';
    } else if (rankVal == 10) {
        return 'T';
    } else if (rankVal == 11) {
        return 'J';
    } else if (rankVal == 12) {
        return 'Q';
    } else if (rankVal == 13) {
        return 'K';
    } else {
        return (rankVal + '0');
    }
}

void Game::start(unsigned seed) {
    makeDeck();
    while (highestDiscard() < 80) {
        shuffleDeck(seed);
        dealDeck();
        int currentPlayer = findStarter();
        cout << "A new round begins. It's Player" << currentPlayer + 1 << "'s turn to play." << endl;
   
        while (!gamePlayers[currentPlayer]->emptyHandCards()) {     
            cout << "Cards on the table:" << endl;
            for (int i = 0; i < 4; ++i) {
                if (i == 0) {
                    cout << "Clubs: ";
                } else if (i == 1) {
                    cout << "Diamonds: ";
                } else if (i == 2) {
                    cout << "Hearts: ";
                } else if (i == 3) {
                    cout << "Spades: ";
                }
                for (int j = 0; j < playedDeck[i].size(); ++j) {
                    Card playedCard = playedDeck[i][j];
                    if(playedCard.getSuit() != '\0'){
                        cout << playedDeck[i][j].getRank() << " ";
                    }
                }
                cout << endl;
            }  
            gamePlayers[currentPlayer]->printHumanTurn(playedDeck);
            while (1) {
                cout << ">";
                Action move = gamePlayers[currentPlayer]->makeMove(playedDeck);
                if (move.actionType == "play") {
                    cout << "Player" << currentPlayer + 1 << " plays " << move.actionCard.getCardName() << "." << endl;
                    auto playedCard = Card();
                    playedCard.setSuit(move.actionCard.getSuit());
                    playedCard.setRank(move.actionCard.getRank());
                    playedDeck[move.actionCard.getSuitVal()][move.actionCard.getRankVal() - 1] = playedCard;
                    for (int i = 0; i < (gamePlayers[currentPlayer]->getHandCards()).size(); ++i) {
                        if (gamePlayers[currentPlayer]->getHandCards()[i].getCardName() == playedCard.getCardName()) {
                            gamePlayers[currentPlayer]->eraseHandCard(i);
                        }
                    }
                    break;
                } else if (move.actionType == "discard") {
                    cout << "Player" << currentPlayer + 1 << " discards " << move.actionCard.getCardName() << "." << endl;
                    gamePlayers[currentPlayer]->setDiscardSum(gamePlayers[currentPlayer]->getDiscardSum() + move.actionCard.getRankVal());
                    for (int i = 0; i < (gamePlayers[currentPlayer]->getHandCards()).size(); ++i) {
                        if (gamePlayers[currentPlayer]->getHandCards()[i].getCardName() == move.actionCard.getCardName()) {
                            gamePlayers[currentPlayer]->eraseHandCard(i);
                        }
                    }                    
                    playerDiscards[currentPlayer].push_back(move.actionCard);
                    break;
                } else if (move.actionType == "deck") {
                    for (int i = 1; i <= 52; ++i) {
                        cout << shuffledDeck[i - 1].getCardName() << " ";
                        if (i % 13 == 0) {
                            cout << endl;
                        }
                    }
                    continue;
                } else if (move.actionType == "quit") {
                    return;
                } else if (move.actionType == "rageQuit") {
                    cout << "Player" << currentPlayer + 1 << " ragequits. A computer will now take over." << endl;
                    handleRage(currentPlayer);
                    continue;
                } 
            }

            currentPlayer = (currentPlayer + 1) % 4;
        }
        for (int i = 0; i < 4; ++i) {
            int roundDiscardSum = 0;
            cout << "Player" << i + 1 << "'s discards: ";
            for (Card discard : playerDiscards[i]) {
                cout << discard.getCardName() << " ";
                roundDiscardSum += discard.getRankVal();
            }
            cout << endl;
            cout << "Player" << i + 1 << "'s score: ";
            cout << gamePlayers[i]->getDiscardSum() - roundDiscardSum;
            for (Card discard : playerDiscards[i]) {
                cout << " + " << discard.getRankVal();
            }
            cout << " = " << gamePlayers[i]->getDiscardSum() << endl;
            playerDiscards[i].clear();
        }
        clearTable();
    }

    int lowestSum = gamePlayers[0]->getDiscardSum();
    for (int playerNum = 1; playerNum < 4; ++playerNum) {
        if (gamePlayers[playerNum]->getDiscardSum() < lowestSum) {
            lowestSum = gamePlayers[playerNum]->getDiscardSum();
        }
    }
    for (int playerNum = 0; playerNum < 4; ++playerNum) {
        if (lowestSum == gamePlayers[playerNum]->getDiscardSum()) {
            cout << "Player" << playerNum + 1 << " wins!" << endl;
        }
    }
}
