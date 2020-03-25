#include "hashtable.h"

int Hash(string word)
{
	int k = 0;
	for (int i = 0; i < word.length(); i++) k = (k * m + word[i] + mod) % mod;
	return k;
}

void Add(Node **&HashTable, string word, string sub)
{ 
	int k = Hash(word);
	Node *q = new Node;
	q->word = word;
	q->sub = sub;
	q->next = NULL;
	if (HashTable[k] == NULL) HashTable[k] = q;
	else
	{
		Node *p = HashTable[k];
		while (p)
		{
			if (p->word == word) return;
			p = p->next;
		}
		p = q;
	}
}

void Search(Node **HashTable, string word)
{
	int k = Hash(word);
	Node *p = HashTable[k];
	while (p)
	{
		if (p->word == word)
		{
			cout << p->sub << endl;
			return;
		}
		p = p->next;
	}
	SetColor(12);
	cout << "Keyword don't exist!!!\n";
}

void Edit(Node **&HashTable, string word, string sub)
{
	int k = Hash(word);
	Node *p = HashTable[k];
	while (p)
	{
		if (p->word == word)
		{
			p->sub = sub;
			return;
		}
		p = p->next;
	}
	SetColor(12);
	cout << "Keyword don't exist!!!\n";
}

void Delete(Node **&HashTable, string word)
{
	int k = Hash(word);
	Node *p = HashTable[k];
	Node *prev = NULL;
	while (p)
	{
		if (p->word == word)
		{
			if (prev == NULL) HashTable[k] = p->next;
			else prev->next = p->next;
			return;
		}
		prev = p;
		p = p->next;
	}
	SetColor(12);
	cout << "Keyword don't exist!!!\n";
}

void ToFile(ofstream &f1, Node **HashTable)
{
	for (int i = 0; i < mod; i++)
	{
		Node *p = HashTable[i];
		while (p)
		{
			f1 << p->word << "  " << p->sub << endl;
			p = p->next;
		}
	}
}

void HashTB()
{
	system("cls");
	Node **HashTable;
	HashTable = new Node *[mod];
	for (int i = 0; i < mod; i++) HashTable[i] = NULL;
	fstream f;
	f.open("Dictionary.txt", ios::in);
	string word;
	SetColor(11);
	cout << "DICTIONARY IS LOADING...\n";
	while (!f.eof())
	{
		getline(f, word);
		int pos = word.find("  ");
		if (pos != -1)
			Add(HashTable, word.substr(0, pos), word.substr(pos + 2));
	}
	SetColor(10);
	cout << "ACCESS!!!\n";
	f.close();
	SetColor(6);
	cout << "Enter a keyword to search: ";
	string sword;
	SetColor(15);
	getline(cin, sword);
	Search(HashTable, sword);
	SetColor(6);
	cout << "Enter a keyword to add to the dictionary: ";
	string Key, Sub;
	SetColor(15);
	getline(cin, Key);
	SetColor(6);
	cout << "Enter the meaning of the keyword: ";
	SetColor(15);
	getline(cin, Sub);
	Add(HashTable, Key, Sub);
	SetColor(6);
	cout << "Enter a keyword to edit: ";
	string eword, esub;
	SetColor(15);
	getline(cin, eword);
	SetColor(6);
	cout << "Enter the meaning of the keyword: ";
	SetColor(15);
	getline(cin, esub);
	Edit(HashTable, eword, esub);
	SetColor(6);
	cout << "Enter a keyword to delete: ";
	string dword;
	SetColor(15);
	getline(cin, dword);
	Delete(HashTable, dword);
	SetColor(11);
	cout << "NEW DICTIONARY IS CREATING...\n";
	ofstream f1("NewDictionary.txt");
	ToFile(f1, HashTable);
	SetColor(10);
	cout << "ACCESS!!!\n";
	f1.close();
	delete[]HashTable;
}

