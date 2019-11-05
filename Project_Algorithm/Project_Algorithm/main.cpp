//
//  main.cpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 01/11/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
    /*
    if(argc<=1){
        cout << "Argument demandé :" << argv[0]<<" [fichier] "<<endl;
        return 1;
    }
    */
    
    //ifstream input(argv[1]);
    ifstream input("/Users/langletmaxime/Desktop/P4/C++/swipe/P00533.fasta");
    if(input){
        /*
        Style de format FASTA :
        >Rosetta_Example_1
        THERECANBENOSPACE
        >Rosetta_Example_2
        THERECANBESEVERAL
        LINESBUTTHEYALLMUST
        BECONCATENATED
        */
        string ligne;
        while(getline(input, ligne)){
            cout<<ligne<<endl;
        }
    }
    else{
        cout << "Erreur dans l'ouverture du fichier"<<endl;
        return 2;
    }
    return 0;
}
