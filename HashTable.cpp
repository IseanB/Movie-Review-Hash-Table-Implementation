#include "HashTable.h"
#include "WordEntry.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>


/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s): hashTable(new list<WordEntry>[s]){
    size = s;
    // bool* boolTableTemp = new bool[s]{false};
    // occupiedTable = boolTableTemp;
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
    // int hashConstant = 4;
    // int hashCounter = 0;
    // long long int returnValue = 0;
    // for(char k : s){
    //     returnValue += (hashCounter * k);
    //     ++hashCounter;
    // }
    long long int sum = 0;
    for(char k : s){
        sum += k;
    }
    return sum*(size + s.size())%size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
update boolTable, cases if empty and case if not. Check if alreadt
*/
void HashTable::put(const string &s, int score) {
    // cout << "InsidePut" << endl;
    int hashNum = computeHash(s);
    // cout << "After Hash" << endl;
    for(list<WordEntry>::iterator i = hashTable[hashNum].begin(); i != hashTable[hashNum].end(); ++i){
        // cout << "In Loop";
        if((*i).getWord() == s){//if element found in list, return true
            //2. update its score
            // cout << "Test6";
            (*i).addNewAppearance(score);
            // cout << "Test7";
            return;
        }
    }
    hashTable[hashNum].push_back(WordEntry(s, score));
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
    if(!(this->contains(s))){
        return 2.0;
    }
    else{
        int hashNum = computeHash(s);
        list<WordEntry> currList = hashTable[hashNum];
        for(WordEntry currItem : currList){
            if(currItem.getWord() == s){//if element found in list, return true
                return currItem.getAverage();
            }
        }
    }
    return 2.0;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
    int hashNum = computeHash(s);
    list<WordEntry> currList = hashTable[hashNum];
        for(WordEntry currItem : currList){
            if(currItem.getWord() == s){//if element found in list, return true
                return true;
            }
        }// if nothing found in whole list, return false
    return false;
}

int main() {
	// declare a few needed variables for inputing the data
	string line;    
	int score;
	string message = " ";
	
	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	
	// cout << "Test1" << endl;
	//create hash table
	HashTable table(20071);
	
	while (!myfile.eof()) {
	    myfile >> score;     // get score
	    myfile.get();        // get blank space
	    getline(myfile, line);
	    int len = line.size();
	    while(len > 0) {     // identify all individual strings
	        string sub;
	        len = line.find(" ");
	        if (len > 0) {
	            sub = line.substr(0, len);
	            line = line.substr(len + 1, line.size());
	        }
	        else {
	            sub = line.substr(0, line.size() - 1);
	        }
			// cout << "Test 4" << endl;
	        table.put(sub, score); // insert string with the score
	    }
	}
	// cout << "Test2" << endl;
	// after data is entered in hash function
	// prompt user for a new movie review
	while(message.length() > 0) {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);

	    // used for calculating the average
	    double sum = 0;
	    int count = 0;
	    
	    double sentiment = 0.0;
	    
	    size_t len = message.size();
	    // get each individual word from the input
	    while(len != string::npos) {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else {
	            sub = message;
	        }
	        // calculate the score of each word
	        sum += table.getAverage(sub);
	        ++count;
	    }
	    if (message.size() > 0) {
	    	sentiment = sum / count;
	        cout << "The review has an average value of " << sentiment << endl;
	        if (sentiment >= 3.0) {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	
	return 0;
}