// Marti Mas Fullana
// Usuari u1956231
// Sessio 4

#ifndef SOLUCIO_UTILS_H
#define SOLUCIO_UTILS_H

#include <vector>

using namespace std;

/**
 @pre  Cert.
 @post Opens and attaches file  filename  to stream  f
**/
void openFile(ifstream &f, const string &filename);

/**
 @pre  str  is a stream in CSV format
 @post reads and returns the fields in the first line of  str  removing quotes if any
**/
vector<string> getNextLineAndSplitIntoTokens(istream &str);

#endif //SOLUCIO_UTILS_H
