#include <iostream>
#include <fstream>
#include <string>
#include "console.h"

using namespace std;

struct AVLTree
{
	string key;
	string sub;
	int h;
	AVLTree *TreeLeft;
	AVLTree *TreeRight;
};

void TurnLeft(AVLTree *&p);

void TurnRight(AVLTree *&p);

int Add(AVLTree *&p, string word, string wsub);

void Search(AVLTree *p, string word);

void Edit(AVLTree *p, string eword, string esub);

void Delete(AVLTree *p, string dword);

void ToFile(ofstream &f1, AVLTree *p);

void AVL();