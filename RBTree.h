#include <iostream>
#include <fstream>
#include <string>
#include "console.h"

using namespace std;

struct RBTree
{
	string key;
	string sub;
	int type;
	RBTree *TreeLeft, *TreeRight, *TreeParent;
};

RBTree *Uncle(RBTree *n, int &k);

void TurnLeft(RBTree *&RB, RBTree *&x);

void TurnRight(RBTree *&RB, RBTree *&x);

RBTree *uncle(RBTree *n);

void Add(RBTree *&RB, string key, string sub, RBTree *parent);

bool Insert(RBTree *&RB, RBTree *p, RBTree *parent);

void Search(RBTree *p, string word);

void Edit(RBTree *p, string eword, string esub);

void Delete(RBTree *p, string dword);

void ToFile(ofstream &f1, RBTree *p);

void RB();