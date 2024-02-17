#include "Olympicsa1.h"



Olympics::Olympics():m_countries(),m_teams(),m_contestants(){

}

Olympics::~Olympics(){

}
	
StatusType Olympics::add_country(int countryId, int medals){
    if (countryId <= 0 || medals < 0)
        return StatusType::INVALID_INPUT;

    try {
        Country toAdd = Country(countryId, medals);
        m_countries.insert(countryId, toAdd);
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyExists &error) {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}
	
StatusType Olympics::remove_country(int countryId){
    if (countryId <= 0)
        return StatusType::INVALID_INPUT;

    try {
        Country* toRemove = m_countries.find(countryId);
        if(toRemove->get_number_of_teams() > 0 || toRemove->get_number_of_contestants() > 0 )
            return StatusType::FAILURE;
        m_countries.remove(countryId);
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
    if (teamId <= 0 || countryId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        if(!m_teams.exist(teamId) && m_countries.exist(countryId)) {
            Country *tempCountry = m_countries.find(countryId);
            Team toAdd = Team(teamId,countryId,sport,tempCountry);
            m_teams.insert(teamId,toAdd);
            tempCountry->add_team();
        }
        else{
            return StatusType::FAILURE;
        }
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyExists &error) {
        return StatusType::FAILURE;
    }
    catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_team(int teamId){
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        Team* team = m_teams.find(teamId);
        if(team->getContestantCount() != 0)
            return StatusType::FAILURE;
        team->getCountryPtr()->remove_team();
        m_teams.remove(teamId);
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}
	
StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    if (countryId <= 0 || strength < 0 || contestantId <= 0 )
        return StatusType::INVALID_INPUT;

    try {
        if(!m_contestants.exist(contestantId) && m_countries.exist(countryId)) {
            Country *tempCountry = m_countries.find(countryId);
            Contestant toAdd = Contestant(contestantId,countryId,sport,strength,tempCountry);
            m_contestants.insert(contestantId,toAdd);
            tempCountry->add_contestant();
        }
        else{
            return StatusType::FAILURE;
        }
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyExists &error) {
        return StatusType::FAILURE;
    }
    catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}
	
StatusType Olympics::remove_contestant(int contestantId){
    if (contestantId <= 0)
        return StatusType::INVALID_INPUT;

    try {
        Contestant* toRemove = m_contestants.find(contestantId);
        if( !(toRemove->is_team1_free()) || !(toRemove->is_team2_free()) || !(toRemove->is_team3_free()) ) // meaning the constesant is active in some team or teams
            return StatusType::FAILURE;
        toRemove->get_country_ptr()->remove_contestant();
        m_contestants.remove(contestantId);
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}
	
StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    if (teamId <= 0 || contestantId <= 0)
        return StatusType::INVALID_INPUT;
    try {
            Team *team = m_teams.find(teamId);
            Contestant *contestant = m_contestants.find(contestantId);
            if(contestant->teamsFull())
                return StatusType::FAILURE;
            if(team->aleadyExists(contestantId))
                return StatusType::FAILURE;
            if((contestant->get_sport()!=team->get_sport())||
                    ((contestant->get_country_ptr()->get_country_id())!=(team->getCountryPtr()->get_country_id())))
                return StatusType::FAILURE;
        team->addContestantToTeam(contestant);
        if(contestant->is_team1_free())
            contestant->join_team1(team);
        else if(contestant->is_team2_free())
            contestant->join_team2(team);
        else
            contestant->join_team3(team);
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyExists &error) {
        return StatusType::FAILURE;
    }
    catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
	return StatusType::FAILURE;
}

StatusType Olympics::update_contestant_strength(int contestantId ,int change){
	return StatusType::FAILURE;
}

output_t<int> Olympics::get_strength(int contestantId){
    if (contestantId <= 0)
        return StatusType::INVALID_INPUT;

    int contestant_strength=0;
    try {
        Contestant* tempPtr = m_contestants.find(contestantId);
        contestant_strength = tempPtr->get_strength();
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }
    return contestant_strength;
}

output_t<int> Olympics::get_medals(int countryId){
    if (countryId <= 0)
        return StatusType::INVALID_INPUT;

    int number_of_medals=0;

    try {
        Country* countryPtr = m_countries.find(countryId);
        number_of_medals=countryPtr->get_medals();
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }

	return number_of_medals;
}

output_t<int> Olympics::get_team_strength(int teamId){
	return 0;
}

StatusType Olympics::unite_teams(int teamId1,int teamId2){
	return StatusType::FAILURE;
}

StatusType Olympics::play_match(int teamId1,int teamId2){
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1==teamId2)
        return StatusType::INVALID_INPUT;

    try {
        Team* team1 = m_teams.find(teamId1);
        Team* team2 = m_teams.find(teamId2);

        if( team1->get_sport() != team2->get_sport())
            return StatusType::FAILURE;

        int team1_score = team1->getCountryPtr()->get_medals() + get_team_strength(teamId1);
        int team2_score = team2->getCountryPtr()->get_medals() + get_team_strength(teamId2);

        if( team1_score > team2_score)
            team1->getCountryPtr()->add_a_medal();
        else
            if(team1_score < team2_score)
                team2->getCountryPtr()->add_a_medal();
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> Olympics::austerity_measures(int teamId){
	return 0;
}



