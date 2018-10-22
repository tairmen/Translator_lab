#pragma once
#include "LexAnaliz.h"

//узел дерева разбора программы
struct Node
{
	int Code;// код терминала
	string Name; // название терминала
	int Line; // строка терминала в коде
	int Column; // столбец терминала в коде
	string Info; // информаци€ про элемент узла
	string Func; // функци€ даного узла 
	bool IsTerminal; // флаг определ€ющий чем €вл€етс€ элемент узла, терминалом, или нетерминалом
	Node* Next; // указатель на следующий на текущем уровне дерева узел
	Node* Down; // указатель на узел нижнего уровн€
};

struct KnutEl {
	int Op;
	int AT;
	int AF;
};

//класс реализующий синтаксический анализатор
class SyntaxAnaliz
{
public:
	//указатель на вершину дерева разбора
	Node * Tree;
	//таблица идентиффикаторов сгенерированых лексическим анализатором
	vector<Lex> Lexems;
	// машина  нута
	vector<KnutEl> Knut;
	//текуща€ лексема
	int Pos;
	int LevelCounter;
	int IdentMin;
	int ConstMin;
	int ConstMax;
	vector<string> IdentTable;
	vector<string> ConstTable;
	//—чЄтчик ошибок
	int ErrorCounter;
	//конструктор
	SyntaxAnaliz(string FileName);
	//инициализаци€ дерева
	Node* InitTree();
	//добавление узла в дерево
	Node* AddNode(Node* Nd, int dirrection, int code, string Name, int line, int column, string info, string Func, bool isterminal);
	//удаление указанного узла
	Node* RemoveNode(Node* N);
	//процедура вывода дерева
	void WriteTree(Node* Root, string sps);
	string TreeStr;
	string ErrorStr;
	//текст дерева в файл
	void TreeListing(string FileName);
	//вывод ошибок
	void Errors(int p, int pos);
	void InitKnut();
	void KnutMachine();
	//процедуры синтаксического анализатора заданной грамматики
	bool START();
	bool PROG(Node* NodePtr);
	bool BLOCK(Node* NodePtr);
	bool PARAMS(Node* NodePtr);
	bool DECLARATION(Node* NodePtr);
	bool DECL(Node* NodePtr);
	bool ATTRLIST(Node* NodePtr);
	bool ATTR(Node* NodePtr);
	bool DECLIST(Node* NodePtr);
	bool DECLISTING(Node* NodePtr);
	bool STATMLIST(Node* NodePtr);
	bool LABELDECL(Node* NodePtr);
	bool LABELLIST(Node* NodePtr);
	bool LABELLIST1(Node* NodePtr);
	bool CONST(Node* NodePtr);
	bool PROCIDNT(Node* NodePtr);
};