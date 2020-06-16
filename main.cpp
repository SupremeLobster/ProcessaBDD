// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include "Flight.h"
#include "Airport.h"
#include "Airline.h"
#include "Plane.h"
#include "Route.h"
#include "utils.h"

#include <chrono>

using namespace std;
using namespace std::chrono;

#ifdef _WIN32
   #include <windows.h>
#endif // _WIN32

/**
 @pre  Cert.
 @post Retorna TRUE si 'x' es un numero o una lletra majuscula, FALSE altrament.
**/
bool isValidChar(const char& x);

/**
 @pre  Cert.
 @post Retorna una llista amb totes les paraules que hi hagues a 's', una paraula a cada posicio.
**/
list<string> sentence_to_list_of_words(const string& s);

/**
 @pre  'vr' es un vector que conte una ruta llegida del fitxer de rutes, amb el format correcte.
 @post Diu si la ruta continguda al vector 'vr' es valida o no.
**/
bool esRutaValida(const vector<string>& vr,
                  const map<int, Airport>& m_int_airports, const map<string, Airport*>& m_str_airports_IATA, const map<string, Airport*>& m_str_airports_ICAO,
                  const map<int, Airline>& m_airlines, const map<string, Plane>& m_planes);

/**
 @pre  'vv' es un vector que conte un vol llegit del fitxer de vols, amb el format correcte.
 @post Diu si el vol contingut al vector 'vv' es valid o no.
**/
bool esVolValid(const vector<string>& vv, const map<string, Airport*>& m_str_airports_IATA, const map<string, Airline*>& m_str_airlines_IATA);

/**
 @pre  Cert.
 @post Compta quantes rutes nacionals i internacionals te cada companyia aeria i ho mostra.
**/
void countRoutes(const map<int, Airport>& m_int_airports, const map<string, Airport*>& m_str_airports_IATA, const map<string, Airport*>& m_str_airports_ICAO,
                 const map<int, Airline>& m_airlines,
                 const map<string, Plane>& m_planes,
                 const list<Route>& l_routes);

/**
 @pre  Cert.
 @post Diu quin es l'avio mes utilitzat per una companyia donada a 'al_IATA'. Mostra tots els mes utilitzats en cas d'empat.
**/
void mostUsedPlane(const map<int, Airline>& m_airlines, const map<string, Plane>& m_planes, const list<Route>& l_routes, string al_IATA);

/**
 @pre  'opcio' es 1 si es vol la consulta "DEPARTURE DELAY AIRPORTS" o 2 si es vol "ARRIVAL DELAY AIRPORTS". 'n' >= 0.
 @post Mostra el llistat ordenat dels 'n' (0 per indicar tots) aeroports amb mes retards de sortida/arribada (en funcio de 'opcio') en una data determinada.
**/
void delayAirports(const map<string, Airport*>& m_str_airports_IATA, const multimap<string, Flight>& mm_flights_DATE, int n, string year, string month, string day, int opcio);

/**
 @pre  'opcio' es 1 si es vol la consulta "DEPARTURE DELAY AIRLINES" o 2 si es vol "ARRIVAL DELAY AIRLINES". 'n' >= 0.
 @post Mostra el llistat ordenat de les 'n' (0 per indicar tots) aerolinies amb mes retards de sortida/arribada (en funcio de 'opcio').
**/
void delayAirlines(const map<string, Airline*>& m_str_airlines_IATA, const multimap<string, Flight*>& mm_flights_AL, int n, int opcio);

/**
 @pre Cert.
 @post Dia amb mes retards tant de sortida com d'arribada en un subconjunt donat d'aeroports (conjunt buit per indicar tots els aeroports). En cas d'empat llista tots els dies amb retards maxims.
**/
void dayWithMoreDelays(const map<string, Airport*>& m_str_airports_IATA,
                       const multimap<string, Flight>& mm_flights_DATE, const multimap<string, Flight*>& mm_flights_AL,
                       const list<string>& l_airports_IATA);

