//
//  ouverture.cpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 17/11/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#include "ouverture.hpp"
#ifdef __linux__
#include <byteswap.h>
#elif defined(__APPLE__)
#include <libkern/OSByteOrder.h>
#define bswap_16(x) OSSwapInt16(x)
#define bswap_32(x) OSSwapInt32(x)
#define bswap_64(x) OSSwapInt64(x)
#endif

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

vector<int> header_offset(ifstream &file){
    vector<int> buffer;
    int i = 0;
    int myint;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(&myint), sizeof(int));
        buffer.push_back((int)(bswap_32(myint)));
        i++;
        if (bswap_32(myint)==1 && i>=12) {
            buffer.pop_back();//enleve le 1
            break;
        }
       }
    /*
    for (int j=0; j<i; j++) {
        cout << (int)(buffer[j]) << endl;
    }
     */
    return buffer;
}

vector<int> sequence_offset(ifstream &file){
    vector<int> buffer;
    int i = 0;
    int myint;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(&myint), sizeof(int));
        buffer.push_back((int)(bswap_32(myint)));
        i++;
        if (buffer[i-1]==1) {
            buffer.clear();
            //buffer.push_back(1);// ajoute le 1
        }
       }
    buffer.insert(buffer.begin(), 1);//ajoute le 1
    return buffer;
}
