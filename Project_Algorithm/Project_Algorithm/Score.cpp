//
//  Score.cpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 08/11/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#include "Score.hpp"

int comparaison_De_Sequence(ifstream &file, string sequence){
    if(file){
        char lettre2;
        int i = 0, k=0, l=0;
        string bits, test1, test2;
        do{
            file.get(lettre2);
            bits.push_back(lettre2);
        }while(!file.eof());
        /*
        for(i = 0; i<sequence.size();i++){
            cout << bits[i] << endl;
            cout << lettre2 << endl;
        }
         */
        while(i<bits.size()-sequence.size()){
            for(int j =k; j<sequence.size()+k;j++){
                test1.push_back(bits[j]);
            }
            for(int j=0;j<sequence.size();j++){
                if(test1[j]!=sequence[j]){
                    test1 = "";
                    l=0;
                    break;
                }
                else{
                    l++;
                    if(l==sequence.size()){
                        cout << "Comparaison trouvée" << endl;
                        break;
                    }
                }
            }
            i++;
        }
    }
    else{
        cout << "Fichier pas ouvert" << endl;
        return 1;
    }
    return 0;
}
//Pas sur de si c'est juste ca mais bon au cas ou

int score(string sequence){//lire séquence et assigner score pour chaque lettre donc faire binaire en lettre
    int i=0, score = 0;
    char lettre = '\0';
    for(i=0;i<sequence.size();i++){
        lettre = sequence[i];
        if(lettre == 'A'){
            score += 1;
        }
        if(lettre == 'B'){
            score += 2;
        }
        if(lettre == 'C'){
            score += 3;
        }
        if(lettre == 'D'){
            score += 4;
        }
        if(lettre == 'E'){
            score += 5;
        }
        if(lettre == 'F'){
            score += 6;
        }
        if(lettre == 'G'){
            score += 7;
        }
        if(lettre == 'H'){
            score += 8;
        }
        if(lettre == 'I'){
            score += 9;
        }
        if(lettre == 'J'){
            score += 27;
        }
        if(lettre == 'K'){
            score += 10;
        }
        if(lettre == 'L'){
            score += 11;
        }
        if(lettre == 'M'){
            score += 12;
        }
        if(lettre == 'N'){
            score += 13;
        }
        if(lettre == 'O'){
            score += 26;
        }
        if(lettre == 'P'){
            score += 14;
        }
        if(lettre == 'Q'){
            score += 15;
        }
        if(lettre == 'R'){
            score += 16;
        }
        if(lettre == 'S'){
            score += 17;
        }
        if(lettre == 'T'){
            score += 18;
        }
        if(lettre == 'U'){
            score += 24;
        }
        if(lettre == 'V'){
            score += 19;
        }
        if(lettre == 'W'){
            score += 20;
        }
        if(lettre == 'X'){
            score += 21;
        }
        if(lettre == 'Y'){
            score += 22;
        }
        if(lettre == 'Z'){
            score += 23;
        }
        if(lettre == '*'){
            score += 25;
        }
    }
    return score;
}
