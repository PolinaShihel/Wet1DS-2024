#ifndef WET1_WINTER2024_CONTESTANTID_H
#define WET1_WINTER2024_CONTESTANTID_H

#include "Contestant.h"
#include "ContestantStr.h"
class Contestant;
class ContestantStr;
class ContestantID {
private:
    ContestantStr* conStrPtr;
    Contestant* conPtr;
public:
    ContestantID() = default;
    ContestantID(const ContestantID& conID) = default;
    ContestantID(Contestant* conPtr);
    ~ContestantID()=default;
    void setStrPtr(ContestantStr* conStrPtr);
    ContestantStr* getContestantStrPtr();
    Contestant* getContestantPtr();
};

#endif //WET1_WINTER2024_CONTESTANTID_H
