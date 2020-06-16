// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <vector>
#include "utils.h"

using namespace std;

class Route {
    public:
        /**
         @pre  El vector conte les dades d'una ruta amb el format correcte.
         @post Crea una nova ruta a partir de les dades contingudes en el vector.
        **/
        Route(const vector<string>& v);

        /**
         @pre  Cert.
         @post Retorna el codi IATA o ICAO de l'aerolinia d'aquesta ruta.
        **/
        string get_airline() const;

        /**
         @pre  Cert.
         @post Retorna la OpenFlights ID de l'aerolinia d'aquesta ruta.
        **/
        int get_airline_id() const;

        /**
         @pre  Cert.
         @post Retorna el codi IATA o ICAO de l'aeroport d'origen d'aquesta ruta.
        **/
        string get_source() const;

        /**
         @pre  Cert.
         @post Retorna la OpenFlights ID de l'aeroport d'origen d'aquesta ruta.
        **/
        int get_source_id() const;

        /**
         @pre  Cert.
         @post Retorna el codi IATA o ICAO de l'aeroport de desti d'aquesta ruta.
        **/
        string get_dest() const;

        /**
         @pre  Cert.
         @post Retorna la OpenFlights ID de l'aeroport de desti d'aquesta ruta.
        **/
        int get_dest_id() const;

        /**
         @pre  Cert.
         @post Retorna un sol string que conte tots els codis IATA dels avions d'aquesta ruta.
        **/
        string get_plane_IATAs() const;

    private:
        string a_airline;
        int a_airline_id;
        string a_source;
        int a_source_id;
        string a_dest;
        int a_dest_id;
        char a_codeshare;
        int a_n_stops;

        /// Guarda tots els codi IATA dels avions d'aquesta ruta en un sol string.
        string a_plane_IATAs;
};

#endif // ROUTE_H