int main() {

    //
    #ifdef _WIN32
       SetConsoleOutputCP(65001);
       SetConsoleCP(65001);
    #endif // _WIN32
    //

	string nAirports, nAirlines, nPlanes, nRoutes, nFlights, nQueries;

	cout << "Fitxer d'Aeroports: ";
	getline(cin, nAirports);

	cout << "Fitxer d'Aerolínies: ";
	getline(cin, nAirlines);

	cout << "Fitxer d'Avions: ";
	getline(cin, nPlanes);

	cout << "Fitxer de Rutes: ";
	getline(cin, nRoutes);

	cout << "Fitxer de Vols: ";
	getline(cin, nFlights);

	cout << "Fitxer de Consultes: ";
	getline(cin, nQueries);

	ifstream fAirports, fAirlines, fPlanes, fRoutes, fFlights, fQueries;

    cout << "Loading airports..." << endl;
	openFile(fAirports, nAirports);

	map<int, Airport> m_int_airports;
	map<string, Airport*> m_str_airports_IATA;
	map<string, Airport*> m_str_airports_ICAO;

    while(!fAirports.eof()) {
        vector<string> v = getNextLineAndSplitIntoTokens(fAirports);

        if(v.size() > 1) {
            Airport *aux = &m_int_airports.insert( pair<int, Airport>(stoi(v.front()), Airport(v)) ).first->second;
            if(v[4] != "\\N") m_str_airports_IATA[v[4]] = aux;
            if(v[5] != "\\N") m_str_airports_ICAO[v[5]] = aux;
        }
    }
    fAirports.close();


    cout << "Loading airlines..." << endl;
    openFile(fAirlines, nAirlines);

    map<int, Airline> m_airlines;
    map<string, Airline*> m_str_airlines_IATA;
    getNextLineAndSplitIntoTokens(fAirlines); // SKIP FIRST LINE

    while(!fAirlines.eof()) {
        vector<string> v = getNextLineAndSplitIntoTokens(fAirlines);

        if(v.size() > 1) {
            Airline *aux = &m_airlines.insert( pair<int, Airline>(stoi(v.front()), Airline(v)) ).first->second;
            if(v[3] != "") m_str_airlines_IATA[v[3]] = aux;
        }
    }
    fAirlines.close();


    cout << "Loading planes..." << endl;
    openFile(fPlanes, nPlanes);

    map<string, Plane> m_planes;
    set<string> s_repetits;

    while(!fPlanes.eof()) {
        vector<string> v = getNextLineAndSplitIntoTokens(fPlanes);

        if(v.size()>1 && v[1]!="\\N") {
            map<string, Plane>::const_iterator it_m = m_planes.find(v[1]);
            set<string>::const_iterator it_s = s_repetits.find(v[1]);

            if(it_m != m_planes.end()) {
                s_repetits.insert(v[1]);
                m_planes.erase(it_m);
            }
            else if(it_s == s_repetits.end()) {
                m_planes.insert(pair<string, Plane>(v[1], Plane(v)));
            }
        }
    }
    fPlanes.close();
    s_repetits.clear();


    cout << "Loading routes..." << endl;
    openFile(fRoutes, nRoutes);

    list<Route> l_routes;

    while(!fRoutes.eof()) {
        vector<string> v = getNextLineAndSplitIntoTokens(fRoutes);

        if(v.size()>1 && esRutaValida(v, m_int_airports, m_str_airports_IATA, m_str_airports_ICAO, m_airlines, m_planes)) {
            l_routes.push_back(Route(v));
        }
    }
    fRoutes.close();


    cout << "Loading flights..." << endl;
    openFile(fFlights, nFlights);
    multimap<string, Flight> mm_flights_DATE; // DATE IS KEY WITH FORMAT [YYYYMMDD]
    multimap<string, Flight*> mm_flights_AL; // AIRLINE'S IATA IS KEY
    multimap<string, Flight*> mm_flights_AP;  // AIRPORT'S IATA IS KEY

    getNextLineAndSplitIntoTokens(fFlights); // SKIP FIRST LINE
    while(!fFlights.eof()) {
        vector<string> v = getNextLineAndSplitIntoTokens(fFlights);

        if(v.size()>1 && esVolValid(v, m_str_airports_IATA, m_str_airlines_IATA)) {
            string date = v[0];

            if(v[1].length() == 1) date += ("0"+v[1]);
            else date += v[1];
            if(v[2].length() == 1) date += ("0"+v[2]);
            else date += v[2];

            Flight *aux = &mm_flights_DATE.insert( pair<string, Flight>(date, Flight(v))  )->second;
            mm_flights_AL.insert( pair<string, Flight*>(v[4], aux) );
            mm_flights_AP.insert( pair<string, Flight*>(v[6], aux) );
            mm_flights_AP.insert( pair<string, Flight*>(v[8], aux) );
        }
    }
    fFlights.close();




    cout << "Processing queries..." << endl;
    openFile(fQueries, nQueries);

    vector<string> v_query = getNextLineAndSplitIntoTokens(fQueries);

    while(!fQueries.eof() && v_query.size()>0) {
        cout << "--------------------------------------------------------------------------------" << endl;

        cout << "Query: " << v_query[0];
        if(v_query[0] == "COUNT ROUTES") {
            cout << endl << endl;
            countRoutes(m_int_airports, m_str_airports_IATA, m_str_airports_ICAO, m_airlines, m_planes, l_routes);
        }
        else if(v_query[0] == "MOST USED PLANE") {
            cout << "," << v_query[1] << endl << endl;
            mostUsedPlane(m_airlines, m_planes, l_routes, v_query[1]);
        }
        else if(v_query[0] == "DEPARTURE DELAY AIRPORTS") {
            cout << "," << v_query[1] << "," << v_query[2] << "," << v_query[3] << "," << v_query[4] << endl << endl;
            delayAirports(m_str_airports_IATA, mm_flights_DATE, stoi(v_query[1]), v_query[2], v_query[3], v_query[4], 1);
        }
        else if(v_query[0] == "ARRIVAL DELAY AIRPORTS") {
            cout << "," << v_query[1] << "," << v_query[2] << "," << v_query[3] << "," << v_query[4] << endl << endl;
            delayAirports(m_str_airports_IATA, mm_flights_DATE, stoi(v_query[1]), v_query[2], v_query[3], v_query[4], 2);
        }
        else if(v_query[0] == "DEPARTURE DELAY AIRLINES") {
            cout << "," << v_query[1] << endl << endl;
            delayAirlines(m_str_airlines_IATA, mm_flights_AL, stoi(v_query[1]), 1);
        }
        else if(v_query[0] == "ARRIVAL DELAY AIRLINES") {
            cout << "," << v_query[1] << endl << endl;
            delayAirlines(m_str_airlines_IATA, mm_flights_AL, stoi(v_query[1]), 2);
        }
        else if(v_query[0] == "DAY WITH MORE DELAYS") {
            list<string> l_airports_IATA;
            for(int i=1; i<int(v_query.size()); i++) {
                cout << "," << v_query[i];
                l_airports_IATA.push_back(v_query[i]);
            }
            cout << endl << endl;

            dayWithMoreDelays(m_str_airports_IATA, mm_flights_DATE, mm_flights_AP, l_airports_IATA);
        }
        else {
            cout << endl << endl << "ERROR: unknown query" << endl;
        }

        v_query = getNextLineAndSplitIntoTokens(fQueries);
    }

    fQueries.close();

	return 0;
}

