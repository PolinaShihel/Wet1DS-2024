#include "Team.h"

Team::Team(int teamId, Sport sport, Country *CountryPtr)
        : teamId(teamId), sport(sport),
          countryPtr(CountryPtr), contenstantId1(new AVLTree<ContestantID *, int>()),
          contenstantStr1(new AVLTree<ContestantStr *, StrCond>()), contenstantId2(new AVLTree<ContestantID *, int>()),
          contenstantStr2(new AVLTree<ContestantStr *, StrCond>()), contenstantId3(new AVLTree<ContestantID *, int>()),
          contenstantStr3(new AVLTree<ContestantStr *, StrCond>()) {
}

Team::Team(int teamId, Sport sport, Country *CountryPtr,
           Node<ContestantID *, int> *teamTotalID[], int unitedStr1Size,
           int unitedStr2Size, int unitedStr3Size,
           Node<ContestantStr *, StrCond> *unitedStr1[],
           Node<ContestantStr *, StrCond> *unitedStr2[],
           Node<ContestantStr *, StrCond> *unitedStr3[])
        : teamId(teamId), sport(sport),
          countryPtr(CountryPtr) {

    this->contenstantId1 = new AVLTree<ContestantID *, int>(
            teamTotalID, unitedStr1Size, 0, unitedStr1Size - 1);
    this->contenstantId2 = new AVLTree<ContestantID *, int>(
            teamTotalID, unitedStr2Size, unitedStr1Size,
            unitedStr1Size + unitedStr2Size - 1);
    this->contenstantId3 = new AVLTree<ContestantID *, int>(
            teamTotalID, unitedStr3Size, unitedStr1Size + unitedStr2Size,
            unitedStr1Size + unitedStr2Size + unitedStr3Size - 1);
    this->contenstantStr1 = new AVLTree<ContestantStr *, StrCond>(
            unitedStr1, unitedStr1Size, 0, unitedStr1Size - 1);
    this->contenstantStr2 = new AVLTree<ContestantStr *, StrCond>(
            unitedStr2, unitedStr2Size, 0, unitedStr2Size - 1);
    this->contenstantStr3 = new AVLTree<ContestantStr *, StrCond>(
            unitedStr3, unitedStr3Size, 0, unitedStr3Size - 1);
}

int Team::getContestantCount() {
    return this->contenstantId1->getSize() + this->contenstantId2->getSize() +
           this->contenstantId3->getSize();
}

Country *Team::getCountryPtr() { return this->countryPtr; }

Sport Team::get_sport() { return this->sport; }

int Team::getID() { return this->teamId; }

int Team::getTeamSize(int teamNum) {
    if (teamNum == 1)
        return this->contenstantId1->getSize();
    if (teamNum == 2)
        return this->contenstantId2->getSize();
    return this->contenstantId3->getSize();
}

bool Team::aleadyExists(int id) {
    return (this->contenstantId1->exist(id) || this->contenstantId2->exist(id) ||
            this->contenstantId3->exist(id));
}

