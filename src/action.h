#ifndef ACTION
#define ACTION

#include "card.h"

class Action {
    public:
        Action();
        ~Action() {}
        Card actionCard;
        string actionType;
};

#endif
