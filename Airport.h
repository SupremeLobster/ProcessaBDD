// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#ifndef AIRPORT_H
#define AIRPORT_H

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Airport {
    public:
        /**
         @pre  El vector conte les dades d'un aeroport amb el format correcte.
         @post Crea un nou aeroport a partir de les dades contingudes en el vector.
        **/
        Airport(const vector<string>& v);


        /**
         @pre  Cert.
         @post Mostra el nom, la ciutat i el pais d'aquest aeroport.
        **/
        void mostra() const;

        /**
         @pre  Cert.
         @post Retorna el pais d'aquest aeroport.
        **/
        string get_country() const;

        /**
         @pre  Cert.
         @post Retorna el codi IATA d'aquest aeroport.
        **/
        string get_IATA() const;

        /**
         @pre  Cert.
         @post Retorna el codi ICAO d'aquest aeroport.
        **/
        string get_ICAO() const;

    private:
        int a_id;
        string a_name, a_city, a_country, a_IATA, a_ICAO;
        double a_lat, a_long;
        int a_alt;
        float a_timezone;
        char a_DST;
        string a_TZ, a_type, a_source;
};

#endif // AIRPORT_H
