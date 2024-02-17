
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
    Team* team1ptr; //NOT SURE IF PTR
    Team* team2ptr;//NOT SURE IF PTR
    Team* team3ptr;//NOT SURE IF PTR
public:
    Contestant(int contestantId, int countryId, Sport sport, int strength ,Country* countryPtr);
    ~Contestant() = default;
    Contestant(const Contestant &toCopy) = default;
    int get_strength();
    int get_id();
    void change_strength(int updated_strength);
    void join_team1 (Team* team);
    void join_team2 (Team* team);
    void join_team3 (Team* team);
    bool is_team1_free ();
    bool is_team2_free ();
    bool is_team3_free ();



};


#endif //WET1_WINTER2024_CONTESTANT_H
