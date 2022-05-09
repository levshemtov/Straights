#ifndef CARD
#define CARD
#include <string>


using namespace std;
class Card {
    private:
        char suit;
        char rank;
    public:
        Card(); 
        Card(char suit, char rank);
        ~Card() {}
        void setSuit(char suitGiven);
        void setRank(char rankGiven);
        char getSuit();
        char getRank();
        int getSuitVal();
        int getRankVal();
        
        string getCardName();    
};

#endif
