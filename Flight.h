// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Flight {
    public:
        /**
         @pre  El vector conte les dades d'un vol amb el format correcte.
         @post Crea un nou vol a partir de les dades contingudes en el vector.
        **/
        Flight(const vector<string>& v);


        /**
         @pre  Cert.
         @post Retorna la data d'aquest vol en format [AAAAMMDD].
        **/
        string get_date() const;

        /**
         @pre  Cert.
         @post Retrona el codi IATA de la aerolinia d'aquest vol.
        **/
        string get_op_carrier_IATA() const;

        /**
         @pre  Cert.
         @post Retorna el codi IATA de l'aeroport d'origen d'aquest vol.
        **/
        string get_origin_IATA() const;

        /**
         @pre  Cert.
         @post Retorna el codi IATA de l'aeroport de desti d'aquest vol.
        **/
        string get_dest_IATA() const;

        /**
         @pre  Cert.
         @post Retorna el retard de sortida d'aquest vol.
        **/
        float get_dept_DELAY() const;

        /**
         @pre  Cert.
         @post Retorna el retard d'arribada d'aquest vol.
        **/
        float get_arr_DELAY() const;

        /**
         @pre  'ap' es el codi IATA d'un aeroport.
         @post Diu si 'ap' es l'aeroport d'origen d'aquest vol.
        **/
        bool es_aeroport_origen(const string& ap) const;

    private:
        string _s_year, _s_month, _s_day_of_month, _s_day_of_week, _s_op_carrier_IATA;
        int _i_op_carrier_fl_num;
        string _s_origin_IATA, _s_origin_CITY, _s_dest_IATA, _s_dest_CITY;
        int _i_CRS_dept, _i_ACTUAL_dept, _i_CRS_arr, _i_ACTUAL_arr;
        float _f_dept_DELAY, _f_arr_DELAY;
        bool _b_cancelled;
        float _f_CRS_elapsed, _f_ACTUAL_elapsed, _f_distance;
};

#endif // FLIGHT_H
