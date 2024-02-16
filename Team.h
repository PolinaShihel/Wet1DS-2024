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
    AVLTree<ContestantI int> contenstantId3;
    AVLTree<ContestantStr*, int> contenstantStr3;
//    Node<ContestantStr*,int> * contenstantStr1Max; // check after insert and delete if max/min changed
//    Node<ContestantStr*,int> * contenstantStr1Min;
//    Node<ContestantStr*,int> * contenstantStr2Max;
//    Node<ContestantStr*,int> * contenstantStr2Min;
//    Node<ContestantStr*,int> * contenstantStr3Max;
//    Node<ContestantStr*,int> * contenstantStr3Min;

public:

};



#endif //WET1_WINTER2024_TEAM_H
