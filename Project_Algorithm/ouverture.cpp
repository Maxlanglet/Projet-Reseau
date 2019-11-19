#include <iostream> 
#include <fstream>
#include <string.h>
#include <arpa/inet.h>

//using std::ifstream;
//using std::ofstream;
using namespace std;

string toBin(int dec){
	int bin;
	string res;
	while(dec != 0){
		bin = dec%2;
		res = to_string(bin)+res;
		dec=dec/2;
	}
	return res;
}

int main(int argc,char *argv[]){
	
	int version, type1, type2, type3, type4, title_lenght;
	string test = "a";
	char* buff = new char[100];
	
	if(argc != 2){
		cout << "argument incorrect" << endl;
		return EXIT_FAILURE;
	}
	
	
	string fichier = argv[1];
	
	ifstream f(fichier, ios::in | ios::binary);
	
	if(!f.is_open()){
		cout << "erreur, impossible d'ouvrir le fichier" << endl;
	}
	else { 
		
		f.read (buff, 100);
		//f.read ((char *)&type1, 1);
		//f.read ((char *)&type2, 8);
		//f.read ((char *)&type3, 8);
		//f.read ((char *)&type4, 8);
		//f.read ((char *)&title_lenght, 1);
		
		/**for (i = 0; i < 6; i++){
			f.read ((char *)&t1[i], sizeof(int));
     }**/
    }
    f.close();
    
	
    for(int i = 0; i < 100; i++){
		cout << int(buff[i]) << endl;
	}
    
    /**cout << "version=" << version << endl
    << "type(pb)=" << type1  << endl
    << "longueur du titre= " << title_lenght << endl;
    //<< "mot= " << mot << endl;
    //cout << "int size " << sizeof(a) << endl;
    //cout << "double size " << sizeof(b) << endl;
    
    /**for (i = 0; i < 6; i++){
		cout << t1 [i] << endl;
    } **/
    
    //cout << "version "<< toBin(version) <<endl;
    //cout << "type1 "<< toBin(type1) << endl
    /**<< "type2 "<< toBin(type2) << endl
    << "type3 "<< toBin(type3) << endl
    << "type4 "<< toBin(type1) << endl**/;
    //cout << "longeur titre "<< toBin(title_lenght) <<endl;
    
    return 0;
}
