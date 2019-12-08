//
//  Sequence.cpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 06/12/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#include "Sequence.hpp"

Sequence::Sequence(string adr) : Binaire(adr){
    vector<char> sequence;
    adresse = adr;
}

void Sequence::read_psq(){
    ifstream f(adresse);
    if (!f.is_open()){
        cout << " erreur ouverture fichier" << endl;
        //break;
    }
    else{
        cout << "lecture psq" << endl;
         char buf;
         while (f) {
             //f.read(reinterpret_cast<char*>(&buf), sizeof(char));//embiguité soit buf doit etre un int ou un char je sais pas
             f.read(&buf, sizeof(char));
             sequence.push_back(buf);
        }
         cout << "finis psq" <<  endl;
         f.close();
    }
}

void Sequence::get_sequence(int k, int l){
    for (int j = k; j <l-1; j++) {
        cout << score_Inverse(sequence[j]);
    }
    cout << endl;
}

vector<char> Sequence::get_sequence2(){
    return sequence;
}

string Sequence::get_adresse(){
    return adresse;
}