void dayWithMoreDelays(const map<string, Airport*>& m_str_airports_IATA,
                       const multimap<string, Flight>& mm_flights_DATE, const multimap<string, Flight*>& mm_flights_AP,
                       const list<string>& l_airports_IATA) {

    map<string, float> m_count_delays; // LA CLAU ES UNA DATA EN FORMAT [YYYYMMDD]
    pair< multimap<string, Flight>::const_iterator, multimap<string, Flight>::const_iterator > r_ini;
    multimap<string, Flight>::const_iterator mm_f_D_it;

    // CREC QUE ES LA MANERA MES RAPIDA I EFICIENT D'INICIALITZAR
    // REPASSAR-HO
    for(mm_f_D_it=mm_flights_DATE.begin(); mm_f_D_it!=mm_flights_DATE.end(); mm_f_D_it++) { // INICIALITZAR COMPTADORS
        r_ini = mm_flights_DATE.equal_range(mm_f_D_it->first);
        m_count_delays[r_ini.first->first] = 0.0;
        mm_f_D_it = r_ini.second;
        if(mm_f_D_it == mm_flights_DATE.end()) mm_f_D_it--;
    }


    if(l_airports_IATA.size() == 0) { // EL CONJUNT DE IATAs ES BUIT
        for(mm_f_D_it=mm_flights_DATE.begin(); mm_f_D_it!=mm_flights_DATE.end(); mm_f_D_it++) { // INICIALITZAR COMPTADORS
            float delay = 0.0;
            float dept_delay = mm_f_D_it->second.get_dept_DELAY();
            float arr_delay = mm_f_D_it->second.get_arr_DELAY();

            if(dept_delay > 0.0) delay += dept_delay;
            if(arr_delay > 0.0) delay += arr_delay;

            if(delay > 0.0) m_count_delays[mm_f_D_it->first] += delay;
        }
    }
    else { // EL CONJUNT DE IATAs NO ES BUIT
        list<string>::const_iterator l_ap_IATA_it = l_airports_IATA.begin();

        while(l_ap_IATA_it != l_airports_IATA.end()) {
            if(m_str_airports_IATA.count(*l_ap_IATA_it) == 1) { // EXISTEIX AEROPORT AMB AQUEST IATA
                pair< multimap<string, Flight*>::const_iterator, multimap<string, Flight*>::const_iterator > rang;
                multimap<string, Flight*>::const_iterator mm_f_AP_it;
                rang = mm_flights_AP.equal_range(*l_ap_IATA_it);

                for(mm_f_AP_it=rang.first; mm_f_AP_it!=rang.second; mm_f_AP_it++) {
                    float delay;

                    if( mm_f_AP_it->second->es_aeroport_origen(*l_ap_IATA_it) ) delay = mm_f_AP_it->second->get_dept_DELAY();
                    else delay = mm_f_AP_it->second->get_arr_DELAY();

                    if(delay > 0.0) m_count_delays[mm_f_AP_it->second->get_date()] += delay;
                }
            }
            else { // NO EXISTEIX AEROPORT AMB AQUEST IATA
                cout << "ERROR: " << *l_ap_IATA_it << " is an unknown IATA airport code" << endl << endl;
            }

            l_ap_IATA_it++;
        }
    }

    map<string, float>::const_iterator max_it = m_count_delays.begin();
    map<string, float>::const_iterator m_c_d_it;

    for(m_c_d_it=m_count_delays.begin(); m_c_d_it!=m_count_delays.end(); m_c_d_it++) { // TROBAR EL MAXIM [TEMPORAL]
        if(m_c_d_it->second > max_it->second) max_it = m_c_d_it;
    }

    if(max_it->second != 0.0) {
        cout << "The day with more delays in the given airports has been ";
        cout << max_it->first.substr(0, 4) << '/' << max_it->first.substr(4, 2) << '/' << max_it->first.substr(6, 2) << " " << endl;
        cout << "with total departure and arrival delays = " << int(max_it->second) << endl;
    }
    else cout << "No flights, no delays." << endl;
}

