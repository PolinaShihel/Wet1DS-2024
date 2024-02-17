#include "Team.h"

Team::Team(int teamId, int countryId, Sport sport, Country *CountryPtr) :
        teamId(teamId), countryId(countryId), sport(sport), countryPtr(CountryPtr) {}


int Team::getContestantCount() {
    return this->contenstantId1.getSize() + this->contenstantId2.getSize() + this->contenstantId3.getSize();
}

Country* Team::getCountryPtr() {
    return this->countryPtr;
}

Sport Team::get_sport() {
    return this->sport;
}

bool Team::aleadyExists(int id)
{
    return (this->contenstantId1.exist(id)||this->contenstantId2.exist(id)||this->contenstantId3.exist(id));
}

void Team::addContestantToTeam(Contestant *contestant) {
    int id = contestant->get_id();
    int str = contestant->get_strength();
    Node<ContestantID *, int> *id1 = this->contenstantId1.getBiggest();
    Node<ContestantID *, int> *idSmall2 = this->contenstantId2.getSmallest();
    Node<ContestantID *, int> *idBig2 = this->contenstantId2.getBiggest();
    Node<ContestantID *, int> *id3 = this->contenstantId3.getSmallest();
    ContestantID* toAddID = new ContestantID(contestant);
    ContestantStr* toAddSTR;
    try{
        toAddSTR = new ContestantStr(toAddID,contestant);
        toAddID->setStrPtr(toAddSTR);
    }
    catch (std::bad_alloc &error) {
        delete toAddID;
        throw;
    }
    StrCond strCond = StrCond(str,id);
    try
    {
        if (id1 == nullptr || id < id1->getKey()) {
            this->contenstantId1.insert(id, toAddID);
            this->contenstantStr1.insert(strCond, toAddSTR);

            if (this->contenstantId1.getSize() > this->contenstantId2.getSize() + 1) {
//                move id1 to id2
                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId1, &this->contenstantStr1,
                                     id1);
            } else if (this->contenstantId1.getSize() > this->contenstantId3.getSize() + 1) {
//                    move id2 biggest to id3 and move id1 biggest to id2
                this->moveContestant(&this->contenstantId3, &this->contenstantStr3,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idBig2);

                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId1, &this->contenstantStr1,
                                     id1);
            }
        } else if (idSmall2 == nullptr || (id > id1->getKey() && id < idBig2->getKey())) {
            this->contenstantId2.insert(id, toAddID);
            this->contenstantStr2.insert(strCond, toAddSTR);
            if (this->contenstantId2.getSize() > this->contenstantId1.getSize() + 1) {
//                   move id2 smallest to id1
                this->moveContestant(&this->contenstantId1, &this->contenstantStr1,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idSmall2);
            } else if (this->contenstantId2.getSize() > this->contenstantId3.getSize() + 1) {
//                  move id2 biggest to id3
                this->moveContestant(&this->contenstantId3, &this->contenstantStr3,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idBig2);
            };
        } else if (id3 == nullptr || id > idBig2->getKey()) {
            this->contenstantId3.insert(id, toAddID);
            this->contenstantStr3.insert(strCond, toAddSTR);

            if (this->contenstantId3.getSize() > this->contenstantId2.getSize() + 1) {
//                move id3 smallest to id2
                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId3, &this->contenstantStr3,
                                     id3);
            } else if (this->contenstantId3.getSize() > this->contenstantId1.getSize() + 1) {
//                move id2 smallest to id1 and move id3 smallest to id2
                this->moveContestant(&this->contenstantId1, &this->contenstantStr1,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idSmall2);

                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId3, &this->contenstantStr3,
                                     id3);
            }
        }
    }
    catch (...)
    {
        delete toAddID;
        delete toAddSTR;
        throw;
    }
}

void Team::moveContestant(AVLTree<ContestantID *, int> *idDest, AVLTree<ContestantStr *, StrCond> *strDest,
                          AVLTree<ContestantID *, int> *idSrc, AVLTree<ContestantStr *, StrCond> *strSrc,
                          Node<ContestantID *, int> *item) {
    int id = item->getKey();
    ContestantStr *contestantStr = item->getNodeData()->getContestantStrPtr();
    int str = contestantStr->getConPtr()->get_strength();
    StrCond strCond = StrCond(str,id);
    idDest->insert(id, item->getNodeData());
    strDest->insert(strCond, contestantStr);
    idSrc->remove(id);
    strSrc->remove(strCond);
}