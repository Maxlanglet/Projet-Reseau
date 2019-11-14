//
//  Score.hpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 08/11/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#ifndef Score_hpp
#define Score_hpp


#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

string Score(string sequence);
char score_Inverse(int valeur);
int comparaison_De_Sequence(ifstream &file, string sequence);

#endif /* Score_hpp */
