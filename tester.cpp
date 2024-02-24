////
//// Created by Lotan Dahan on 22/02/2024.
////

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
    cout << "==SUCCESS" <<endl;
    print(ol.get_strength(311));
    cout << "==12" <<endl;
    print(ol.update_contestant_strength(311,-15)); // below 0
    cout << "==FAILURE" <<endl;
    print(ol.update_contestant_strength(0,6)); // invalid id
    cout << "==INVALID_INPUT" << endl;
    print(ol.update_contestant_strength(5,6)); // no existing id
    cout << "==FAILURE" << endl;
    print(ol.get_strength(0)); // invalid id
    cout << "==INVALID_INPUT" << endl;
    print(ol.get_strength(5)); // no existing id
    cout << "==FAILURE" << endl;
    print(ol.update_contestant_strength(312,44));
    cout << "==SUCCESS" <<endl;
    print(ol.get_strength(312));
    cout << "==50" <<endl;
    cout <<endl<< "-----------done update strength,get strength------" << endl << "checking get medals:" << endl;

    print(ol.get_medals(222));
    cout << "==4" <<endl;
    print(ol.get_medals(333));
    cout << "==15" <<endl;
    print(ol.get_medals(0)); // invalid id
    cout << "==INVALID INPUT" <<endl;
    print(ol.get_medals(4)); // none existing country
    cout << "==FAILURE" <<endl;
    cout <<endl<< "-----------done get medal------" << endl << "checking get team str and play match:" << endl;
    // countries: 222-4, 333-15
    // teams: 22-football-222 , 33-acro-333 , 44-acro-333 , 55-acro-333 , 66-acro-333, 77-football-333
    // contestants : 311-acro- 66,33 (12)   |  312-acro (50) | 313-acro (3) | 304-acro (9)
    //changing data:
    print(ol.remove_contestant_from_team(66,311));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(210,222,Sport::FOOTBALL,6));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(215,222,Sport::FOOTBALL,22));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(213,222,Sport::FOOTBALL,9));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(315,333,Sport::ACROBATICS,2));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(305,333,Sport::ACROBATICS,10));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(366,333,Sport::ACROBATICS,20));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(367,333,Sport::ACROBATICS,5));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(368,333,Sport::ACROBATICS,15));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(266,222,Sport::ACROBATICS,2));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(267,222,Sport::ACROBATICS,5));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant(268,222,Sport::ACROBATICS,15));
    cout << "==SUCCESS" <<endl;
    print(ol.add_team(23,222,Sport::ACROBATICS));
    cout << "==SUCCESS" <<endl;
    print(ol.update_contestant_strength(312,-34));
    cout << "==SUCCESS" <<endl;
    print(ol.get_strength(312));
    cout << "==16" << endl;
    print(ol.add_contestant_to_team(22,210));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(22,213));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(22,215));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(33,305));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(33,312));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(33,313));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(33,304));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(33,315));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(66,366));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(66,367));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(66,368));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(55,368));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(55,311));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(23,266));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(23,267));
    cout << "==SUCCESS" <<endl;
    print(ol.add_contestant_to_team(23,268));

    print(ol.get_team_strength(33));
    cout << "==29" <<endl;
    print(ol.get_team_strength(22));
    cout << "==37" <<endl;
    print(ol.get_team_strength(66));
    cout << "==40" <<endl;
    print(ol.get_team_strength(44));
    cout << "==0" <<endl;
    print(ol.get_team_strength(55));
    cout << "==0" <<endl;
    print(ol.get_team_strength(23));
    cout << "==22" <<endl;
    print(ol.get_team_strength(0)); // id invalid
    cout << "==INVALID_INPUT" <<endl;
    print(ol.get_team_strength(7)); // none exisiting
    cout << "==FAILURE" <<endl;

    print(ol.play_match(22,22)); // id1==id2
    cout << "==INVALID_INPUT" <<endl;
    print(ol.play_match(22,0)); // id2 invalid
    cout << "==INVALID_INPUT" <<endl;
    print(ol.play_match(4,22)); // id1 not exist
    cout << "==FAILURE" <<endl;
    print(ol.play_match(23,8)); // id2 not exist
    cout << "==FAILURE" <<endl;
    print(ol.play_match(0,22)); //id1 invalid
    cout << "==INVALID_INPUT" <<endl;
    print(ol.play_match(55,22)); //diff sport
    cout << "==FAILURE" <<endl;
    print(ol.get_medals(333));
    cout << "==15" <<endl;
    print(ol.play_match(33,66));
    cout << "==SUCCESS" <<endl;
    print(ol.get_medals(333));
    cout << "==16" <<endl;
    print(ol.get_medals(222));
    cout << "==4" <<endl;
    print(ol.play_match(23,55));
    cout << "==SUCCESS" <<endl;
    print(ol.get_medals(222));
    cout << "==5" <<endl;
    print(ol.play_match(44,55)); // no change in medal - tie
    cout << "==SUCCESS" <<endl;
    print(ol.get_medals(333));
    cout << "==16" <<endl;

    cout <<endl<< "-----------done get team str and play match------" << endl << "checking unite teams:" << endl;
    print(ol.unite_teams(22,0)); // id2 invalid
    cout << "==INVALID INPUT" << endl;
    print(ol.unite_teams(0,22)); // id1 invalid
    cout << "==INVALID INPUT" << endl;
    print(ol.unite_teams(22,22)); // id1==id2
    cout << "==INVALID INPUT" << endl;
    print(ol.unite_teams(22,23)); // diff sport
    cout << "==FAILURE" << endl;
    print(ol.unite_teams(6,23)); //  id1 not exist
    cout << "==FAILURE" << endl;
    print(ol.unite_teams(22,8)); //  id2 not exist
    cout << "==FAILURE" << endl;
    print(ol.unite_teams(22,66)); //  diff countries
    cout << "==FAILURE" << endl;
    print(ol.get_team_strength(33));
    cout << "==29" << endl;
    print(ol.austerity_measures(33));
    cout << "==38" << endl;
    print(ol.unite_teams(33,66));
    cout << "==SUCCESS" << endl;
    print(ol.get_team_strength(33));
    cout << "==48" << endl;
    print(ol.get_team_strength(66)); // united with 33 so doesnt exist
    cout << "==FAILURE" << endl;
    print(ol.add_team(66,222,Sport::ACROBATICS));
    cout << "==SUCCESS" << endl;



    cout <<endl<< "-----------done unite teams------" << endl << "checking austerity measures:" << endl;

    print(ol.austerity_measures(0)); // invalid id
    cout << "==INVALID INPUT" << endl;
    print(ol.austerity_measures(9)); // not exist
    cout << "==FAILURE" << endl;
    print(ol.austerity_measures(55)); // less than 3 contestants
    cout << "==FAILURE" << endl;
    print(ol.austerity_measures(22)); // only 3 contestants
    cout << "==0" << endl;
    print(ol.austerity_measures(33)); // only 3 contestants
    cout << "==51" << endl;


    cout <<endl<< "-----------done austerity measures------" << endl;
    cout <<endl<< "-----------more tests------" << endl;

    Olympics ol2 = Olympics();
    print(ol2.austerity_measures(2));
    cout << "==FAILURE" << endl;
    print(ol2.remove_contestant_from_team(2,44));
    cout << "==FAILURE" << endl;
    print(ol2.remove_team(2));
    cout << "==FAILURE" << endl;
    print(ol2.remove_contestant(2));
    cout << "==FAILURE" << endl;
    print(ol2.play_match(2,4));
    cout << "==FAILURE" << endl;
    print(ol2.austerity_measures(2));
    cout << "==FAILURE" << endl;
    print(ol2.get_team_strength(2));
    cout << "==FAILURE" << endl;
    print(ol2.get_strength(2));
    cout << "==FAILURE" << endl;
    print(ol2.get_medals(2));
    cout << "==FAILURE" << endl;
    print(ol2.remove_country(2));
    cout << "==FAILURE" << endl;
    print(ol2.add_country(2,5));
    cout << "==SUCCESS" << endl;
    print(ol2.add_country(3,6));
    cout << "==SUCCESS" << endl;
    print(ol2.remove_country(3));
    cout << "==SUCCESS" << endl;
    print(ol2.add_country(3,6));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(200,2,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(210,2,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(220,2,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(230,2,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(240,2,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(250,2,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(260,2,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(270,2,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(300,3,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(310,3,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(320,3,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(330,3,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(340,3,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(350,3,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;
    print(ol2.add_team(360,3,Sport::FOOTBALL));
    cout << "==SUCCESS" << endl;

    print(ol2.add_contestant(20,2,Sport::FOOTBALL,4));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(21,2,Sport::FOOTBALL,5));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(22,2,Sport::FOOTBALL,3));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(23,2,Sport::FOOTBALL,14));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(24,2,Sport::FOOTBALL,8));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(25,2,Sport::FOOTBALL,9));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(26,2,Sport::FOOTBALL,2));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(27,2,Sport::FOOTBALL,6));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(28,2,Sport::FOOTBALL,10));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(29,2,Sport::FOOTBALL,11));
    cout << "==SUCCESS" << endl;

    print(ol2.add_contestant(30,3,Sport::FOOTBALL,9));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(31,3,Sport::FOOTBALL,10));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(32,3,Sport::FOOTBALL,3));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(33,3,Sport::FOOTBALL,7));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(34,3,Sport::FOOTBALL,4));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(35,3,Sport::FOOTBALL,9));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(36,3,Sport::FOOTBALL,2));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(37,3,Sport::FOOTBALL,1));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(38,3,Sport::FOOTBALL,10));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant(39,3,Sport::FOOTBALL,11));
    cout << "==SUCCESS" << endl;

    print(ol2.add_contestant_to_team(220,20));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(230,21));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(240,22));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(250,26));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(250,29));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(260,25));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(260,28));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(270,27));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(270,26));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(270,25));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(270,23));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(270,24));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(270,28));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(270,29));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(270,22));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(270,21));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(300,30));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(300,31));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(300,37));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(300,32));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(300,33));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(300,35));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(300,34));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(300,39));
    cout << "==SUCCESS" << endl;
    print(ol2.add_contestant_to_team(300,38));
    cout << "==SUCCESS" << endl;

    print(ol2.unite_teams(220,230));
    cout << "==SUCCESS" << endl;
    print(ol2.unite_teams(220,250));
    cout << "==SUCCESS" << endl;
    print(ol2.unite_teams(220,260));
    cout << "==SUCCESS" << endl;
    print(ol2.get_team_strength(220));
    cout << "==24" << endl;
    print(ol2.austerity_measures(220));
    cout << "==30" << endl;
    print(ol2.get_team_strength(270));
    cout << "==34" << endl;
    print(ol2.austerity_measures(270));
    cout << "==34" << endl;
    print(ol2.get_team_strength(300));
    cout << "==30" << endl;
    print(ol2.get_medals(2));
    cout << "==5" << endl;
    print(ol2.get_medals(3));
    cout << "==6" << endl;
    print(ol2.play_match(270,300));
    cout << "==SUCCESS MATCH1" << endl;
    print(ol2.get_medals(2));
    cout << "==6" << endl;
    print(ol2.get_medals(3));
    cout << "==6" << endl;
    print(ol2.update_contestant_strength(34,9));
    cout << "==SUCCESS" << endl;
    print(ol2.get_team_strength(300));
    cout << "==34" << endl;
    print(ol2.play_match(270,300));
    cout << "==SUCCESS MATCH2" << endl;
    print(ol2.get_medals(2));
    cout << "==6" << endl;
    print(ol2.get_medals(3));
    cout << "==6" << endl;
    print(ol2.update_contestant_strength(32,10));
    cout << "==SUCCESS" << endl;
    print(ol2.get_team_strength(300));
    cout << "==37" << endl;
    print(ol2.play_match(270,300));
    cout << "==SUCCESS MATCH3" << endl;
    print(ol2.get_medals(2));
    cout << "==6" << endl;
    print(ol2.get_medals(3));
    cout << "==7" << endl;

    print(ol2.austerity_measures(300));
    cout << "==37" << endl;
   print(ol2.austerity_measures(220));
    cout << "==30" << endl;
   print(ol2.remove_contestant_from_team(300,37));////// something is wrong here
    print(ol2.remove_contestant_from_team(300,34));
    print(ol2.remove_contestant_from_team(300,30));
    print(ol2.austerity_measures(300));




}



