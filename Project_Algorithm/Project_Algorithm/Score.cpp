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

string Score(string sequence){//lire séquence et assigner score pour chaque lettre donc faire binaire en lettre
    int i=0;
    char lettre = '\0';
    string score;
    for(i=0;i<sequence.size();i++){
        lettre = sequence[i];
        if(lettre == '-'){
            score += bitset<8>(0).to_string();
        }
        if(lettre == 'A'){
            score += bitset<8>(1).to_string();
        }
        if(lettre == 'B'){
            score += bitset<8>(2).to_string();
        }
        if(lettre == 'C'){
            score += bitset<8>(3).to_string();
        }
        if(lettre == 'D'){
            score += bitset<8>(4).to_string();
        }
        if(lettre == 'E'){
            score += bitset<8>(5).to_string();
        }
        if(lettre == 'F'){
            score += bitset<8>(6).to_string();
        }
        if(lettre == 'G'){
            score += bitset<8>(7).to_string();
        }
        if(lettre == 'H'){
            score += bitset<8>(8).to_string();
        }
        if(lettre == 'I'){
            score += bitset<8>(9).to_string();
        }
        if(lettre == 'J'){
            score += bitset<8>(27).to_string();
        }
        if(lettre == 'K'){
            score += bitset<8>(10).to_string();
        }
        if(lettre == 'L'){
            score += bitset<8>(11).to_string();
        }
        if(lettre == 'M'){
            score += bitset<8>(12).to_string();
        }
        if(lettre == 'N'){
            score += bitset<8>(13).to_string();
        }
        if(lettre == 'O'){
            score += bitset<8>(26).to_string();
        }
        if(lettre == 'P'){
            score += bitset<8>(14).to_string();
        }
        if(lettre == 'Q'){
            score += bitset<8>(15).to_string();
        }
        if(lettre == 'R'){
            score += bitset<8>(16).to_string();
        }
        if(lettre == 'S'){
            score += bitset<8>(17).to_string();
        }
        if(lettre == 'T'){
            score += bitset<8>(18).to_string();
        }
        if(lettre == 'U'){
            score += bitset<8>(24).to_string();
        }
        if(lettre == 'V'){
            score += bitset<8>(19).to_string();
        }
        if(lettre == 'W'){
            score += bitset<8>(20).to_string();
        }
        if(lettre == 'X'){
            score += bitset<8>(21).to_string();
        }
        if(lettre == 'Y'){
            score += bitset<8>(22).to_string();
        }
        if(lettre == 'Z'){
            score += bitset<8>(23).to_string();
        }
        if(lettre == '*'){
            score += bitset<8>(25).to_string();
        }
    }
    return score;
}


char score_Inverse(int valeur){
    char lettre = '\0';
    if(valeur == 0){
        lettre = '-';
    }
    if(valeur == 1){
        lettre = 'A';
    }
    if(valeur == 2){
        lettre = 'B';
    }
    if(valeur == 3){
        lettre = 'C';
    }
    if(valeur == 4){
        lettre = 'D';
    }
    if(valeur == 5){
        lettre = 'E';
    }
    if(valeur == 6){
        lettre = 'F';
    }
    if(valeur == 7){
        lettre = 'G';
    }
    if(valeur == 8){
        lettre = 'H';
    }
    if(valeur == 9){
        lettre = 'I';
    }
    if(valeur == 27){
        lettre = 'J';
    }
    if(valeur == 10){
        lettre = 'K';
    }
    if(valeur == 11){
        lettre = 'L';
    }
    if(valeur == 12){
        lettre = 'M';
    }
    if(valeur == 13){
        lettre = 'N';
    }
    if(valeur == 26){
        lettre = 'O';
    }
    if(valeur == 14){
        lettre = 'P';
    }
    if(valeur == 15){
        lettre = 'Q';
    }
    if(valeur == 16){
        lettre = 'R';
    }
    if(valeur == 17){
        lettre = 'S';
    }
    if(valeur == 18){
        lettre = 'T';
    }
    if(valeur == 24){
        lettre = 'U';
    }
    if(valeur == 19){
        lettre = 'V';
    }
    if(valeur == 20){
        lettre = 'W';
    }
    if(valeur == 21){
        lettre = 'X';
    }
    if(valeur == 22){
        lettre = 'Y';
    }
    if(valeur == 23){
        lettre = 'Z';
    }
    if(valeur == 25){
        lettre = '*';
    }
    return lettre;
}
