#include "SemAnaliz.h"

SemAnaliz::SemAnaliz(string filename) {
	SyntaxAnaliz SynAn(filename);
	Tree = SynAn.Tree;
	AsmCode = "";
}

int SemAnaliz::LabelAnaliz(Node* root) {
	if (root->Func == "LABELDECL()") {
		root = root->Down;
		if (root->Func != "EMPTY()") {
			root = root->Next;
			string lb = root->Down->Name;
			LabelTable.push_back(lb);
			root = root->Next;
			root = root->Down;
			while (root->Func != "EMPTY()") {
				root = root->Next;
				lb = root->Down->Name;
				for (int i = 0; i < LabelTable.size(); i++) {
					if (lb == LabelTable[i]) {
						return 1;
					}
				}
				LabelTable.push_back(lb);
				root = root->Next;
				root = root->Down;
			}
			return 0;
		}
		return 0;
	}
	return 0;
}

void SemAnaliz::GodeGen(string filename) {
	AsmCode += ".code\n";
	Tree = Tree->Down;
	if (Tree->Name == "PROCEDURE") {
		string procid = Tree->Next->Down->Name;
		AsmCode += procid + " proc\n";
		AsmCode += procid + " endp\n";
	}
	while (Tree->Func != "BLOCK()") {
		Tree = Tree->Next;
	}
	if (LabelAnaliz(Tree->Down->Down) == 1) {
		cout << "Semantic error" << endl;
		return;
	}

	for (int i = 0; i < LabelTable.size(); i++) {
		AsmCode += "@" + LabelTable[i] + ":\n";
	}
	AsmCode += "BEGIN:\n";
	AsmCode += "END BEGIN";

	filename = filename + ".lst";
	fstream f;
	f.open(filename, std::ios::app);
	f << AsmCode;
	cout << "asm code was generated" << endl;
}