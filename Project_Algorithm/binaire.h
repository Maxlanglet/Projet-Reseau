#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;
class Binaire
{
private :
	string adresse;
	
	
public : 
	Binaire(string adr);
	//void setAdresse(string adresse);
	string getAdresse();
	void open_fichier();
	void test_fichier();
	void close_fichier();
	ifstream f;
};
