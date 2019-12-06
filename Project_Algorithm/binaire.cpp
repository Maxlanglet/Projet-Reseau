#include "binaire.h"


Binaire::Binaire(string adr){
	adresse = adr;
}

//void Binaire::setAdresse(string adresse);

string getAdresse();

ifstream Binaire::open_fichier(){
	ifstream f(adresse, ios::in | ios::binary);
	
	if(!f.is_open()){
		cout << "erreur, impossible d'ouvrir le fichier" << endl;
		//return null;
	}

	return f;
}

void Binaire::close_fichier(ifstream fichier){
	fichier.close();
}