void delayAirlines(const map<string, Airline*>& m_str_airlines_IATA, const multimap<string, Flight*>& mm_flights_AL, int n, int opcio) {

    map<string, float> m_count_delays;
    map<string, Airline*>::const_iterator m_str_al_it;

    for(m_str_al_it=m_str_airlines_IATA.begin(); m_str_al_it!=m_str_airlines_IATA.end(); m_str_al_it++) { // INICIALITZAR COMPTADORS
        m_count_delays[m_str_al_it->first] = 0.0;
    }

    multimap<string, Flight*>::const_iterator mm_f_AL_it;

    for(mm_f_AL_it=mm_flights_AL.begin(); mm_f_AL_it!=mm_flights_AL.end(); mm_f_AL_it++) { // FER EL RECOMPTE DE RETARDS
        float delay;

        if(opcio == 1) delay = mm_f_AL_it->second->get_dept_DELAY();
        else delay = mm_f_AL_it->second->get_arr_DELAY();

        if(delay > 0.0) m_count_delays[mm_f_AL_it->second->get_op_carrier_IATA()] += delay;
    }

    multimap<float, Airline*> mm_count_ordered;
    map<string, float>::const_iterator m_c_del_it;

    for(m_c_del_it=m_count_delays.begin(); m_c_del_it!=m_count_delays.end(); m_c_del_it++) { // ORDENAR
        if(m_c_del_it->second != 0.0) mm_count_ordered.insert( pair<float, Airline*>(m_c_del_it->second, m_str_airlines_IATA.at(m_c_del_it->first)) );
    }

    multimap<float, Airline*>::reverse_iterator mm_c_o_it;
    string tipusDelay;

    if(opcio == 1) tipusDelay = "departure";
    else tipusDelay = "arrival";

    // MOSTRAR
    if(n == 0) {
        cout << "The airlines with more " << tipusDelay << " delays are" << endl << endl;

        for(mm_c_o_it=mm_count_ordered.rbegin(); mm_c_o_it!=mm_count_ordered.rend(); mm_c_o_it++) {
            multimap<float, Airline*>::reverse_iterator it;

            cout << "Accum. " << tipusDelay << " delays: " << int(mm_c_o_it->first);
            for(it=mm_c_o_it; it->first==mm_c_o_it->first; it++) {
                cout << " - ";
                it->second->mostra();
            }
            it--;
            mm_c_o_it = it;

            cout << endl;
        }
    }
    else {
        int i = 0;
        mm_c_o_it = mm_count_ordered.rbegin();

        cout << "The " << n << " airlines with more " << tipusDelay << " delays are" << endl << endl;

        while(i<n && mm_c_o_it!=mm_count_ordered.rend()) {
            multimap<float, Airline*>::reverse_iterator it;

            cout << "Accum. " << tipusDelay << " delays: " << int(mm_c_o_it->first);
            for(it=mm_c_o_it; it->first==mm_c_o_it->first; it++) {
                cout << " - ";
                it->second->mostra();
            }
            it--;
            mm_c_o_it = it;

            cout << endl;

            mm_c_o_it++;
            i++;
        }
    }
}

