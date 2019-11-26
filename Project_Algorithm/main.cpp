//
//  main.cpp
//  Project_Algorithm
//
//  Created by Langlet Maxime on 01/11/2019.
//  Copyright © 2019 Langlet Maxime. All rights reserved.
//

#include "Fasta_To_Bits.hpp"
#include "Score.hpp"
#include "ouverture.hpp"
#include "comparaison.hpp"


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
    ifstream input2("/Users/langletmaxime/Desktop/P4/C++/swipe/uniprot_sprot.fasta.pin");
    ifstream file("/Users/langletmaxime/Desktop/P4/C++/swipe/uniprot_sprot.fasta.psq");
    ifstream file2("/Users/langletmaxime/Desktop/P4/C++/swipe/uniprot_sprot.fasta.phr");
    chrono::time_point<chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    vector<char> buffer = read_psq(file);
    cout<<endl;
    vector<int> header_offsets;
    vector<int> sequence_offsets;
    header_offsets = header_offset(input2);
    sequence_offsets = sequence_offset(input2);
    bits = Fasta_To_String(input);
    Sequence_comp(bits, buffer, sequence_offsets, header_offsets, file2);
    end = std::chrono::system_clock::now();
    int elapsed_seconds = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    cout << "elapsed time: " << elapsed_seconds << "s\n";
    cout << header_offsets.size() << sequence_offsets.size() << endl;
    input.close();
    input2.close();
    file.close();
    return 0;
}
