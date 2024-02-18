#ifndef WET1_WINTER2024_TEAM_H
#define WET1_WINTER2024_TEAM_H

#include "wet1util.h"
#include "AVL_tree.h"
#include "Contestant.h"
#include "Country.h"
#include "ContestantID.h"
#include "ContestantStr.h"
#include "StrCond.h"

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
    AVLTree<ContestantStr*, StrCond> contenstantStr1;
    AVLTree<ContestantID*, int> contenstantId2;
    AVLTree<ContestantStr*, StrCond> contenstantStr2;
    AVLTree<ContestantID*, int> contenstantId3;
    AVLTree<ContestantStr*, StrCond> contenstantStr3;
    void moveContestant(AVLTree<ContestantID*, int>* idDest,AVLTree<ContestantStr*, StrCond>* strDest,
            AVLTree<ContestantID*, int>* idSrc,AVLTree<ContestantStr*, StrCond>* strSrc,
            Node<ContestantID*, int> * item);
    void deleteInOrderID(Node<ContestantID*, int>* node);
    void deleteInOrderStr(Node<ContestantStr*, StrCond>* node);
public:
    Team(int teamId,int countryId, Sport sport,Country* country);
    Team(const Team &toCopy) = default;
    ~Team()= default;
    int getContestantCount();
    Country* getCountryPtr();
    Sport get_sport();
    int getID();
    int getTeamSize(int teamNum);
    void addContestantToTeam(Contestant * contestant);
    void removeContestantFromTeam(Contestant * contestant);
    bool aleadyExists(int id);
    void destoryTrees();
    void updateContestantStr(int id, int prevStr, int str);
    int getTeamStrength();
    void fillArray(Node<ContestantID*, int>* ID[], Node<ContestantStr*, StrCond>* Str1[],
                   Node<ContestantStr*, StrCond>* Str2[], Node<ContestantStr*, StrCond>* Str3[], int size1,
                   int size2, int size3);
    void merge2arrays(Node<ContestantID*, int>* total[], Node<ContestantID*, int>* ID1[],
                      Node<ContestantID*, int>* ID2[], int size1, int size2);
    int austerity_measures();
};



#endif //WET1_WINTER2024_TEAM_H
