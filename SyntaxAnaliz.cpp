#include "SyntaxAnaliz.h"

SyntaxAnaliz::SyntaxAnaliz(string FileName)
{
	//FuncCounter = 0;
	ErrorStr = "";
	ErrorCounter = 0;
	Pos = 0;
	LeksAnaliz LexAn;
	LexAn.Analizator(FileName);
	LexAn.MakeListing(FileName);
	IdentMin = LexAn.MinIdent;
	ConstMin = LexAn.MinConst;
	ConstMax = LexAn.ConstMax;
	Lexems = LexAn.Lexems;
	IdentTable = LexAn.TableC;
	ConstTable = LexAn.Table;
	InitKnut();
	START();
	if (ErrorCounter == 0) {
		cout << "syntax analysis completed successfully" << endl;
	}
}

bool SyntaxAnaliz::START()
{
	Tree = InitTree();
	return PROG(Tree);
}

bool SyntaxAnaliz::PROG(Node* NodePtr)
{
	Node* N = NodePtr;
	if (Pos >= Lexems.size()) { 
		Errors(1, Pos);
		return false;
	}
	if (Lexems[Pos].Code == 402) {
		N->Down = AddNode(N, 1, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Standart identifier", "", true);
		N = N->Down;
		Pos++;
		if (Pos >= Lexems.size()) {
			Errors(1, Pos);
			return false;
		}
		N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "PROCIDNT()", false);
		N = N->Next;
		if (PROCIDNT(N)){
			Pos++;
		}
		else{
			return false;
		}
		if (Lexems[Pos].Code == 59){
			N->Next = AddNode(N, 0, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Separator", "", true);
			Pos++;
			N = N->Next;
			N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "BLOCK()", false);
			N = N->Next;
		}
		else{
			Errors(2, Pos);
			return false;
		}
		if (Pos >= Lexems.size()) {
			Errors(1, Pos);
			return false;
		}
		if (BLOCK(N)){
			Pos++;
		}
		else{
			return false;
		}
		if (Pos >= Lexems.size()) {
			Errors(1, Pos);
			return false;
		}
		if ((Pos < Lexems.size()) && (Lexems[Pos].Code == 46)){
			N->Next = AddNode(N, 0, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Separator", "", true);
			return true;
		}
		else
		{
			Errors(3, Pos);
			return false;
		}
	}
	if (Lexems[Pos].Code == 401) {
		N->Down = AddNode(N, 1, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Standart identifier", "", true);
		N = N->Down;
		Pos++;
		if (Pos >= Lexems.size()) {
			Errors(1, Pos);
			return false;
		}
		N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "PROCIDNT()", false);
		N = N->Next;
		if (PROCIDNT(N)) {
			Pos++;
			N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "PARAMS()", false);
			N = N->Next;
		}
		else{
			return false;
		}
		if (PARAMS(N)) {
			//Pos = ResPos;			
		}
		else{
			return false;
		}
		if (Lexems[Pos].Code == 59) {
			N->Next = AddNode(N, 0, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Separator", "", true);
			Pos++;
			N = N->Next;
			N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "BLOCK()", false);
			N = N->Next;
		}
		else {
			Errors(2, Pos);
			return false;
		}
		if (Pos >= Lexems.size()) {
			Errors(1, Pos);
			return false;
		}
		if (BLOCK(N)) {
			Pos++;
		}
		else {
			return false;
		}
		if (Pos >= Lexems.size()) {
			Errors(1, Pos);
			return false;
		}
		if ((Pos < Lexems.size()) && (Lexems[Pos].Code == 59)) {
			N->Next = AddNode(N, 0, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Separator", "", true);
			return true;
		}
		else {
			Errors(2, Pos);
			return false;
		}
	}
	else{
		Errors(5, Pos);
		return false;
	}
}

bool SyntaxAnaliz::BLOCK(Node* NodePtr)
{
	if (Pos >= Lexems.size()) { 
		Errors(1, Pos);
		return false; 
	}
	//Lex Help = Lexems[Pos];
	//int HelpPos = Pos;
	Node* N = NodePtr;
	N->Down = AddNode(N, 1, -1, "", -1, -1, "Procedure", "DECLARATION()", false);
	// переход на уровень вниз
	N = N->Down;
	if (DECLARATION(N))
	{
		//Pos = ResPos;
	}
	else
	{
		//ResPos = HelpPos;
		return false;
	}
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	if (Lexems[Pos].Code == 404)
	{
		N->Next = AddNode(N, 0, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Standart Identifier", "", true);
		N = N->Next;
		Pos++;
		N->Next = AddNode(N, 1, -1, "", -1, -1, "Procedure", "STATMLIST()", false);
		N = N->Next;
	}
	else
	{
		Errors(8, Pos);
		//ResPos = HelpPos;
		return false;
	}
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	if (STATMLIST(N)) {
		
	}
	else return false;
	if (Lexems[Pos].Code == 405)
	{
		N->Next = AddNode(N, 0, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Standart Identifier", "", true);
		//ResPos = Pos;
		return true;
	}
	else
	{
		Errors(9, Pos);
		//ResPos = HelpPos;
		return false;
	}
}

bool SyntaxAnaliz::PROCIDNT(Node* NodePtr) {
	if (Pos >= Lexems.size()) { 
		Errors(1, Pos);
		return false; 
	}
	//int HelpPos = Pos;
	if (Lexems[Pos].Code >= IdentMin)
	{
		Node* N = NodePtr;
		N->Down = AddNode(N, 1, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Identifier", "", true);
		return true;
	}
	else
	{
		Errors(6, Pos);
		return false;
	}
}

bool SyntaxAnaliz::PARAMS(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	if (Lexems[Pos].Code == 40) {
		N->Down = AddNode(N, 1, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "delimiter", "", true);
		N = N->Down;
		N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "DECLIST()", false);
		N = N->Next;
		Pos++;
	}
	else {
		N->Down = AddNode(N, 0, -1, "", -1, -1, "Procedure", "EMPTY()", false);
		return true;
	}
	if (DECLIST(N)) {
	}
	else { 
		return false;
	}
	if (Lexems[Pos].Code == 41) {
		N->Next = AddNode(N, 1, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "delimiter", "", true);
		Pos++;
		return true;
	}
	else {
		Errors(7, Pos);
		return false;
	}
}

bool SyntaxAnaliz::DECLIST(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	if (DECL(N)) {
		// Pos++;
		N->Down->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "DECLIST()", false);
		N = N->Down->Next;
	}
	else {
		N->Down = AddNode(N, 0, -1, "", -1, -1, "Procedure", "EMPTY()", false);
		return true;
	}
	if (DECLISTING(N)) {
		return true;
	}
	else {
		return false; 
	}
}

bool SyntaxAnaliz::DECLISTING(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	if (Lexems[Pos].Code == ';') {
		//Pos++;
		N->Next = AddNode(N, 1, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "delimiter", "", true);
		Pos++;
	}
	else {
		N->Down = AddNode(N, 0, -1, "", -1, -1, "Procedure", "EMPTY()", false);
		return true;
	}
	if (DECL(N)) {
		// Pos++;
		N->Down->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "DECLIST()", false);
		N = N->Down->Next;
	}
	else {
		return false;
	}
	if (DECLISTING(N)) {
		return true;
	}
	else {
		return false;
	}
}

bool SyntaxAnaliz::DECL(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	if (Lexems[Pos].Code == 41) {
		return false;
	}
	N->Down = AddNode(N, 1, -1, "", -1, -1, "Procedure", "LABELLIST()", false);
	if (LABELLIST1(N->Down)){
	}
	else {
		N->Down = AddNode(N, 0, -1, "", -1, -1, "Procedure", "DECL()", false);
		N = N->Down;
		N->Down = AddNode(N, 0, -1, "", -1, -1, "Procedure", "IDENT()", false);
		N = N->Down;
		if (PROCIDNT(N)) {
			Pos++;
		}
		else return false;
		if (Lexems[Pos].Code == 58) {
			N->Next = AddNode(N, 1, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "delimiter", "", true);
			N = N->Next;
			N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "ATTRLIST()", false);
			N = N->Next;
			Pos++;
		}
		else {
			return false;
		}
		if (ATTRLIST(N)) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool SyntaxAnaliz::ATTRLIST(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	N->Down = AddNode(N, 0, -1, "", -1, -1, "Procedure", "ATTR()", false);
	N = N->Down;
	if (ATTR(N)) {
		Pos++;
		N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "ATTRLIST()", false);
		N = N->Next;
	}
	else {
		N->Func = "EMPTY()";
		return true;
	}
	if (ATTRLIST(N)) {
		return true;
	}
	else {
		return false;
	}
}

bool SyntaxAnaliz::ATTR(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	if (Lexems[Pos].Code >= ConstMin) {
		N->Down = AddNode(N, 1, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "attribute", "", true);
		N = N->Down;
		return true;
	}
	else {
		return false;
	}
}

bool SyntaxAnaliz::DECLARATION(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	N->Down = AddNode(N, 0, -1, "", -1, -1, "Procedure", "LABELDECL()", false);
	N = N->Down;
	if (LABELDECL(N)) {
		return true;
	}
	else return false;
}

bool SyntaxAnaliz::STATMLIST(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	N->Down = AddNode(N, 0, -1, "", -1, -1, "Procedure", "EMPTY()", false);
	return true;
}

bool SyntaxAnaliz::LABELDECL(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	if (Lexems[Pos].Code == 403) {
		N->Down = AddNode(N, 0, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Standart Identifier", "", true);
		N = N->Down;
		N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "CONST()", false);
		N = N->Next;
		Pos++;
	}
	else {
		N->Down = AddNode(N, 0, -1, "", -1, -1, "Procedure", "EMPTY()", false);
		return true;
	}
	if (CONST(N)) {
		N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "LABELLIST()", false);
		N = N->Next;
		Pos++;
	}
	else return false;
	if (LABELLIST(N)) {
	}
	else return false;
	if ((Pos < Lexems.size()) && (Lexems[Pos].Code == 59)) {
		N->Next = AddNode(N, 0, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Separator", "", true);
		Pos++;
		return true;
	}
	else {
		Errors(2, Pos);
		return false;
	}
}

bool SyntaxAnaliz::CONST(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	if ((Lexems[Pos].Code >= ConstMin) && (Lexems[Pos].Code <= ConstMax))
	{
		Node* N = NodePtr;
		N->Down = AddNode(N, 1, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "Const", "", true);
		N = N->Down;
		return true;
	}
	else
	{
		Errors(10, Pos);
		return false;
	}
}

bool SyntaxAnaliz::LABELLIST(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	if (Lexems[Pos].Code == 44) {
		N->Down = AddNode(N, 1, Lexems[Pos].Code, Lexems[Pos].Name, Lexems[Pos].Line, Lexems[Pos].Column, "delimiter", "", true);
		N = N->Down;
		N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "CONST()", false);
		N = N->Next;
		Pos++;
	}
	else {
		N->Down = AddNode(N, 0, -1, "", -1, -1, "Procedure", "EMPTY()", false);
		return true;
	};
	if (CONST(N)) {
		N->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "LABELLIST()", false);
		N = N->Next;
		Pos++;
	}
	else return false;
	if (LABELLIST(N)) {

	}
	else return false;
}

