//
//  ouverture.hpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 17/11/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#ifndef ouverture_hpp
#define ouverture_hpp

#include "Fasta_To_Bits.hpp"

vector<char> read_psq( ifstream &file);
vector<int> header_offset(ifstream &file);
vector<int> sequence_offset(ifstream &file);
#endif /* ouverture_hpp */