void delayAirports(const map<string, Airport*>& m_str_airports_IATA, const multimap<string, Flight>& mm_flights_DATE, int n, string year, string month, string day, int opcio) {

    pair< multimap<string, Flight>::const_iterator, multimap<string, Flight>::const_iterator > rang;
    multimap<string, Flight>::const_iterator mm_f_D_it;
    map<string, float> m_count_delays;

    string format_month = month;
    string format_day = day;

    if(format_month.length() == 1) format_month = "0"+format_month;
    if(format_day.length() == 1) format_day = "0"+format_day;


    rang = mm_flights_DATE.equal_range(year+format_month+format_day);

    for(mm_f_D_it=rang.first; mm_f_D_it!=rang.second; mm_f_D_it++) { // INICIALITZAR COMPTADORS
        if(opcio == 1) m_count_delays[mm_f_D_it->second.get_origin_IATA()] = 0.0;
        else m_count_delays[mm_f_D_it->second.get_dest_IATA()] = 0.0;
    }

    for(mm_f_D_it=rang.first; mm_f_D_it!=rang.second; mm_f_D_it++) { // FER EL RECOMPTE DE RETARDS
        float delay;

        if(opcio == 1) {
            delay = mm_f_D_it->second.get_dept_DELAY();
            if(delay > 0.0) m_count_delays[mm_f_D_it->second.get_origin_IATA()] += delay;
        }
        else {
            delay = mm_f_D_it->second.get_arr_DELAY();
            if(delay > 0.0) m_count_delays[mm_f_D_it->second.get_dest_IATA()] += delay;
        }
    }

    multimap<float, Airport*> mm_count_ordered;
    map<string, float>::const_iterator m_c_del_it;

    for(m_c_del_it=m_count_delays.begin(); m_c_del_it!=m_count_delays.end(); m_c_del_it++) { // ORDENAR
        if(m_c_del_it->second != 0.0) mm_count_ordered.insert( pair<float, Airport*>(m_c_del_it->second, m_str_airports_IATA.at(m_c_del_it->first)) );
    }


    multimap<float, Airport*>::reverse_iterator mm_c_o_it;
    string tipusDelay;

    if(opcio == 1) tipusDelay = "departure";
    else tipusDelay = "arrival";

    // MOSTRAR
    if(n == 0) {
        cout << "The airports with more " << tipusDelay << " delays on " << year << '/' << format_month << '/' << format_day << " are" << endl << endl;

        for(mm_c_o_it=mm_count_ordered.rbegin(); mm_c_o_it!=mm_count_ordered.rend(); mm_c_o_it++) {
            multimap<float, Airport*>::reverse_iterator it;

            cout << "Accum. " << tipusDelay << " delays: " << mm_c_o_it->first;
            for(it=mm_c_o_it; it->first==mm_c_o_it->first; it++) {
                cout << " - ";
                it->second->mostra();
            }
            it--;
            mm_c_o_it = it;

            cout << endl;
        }
    }
    else {
        int i = 0;
        mm_c_o_it = mm_count_ordered.rbegin();

        cout << "The " << n << " airports with more " << tipusDelay << " delays on " << year << '/' << format_month << '/' << format_day << " are" << endl << endl;

        while(i<n && mm_c_o_it!=mm_count_ordered.rend()) {
            multimap<float, Airport*>::reverse_iterator it;

            cout << "Accum. " << tipusDelay << " delays: " << mm_c_o_it->first;
            for(it=mm_c_o_it; it->first==mm_c_o_it->first; it++) {
                cout << " - ";
                it->second->mostra();
            }
            it--;
            mm_c_o_it = it;

            cout << endl;

            mm_c_o_it++;
            i++;
        }
    }
}

