//
// Created by pshih on 15/02/2024.
//

#include "Contestant.h"

Contestant::Contestant(int contestantId, int countryId, Sport sport, int strength ,Country* countryPtr) :
    contestantId(contestantId), countryId(countryId), sport(sport), strength(strength) ,countryPtr(countryPtr),number_of_teams(0)
    {}
int Contestant::get_strength() {
    return strength;
}
void Contestant::change_strength(int updated_strength) {
    strength = updated_strength;
}
int Contestant::get_number_of_teams() {
    return number_of_teams;
}
