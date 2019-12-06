#include "binaire.h"


Binaire::Binaire(string adr)
	// : f(...) initialisation list
{
	adresse = adr;
}

//void Binaire::setAdresse(string adresse);

string getAdresse();

void Binaire::open_fichier(){
	cout << adresse<< endl;
	f.open(adresse, ios::in | ios::binary);
	//f(adresse, ios::in | ios::binary);
	
	if(!f.is_open()){
		cout << "erreur, impossible d'ouvrir le fichier" << endl;
		//return null;
	}

	//return f;
}

void Binaire::test_fichier(){
	if(!f.is_open()){
		cout << "erreur, impossible d'accéder au fichier" << endl;
		//return null;
	}
	else{
		char octet;
		f.read(&octet,1);
		cout << (int)octet << endl;
	}
}

void Binaire::close_fichier(ifstream fichier){
	fichier.close();
}
