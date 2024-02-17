#include "Olympicsa1.h"



Olympics::Olympics(){

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
	return StatusType::FAILURE;
}

StatusType Olympics::remove_team(int teamId){
	return StatusType::FAILURE;
}
	
StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    if (countryId <= 0 || strength < 0 || contestantId <= 0 )
        return StatusType::INVALID_INPUT;

    if(!m_countries.exist(countryId) ) // if the country doesn't exist
        return StatusType::FAILURE;

    try {
        Contestant toAdd = Contestant(contestantId, countryId, sport, strength,m_countries.find(countryId));
        m_contestants.insert(contestantId, toAdd);
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (KeyExists &error) {
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
	return StatusType::FAILURE;
}

StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
	return StatusType::FAILURE;
}

StatusType Olympics::update_contestant_strength(int contestantId ,int change){
	return StatusType::FAILURE;
}

output_t<int> Olympics::get_strength(int contestantId){
	return 0;
}

output_t<int> Olympics::get_medals(int countryId){
	return 0;
}

output_t<int> Olympics::get_team_strength(int teamId){
	return 0;
}

StatusType Olympics::unite_teams(int teamId1,int teamId2){
	return StatusType::FAILURE;
}

StatusType Olympics::play_match(int teamId1,int teamId2){
	return StatusType::FAILURE;
}

output_t<int> Olympics::austerity_measures(int teamId){
	return 0;
}



