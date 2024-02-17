//
// Created by pshih on 15/02/2024.
//

#include "Country.h"

Country::Country(int countryId, int medals)
: countryId(countryId), medals(medals), teamsCounter(0), contestantsCounter(0)
{}

int Country::get_country_id()  {
    return countryId;
}
int Country::get_medals()  {
    return medals;
}
void Country::add_a_medal() {
    medals+=1;
}
void Country::add_contestant() {
    contestantsCounter += 1;
}
void Country::add_team() {
    teamsCounter += 1;
}
void Country::remove_contestant() {
    contestantsCounter -= 1;
}
void Country::remove_team() {
    teamsCounter -= 1;
}
int Country::get_number_of_teams(){
    return teamsCounter;
}
int Country::get_number_of_contestants(){
    return contestantsCounter;
}