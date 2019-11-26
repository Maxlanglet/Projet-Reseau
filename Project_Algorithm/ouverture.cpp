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
    char buf;
    while (!file.eof()) {
        //file.read(reinterpret_cast<char*>(&buf), sizeof(char));//embiguité soit buf doit etre un int ou un char je sais pas
        file.read(&buf, sizeof(char));
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
    vector<int> v2;
    int i = 0;
    int myint;
    int offset = 0;
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(&myint), sizeof(int));
        buffer.push_back((int)(bswap_32(myint)));
        i++;
        if (buffer[i-1]==0) {
            //buffer.clear();
            //buffer.push_back(1);// ajoute le 1
            offset=i-1;
            //cout << offset << endl;
        }
        if (bswap_32(myint)==1 && i>=12) {//on regarde apres les 12 premiers éléments du fichier pin car sont les autres elements
            buffer.pop_back();//enleve le 1
            break;
        }
       }
    //buffer.insert(buffer.begin(), 0);//ajoute le 0
    v2 = vector<int>(buffer.begin() + offset, buffer.end()); //probleme dans les vecteurs de taille diff 1
    return v2;
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
    buffer.pop_back(); //apparement lit 2 fois le dernier je sais pas pq du coup voir assistant
    return buffer;
}

void acquiert(int offset, ifstream &f){
    if(!f.is_open()){
        cout << "erreur, impossible d'ouvrir le fichier header" << endl;
    }
    f.seekg(offset);
    //int pos = f.tellg();
    //cout << "position : " << pos << endl;
    int var = 0;
    char octet;
    while(var < 4){
        f.read(&octet, 1);
        //cout << int(octet) <<endl;
        if(int(octet) == 26){
            read_string(&f);
            var++;
        }
        if(int(octet) == 2){
            read_int(&f);
            var++;
        }
        
    }
    //cout << "position : " << f.tellg() << endl;
    
}

string read_string(ifstream* f){
    string res = "";
    //cout << "position string : " << f->tellg() << endl;
    char size;
    f->read(&size, 1);
    //cout << "taille string : " << int(size) << endl;
    char* text = new char[int(size)];
    f->read(text, int(size));
    cout << ">" << text << endl;
    res = text;
    return res;
}

int read_int(ifstream* f){
    int res = 0;
    //cout << "position int : " << f->tellg() << endl;
    char size;
    f->read(&size,1);
    //cout << "taille int : " << int(size) << endl;
    //cout << "position int : " << f->tellg() << endl;
    int buffer;
    f-> read((char*)&buffer, int(size));
    bswap_64(buffer);
    
    cout<<"int : "<< buffer << endl;
    
    res = buffer;
    
    return res;
}
