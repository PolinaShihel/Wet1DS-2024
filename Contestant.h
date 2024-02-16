
#ifndef WET1_WINTER2024_CONTESTANT_H
#define WET1_WINTER2024_CONTESTANT_H

#include "wet1util.h"
#include "Country.h"
#include "Team.h"

class Team;
class Country;
class Contestant {
private:
    int contestantId;
    int countryId;
    Sport sport;
    int strength;
    Country* countryPtr;
    int number_of_teams; // max 3
    /*Team* team1ptr; //NOT SURE IF PTR
    Team* team2ptr;//NOT SURE IF PTR
    Team* team3ptr;//NOT SURE IF PTR*/
public:
    Contestant(int contestantId, int countryId, Sport sport, int strength ,Country* countryPtr);
    ~Contestant() = default;
    Contestant(const Contestant &toCopy) = default;
    int get_strength();
    void change_strength(int updated_strength);
    int get_number_of_teams();
};


#endif //WET1_WINTER2024_CONTESTANT_H
