
#ifndef WET1_WINTER2024_CONTESTANT_H
#define WET1_WINTER2024_CONTESTANT_H

#include "wet1util.h"
#include "Country.h"
#include "Team.h"

class Team; //
class Country; //
class Contestant {
private:
    int contestantId;
    int countryId;
    Sport sport;
    int strength;
    Country* countryPtr;
    Team* team1ptr; //NOT SURE IF PTR
    Team* team2ptr;//NOT SURE IF PTR
    Team* team3ptr;//NOT SURE IF PTR
public:


};


#endif //WET1_WINTER2024_CONTESTANT_H