bool SyntaxAnaliz::LABELLIST1(Node* NodePtr) {
	if (Pos >= Lexems.size()) {
		Errors(1, Pos);
		return false;
	}
	Node* N = NodePtr;
	if (CONST(N)) {
		N->Down->Next = AddNode(N, 0, -1, "", -1, -1, "Procedure", "LABELLIST()", false);
		N = N->Down->Next;
		Pos++;
	}
	else return false;
	if (LABELLIST(N)) {

	}
	else { 
		return false;
	}
}

void SyntaxAnaliz::Errors(int p, int pos) {
	switch (p) {
	case 1:
		cout << "Syntactic error: Unexpected end of the file!" << endl;
		ErrorStr += "Syntactic error: Unexpected end of the file!";
		ErrorCounter++;
		break;
	case 2:
		cout << "Syntactic error on Line " << Lexems[pos].Line << " Column " << Lexems[pos].Column << ": \";\" is passed" << endl;
		ErrorStr += "Syntactic error on Line ";
		ErrorStr += to_string(Lexems[pos].Line);
		ErrorStr += " Column ";
		ErrorStr += to_string(Lexems[pos].Column);
		ErrorStr += ": \";\" is passed";
		ErrorCounter++;
		break;
	case 3:
		cout << "Syntactic error on Line " << Lexems[pos].Line << " Column " << Lexems[pos].Column << ": \".\" is passed" << endl;
		ErrorStr += "Syntactic error on Line ";
		ErrorStr += to_string(Lexems[pos].Line);
		ErrorStr += " Column ";
		ErrorStr += to_string(Lexems[pos].Column);
		ErrorStr += ": \".\" is passed";
		ErrorCounter++;
		break;
	//case 4:
	//	cout << "Syntactic error: \".\" is passed after the \"END\"" << endl;
	//	break;
	case 5:
		cout << "Syntactic error on Line " << Lexems[pos].Line << " Column " << Lexems[pos].Column << ": Keyword \"PROGRAM\" is passed" << endl;
		ErrorStr += "Syntactic error on Line ";
		ErrorStr += to_string(Lexems[pos].Line);
		ErrorStr += " Column ";
		ErrorStr += to_string(Lexems[pos].Column);
		ErrorStr += ": Keyword \"PROGRAM\" is passed";
		ErrorCounter++;
		break;
	case 6:
		cout << "Syntactic error on Line " << Lexems[pos].Line << " Column " << Lexems[pos].Column << ": Must be procedure identifier" << endl;
		ErrorStr += "Syntactic error on Line ";
		ErrorStr += to_string(Lexems[pos].Line);
		ErrorStr += " Column ";
		ErrorStr += to_string(Lexems[pos].Column);
		ErrorStr += ": Must be procedure identifier";
		ErrorCounter++;
		ErrorCounter++;
		break;
	case 7:
		cout << "Syntactic error on Line " << Lexems[pos].Line << " Column " << Lexems[pos].Column << ": \")\" is passed" << endl;
		ErrorStr += "Syntactic error on Line ";
		ErrorStr += to_string(Lexems[pos].Line);
		ErrorStr += " Column ";
		ErrorStr += to_string(Lexems[pos].Column);
		ErrorStr += ": \")\" is passed";
		ErrorCounter++;
		break;
	case 8:
		cout << "Syntactic error on Line " << Lexems[pos].Line << " Column " << Lexems[pos].Column << ": Keyword \"BEGIN\" is passed" << endl;
		ErrorStr += "Syntactic error on Line ";
		ErrorStr += to_string(Lexems[pos].Line);
		ErrorStr += " Column ";
		ErrorStr += to_string(Lexems[pos].Column);
		ErrorStr += ": Keyword \"BEGIN\" is passed";
		ErrorCounter++;
		break;
	case 9:
		cout << "Syntactic error on Line " << Lexems[pos].Line << " Column " << Lexems[pos].Column << ": Keyword \"END\" is passed" << endl;
		ErrorStr += "Syntactic error on Line ";
		ErrorStr += to_string(Lexems[pos].Line);
		ErrorStr += " Column ";
		ErrorStr += to_string(Lexems[pos].Column);
		ErrorStr += ": Keyword \"END\" is passed";
		ErrorCounter++;
		break;
	/*case 10:
		cout << "Syntactic error on Line " << Lexems[pos].Line << " Column " << Lexems[pos].Column << ": Must be constant" << endl;
		ErrorStr += "Syntactic error on Line ";
		ErrorStr += to_string(Lexems[pos].Line);
		ErrorStr += " Column ";
		ErrorStr += to_string(Lexems[pos].Column);
		ErrorStr += ": Must be constant";
		ErrorCounter++;
		break;*/
	}
}

