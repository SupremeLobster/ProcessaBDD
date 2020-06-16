// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#include "Airline.h"

Airline::Airline(const vector<string>& v) {

    vector<string>::const_iterator it = v.begin();

    a_id = stoi(*it); it++;
    a_name = *it; it++;
    a_alias = *it; it++;
    a_IATA = *it; it++;
    a_ICAO = *it; it++;
    a_callsign = *it; it++;
    a_country = *it; it++;
    a_active = (*it)[0]; it++;
}

void Airline::mostra() const {

    cout << a_name << ", " << a_country;
}

string Airline::get_name() const {

    return a_name;
}

string Airline::get_country() const {

    return a_country;
}

string Airline::get_IATA() const {

    return a_IATA;
}

string Airline::get_ICAO() const {

    return a_ICAO;
}
