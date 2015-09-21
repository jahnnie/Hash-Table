// File hashDriver.cpp:
// Place your identifying information here CLEARLY.
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <math.h>
//#include "hashTime.cpp"
//#define TABLE_SIZE 11 // Change as necessary
using namespace std;

int TABLE_SIZE = 0;
int totalProbes = 0;
int tempProbes = 0;
int numInserts = 0;
int tempInserts = 0;
string stringArray[7];
int ind = 1;

using namespace std;
class TableEntry {
private:
    std::string key;
    int value;
public:
    TableEntry(std::string key, int value) {
        this->key = key;
        this->value = value;
    }
    
    std::string getKey() { return key; }
    int getValue() { return value; }
    
};

class Hasher {
    private:
    TableEntry** table; //how do you access this
    char type;
    char crp;
    double lfactor;
    
    public:
    // Define the necessary constructors (be sure to initialize your table entries to NULL):
    // See assignment description.
    Hasher(char type, char crp){
        this->type = type;
        this->crp = crp;
        table =  new TableEntry*[TABLE_SIZE];
    };

    Hasher(char hashType, char probeType, double loadFactor, string name){
        //stringstream ss;
        string title =  "Hash fn |Load Factor |Capacity |Rows Inserted |AvgProbesperInsert |Expected#Probes";
        //stringArray[0] = ss.str();
        stringArray[0] = title;


        type = hashType;
        crp = probeType;
        lfactor = loadFactor;

        int number_of_lines = 0;
        ifstream f(name.c_str());
        string line;
        string line1;
    
        while(getline(f, line)){
            ++number_of_lines;
        }

        int numFactor =  number_of_lines * pow(lfactor, -1);
        TABLE_SIZE = getPrime(numFactor);

        table =  new TableEntry*[TABLE_SIZE];
        f.close();
        ifstream f1(name.c_str());
        int value = 0;
        while(getline(f1, line1)){
            insert(line1.substr(0,8), ++value);
        }

        double avgpi = (double)totalProbes/(double)numInserts;
        double lf = (double)numInserts/(double)TABLE_SIZE;
        stringArray[ind] = getRow(lf, TABLE_SIZE, avgpi, expectedProbes(lf));
        ind++;
        tempProbes = totalProbes;
        tempInserts = numInserts;
        numInserts = 0;
        totalProbes = 0;
    };

    double expectedProbes(double lf){
        return (1/lf) * log(1/(1-lf));
    };

    string getRow(double lf, int capacity, double avgp, double donald){
        string row;
        stringstream ss;
        if(this->type == 'g'){
            ss << "goodHash " << lf << " " << " "  << " " << " " << " " << capacity << " " << " " << " " << " " << " " << " " << " " <<numInserts  <<  "         " << avgp << "                  " << donald;
            row = ss.str();
            return row;
        }
        if(this->type == 'p'){
            ss << "poorHash " << lf << " "  << " " << " " << " " << " " << capacity << " " << " " << " " <<" " << " " << " " << " " << numInserts << "         " << avgp << "                  "<< donald;
            row = ss.str();
            return row;
        }
    }


    TableEntry** getTable(){
        return table;
    };
    // See assignment description.
   //Hasher(char type, char crp, char* filename); 
    
    // Define the following functions:
    
    // See assignment description.
    bool search(std::string key, int& subscript, char intent){
        if(intent == 's'){
            if(this->crp == 'q'){
                return quad_search(key, subscript);
            }
            if(this->crp == 'd') {
                return double_search(key, subscript);
            }
        }
        else if(intent == 'i')//insert
        {
            if(this->crp == 'q'){
                return quad_insearch(key, subscript);
            }
            if(this->crp == 'd') {
                return double_insearch(key, subscript);
            }
        }
    };
    // See assignment description.
    bool insert(std::string key, int value){
        int subscript = -1;
        if(search(key, subscript, 'i')){
            table[subscript] = new TableEntry(key, value);
            return true;
        }
        else{
            cout << "Table full.";
            return false;
        }
    };
    // See assignment description.
    bool remove(std::string key){
        int subscript = -1;
        if(search(key, subscript, 's')){
            table[subscript] = new TableEntry("t", 0);
            return true;
        }
        return false;
    };
    /*
    bool isFull(){
        for(int i = 0; i < TABLE_SIZE; i++){
            if(table[i]->getKey() == "t"||table[i] == NULL)
                return false;
        }
        return true;
    };*/
    
    // Simply outputs the current contents of the table and the indices (you can write a loop
    // that just prints out the underlying array):
    // E.g.
    //    table->printTable() might generate:
    //        25  HBZEJKGA   1
    //        32  RHJMIVTA   2
    //
    void printTable(){
        for(int i = 0; i < TABLE_SIZE; i++){
            if (table[i] != NULL)
            {
            cout << i << " " << table[i]->getKey() << " " << table[i]->getValue() << endl;}
            else
            {
                cout << i << "" << endl;
            }
        }
    };

