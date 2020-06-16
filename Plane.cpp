// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#include "Plane.h"

Plane::Plane(const vector<string>& v) {

    vector<string>::const_iterator it = v.begin();

    a_name = *it; it++;
    a_IATA = *it; it++;
    a_ICAO = *it; it++;
}

string Plane::get_name() const {

    return a_name;
}
