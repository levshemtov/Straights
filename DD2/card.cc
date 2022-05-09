#include "card.h"

using namespace std;

Card::Card() {
    setSuit('\0');
}

Card::Card(char suit, char rank) {
    setSuit(suit);
    setRank(rank);
}

void Card::setSuit(char suitGiven) {
    suit = suitGiven;
}

void Card::setRank(char rankGiven) {
    rank = rankGiven;
}

char Card::getSuit() {
    return suit;
}

char Card::getRank() {
    return rank;
}

int Card::getSuitVal() {
    if (suit == 'C') {
        return 0; 
    } else if (suit == 'D') {
        return 1;
    } else if (suit == 'H') {
        return 2;
    } else if (suit == 'S') {
        return 3;
    }
}

int Card::getRankVal() {
    if (rank >= '2' && rank <= '9') {
        return (rank - '0'); 
    } else if (rank == 'A') {
        return 1;
    } else if (rank == 'T') {
        return 10;
    } else if (rank == 'J') {
        return 11;
    } else if (rank == 'Q') {
        return 12;
    } else if (rank == 'K') {
        return 13;
    }
}

string Card::getCardName() {
    string cardName = "";
    cardName += rank;
    cardName += suit;
    return cardName;
}