Node* SyntaxAnaliz::InitTree()
{
	Node* Help = new Node;
	Help->Code = -1;
	Help->Column = -1;
	Help->Down = NULL;
	Help->Info = "";
	Help->IsTerminal = false;
	Help->Line = -1;
	Help->Name = "";
	Help->Next = NULL;
	Help->Func = "PROG()";
	return Help;
}

Node* SyntaxAnaliz::AddNode(Node* Nd, int dirrection, int code, string name, int line, int column, string info, string Func, bool isterminal)
{
	Node* Help = new Node;
	Help->Code = code;
	Help->Column = column;
	Help->Down = NULL;
	Help->Info = "";
	Help->IsTerminal = isterminal;
	Help->Line = line;
	Help->Name = name;
	Help->Next = NULL;
	if (!dirrection)
	{
		Help->Down = NULL;
	}
	else
	{
		Help->Down = NULL;
	}
	Help->Func = new char[255]; 
	Help->Func = Func;
	return Help;
}

Node* SyntaxAnaliz::RemoveNode(Node* N)
{
	if (N != NULL) free(N);
	return NULL;
}

void SyntaxAnaliz::WriteTree(Node* Root, string sps)
{
	while (Root != NULL)
	{
		if (Root->IsTerminal)
		{
			TreeStr += sps + "'" + Root->Name + "'" + "\n";
		}
		else
		{
			TreeStr += sps + Root->Func + "\n";
		}
		if (Root->Down != NULL) {
			for (int i = 0; i < 6; i++) {
				sps.push_back(' ');
			}
			WriteTree(Root->Down, sps);
			for (int i = 0; i < 6; i++) {
				sps.pop_back();
			}
		}
		Root = Root->Next;
	}
}