void Team::addContestantToTeam(Contestant *contestant) {
    int id = contestant->get_id();
    int str = contestant->get_strength();
    Node<ContestantID *, int> *id1 = this->contenstantId1->getBiggest();
    Node<ContestantID *, int> *idSmall2 = this->contenstantId2->getSmallest();
    Node<ContestantID *, int> *idBig2 = this->contenstantId2->getBiggest();
    Node<ContestantID *, int> *id3 = this->contenstantId3->getSmallest();
    ContestantID *toAddID = new ContestantID(contestant);
    ContestantStr *toAddSTR;
    try {
        toAddSTR = new ContestantStr(toAddID, contestant);
        toAddID->setStrPtr(toAddSTR);
    } catch (std::bad_alloc &error) {
        delete toAddID;
        throw;
    }
    StrCond strCond = StrCond(str, id);
    try {
        if (id1 == nullptr || id < id1->getKey()) {
            this->contenstantId1->insert(id, toAddID);
            this->contenstantStr1->insert(strCond, toAddSTR);
            id1 = this->contenstantId1->getBiggest();
            if (this->contenstantId1->getSize() >
                this->contenstantId2->getSize() + 1) {
                //                move id1 to id2
                this->moveContestant(this->contenstantId2, this->contenstantStr2,
                                     this->contenstantId1, this->contenstantStr1, id1);
            } else if (this->contenstantId1->getSize() >
                       this->contenstantId3->getSize() + 1) {
                //                    move id2 biggest to id3 and move id1 biggest to
                //                    id2
                this->moveContestant(this->contenstantId3, this->contenstantStr3,
                                     this->contenstantId2, this->contenstantStr2,
                                     idBig2);

                this->moveContestant(this->contenstantId2, this->contenstantStr2,
                                     this->contenstantId1, this->contenstantStr1, id1);
            }
        } else if (idSmall2 == nullptr ||
                   (id > id1->getKey() && id < idBig2->getKey())) {
            this->contenstantId2->insert(id, toAddID);
            this->contenstantStr2->insert(strCond, toAddSTR);
            idSmall2 = this->contenstantId2->getSmallest();
            idBig2 = this->contenstantId2->getBiggest();
            if (this->contenstantId2->getSize() >
                this->contenstantId1->getSize() + 1) {
                //                   move id2 smallest to id1
                this->moveContestant(this->contenstantId1, this->contenstantStr1,
                                     this->contenstantId2, this->contenstantStr2,
                                     idSmall2);
            } else if (this->contenstantId2->getSize() >
                       this->contenstantId3->getSize() + 1) {
                //                  move id2 biggest to id3
                this->moveContestant(this->contenstantId3, this->contenstantStr3,
                                     this->contenstantId2, this->contenstantStr2,
                                     idBig2);
            };
        } else if (id3 == nullptr || id > idBig2->getKey()) {
            this->contenstantId3->insert(id, toAddID);
            this->contenstantStr3->insert(strCond, toAddSTR);
            id3 = this->contenstantId3->getSmallest();
            if (this->contenstantId3->getSize() >
                this->contenstantId2->getSize() + 1) {
                //                move id3 smallest to id2
                this->moveContestant(this->contenstantId2, this->contenstantStr2,
                                     this->contenstantId3, this->contenstantStr3, id3);
            } else if (this->contenstantId3->getSize() >
                       this->contenstantId1->getSize() + 1) {
                //                move id2 smallest to id1 and move id3 smallest to id2
                this->moveContestant(this->contenstantId1, this->contenstantStr1,
                                     this->contenstantId2, this->contenstantStr2,
                                     idSmall2);

                this->moveContestant(this->contenstantId2, this->contenstantStr2,
                                     this->contenstantId3, this->contenstantStr3, id3);
            }
        }
    } catch (...) {
        delete toAddID;
        delete toAddSTR;
        throw;
    }
}

