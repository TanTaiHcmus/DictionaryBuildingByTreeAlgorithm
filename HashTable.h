#include <iostream>
#include <string>
#include <fstream>
#include "console.h"

using namespace std;

const int mod = 10000019;

const int m = 127;

struct Node
{
	string word;
	string sub;
	Node *next;
};

int Hash(string word);

void Add(Node **&HashTable, string word, string sub);

void Search(Node **HashTable, string word);

void Edit(Node **&HashTable, string word, string sub);

void Delete(Node **&HashTable, string word);

void ToFile(ofstream &f1, Node **HashTable);

void HashTB();