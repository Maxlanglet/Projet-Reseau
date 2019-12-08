//
//  SwipeAlgo.cpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 03/12/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#include "blosum.hpp"

int get_pos(char prot){
    int pos=0;
    if (prot=='A') {
        pos=0;
    }
    if (prot=='R') {
        pos=1;
    }
    if (prot=='N') {
        pos=2;
    }
    if (prot=='D') {
        pos=3;
    }
    if (prot=='C') {
        pos=4;
    }
    if (prot=='Q') {
        pos=5;
    }
    if (prot=='E') {
        pos=6;
    }
    if (prot=='G') {
        pos=7;
    }
    if (prot=='H') {
        pos=8;
    }
    if (prot=='I') {
        pos=9;
    }
    if (prot=='L') {
        pos=10;
    }
    if (prot=='K') {
        pos=11;
    }
    if (prot=='M') {
        pos=12;
    }
    if (prot=='F') {
        pos=13;
    }
    if (prot=='P') {
        pos=14;
    }
    if (prot=='S') {
        pos=15;
    }
    if (prot=='T') {
        pos=16;
    }
    if (prot=='W') {
        pos=17;
    }
    if (prot=='Y') {
        pos=18;
    }
    if (prot=='V') {
        pos=19;
    }
    if (prot=='B') {
        pos=20;
    }
    if (prot=='J') {
        pos=21;
    }
    if (prot=='Z') {
        pos=22;
    }
    if (prot=='X') {
        pos=23;
    }
    if (prot=='*') {
        pos=24;
    }
    return pos;
}
//TODO: Pas finis mais deja un debut
void swipe(string fasta, vector<char> psq, int offset1, int offset2){
    cout << "lancement swipe" << endl;
    int posi=0;
    int posj=0;
    int max=0;
    vector<vector<int> > mat(fasta.size(), vector<int>(offset2-offset1, 0));//TODO: meilleur choix avec matrice et memoisation de je sais pas quoi, comme pas possible de faire int [truc variable] il faut passer par des pointeurs je pense
    for (int i =1; i<fasta.size(); i++) {
        posi=get_pos(fasta[i-1]);
        for (int j =1; j<offset2-offset1; j++) {
            int maxlocal=0;
            posj=get_pos(score_Inverse(psq[j+offset1]));
            int score = mat[i][j-1] -11;
            if (score>maxlocal) {
                maxlocal = score;
            }
            score = mat[i-1][j]-11;
            if (score>maxlocal) {
                maxlocal = score;
            }
            int alignement = get_blosum(posi, posj);
            score = mat[i-1][j-1] + alignement;
            if (score>maxlocal) {
                maxlocal = score;
            }
            mat[i][j] = maxlocal;
            
            if (maxlocal>max) {
                max = maxlocal;
            }
            //cout << maxlocal << endl;
        }
    }
    cout << "score :"<< max << endl;
}
//void swipe::lireBlosum(const char blosum)//si on a le choix pour les matrices BLOSUM alors on fait direct une map