bool esVolValid(const vector<string>& vv, const map<string, Airport*>& m_str_airports_IATA, const map<string, Airline*>& m_str_airlines_IATA) {

    return ( m_str_airlines_IATA.find(vv[4])!=m_str_airlines_IATA.end() &&
             m_str_airports_IATA.find(vv[6])!=m_str_airports_IATA.end() &&
             m_str_airports_IATA.find(vv[8])!=m_str_airports_IATA.end() );
}

void mostUsedPlane(const map<int, Airline>& m_airlines, const map<string, Plane>& m_planes, const list<Route>& l_routes, string al_IATA) {

    map<int, Airline>::const_iterator m_al_it = m_airlines.begin();

    while(m_al_it!=m_airlines.end() && m_al_it->second.get_IATA()!=al_IATA) m_al_it++;

    if(m_al_it == m_airlines.end()) cout << "ERROR: " << al_IATA << " is an unknown IATA airline code" << endl;
    else { // AIRLINE EXISTS
        list<Route>::const_iterator l_r_it = l_routes.begin();

        while(l_r_it!=l_routes.end() && l_r_it->get_airline()!=al_IATA) l_r_it++;

        if(l_r_it == l_routes.end()) cout << "ERROR: " << al_IATA << " has no routes" << endl;
        else { // AIRLINE HAS ROUTES
            map<string, int> m_p_count;
            map<string, Plane>::const_iterator m_p_it;
            list<string> l_planes;
            int maxim = 0;

            for(m_p_it=m_planes.begin(); m_p_it!=m_planes.end(); m_p_it++) { // INICIALITZAR COMPTADORS
                m_p_count[m_p_it->first] = 0;
            }

            while(l_r_it->get_airline() == al_IATA) {
                l_planes = sentence_to_list_of_words(l_r_it->get_plane_IATAs());

                while(!l_planes.empty()) {
                    map<string, int>::iterator aux_it = m_p_count.find(l_planes.front());
                    aux_it->second++;
                    if(aux_it->second > maxim) maxim = aux_it->second;

                    l_planes.pop_front();
                }

                l_r_it++;
            }

            cout << "The most used plane by \"" << m_al_it->second.get_name() << "\" is ";

            map<string, int>::iterator m_p_c_it = m_p_count.begin();

            while(m_p_c_it != m_p_count.end()) {
                if(m_p_c_it->second == maxim) cout << "\"" << m_planes.at(m_p_c_it->first).get_name() << "\"";
                m_p_c_it++;
            }
            cout << endl;
        }
    }
}