void Team::removeContestantFromTeam(Contestant *contestant) {
    int id = contestant->get_id();
    int str = contestant->get_strength();
    Node<ContestantID *, int> *id1 = this->contenstantId1->getBiggest();
    Node<ContestantID *, int> *idSmall2 = this->contenstantId2->getSmallest();
    Node<ContestantID *, int> *idBig2 = this->contenstantId2->getBiggest();
    Node<ContestantID *, int> *id3 = this->contenstantId3->getSmallest();
    StrCond strCond = StrCond(str, id);
    int id1Size = this->contenstantId1->getSize();
    int id2Size = this->contenstantId2->getSize();
    int id3Size = this->contenstantId3->getSize();
    if (id <= id1->getKey()) {
        ContestantID *toDelete = *(this->contenstantId1->find(id));
        ContestantStr *toDeleteStr = toDelete->getContestantStrPtr();
        this->contenstantId1->remove(id);
        this->contenstantStr1->remove(strCond);
        id1 = this->contenstantId1->getBiggest();//why needed?
        delete toDelete;
        delete toDeleteStr;
        id1Size--;
        if (id1Size == 0) {
            if (id2Size > 0) {
                this->moveContestant(this->contenstantId1, this->contenstantStr1,
                                     this->contenstantId2, this->contenstantStr2,
                                     idSmall2);
                id2Size--;
                if (id2Size == 0 && id3Size > 0) {
                    this->moveContestant(this->contenstantId2, this->contenstantStr2,
                                         this->contenstantId3, this->contenstantStr3,
                                         id3);
                }
            }
        } else {
            if (id1Size + 1 < id2Size) {
                this->moveContestant(this->contenstantId1, this->contenstantStr1,
                                     this->contenstantId2, this->contenstantStr2,
                                     idSmall2);
            } else if (id1Size + 1 < id3Size) {
                this->moveContestant(this->contenstantId1, this->contenstantStr1,
                                     this->contenstantId2, this->contenstantStr2,
                                     idSmall2);
                this->moveContestant(this->contenstantId2, this->contenstantStr2,
                                     this->contenstantId3, this->contenstantStr3, id3);
            }
        }
    } else if (id >= idSmall2->getKey() && id <= idBig2->getKey()) {
        ContestantID *toDelete = *(this->contenstantId2->find(id));
        ContestantStr *toDeleteStr = toDelete->getContestantStrPtr();
        this->contenstantId2->remove(id);
        this->contenstantStr2->remove(strCond);
        idSmall2 = this->contenstantId2->getSmallest();
        idBig2 = this->contenstantId2->getBiggest();
        delete toDelete;
        delete toDeleteStr;
        id2Size--;
        if (id2Size == 0 && id3Size > 0) {
            this->moveContestant(this->contenstantId2, this->contenstantStr2,
                                 this->contenstantId3, this->contenstantStr3, id3);
        } else {
            if (id2Size + 1 < id1Size) {
                this->moveContestant(this->contenstantId2, this->contenstantStr2,
                                     this->contenstantId1, this->contenstantStr1, id1);
            } else if (id2Size + 1 < id3Size) {
                this->moveContestant(this->contenstantId2, this->contenstantStr2,
                                     this->contenstantId3, this->contenstantStr3, id3);
            }
        }
    } else if (id >= id3->getKey()) {
        ContestantID *toDelete = *(this->contenstantId3->find(id));
        ContestantStr *toDeleteStr = toDelete->getContestantStrPtr();
        this->contenstantId3->remove(id);
        this->contenstantStr3->remove(strCond);
        id3 = this->contenstantId3->getSmallest();
        delete toDelete;
        delete toDeleteStr;
        id3Size--;
        if (id3Size + 1 < id2Size) {
            this->moveContestant(this->contenstantId3, this->contenstantStr3,
                                 this->contenstantId2, this->contenstantStr2, idBig2);
        } else if (id3Size + 1 < id1Size) {
            this->moveContestant(this->contenstantId3, this->contenstantStr3,
                                 this->contenstantId2, this->contenstantStr2, idBig2);
            this->moveContestant(this->contenstantId2, this->contenstantStr2,
                                 this->contenstantId1, this->contenstantStr1, id1);
        }
    }
}

void Team::destoryTreeObjects() {
    deleteInOrderStr(this->contenstantStr1->getRoot());
    deleteInOrderStr(this->contenstantStr2->getRoot());
    deleteInOrderStr(this->contenstantStr3->getRoot());
    deleteInOrderID(this->contenstantId1->getRoot());
    deleteInOrderID(this->contenstantId2->getRoot());
    deleteInOrderID(this->contenstantId3->getRoot());
}

