#include "player.h"

Player::~Player() {}

bool Player::allowedMove(vector<vector<Card>> playedDeck, Card givenCard) {
    if(givenCard.getSuit()=='\0'){
        return false;
    }
    bool firstPlay = true;
    for (auto suitDeck : playedDeck) {
        for (auto card : suitDeck) {
            if (card.getSuit() != '\0' ) {
                firstPlay = false;
                break;
            }
        } 
        
        if (!firstPlay) {
            break;
        }
    }
    if (firstPlay) {
        if (givenCard.getCardName() == "7S") {
            return true;
        } else {
            return false;
        }
    }
    int index = givenCard.getRankVal() - 1;
    vector<Card> suitDeck = playedDeck[givenCard.getSuitVal()];
    if (givenCard.getRankVal() == 7) {
        return true;
    } else if (index >= 1 && index <= 11 && (suitDeck[index + 1].getSuit() != '\0' || suitDeck[index - 1].getSuit() != '\0')) {
        return true;
    } else if (index == 0 && suitDeck[index + 1].getSuit() != '\0') {
        return true;
    } else if (index == 12 && suitDeck[index - 1].getSuit() != '\0') {
        return true;
    } else {
        return false;
    }
}

void Player::setDiscardSum(int sum) {
    discardSum = sum;
}

void Player::setHuman(bool type) {
    humanPlayer = type;
}

int Player::getDiscardSum() {
    return discardSum;
}

int Player::getPlayerType() {
    return humanPlayer;
}

void Player::setHandCards(vector<Card> cards) {
    handCards = cards;
}

vector<Card> Player::getHandCards() {
    return handCards;
}
bool Player::emptyHandCards(){
    if (handCards.empty()) {
        return true;
    } else {
        return false;
    }
}

void Player::eraseHandCard(int index){
    handCards.erase(handCards.begin()+index);
}

void Player::addHandCard(vector<Card> cards, int index) {
    handCards.push_back( cards[index]);
}

void Player::printHandCards() {
    cout << "Your hand: ";
    for (auto handCard : handCards) {
        cout << handCard.getCardName() << " ";
    }
    cout << endl;
}

void Player::printAllowedMoves(vector<vector<Card>> playedDeck) {
    cout << "Legal plays: ";
    for (auto handCard: handCards) {
        if (allowedMove(playedDeck, handCard)) {
            cout << handCard.getCardName() << " ";
        }
    }
    cout << endl;
}
void Player::printHumanTurn(vector<vector<Card>> playedDeck) {
    printHandCards();
    printAllowedMoves(playedDeck); 
}