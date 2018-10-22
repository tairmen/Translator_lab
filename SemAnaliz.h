#pragma once
#include "SyntaxAnaliz.h"

class SemAnaliz {
public:
	// ������� �����
	vector<string> LabelTable;
	// ������
	Node* Tree;
	string AsmCode;
	SemAnaliz(string filename);
	int LabelAnaliz(Node* root);
	void GodeGen(string filename);
};