#include "Menu.h"

Menu::Menu()
{
	Size = 0;
	Pear = 0;
	Width = 0;
	Cur = 0;
	Addx = 0;
	Addy = 0;
	
}

Menu::~Menu()
{
}

Menu::Menu(int pear, int width, int cur){
	Size = 0;
	Pear = pear;
	Width = width;
	Cur = cur;
	
}

void Menu::Set_Header(string b){
	Header = b;
}

void Menu::add(string a){
	Value[Size++] = a;
}

void Menu::Display(){

	///Ve vi tri dau tien + xet mau binh thuong
	ConsoleProcess::gotoxy(0 + Addx, 1 + Addy);
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	///In Header
	foru(i, 1, Pear) cout << " "; cout << " "; foru(i, 1, Width - 2) cout << "_"; cout << " \n";
	ConsoleProcess::gotoxy(Addx, 2 + Addy); foru(i, 1, Pear) cout << " "; cout << "\xb3"; foru(i, 1, Width - 2) cout << " "; cout << "\xb3\n";
	//foru(i, 1, Pear) cout << " "; cout << "\xb3"; foru(i, 1, Width - 2) cout << " "; cout << "\xb3\n";
	ConsoleProcess::gotoxy(Addx, 3 + Addy); foru(i, 1, Pear) cout << " "; cout << "\xb3"; ConsoleProcess::InTungPhanTu_Xau(Header, Width - 1, -1); cout << "\n";
	//foru(i, 1, Pear) cout << " "; cout << "\xb3"; foru(i, 1, Width - 2) cout << " "; cout << "\xb3\n";
	ConsoleProcess::gotoxy(Addx, 4 + Addy); foru(i, 1, Pear) cout << " "; cout << "\xb3"; foru(i, 1, Width - 2) cout << "_"; cout << "\xb3\n";

	foru(i, 1, Size) InTungDong(i);
}

void Menu::InTungDong(int x){
	/// Dua con tro ve vi tri can in
	ConsoleProcess::gotoxy(0 + Addx, (x - 1) * 2 + 5 + Addy);
	int zzz = (x - 1) * 2 + 5 + Addy;
	///xet mau de in
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);

	///Neu la dong con tro dang nhay -> doi mau sang special
	/*foru(i, 1, Pear) cout << " ";
	cout << "\xb3";
	if (x == Cur) SetConsoleTextAttribute(hConsoleColor, Special_Color);
	foru(i, 1, Width - 2) cout << " ";
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	cout << "\xb3\n";*/

	ConsoleProcess::gotoxy(Addx, zzz);
	foru(i, 1, Pear) cout << " ";
	cout << "\xb3";
	if (x == Cur) SetConsoleTextAttribute(hConsoleColor, Special_Color);
	ConsoleProcess::InTungPhanTu_Xau(Value[x - 1], Width - 1, 5); cout << "\n";

	ConsoleProcess::gotoxy(Addx, zzz + 1);
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);

	foru(i, 1, Pear) cout << " ";
	cout << "\xb3";
	if (x == Cur) SetConsoleTextAttribute(hConsoleColor, Special_Color);
	foru(i, 1, Width - 2) cout << "_";
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	cout << "\xb3\n";
}

void Menu::Up(){
	int Cur1 = Cur;
	Cur--;
	if (Cur == 0) Cur = Size;
	InTungDong(Cur1);
	InTungDong(Cur);
	
}

void Menu::Down(){
	int Cur1 = Cur;
	Cur++;
	if (Cur > Size) Cur = 1;
	InTungDong(Cur1);
	InTungDong(Cur);
}

int Menu::run(int &_err){
	system("cls");
	Display();
	while (true){
		fflush(stdin);
		int k = getch();

		if (k == Control_Esc){
			Menu Thoat(0, 40, 1);
			Thoat.Set_Header("Ban co chac chan muon thoat khong?");
			Thoat.add("Co");
			Thoat.add("Khong");
			Thoat.setToaDo(55, 25);
			int ms = Thoat.run1();
			switch (ms){
			case 1:{
					   _err = 1;
					   return 0;
			}
			case 2: continue;
			}
		}
		if (k == Control_Enter) break;
		if (k == Control){
			fflush(stdin);
			k = getch();
			if (k == Control_Down) Down();
			if (k == Control_Up) Up();
		}

	}
	_err = 0;
	return Cur;
}

void Menu::setToaDo(int x, int y){
	this->Addx = x;
	this->Addy = y;
}

void Menu::XoaMenu(){
	int kichthuoc = (Pear + Width);
	ConsoleProcess::gotoxy(Addx, Addy + 1);
	foru(i, 1, kichthuoc) cout << " ";
	ConsoleProcess::gotoxy(Addx, Addy + 2);
	foru(i, 1, kichthuoc) cout << " ";
	ConsoleProcess::gotoxy(Addx, Addy + 3);
	foru(i, 1, kichthuoc) cout << " ";
	ConsoleProcess::gotoxy(Addx, Addy + 4);
	foru(i, 1, kichthuoc) cout << " ";

	if (Value->empty()) return;
	foru(i, 1, Size){
		int zzz = (i - 1) * 2 + 5 + Addy;
		ConsoleProcess::gotoxy(Addx, zzz);
		foru(j, 1, kichthuoc) cout << " ";
		ConsoleProcess::gotoxy(Addx, zzz + 1);
		foru(j, 1, kichthuoc) cout << " ";
	}
	
	delete[] Value;
	

}

void Menu::Down1(){
	int Cur1 = Cur;
	Cur++;
	if (Cur > Size) Cur = 1;
	InTungDong1(Cur1);
	InTungDong1(Cur);
}

void Menu::Up1(){
	int Cur1 = Cur;
	Cur--;
	if (Cur == 0) Cur = Size;
	InTungDong1(Cur1);
	InTungDong1(Cur);
}

void Menu::InTungDong1(int x){
	int zzz = (x - 1) * 2 + 5 + Addy;
	ConsoleProcess::gotoxy(Addx, zzz);
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	if (x == Cur) SetConsoleTextAttribute(hConsoleColor, 31);
	cout << Value[x - 1] << endl;
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
}

void Menu::Display1(){
	ConsoleProcess::gotoxy(Addx, Addy + 1);
	cout << Header << endl;
	foru(i, 1, Size) InTungDong1(i);
}

int Menu::run1(){
	Display1();
	while (true){
		fflush(stdin);
		int k = getch();

		if (k == Control_Enter) break;
		if (k == Control){
			fflush(stdin);
			k = getch();
			if (k == Control_Down) Down1();
			if (k == Control_Up) Up1();
		}

	}
	XoaMenu();
	return Cur;
}