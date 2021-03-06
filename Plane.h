// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <vector>

using namespace std;

class Plane {
    public:
        /**
         @pre  El vector conte les dades d'un avio amb el format correcte.
         @post Crea un nou avio a partir de les dades contingudes en el vector.
        **/
        Plane(const vector<string>& v);


        /**
         @pre  Cert.
         @post Retorna el nom d'aquest avio.
        **/
        string get_name() const;

    private:
        string a_name, a_IATA, a_ICAO;
};

#endif // PLANE_H
