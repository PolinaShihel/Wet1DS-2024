#include "Team.h"

Team::Team(int teamId, int countryId, Sport sport, Country *CountryPtr) :
        teamId(teamId), countryId(countryId), sport(sport), countryPtr(CountryPtr) {}


int Team::getContestantCount() {
    return this->contenstantId1.getSize() + this->contenstantId2.getSize() + this->contenstantId3.getSize();
}

Country *Team::getCountryPtr() {
    return this->countryPtr;
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
//    TODO change nullptr with new objects, wrap in try catch if catch delete
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
    try
    {
        if (id1 == nullptr || id < id1->getKey()) {
            if (this->contenstantId1.getSize() > this->contenstantId2.getSize()) {
//                move id1 to id2
                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId1, &this->contenstantStr1,
                                     id1);
            } else if (this->contenstantId1.getSize() > this->contenstantId3.getSize()) {
//                    move id2 biggest to id3 and move id1 biggest to id2
                this->moveContestant(&this->contenstantId3, &this->contenstantStr3,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idBig2);

                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId1, &this->contenstantStr1,
                                     id1);
            }
            this->contenstantId1.insert(id, toAddID);
            this->contenstantStr1.insert(str, toAddSTR);
        } else if (idSmall2 == nullptr || (id > idSmall2->getKey() && id < idBig2->getKey())) {
            if (this->contenstantId2.getSize() > this->contenstantId1.getSize()) {
//                   move id2 smallest to id1
                this->moveContestant(&this->contenstantId1, &this->contenstantStr1,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idSmall2);
            } else if (this->contenstantId2.getSize() > this->contenstantId3.getSize()) {
//                  move id2 biggest to id3
                this->moveContestant(&this->contenstantId3, &this->contenstantStr3,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idBig2);
            }
            this->contenstantId2.insert(id, toAddID);
            this->contenstantStr2.insert(str, toAddSTR);
        } else if (id3 == nullptr || id > id3->getKey()) {
            if (this->contenstantId3.getSize() > this->contenstantId2.getSize()) {
//                move id3 smallest to id2
                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId3, &this->contenstantStr3,
                                     id3);
            } else if (this->contenstantId3.getSize() > this->contenstantId1.getSize()) {
//                move id2 smallest to id1 and move id3 smallest to id2
                this->moveContestant(&this->contenstantId1, &this->contenstantStr1,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idSmall2);

                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId3, &this->contenstantStr3,
                                     id3);
            }
            this->contenstantId1.insert(id, toAddID);
            this->contenstantStr1.insert(str, toAddSTR);
        }
    }
    catch (...)
    {
        delete toAddID;
        delete toAddSTR;
        throw;
    }
}

void Team::moveContestant(AVLTree<ContestantID *, int> *idDest, AVLTree<ContestantStr *, int> *strDest,
                          AVLTree<ContestantID *, int> *idSrc, AVLTree<ContestantStr *, int> *strSrc,
                          Node<ContestantID *, int> *item) {
    int id = item->getKey();
    ContestantStr *contestantStr = item->getNodeData()->getContestantStrPtr();
    int str = contestantStr->getConPtr()->get_strength();
    idDest->insert(id, item->getNodeData());
    strDest->insert(str, contestantStr);
    idSrc->remove(id);
    strSrc->remove(str);
}