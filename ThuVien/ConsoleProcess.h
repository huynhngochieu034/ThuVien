#pragma once
#include "Template.h"
#include "Menu.h"

static class ConsoleProcess
{
public:
	ConsoleProcess();
	~ConsoleProcess();
	static void gotoxy(int x, int y);
	static void InTungPhanTu_Xau(string a, int _size, int _mod);
	static void InTungPhanTu_XauMau(string a, int _size, int _mod);
	static string DocVaoXauKiTu(int x, int y, int &err);
	static char uppercase(char a);
	static char lowercase(char a);
	static void StringtoChar(string a, char b[]);
	static string ChartoString(char a[]);
	static void ShowCur(bool CursorVisibility);
	static void ThongBao(int x, int y, string a, int check);
	static string convert(int a);
};

