#pragma once
#include "SyntaxAnaliz.h"

class SemAnaliz {
public:
	// таблица меток
	vector<string> LabelTable;
	// дерево
	Node* Tree;
	string AsmCode;
	SemAnaliz(string filename);
	int LabelAnaliz(Node* root);
	void GodeGen(string filename);
};