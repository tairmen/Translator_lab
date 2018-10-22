#include "LexAnaliz.h"
#include "SyntaxAnaliz.h"
#include "SemAnaliz.h"

int main()
{
	string FileName;
	cout << "This is translator of the part of SIGNAL programming language" << endl;
	cout << "Created by Tair Abduraimov" << endl;
	cout << "enter source filename: ";
	//cin >> FileName;
	FileName = "test2.sig";
	cout << endl;
	cout << "..." << endl;
	//LeksAnaliz LexAn;
	//LexAn.Analizator(FileName);
	//LexAn.MakeListing(FileName);
	//SyntaxAnaliz SyntAn(FileName);
	//SyntAn.TreeListing(FileName);
	SemAnaliz Sem(FileName);
	Sem.GodeGen(FileName);
	system("pause");
	return 0;
}