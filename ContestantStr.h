#ifndef WET1_WINTER2024_CONTESTANTSTR_H
#define WET1_WINTER2024_CONTESTANTSTR_H

#include "Contestant.h"
#include "ContestantID.h"

class ContestantStr {
private:
    ContestantID* conIDPtr;
    Contestant* conPtr;
public:
    ContestantStr() = default;
    ContestantStr(const ContestantStr& conStr) = default;
    ContestantStr(ContestantID* IDptr, Contestant* conPtr);
    ~ContestantStr()=default;
};


#endif //WET1_WINTER2024_CONTESTANTSTR_H
