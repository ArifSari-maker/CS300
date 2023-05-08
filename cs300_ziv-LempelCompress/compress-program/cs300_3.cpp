#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.cpp"
using namespace std;


///Arif Kemal Sari 28999
/*
read file compin compress it as compout (file contains only integers)
using hash table as dictionary
*/
int main(){
	
	string p = "";
	char c;
	int key = 0;
	int notfound = -1;
	
    ifstream read_file("compin");
	if (!read_file.is_open()) {
        cerr << "Error: unable to open input file" << endl;
        return -1;
    }
	
	HashTable<int,string> hashtable(notfound, 4096);

	for (int i = 0; i < 256; i++) { ///initilize all standart charactes as string object
        hashtable.insert(key,string(1,char(i)));
		key++;
    }
    ofstream write_file("compout");
	while(!read_file.eof()){
		
		read_file.get(c);
		if(hashtable.find(p+c)!=-1){
			p = p + c;
		}
		else{
			//output index of p Encode value from hash table
			write_file<< hashtable.find(p) <<" ";
			hashtable.insert(key,p+c);
			p = "";
			p += c;
			key++;
		}
		
	}
	write_file<< hashtable.find(p) <<" ";
	read_file.close();
	write_file.close();
	return 0;
}
