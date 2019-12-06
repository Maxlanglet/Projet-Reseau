#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Binaire
{
private :
	string adresse;
	ifstream f;
	
public : 
	Binaire(string adr);
	//void setAdresse(string adresse);
	string getAdresse();
	void open_fichier();
	void test_fichier();
	void close_fichier(ifstream fichier);
};