void Team::destoryTrees() {
    delete this->contenstantStr1;
    delete this->contenstantId1;
    delete this->contenstantStr2;
    delete this->contenstantId2;
    delete this->contenstantStr3;
    delete this->contenstantId3;
}

void Team::deleteInOrderStr(Node<ContestantStr *, StrCond> *node) {
    if (node == nullptr)
        return;
    this->deleteInOrderStr(node->getLeft());
    delete (node->getNodeData());
    this->deleteInOrderStr(node->getRight());
}

void Team::deleteInOrderID(Node<ContestantID *, int> *node) {
    if (node == nullptr)
        return;
    this->deleteInOrderID(node->getLeft());
    delete (node->getNodeData());
    this->deleteInOrderID(node->getRight());
}

void Team::moveContestant(AVLTree<ContestantID *, int> *idDest,
                          AVLTree<ContestantStr *, StrCond> *strDest,
                          AVLTree<ContestantID *, int> *idSrc,
                          AVLTree<ContestantStr *, StrCond> *strSrc,
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

void Team::updateContestantStr(int id, int prevStr, int str) {
    int id1 = this->contenstantId1->getBiggest()->getKey();
    int idSmall2 = this->contenstantId2->getSmallest() ? this->contenstantId2->getSmallest()->getKey() : 0;
    int idBig2 = this->contenstantId2->getBiggest() ? this->contenstantId2->getBiggest()->getKey(): 0;
    StrCond st = StrCond(prevStr, id);
    if (id <= id1) // the contestant is in the first tree
    {
        ContestantStr *strObj = *(this->contenstantStr1->find(st));
        this->contenstantStr1->remove(st);
        st = StrCond(str, id);
        this->contenstantStr1->insert(st, strObj);
    } else if ((id >= idSmall2) &&
               (id <= idBig2)) // the contestant is in the second tree
    {
        ContestantStr *strObj = *(this->contenstantStr2->find(st));
        this->contenstantStr2->remove(st);
        st = StrCond(str, id);
        this->contenstantStr2->insert(st, strObj);
    } else { // the contestant is in the third tree
        ContestantStr *strObj = *(this->contenstantStr3->find(st));
        this->contenstantStr3->remove(st);
        st = StrCond(str, id);
        this->contenstantStr3->insert(st, strObj);
    }
}

int Team::getTeamStrength() {
    if ((this->getContestantCount() == 0)||(this->getContestantCount() % 3) != 0)
        return 0;
    return this->contenstantStr1->getBiggest()->getKey() + this->contenstantStr2->getBiggest()->getKey() +
           this->contenstantStr3->getBiggest()->getKey();
}

void Team::fillArray(Node<ContestantID *, int> *ID[],
                     Node<ContestantStr *, StrCond> *Str1[],
                     Node<ContestantStr *, StrCond> *Str2[],
                     Node<ContestantStr *, StrCond> *Str3[], int size1,
                     int size2, int size3) {
    this->contenstantId1->fillArray(ID, 0);
    if (size2 != 0 || size3 != 0)
        this->contenstantId2->fillArray(ID, size1);
    if (size3 != 0)
        this->contenstantId3->fillArray(ID, size1 + size2);
    this->contenstantStr1->fillArray(Str1, 0);
    this->contenstantStr2->fillArray(Str2, 0);
    this->contenstantStr3->fillArray(Str3, 0);
}

int Team::austerity_measures() {
    int highest_score = 0;

    int str3_biggest_str = this->contenstantStr3->get_biggest()->getNodeData()->getConPtr()->get_strength();
    int str2_biggest_str = this->contenstantStr2->get_biggest()->getNodeData()->getConPtr()->get_strength();
    int str1_biggest_str = this->contenstantStr1->get_biggest()->getNodeData()->getConPtr()->get_strength();

    int str3_second_biggest_str = this->contenstantStr3->get_second_biggest()->getNodeData()->getConPtr()->get_strength();
    int str2_second_biggest_str = this->contenstantStr2->get_second_biggest()->getNodeData()->getConPtr()->get_strength();
    int str1_second_biggest_str = this->contenstantStr1->get_second_biggest()->getNodeData()->getConPtr()->get_strength();

    if(this->getContestantCount() == 6){
        int temp;
        highest_score=str1_biggest_str+str2_biggest_str+str3_biggest_str; //case1 : 1 low , 1 mid ,1 high
        temp =str2_biggest_str+str3_biggest_str+str2_second_biggest_str;  //case2: 2 low, 1 high
        highest_score = (temp > highest_score) ? temp : highest_score;
        temp =str1_biggest_str+str2_biggest_str+str2_second_biggest_str;  //case3: 2 high, 1 low
        highest_score = (temp > highest_score) ? temp : highest_score;
        temp =str1_biggest_str+str3_biggest_str+str1_second_biggest_str;  //case4: 2 mid, 1 high
        highest_score = (temp > highest_score) ? temp : highest_score;
        temp =str1_biggest_str+str3_biggest_str+str3_second_biggest_str;  //case5: 2 mid, 1 low
        highest_score = (temp > highest_score) ? temp : highest_score;
        temp =str1_biggest_str+str2_biggest_str+str1_second_biggest_str;  //case6: 2 high, 1 mid
        highest_score = (temp > highest_score) ? temp : highest_score;
        temp =str2_biggest_str+str3_biggest_str+str3_second_biggest_str;  //case7: 2 low, 1 mid
        highest_score = (temp > highest_score) ? temp : highest_score;
        return highest_score;
    }

    //Contestant count > 6

    Contestant *id1_first_big =this->contenstantId1->get_biggest()->getNodeData()->getContestantPtr();
    Contestant *id2_first_big =this->contenstantId2->get_biggest()->getNodeData()->getContestantPtr();
    Contestant *id2_second_big = this->contenstantId2->get_second_biggest()->getNodeData()->getContestantPtr();
    Contestant *id2_last =this->contenstantId2->get_smallest()->getNodeData()->getContestantPtr();
    Contestant *id2_second_last = this->contenstantId2->get_second_smallest()->getNodeData()->getContestantPtr();
    Contestant *id3_last =this->contenstantId3->get_smallest()->getNodeData()->getContestantPtr();

    int str3_biggest_id =this->contenstantStr3->get_biggest()->getNodeData()->getConPtr()->get_id();
    int str2_biggest_id =this->contenstantStr2->get_biggest()->getNodeData()->getConPtr()->get_id();
    int str1_biggest_id =this->contenstantStr1->get_biggest()->getNodeData()->getConPtr()->get_id();

    int temp1,temp2,temp3; //highest of each tree

    //case 1: 1 of each tree
    highest_score=str1_biggest_str+str2_biggest_str+str3_biggest_str;

    // case 2: 2 of the lower tree and 1 of the middle tree
    temp3 = (id3_last->get_id() == str3_biggest_id) ? str3_second_biggest_str
                                                    : str3_biggest_str;
    temp2 = (id2_last->get_id() == str2_biggest_id) ? str2_second_biggest_str
                                                    : str2_biggest_str;
    temp2 = (id3_last->get_strength() > temp2) ? id3_last->get_strength() : temp2;
    temp1 = (id2_last->get_strength() > str1_biggest_str)
            ? id2_last->get_strength()
            : str1_biggest_str;
    highest_score = ((temp3 + temp2 + temp1) > highest_score)
                    ? temp3 + temp2 + temp1
                    : highest_score;

    // case 3: 2 of the lower tree and 1 of the higher tree
    temp3 = str3_biggest_str;
    temp2 = (id2_last->get_id() == str2_biggest_id) ? str2_second_biggest_str
                                                    : str2_biggest_str;
    temp1 = (id2_last->get_strength() > str1_biggest_str)
            ? id2_last->get_strength()
            : str1_biggest_str;
    highest_score = ((temp3 + temp2 + temp1) > highest_score)
                    ? temp3 + temp2 + temp1
                    : highest_score;

    // case 4: 2 of the middle tree and 1 of the lower tree
    temp3 = (id3_last->get_id() == str3_biggest_id) ? str3_second_biggest_str
                                                    : str3_biggest_str;
    temp2 = (id3_last->get_strength() > str2_biggest_str)
            ? id3_last->get_strength()
            : str2_biggest_str;
    temp1 = str1_biggest_str;
    highest_score = ((temp3 + temp2 + temp1) > highest_score)
                    ? temp3 + temp2 + temp1
                    : highest_score;

    // case 5: 2 of the middle tree and 1 of the higher tree
    temp3 = str3_biggest_str;
    temp2 = (id1_first_big->get_strength() > str2_biggest_str)
            ? id1_first_big->get_strength()
            : str2_biggest_str;
    temp1 = (id1_first_big->get_id() == str1_biggest_id) ? str1_second_biggest_str
                                                         : str1_biggest_str;
    highest_score = ((temp3 + temp2 + temp1) > highest_score)
                    ? temp3 + temp2 + temp1
                    : highest_score;

    // case 6: 2 of the higher tree and 1 of the lower tree
    temp3 = (id2_first_big->get_strength() > str3_biggest_str)
            ? id2_first_big->get_strength()
            : str3_biggest_str;
    temp2 = (id2_first_big->get_id() == str2_biggest_id) ? str2_second_biggest_str
                                                         : str2_biggest_str;
    temp1 = str1_biggest_str;
    highest_score = ((temp3 + temp2 + temp1) > highest_score)
                    ? temp3 + temp2 + temp1
                    : highest_score;

    // case 7: 2 of the higher tree and 1 of the middle tree
    temp3 = (id2_first_big->get_strength() > str3_biggest_str)
            ? id2_first_big->get_strength()
            : str3_biggest_str;
    temp2 = (id2_first_big->get_id() == str2_biggest_id) ? str2_second_biggest_str
                                                         : str2_biggest_str;
    temp2 = (id1_first_big->get_strength() > temp2)
            ? id1_first_big->get_strength()
            : temp2;
    temp1 = (str1_biggest_id == id1_first_big->get_id()) ? str1_second_biggest_str
                                                         : str1_biggest_str;
    highest_score = ((temp3 + temp2 + temp1) > highest_score)
                    ? temp3 + temp2 + temp1
                    : highest_score;

    int str2_third_biggest_str = this->contenstantStr2->get_third_biggest()->getNodeData()->getConPtr()->get_strength();
    int str2_second_biggest_id = this->contenstantStr2->get_second_biggest()->getNodeData()->getConPtr()->get_id();

    //case 8: 3 of the lower tree
    temp3 = (id3_last->get_id() == str3_biggest_id) ? str3_second_biggest_str : str3_biggest_str;
    if ((id2_last->get_id() == str2_biggest_id && id2_second_last->get_id() == str2_second_biggest_id)
                                                  ||(id2_last->get_id() == str2_second_biggest_id && id2_second_last->get_id() == str2_biggest_id))
        temp2 = str2_third_biggest_str;
    else {
        if (id2_last->get_id() == str2_biggest_id ||
            id2_second_last->get_id() == str2_biggest_id)
            temp2 = str2_second_biggest_str;
        else
            temp2 = str2_biggest_str;
    }
    temp2 = (id3_last->get_strength() > temp2) ? id3_last->get_strength() : temp2;
    temp1 = (id2_last->get_strength() > id2_second_last->get_strength()) ? id2_last->get_strength(): id2_second_last->get_strength();
    temp1 = (str1_biggest_str > temp1) ? str1_biggest_str : temp1;
    highest_score = ((temp3 + temp2 + temp1) > highest_score) ? temp3 + temp2 + temp1 : highest_score;

    //case 9: 3 of the middle tree
    temp3 = (id3_last->get_id() == str3_biggest_id) ? str3_second_biggest_str : str3_biggest_str;
    temp2 = (str2_biggest_str > id3_last->get_strength()) ? str2_biggest_str : id3_last->get_strength();
    temp2 = (id1_first_big->get_strength() > temp2) ? id1_first_big->get_strength() : temp2;
    temp1 = (id1_first_big->get_id() == str1_biggest_id) ? str1_second_biggest_str : str1_biggest_str;
    highest_score = ((temp3 + temp2 + temp1) > highest_score) ? temp3 + temp2 + temp1 : highest_score;

    //case 10: 3 of the higher tree
    temp3 = (str3_biggest_str > id2_first_big->get_strength()) ? str3_biggest_str : id2_first_big->get_strength();
    temp3 = (id2_second_big->get_strength() > temp3) ? id2_second_big->get_strength() : temp3;
    if ((id2_first_big->get_id() == str2_biggest_id && id2_second_big->get_id() == str2_second_biggest_id)
    || (id2_first_big->get_id() == str2_second_biggest_id && id2_second_big->get_id() == str2_biggest_id))
        temp2 = str2_third_biggest_str;
    else {
        if (id2_first_big->get_id() == str2_biggest_id ||
            id2_second_big->get_id() == str2_biggest_id)
            temp2 = str2_second_biggest_str;
        else
            temp2 = str2_biggest_str;
    }
    temp2 = (id1_first_big->get_strength() > temp2) ? id1_first_big->get_strength() : temp2;
    temp1 = (id1_first_big->get_id() == str1_biggest_id) ? str1_second_biggest_str : str1_biggest_str;
    highest_score = ((temp3 + temp2 + temp1) > highest_score) ? temp3 + temp2 + temp1 : highest_score;

    return highest_score;
}

void Team::setAllTrees(Node<ContestantID *, int> *teamTotalID[],
                       int unitedStr1Size, int unitedStr2Size,
                       int unitedStr3Size,
                       Node<ContestantStr *, StrCond> *unitedStr1[],
                       Node<ContestantStr *, StrCond> *unitedStr2[],
                       Node<ContestantStr *, StrCond> *unitedStr3[]) {
    AVLTree<ContestantID *, int> *ID1 = new AVLTree<ContestantID *, int>(teamTotalID, unitedStr1Size, 0,
                                                                         unitedStr1Size - 1);
    AVLTree<ContestantID *, int> *ID2 = new AVLTree<ContestantID *, int>(teamTotalID, unitedStr2Size, unitedStr1Size,
                                                                         unitedStr1Size + unitedStr2Size - 1);
    AVLTree<ContestantID *, int>* ID3 = new AVLTree<ContestantID *,int>(teamTotalID, unitedStr3Size,
                 unitedStr1Size + unitedStr2Size,unitedStr1Size+unitedStr2Size+unitedStr3Size - 1);
    AVLTree<ContestantStr *, StrCond>* STR1 = new AVLTree<ContestantStr *,StrCond>(unitedStr1, unitedStr1Size,
                                                                                   0, unitedStr1Size - 1);
    AVLTree<ContestantStr *, StrCond>* STR2 = new AVLTree<ContestantStr *,StrCond>(unitedStr2, unitedStr2Size,
                                                                                   0, unitedStr2Size - 1);
    AVLTree<ContestantStr *, StrCond> *STR3 = new AVLTree<ContestantStr *,StrCond>(unitedStr3, unitedStr3Size,
                                                                                   0, unitedStr3Size - 1);
    destoryTrees();
    this->contenstantId1 = ID1;
    this->contenstantId2 = ID2;
    this->contenstantId3 = ID3;
    this->contenstantStr1 = STR1;
    this->contenstantStr2 = STR2;
    this->contenstantStr3 = STR3;
}
