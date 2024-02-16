//
// Created by pshih on 15/02/2024.
//

#ifndef WET1_WINTER2024_COUNTRY_H
#define WET1_WINTER2024_COUNTRY_H

class Country {
private:
    int countryId;
    int medals;
    int teamsCounter;
    int contestantsCounter;
public:
    Country(int countryId, int medals);
    ~Country() = default;
    Country(const Country &toCopy) = default;
    int get_country_id() const;
    int get_medals();
    void add_contestant();
    void add_team();
    void remove_contestant();
    void remove_team();

};


#endif //WET1_WINTER2024_COUNTRY_H