    bool quad_insearch(string key, int& subscript){
        if(this->type == 'p'){
            int hashed = poorHash(key);
            int i = 0;
            while(i < TABLE_SIZE){
                if(table[(hashed + i*i)%TABLE_SIZE] == NULL || table[(hashed+i*i)%TABLE_SIZE]->getKey() == "t"
                    ||table[(hashed+i*i)%TABLE_SIZE]->getKey() == key){
                        subscript = (hashed+i*i)%TABLE_SIZE;
                        numInserts++;
                        return true;
                    }
                totalProbes++;
                i++;
                }
            return false;
        }
        if(this->type =='g'){
            int  hashed_1= goodHash(key);
            int j = 0;
            while(j < TABLE_SIZE){
                if(table[(hashed_1+j*j)%TABLE_SIZE]== NULL || table[(hashed_1+j*j)%TABLE_SIZE]->getKey() == "t"
                    ||table[(hashed_1+j*j)%TABLE_SIZE]->getKey() == key){
                        subscript = (hashed_1+j*j)%TABLE_SIZE;
                        numInserts++;
                        return true;
                    }
                totalProbes++;
                j++;
                }
            return false;
        }
    };

    bool double_insearch(string key, int& subscript){
        int hashed_1 = primeHash(key);
        if(this->type == 'p'){
            int hashed = poorHash(key);
            int i = 0;
            while(i < TABLE_SIZE){
                if(table[(hashed + i*hashed_1)%TABLE_SIZE] == NULL|| table[(hashed+i*hashed_1)%TABLE_SIZE]->getKey() == "t"
                    ||table[(hashed+i*hashed_1)%TABLE_SIZE]->getKey() == key){
                    subscript = (hashed + i*hashed_1)%TABLE_SIZE;
                    numInserts++;
                    return true;
                }
                totalProbes++;
                i++;
            }
            return false;
        }

        if(this->type =='g'){
            int hashed_2= goodHash(key);
            int j = 0;
            while(j < TABLE_SIZE){
                if(table[(hashed_2+j*hashed_1)%TABLE_SIZE]== NULL || table[(hashed_2+j*hashed_1)%TABLE_SIZE]->getKey() == "t"
                    ||table[(hashed_2+j*hashed_1)%TABLE_SIZE]->getKey() == key){
                        subscript = (hashed_2+j*hashed_1)%TABLE_SIZE;
                        numInserts++;
                        return true;
                    }
                totalProbes++;
                j++;
                }
            return false;
        }
    };


    bool quad_search(string key, int& subscript){
        if(this->type == 'p'){
            int hashed = poorHash(key);
            int i = 0;
            while(i < TABLE_SIZE){
                if(table[(hashed + i*i)%TABLE_SIZE] != NULL){
                    if(table[(hashed + i*i)%TABLE_SIZE] ->getKey() == key){
                        subscript = hashed;
                        return true;
                    }
                i++;
                }
                else return false;
            }
            return false;
        }

        if(this->type == 'g'){
            int hashed_1 = goodHash(key);
            int j = 0;
            while(j < TABLE_SIZE){
                if(table[(hashed_1+j*j)%TABLE_SIZE] != NULL){
                    if(table[(hashed_1+j*j)%TABLE_SIZE] ->getKey() == key){
                        subscript = (hashed_1+j*j)%TABLE_SIZE;
                        return true;
                    }
                    j++;
                }
                else return false;
            }
            return false;
            }
            return false;
    };

    bool double_search(string key, int& subscript){
        int hashed_1 = primeHash(key);
        if(this->type == 'p'){
            int hashed = poorHash(key);
            int i = 0;
            while(i < TABLE_SIZE){
                if(table[(hashed + i*hashed_1)%TABLE_SIZE] != NULL){
                    if(table[(hashed + i*hashed_1)%TABLE_SIZE] ->getKey() == key){
                        subscript = (hashed + i*hashed_1)%TABLE_SIZE;
                        return true;
                    }
                i++;
                }
                else return false;
            }
            return false;
        }

        if(this->type == 'g'){
            int hashed_2 = goodHash(key);
            int j = 0;
        while(j < TABLE_SIZE){
            if(table[(hashed_2+j*hashed_1)%TABLE_SIZE] != NULL){
                if(table[(hashed_2+j*hashed_1)%TABLE_SIZE] ->getKey() == key){
                    subscript = (hashed_2+j*hashed_1)%TABLE_SIZE;
                    return true;
                }
                j++;
            }
            else return false;
        }
        return false;
        }

        return false;
    };

