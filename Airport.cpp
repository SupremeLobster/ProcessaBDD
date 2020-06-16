// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#include "Airport.h"

Airport::Airport(const vector<string>& v) {

    vector<string>::const_iterator it = v.begin();

    a_id = stoi(*it); it++;
    a_name = *it; it++;
    a_city = *it; it++;
    a_country = *it; it++;
    a_IATA = *it; it++;
    a_ICAO = *it; it++;
    if(*it != "\\N") a_lat = stod(*it);
    else a_lat = -1;
    it++;
    if(*it != "\\N") a_long = stod(*it);
    else a_long = -1;
    it++;
    if(*it != "\\N") a_alt = stoi(*it);
    else a_alt = -1;
    it++;
    if(*it != "\\N") a_timezone = stof(*it);
    else a_timezone = -1;
    it++;
    if(*it != "\\N") a_DST = (*it)[0];
    else a_DST = '\0';
    it++;
    a_TZ = *it; it++;
    a_type = *it; it++;
    a_source = *it; it++;
}

void Airport::mostra() const {

    cout << a_name << ", " << a_city << ", " << a_country;
}

string Airport::get_country() const {

    return a_country;
}

string Airport::get_IATA() const {

    return a_IATA;
}

string Airport::get_ICAO() const {

    return a_ICAO;
}
