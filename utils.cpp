// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "utils.h"

using namespace std;

void openFile(ifstream &f, const string &filename) {

    f.open(filename.c_str());

    if (f.fail()) {
        cerr << "Error: unable to open file " << filename << endl;
        exit(-1);
    }
}

vector<string> getNextLineAndSplitIntoTokens(istream &str) {

    vector<string> result;
    string line;
    getline(str, line);

    stringstream lineStream(line);
    string cell, rest, empty;

    while(getline(lineStream, cell, ',')) {
        if(cell.front()=='"' && cell.back()!='"') { // Found quoted string with commas inside
            getline(lineStream, rest, '"'); // Read rest of string after first comma
            cell += rest += '"';
            getline(lineStream, empty, ','); // Skip comma after string
        }

        // Remove quotes if any
        if(cell.front() == '"') { // invariant: cell.back() == '"'
          cell = cell.substr(1, cell.size()-2);
        }

        result.push_back(cell);
    }

    // This checks for a trailing comma with no data after it
    if(!lineStream && cell.empty()) {
        // If there was a trailing comma then add an empty element
        result.emplace_back("");
    }

    return result;
}

