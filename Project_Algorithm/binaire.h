#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Binaire
{
private :
	string adresse;

	
public : 
	Binaire(string adr);
	//void setAdresse(string adresse);
	string getAdresse();
	ifstream open_fichier();
	void close_fichier(ifstream fichier);
};
