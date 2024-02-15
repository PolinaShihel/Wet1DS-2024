#ifndef WET1_WINTER2024_CONTESTANTID_H
#define WET1_WINTER2024_CONTESTANTID_H

#include "Contestant.h"
#include "ContestantStr.h"

class ContestantID {
private:
    ContestantStr* conStrPtr;
    Contestant* conPtr;
public:
    ContestantID() = default;
    ContestantID(const ContestantID& conID) = default;
    ContestantID(Contestant* conPtr);
    void setStrPtr(ContestantStr* conStrPtr);
    ~ContestantID()=default;
};

#endif //WET1_WINTER2024_CONTESTANTID_H
