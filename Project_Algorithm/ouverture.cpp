//
//  ouverture.cpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 17/11/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#include "ouverture.hpp"

//using std::ifstream;
//using std::ofstream;
using namespace std;

char* read_psq( ifstream &file, int j){
    char* buffer = new char[j];
    file.read(buffer, j);  // lit 100 bytes
    return buffer;
}
/*
VA TOUJOURS AVEC UN:
ifstream file;
file.open ("stuff.bin", ios::binary );
char* buffer = new char[100];
file.read(buffer, 100);  // lit 100 bytes
cout << (int)(buffer[0]) << endl;  a iterer
*/

//TODO pin offset
