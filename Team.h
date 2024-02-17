#ifndef WET1_WINTER2024_TEAM_H
#define WET1_WINTER2024_TEAM_H

#include "wet1util.h"
#include "AVL_tree.h"
#include "Contestant.h"
#include "Country.h"
#include "ContestantID.h"
#include "ContestantStr.h"

class Contestant;
class Country;
class ContestantID;
class ContestantStr;
class Team {
private:
    int teamId;
    int countryId;
    Sport sport;
    Country* countryPtr;
    AVLTree<ContestantID*, int> contenstantId1;
    AVLTree<ContestantStr*, int> contenstantStr1;
    AVLTree<ContestantID*, int> contenstantId2;
    AVLTree<ContestantStr*, int> contenstantStr2;
    AVLTree<ContestantID*, int> contenstantId3;
    AVLTree<ContestantStr*, int> contenstantStr3;
    void moveContestant(AVLTree<ContestantID*, int>* idDest,AVLTree<ContestantStr*, int>* strDest,
            AVLTree<ContestantID*, int>* idSrc,AVLTree<ContestantStr*, int>* strSrc,
            Node<ContestantID*, int> * item);
public:
    Team(int teamId,int countryId, Sport sport,Country* country);
    Team(const Team &toCopy) = default;
    ~Team()= default;
    int getContestantCount();
    Country* getCountryPtr();
    void addContestantToTeam(Contestant * contestant);
    bool aleadyExists(int id);
};



#endif //WET1_WINTER2024_TEAM_H
