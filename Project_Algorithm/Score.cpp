//
//  Score.cpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 08/11/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#include "Score.hpp"
//Pas sur de si c'est juste ca mais bon au cas ou
/*
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
*/

char score_Inverse(int valeur){
    char lettre = '\0';
    switch (valeur) {
        case 0:
            lettre = '-';
        break;
        case 1:
            lettre = 'A';
            break;
        case 2:
            lettre = 'B';
            break;
        case 3:
            lettre = 'C';
            break;
        case 4:
            lettre = 'D';
            break;
        case 5:
            lettre = 'E';
            break;
        case 6:
            lettre = 'F';
            break;
        case 7:
            lettre = 'G';
            break;
        case 8:
            lettre = 'H';
            break;
        case 9:
            lettre = 'I';
            break;
        case 10:
            lettre = 'K';
            break;
        case 11:
            lettre = 'L';
            break;
        case 12:
            lettre = 'M';
            break;
        case 13:
            lettre = 'N';
            break;
        case 14:
            lettre = 'P';
            break;
        case 15:
            lettre = 'Q';
            break;
        case 16:
            lettre = 'R';
            break;
        case 17:
            lettre = 'S';
            break;
        case 18:
            lettre = 'T';
            break;
        case 19:
            lettre = 'V';
            break;
        case 20:
            lettre = 'W';
            break;
        case 21:
            lettre = 'X';
            break;
        case 22:
            lettre = 'Y';
            break;
        case 23:
            lettre = 'Z';
            break;
        case 24:
            lettre = 'U';
            break;
        case 25:
            lettre = '*';
            break;
        case 26:
            lettre = '0';
        break;
        case 27:
            lettre = 'J';
        break;
        //default:
            //break;
    }
    return lettre;
}
