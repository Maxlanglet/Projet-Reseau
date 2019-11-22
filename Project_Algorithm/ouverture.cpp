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

using namespace std;

vector<char> read_psq( ifstream &file){
    vector<char> buffer;
    int buf;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(&buf), sizeof(char));//embiguité soit buf doit etre un int ou un char je sais pas
        buffer.push_back(buf);
    }
    return buffer;
}
/*
char* read_psq( ifstream &file, int j){ //code initial de read_psq je le garde juste au cas ou
    char* buffer = new char[j];
    file.read(buffer, j);  // lit 100 bytes
    return buffer;
}
*/
vector<int> header_offset(ifstream &file){
    vector<int> buffer;
    int i = 0;
    int myint;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(&myint), sizeof(int));
        buffer.push_back((int)(bswap_32(myint)));
        i++;
        if (bswap_32(myint)==1 && i>=12) {//on regarde apres les 12 premiers éléments du fichier pin car sont les autres elements
            buffer.pop_back();//enleve le 1
            break;
        }
       }
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
