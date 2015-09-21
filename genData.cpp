#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace std;
/*
generate n lines containing key-value pairs,
then write to file
*/
string makeKey(int keyInt[]);

int main(int argc, char* argv[]){
	int number_of_lines = 0;
	srand (time(NULL));
	ofstream myfile;
	myfile.open(argv[2]);
	int size = atoi(argv[1]);
	for(int i = 0; i < size; i++){
		// create a new int array holding 8 rand #s 0-25
		// convert array to string
		//append string to " " and i+1
		//write it as a line in a text file
		int* keyInt = new int[8];
		for(int j = 0; j < 8; j++){
			keyInt[j] = rand() % 26;
		}

		string key = makeKey(keyInt);
		delete(keyInt);
		ostringstream oss;
		oss << " " << i+1;
		key += oss.str();
		myfile << key << "\r\n";
	}	
	myfile.close();
	return 0;
}

string makeKey(int keyInt[]){
	char keyArray[8];
	for(int i = 0; i < 8; i++){
		switch(keyInt[i]){
			case 0:
				keyArray[i] = 'A';
				break;
			case 1:
				keyArray[i] = 'B';
				break;
			case 2:
				keyArray[i] = 'C';
				break;
			case 3:
				keyArray[i] = 'D';
				break;
			case 4:
				keyArray[i] = 'E';
				break;
			case 5:
				keyArray[i] = 'F';
				break;
			case 6:
				keyArray[i] = 'G';
				break;
			case 7:
				keyArray[i] = 'H';
				break;
			case 8:
				keyArray[i] = 'I';
				break;
			case 9:
				keyArray[i] = 'J';
				break;
			case 10:
				keyArray[i] = 'K';
				break;
			case 11:
				keyArray[i] = 'L';
				break;
			case 12:
				keyArray[i] = 'M';
				break;
			case 13:
				keyArray[i] = 'N';
				break;
			case 14:
				keyArray[i] = 'O';
				break;
			case 15:
				keyArray[i] = 'P';
				break;
			case 16:
				keyArray[i] = 'Q';
				break;
			case 17:
				keyArray[i] = 'R';
				break;
			case 18:
				keyArray[i] = 'S';
				break;
			case 19:
				keyArray[i] = 'T';
				break;
			case 20:
				keyArray[i] = 'U';
				break;
			case 21:
				keyArray[i] = 'V';
				break;
			case 22:
				keyArray[i] = 'W';
				break;
			case 23:
				keyArray[i] = 'X';
				break;
			case 24:
				keyArray[i] = 'Y';
				break;
			case 25:
				keyArray[i] = 'Z';
				break;
			default:
				cout << "Invalid Key" << endl;		
		}
	}
	string key(keyArray, keyArray+8);
	return key;
}
