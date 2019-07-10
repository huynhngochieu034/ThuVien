#include "Template.h"

// cac struct can su dung

//--------------Danh muc sach-------------
struct DanhMucSach{
	string MaSach;
	int TrangThai; //0: cho mượn được, 1: đã có độc giả mượn, 2: sách đã thanh lý . 
	string ViTri;
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
	string ISBN;
	string TenSach;
	int SoTrang;
	string TacGia;
	int NamXuatBan;
	string TheLoai;
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
	string MaSach;
	Date NgayMuon;
	Date NgayTra;
	int TrangThai;//trạng thái = 0 là sách đang mượn (chưa trả), =1 là đã trả, =2 : làm mất sách 
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
	unsigned int MATHE;
	string Ho;
	string Ten;
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

unsigned int Random()
{
	srand(time(0));
	int x;
	// bo ham rand() vao vong lap moi khong bi loi tang dan, hay giam dan.
	for (int i = 0; i < 500; i++)
		x = rand();
	return x;
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
		/*checkMaDocGia:*/
		//cay co ton tai phan tu
	     if(t->data.MATHE > x.MATHE){
			ThemNodeVaoCay(t->pLeft, x);
			return 1;
		}
		else if(t->data.MATHE < x.MATHE){
			ThemNodeVaoCay(t->pRight, x);
			return 1;
		}
		else {
			return 0;
			/*x.MATHE = Random();
			goto checkMaDocGia;*/
		}
		
	}
	
}

NODETHEDOCGIA* TimKiemDocGia(TREE t, int x){

	if (t == NULL) return NULL;
	else{
		if (x < t->data.MATHE) TimKiemDocGia(t->pLeft, x);
		else if (x > t->data.MATHE) TimKiemDocGia(t->pRight, x);
		else return t;
	}
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

void NhapDocGia(TheDocGia &x, int w[], unsigned int mathe){
	x.MATHE = mathe;
	cout << "Ma doc gia: "<<x.MATHE<<"\n";
	cout << "Nhap ho: ";
	cin >> x.Ho;
	cout << "Nhap ten: ";
	cin >> x.Ten;
	cout << "Nhap phai(0: Nu, 1:Nam): ";
	cin >> x.Phai;
	cout << "Nhap trang thai(0: Khoa, 1: Hoat Dong): ";
	cin >> x.TrangThai;
}


void InDanhSachDocGia(TREE t, int w[]){

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
		
		
		ConsoleProcess::InTungPhanTu_Xau(ConsoleProcess::convert(t->data.MATHE), w[1] - 1, -1);
		ConsoleProcess::InTungPhanTu_Xau(t->data.Ho, w[2], -1);
		ConsoleProcess::InTungPhanTu_Xau(t->data.Ten, w[3], -1);

		(t->data.Phai == 1) ? 
		ConsoleProcess::InTungPhanTu_Xau("NAM", w[4], -1) : 
		ConsoleProcess::InTungPhanTu_Xau("NU", w[4], -1);
		
		(t->data.TrangThai == 1) ?
			ConsoleProcess::InTungPhanTu_Xau("HOAT DONG", w[5], -1) :
			ConsoleProcess::InTungPhanTu_Xau("KHOA", w[5], -1);
		cout << endl;

		/// in dong _
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
		foru(i, 2, 5){
			foru(j, 1, w[i] - 1)cout << "_";
			cout << "\xb3";
		}
		cout << endl;
		InDanhSachDocGia(t->pLeft, w);
		InDanhSachDocGia(t->pRight, w);
	}
}

int DemSoDocGia(TREE t){
	int dem = 1;
	if (t != NULL){
		dem += DemSoDocGia(t->pLeft);
		dem += DemSoDocGia(t->pRight);
		return dem;
	}
	else return 0;
}

void GhiThongTin1DocGia(TREE t, fstream &fileout){
	
	fileout << t->data.MATHE << endl;
	fileout << t->data.Ho << endl;
	fileout << t->data.Ten << endl;
	fileout << t->data.Phai << endl;
	fileout << t->data.TrangThai << endl;
}


void GhiThongTinDanhSachDocGia(TREE t, fstream &fileout){
	if (t != NULL)
	{
		GhiThongTin1DocGia(t, fileout);
		GhiThongTinDanhSachDocGia(t->pLeft, fileout);
		GhiThongTinDanhSachDocGia(t->pRight, fileout);
	}
}

void LuuDuLieuDocGia(TREE t){
	fstream fileout;
	fileout.open(databasedocgia, ios::out);
	if (fileout.is_open())
	{
		fileout << DemSoDocGia(t) << endl;
		GhiThongTinDanhSachDocGia(t, fileout);
	}
	else cout << "Loi ket noi file! ";
	fileout.close();
}

void DocThongTin1DocGia(TheDocGia &tdg, fstream &filein){
	
	filein >> tdg.MATHE;
	
	filein >> tdg.Ho;
	filein >> tdg.Ten;
	filein >> tdg.Phai;
	filein >> tdg.TrangThai;
}

void DocDuLieuDocGia(TREE &t){

	KhoiTaoCay(t);

	fstream filein;
	TheDocGia tdg;
	int soDocGia;
	filein.open(databasedocgia, ios::in);
	if (filein.is_open()){
		
		filein >> soDocGia;
		for (int i = 0; i < soDocGia; i++)
		{
			DocThongTin1DocGia(tdg, filein);
			ThemNodeVaoCay(t, tdg);
		}
	}
	else cout << "Loi ket noi file! ";
	filein.close();
}