void countRoutes(const map<int, Airport>& m_int_airports, const map<string, Airport*>& m_str_airports_IATA, const map<string, Airport*>& m_str_airports_ICAO,
                 const map<int, Airline>& m_airlines,
                 const map<string, Plane>& m_planes,
                 const list<Route>& l_routes) {

    map<int, Airline>::const_iterator it_al = m_airlines.begin();
    list<Route>::const_iterator it_r = l_routes.begin();
    map< int, pair<int, int> > m_count_routes;

    while(it_al != m_airlines.end()) { // INICIALITZAR TOT A 0
        m_count_routes[it_al->first].first = 0;
        m_count_routes[it_al->first].second = 0;
        it_al++;
    }

    while(it_r != l_routes.end()) {
        int source_id = it_r->get_source_id();
        int dest_id = it_r->get_dest_id();
        int airline_id = it_r->get_airline_id();
        string country = m_airlines.find(airline_id)->second.get_country();
        map< int, pair<int, int> >::iterator it_count = m_count_routes.find(airline_id);
        map<int, Airport>::const_iterator it_source_id = m_int_airports.find(source_id);
        map<int, Airport>::const_iterator it_dest_id = m_int_airports.find(dest_id);

        if(it_source_id!=m_int_airports.end() && it_dest_id!=m_int_airports.end()) {
            if( it_source_id->second.get_country()==country && it_dest_id->second.get_country()==country ) {
                it_count->second.first++;
            }
            else it_count->second.second++;
        }
        else {
            string source = it_r->get_source();
            string dest = it_r->get_dest();
            map<string, Airport*>::const_iterator it_source_IATA = m_str_airports_IATA.find(source);
            map<string, Airport*>::const_iterator it_dest_IATA = m_str_airports_IATA.find(dest);

            if(it_source_IATA!=m_str_airports_IATA.end() or it_dest_IATA!=m_str_airports_IATA.end()) {
                if( it_source_IATA->second->get_country()==country && it_dest_IATA->second->get_country()==country ) {
                    it_count->second.first++;
                }
                else it_count->second.second++;
            }
            else {
                map<string, Airport*>::const_iterator it_source_ICAO = m_str_airports_ICAO.find(source);
                map<string, Airport*>::const_iterator it_dest_ICAO = m_str_airports_ICAO.find(dest);

                if(it_source_ICAO!=m_str_airports_ICAO.end() or it_dest_ICAO!=m_str_airports_ICAO.end()) {
                    if( it_source_ICAO->second->get_country()==country && it_dest_ICAO->second->get_country()==country ) {
                        it_count->second.first++;
                    }
                    else it_count->second.second++;
                }
            }
        }

        it_r++;
    }

    map< int, pair<int, int> >::const_iterator it_cr = m_count_routes.begin();
    map< string, pair<int, int> > m_al_count_routes;

    while(it_cr != m_count_routes.end()) {
        if(it_cr->second.first!=0 or it_cr->second.second!=0) m_al_count_routes[ m_airlines.find(it_cr->first)->second.get_name() ] = m_count_routes[it_cr->first];
        it_cr++;
    }

    map< string, pair<int, int> >::const_iterator it_al_cr = m_al_count_routes.begin();

    // CREAR UN MAPA AUXILIAR PER FER L'ORDENACIO ES MES EFICIENT I RAPID

    cout << right << setw(6) << "NAT." << setw(6) << "INTL." << "  " << left << "AIRLINE" << endl;

    while(it_al_cr != m_al_count_routes.end()) {
        cout << right << setw(6) << it_al_cr->second.first << setw(6) << it_al_cr->second.second << "  " << left << it_al_cr->first << endl;
        it_al_cr++;
    }
}

