#ifndef WET1_WINTER2024_CONTESTANTSTR_H
#define WET1_WINTER2024_CONTESTANTSTR_H

#include "Contestant.h"
#include "ContestantID.h"
class Contestant;
class  ContestantID;
class ContestantStr {
private:
    ContestantID* conIDPtr;
    Contestant* conPtr;
public:
    ContestantStr() = default;
    ContestantStr(ContestantID* IDptr, Contestant* conPtr);
    ContestantStr(const ContestantStr &toCopy) = default;
    ~ContestantStr()=default;

    Contestant* getConPtr();
};


#endif //WET1_WINTER2024_CONTESTANTSTR_H
