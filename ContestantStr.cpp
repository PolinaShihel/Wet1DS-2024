#include "ContestantStr.h"

ContestantStr::ContestantStr(ContestantID* IDPtr,Contestant* conPtr): conIDPtr(IDPtr),conPtr(conPtr),index(-1){}


Contestant* ContestantStr::getConPtr(){
    return this->conPtr;
}

void ContestantStr::setIndex(int IDindex)
{
    this->index = IDindex;
}

int ContestantStr::getIndex(){
    return this->index;
}