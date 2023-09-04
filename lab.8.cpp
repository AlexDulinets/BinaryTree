#define _USE
#include <iostream>
#include <cstdlib>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>
#include "BinaryTree.h"

using namespace std;

void menu()
{
	red();
	wcout << "\u2642\t#1.Enter tree manually\n";
	wprintf(L"\u5350\t#1.Enter tree manually\n");
	wcout << "\t#2.Generate random tree\n";
	wcout << "\t#3.Print tree\n";
	wcout << "\t#4.Delete item\n";
	wcout << "\t#5.Erase tree\n";
	wcout << "\t#6.Search item\n";
	wcout << "\t#7.Individual task #8\n";
	wcout << "\t#8.Height, depth, level\n";
	wcout << "\t#0.Exit\n";
	yellow();
	wcout << "\n";
	wcout << "        #";

}



int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	//setlocale(0, "ru");
	Tree NewTree;
	bool move = true;
	int action = 0, Size = 0, endOfDel = 0, temp = 0;
	while (move)
	{
		menu();
		cin >> action;
		wcout << "\n";
		switch (action)
		{
		case 1:
			wcout << "Enter the number of items you want to add: \n";
			cin >> Size;
			wcout << "Enter your items: \n";
			for (int i = 0; i < Size; i++)
			{
				cin >> temp;
				NewTree.AddLeaf(temp);
			}
			wcout << "Elements was added successfully \n";
			break;
		case 2:
			wcout << "Enter the number of items you want to add: \n";
			cin >> Size;
			for (int i = 0; i < Size; i++)
			{
				NewTree.AddLeaf(rand() % 200 - 50);
			}
			wcout << "Elements was added successfully \n";
			break;
		case 3:
			wcout << "Print in order:  ";//симметричный
			NewTree.PrintInOrder();
			wcout << endl;
			wcout << "Print pre order: ";//прямой
			NewTree.PrintPreOrder();
			wcout << endl;
			wcout << "Print post order: ";//в обратном
			NewTree.PrintPostOrder();
			wcout << endl;
			wcout << "Tree:\n";
			NewTree.ColorPrint();
			wcout << endl;
			break;
		case 4:
			wcout << "Enter the item you want to delete: \n";
			cin >> endOfDel;
			NewTree.RemoveNode(endOfDel);
			break;
		case 5:
			endOfDel = NewTree.ReturnRootKey();
			while (endOfDel != -1000) {
				NewTree.RemoveNode(endOfDel);
				endOfDel = NewTree.ReturnRootKey();
			}
			break;
		case 6:
			wcout << "Enter the items for search: \n";
			cin >> temp;
			if (NewTree.FindItem(temp) != -1000)wcout << NewTree.FindItem(temp);
			break;
		case 7:
			NewTree.IndTask();
			break;
		case 8:
			NewTree.HeightDepthLevel();

			break;
		case 0:
			red();
			move = false;
			break;
		}
	}
	return 0;
}