#include "ContestantID.h"

ContestantID::ContestantID(Contestant* conPtr): conStrPtr(NULL), conPtr (conPtr){}

void ContestantID::setStrPtr(ContestantStr* StrPtr)
{
    conStrPtr = StrPtr;
}