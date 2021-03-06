// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#include "Flight.h"

Flight::Flight(const vector<string>& v) {

    _s_year = v[0];
    _s_month = v[1];
    _s_day_of_month = v[2];
    _s_day_of_week = v[3];
    _s_op_carrier_IATA = v[4];
    _i_op_carrier_fl_num = stoi(v[5]);
    _s_origin_IATA = v[6];
    _s_origin_CITY = v[7];
    _s_dest_IATA = v[8];
    _s_dest_CITY = v[9];
    if(v[10] != "") _i_CRS_dept = stoi(v[10]);
    else _i_CRS_dept = 0;
    if(v[11] != "") _i_ACTUAL_dept = stoi(v[11]);
    else _i_ACTUAL_dept = 0;
    if(v[12] != "") _f_dept_DELAY = stof(v[12]);
    else _f_dept_DELAY = 0.0;
    if(v[13] != "") _i_CRS_arr = stoi(v[13]);
    else _i_CRS_arr = 0;
    if(v[14] != "") _i_ACTUAL_arr = stoi(v[14]);
    else _i_ACTUAL_arr = 0;
    if(v[15] != "") _f_arr_DELAY = stof(v[15]);
    else _f_arr_DELAY = 0.0;
    if(v[16] == "1.00") _b_cancelled = true;
    else _b_cancelled = false;

    if(v[17] != "") _f_CRS_elapsed = stof(v[17]);
    else _f_CRS_elapsed = 0.0;
    if(v[18] != "") _f_ACTUAL_elapsed = stof(v[18]);
    else _f_ACTUAL_elapsed = 0.0;
    if(v[19] != "") _f_distance = stof(v[19]);
    else _f_distance = 0.0;
}

string Flight::get_date() const {

    string month = _s_month;
    string day = _s_day_of_month;
    if(month.length() == 1) month = "0"+month;
    if(day.length() == 1) day = "0"+day;
    return (_s_year + month + day);
}

string Flight::get_op_carrier_IATA() const {

    return _s_op_carrier_IATA;
}

string Flight::get_origin_IATA() const {

    return _s_origin_IATA;
}

string Flight::get_dest_IATA() const {

    return _s_dest_IATA;
}

float Flight::get_dept_DELAY() const {

    return _f_dept_DELAY;
}

float Flight::get_arr_DELAY() const {

    return _f_arr_DELAY;
}

bool Flight::es_aeroport_origen(const string& ap) const {

    return (ap == _s_origin_IATA);
}
