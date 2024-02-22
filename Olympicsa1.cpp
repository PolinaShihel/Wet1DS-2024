#include "Olympicsa1.h"

Olympics::Olympics() : m_countries(), m_teams(), m_contestants() {}

Olympics::~Olympics() { this->travelInOrderTeams(m_teams.getRoot()); }

void Olympics::travelInOrderTeams(Node<Team, int> *node) {
  if (node == nullptr)
    return;
  this->travelInOrderTeams(node->getLeft());
  node->getNodeDataPointer()->destoryTreeObjects();
   node->getNodeDataPointer()->destoryTrees();
  this->travelInOrderTeams(node->getRight());
}

StatusType Olympics::add_country(int countryId, int medals) {
  if (countryId <= 0 || medals < 0)
    return StatusType::INVALID_INPUT;

  try {
    Country toAdd = Country(countryId, medals);
    m_countries.insert(countryId, toAdd);
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyExists &error) {
    return StatusType::FAILURE;
  }

  return StatusType::SUCCESS;
}

StatusType Olympics::remove_country(int countryId) {
  if (countryId <= 0)
    return StatusType::INVALID_INPUT;

  try {
    Country *toRemove = m_countries.find(countryId);
    if (toRemove->get_number_of_teams() > 0 ||
        toRemove->get_number_of_contestants() > 0)
      return StatusType::FAILURE;
    m_countries.remove(countryId);
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }

  return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId, int countryId, Sport sport) {
  if (teamId <= 0 || countryId <= 0)
    return StatusType::INVALID_INPUT;
  try {
    if (!m_teams.exist(teamId) && m_countries.exist(countryId)) {
      Country *tempCountry = m_countries.find(countryId);
      Team toAdd = Team(teamId, sport, tempCountry);
      m_teams.insert(teamId, toAdd);
      tempCountry->add_team();
    } else {
      return StatusType::FAILURE;
    }
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyExists &error) {
    return StatusType::FAILURE;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
  return StatusType::SUCCESS;
}

StatusType Olympics::remove_team(int teamId) {
  if (teamId <= 0)
    return StatusType::INVALID_INPUT;
  try {
    Team *team = m_teams.find(teamId);
    if (team->getContestantCount() != 0)
      return StatusType::FAILURE;
    team->getCountryPtr()->remove_team();
    team->destoryTrees();
    m_teams.remove(teamId);
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
  return StatusType::SUCCESS;
}

StatusType Olympics::add_contestant(int contestantId, int countryId,
                                    Sport sport, int strength) {
  if (countryId <= 0 || strength < 0 || contestantId <= 0)
    return StatusType::INVALID_INPUT;

  try {
    if (!m_contestants.exist(contestantId) && m_countries.exist(countryId)) {
      Country *tempCountry = m_countries.find(countryId);
      Contestant toAdd =
          Contestant(contestantId, sport, strength, tempCountry);
      m_contestants.insert(contestantId, toAdd);
      tempCountry->add_contestant();
    } else {
      return StatusType::FAILURE;
    }
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyExists &error) {
    return StatusType::FAILURE;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
  return StatusType::SUCCESS;
}

StatusType Olympics::remove_contestant(int contestantId) {
  if (contestantId <= 0)
    return StatusType::INVALID_INPUT;

  try {
    Contestant *toRemove = m_contestants.find(contestantId);
    if (!(toRemove->is_team1_free()) || !(toRemove->is_team2_free()) ||
        !(toRemove->is_team3_free())) // meaning the constesant is active in
                                      // some team or teams
      return StatusType::FAILURE;
    toRemove->get_country_ptr()->remove_contestant();
    m_contestants.remove(contestantId);
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
  return StatusType::SUCCESS;
}

StatusType Olympics::add_contestant_to_team(int teamId, int contestantId) {
  if (teamId <= 0 || contestantId <= 0)
    return StatusType::INVALID_INPUT;
  try {
    Team *team = m_teams.find(teamId);
    Contestant *contestant = m_contestants.find(contestantId);
    if (contestant->teamsFull())
      return StatusType::FAILURE;
    if (team->aleadyExists(contestantId))
      return StatusType::FAILURE;
    if ((contestant->get_sport() != team->get_sport()) ||
        ((contestant->get_country_ptr()->get_country_id()) !=
         (team->getCountryPtr()->get_country_id())))
      return StatusType::FAILURE;
    team->addContestantToTeam(contestant);
    if (contestant->is_team1_free())
      contestant->join_team1(team);
    else if (contestant->is_team2_free())
      contestant->join_team2(team);
    else
      contestant->join_team3(team);
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyExists &error) {
    return StatusType::FAILURE;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
  return StatusType::SUCCESS;
}

StatusType Olympics::remove_contestant_from_team(int teamId, int contestantId) {
  if (teamId <= 0 || contestantId <= 0)
    return StatusType::INVALID_INPUT;
  try {
    Team *team = m_teams.find(teamId);
    Contestant *contestant = m_contestants.find(contestantId);
    if (!team->aleadyExists(contestantId))
      return StatusType::FAILURE;
    team->removeContestantFromTeam(contestant);
    contestant->freeTeam(teamId);
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
  return StatusType::SUCCESS;
}

StatusType Olympics::update_contestant_strength(int contestantId, int change) {
  if (contestantId <= 0)
    return StatusType::INVALID_INPUT;
  try {
    Contestant *contestant = this->m_contestants.find(contestantId);
    int currStrength = contestant->get_strength() + change;
    if (currStrength < 0)
      return StatusType::FAILURE;
    Team *team1 = contestant->getTeamPtr(1);
    Team *team2 = contestant->getTeamPtr(2);
    Team *team3 = contestant->getTeamPtr(3);
    if (team1)
      team1->updateContestantStr(contestantId, contestant->get_strength(),
                                 currStrength);
    if (team2)
      team2->updateContestantStr(contestantId, contestant->get_strength(),
                                 currStrength);
    if (team3)
      team3->updateContestantStr(contestantId, contestant->get_strength(),
                                 currStrength);
    contestant->setStrength(currStrength);
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
  return StatusType::SUCCESS;
}

output_t<int> Olympics::get_strength(int contestantId) {
  if (contestantId <= 0)
    return StatusType::INVALID_INPUT;

  int contestant_strength = 0;
  try {
    Contestant *tempPtr = m_contestants.find(contestantId);
    contestant_strength = tempPtr->get_strength();
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
  return contestant_strength;
}

output_t<int> Olympics::get_medals(int countryId) {
  if (countryId <= 0)
    return StatusType::INVALID_INPUT;

  int number_of_medals = 0;

  try {
    Country *countryPtr = m_countries.find(countryId);
    number_of_medals = countryPtr->get_medals();
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }

  return number_of_medals;
}

output_t<int> Olympics::get_team_strength(int teamId) {
  if (teamId <= 0)
    return StatusType::INVALID_INPUT;
  try {
    Team *team = this->m_teams.find(teamId);
    return team->getTeamStrength();
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
}

void Olympics::uniteStr(int t1size1, int t1size2, int t1size3, int t2size1,
                        int t2size2, int t2size3,
                        Node<ContestantStr *, StrCond> *team1STR1[],
                        Node<ContestantStr *, StrCond> *team1STR2[],
                        Node<ContestantStr *, StrCond> *team1STR3[],
                        Node<ContestantStr *, StrCond> *team2STR1[],
                        Node<ContestantStr *, StrCond> *team2STR2[],
                        Node<ContestantStr *, StrCond> *team2STR3[],
                        int unitedStrSize, int totalSize,
                        Node<ContestantStr *, StrCond> *unitedStr[]) {
  Node<ContestantStr *, StrCond> *selectedData;
  int *updated;
  int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, currIndex = 0, smallest;
  while ((i < t1size1) || (j < t1size2) || (k < t1size3) || (l < t2size1) ||
         (m < t2size2) || (n < t2size3)) {
    selectedData = nullptr, updated = nullptr;
    smallest = -1;
    while ((i < t1size1) &&
           (team1STR1[i]->getNodeData()->getIndex() >= unitedStrSize))
      i++;
    while ((j < t1size2) &&
           (team1STR2[j]->getNodeData()->getIndex() >= unitedStrSize))
      j++;
    while ((k < t1size3) &&
           (team1STR3[k]->getNodeData()->getIndex() >= unitedStrSize))
      k++;
    while ((l < t2size1) &&
           (team2STR1[l]->getNodeData()->getIndex() >= unitedStrSize))
      l++;
    while ((m < t2size2) &&
           (team2STR2[m]->getNodeData()->getIndex() >= unitedStrSize))
      m++;
    while ((n < t2size3) &&
           (team2STR3[n]->getNodeData()->getIndex() >= unitedStrSize))
      n++;
    if ((i < t1size1) &&
        ((smallest == -1) || (team1STR1[i]->getKey() < smallest))) {
      smallest = team1STR1[i]->getKey();
      selectedData = team1STR1[i];
      updated = &i;
    }
    if ((j < t1size2) &&
        ((smallest == -1) || (team1STR2[j]->getKey() < smallest))) {
      smallest = team1STR2[j]->getKey();
      selectedData = team1STR2[j];
      updated = &j;
    }
    if ((k < t1size3) &&
        ((smallest == -1) || (team1STR3[k]->getKey() < smallest))) {
      smallest = team1STR3[k]->getKey();
      selectedData = team1STR3[k];
      updated = &k;
    }
    if ((l < t2size1) &&
        ((smallest == -1) || (team2STR1[l]->getKey() < smallest))) {
      smallest = team2STR1[l]->getKey();
      selectedData = team2STR1[l];
      updated = &l;
    }
    if ((m < t2size2) &&
        ((smallest == -1) || (team2STR2[m]->getKey() < smallest))) {
      smallest = team2STR2[m]->getKey();
      selectedData = team2STR2[m];
      updated = &m;
    }
    if ((n < t2size3) &&
        ((smallest == -1) || (team2STR3[n]->getKey() < smallest))) {
      smallest = team2STR3[n]->getKey();
      selectedData = team2STR3[n];
      updated = &n;
    }
    if(selectedData == nullptr)
        break;
    unitedStr[currIndex++] = selectedData;
    selectedData->getNodeData()->setIndex(totalSize + 10);
    (*updated)++;
  }
}

StatusType Olympics::unite_teams(int teamId1, int teamId2) {
  if ((teamId1 <= 0) || (teamId2 <= 0) || (teamId1 == teamId2))
    return StatusType::INVALID_INPUT;
  try {
    Team *team1 = m_teams.find(teamId1);
    Team *team2 = m_teams.find(teamId2);
    if (((team1->getCountryPtr()->get_country_id()) !=
         (team2->getCountryPtr()->get_country_id())) ||
        (team1->get_sport() != team2->get_sport()))
      return StatusType::FAILURE;
    int t1size1 = team1->getTeamSize(1);
    int t1size2 = team1->getTeamSize(2);
    int t1size3 = team1->getTeamSize(3);
    int t2size1 = team2->getTeamSize(1);
    int t2size2 = team2->getTeamSize(2);
    int t2size3 = team2->getTeamSize(3);
    int totalSize = t1size1 + t1size2 + t1size3 + t2size1 + t2size2 + t2size3;
    Node<ContestantID *, int> *team1ID[t1size1 + t1size2 + t1size3];
    Node<ContestantStr *, StrCond> *team1STR1[t1size1];
    Node<ContestantStr *, StrCond> *team1STR2[t1size2];
    Node<ContestantStr *, StrCond> *team1STR3[t1size3];
    Node<ContestantID *, int> *team2ID[t2size1 + t2size2 + t2size3];
    Node<ContestantStr *, StrCond> *team2STR1[t2size1];
    Node<ContestantStr *, StrCond> *team2STR2[t2size2];
    Node<ContestantStr *, StrCond> *team2STR3[t2size3];

    team1->fillArray(team1ID, team1STR1, team1STR2, team1STR3, t1size1, t1size2,
                     t1size3);
    team2->fillArray(team2ID, team2STR1, team2STR2, team2STR3, t2size1, t2size2,
                     t2size3);
    for(int i = 0; i< t2size1 + t2size2 + t2size3; i++)
        team2ID[i]->getNodeData()->getContestantPtr()->uniteTeams(team2, team1);
    Node<ContestantID *, int> *teamTotalID[totalSize];
    int indexT1 = 0, indexT2 = 0, duplicates = 0, currIndex = 0;
    while ((indexT1 < t1size1 + t1size2 + t1size3) ||
           (indexT2 < t2size1 + t2size2 + t2size3)) {
      if ((indexT2 >= t2size1 + t2size2 + t2size3) ||
          ((indexT1 < t1size1 + t1size2 + t1size3) &&
           (team1ID[indexT1]->getKey()) < (team2ID[indexT2]->getKey())))
        teamTotalID[currIndex++] = team1ID[indexT1++];
      else if ((indexT1 >= t1size1 + t1size2 + t1size3) ||
               ((indexT2 < t2size1 + t2size2 + t2size3) &&
                (team1ID[indexT1]->getKey()) > (team2ID[indexT2]->getKey())))
        teamTotalID[currIndex++] = team2ID[indexT2++];
      else // they are the same contestant
      {
        teamTotalID[currIndex++] = team1ID[indexT1++];
        duplicates++;
        indexT2++;
      }
      teamTotalID[currIndex - 1]
          ->getNodeData()
          ->getContestantStrPtr()
          ->setIndex(currIndex - 1);
    }
    int leftOver = (totalSize - duplicates) % 3;
    int unitedStr1Size = (totalSize - duplicates) / 3;
    int unitedStr2Size = unitedStr1Size;
    int unitedStr3Size = unitedStr1Size;
    if (leftOver >= 1) {
      unitedStr1Size++;
      if (leftOver == 2)
        unitedStr2Size++;
    }
    Node<ContestantStr *, StrCond> *unitedStr1[unitedStr1Size];
    Node<ContestantStr *, StrCond> *unitedStr2[unitedStr2Size];
    Node<ContestantStr *, StrCond> *unitedStr3[unitedStr3Size];
    uniteStr(t1size1, t1size2, t1size3, t2size1, t2size2, t2size3, team1STR1,
             team1STR2, team1STR3, team2STR1, team2STR2, team2STR3,
             unitedStr1Size, totalSize, unitedStr1);
    uniteStr(t1size1, t1size2, t1size3, t2size1, t2size2, t2size3, team1STR1,
             team1STR2, team1STR3, team2STR1, team2STR2, team2STR3,
             unitedStr1Size + unitedStr2Size, totalSize, unitedStr2);
    uniteStr(t1size1, t1size2, t1size3, t2size1, t2size2, t2size3, team1STR1,
             team1STR2, team1STR3, team2STR1, team2STR2, team2STR3,
             unitedStr1Size + unitedStr2Size + unitedStr3Size, totalSize,
             unitedStr3);

    team1->setAllTrees(teamTotalID, unitedStr1Size, unitedStr2Size,unitedStr3Size, unitedStr1, unitedStr2, unitedStr3);
    team2->destoryTrees();
    m_teams.remove(teamId2);
    team1->getCountryPtr()->remove_team();
  }
  catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
  return StatusType::SUCCESS;
}

StatusType Olympics::play_match(int teamId1, int teamId2) {
  if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
    return StatusType::INVALID_INPUT;

  try {
    Team *team1 = m_teams.find(teamId1);
    Team *team2 = m_teams.find(teamId2);

    if (team1->get_sport() != team2->get_sport())
      return StatusType::FAILURE;

    int team1_score =
        team1->getCountryPtr()->get_medals() + team1->getTeamStrength();
    int team2_score =
        team2->getCountryPtr()->get_medals() + team2->getTeamStrength();

    if (team1_score > team2_score)
      team1->getCountryPtr()->add_a_medal();
    else if (team1_score < team2_score)
      team2->getCountryPtr()->add_a_medal();
  } catch (std::bad_alloc &error) {
    return StatusType::ALLOCATION_ERROR;
  } catch (KeyNotFound &error) {
    return StatusType::FAILURE;
  }
  return StatusType::SUCCESS;
}

output_t<int> Olympics::austerity_measures(int teamId) {
  if (teamId <= 0)
    return StatusType::INVALID_INPUT;

  int highest_strength = 0;

    try {
        Team *team = this->m_teams.find(teamId);
        if(team->getContestantCount() < 3)
            return StatusType::FAILURE;
        if (team->getContestantCount() == 3 || (team->getContestantCount() % 3) != 0 )
            return 0;
        highest_strength= team->austerity_measures();
    }
        catch (std::bad_alloc &error) {
            return StatusType::ALLOCATION_ERROR;
        }
        catch (KeyNotFound &error) {
            return StatusType::FAILURE;
        }
        return highest_strength;
}
