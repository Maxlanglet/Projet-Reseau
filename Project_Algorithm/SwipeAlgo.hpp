//
//  SwipeAlgo.hpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 03/12/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#ifndef SwipeAlgo_hpp
#define SwipeAlgo_hpp

#include "header.h"

class swipe{
public:
    //void lireBlosum(const char blosum);
    void get_pos(char prot);
    swipe();
    void Algo();
private:
    
};
int get_pos(char prot);
void swipe(string fasta, vector<char> psq, int offset1, int offset2);


#endif /* SwipeAlgo_hpp */
