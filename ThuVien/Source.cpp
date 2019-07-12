#include "Template.h"

// cac struct can su dung

//--------------Struct Danh muc sach-------------
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

//-----------Struct Dau sach-----------------
struct DauSach{
	string ISBN;
	string TenSach;
	int SoTrang;
	string TacGia;
	int NamXuatBan;
	string TheLoai;
	
};
typedef struct DauSach DAUSACH;

struct NodeDauSach{
	DAUSACH data;
	LIST_DMS listDMS;/// chua danh sach cac danh muc sach cua danh muc sach do
};
typedef struct NodeDauSach NODEDAUSACH;


struct ListDauSach{
	int n;
	NODEDAUSACH* ListDS[120];
};
typedef struct ListDauSach LIST_DS;

//---------------Struct Muon tra--------------------
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

//----------------Struct The doc gia---------------------

struct HoTenDG{
	string hoTen;
	unsigned int MATHE;
};

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

//-----------Biến toàn cục------------------
int nDocGia=0;
int vitri=0;


//--------------Chuẩn hóa chuỗi--------------
void XoaKhoangTrangDauVaCuoi(string &str){

	while (str[0] == ' ') str.erase(str.begin() + 0); // xóa kí tự tại vị trí 0
	while (str[str.length() - 1] == ' ') str.erase(str.begin() + str.length() - 1);// xóa vị trí cuối
}

void XoaKhoangTrangGiua(string &str){

	foru(i, 0, str.length() - 1)
	if (str[i] == ' ' && str[i + 1] == ' '){
		str.erase(str.begin() + i);
		i--;
	}
}

void InHoaKiTuDau(string &str){
	strlwr((char *)str.c_str());

	if (str[0] != ' '){
		if (str[0] >= 97 && str[0] <= 122)
			str[0] -= 32;
	}
		
	foru(i, 0, str.length()){
		if (str[i] == ' ' && str[i + 1] != ' ')
		if (str[i + 1] >= 97 && str[i + 1] <= 122)
			str[i + 1] -= 32;
	}
		
}

void ChuanHoaChuoi(string &str){
	XoaKhoangTrangDauVaCuoi(str);
	XoaKhoangTrangGiua(str);
	InHoaKiTuDau(str);
}

int checkNhapChu(string str){
	
	foru(i, 0, str.length())
		if (!(((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) || str[i]==32))
			if (str[i] != '\0')
				return 0;
	return 1;
}

int checkNhapSo(string str){
	foru(i, 0, str.length())
		if (!(str[i] == 48 || str[i] == 49))
			if (str[i] != '\0')
				return 0;
	return 1;
}


//--------------Cài đặt cây tìm kiếm nhị phân-----------------

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
		
		//cay co ton tai phan tu
	     if(t->data.MATHE > x.MATHE){
			ThemNodeVaoCay(t->pLeft, x);
			return 1;
		}
		else if(t->data.MATHE < x.MATHE){
			ThemNodeVaoCay(t->pRight, x);
			return 1;
		}
		
		
	}
	return 0;
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
	ConsoleProcess::InTungPhanTu_XauMau("MA THE", w[1] - 1, -1);
	ConsoleProcess::InTungPhanTu_XauMau("HO", w[2], -1);
	ConsoleProcess::InTungPhanTu_XauMau("TEN", w[3], -1);
	ConsoleProcess::InTungPhanTu_XauMau("GIOI TINH(0: Nu, 1:Nam)", w[4], -1);
	ConsoleProcess::InTungPhanTu_XauMau("TRANG THAI(0: Bi khoa , 1: Dang hoat dong)", w[5], -1);
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
	string phai, trangthai;
	string ho, ten;
	x.MATHE = mathe;
	cout << "Ma doc gia: "<<x.MATHE<<"\n";

	nhapho:
	cout << "Nhap ho: ";
	getline(cin, ho);
	if (checkNhapChu(ho) == 0){
		cout << "Vui long nhap dung du lieu.Nhap lai\n";
		goto nhapho;
	}

	nhapten:
	cout << "Nhap ten: ";
	getline(cin, ten);
	if (checkNhapChu(ten) == 0){
		cout << "Vui long nhap dung du lieu.Nhap lai\n";
		goto nhapten;
	}
	cout << ten;
	
	nhapphai:
	cout << "Nhap phai(0: Nu, 1:Nam): ";
	cin >> phai;
	if (checkNhapSo(phai) == 0){
		cout << "Vui long nhap dung du lieu.Nhap lai\n";
		goto nhapphai;
	}

	nhaptrangthai:
	cout << "Nhap trang thai(0: Khoa, 1: Hoat Dong): ";
	cin >> trangthai;
	if (checkNhapSo(trangthai) == 0){
		cout << "Vui long nhap dung du lieu.Nhap lai\n";
		goto nhaptrangthai;
	}
	ChuanHoaChuoi(ho);
	ChuanHoaChuoi(ten);
	x.Ho = ho;
	x.Ten = ten;
	x.Phai = stoi(phai);
	x.TrangThai = stoi(trangthai);
	cout << x.Ho<<endl;
	cout << x.Ten<<endl;
	cout << x.Phai << endl;
	cout << x.TrangThai << endl;
}

