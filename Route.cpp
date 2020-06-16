// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#include "Route.h"

Route::Route(const vector<string>& v) {

    vector<string>::const_iterator it = v.begin();

    a_airline = *it; it++;
    if(*it != "\\N") a_airline_id = stoi(*it);
    else a_airline_id = -1;
    it++;
    a_source = *it; it++;
    if(*it != "\\N") a_source_id = stoi(*it);
    else a_source_id = -1;
    it++;
    a_dest = *it; it++;
    if(*it != "\\N") a_dest_id = stoi(*it);
    else a_dest_id = -1;
    it++;
    a_codeshare = (*it)[0]; it++;
    if(*it != "\\N") a_n_stops = stoi(*it);
    else a_n_stops = -1;
    it++;
    a_plane_IATAs = *it; it++;
}

string Route::get_airline() const {

    return a_airline;
}

int Route::get_airline_id() const {

    return a_airline_id;
}

string Route::get_source() const {

    return a_source;
}

int Route::get_source_id() const {

    return a_source_id;
}

string Route::get_dest() const {

    return a_dest;
}

int Route::get_dest_id() const {

    return a_dest_id;
}

string Route::get_plane_IATAs() const {

    return a_plane_IATAs;
}
