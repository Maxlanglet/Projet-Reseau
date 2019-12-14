
#include "Fasta_To_Bits.hpp"
#include "Score.hpp"
#include "ouverture.hpp"
#include "comparaison.hpp"
#include "SwipeAlgo.hpp"
#include "binaire.h"
#include "Sequence.hpp"
#include "Offsets.hpp"
#include "blosum.hpp"
#include "header.h"
#include <map>
#include <iterator>


int main(int argc, const char * argv[]) {
    /*
    if(argc<=1){
        cout << "Argument demandé :" << argv[0]<<" [fichier] "<<endl;
        return 1;
    }
    

    
    //ifstream input(argv[1]);
    string bits;
    //ifstream input(argv[1]);
    //ifstream input2(argv[2]);
    //ifstream file(argv[3]);
    //ifstream file2(argv[4]);
     */
    //"/Users/langletmaxime/Desktop/P4/C++/swipe/uniprot_sprot.fasta.psq"
    //"/Users/langletmaxime/Desktop/P4/C++/swipe/uniprot_sprot.fasta.pin"
    Sequence sequence("/Users/langletmaxime/Desktop/P4/C++/swipe/uniprot_sprot.fasta.psq");
    Offsets offsets("/Users/langletmaxime/Desktop/P4/C++/swipe/uniprot_sprot.fasta.pin");
    Header head("/Users/langletmaxime/Desktop/P4/C++/swipe/uniprot_sprot.fasta.phr");
    Swipe swipe;
    ifstream input("/Users/langletmaxime/Desktop/P4/C++/swipe/P00533.fasta");
    
    string fasta = Fasta_To_String(input);
    sequence.read_psq();
    offsets.offset();
    
    
    map<double, int> score_max;
    double score = 0;
    const char* seq = sequence.get_sequence2();
    
    
    cout << "lancement swipe" << endl;
    double tempsmoyen = 0.0;
    chrono::time_point<chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for (int g = 116000; g<123000; g++) {//1878 pbm //offsets.get_size()
        int h = offsets.get_seq_offset(g-1);
        int u = offsets.get_seq_offset(g);
        chrono::time_point<chrono::system_clock> start2, end2;
        start2 = std::chrono::system_clock::now();
        
        score = swipe.Algo(fasta, seq, h, u);
        if(score_max.size() < 21){
            score_max.insert(pair<double, int>(score,g));
        }
        else if(score_max.size() == 20 && score_max.begin()->first < score){
            score_max.erase(score_max.begin());
            score_max.insert(pair<double, int>(score,g));
        }
        
        end2 = std::chrono::system_clock::now();
        double elapsed_seconds2 = chrono::duration_cast<chrono::milliseconds>(end2-start2).count();
        //cout << "elapsed time: " << elapsed_seconds2 << "ms\n";
        tempsmoyen += elapsed_seconds2;
        if(g%1000 == 0 ){
            cout<<g-1<<endl;
        }
    }
    end = std::chrono::system_clock::now();
    double elapsed_seconds = chrono::duration_cast<chrono::seconds>(end-start).count();
    cout << "elapsed time: " << elapsed_seconds << "s\n";
    cout << "temps moyen par sequence: " << tempsmoyen/7000 << "ms" << endl;
    
    
    map<double,int>::iterator itr;
    int off=0;
    head.open_fichier();
    //head.test_fichier();
    /*head.close_fichier();
    head.acquiert((int)max);
    head.getData();
    head.close_fichier();*/
    for(itr = --score_max.end(); itr != score_max.begin(); itr--){
        cout<<"score : "<<itr->first<<" g : "<<itr->second - 1<<endl;
        head.acquiert(itr->second - 1);
    }
    head.close_fichier();
    
    return 0;
}
