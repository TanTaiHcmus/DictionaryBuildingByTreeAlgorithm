#include "AVLTree.h"

void TurnLeft(AVLTree *&p)
{
	AVLTree *q = p->TreeRight;
	AVLTree *tmp = q;
	if (q->h == 1)
	{
		tmp = q->TreeLeft;
		q->TreeLeft = tmp->TreeRight;
		tmp->TreeRight = q;
	}
	p->TreeRight = tmp->TreeLeft;
	tmp->TreeLeft = p;
	p = tmp;
	if (tmp == q)
	{
		if (p->TreeLeft) p->TreeLeft->h = 0;
		if (p->TreeRight) p->TreeRight->h = 0;
	}
	else
	{
		switch (p->h)
		{
		case 0:
			if (p->TreeLeft) p->TreeLeft->h = 0;
			if (p->TreeRight) p->TreeRight->h = 0;
			break;
		case 1:
			if (p->TreeLeft) p->TreeLeft->h = 0;
			if (p->TreeRight) p->TreeRight->h = -1;
			break;
		case -1:
			if (p->TreeLeft) p->TreeLeft->h = 1;
			if (p->TreeRight) p->TreeRight->h = 0;
			break;
		}
	}
	p->h = 0;
}

void TurnRight(AVLTree *&p)
{
	AVLTree *q = p->TreeLeft;
	AVLTree *tmp = q;
	if (q->h == -1)
	{
		tmp = q->TreeRight;
		q->TreeRight = tmp->TreeLeft;
		tmp->TreeLeft = q;
	}
	p->TreeLeft = tmp->TreeRight;
	tmp->TreeRight = p;
	p = tmp;
	if (tmp == q)
	{
		if (p->TreeLeft) p->TreeLeft->h = 0;
		if (p->TreeRight) p->TreeRight->h = 0;
	}
	else
	{
		switch (p->h)
		{
		case 0:
			if (p->TreeLeft) p->TreeLeft->h = 0;
			if (p->TreeRight) p->TreeRight->h = 0;
			break;
		case 1:
			if (p->TreeLeft) p->TreeLeft->h = 0;
			if (p->TreeRight) p->TreeRight->h = -1;
			break;
		case -1:
			if (p->TreeLeft) p->TreeLeft->h = 1;
			if (p->TreeRight) p->TreeRight->h = 0;
			break;
		}
	}
	p->h = 0;
}

int Add(AVLTree *&p, string word, string wsub)
{
	int k;
	if (p)
	{
		if (word == p->key) return -1;
		if (word < p->key)
		{
			k = Add(p->TreeLeft, word, wsub);
			if (k == 1)
			{
				switch (p->h)
				{
				case 0: p->h = 1; return 1;
				case -1: p->h = 0; return 0;
				case 1: TurnRight(p); return 0;
				}
			}
		}
		else
		{
			k = Add(p->TreeRight, word, wsub);
			if (k == 1)
			{
				switch (p->h)
				{
				case 0: p->h = -1; return 1;
				case 1: p->h = 0; return 0;
				case -1: TurnLeft(p); return 0;
				}
			}
		}
	}
	else
	{
		p = new AVLTree;
		if (p == NULL)
			return -1;
		p->key = word;
		p->sub = wsub;
		p->h = 0;
		p->TreeLeft = p->TreeRight = NULL;
		return 1;
	}
}

void Search(AVLTree *p, string word)
{
	if (p)
	{
		if (p->key == word) cout << p->sub << endl;
		else if (p->key < word) Search(p->TreeRight, word);
		else Search(p->TreeLeft, word);
	}
	else
	{
		SetColor(12);
		cout << "Keyword don't exist!!!\n";
	}
}

void Edit(AVLTree *p, string eword, string esub)
{
	if (p)
	{
		if (p->key == eword) p->sub = esub;
		else if (p->key < eword) Edit(p->TreeRight, eword, esub);
		else Edit(p->TreeLeft, eword, esub);
	}
	else
	{
		SetColor(12);
		cout << "Keyword don't exist!!!\n";
	}
}

void Delete(AVLTree *p, string dword)
{
	if (p)
	{
		if (p->key == dword)
		{
			p->key = "";
			p->sub = "";
		}
		else if (p->key < dword) Delete(p->TreeRight, dword);
		else Delete(p->TreeLeft, dword);
	}
	else
	{
		SetColor(12);
		cout << "Keyword don't exist!!!\n";
	}
}

void ToFile(ofstream &f1, AVLTree *p)
{
	if (p->TreeLeft) ToFile(f1, p->TreeLeft);
	if (p->key != "") f1 << p->key << "  " << p->sub << endl;
	if (p->TreeRight) ToFile(f1, p->TreeRight);
}

void AVL()
{
	system("cls");
	AVLTree *AVL = NULL;
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
			Add(AVL, word.substr(0, pos), word.substr(pos + 2));
	}
	SetColor(10);
	cout << "ACCESS!!!\n";
	f.close();
	SetColor(6);
	cout << "Enter a keyword to search: ";
	string sword;
	SetColor(15);
	getline(cin, sword);
	Search(AVL, sword);
	SetColor(6);
	cout << "Enter a keyword to add to the dictionary: ";
	string Key, Sub;
	SetColor(15);
	getline(cin, Key);
	SetColor(6);
	cout << "Enter the meaning of the keyword: ";
	SetColor(15);
	getline(cin, Sub);
	Add(AVL, Key, Sub);
	SetColor(6);
	cout << "Enter a keyword to edit: ";
	string eword, esub;
	SetColor(15);
	getline(cin, eword);
	SetColor(6);
	cout << "Enter the meaning of the keyword: ";
	SetColor(15);
	getline(cin, esub);
	Edit(AVL, eword, esub);
	SetColor(6);
	cout << "Enter a keyword to delete: ";
	string dword;
	SetColor(15);
	getline(cin, dword);
	Delete(AVL, dword);
	SetColor(11);
	cout << "NEW DICTIONARY IS CREATING...\n";
	ofstream f1("NewDictionary.txt");
	ToFile(f1, AVL);
	SetColor(10);
	cout << "ACCESS!!!\n";
	f1.close();
}