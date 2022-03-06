#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {
//isean is a slowpoke and he confuses me all the time like JAHDKFJHAJKDHF sometimes i just wanna get a hug but other times im like hmm maybe if i give him a fat slap then he'll LISTEN TO ME
 private:
	list<WordEntry> *hashTable;
	// bool *occupiedTable;
	int size;

 public:
	HashTable(int);
	bool contains(const string &);
	double getAverage(const string &);
	void put(const string &, int);
 
 private:
	int computeHash(const string &);
};

#endif