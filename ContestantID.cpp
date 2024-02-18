#include "ContestantID.h"

ContestantID::ContestantID(Contestant* conPtr): conStrPtr(nullptr), conPtr (conPtr){}

void ContestantID::setStrPtr(ContestantStr* StrPtr)
{
    conStrPtr = StrPtr;
}

ContestantStr* ContestantID::getContestantStrPtr(){
    return this->conStrPtr;
}

Contestant* ContestantID::getContestantPtr(){
    return this->conPtr;
}