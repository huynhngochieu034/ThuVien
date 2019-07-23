#include "ConsoleProcess.h"


ConsoleProcess::ConsoleProcess()
{
}

ConsoleProcess::~ConsoleProcess()
{
}

void ConsoleProcess::gotoxy(int x, int y){
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void ConsoleProcess::InTungPhanTu_Xau(string a, int _size, int _mod){
	string t = "";
	int n = a.size();
	int _pear = _mod;
	if (_mod == -1) _pear = (_size - n - 1) / 2;
	if (_mod == -2) _pear = (_size - n - 2);
	foru(i, 1, _pear) cout << " ";
	cout << a;
	foru(i, 1, _size - n - _pear - 1) cout << " ";
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	cout << "\xb3";
}

int dd(string ans){
	if (ans.empty()) return 0;
	return ans.size();
}

string ConsoleProcess::DocVaoXauKiTu(int x, int y, int &err){
	gotoxy(x, y);
	int _x = x;
	int _y = y;
	string ans = "";
	err = 0;
	while (true){
		fflush(stdin);

		ShowCur(1);
		int k = getch();
		ShowCur(0);

		if ((dd(ans)<30) && ((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z') || (k == 32) || (k >= '0' && k <= '9') || (k == '/') || (k == '.') || (k == '-'))){
			ans = ans + ' ';
			string ans1 = "";
			foru(j, 0, (_x - x - 1)) ans1 = ans1 + ans[j];
			ans1 = ans1 + char(k);
			foru(j, (_x - x), dd(ans) - 2) ans1 = ans1 + ans[j];
			ans = ans1;

			gotoxy(x, _y);
			foru(iz, 1, ans.size()) cout << " ";
			gotoxy(x, _y);
			cout << ans;
			_x++;
			gotoxy(_x, _y);
			continue;
		}

		if (k == Control_Enter) {
			gotoxy(0, y + 1);
			return ans;
		}

		if (k == Control_Esc){
			//int msgboxID = MessageBox(NULL, "Ban co chac chan muon thoat khong?", "Thông báo", MB_OKCANCEL);
			Menu Thoat(0, 40, 1);
			Thoat.Set_Header("Ban co chac chan  muon thoat khong?");
			Thoat.add("Co");
			Thoat.add("Khong");
			Thoat.setToaDo(55, 25);
			int ch = Thoat.run1();
			switch (ch){
			case 1: err = 1; ShowCur(0); return ""; break;
			case 2: gotoxy(_x, _y); break;
			}
			continue;
		}

		if (k == Control_BackSpace && _x>x){
			_x--;

			string ans1 = "";
			foru(i, x, _x - 1) ans1 = ans1 + ans[i - x];
			foru(i, _x + 1, dd(ans) + x - 1) ans1 = ans1 + ans[i - x];

			ans = ans1;
			gotoxy(x, _y);
			foru(iz, 1, ans.size() + 1) cout << " ";
			gotoxy(x, _y);
			cout << ans;
			gotoxy(_x, _y);
			continue;
		}

		if (k == Control){
			fflush(stdin);
			k = getch();

			if (k == Control_Left && _x>x){
				_x--;
				gotoxy(_x, _y);
			}

			if (k == Control_Right && _x <= dd(ans) + x - 1){
				_x++;
				gotoxy(_x, _y);
			}

			continue;
		}

	}
}

char ConsoleProcess::uppercase(char a){
	if (a >= 'a' && a <= 'z') a = a - 32;
	return a;
}

char ConsoleProcess::lowercase(char a){
	if (a >= 'A' && a <= 'Z') a = a + 32;
	return a;
}

void ConsoleProcess::StringtoChar(string a, char b[]){
	foru(i, 0, a.size() - 1) b[i] = a[i];
	b[a.size()] = '\0';
}

string ConsoleProcess::ChartoString(char a[]){
	string ans = "";
	int n = strlen(a);
	foru(i, 0, n - 1) ans = ans + a[i];
	return ans;
}

void ConsoleProcess::InTungPhanTu_XauMau(string a, int _size, int _mod){
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, Special_Color);
	string t = "";
	int n = a.size();
	int _pear = _mod;
	if (_mod == -1) _pear = (_size - n - 1) / 2;
	foru(i, 1, _pear) cout << " ";
	cout << a;
	foru(i, 1, _size - n - _pear - 1) cout << " ";
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	cout << "\xb3";
}

void ConsoleProcess::ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void ConsoleProcess::ThongBao(int x, int y, string a, int check){
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	if (check == 0)
	SetConsoleTextAttribute(hConsoleColor, 12);
	else SetConsoleTextAttribute(hConsoleColor, 10);
	gotoxy(x, y);
	cout << a << endl;
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	getch();
	gotoxy(x, y);
	foru(i, 1, 40) cout << " ";

}

void ConsoleProcess::CreateBoxTitle(int x, int y, string text, int length)
{
	gotoxy(x - 2, y - 1);
	cout << char(201) << setw(length) << setfill(char(205)) << char(205) << char(187);

	gotoxy(x - 2, y);
	cout << char(186) << text << setw(length - text.length() + 1) << setfill(' ') << char(186);

	gotoxy(x - 2, y + 1);
	cout << char(200) << setw(length) << setfill(char(205)) << char(205) << char(188);
}

void ConsoleProcess::CreateBoxAdd(int x, int y, string text, int length)
{
	gotoxy(x - 2, y);
	cout << char(186) << text << setw(length - text.length() + 1) << setfill(' ') << char(186);
}

void ConsoleProcess::CreateBoxEnd(int x, int y, string text, int length)
{
	gotoxy(x - 2, y);
	cout << char(186) << text << setw(length - text.length() + 1) << setfill(' ') << char(186);
	gotoxy(x - 2, y + 1);
	cout << char(200) << setw(length) << setfill(char(205)) << char(205) << char(188);
}

string ConsoleProcess::convert(int a){
	string ans = "";
	if (a == 0) return "0";

	while (a > 0){
		int r = a % 10;
		ans = char(r + 48) + ans;
		a /= 10;
	}

	return ans;
}