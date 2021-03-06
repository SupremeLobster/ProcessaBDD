// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#ifndef AIRLINE_H
#define AIRLINE_H

#include <iostream>
#include <vector>

using namespace std;

class Airline {
    public:
        /**
         @pre  El vector conte les dades d'una aerolinia amb el format correcte.
         @post Crea una nova aerolinia a partir de les dades contingudes en el vector.
        **/
        Airline(const vector<string>& v);


        /**
         @pre  Cert.
         @post Mostra el nom i el pais d'aquesta aerolinia.
        **/
        void mostra() const;

        /**
         @pre  Cert.
         @post Retorna el nom d'aquesta aerolinia.
        **/
        string get_name() const;

        /**
         @pre  Cert.
         @post Retorna el pais d'aquesta aerolinia.
        **/
        string get_country() const;

        /**
         @pre  Cert.
         @post Retorna el codi IATA d'aquesta aerolinia.
        **/
        string get_IATA() const;

        /**
         @pre  Cert.
         @post Retorna el codi ICAO d'aquesta aerolinia.
        **/
        string get_ICAO() const;

    private:
        int a_id;
        string a_name, a_alias, a_IATA, a_ICAO, a_callsign, a_country;
        char a_active;
};

#endif // AIRLINE_H
