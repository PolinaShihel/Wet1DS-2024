//
// Created by Lotan Dahan on 22/02/2024.
//

#include <string>
#include <iostream>
#include "Olympicsa1.h"

using namespace std;
static const char *StatusTypeStr[] =
        {
                "SUCCESS",
                "ALLOCATION_ERROR",
                "INVALID_INPUT",
                "FAILURE"
        };

void print( StatusType res)
{
    cout  << StatusTypeStr[(int) res] ;
}

void print( output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
        cout  << StatusTypeStr[(int) res.status()] << ", " << res.ans() ;
    } else {
        cout  << StatusTypeStr[(int) res.status()] ;
    }
}

int main() {

    Olympics ol = Olympics();
    // country check
    print(ol.add_country(222,4));
    cout << "== SUCCESS" << endl;
    print(ol.add_team(22,222,Sport::FOOTBALL));
    cout << "== SUCCESS" << endl;
    print(ol.add_country(333,12));
    cout << "== SUCCESS" << endl;
    print(ol.add_country(333,12)); // try to add the same country
    cout << "== FAILURE" << endl;
    print(ol.remove_country(333)); // delete country
    cout << "== SUCCESS" << endl;
    print(ol.remove_country(1)); // delete country that doesnt exist
    cout << "== FAILURE" << endl;
    print(ol.remove_country(222)); // try to delete country with a team
    cout << "== FAILURE" << endl;
    print(ol.add_country(0,1)); // try to add country with invalid id
    cout << "== INVALID INPUT" << endl;
    print(ol.add_country(2,-1)); // try to add country with invalid medals
    cout << "== INVALID INPUT" << endl;
    print(ol.add_country(333,15));
    cout << "== SUCCESS" << endl;
    print(ol.add_contestant(311,333,Sport::ACROBATICS,10));
    cout << "== SUCCESS" << endl;
    print(ol.remove_country(333)); //try to delete country with contestant
    cout << "== FAILURE" << endl;
    cout <<endl<< "----------done country check------------" << endl << "team check:" << endl;
    // team check
    print(ol.add_team(33,333,Sport::ACROBATICS));
    cout << "== SUCCESS" << endl;
    print(ol.remove_team(22)); // delete team
    cout << "== SUCCESS" << endl;
    print(ol.remove_team(0)); // invalid team
    cout << "== INVALID INPUT" << endl;
    print(ol.remove_team(22)); //remove none existing team
    cout << "== FAILURE" << endl;
    print(ol.add_team(22,222,Sport::FOOTBALL));
    cout << "== SUCCESS" << endl;
    print(ol.add_team(22,222,Sport::ACROBATICS)); // try to add the same team again
    cout << "== FAILURE" << endl;
    print(ol.add_team(22,333,Sport::ACROBATICS)); // try to add the same team to diff country
    cout << "== FAILURE" << endl;
    print(ol.add_team(0,222,Sport::ACROBATICS)); //try to add team with invalid id
    cout << "== INVALID INPUT" << endl;
    print(ol.add_team(4,0,Sport::ACROBATICS)); //try to add team with invalid id country
    cout << "== INVALID INPUT" << endl;
    print(ol.add_team(2,11,Sport::FOOTBALL)); //try to add team to no legit country
    cout << "== FAILURE" << endl;
    print(ol.add_contestant_to_team(33,311));
    cout << "== SUCCESS" << endl;
    print(ol.remove_team(33)); //try to remove team with contestant
    cout << "== FAILURE" << endl;
    cout << endl << "---------done team check--------" << endl << "contestant check:" << endl;
    // conestant check
    print(ol.remove_contestant(311)); // try to delete contestant whos active
    cout << "== FAILURE" << endl;
    print(ol.remove_contestant(0)); // invalid id
    cout << "== INVALID INPUT" << endl;
    print(ol.remove_contestant(2)); // try to delete none exisiting contestant
    cout << "== FAILURE" << endl;
    print(ol.add_contestant(311,333,Sport::FOOTBALL,4)); // try to add the same contestant
    cout << "== FAILURE" << endl;
    print(ol.add_contestant(311,222,Sport::FOOTBALL,4)); // the same contestant to diff country
    cout << "== FAILURE" << endl;
    print(ol.add_contestant(0,333,Sport::FOOTBALL,4)); // invalid id
    cout << "== INVALID INPUT" << endl;
    print(ol.add_contestant(312,0,Sport::ACROBATICS,6));// invalid country id
    cout << "== INVALID INPUT" << endl;
    print(ol.add_contestant(312,333,Sport::ACROBATICS,-1));// invalid strength
    cout << "== INVALID INPUT" << endl;
    print(ol.remove_contestant_from_team(33,311));
    cout << "== SUCCESS" << endl;
    print(ol.remove_contestant(311));
    cout << "== SUCCESS" << endl;

    cout <<endl<< "-----------done conestant check------" << endl << "checking contestant to team: " << endl;
    // countries: 222, 333  teams: 22-football , 33-acro
    ol.add_team(44,333,Sport::ACROBATICS);
    ol.add_team(55,333,Sport::ACROBATICS);
    ol.add_team(66,333,Sport::ACROBATICS);
    ol.add_team(77,333,Sport::FOOTBALL);
    ol.add_contestant(311,333,Sport::ACROBATICS,5);
    ol.add_contestant(312,333,Sport::ACROBATICS,6);
    ol.add_contestant(313,333,Sport::ACROBATICS,3);
    ol.add_contestant(304,333,Sport::ACROBATICS,9);
    ol.add_contestant_to_team(44,311);
    ol.add_contestant_to_team(66,311);
    ol.add_contestant_to_team(33,311);
    print(ol.add_contestant_to_team(55,311)); // trying to add to more than 3 teams
    cout << "==FAILURE" << endl;
    print(ol.add_contestant_to_team(77,312)); // diff sports
    cout << "==FAILURE"<< endl;
    print(ol.add_contestant_to_team(22,311)); // no matching contestant's country id
    cout << "==FAILURE"<< endl;
    print(ol.add_contestant_to_team(0,311)); // invalid id
    cout << "==INVALID_INPUT" << endl;
    print(ol.add_contestant_to_team(22,0)); // invalid id
    cout << "==INVALID_INPUT" << endl;
    print(ol.add_contestant_to_team(22,56)); // none existing contestant
    cout << "==FAILURE" << endl;
    print(ol.remove_contestant_from_team(22,0)); // invalid id
    cout << "==INVALID_INPUT" << endl;
    print(ol.remove_contestant_from_team(0,30)); // invalid id
    cout << "==INVALID_INPUT" << endl;
    print(ol.remove_contestant_from_team(22,30)); // none existing contestant
    cout << "==FAILURE" << endl;
    print(ol.remove_contestant_from_team(77,311)); // 311 is in team 44,66,33
    cout << "==FAILURE" << endl;
    print(ol.remove_contestant_from_team(44,311));
    cout << "==SUCCESS" << endl;

    cout <<endl<< "-----------done conestant to team check------" << endl << "checking update strength,get strength:" << endl;
    // countries: 222, 333
    // teams: 22-football-222 , 33-acro-333 , 44-acro-333 , 55-acro-333 , 66-acro-333, 77-football-333
    // contestants : 311-acro- 66,33 (5)   |  312-acro (6) | 313-acro (3) | 304-acro (9)
    print(ol.get_strength(311));
    cout << "==5" <<endl;
    print(ol.update_contestant_strength(311,7));
    cout << "==12" <<endl;
    print(ol.update_contestant_strength(311,-15)); // below 0
    cout << "FAILURE" <<endl;
    print(ol.update_contestant_strength(0,6)); // invalid id
    cout << "INVALID_INPUT" << endl;
    print(ol.update_contestant_strength(5,6)); // no existing id
    cout << "FAILURE" << endl;
    print(ol.get_strength(0)); // invalid id
    cout << "INVALID_INPUT" << endl;
    print(ol.get_strength(5)); // no existing id
    cout << "FAILURE" << endl;

}



