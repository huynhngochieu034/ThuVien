#pragma once
#include "Template.h"


class Menu
{
private:
	int Addx, Addy;
private:
	int Size, Cur, Pear, Width;
	int current_size = 50;
	string Header;
	string *Value = new string[current_size];

public:
	Menu();
	Menu(int pear, int width, int cur);
	~Menu();
	void add(string a);
	void Set_Header(string b);
	int run(int &_err);
	void setToaDo(int x, int y);
	void XoaMenu();
	int run1();/// chay menu mini
	void Display1();/// in ra lua chon kieu menu
private:
	void InTungDong(int x);
	void Up();
	void Down();
	void Display();
	void indongrong();
	void InTungDong1(int x);/// in o menu dang 2
	void Down1();
	void Up1();
};

