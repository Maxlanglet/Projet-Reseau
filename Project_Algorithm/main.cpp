//
//  main.cpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 01/11/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#include "Fasta_To_Bits.hpp"
#include "Score.hpp"
#include "Bits_To_Text.hpp"
#include "ouverture.hpp"


int main(int argc, const char * argv[]) {
    /*
    if(argc<=1){
        cout << "Argument demandé :" << argv[0]<<" [fichier] "<<endl;
        return 1;
    }
    */
    
    //ifstream input(argv[1]);
    string bits;
    ifstream input("/Users/langletmaxime/Desktop/P4/C++/swipe/P00533.fasta");
    ifstream file("/Users/langletmaxime/Desktop/P4/C++/swipe/uniprot_sprot.fasta.psq");
    char* buffer = read_psq(file, 500);
    for (int i=0; i<500; i++) {
        cout << score_Inverse(buffer[i]);
    }
    //bits = Fasta_To_Bits(input);
    //cout << Bits_To_Text(bits) << endl;
    //cout << comparaison_De_Sequence(dna, bits) << endl;
    /*
    int version, type1, type2, type3, type4, title_lenght;
    string test = "a";
    
    if(argc != 2){
        cout << "argument incorrect" << endl;
        return EXIT_FAILURE;
    }
    
    
    string fichier = argv[1];
    
    ifstream f(fichier, ios::in | ios::binary);
    
    if(!f.is_open()){
        cout << "erreur, impossible d'ouvrir le fichier" << endl;
    }
    else {
        
        f.read ((char *)&version, sizeof(int));
        f.read ((char *)&type1, 8);
        //f.read ((char *)&type2, 8);
        //f.read ((char *)&type3, 8);
        //f.read ((char *)&type4, 8);
        //f.read ((char *)&title_lenght, 1);
        
        for (i = 0; i < 6; i++){
            f.read ((char *)&t1[i], sizeof(int));
     }
    }
    f.close();
    
    
    
    cout << "version=" << version << endl
    << "type(pb)=" << type1  << endl
    << "longueur du titre= " << title_lenght << endl;
    //<< "mot= " << mot << endl;
    //cout << "int size " << sizeof(a) << endl;
    //cout << "double size " << sizeof(b) << endl;
    
    for (i = 0; i < 6; i++){
        cout << t1 [i] << endl;
    }
    
    cout << "version "<< toBin(version) <<endl;
    cout << "type1 "<< toBin(type1) << endl
    << "type2 "<< toBin(type2) << endl
    << "type3 "<< toBin(type3) << endl
    << "type4 "<< toBin(type1) << endl;
    //cout << "longeur titre "<< toBin(title_lenght) <<endl;
    
    */
    return 0;
}
