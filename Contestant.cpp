//
// Created by pshih on 15/02/2024.
//

#include "Contestant.h"

Contestant::Contestant(int contestantId, int countryId, Sport sport, int strength ,Country* countryPtr) :
    contestantId(contestantId), countryId(countryId), sport(sport), strength(strength) ,countryPtr(countryPtr)
    ,team1ptr(nullptr), team2ptr(nullptr), team3ptr(nullptr) {}
int Contestant::get_strength() {
    return strength;
}
void Contestant::change_strength(int updated_strength) {
    strength = updated_strength;
}
int Contestant::get_id(){
    return this->contestantId;
}
void Contestant::join_team1 (Team* team){
    team1ptr = team;
}
void Contestant::join_team2 (Team* team){
    team2ptr = team;
}
void Contestant::join_team3 (Team* team) {
    team3ptr = team;
}
bool Contestant::is_team1_free () {
    return (team1ptr == nullptr);
}
bool Contestant::is_team2_free () {
    return (team2ptr == nullptr);
}
bool Contestant::is_team3_free () {
    return (team3ptr == nullptr);
}

bool Contestant::teamsFull() {
    return (!is_team1_free())&&(!is_team2_free())&&(!is_team3_free());
}

Sport Contestant::get_sport()
{
    return this->sport;
}

Country* Contestant::get_country_ptr(){
    return this->countryPtr;
}

