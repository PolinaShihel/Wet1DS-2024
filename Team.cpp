#include "Team.h"

Team::Team(int teamId, int countryId, Sport sport, Country *CountryPtr) :
        teamId(teamId), countryId(countryId), sport(sport), countryPtr(CountryPtr) {}


int Team::getContestantCount() {
    return this->contenstantId1.getSize() + this->contenstantId2.getSize() + this->contenstantId3.getSize();
}

Country *Team::getCountryPtr() {
    return this->countryPtr;
}

Sport Team::get_sport() {
    return this->sport;
}

int Team::getID(){
    return this->teamId;
}

int Team::getTeamSize(int teamNum)
{
    if(teamNum == 1)
        return this->contenstantId1.getSize();
    if(teamNum == 2)
        return this->contenstantId2.getSize();
    return this->contenstantId3.getSize();
}
bool Team::aleadyExists(int id) {
    return (this->contenstantId1.exist(id) || this->contenstantId2.exist(id) || this->contenstantId3.exist(id));
}


void Team::addContestantToTeam(Contestant *contestant) {
    int id = contestant->get_id();
    int str = contestant->get_strength();
    Node<ContestantID *, int> *id1 = this->contenstantId1.getBiggest();
    Node<ContestantID *, int> *idSmall2 = this->contenstantId2.getSmallest();
    Node<ContestantID *, int> *idBig2 = this->contenstantId2.getBiggest();
    Node<ContestantID *, int> *id3 = this->contenstantId3.getSmallest();
    ContestantID *toAddID = new ContestantID(contestant);
    ContestantStr *toAddSTR;
    try {
        toAddSTR = new ContestantStr(toAddID, contestant);
        toAddID->setStrPtr(toAddSTR);
    }
    catch (std::bad_alloc &error) {
        delete toAddID;
        throw;
    }
    StrCond strCond = StrCond(str, id);
    try {
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
    catch (...) {
        delete toAddID;
        delete toAddSTR;
        throw;
    }
}

void Team::removeContestantFromTeam(Contestant *contestant) {
    int id = contestant->get_id();
    int str = contestant->get_strength();
    Node<ContestantID *, int> *id1 = this->contenstantId1.getBiggest();
    Node<ContestantID *, int> *idSmall2 = this->contenstantId2.getSmallest();
    Node<ContestantID *, int> *idBig2 = this->contenstantId2.getBiggest();
    Node<ContestantID *, int> *id3 = this->contenstantId3.getSmallest();
    StrCond strCond = StrCond(str, id);
    int id1Size = this->contenstantId1.getSize();
    int id2Size = this->contenstantId2.getSize();
    int id3Size = this->contenstantId3.getSize();
    if (id <= id1->getKey()) {
        ContestantID *toDelete = *(this->contenstantId1.find(id));
        ContestantStr *toDeleteStr = toDelete->getContestantStrPtr();
        this->contenstantId1.remove(id);
        this->contenstantStr1.remove(strCond);
        delete toDelete;
        delete toDeleteStr;
        id1Size--;
        if (id1Size == 0) {
            if (id2Size > 0) {
                this->moveContestant(&this->contenstantId1, &this->contenstantStr1,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idSmall2);
                id2Size--;
                if (id2Size == 0 && id3Size > 0) {
                    this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                         &this->contenstantId3, &this->contenstantStr3,
                                         id3);
                }
            }
        } else {
            if (id1Size + 1 < id2Size) {
                this->moveContestant(&this->contenstantId1, &this->contenstantStr1,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idSmall2);
            } else if (id1Size + 1 < id3Size) {
                this->moveContestant(&this->contenstantId1, &this->contenstantStr1,
                                     &this->contenstantId2, &this->contenstantStr2,
                                     idSmall2);
                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId3, &this->contenstantStr3,
                                     id3);
            }
        }
    } else if (id >= idSmall2->getKey() && id <= idBig2->getKey()) {
        ContestantID *toDelete = *(this->contenstantId2.find(id));
        ContestantStr *toDeleteStr = toDelete->getContestantStrPtr();
        this->contenstantId2.remove(id);
        this->contenstantStr2.remove(strCond);
        delete toDelete;
        delete toDeleteStr;
        id2Size--;
        if (id2Size == 0 && id3Size > 0) {
            this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                 &this->contenstantId3, &this->contenstantStr3,
                                 id3);
        } else {
            if (id2Size + 1 < id1Size) {
                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId1, &this->contenstantStr1,
                                     id1);
            } else if (id2Size + 1 < id3Size) {
                this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                     &this->contenstantId3, &this->contenstantStr3,
                                     id3);
            }
        }
    } else if (id > id3->getKey()) {
        ContestantID *toDelete = *(this->contenstantId3.find(id));
        ContestantStr *toDeleteStr = toDelete->getContestantStrPtr();
        this->contenstantId3.remove(id);
        this->contenstantStr3.remove(strCond);
        delete toDelete;
        delete toDeleteStr;
        id3Size--;
        if(id3Size + 1 < id2Size){
            this->moveContestant(&this->contenstantId3, &this->contenstantStr3,
                                 &this->contenstantId2, &this->contenstantStr2,
                                 idBig2);
        }
        else if(id3Size + 1 < id1Size){
            this->moveContestant(&this->contenstantId3, &this->contenstantStr3,
                                 &this->contenstantId2, &this->contenstantStr2,
                                 idBig2);
            this->moveContestant(&this->contenstantId2, &this->contenstantStr2,
                                 &this->contenstantId1, &this->contenstantStr1,
                                 id1);
        }
    }
}

