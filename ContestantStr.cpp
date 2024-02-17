#include "ContestantStr.h"

ContestantStr::ContestantStr(ContestantID* IDPtr,Contestant* conPtr): conIDPtr(IDPtr),conPtr(conPtr){}


Contestant* ContestantStr::getConPtr(){
    return this->conPtr;
}