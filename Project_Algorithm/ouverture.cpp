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

string toBin(int dec){
    int bin;
    string res;
    while(dec != 0){
        bin = dec%2;
        res = to_string(bin)+res;
        dec=dec/2;
    }
    return res;
}

