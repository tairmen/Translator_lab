#pragma once
using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

struct Lex
{
	int Code;
	int Line;
	int Column;
	string Name;
};

class LeksAnaliz
{
public:
	int LexCounter;
	//������� ������
	vector <Lex> Lexems;
	//������� ���������������
	vector <string> Table;
	//������� ��������
	vector <string> TableC;
	//������� ����� ������ ��������� �����
	int Line;
	int SaveLine;
	//������� ����� ������� �������� �����
	int Column;
	int SaveColumn;
	int LexErrorCode;
	//������� ����������������
	int IdentCounter;	
	//����������� ��� �������������� 
	int MinIdent;
	//������� ��������
	int ConstCounter;	
	//����������� ��� ���������
	int MinConst;
	//���� �������� ����
	int KeyWordsMin;
	//�������� ������� �������� � �������
	int ConstMax;
	//���������� �������� � �����
	int Size;
	//������ ����� ASCCII ��������
	int ASCIIArr[128];
	//������ ����������� ����������������
	vector <string> StdIdent { "PROCEDURE", "PROGRAM", "LABEL" , "BEGIN", "END" };
	//������� ������� � �����
	int Pos;
	//������ � �������� �����
	//string Str;
	//�������� ������
	char sbuff;
	//���� � �����
	fstream t;

	//�����������
	LeksAnaliz();
	~LeksAnaliz();
	//��������� � ����� ������ �������
	void AddLeksem(int Code, string Name, int Line, int Column);
	//�������� ������ �� ����� ������
	bool SizeOut();
	//����������� ����������
	void Analizator(string filename);
	//���� ���������� ������� ������
	void INP();
	//whitespace
	void SEP();
	//���� ���������
	void CONST();
	//���� ���������������
	void IDN();
	//�������� ������ ����������
	void BCOM();
	//�������� ����������
	void COM();
	//�������� ����� ����������
	void ECOM();
	//�������� �� �������������� �����������
	void DM();
	//�������� �� ������
	void ERR(string pt);
	//����� � ������� ����������������
	int SearchIdent(string Ident);
	//����� ����� ����������������� ����
	int SearchStandartIdent(string Ident);
	//����� � ������� ��������
	int SearchConst(string Const);
	//������ ������
	void MakeListing(string filename);
};