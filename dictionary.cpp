#include "RBTree.h"
#include "AVLTree.h"
#include "console.h"
#include "HashTable.h"

enum TRANGTHAI { UP, DOWN, LEFT, RIGHT, ENTER, BACK, Null };

TRANGTHAI key(int z)
{
	if (z == 224) {
		char c = _getch();
		if (c == 72) return UP;
		if (c == 80) return DOWN;
		if (c == 75) return LEFT;
		if (c == 77) return RIGHT;
	}
	else if (z == 13) return ENTER;
	else if (z == 8) return BACK;

	return Null;
}

int main()
{
	FixConsoleWindow();
	//HideControl();
	string menu[3] = { "AVLTree", "RBTree", "HashTable" };
	int mau[3];
	mau[0] = 10;
	for (int i = 1; i < 3; i++) mau[i] = 15;
	int k = 1;
	system("cls");
	while (1)
	{
		GotoXY(50, 10);
		SetColor(9);
		cout << "DICTIONARY" << endl;
		for (int i = 1; i <= 3; i++)
		{
			GotoXY(50, 13 + i);
			SetColor(mau[i - 1]);
			cout << i << ". " << menu[i - 1];
		}
		int z = _getch();
		TRANGTHAI trangthai = key(z);
		switch (trangthai)
		{
		case UP:
			if (k == 1) k = 3;
			else --k;
			break;
		case DOWN:
			if (k == 3) k = 1;
			else k++;
			break;
		case ENTER:
			if (k == 1) AVL();
			if (k == 2) RB();
			if (k == 3) HashTB();
			SetColor(15);
			system("pause");
			return 0;
		}
		for (int i = 0; i < 3; i++) mau[i] = 15;
		mau[k - 1] = 10;
	}
}