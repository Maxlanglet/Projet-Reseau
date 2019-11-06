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
        Qui donnera au final :
         Rosetta_Example_1 : THERECANBENOSPACE
         Rosetta_Example_2 : THERECANBESEVERALLINESBUTTHEYALLMUSTBECONCATENATED
         
         En gros ce que fait le code ci-dessous, c'est qu'il regarde prend le nom et ajoute les lignes de manières consécutives plutot que 80 caracteres par 80 caracteres, ce qui est mieux je crois. Ensuite il print le nom et le contenu.
        */
        string ligne, nom, contenu;
        while(getline(input, ligne)){
            if(ligne.empty() || ligne[0]=='>'){
                if(!nom.empty()){
                    cout << nom << ":" << contenu << endl;
                    nom.clear();
                }
                if(!ligne.empty()){
                    nom=ligne.substr(1); //On enleve le ">" et on retient le nom
                }
                contenu.clear();
            }
            else if(!nom.empty()){
                if(ligne.find(' ') != string::npos){
                    contenu.clear();
                    nom.clear();
                }
                else{
                    contenu += ligne;
                }
            }
        }
        if(!nom.empty()){
            cout << nom << ":" << contenu << endl;
        }
    }
    else{
        cout << "Erreur dans l'ouverture du fichier"<<endl;
        return 2;
    }
    return 0;
}