void Team::destoryTrees(){
    deleteInOrderStr(this->contenstantStr1.getRoot());
    deleteInOrderStr(this->contenstantStr2.getRoot());
    deleteInOrderStr(this->contenstantStr3.getRoot());
    deleteInOrderID(this->contenstantId1.getRoot());
    deleteInOrderID(this->contenstantId2.getRoot());
    deleteInOrderID(this->contenstantId3.getRoot());
}

void Team::deleteInOrderStr(Node<ContestantStr*, StrCond>* node){
    if(node == nullptr)
        return;
    this->deleteInOrderStr(node->getLeft());
    delete (node->getNodeData());
    this->deleteInOrderStr(node->getRight());

}
void Team::deleteInOrderID(Node<ContestantID*, int>* node){
    if(node == nullptr)
        return;
    this->deleteInOrderID(node->getLeft());
    delete (node->getNodeData());
    this->deleteInOrderID(node->getRight());
}

void Team::moveContestant(AVLTree<ContestantID *, int> *idDest, AVLTree<ContestantStr *, StrCond> *strDest,
                          AVLTree<ContestantID *, int> *idSrc, AVLTree<ContestantStr *, StrCond> *strSrc,
                          Node<ContestantID *, int> *item) {
    int id = item->getKey();
    ContestantStr *contestantStr = item->getNodeData()->getContestantStrPtr();
    int str = contestantStr->getConPtr()->get_strength();
    StrCond strCond = StrCond(str, id);

    idDest->insert(id, item->getNodeData());
    strDest->insert(strCond, contestantStr);

    idSrc->remove(id);
    strSrc->remove(strCond);
}

void Team::updateContestantStr(int id, int prevStr, int str){
    int id1 = this->contenstantId1.getBiggest()->getKey();
    int idSmall2 = this->contenstantId2.getSmallest()->getKey();
    int idBig2 = this->contenstantId2.getBiggest()->getKey();
    StrCond st = StrCond(prevStr,id);
    if(id <= id1) //the contestant is in the first tree
    {
        ContestantStr * strObj =  *(this->contenstantStr1.find(st));
        this->contenstantStr1.remove(st);
        st = StrCond(str,id);
        this->contenstantStr1.insert(st,strObj);
    }
    else if((id >= idSmall2)&&(id <= idBig2))//the contestant is in the second tree
    {
        ContestantStr * strObj =  *(this->contenstantStr2.find(st));
        this->contenstantStr2.remove(st);
        st = StrCond(str,id);
        this->contenstantStr2.insert(st,strObj);
    }
    else{//the contestant is in the third tree
        ContestantStr * strObj =  *(this->contenstantStr3.find(st));
        this->contenstantStr3.remove(st);
        st = StrCond(str,id);
        this->contenstantStr3.insert(st,strObj);
    }
}

int Team::getTeamStrength(){
    if((this->getContestantCount()%3) != 0)
        return 0;
    return this->contenstantStr1.getBiggest()->getKey() + this->contenstantStr2.getBiggest()->getKey()
                                                                     + this->contenstantStr3.getBiggest()->getKey();
}

void Team::fillArray(Node<ContestantID*, int>* ID[], Node<ContestantStr*, StrCond>* Str1[],
               Node<ContestantStr*, StrCond>* Str2[], Node<ContestantStr*, StrCond>* Str3[],
               int size1, int size2, int size3)
{
    this->contenstantId1.fillArray(ID, 0);
    if(size2!=0 || size3!=0)
        this->contenstantId2.fillArray(ID, size1);
    if(size3!=0)
        this->contenstantId3.fillArray(ID, size1+size2);
    this->contenstantStr1.fillArray(Str1, 0);
    this->contenstantStr2.fillArray(Str2, 0);
    this->contenstantStr3.fillArray(Str3, 0);
}

void Team::merge2arrays(Node<ContestantID*, int>* total[], Node<ContestantID*, int>* ID1[],
                        Node<ContestantID*, int>* ID2[], int size1, int size2)
{

}
