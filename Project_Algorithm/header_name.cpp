#include "header_name.h"
#include <iostream> 
#include <fstream>
//#include <string.h>

using namespace std;

int main(){
	int offset = 21878502;
	string fichier = "uniprot_sprot.fasta.phr";
	//string fichier = "uniprot_sprot.fasta.pin"
	acquiert(offset, fichier);
	
}

void acquiert(int offset, string fichier){
	ifstream f(fichier, ios::in | ios::binary);
	
	if(!f.is_open()){
		cout << "erreur, impossible d'ouvrir le fichier header" << endl;
	}
	f.seekg(offset);
	int pos = f.tellg();
	//cout << "position : " << pos << endl;
	int var = 0;
	char octet;
	while(var < 4){
		f.read(&octet, 1);
		//cout << int(octet) <<endl;
		if(int(octet) == 26){
			read_string(&f);
			var++;
		}
		if(int(octet) == 2){
			read_int(&f);
			var++;
		}
		
	}
	//cout << "position : " << f.tellg() << endl;
	
}

string read_string(ifstream* f){
	string res = "";
	//cout << "position string : " << f->tellg() << endl;
	char size;
	f->read(&size, 1);
	//cout << "taille string : " << int(size) << endl;
	char* text = new char[int(size)];
	f->read(text, int(size));
	cout << "texte : " << text << endl;
	res = text;
	return res;
}

int read_int(ifstream* f){
	int res = 0;
	//cout << "position int : " << f->tellg() << endl;
	char size;
	f->read(&size,1);
	//cout << "taille int : " << int(size) << endl;
	//cout << "position int : " << f->tellg() << endl;
	int buffer;
	f-> read((char*)&buffer, int(size));
	bswap_64(buffer);
	
	cout<<"int : "<< buffer << endl;
	
	res = buffer;
	
	return res;
}
