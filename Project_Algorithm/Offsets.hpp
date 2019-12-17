//
//  Offsets.hpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 06/12/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#ifndef Offsets_hpp
#define Offsets_hpp

#include "Sequence.hpp"
#include "ouverture.hpp"
#ifdef __linux__
#include <byteswap.h>

#elif defined(__APPLE__)
#include <libkern/OSByteOrder.h>
#define bswap_16(x) OSSwapInt16(x)
#define bswap_32(x) OSSwapInt32(x)
#define bswap_64(x) OSSwapInt64(x)
#endif

class Offsets : public Binaire
{
public:
    void header_offset();
    void offset();
    //void get_seq_offsets();
    int get_seq_offset(int pos);
    int get_head_offset(int pos);
<<<<<<< HEAD
=======
    void print_info(ifstream* f);
>>>>>>> 16fb9d09a4afc4ee8957e3e23b9fe45f7ee87c68
    unsigned long get_size();
    Offsets(string adr);
private:
    string adresse;
    vector<int> seq_offsets;
    vector<int> head_offsets;
<<<<<<< HEAD
=======
    vector<int> info;
>>>>>>> 16fb9d09a4afc4ee8957e3e23b9fe45f7ee87c68
    //ifstream f;
};

#endif /* Offsets_hpp */
