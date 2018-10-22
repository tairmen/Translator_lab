#pragma once
#include "LexAnaliz.h"

//���� ������ ������� ���������
struct Node
{
	int Code;// ��� ���������
	string Name; // �������� ���������
	int Line; // ������ ��������� � ����
	int Column; // ������� ��������� � ����
	string Info; // ���������� ��� ������� ����
	string Func; // ������� ������ ���� 
	bool IsTerminal; // ���� ������������ ��� �������� ������� ����, ����������, ��� ������������
	Node* Next; // ��������� �� ��������� �� ������� ������ ������ ����
	Node* Down; // ��������� �� ���� ������� ������
};

struct KnutEl {
	int Op;
	int AT;
	int AF;
};

//����� ����������� �������������� ����������
class SyntaxAnaliz
{
public:
	//��������� �� ������� ������ �������
	Node * Tree;
	//������� ���������������� �������������� ����������� ������������
	vector<Lex> Lexems;
	// ������ �����
	vector<KnutEl> Knut;
	//������� �������
	int Pos;
	int LevelCounter;
	int IdentMin;
	int ConstMin;
	int ConstMax;
	vector<string> IdentTable;
	vector<string> ConstTable;
	//������� ������
	int ErrorCounter;
	//�����������
	SyntaxAnaliz(string FileName);
	//������������� ������
	Node* InitTree();
	//���������� ���� � ������
	Node* AddNode(Node* Nd, int dirrection, int code, string Name, int line, int column, string info, string Func, bool isterminal);
	//�������� ���������� ����
	Node* RemoveNode(Node* N);
	//��������� ������ ������
	void WriteTree(Node* Root, string sps);
	string TreeStr;
	string ErrorStr;
	//����� ������ � ����
	void TreeListing(string FileName);
	//����� ������
	void Errors(int p, int pos);
	void InitKnut();
	void KnutMachine();
	//��������� ��������������� ����������� �������� ����������
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