    bool isPrime(int number){
       int i;
        for (i=2; i<number; i++){
            if (number % i == 0){
                return false;
        }
    }
    return true;    
    };

    int getPrime(int n){
        if(isPrime(n)){
            return n;}
        getPrime(++n);
    };

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
    };

    int goodHash(string key){
        int unique = 0;
        for(int i = 0; i< key.length(); i++)
            unique = (2*unique + key.at(i));    
        return unique%TABLE_SIZE;
    };

    int primeHash(string key){
    int sum = 0;
    for (int i = 0; i < key.length(); ++i){
        sum += 5 - (key.at(i) % 5);
    }
    return sum % TABLE_SIZE;
    };

    const string getKey(const int subscript){
        return table[subscript]->getKey();
    };

    const int getValue(const int subscript){
        return table[subscript]->getValue();
    };

    const int getProbes(){
        int temp = tempProbes;
        tempProbes = 0;
        return temp;
    };

    const int getCapacity(){
        return TABLE_SIZE;
    };

    const int getSize(){
        int temp = tempInserts;
        tempInserts = 0;
        return temp;
    };


   
    // Define any other necessary functions that are part of the public interface:
    
    // Destructor-- do not alter.
    ~Hasher() 
    {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL)
                delete table[i];
        delete[] table;
    };
};


// **Sample** main function/driver-- THIS IS NOT A COMPLETE TEST SUITE
// YOU MUST WRITE YOUR OWN TESTS
// See assignment description.
int main( int argc, char* argv[])
{
    //cout << stringArray[0];
        // Generate empty hash tables:
    /*
    Hasher* goodHashRP1 = new Hasher('g', 'q');
    Hasher* goodHashQP1 = new Hasher('g', 'q');
    Hasher* badHashRP1 = new Hasher('p', 'd');
    Hasher* badHashQP1 = new Hasher('p', 'q');
    */
    
    // Generate hash tables that are systematically loaded from file.
    // Note that if you cannot fit an element you should stop inserting elements
    // and set a flag to full.
    Hasher* goodHashRP1 = new Hasher('g', 'd', 0.25, "small.txt");
    Hasher* goodHashQP2 = new Hasher('g', 'q', 0.5, "small.txt");
    Hasher* goodHashRP2 = new Hasher('g', 'd', 0.75, "small.txt");
    Hasher* poorHashRP1 = new Hasher('p', 'd', 0.25, "small.txt");
    Hasher* poorHashQP2 = new Hasher('p', 'q', 0.5, "small.txt");
    Hasher* poorHashRP2 = new Hasher('p', 'd', 0.75, "small.txt");


    for(int i = 0; i < 7; i++)
        cout << stringArray[i] << endl;

    
    /*
    string key = "ABCDEFGH";
    int value = 10;
    goodHashRP1->insert(key, value);
    cout << goodHash(key) << " "<< endl;

    string key1 = "XYWCHJKL";
    int value1 = 9;
    goodHashRP1->insert(key1, value1);
    cout << goodHash(key1) << " "<< endl;
    

    string key2 = "YUIOPDFG";
    int value2 = 42;
    goodHashRP1->insert(key2, value2);
    cout << goodHash(key2) << " "<< endl;
    

    string key3 = "QWERTYASF";
    int value3 = 2;
    goodHashRP1->insert(key3, value3);
    cout << goodHash(key3) << " "<< endl;
    

    string key4 = "ASDFGHJR";
    int value4 = 3;
    goodHashRP1->insert(key4, value4);
    cout << goodHash(key4) << " "<< endl;
    
    
    string key5 = "ZCCZZZZZ";
    int value5 = 5;
    goodHashRP1->insert(key5, value5);
    cout << goodHash(key5) <<endl;
    

    string key6 = "ZDCZZZZZ";
    int value6 = 5;
    goodHashRP1->insert(key6, value6);
    cout << goodHash(key6) << " "<< endl;



    string key7 = "SAUDERCS";
    int value7 = 5;
    goodHashRP1->insert(key7, value7);
    cout << goodHash(key7) << " "<< endl;

    string key8 = "CLARENCEL";
    int value8 = 6;
    goodHashRP1->insert(key8, value8);
    cout << goodHash(key8) << " "<< endl;
    

    string key9 = "ZZZZZZZZ";
    int value9 = 6;
    goodHashRP1->insert(key9, value9);
    cout << goodHash(key9) << " "<< endl;

    
    string key10 = "YIXIYIXI";
    int value10 = 6;
    goodHashRP1->insert(key10, value10);
    cout << goodHash(key10)<< endl;

    //goodHashRP1->remove(key10);
    cout << "\n";

    goodHashRP1->printTable();
*/
    return 0;
}