void SyntaxAnaliz::TreeListing(string FileName) {
	TreeStr = "";
	FileName = FileName + ".lst";
	fstream f;
	f.open(FileName, std::ios::app);
	if (ErrorCounter > 0) {
		f << ErrorStr << endl;
	}
	else {
		WriteTree(Tree, "");
		f << TreeStr << endl;
	}
}

void SyntaxAnaliz::InitKnut() {
	Knut = {
	{-1, 1, -1},
	{402, 0, 6},
	{-12, 0, -1},
	{59, 0, -1},
	{-18, 0, -1},
	{46, 1, -1},
	{401, 0, -1},
	{-12, 0, -1},
	{-13, 0, -1},
	{59, 0, -1},
	{-18, 0, -1},
	{59, 1, -1},
	{1001, 1, -1},
	{40, 0, 16},
	{-17, 0, -1},
	{41, 1, -1},
	{0, 1, 1},
	{0, 1, 1},
	{-22, 0, -1},
	{404, 0, -1},
	{-31, 0, -1},
	{405, 1, -1},
	{-23, 1, -1},
	{403, 0, 26},
	{501, 0, -1},
	{27, 1, -1},
	{0, 1, 1},
	{44, 0, 30},
	{501, 0, -1},
	{-27, 1, -1},
	{0, 1, 1},
	{0, 1, 1}
	};
}

void SyntaxAnaliz::KnutMachine() {

}