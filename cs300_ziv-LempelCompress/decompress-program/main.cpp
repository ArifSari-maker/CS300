#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "HashTableD.cpp"
using namespace std; 
///Arif Kemal Sari 28999
/*
read file compout which contains only integers and transform to original file and 
write to decompout file
hash table use for construct dictionary
*/
int main(){
	string notFound = "";
	int key = 0;
	int code;
	HashTable<int, string> hashtable(notFound,4096);/// construct dictionary

    ifstream read_file("compout");
	if (!read_file.is_open()) {
        cerr << "Error: unable to open input file" << endl;
        return -1;
    }
	for (int i = 0; i < 256; i++) {
        hashtable.insert(key,string(1,char(i)));
		key++;
    }
	vector<int> number_input;
	ofstream write_file("decompout");
	if(!read_file.eof()){
		read_file>>code;
		write_file<<hashtable.find(code);
		number_input.push_back(code);
	}
	while(!read_file.eof()){  // read file till the end of the file
		read_file>>code;
		number_input.push_back(code);
	}
	read_file.close();// we done with our file
	string p ,current; 
	char c;
	for(unsigned int i = 1;i<number_input.size();i++){
        // if number is not in hash table
		if(hashtable.find(number_input[i])==""){
			 p = hashtable.find(number_input[i-1]); 
			 c = p[0]; 
			 hashtable.insert(key,p+c);
			 key++;
			 write_file<<p+c;
		}
		else{
			p = hashtable.find(number_input[i-1]); // find previous string from hash table
			current = hashtable.find(number_input[i]);// find first character of current string
			hashtable.insert(key,p + (current[0]));
			key++;
			write_file<<current;
		}
	}
	write_file.close();

	return 0;
} 