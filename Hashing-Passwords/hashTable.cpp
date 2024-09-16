#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "hashTable.h"
using std::string;
using std::cout;

hashTable::hashTable(int size)
{
	//you need to add everything else that belongs in the constructor--------------------------------------
	tableSize = size;
	hashArray = new entry*[tableSize];
	for (int i = 0; i < tableSize; i++)
	{
		hashArray[i] = nullptr;
	}
	srand (time(0));	//this needs to be in the constructor, otherwise every user gets the same salt
}

//don't touch this!
int hashTable::hash(string key)
{
	int sum = 0;
	for(int i = 0; i < key.size(); i++)
		sum += key[i];
	
	return sum % tableSize;
}

//don't touch this!
string hashTable::generateSalt()
{
	string s = "";
	
	for(int i = 0; i < tableSize; i++)
		s = s + char('!' + (rand() % 93));
	return s;
}