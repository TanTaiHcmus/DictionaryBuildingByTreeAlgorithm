#include "RBTree.h"

RBTree *Uncle(RBTree *n, int &k)
{
	if (n->TreeParent == n->TreeParent->TreeParent->TreeLeft)
	{
		k = 0;
		return n->TreeParent->TreeParent->TreeRight;
	}
	else
	{
		k = 1;
		return n->TreeParent->TreeParent->TreeLeft;
	}
}

void TurnLeft(RBTree *&RB, RBTree *&x)
{
	RBTree *y = x->TreeRight;
	x->TreeRight = y->TreeLeft;
	if (y->TreeLeft != NULL)
		y->TreeLeft->TreeParent = x;
	if (x->TreeParent != NULL)
	{
		if (x->TreeParent->TreeLeft == x)
			x->TreeParent->TreeLeft = y;
		else
			x->TreeParent->TreeRight = y;
	}
	else RB = y;
	y->TreeLeft = x;
	y->TreeParent = x->TreeParent;
	y->TreeLeft->TreeParent = y;
}

void TurnRight(RBTree *&RB, RBTree *&x)
{
	RBTree *y = x->TreeLeft;
	x->TreeLeft = y->TreeRight;
	if (y->TreeRight != NULL)
		y->TreeRight->TreeParent = x;
	if (x->TreeParent != NULL)
	{
		if (x->TreeParent->TreeLeft == x)
			x->TreeParent->TreeLeft = y;
		else
			x->TreeParent->TreeRight = y;
	}
	else RB = y;
	y->TreeRight = x;
	y->TreeParent = x->TreeParent;
	y->TreeRight->TreeParent = y;
}

bool Insert(RBTree *&RB, RBTree *p, RBTree *parent)
{
	if (RB)
	{
		if (p->key == RB->key) return false;
		else if (p->key < RB->key)
		{
			return(Insert(RB->TreeLeft, p, RB));
		}
		else
		{
			return(Insert(RB->TreeRight, p, RB));
		}
	}
	else
	{
		RB = p;
		RB->TreeParent = parent;
		return true;
	}
}

void Add(RBTree *&RB, string word, string sub, RBTree *parent)
{
	RBTree *p = new RBTree;
	p->key = word;
	p->sub = sub;
	p->type = 1;
	p->TreeLeft = p->TreeRight = NULL;
	bool k = Insert(RB, p, parent);
	if (k == true)
	{
		while (p != RB && p->TreeParent->type == 1)
		{
			int k;
			RBTree *uncle = Uncle(p, k);
			if (uncle != NULL && uncle->type == 1)
			{
				p->TreeParent->type == 0;
				uncle->type = 0;
				p->TreeParent->TreeParent->type = 1;
				p = p->TreeParent->TreeParent;
			}
			else
			{
				if (k == 0)
				{
					if (p == p->TreeParent->TreeRight)
					{
						p = p->TreeParent;
						TurnLeft(RB, p);
					}
					p->TreeParent->type = 0;
					p->TreeParent->TreeParent->type = 1;
					TurnRight(RB, p->TreeParent->TreeParent);
				}
				else
				{
					if (p == p->TreeParent->TreeLeft)
					{
						p = p->TreeParent;
						TurnRight(RB, p);
					}
					p->TreeParent->type = 0;
					p->TreeParent->TreeParent->type = 1;
					TurnLeft(RB, p->TreeParent->TreeParent);
				}
			}
		}
		RB->type = 0;
	}
}

void Search(RBTree *p, string word)
{
	if (p)
	{
		if (p->key == word) cout << p->sub << endl;
		else if (p->key < word) Search(p->TreeRight, word);
		else Search(p->TreeLeft, word);
	}
	else cout << "Keyword don't exist!!!\n";
}

void Edit(RBTree *p, string eword, string esub)
{
	if (p)
	{
		if (p->key == eword) p->sub = esub;
		else if (p->key < eword) Edit(p->TreeRight, eword, esub);
		else Edit(p->TreeLeft, eword, esub);
	}
	else cout << "Keyword don't exist!!!\n";
}

void Delete(RBTree *p, string dword)
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
	else cout << "Keyword don't exist!!!\n";
}

void ToFile(ofstream &f1, RBTree *p)
{
	if (p->TreeLeft) ToFile(f1, p->TreeLeft);
	if (p->key != "") f1 << p->key << "  " << p->sub << endl;
	if (p->TreeRight) ToFile(f1, p->TreeRight);
}

void RB()
{
	system("cls");
	RBTree *RB = NULL;
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
			Add(RB, word.substr(0, pos), word.substr(pos + 2), NULL);
	}
	SetColor(10);
	cout << "ACCESS!!!\n";
	f.close();
	SetColor(6);
	cout << "Enter a keyword to search: ";
	string sword;
	SetColor(15);
	getline(cin, sword);
	Search(RB, sword);
	SetColor(6);
	cout << "Enter a keyword to add to the dictionary: ";
	string Key, Sub;
	SetColor(15);
	getline(cin, Key);
	SetColor(6);
	cout << "Enter the meaning of the keyword: ";
	SetColor(15);
	getline(cin, Sub);
	Add(RB, Key, Sub, NULL);
	SetColor(6);
	cout << "Enter a keyword to edit: ";
	string eword, esub;
	SetColor(15);
	getline(cin, eword);
	SetColor(6);
	cout << "Enter the meaning of the keyword: ";
	SetColor(15);
	getline(cin, esub);
	Edit(RB, eword, esub);
	SetColor(6);
	cout << "Enter a keyword to delete: ";
	string dword;
	SetColor(15);
	getline(cin, dword);
	Delete(RB, dword);
	SetColor(11);
	cout << "NEW DICTIONARY IS CREATING...\n";
	ofstream f1("NewDictionary.txt");
	ToFile(f1, RB);
	SetColor(10);
	cout << "ACCESS!!!\n";
	f1.close();
}