void DiTimNodeTheMang(TREE &x, TREE &y){
	//duyet sang ben trai nhat
	if (y->pLeft != NULL){
		DiTimNodeTheMang(x, y->pLeft);
	}
	else{ //tim duoc node trai nhat
		x->data = y->data; //cap nhat data cua node can xoa la data cua node the mang	
		x = y; //cho node X =y
		y = y->pRight; //ban chat cho nay chinh la cap nhat lai moi lien ket cho node cha cua node the mang
	}
}

int XoaDocGia(TREE &t, int maDocGia){
	//Neu cay dang rong
	if (t == NULL){
		return 0;
	}
	else{
		//neu data nho hon node goc
		if (maDocGia < t->data.MATHE){
			XoaDocGia(t->pLeft, maDocGia);
		}
		else if (maDocGia > t->data.MATHE){
			XoaDocGia(t->pRight, maDocGia);
		}
		else if(maDocGia == t->data.MATHE){
			NODETHEDOCGIA *x = t; // node x la node the mang - ti nua se xoa no
			//neu nhanh trai = NULL <=> day la cay co 1 con chinh la con phai
			if (t->pLeft == NULL){
				t = t->pRight; //duyet sang phai cua node can xoa de cap nhat moi lien ket giua node cha 
								//cua node can xoa voi node con cua node can xoa
			}
			else if (t->pRight == NULL){
				t = t->pLeft; //duyet sang trai cua node can xoa de cap nhat moi lien ket giua node cha 
								//cua node can xoa voi node con cua node can xoa
			}
			else //node can xoa la node co 2 con
			{
				//C1: Tim node trai nhat cua cay con phai( cay con phai cua node can xoa)	
				NODETHEDOCGIA *y = t->pRight; //node y la node the mang cho node can xoa -  node nay se dam nhiem tim ra node trai nhat
				DiTimNodeTheMang(x, y);
			}
			delete x; //xoa node can xoa
			return 1;
		}
		else return 0;
	}
}

void HieuChinhDocGia(TREE &t, TheDocGia &tdg, int w[]){

	unsigned int maThe = tdg.MATHE;

	cout << "-------Thong tin doc gia can hieu chinh--------"<<endl;
	cout << "Ma The: " << tdg.MATHE <<endl;
	cout << "Ho: " << tdg.Ho << endl;;
	cout << "Ten: " << tdg.Ten << endl;;
	(tdg.Phai == 1) ? cout << "Phai: " << "NAM" << endl : cout << "Phai: " << "NU" << endl;
	(tdg.TrangThai == 1) ? cout << "Trang thai: " << "Hoat Dong" << endl : cout << "Trang Thai: " << "Khoa" << endl;;

	cout << "---------Nhap thong tin can chinh sua--------"<<endl;
	NhapDocGia(tdg, w, maThe);
	
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
	int w[6] = { 20, 10, 30, 20, 35, 45 };
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
		DocDuLieuDocGia(t);
		InTieuDe(w);
		InDanhSachDocGia(t,w);
		getch();
	}

	if (k == 2) {
		system("cls");
		unsigned int mathe = Random();
		TheDocGia p;
		NhapDocGia(p, w, mathe);
		int check = ThemNodeVaoCay(t, p);
		if (check == 1){
			LuuDuLieuDocGia(t);
			DocDuLieuDocGia(t);
			ConsoleProcess::ThongBao(20, 2, "Them doc gia thanh cong", 1);
		}
		else ConsoleProcess::ThongBao(20, 2, "Them doc gia that bai", 0);
		getch();
		
	}
	if (k == 3){
		InTieuDe(w);
		InDanhSachDocGia(t, w);
		int maDocGia;
		cout << "Nhap ma doc gia can hieu chinh: ";
		cin >> maDocGia;
		NODETHEDOCGIA *p = TimKiemDocGia(t, maDocGia);
		if (p == NULL) cout << "Ma doc gia " << maDocGia << "khong ton tai!";
		else{
			HieuChinhDocGia(t, p->data, w);
			LuuDuLieuDocGia(t);
			DocDuLieuDocGia(t);
			ConsoleProcess::ThongBao(20, 2, "Hieu chinh doc gia thanh cong", 1);

			getch();
		}
		
	}
	if (k == 4){

		InTieuDe(w);
		InDanhSachDocGia(t, w);
		int madocgia;
		cout << "Nhap ma the doc gia can xoa: ";
		cin >> madocgia;
		int check = XoaDocGia(t, madocgia);
		if (check == 1){
			LuuDuLieuDocGia(t);
			DocDuLieuDocGia(t);
			ConsoleProcess::ThongBao(20, 2, "Xoa doc gia thanh cong", 1);
		}
			
		else ConsoleProcess::ThongBao(20, 2, "Xoa doc gia that bai", 0);

		getch();
	}
}

int main()
{
	TREE t;
	
	ConsoleProcess::ShowCur(0);
	while (true){
		int k = LuaChon();
		switch (k){
		case 1: CapNhatDanhSachCacDocGia(t); break;///OK
		case 2:  return 0; break;
		}
	}
	system("pause");
	return 0;
}