void InDongDuLieu(TREE t, int w[]){
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


		ConsoleProcess::InTungPhanTu_XauMau(ConsoleProcess::convert(t->data.MATHE), w[1] - 1, -1);
		ConsoleProcess::InTungPhanTu_XauMau(t->data.Ho, w[2], -1);
		ConsoleProcess::InTungPhanTu_XauMau(t->data.Ten, w[3], -1);

		(t->data.Phai == 1) ?
			ConsoleProcess::InTungPhanTu_XauMau("NAM", w[4], -1) :
			ConsoleProcess::InTungPhanTu_XauMau("NU", w[4], -1);

		(t->data.TrangThai == 1) ?
			ConsoleProcess::InTungPhanTu_XauMau("HOAT DONG", w[5], -1) :
			ConsoleProcess::InTungPhanTu_XauMau("KHOA", w[5], -1);
		cout << endl;

		/// in dong _
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
		foru(i, 2, 5){
			foru(j, 1, w[i] - 1)cout << "_";
			cout << "\xb3";
		}
		cout << endl;
	}
	
}

void InDanhSachDocGia(TREE t, int w[]){
	
	/// in cac dong sau
	if (t != NULL){
		InDanhSachDocGia(t->pLeft, w);
		InDongDuLieu(t, w);
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
	string temp;
	filein >> tdg.MATHE;
	getline(filein, temp);
	getline(filein, tdg.Ho);
	getline(filein, tdg.Ten);
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
	system("cls");
	cout << "-------Thong tin doc gia can hieu chinh--------"<<endl;
	cout << "Ma The: " << tdg.MATHE <<endl;
	cout << "Ho: " << tdg.Ho << endl;;
	cout << "Ten: " << tdg.Ten << endl;;

	(tdg.Phai == 1) ? cout << "Phai: " << "NAM" << endl : cout << "Phai: " << "NU" << endl;
	(tdg.TrangThai == 1) ? cout << "Trang thai: " << "Hoat Dong" << endl : cout << "Trang Thai: " << "Khoa" << endl;;

	cout << "---------Nhap thong tin can chinh sua--------"<<endl;
	NhapDocGia(tdg, w, maThe);
	
}

void ThemDuLieuVaoMangHoTen(TREE t, HoTenDG* ht){
	//Duyệt mảng thêm dữ liệu mã độc giả vào mảng int
	if (t != NULL){
		ThemDuLieuVaoMangHoTen(t->pLeft,ht);
		ht[vitri].hoTen = t->data.Ten + t->data.Ho;
		ht[vitri].MATHE = t->data.MATHE;
		vitri++;
		ThemDuLieuVaoMangHoTen(t->pRight, ht);
	}

}

void Swap(HoTenDG &x, HoTenDG &y){
	HoTenDG temp;
	temp = x;
	x = y;
	y = temp;
}

void Quick_Sort(HoTenDG *ht, int left, int right){
	HoTenDG key = ht[(left + right) / 2];
	int i = left, j = right;
	do{
		while (ht[i].hoTen < key.hoTen)
			i++;
		while (ht[j].hoTen >key.hoTen)
			j--;
		if (i <= j){
			if (i < j) Swap(ht[i], ht[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (left < j) Quick_Sort(ht, left, j);
	if (right > i) Quick_Sort(ht, i, right);
}

void InDanhSachTamThoi(TREE t, HoTenDG *ht, int n, int w[]){
	NODETHEDOCGIA* temp = NULL;
	if (t != NULL){
		foru(i, 0, n){
			temp = TimKiemDocGia(t, ht[i].MATHE);
			InDongDuLieu(temp, w);
		}
	}
}

void InDanhSachDocGiaTangDanTheoTenHo(TREE t, int w[]){
	nDocGia = DemSoDocGia(t);
	HoTenDG *p = new HoTenDG[nDocGia];
	ThemDuLieuVaoMangHoTen(t, p);
	Quick_Sort(p, 0, nDocGia - 1);
	InTieuDe(w);
	InDanhSachTamThoi(t, p, nDocGia, w);
	// xoa vung nho
	delete[] p;
}

int LuaChon(){
	Menu a(35, 60, 1);
	a.Set_Header("MENU LUA CHON");
	a.add("1. Quan ly The Doc Gia");
	a.add("2. Quan Ly Dau Sach");
	a.add("3. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 3;
	return k;
}

void CapNhatDanhSachCacDocGia(TREE &t){
	/// danh sach gom 5 cot mathe, ho, ten, gioitinh, trang thai
	int w[6] = { 20, 10, 30, 20, 35, 45 };
	Menu a(35, 60, 1);
	a.Set_Header("MENU LUA CHON");
	a.add("1. In danh sach doc gia tang theo ma ");
	a.add("2. In danh sach doc gia tang theo ten ho");
	a.add("3. Them doc gia");
	a.add("4. Sua doc gia");
	a.add("5. Xoa doc gia");
	a.add("6. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 6;
		
	if (k == 6) return;
	if (k == 1){
		DocDuLieuDocGia(t);
		InTieuDe(w);
		InDanhSachDocGia(t,w);
		getch();
	}
	if (k == 2){
		DocDuLieuDocGia(t);
		InDanhSachDocGiaTangDanTheoTenHo(t, w);
		getch();
	}

	if (k == 3) {
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
	if (k == 4){
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
	if (k == 5){

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

void CapNhatDanhSachDauSach(){
	/// danh sach gom 5 cot mathe, ho, ten, gioitinh, trang thai
	int w[6] = { 20, 10, 30, 20, 35, 45 };
	Menu a(35, 60, 1);
	a.Set_Header("MENU LUA CHON");
	a.add("1. In danh sach dau sach tang theo ma ");
	a.add("2. In danh sach dau sach tang theo ten ho");
	a.add("3. Them dau sach");
	a.add("4. Sua dau sach");
	a.add("5. Xoa dau sach");
	a.add("6. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 6;

	if (k == 6) return;
	if (k == 1){
	
	}
	if (k == 2){
		
	}

	if (k == 3) {

	}
	if (k == 4){
		
	}
	if (k == 5){

	}
}

int main()
{
	TREE t;
	DocDuLieuDocGia(t);
	ConsoleProcess::ShowCur(0);
	while (true){
		int k = LuaChon();
		switch (k){
		case 1: CapNhatDanhSachCacDocGia(t); break;///OK
		case 2:	CapNhatDanhSachDauSach(); break;
		case 3:  return 0; break;
		}
	}
	system("pause");
	return 0;
}


