#ifndef HEADER_NAME_H
#define HEADER_NAME_H

//#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <byteswap.h>
//using std::string;
using namespace std;

void acquiert(int offset, string fichier);
string read_string(ifstream* f);
int read_int(ifstream* f);

#endif 
