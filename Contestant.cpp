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

Team* Contestant::getTeamPtr(int numOfTeam)
{
    if(numOfTeam == 1)
        return this->team1ptr;
    else if(numOfTeam == 2)
        return this->team2ptr;
    else
        return this->team3ptr;
}

void Contestant::freeTeam(int id){
   if(!(this->is_team1_free())&&(this->team1ptr->getID()==id))
       this->team1ptr= nullptr;
   else if(!(this->is_team2_free())&&(this->team2ptr->getID()==id))
       this->team2ptr= nullptr;
   else
       this->team3ptr = nullptr;
}

void Contestant::setStrength(int strength)
{
    this->strength = strength;
}
bool Contestant::inTeam(int id){
    return (team1ptr!= nullptr && team1ptr->getID() == id)||(team2ptr!= nullptr && team2ptr->getID() == id)||
    (team3ptr!= nullptr && team3ptr->getID() == id);
}
void Contestant::uniteTeams(Team *toDelete, Team *toCheck) {
    bool exists = inTeam(toCheck->getID());
    if(this->team1ptr->getID() == toDelete->getID()){
        if(exists)
            this->team1ptr= nullptr;
        else
            this->team1ptr = toCheck;
    }
    else if(this->team2ptr->getID() == toDelete->getID()) {
        if (exists)
            this->team2ptr = nullptr;
        else
            this->team2ptr = toCheck;
    }
    else
    {
        if (exists)
            this->team3ptr = nullptr;
        else
            this->team3ptr = toCheck;
    }
}