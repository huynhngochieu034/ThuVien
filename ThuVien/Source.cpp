#include "Template.h"

// cac struct can su dung

//--------------Danh muc sach-------------
struct DanhMucSach{
	char MaSach[15];
	int TrangThai; //0: cho mượn được, 1: đã có độc giả mượn, 2: sách đã thanh lý . 
	char ViTri[200];
};

struct nodeDMS{
	DanhMucSach data;
	struct nodeDMS *pNext;
};
typedef struct nodeDMS NODE_DMS;

struct listDMS{
	NODE_DMS *pHead;
	NODE_DMS *pTail;
};
typedef struct listDMS LIST_DMS;

//-----------Dau sach-----------------
struct DauSach{
	char ISBN[6];
	char TenSach[100];
	int SoTrang;
	char TacGia[50];
	int NamXuatBan;
	char TheLoai[40];
	LIST_DMS listDMS;/// chua danh sach cac danh muc sach cua danh muc sach do
};
typedef struct DauSach DAUSACH;


//---------------Muon tra--------------------
struct Date
{
	int Ngay;
	int Thang;
	int Nam;
};
struct MuonTra
{
	char MaSach[15];
	Date NgayMuon;
	Date NgayTra;
	int TrangThai;//trạng thái =0 là sách đang mượn (chưa trả), =1 là đã trả, =2 : làm mất sách 
};

struct nodeMuonTra{
	MuonTra data;
	struct nodeMuonTra *pNext;
	struct nodeMuonTra *pPrev;
};
typedef struct nodeMuonTra NODE_MUONTRA;

struct listMuonTra{
	NODE_MUONTRA *pHead;
	NODE_MUONTRA *pTail;
};
typedef struct listMuonTra LIST_MUONTRA;

//----------------The doc gia---------------------
struct TheDocGia{
	int MATHE;
	char Ho[100];
	char Ten[100];
	int Phai; /// 0: nu, 1 nam
	int TrangThai;
	LIST_MUONTRA listMuonTra;
};

struct nodeTheDocGia{
	TheDocGia data;
	struct nodeTheDocGia *pLeft;
	struct nodeTheDocGia *pRight;
};
typedef struct nodeTheDocGia NODETHEDOCGIA;
typedef NODETHEDOCGIA* TREE;


void KhoiTaoCay(TREE &t){
	t = NULL;
}

int ThemNodeVaoCay(TREE &t, TheDocGia x){

	//neu cay rong
	if (t == NULL){
		NODETHEDOCGIA *p = new NODETHEDOCGIA;
		p->data = x;
		p->pLeft = NULL;
		p->pRight = NULL;
		t = p;//node p chinh la goc
		return 1;
	}
	else {
		//cay co ton tai phan tu
	     if(t->data.MATHE > x.MATHE){
			ThemNodeVaoCay(t->pLeft, x);
			return 1;
		}
		else if(t->data.MATHE < x.MATHE){
			ThemNodeVaoCay(t->pRight, x);
			return 1;
		}
		else return 0;
		
	}
	return 0;
}

void InTieuDe(int w[]){
	system("cls");
	cout << endl;
	cout << endl;


	int sum = 0;
	foru(i, 1, 5) sum = sum + w[i];

	/// dong 1
	foru(i, 1, w[0] + 1) cout << " "; foru(i, 1, sum - 2) cout << "_"; cout << endl;

	/// dong 2
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
	foru(i, 2, 5){
		foru(j, 1, w[i] - 1)cout << " ";
		cout << "\xb3";
	}
	cout << endl;

	/// dong 3
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	ConsoleProcess::InTungPhanTu_Xau("MA THE", w[1] - 1, -1);
	ConsoleProcess::InTungPhanTu_Xau("HO", w[2], -1);
	ConsoleProcess::InTungPhanTu_Xau("TEN", w[3], -1);
	ConsoleProcess::InTungPhanTu_Xau("GIOI TINH(0: Nu, 1:Nam)", w[4], -1);
	ConsoleProcess::InTungPhanTu_Xau("TRANG THAI(0: Bi khoa , 1: Dang hoat dong)", w[5], -1);
	cout << endl;

	/// dong 4
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
	foru(i, 2, 5){
		foru(j, 1, w[i] - 1)cout << "_";
		cout << "\xb3";
	}
	cout << endl;
}