bool esRutaValida(const vector<string>& vr,
                  const map<int, Airport>& m_int_airports, const map<string, Airport*>& m_str_airports_IATA, const map<string, Airport*>& m_str_airports_ICAO,
                  const map<int, Airline>& m_airlines, const map<string, Plane>& m_planes) {

    bool valida = true;
    map<int, Airline>::const_iterator it_al;

    if(vr[1] != "\\N") it_al = m_airlines.find(stoi(vr[1]));
    else valida = false;

    if(valida) {
        if(it_al == m_airlines.end()) valida = false;
        else if(vr[0]!=it_al->second.get_IATA() && vr[0]!=it_al->second.get_ICAO()) valida = false;
        else if(vr[3] != "\\N") {
            map<int, Airport>::const_iterator it_ap_s_int = m_int_airports.find(stoi(vr[3]));

            if(it_ap_s_int == m_int_airports.end()) valida = false;
        }
        else if(vr[3] == "\\N") {
            string IATAorICAO = vr[2];
            map<string, Airport*>::const_iterator it_ap_s_str_IATA = m_str_airports_IATA.find(IATAorICAO);
            map<string, Airport*>::const_iterator it_ap_s_str_ICAO = m_str_airports_ICAO.find(IATAorICAO);

            if(it_ap_s_str_IATA==m_str_airports_IATA.end() && it_ap_s_str_ICAO==m_str_airports_ICAO.end()) valida = false;
        }
        if(valida) {
            if(vr[5] != "\\N") {
                map<int, Airport>::const_iterator it_ap_d_int = m_int_airports.find(stoi(vr[5]));

                if(it_ap_d_int == m_int_airports.end()) valida = false;
            }
            else if(vr[5] == "\\N") {
                string IATAorICAO = vr[4];
                map<string, Airport*>::const_iterator it_ap_d_str_IATA = m_str_airports_IATA.find(IATAorICAO);
                map<string, Airport*>::const_iterator it_ap_d_str_ICAO = m_str_airports_ICAO.find(IATAorICAO);

                if(it_ap_d_str_IATA==m_str_airports_IATA.end() && it_ap_d_str_ICAO==m_str_airports_ICAO.end()) valida = false;
            }
            if(valida) {
                list<string> l_planes = sentence_to_list_of_words(vr[8]);

                while(!l_planes.empty() && valida) {
                    if(m_planes.find(l_planes.front()) == m_planes.end()) valida = false;
                    else l_planes.pop_front();
                }
            }
        }
    }

    return valida;
}

list<string> sentence_to_list_of_words(const string& s) {

    list<string> res;

    for(int i=0; i<int(s.length()); i++) {
        string word = "";

        if(s[i] == ' ') i++;
        while(isValidChar(s[i]) && i<int(s.length())) {
            word += s[i];
            i++;
        }
        res.push_back(word);
    }

    return res;
}

bool isValidChar(const char& x) {

    return ( (x>='0' && x<='9') or (x>='A' && x<='Z') );
}
