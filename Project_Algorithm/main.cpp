#include "binaire.h"

int main(int argc, char * argv[]){
	Binaire bin("uniprot_sprot.fasta.phr");
	bin.open_fichier();
	bin.test_fichier();	
}