void NhapDocGia(TheDocGia &x, int w[]){
	int mathe = rand() % 10000 + 1;
	x.MATHE = mathe;
	cout << x.MATHE<<"\n";
	cin >> x.Ho;
	cin >> x.Ten;
	cin >> x.Phai;
	cin >> x.TrangThai;
}


void InDanhSachDocGia(TREE t, int w[]){
	char static gioitinh[10];
	char static trangthai[50];

	/// in cac dong sau
	if (t != NULL){

		/// in dong trang
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
		foru(i, 2, 5){
			foru(j, 1, w[i] - 1)cout << " ";
			cout << "\xb3";
		}
		cout << endl;

		/// in dong du lieu

		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		InDanhSachDocGia(t->pLeft, w);
		
		ConsoleProcess::InTungPhanTu_Xau(ConsoleProcess::convert(t->data.MATHE), w[1] - 1, -1);
		ConsoleProcess::InTungPhanTu_Xau(t->data.Ho, w[2], -1);
		ConsoleProcess::InTungPhanTu_Xau(t->data.Ten, w[3], -1);

		if (t->data.Phai == 1)
			strcpy(gioitinh, "NAM");
		else if(t->data.Phai == 0)
			strcpy(gioitinh, "NU");
		ConsoleProcess::InTungPhanTu_Xau(gioitinh, w[4], -1);

		if (t->data.TrangThai == 1)
			strcpy(trangthai, "DANG HOAT DONG");
		else if(t->data.TrangThai == 0)
			strcpy(trangthai, "DA KHOA");
		ConsoleProcess::InTungPhanTu_Xau(trangthai, w[5], -1);
		cout << endl;

		/// in dong _
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
		foru(i, 2, 5){
			foru(j, 1, w[i] - 1)cout << "_";
			cout << "\xb3";
		}
		cout << endl;

		InDanhSachDocGia(t->pRight, w);
	}
}
void DocThongTin1DocGia(ifstream &filein, TheDocGia &t){
	filein >> t.MATHE;
	filein >> t.Ho;
	filein >> t.Ten;
	filein >> t.Phai;
	filein >> t.TrangThai;
}

void GhiThongTin1DocGia(ofstream &fileout, TheDocGia t){
	fileout << t.MATHE <<"\n";
	fileout << t.Ho << "\n";
	fileout << t.Ten << "\n";
	fileout << t.Phai << "\n";
	fileout << t.TrangThai;
}

void DocDanhSachDocGia(ifstream &filein, TREE &t){
	while (!filein.eof()){
		TheDocGia p;
		DocThongTin1DocGia(filein, p);
		ThemNodeVaoCay(t, p);
	}
}

int LuaChon(){
	Menu a(35, 60, 1);
	a.Set_Header("MENU LUA CHON");
	a.add("1. Quan ly the doc gia");
	a.add("2. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 2;
	return k;
}

void CapNhatDanhSachCacDocGia(TREE &t){
	/// danh sach gom 5 cot mathe, ho, ten, gioitinh, trang thai
	int w[6] = { 10, 10, 30, 20, 35, 45 };
	Menu a(35, 60, 1);
	a.Set_Header("MENU LUA CHON");
	a.add("1. In danh sach doc gia");
	a.add("2. Them doc gia");
	a.add("3. Sua doc gia");
	a.add("4. Xoa doc gia");
	a.add("5. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 5;
		
	if (k == 5) return;
	if (k == 1){
	
		InTieuDe(w);
		InDanhSachDocGia(t,w);
		
	}

	if (k == 2) {
		system("cls");
		TheDocGia p;
		NhapDocGia(p,w);
		int check = ThemNodeVaoCay(t, p);
		if (check == 1){
			ofstream fileout;
			fileout.open(databasedocgia, ios::out | ios::app);
			GhiThongTin1DocGia(fileout, p);
			fileout.close();
			ConsoleProcess::ThongBao(20, 2, "Them doc gia thanh cong", 1);
		}
		else ConsoleProcess::ThongBao(20, 2, "Them doc gia that bai", 0);
		
	}
}

int main()
{
	TREE t;
	KhoiTaoCay(t);

	ifstream filein;
	filein.open(databasedocgia, ios::in);
	DocDanhSachDocGia(filein, t);
	filein.close();

	ConsoleProcess::ShowCur(0);
	while (true){
		int k = LuaChon();
		switch (k){
		case 1: CapNhatDanhSachCacDocGia(t); break;///OK
		case 2:  return 0; break;
		}
	}
	return 0;
}


