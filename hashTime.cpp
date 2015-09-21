#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <ctime>

using namespace std;


int goodHash(string key);
int poorHash(string key);
int primeHash(string key);
bool isPrime(int number);
int getPrime(int n);


/*
int main(){

	cout << getPrime(24);
	return 0;
}
*/
bool isPrime(int number){
       int i;
        for (i=2; i<number; i++){
            if (number % i == 0){
                return false;
        }
    }
    return true;    
}

int getPrime(int n){
	if(isPrime(n))
		return n;
	getPrime(++n);
}

int poorHash(string key){
	int unique = 0;
	//look at each letter
	//assign it a value
	//add all the values together
	//mod it by hashtablesize
	//return the result
	for(int i = 0; i < key.length(); i++)
		unique += key.at(i);
	return unique%TABLE_SIZE;
}

int goodHash(string key){
	int unique = 0;
	for(int i = 0; i< key.length(); i++)
		unique = (2*unique + key.at(i));	
	return unique%TABLE_SIZE;
}