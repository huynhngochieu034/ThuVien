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
	int n;
	NODE_DMS *pHead;
	NODE_DMS *pTail;
};
typedef struct listDMS LIST_DMS;
//------------------END struct DMS-----------------


//-----------Struct Dau sach----------------------
struct DauSach{
	string ISBN;
	string TenSach;
	int SoTrang;
	string TacGia;
	int NamXuatBan;
	string TheLoai;
	int soluotmuon = 0;
};


struct NodeDauSach{
	DauSach data;
	LIST_DMS listDMS;/// chua danh sach cac danh muc sach cua dau sach do
};
typedef struct NodeDauSach NODEDAUSACH;
typedef NODEDAUSACH* pNODEDAUSACH;

struct ListDauSach{
	int n;
	NODEDAUSACH* ListDS[MAXDS];
};
typedef struct ListDauSach LIST_DS;

//-------------------END struct DauSach-------------


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
typedef NODE_MUONTRA* pNODE_MUONTRA;

struct listMuonTra{
	int n;
	NODE_MUONTRA *pHead;
	NODE_MUONTRA *pTail;
};
typedef struct listMuonTra LIST_MUONTRA;

//struct nodeQuaHan
//{
//	unsigned int MATHE;
//	string HoTen;
//	string MaSach;
//	string TenSach;
//	Date NgayMuon;
//	int SoNgayQuaHan;
//};
//typedef struct nodeQuaHan NODEQUAHAN;

struct nodeQuaHanr
{
	unsigned int MATHE;
	int SoNgayQuaHan;
};
typedef struct nodeQuaHanr NODEQUAHANR;

//----------------END struct muon tra-------------------


struct TheDocGia{
	unsigned int MATHE;
	string Ho;
	string Ten;
	int Phai; /// 0: nu, 1 nam
	int TrangThai;
	
};

struct nodeTheDocGia{
	TheDocGia data;
	struct nodeTheDocGia *pLeft;
	struct nodeTheDocGia *pRight;
	LIST_MUONTRA listMuonTra;
};
typedef struct nodeTheDocGia NODETHEDOCGIA;
typedef NODETHEDOCGIA* TREE;
//--------------------END struct the doc gia----------------------


//-------------------Biến toàn cục-------------------------
int nDocGia = 0;
int vitri = 0;
int index= 0;
const int ngayTrongThang[12] = { 31, 28, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31 };

void KhoiTaoDanhMucSach(LIST_DMS &l);
NODE_DMS* KhoiTaoNodeDMS(DanhMucSach dms);
void ThemVaoCuoi(LIST_DMS &l, NODE_DMS *p);
void Init(LIST_MUONTRA &l);
void AddTailMT(LIST_MUONTRA &l, NODE_MUONTRA *p);
string NhapISBN();
int TimKiemDauSach(LIST_DS lds, string ISBN);
void InDanhSachDauSach(LIST_DS lds, int w[]);
NODE_DMS* TimKiemDanhMucSach(LIST_DMS &l, string maSach);
void InDanhSachDanhMucSach(LIST_DMS l, int w[]);
string TimTenSach(string maSach, LIST_DS lds, string &vitri);
int TinhKhoangCachNgay(Date d1, Date d2);
int TimViTriDauSachTuMaSach(LIST_DS lds, string maSach);
void LuuDuLieuDauSach(LIST_DS lds);
void DocDuLieuDauSach(LIST_DS &lds);
void SapXepTheoTheLoaiVaTenSach(LIST_DS lds, int w[]);
void InTieuDeDauSach(int w[]);
void AddHeadMT(LIST_MUONTRA &l, MuonTra data);
//-------------------END bien toan cuc------------------------


//--------------------------Chuẩn hóa chuỗi------------------------------
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
}

void ChuanHoaChuoiInHoa(string &str){
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

int checkNhapSo0va1(string str){
	foru(i, 0, str.length())
		if (!(str[i] == 48 || str[i] == 49))
			if (str[i] != '\0')
				return 0;
	return 1;
}

int checkNhapSo0va1va2(string str){
	foru(i, 0, str.length())
	if (!(str[i] == 48 || str[i] == 49 || str[i] == 50))
	if (str[i] != '\0')
		return 0;
	return 1;
}

int checkNhapSo(string str){
	//check nhap so
	foru(i, 0, str.length())
	if (!(str[i] >= 48 && str[i] <= 57))
	if (str[i] != '\0')
		return 0;

	return 1;
}

int checkNhapISBN(string str){
	//check nhap chu khong dau space
	foru(i, 0, str.length())
	if (!((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))){
		if (str[i] != '\0'){
			return 0;
		}
	}
	else if (str.length() > 6){
		return 0;
	}

	return 1;
}

int checkNhapMaSach(string str){
	//check nhap chu khong dau space
	foru(i, 0, str.length())
	if (!(((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) || (str[i] >= 48 && str[i] <= 57))){
		if (str[i] != '\0'){
			//cout << "Loi nhap so chu";
			return 0;
		}
	}
	return 1;
}

int LayNamHienTai(){
	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	return 1900 + ltm->tm_year;
}

int LayNgayHienTai(){
	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	return ltm->tm_mday;
}

int LayThangHienTai(){
	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	return 1 + ltm->tm_mon;
}

boolean nhuan(int nam){
	if ((nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0)
		return true;
	return false;
}

int songay(int thang, int nam){
	if (thang == 4 || thang == 6 || thang == 9 || thang == 11) return 30;
	if (thang == 2){
		if (nhuan(nam))
		return 28 + 1;
		else{
			return 28;
		}
	}
	return 31;
}

boolean okNgayThangNam(int ngay, int thang, int nam){
	if (thang<1 || thang >12) return false;
	if (ngay<1 || ngay>songay(thang, nam)) return false;
	if (nam<1900 || nam>LayNamHienTai()) return false;
	return true;
}

//-----------------END chuan hoa chuoi-------------------------


//--------------Start process cây tìm kiếm nhị phân Doc Gia-----------------

void KhoiTaoCay(TREE &t){
	t = NULL;
}

unsigned int Random()
{
	srand(time(0));
	int x = rand();
	return x;
}

int ThemNodeVaoCay(TREE &t, TheDocGia x){

	//neu cay rong
	if (t == NULL){
		NODETHEDOCGIA *p = new NODETHEDOCGIA;
		p->data = x;
		p->pLeft = NULL;
		p->pRight = NULL;
		Init(p->listMuonTra);
		t = p;//node p chinh la goc
		return 1;
	}
	else {
		
		//cay co ton tai phan tu
	     if(t->data.MATHE > x.MATHE){
			 Init(t->listMuonTra);
			ThemNodeVaoCay(t->pLeft, x);
			return 1;
		}
		else if(t->data.MATHE < x.MATHE){
			Init(t->listMuonTra);
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
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
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

boolean checkExitMaThe(TREE t, unsigned int mathe){
	if (t == NULL) return false;
	else if (t->data.MATHE == mathe) return true;
	else if (mathe < t->data.MATHE) return checkExitMaThe(t->pLeft, mathe);
	else return checkExitMaThe(t->pRight, mathe);
}

void NhapDocGia(TheDocGia &x, int w[], unsigned int mathe, int check){
	string phai, trangthai;
	string ho, ten;

	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, 11);

	ConsoleProcess::CreateBoxTitle(60, 3, "            NHAP THONG TIN DOC GIA", 50);
	x.MATHE = mathe;
	ConsoleProcess::CreateBoxAdd(60, 5, " Ma doc gia:", 50);
	ConsoleProcess::CreateBoxAdd(60, 6, " Nhap ho:", 50);
	ConsoleProcess::CreateBoxAdd(60, 7, " Nhap ten:", 50);
	ConsoleProcess::CreateBoxAdd(60, 8, " Nhap phai(0: Nu, 1:Nam):", 50);
	ConsoleProcess::CreateBoxAdd(60, 9, " Nhap trang thai(0: Khoa, 1: Hoat Dong):", 50);
	ConsoleProcess::CreateBoxEnd(60, 10, "", 50);
	ConsoleProcess::CreateBoxTitle(60, 15, "Thong Bao: ", 50);
	ConsoleProcess::gotoxy(74, 5);
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	cout << x.MATHE;
	nhapho:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(74, 6);
	ConsoleProcess::ShowCur(1);
	getline(cin, ho);
	if (checkNhapChu(ho) == 0 || ho==""){
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72,15);
		cout << "Vui long nhap dung du lieu.Nhap lai";
		goto nhapho;
	}
	else{
		ConsoleProcess::gotoxy(72, 15);
		cout << "                                   ";
	}

nhapten:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(74, 7);
	ConsoleProcess::ShowCur(1);
	getline(cin, ten);
	if (checkNhapChu(ten) == 0 || ten == ""){
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "Vui long nhap dung du lieu.Nhap lai";
		goto nhapten;
	}
	else{
		ConsoleProcess::gotoxy(72, 15);
		cout << "                                   ";
	}
	
nhapphai:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(90, 8);
	ConsoleProcess::ShowCur(1);
	getline(cin, phai);
	if (checkNhapSo0va1(phai) == 0 || phai ==""){
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "Vui long nhap dung du lieu.Nhap lai";
		goto nhapphai;
	}
	else{
		ConsoleProcess::gotoxy(72, 15);
		cout << "                                   ";
	}
	if (check == 1){
	nhaptrangthai:
		SetConsoleTextAttribute(hConsoleColor, Normal_Color);
		ConsoleProcess::gotoxy(100, 9);
		ConsoleProcess::ShowCur(1);
		getline(cin, trangthai);
		if (checkNhapSo0va1(trangthai) == 0 || trangthai == ""){
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(72, 15);
			cout << "Vui long nhap dung du lieu.Nhap lai\n";
			goto nhaptrangthai;
		}
		else{
			ConsoleProcess::gotoxy(72, 15);
			cout << "                                   ";
		}
	}
	else{
		SetConsoleTextAttribute(hConsoleColor, Normal_Color);
		ConsoleProcess::gotoxy(100, 9);
		cout << "1";
		trangthai = "1";
	}

	ChuanHoaChuoiInHoa(ho);
	ChuanHoaChuoiInHoa(ten);
	x.Ho = ho;
	x.Ten = ten;
	x.Phai = stoi(phai);
	x.TrangThai = stoi(trangthai);
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

	fileout << t->listMuonTra.n << endl;
	for (NODE_MUONTRA* p = t->listMuonTra.pHead; p != NULL; p = p->pNext)
	{
		fileout << p->data.MaSach << endl;

		fileout << p->data.NgayMuon.Ngay << endl;
		fileout << p->data.NgayMuon.Thang << endl;
		fileout << p->data.NgayMuon.Nam << endl;

		fileout << p->data.NgayTra.Ngay << endl;
		fileout << p->data.NgayTra.Thang << endl;
		fileout << p->data.NgayTra.Nam << endl;

		fileout << p->data.TrangThai << endl;
		
	}

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

void DocDuLieuDocGia(TREE &t){

	KhoiTaoCay(t);

	fstream filein;
	MuonTra mt;
	TheDocGia tdg;
	int soDocGia;
	int soSach;
	int index;
	filein.open(databasedocgia, ios::in);

	if (filein.is_open()){
		string temp;
		filein >> soDocGia;
		for (int i = 0; i < soDocGia; i++)
		{
			NODETHEDOCGIA *p = new NODETHEDOCGIA;
			
			filein >> tdg.MATHE;
			getline(filein, temp);
			getline(filein, tdg.Ho);
			getline(filein, tdg.Ten);
			filein >> tdg.Phai;
			filein >> tdg.TrangThai;
			ThemNodeVaoCay(t, tdg);
			p = TimKiemDocGia(t, tdg.MATHE);

			filein >> soSach;
			Init(p->listMuonTra);
			for (int j = 0; j < soSach; j++)
			{
				//NODE_MUONTRA *nmt = new NODE_MUONTRA;
				
				getline(filein, temp);
				getline(filein, mt.MaSach);
				filein >> mt.NgayMuon.Ngay;
				filein >> mt.NgayMuon.Thang;
				filein >> mt.NgayMuon.Nam;
				filein >> mt.NgayTra.Ngay;
				filein >> mt.NgayTra.Thang;
				filein >> mt.NgayTra.Nam;
				filein >> mt.TrangThai;
				//nmt->data = *mt;
				// cap nhat du lieu vao
				AddHeadMT(p->listMuonTra, mt);
				/*index = TimViTriDauSachTuMaSach(lds,nmt->data.MaSach);
				lds.ListDS[index]->data.soluotmuon++;*/
			}

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
				DiTimNodeTheMang(x, t->pRight);
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
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "-------Thong tin doc gia can hieu chinh--------"<<endl;
	cout << "-------Ma The: " << tdg.MATHE <<"  ------------"<<endl;
	cout << "-------Ho: " << tdg.Ho << "  ------------" << endl;;
	cout << "-------Ten: " << tdg.Ten << "  ------------" << endl;;

	(tdg.Phai == 1) ? cout << "-------Phai: " << "NAM ----" << endl : cout << "-------Phai: " << "NU ----" << endl;
	(tdg.TrangThai == 1) ? cout << "-------Trang thai: " << "Hoat Dong ----" << endl : cout << "-------Trang Thai: " << "Khoa----" << endl;;

	//cout << "---------Nhap thong tin can chinh sua--------"<<endl;
	NhapDocGia(tdg, w, maThe,1);
	
}

void ThemNodeVaoCayTheoTenHo(TREE &t, TheDocGia x){

	//neu cay rong
	if (t == NULL){
		NODETHEDOCGIA *p = new NODETHEDOCGIA;
		p->data = x;
		p->pLeft = NULL;
		p->pRight = NULL;
		t = p;//node p chinh la goc
	}
	else {
		//cay co ton tai phan tu
		if (t->data.Ten > x.Ten){
			ThemNodeVaoCayTheoTenHo(t->pLeft, x);
		}
		else if (t->data.Ten < x.Ten){
			ThemNodeVaoCayTheoTenHo(t->pRight, x);
		}
		else{
			if (t->data.Ho > x.Ho){
				ThemNodeVaoCayTheoTenHo(t->pLeft, x);
			}
			else if (t->data.Ho < x.Ho){
				ThemNodeVaoCayTheoTenHo(t->pRight, x);
			}
			else{
				ThemNodeVaoCayTheoTenHo(t->pLeft, x);
			}
		}
	}
}

void InDanhSachDocGiaTheoTenHo(TREE t, TREE &temp){
	if (t != NULL){
		InDanhSachDocGiaTheoTenHo(t->pLeft, temp);
		ThemNodeVaoCayTheoTenHo(temp, t->data);
		InDanhSachDocGiaTheoTenHo(t->pRight, temp);
	}
}

void Free(TREE &t)
{
	if (t == NULL)
		return;
	Free(t->pLeft);
	Free(t->pRight);
	free(t);
}

void CapNhatDanhSachCacDocGia(TREE &t){
	
	/// danh sach gom 5 cot mathe, ho, ten, gioitinh, trang thai
	int w[6] = { 27, 10, 30, 20, 35, 45 };
	Menu a(35, 60, 1);
	a.Set_Header("QUAN LY DOC GIA");
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
		
		InTieuDe(w);
		InDanhSachDocGia(t,w);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(75, 1);
		cout << "----DANH SACH DOC GIA TANG THEO MA---\n";
		SetConsoleTextAttribute(hConsoleColor, 15);
		getch();
	}
	if (k == 2){
		TREE temp = NULL;
		InDanhSachDocGiaTheoTenHo(t, temp);
		InTieuDe(w);
		InDanhSachDocGia(temp, w);
		Free(temp);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(75, 1);
		cout << "----DANH SACH DOC GIA TANG THEO TEN HO---\n";
		SetConsoleTextAttribute(hConsoleColor, 15);
		getch();
	}

	if (k == 3) {
		system("cls");
		unsigned int mathe;

		do
		{
			mathe = Random();
		} while (checkExitMaThe(t, mathe));

		TheDocGia *p = new TheDocGia;
		NhapDocGia(*p, w, mathe,0);
		int check = ThemNodeVaoCay(t, *p);
		if (check == 1){
			LuuDuLieuDocGia(t);
			DocDuLieuDocGia(t);
			ConsoleProcess::ThongBao(72, 15, "Them doc gia thanh cong", 1);
		}
		else ConsoleProcess::ThongBao(72, 15, "Them doc gia that bai", 0);
		getch();
		
	}
	if (k == 4){
		InTieuDe(w);
		InDanhSachDocGia(t, w);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(75, 1);
		cout << "----DANH SACH DOC GIA TANG THEO MA---\n";
		
		ConsoleProcess::CreateBoxTitle(29, 3, "Nhap ma doc gia can hieu chinh: ", 60);
		ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 60);
		string maDocGia;
	nhapmadocgiahieuchinh:
		ConsoleProcess::ShowCur(1);
		ConsoleProcess::gotoxy(62, 3);
		getline(cin, maDocGia);
		if (checkNhapSo(maDocGia) == 0 || maDocGia == ""){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
			goto nhapmadocgiahieuchinh;
		}
		else{
			ConsoleProcess::gotoxy(42, 6);
			cout << "                                                        ";
		}

		NODETHEDOCGIA *p = TimKiemDocGia(t, stoi(maDocGia));
		if (p == NULL) {
			ConsoleProcess::gotoxy(42, 6);
			cout << "Ma doc gia " << maDocGia << " khong ton tai!";
			getch();
		}
		else{
			HieuChinhDocGia(t, p->data, w);
			LuuDuLieuDocGia(t);
			DocDuLieuDocGia(t);
			ConsoleProcess::ThongBao(72, 15, "Hieu chinh doc gia thanh cong", 1);
		}
		
	}
	if (k == 5){
		InTieuDe(w);
		InDanhSachDocGia(t, w);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(75, 1);
		cout << "----DANH SACH DOC GIA TANG THEO MA---\n";
		//SetConsoleTextAttribute(hConsoleColor, 15);
		ConsoleProcess::CreateBoxTitle(29, 3, "Nhap ma doc gia can xoa: ", 60);
		ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 60);

		string madocgia;
	nhapmadocgiaxoa:
		ConsoleProcess::ShowCur(1);
		ConsoleProcess::gotoxy(62, 3);
		getline(cin, madocgia);
		if (checkNhapSo(madocgia) == 0 || madocgia == ""){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
			goto nhapmadocgiaxoa;
		}
		else{
			ConsoleProcess::gotoxy(42, 6);
			cout << "                                                      ";

		}
		NODETHEDOCGIA *p = TimKiemDocGia(t, stoi(madocgia));
		if (p == NULL){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Ma doc gia " << madocgia << " khong ton tai!";
			getch();
			return;
		}
		if (p->listMuonTra.pHead != NULL){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Doc gia da muon sach, Khong duoc xoa.";
			getch();
		}
		else{

			int check = XoaDocGia(t, stoi(madocgia));
			if (check == 1){
				LuuDuLieuDocGia(t);
				DocDuLieuDocGia(t);
				ConsoleProcess::ThongBao(42, 6, "Xoa doc gia thanh cong", 1);
			}
			else {
				ConsoleProcess::gotoxy(42, 6);
				cout << "Ma doc gia " << madocgia << " khong ton tai!";
				getch();
			}
		}
	}
}
//-----------------------------END process Cay Nhi Phan Tim kiem Doc Gia---------------------------------

//-----------------------------Start process Muon tra------------------------------------------
void Init(LIST_MUONTRA &l)
{
	 l.n = 0;
	 l.pHead = NULL; // Con tro dau tro den NULL
	 l.pTail = NULL; // Con tro cuoi tro den NULL
}

int Isempty(LIST_MUONTRA l) //kiem tra DS rong
{
	return (l.pHead == NULL);
}

void InTieuDeMuonTra(int w[]){

	system("cls");
	cout << endl;
	cout << endl;

	int sum = 0;
	foru(i, 1, 6) sum = sum + w[i];

	/// dong 1
	foru(i, 1, w[0] + 1) cout << " "; foru(i, 1, sum - 2) cout << "_"; cout << endl;

	/// dong 2
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
	foru(i, 2, 6){
		foru(j, 1, w[i] - 1)cout << " ";
		cout << "\xb3";
	}
	cout << endl;

	/// dong 3
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	ConsoleProcess::InTungPhanTu_XauMau("MA SACH", w[1] - 1, -1);
	ConsoleProcess::InTungPhanTu_XauMau("TEN SACH", w[2], -1);
	ConsoleProcess::InTungPhanTu_XauMau("NGAY MUON", w[3], -1);
	ConsoleProcess::InTungPhanTu_XauMau("NGAY TRA", w[4], -1);
	ConsoleProcess::InTungPhanTu_XauMau("SO NGAY DA MUON", w[5], -1);
	ConsoleProcess::InTungPhanTu_XauMau("TRANG THAI", w[6], -1);
	cout << endl;

	/// dong 4
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
	foru(i, 2, 6){
		foru(j, 1, w[i] - 1)cout << "_";
		cout << "\xb3";
	}
	cout << endl;
}

void InDongDuLieuMuonTra(LIST_MUONTRA l, LIST_DS lds, int w[]){
	string vitri;
	string ngaymuon;
	string ngaytra;
	Date d2;
	d2.Ngay = LayNgayHienTai();
	d2.Thang = LayThangHienTai();
	d2.Nam = LayNamHienTai();
	/// in cac dong sau
	if (l.n == 0) return;
	for (NODE_MUONTRA *p = l.pHead; p != NULL; p = p->pNext){
		if (p->data.TrangThai == 0){
			ngaymuon = "";
			ngaytra = "";
			/// in dong trang
			foru(i, 1, w[0]) cout << " "; cout << "\xb3";
			foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
			foru(i, 2, 6){
				foru(j, 1, w[i] - 1)cout << " ";
				cout << "\xb3";
			}
			cout << endl;

			/// in dong du lieu

			foru(i, 1, w[0]) cout << " "; cout << "\xb3";
			ConsoleProcess::InTungPhanTu_Xau(p->data.MaSach, w[1] - 1, -1);
			ConsoleProcess::InTungPhanTu_Xau(TimTenSach(p->data.MaSach, lds, vitri), w[2], -1);
			
			
			if (p->data.NgayMuon.Ngay < 10) {
				ngaymuon.append("0");
				ngaymuon.append(ConsoleProcess::convert(p->data.NgayMuon.Ngay));
				ngaymuon.append("/");
			}
			else {
				ngaymuon.append(ConsoleProcess::convert(p->data.NgayMuon.Ngay));
				ngaymuon.append("/");
			}
			if (p->data.NgayMuon.Thang < 10) {
				ngaymuon.append("0");
				ngaymuon.append(ConsoleProcess::convert(p->data.NgayMuon.Thang));
				ngaymuon.append("/");
			}
			else {
				ngaymuon.append(ConsoleProcess::convert(p->data.NgayMuon.Thang));
				ngaymuon.append("/");
			}
			ngaymuon.append(ConsoleProcess::convert(p->data.NgayMuon.Nam));

			ConsoleProcess::InTungPhanTu_Xau(ngaymuon, w[3], -1);

			if (p->data.NgayTra.Ngay < 10) {
				ngaytra.append("0");
				ngaytra.append(ConsoleProcess::convert(p->data.NgayTra.Ngay));
				ngaytra.append("/");
			}
			else {
				ngaytra.append(ConsoleProcess::convert(p->data.NgayTra.Ngay));
				ngaytra.append("/");
			}
			if (p->data.NgayMuon.Thang < 10) {
				ngaytra.append("0");
				ngaytra.append(ConsoleProcess::convert(p->data.NgayTra.Thang));
				ngaytra.append("/");
			}
			else {
				ngaytra.append(ConsoleProcess::convert(p->data.NgayTra.Thang));
				ngaytra.append("/");
			}
			if (p->data.NgayTra.Nam==0)
			ngaytra.append("0000");

			ConsoleProcess::InTungPhanTu_Xau(ngaytra, w[4], -1);
			ConsoleProcess::InTungPhanTu_Xau(ConsoleProcess::convert(TinhKhoangCachNgay(p->data.NgayMuon,d2)), w[5], -1);
			if (p->data.TrangThai == 0)
				ConsoleProcess::InTungPhanTu_Xau("Dang Muon", w[6], -1);
			if (p->data.TrangThai == 1)
				ConsoleProcess::InTungPhanTu_Xau("Da Tra", w[6], -1);
			if (p->data.TrangThai == 2)
				ConsoleProcess::InTungPhanTu_Xau("Da Lam Mat", w[6], -1);
			cout << endl;

			/// in dong _
			foru(i, 1, w[0]) cout << " "; cout << "\xb3";
			foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
			foru(i, 2, 6){
				foru(j, 1, w[i] - 1)cout << "_";
				cout << "\xb3";
			}
			cout << endl;
		}
	}

}

NODE_MUONTRA* KhoiTaoNodeMT(MuonTra mt){
	NODE_MUONTRA *p = new NODE_MUONTRA;//Cap phat vung nho cho con tro
	if (p == NULL) {
		cout << "\nKhong du vung nho de cap phat";
		return NULL;
	}
	p->data = mt;
	p->pPrev = NULL;
	p->pNext = NULL;
	return p;
}

void AddHeadMT(LIST_MUONTRA &l, MuonTra data) {
	NODE_MUONTRA *mt = KhoiTaoNodeMT(data);
	if (l.pHead == NULL) {
		l.pHead = l.pTail = mt;
	}
	else{
		l.pHead->pPrev = mt;
		mt->pNext = l.pHead;
		l.pHead = mt;
	}
	++l.n;
}

void AddTailMT(LIST_MUONTRA &l, NODE_MUONTRA *p){
	
	NODE_MUONTRA *mt = KhoiTaoNodeMT(p->data);
	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
		//l.pTail->pNext = NULL;
		++l.n;
		return;
	}
	else
	{
		l.pTail->pNext = p;
		p->pPrev = l.pTail;
		l.pTail = p;
		//l.pTail->pNext = NULL;
		++l.n;
		return;
	}
	
}

void GiaiPhongDanhSachLKK(LIST_MUONTRA &l){
	NODE_MUONTRA *k;
	while (l.pHead != NULL){
		k = l.pHead;
		l.pHead = l.pHead->pNext;
		delete k;
	}
}

string TimTenSach(string maSach, LIST_DS lds, string &vitri){
	int index = TimViTriDauSachTuMaSach(lds, maSach);
	NODE_DMS *dms;
	dms = TimKiemDanhMucSach(lds.ListDS[index]->listDMS, maSach);
		if (dms != NULL){
			vitri = dms->data.ViTri;
			return lds.ListDS[index]->data.TenSach;
		}
}

NODE_MUONTRA *TimNodeMuonTra(NODETHEDOCGIA* dg, string maSach){
	for (NODE_MUONTRA *p = dg->listMuonTra.pHead; p != NULL; p = p->pNext){
		if (p->data.MaSach == maSach)
			return p;
	}
	return NULL;
}

int demSoNamNhuan(Date d){
	int nam = d.Nam;
	//Kiem tra nam hien tai co can xem xet cho so nam nhuan hay khong
	if (d.Thang <= 2) nam--;
	//Mot nam la mot nam nhuan neu no chia het cho 4 va khong chia het cho 100 hoac chia het cho 400
	return nam / 4 - nam / 100 + nam / 400;
}

int TinhKhoangCachNgay(Date d1, Date d2){
	
	long int n1 = d1.Nam * 365 + d1.Ngay;
	for (int i = 0; i < d1.Thang - 1; i++)
		n1 += ngayTrongThang[i];
	//Neu la nam nhuan tang them 1 ngay
	n1 += demSoNamNhuan(d1);

	long int n2 = d2.Nam * 365 + d2.Ngay;
	for (int i = 0; i < d2.Thang - 1; i++)
		n2 += ngayTrongThang[i];
	//Neu la nam nhuan tang them 1 ngay
	n2 += demSoNamNhuan(d2);

	return (n2 - n1);
}

int KiemTraSachDangMuon(NODETHEDOCGIA* dg, NODE_MUONTRA *mt){

	for (NODE_MUONTRA *p = dg->listMuonTra.pHead; p != NULL; p = p->pNext){
		if (p->data.MaSach == mt->data.MaSach && 
			p->data.NgayMuon.Ngay == mt->data.NgayMuon.Ngay &&
			p->data.NgayMuon.Thang == mt->data.NgayMuon.Thang &&
			p->data.NgayMuon.Nam == mt->data.NgayMuon.Nam){
			return 1;
		}

	}
	return 0;
}

void MuonSach(TREE &t,LIST_MUONTRA &l, TREE &dg, LIST_DS &lds){
	
	int w[7] = { 24, 10, 45, 10, 35, 18, 25 };
	int w2[4] = { 20, 20, 35, 20 };
	string masach[] = {""};
	int dem = 0;
	Date d2;
	d2.Ngay = LayNgayHienTai();
	d2.Thang = LayThangHienTai();
	d2.Nam = LayNamHienTai();
	if (dg->data.TrangThai == 0) {
		ConsoleProcess::CreateBoxTitle(29, 15, "Thong Bao: ", 70);
		ConsoleProcess::gotoxy(42, 15);
		cout<< "The Doc Gia Nay Da Bi Khoa. Khong duoc muon sach";
		getch();
		return;
	}
	system("cls");
	cout << endl;
	cout << "----------------THONG TIN DOC GIA-----------------\n";
	cout << "--------------------------------------------------\n";
	cout << "----Ma Doc Gia: " << dg->data.MATHE << endl;
	cout << "--------------------------------------------------\n";
	cout << "----Ho: " << dg->data.Ho << endl;
	cout << "--------------------------------------------------\n";
	cout << "----Ten: " << dg->data.Ten << endl;
	cout << "--------------------------------------------------\n";
	cout << "----Trang thai the: ";
	if (dg->data.TrangThai == 1) cout << "Dang hoat dong" << endl;
	cout << "--------------------------------------------------\n";
	cout << "--------------------------------------------------\n";
	cout << "---------------------Cac Sach Dang muon--------------------\n";
	if (dg->listMuonTra.pHead == NULL) cout << "Hien chua muon sach nao\n";
	string vitri;
	int ngaydamuon;
	boolean isQuaHan = FALSE;
	for (NODE_MUONTRA *p = dg->listMuonTra.pHead; p != NULL; p = p->pNext){
		if (p->data.TrangThai == 0){
			cout << "Ma Sach: " << p->data.MaSach << endl;
			cout << "Ten Sach: " << TimTenSach(p->data.MaSach, lds, vitri) << endl;
			cout << "Ngay Muon: ";
			if (p->data.NgayMuon.Ngay < 10) cout << "0" << p->data.NgayMuon.Ngay << "/";
			else cout << p->data.NgayMuon.Ngay << "/";
			if (p->data.NgayMuon.Thang < 10) cout << "0" << p->data.NgayMuon.Thang << "/";
			else cout << p->data.NgayMuon.Thang << "/";
			cout << p->data.NgayMuon.Nam << endl;
			cout << "Vi tri: " << vitri << endl;
			ngaydamuon = TinhKhoangCachNgay(p->data.NgayMuon, d2);
			cout << "Tong ngay da muon: ";
			cout << ngaydamuon << endl;
			cout << "--------------------------------------------------\n";
			if (ngaydamuon >= 7)
				isQuaHan = TRUE;
		}
		
		
	}
	cout << "Nhan bat ky phim de muon sach.";
	getch();

	if (isQuaHan == TRUE){
		ConsoleProcess::CreateBoxTitle(50, 6, "Thong Bao: ", 75);
		ConsoleProcess::gotoxy(60, 6);
		cout << "Ban da muon sach qua thoi han. Khong cho muon nua.";
		getch();
		return;
	}
	if (dg->listMuonTra.n < 3){
		InTieuDeDauSach(w);

		SapXepTheoTheLoaiVaTenSach(lds, w);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(75, 1);
		cout << "----DANH SACH DAU SACH THEO THE LOAI VA TEN SACH---\n";

		ConsoleProcess::CreateBoxTitle(29, 3, "Nhap ISBN can muon: ", 70);
		ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 70);


		string ISBN = NhapISBN();
		int vitri = TimKiemDauSach(lds, ISBN);
		for (NODE_MUONTRA *p = dg->listMuonTra.pHead; p != NULL; p = p->pNext){
			if (vitri == TimViTriDauSachTuMaSach(lds, p->data.MaSach) && p->data.TrangThai == 0){
				ConsoleProcess::gotoxy(42, 6);
				cout << "Ban Da Muon Sach Nay, Vui Long Muon Sach Khac!";
				getch();
				return;
			}
		}

		
		if (vitri == -1) {
			ConsoleProcess::gotoxy(42, 6);
			cout << "Dau sach " << ISBN << " khong ton tai!";
			getch();
			return;
		}
		else{
			if (lds.ListDS[vitri]->listDMS.n == 0){ 
				ConsoleProcess::gotoxy(42, 6);
				cout << "Danh Sach rong, hien chua co sach!";
				getch();
				return;
			}

			InDanhSachDanhMucSach(lds.ListDS[vitri]->listDMS, w2);

			HANDLE hConsoleColor;
			hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsoleColor, 6);
			ConsoleProcess::gotoxy(60, 1);
			cout << "----DANH SACH DANH MUC SACH---\n";

			ConsoleProcess::CreateBoxTitle(29, 3, "Nhap ma sach can muon: ", 70);
			ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 70);


			string maSach;
			nhapmasachmuon:
			ConsoleProcess::gotoxy(62, 3);
			ConsoleProcess::ShowCur(1);
			getline(cin, maSach);
			if (checkNhapMaSach(maSach) == 0 || maSach==""){
				ConsoleProcess::gotoxy(42, 6);
				cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.";
				goto nhapmasachmuon;
			}
			else{
				ConsoleProcess::gotoxy(42, 6);
				cout << "                                                      ";
			}
			NODE_DMS *pp = TimKiemDanhMucSach(lds.ListDS[vitri]->listDMS, maSach);
			if (pp == NULL) {
				ConsoleProcess::gotoxy(42, 6);
				cout << "Ma Sach " << maSach << " khong ton tai!";
				getch();
				return;
			}
			else{
				if (pp->data.TrangThai == 1)  {
					ConsoleProcess::gotoxy(42, 6);
					cout << "Sach nay da co doc gia muon!";
					getch();
					return;
				}
				if (pp->data.TrangThai == 2)  {
					ConsoleProcess::gotoxy(42, 6);
					cout << "Sach nay da duoc thanh ly!";
					getch();
					return;
				}
				ConsoleProcess::gotoxy(42, 6);
				cout << "                                                      ";
				NODE_MUONTRA *nmt = new NODE_MUONTRA;
				MuonTra mt;
				mt.MaSach = maSach;
				mt.NgayMuon.Ngay = LayNgayHienTai();
				mt.NgayMuon.Thang = LayThangHienTai();
				mt.NgayMuon.Nam = LayNamHienTai();
				mt.NgayTra.Ngay = 0;
				mt.NgayTra.Thang = 0;
				mt.NgayTra.Nam = 0;
				mt.TrangThai = 0;
				//nmt->data = *mt;
				/*if (KiemTraSachDangMuon(dg, nmt)==1){
					ConsoleProcess::gotoxy(42, 6);
					cout << "Sach nay ban da muon vao hom nay. Vui long den muon vao ngay mai!";
					getch();
					return;
				}*/
				
				pp->data.TrangThai = 1;
				lds.ListDS[vitri]->data.soluotmuon++;
				AddHeadMT(l, mt);
				LuuDuLieuDocGia(t);
				DocDuLieuDocGia(t);
				LuuDuLieuDauSach(lds);
				DocDuLieuDauSach(lds);
				ConsoleProcess::ThongBao(42, 6, "Muon sach thanh cong", 1);
			}
		}
	}
	else{
		ConsoleProcess::CreateBoxTitle(50, 6, "Thong Bao: ", 75);
		ConsoleProcess::gotoxy(60, 6);
		cout << "Moi doc gia chi duoc muon toi da 3 cuon sach.";
		getch();
		return;
	}
	return;

}

void TraSach(TREE &t, NODETHEDOCGIA* &dg, LIST_DS &lds){
	Date d2;
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	d2.Ngay = LayNgayHienTai();
	d2.Thang = LayThangHienTai();
	d2.Nam = LayNamHienTai();
	system("cls");
	cout << endl;
	cout << "----------------THONG TIN DOC GIA-----------------\n";
	cout << "--------------------------------------------------\n";
	cout << "----------Ma Doc Gia: " << dg->data.MATHE << endl;
	cout << "--------------------------------------------------\n";
	cout << "----------Ho: " << dg->data.Ho << endl;
	cout << "--------------------------------------------------\n";
	cout << "----------Ten: " << dg->data.Ten << endl;
	cout << "--------------------------------------------------\n";
	cout << "---------Trang thai the: ";
	if (dg->data.TrangThai == 1) cout << "Dang hoat dong" << endl;
	cout << "--------------------------------------------------\n";
	cout << "--------------------------------------------------\n";
	cout << "---------------------Cac Sach Dang muon--------------------\n";
	if (dg->listMuonTra.pHead == NULL) {
		ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(90, 18);
		cout << "Ban Chua Muon Sach Nao!.\n";
		return;
	}
	string vitri;
	int ngaydamuon;
	for (NODE_MUONTRA *p = dg->listMuonTra.pHead; p != NULL; p = p->pNext){
		if (p->data.TrangThai == 0){
			cout << "   Ma Sach: " << p->data.MaSach << endl;
			cout << "   Ten Sach: " << TimTenSach(p->data.MaSach, lds, vitri) << endl;
			cout << "   Ngay Muon: ";
			if (p->data.NgayMuon.Ngay < 10) cout << "0" << p->data.NgayMuon.Ngay << "/";
			else cout << p->data.NgayMuon.Ngay << "/";
			if (p->data.NgayMuon.Thang < 10) cout << "0" << p->data.NgayMuon.Thang << "/";
			else cout << p->data.NgayMuon.Thang << "/";
			cout << p->data.NgayMuon.Nam << endl;
			cout << "   Vi tri: " << vitri << endl;
			ngaydamuon = TinhKhoangCachNgay(p->data.NgayMuon, d2);
			cout << "   Tong ngay da muon: ";
			cout << ngaydamuon << endl;
			cout << "--------------------------------------------------\n";
		}
	}
	
	string maSach;
	string ngay, thang, nam;
	int vitri1=-1;
	nhapmasachtra:
	cout << "Nhap ma sach can tra: ";
	getline(cin, maSach);
	if (checkNhapMaSach(maSach) == 0 || maSach == ""){
		ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(90, 18);
		cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
		goto nhapmasachtra;
	}
	else{
		ConsoleProcess::gotoxy(90, 18);
		cout << "                                                     ";
	}





	NODE_MUONTRA* p = TimNodeMuonTra(dg, maSach);
	if (p == NULL)  {
		ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(90, 18);
		cout << "Khong tim thay ma sach vua nhap!\n";
		return;
	}
	else{
		ConsoleProcess::gotoxy(90, 18);
		cout << "                                                     ";
	}

	
	SetConsoleTextAttribute(hConsoleColor, 11);
	ConsoleProcess::CreateBoxTitle(80, 15, "Nhap Chuc Nang(0: Tra Sach, 1: Bao Mat Sach): ", 70);
	
	string nhap;
    nhap:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(125, 15);
	ConsoleProcess::ShowCur(1);
	getline(cin, nhap);
	if (checkNhapSo0va1(nhap) == 0 || nhap == ""){

		ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(90, 18);
		cout << "Vui long nhap dung du lieu.Nhap lai\n";
		goto nhap;
	}
	else{
		ConsoleProcess::gotoxy(90, 18);
		cout << "                                        ";
	}

	if (stoi(nhap) == 0){
		ConsoleProcess::CreateBoxTitle(80, 21, "Nhap ngay tra: ", 70);
		ConsoleProcess::gotoxy(116,21);
		cout << "   /  /     ";

		nhapngay:
		ConsoleProcess::gotoxy(116, 21);
		getline(cin, ngay);
		if (checkNhapSo(ngay) == 0 || ngay == "" || stoi(ngay) > 31 || stoi(ngay) < 1 ){
			ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(90, 18);
			cout << "Ngay khong hop le. Nhap lai\n";
			goto nhapngay;
		}
		else{
			ConsoleProcess::gotoxy(90, 18);
			cout << "                                         ";
		}

		nhapthang:
		ConsoleProcess::gotoxy(120, 21);
		getline(cin, thang);
		if (checkNhapSo(thang) == 0 || thang == "" || stoi(thang) > 12 || stoi(thang) < 1){
			ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(90, 18);
			cout << "Thang khong hop le. Nhap lai\n";
			goto nhapthang;
		}
		else{
			ConsoleProcess::gotoxy(90, 18);
			cout << "                                         ";
		}

		nhapnam:
		ConsoleProcess::gotoxy(124, 21);
		getline(cin, nam);
		if (checkNhapSo(nam) == 0 || nam == "" || stoi(nam) > LayNamHienTai() || stoi(nam) < 1900){
			ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(90, 18);
			cout << "Nam khong hop le. Nhap lai";
			goto nhapnam;
		}
		else{
			ConsoleProcess::gotoxy(90, 18);
			cout << "                                         ";
		}

		if (!(okNgayThangNam(stoi(ngay), stoi(thang), stoi(nam)))){
			ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(90, 18);
			cout << "Ngay thang nam khong hop le.Nhap lai";
			goto nhapngay;
		}
		else{
			ConsoleProcess::gotoxy(90, 18);
			cout << "                                            ";
		}
		Date d1, d2, d3;
		d1.Ngay = stoi(ngay);
		d1.Thang = stoi(thang);
		d1.Nam = stoi(nam);
		d2.Ngay = LayNgayHienTai();
		d2.Thang = LayThangHienTai();
		d2.Nam = LayNamHienTai();
		d2.Ngay = LayNgayHienTai();
		d2.Thang = LayThangHienTai();
		d2.Nam = LayNamHienTai();
		//if (stoi(ngay) > LayNgayHienTai() || stoi(thang) > LayThangHienTai() || stoi(nam) > LayNamHienTai()){
			if (TinhKhoangCachNgay(d1,d2) < 0){
			ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(90, 18);
			cout << "Ngay thang nam khong lon hon hien tai.Nhap lai";
			goto nhapngay;
		}
		else{
			ConsoleProcess::gotoxy(90, 18);
			cout << "                                                  ";
		}
		if (TinhKhoangCachNgay(p->data.NgayMuon,d1) < 0){
			ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(90, 18);
			cout << "Ngay tra khong be hon ngay muon. Nhap lai";
			goto nhapngay;
		}
		else{
			ConsoleProcess::gotoxy(90, 18);
			cout << "                                               ";
		}

		p->data.NgayTra.Ngay = stoi(ngay);
		p->data.NgayTra.Thang = stoi(thang);
		p->data.NgayTra.Nam = stoi(nam);
		//chuyen trang thai da tra sach
		p->data.TrangThai = 1;
		//chuyen trang thai sach = 0: cho muon dc
		 vitri1 = TimViTriDauSachTuMaSach(lds, maSach);
		NODE_DMS* pDMS = TimKiemDanhMucSach(lds.ListDS[vitri1]->listDMS, maSach);
		pDMS->data.TrangThai = 0;
		lds.ListDS[vitri1]->data.soluotmuon--;
		dg->listMuonTra.n--;
		LuuDuLieuDauSach(lds);
		DocDuLieuDauSach(lds);
		LuuDuLieuDocGia(t);
		DocDuLieuDocGia(t);
		ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::ThongBao(90, 18, "Tra sach thanh cong", 1);

	}
	else if (stoi(nhap) == 1){
		if (p->data.TrangThai != 2){
			p->data.TrangThai = 2;
			vitri1 = TimViTriDauSachTuMaSach(lds, maSach);
			NODE_DMS* pDMS = TimKiemDanhMucSach(lds.ListDS[vitri1]->listDMS, maSach);
			pDMS->data.TrangThai = 2;
			lds.ListDS[vitri1]->data.soluotmuon--;
			LuuDuLieuDauSach(lds);
			DocDuLieuDauSach(lds);
			LuuDuLieuDocGia(t);
			DocDuLieuDocGia(t);
			ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(90, 18);
			cout << "Da bao mat sach.";
			getch();
		}
		else{
			ConsoleProcess::CreateBoxTitle(80, 18, "Thong Bao: ", 70);
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(90, 18);
			cout << "Sach nay da mat khong can bao.";
			getch();
		}
		
	}
	
}

int CapNhatMuonTra(TREE &t, LIST_MUONTRA &l, NODETHEDOCGIA* &dg, LIST_DS &lds){
	
	int w[7] = { 15, 20, 20, 20, 20, 20, 20 };
	Menu a(35, 60, 1);
	a.Set_Header("MENU LUA CHON");
	a.add("1. Muon Sach");
	a.add("2. Tra sach");
	a.add("3. Liet Ke Sach Dang Muon");
	a.add("4. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 4;
	if (k == 4) return 4;
	if (k == 1){
		MuonSach(t,l, dg, lds);
		getch();
		//return 4;
	}
	if (k == 2){
		TraSach(t, dg, lds);
		getch();
		//return 4;
	}
	if (k == 3) {
		InTieuDeMuonTra(w);
		InDongDuLieuMuonTra(dg->listMuonTra, lds, w);
		getch();
	}
	
}

void LayViTriNodeDuocChonMuonTra(TREE &t,LIST_DS &lds){
	int w[6] = { 20, 10, 30, 20, 35, 45 };
	InTieuDe(w);
	InDanhSachDocGia(t, w);

	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, 6);
	ConsoleProcess::gotoxy(75, 1);
	cout << "----DANH SACH DOC GIA TANG THEO MA---\n";

	ConsoleProcess::CreateBoxTitle(29, 3, "Nhap ma doc gia can quan ly: ", 70);
	ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 70);

	string maDocGia;
	nhapmadocgiaduocchon:
	ConsoleProcess::ShowCur(1);
	ConsoleProcess::gotoxy(62, 3);
	getline(cin, maDocGia);
	if (checkNhapSo(maDocGia) == 0 || maDocGia==""){
		ConsoleProcess::gotoxy(42, 6);
		cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
		goto nhapmadocgiaduocchon;
	}
	ConsoleProcess::gotoxy(42, 6);
	cout << "                                                            ";
	NODETHEDOCGIA *p = TimKiemDocGia(t, stoi(maDocGia));
	if (p == NULL) {
		ConsoleProcess::gotoxy(42, 6);
		cout << "Ma doc gia " << maDocGia << " khong ton tai!";
		getch();
	}
	else{
		//if (p->listMuonTra.n == 0) Init(p->listMuonTra);
		int check;
		while (true){
			check = CapNhatMuonTra(t, p->listMuonTra, p, lds);
			if (check == 4) {
				//GiaiPhongDanhSachLKK(p->listMuonTra);
				break;
			}
		}
	}
	
	return;
}
//-----------------------------End process Muon tra-------------------------------------------


//------------------------------Start process Dau Sach-----------------------------------------
void KhoiTaoDauSach(LIST_DS &lds){
	lds.n = -1;
}

int isEmpty(LIST_DS &lds){
	return lds.n == -1;
}

int isFull(LIST_DS &lds){
	return lds.n == MAXDS-1;
}

int KiemTraTonTaiISBN(LIST_DS lds, string ISBN){
	foru(i, 0, lds.n)
	if (lds.ListDS[i]->data.ISBN == ISBN)
		return 1;
	return 0;
}

int KiemTraTonTaiTenSach(LIST_DS lds, string tenSach, int vitri){
	foru(i, 0, lds.n)
	if (lds.ListDS[i]->data.TenSach == tenSach && i != vitri)
		return 1;
	return 0;
}

void InTieuDeDauSach(int w[]){

	system("cls");
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	int sum = 0;
	foru(i, 1, 6) sum = sum + w[i];

	/// dong 1
	foru(i, 1, w[0] + 1) cout << " "; foru(i, 1, sum - 2) cout << "_"; cout << endl;

	/// dong 2
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
	foru(i, 2, 6){
		foru(j, 1, w[i] - 1)cout << " ";
		cout << "\xb3";
	}
	cout << endl;

	/// dong 3
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	ConsoleProcess::InTungPhanTu_XauMau("ISBN", w[1] - 1, -1);
	ConsoleProcess::InTungPhanTu_XauMau("TEN SACH", w[2], -1);
	ConsoleProcess::InTungPhanTu_XauMau("SO TRANG", w[3], -1);
	ConsoleProcess::InTungPhanTu_XauMau("TAC GIA", w[4], -1);
	ConsoleProcess::InTungPhanTu_XauMau("NAM XUAT BAN", w[5], -1);
	ConsoleProcess::InTungPhanTu_XauMau("THE LOAI", w[6], -1);
	cout << endl;

	/// dong 4
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
	foru(i, 2, 6){
		foru(j, 1, w[i] - 1)cout << "_";
		cout << "\xb3";
	}
	cout << endl;
}

void InDongDuLieuDauSachTimKiem(LIST_DS lds, int w[], string TenSach){
	/// in cac dong sau
	if (lds.n == -1) return;
	system("cls");
	int dem = 0;
	foru(it, 0, lds.n){
		if (lds.ListDS[it]->data.TenSach == TenSach){
			dem++;
			cout << endl;
			cout << "-----------THONG TIN SACH DA TIM KIEM-------------\n";
			cout << "--------------------------------------------------\n";
			cout << "-----------ISBN: " << lds.ListDS[it]->data.ISBN << endl;
			cout << "--------------------------------------------------\n";
			cout << "-----------Ten Sach: " << lds.ListDS[it]->data.TenSach << endl;
			cout << "--------------------------------------------------\n";
			cout << "-----------So Trang: " << lds.ListDS[it]->data.SoTrang << endl;
			cout << "--------------------------------------------------\n";
			cout << "-----------Tac Gia: " << lds.ListDS[it]->data.TacGia << endl;
			cout << "--------------------------------------------------\n";
			cout << "-----------Nam Xuat Ban: " << lds.ListDS[it]->data.NamXuatBan << endl;
			cout << "--------------------------------------------------\n";
			cout << "-----------The Loai: " << lds.ListDS[it]->data.TheLoai << endl;
			cout << "--------------------------------------------------\n";
			cout << "---------------------Cac Ma Sach--------------------\n";
			if (lds.ListDS[it]->listDMS.pHead == NULL) cout << "Khong co ma sach nao!\n";
			for (NODE_DMS* p = lds.ListDS[it]->listDMS.pHead; p != NULL; p = p->pNext)
			{
				
				cout << "Ma: " << p->data.MaSach << "   " << "Trang Thai: ";
				if (p->data.TrangThai == 0)
					cout << "Cho Muon Duoc"<<endl;
				if (p->data.TrangThai == 1)
					cout << "Da Co Doc Gia Muon"<<endl;
				if (p->data.TrangThai == 2)
					cout << "Sach Da Thanh Ly" << endl;
				cout << "--------------------------------------------------\n";
			}
			
		}
		
	}
	if (dem == 0){
		ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 50);
		ConsoleProcess::gotoxy(42, 6);
		cout << "Ten Sach " << TenSach << " khong ton tai!";
	}

}

void InDongDuLieuDauSach(LIST_DS lds, int w[]){
	/// in cac dong sau
	if (lds.n == -1) return;
	foru(it,0, lds.n){
		/// in dong trang
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
		foru(i, 2, 6){
			foru(j, 1, w[i] - 1)cout << " ";
			cout << "\xb3";
		}
		cout << endl;

		/// in dong du lieu

		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		ConsoleProcess::InTungPhanTu_Xau(lds.ListDS[it]->data.ISBN, w[1] - 1, -1);
		ConsoleProcess::InTungPhanTu_Xau(lds.ListDS[it]->data.TenSach, w[2], -1);
		ConsoleProcess::InTungPhanTu_Xau(ConsoleProcess::convert(lds.ListDS[it]->data.SoTrang), w[3], -1);
		ConsoleProcess::InTungPhanTu_Xau(lds.ListDS[it]->data.TacGia, w[4], -1);
		ConsoleProcess::InTungPhanTu_Xau(ConsoleProcess::convert(lds.ListDS[it]->data.NamXuatBan), w[5], -1);
		ConsoleProcess::InTungPhanTu_Xau(lds.ListDS[it]->data.TheLoai, w[6], -1);
		cout << endl;

		/// in dong _
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
		foru(i, 2, 6){
			foru(j, 1, w[i] - 1)cout << "_";
			cout << "\xb3";
		}
		cout << endl;
	}

}

void Swap(pNODEDAUSACH ds1, pNODEDAUSACH ds2){
	NODEDAUSACH temp = *ds1;
	*ds1 = *ds2;
	*ds2 = temp;
}

void SapXepTheoTheLoaiVaTenSach(LIST_DS lds, int w[]){
	int j;
	for (int i = 0; i < lds.n ; i++){
		for (j = 0; j < lds.n - i; j++){
			if (lds.ListDS[j]->data.TheLoai > lds.ListDS[j+1]->data.TheLoai){
				Swap(lds.ListDS[j], lds.ListDS[j + 1]);
			}
			else if (lds.ListDS[j]->data.TheLoai == lds.ListDS[j + 1]->data.TheLoai){
				if (lds.ListDS[j]->data.TenSach > lds.ListDS[j + 1]->data.TenSach){
					Swap(lds.ListDS[j], lds.ListDS[j + 1]);
				}
			}
		}
	}
	InDongDuLieuDauSach(lds, w);
}

void NhapThongTin1DauSach(LIST_DS lds, DauSach &ds, int w[], int isISBN){
	string sotrang, namxuatban;

	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, 11);


	ConsoleProcess::CreateBoxTitle(60, 3, "            NHAP THONG TIN DAU SACH", 50);
	ConsoleProcess::CreateBoxAdd(60, 5, " Nhap ISBN(gom 6 ki tu chu):", 50);
	ConsoleProcess::CreateBoxAdd(60, 6, " Nhap Ten Sach: ", 50);
	ConsoleProcess::CreateBoxAdd(60, 7, " Nhap So Trang: ", 50);
	ConsoleProcess::CreateBoxAdd(60, 8, " Nhap Tac Gia: ", 50);
	ConsoleProcess::CreateBoxAdd(60, 9, " Nhap Nam Xuat Ban( < hon nam hien tai): ", 50);
	ConsoleProcess::CreateBoxAdd(60, 10, " Nhap The Loai: ", 50);
	ConsoleProcess::CreateBoxEnd(60, 11, "", 50);
	ConsoleProcess::CreateBoxTitle(60, 15, "Thong Bao: ", 70);
	
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	

	if (isISBN == 1){
	nhapISBN:
		SetConsoleTextAttribute(hConsoleColor, Normal_Color);
		ConsoleProcess::gotoxy(89, 5);
		ConsoleProcess::ShowCur(1);
		getline(cin, ds.ISBN);
		if (checkNhapISBN(ds.ISBN) == 0 || ds.ISBN == ""){
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(72, 15);
			cout << "Vui long nhap dung dinh dang. Nhap lai";
			goto nhapISBN;
		}
		else if (KiemTraTonTaiISBN(lds, ds.ISBN) == 1){
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(72, 15);
			cout << "ISBN da ton tai trong he thong. Nhap lai";
			goto nhapISBN;
		}
		else{
			ConsoleProcess::gotoxy(72, 15);
			cout << "                                         ";
		}
	}
	else{
		SetConsoleTextAttribute(hConsoleColor, Normal_Color);
		ConsoleProcess::gotoxy(89, 5);
		cout << ds.ISBN;
	}

	int check = TimKiemDauSach(lds, ds.ISBN);

	nhapTenSach:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(76, 6);
	ConsoleProcess::ShowCur(1);
	getline(cin, ds.TenSach);
	if (ds.TenSach == ""){
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "Vui long khong de trong. Nhap lai";
		goto nhapTenSach;
	}
	else if (KiemTraTonTaiTenSach(lds, ds.TenSach, check) == 1){
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "                                      ";
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "Ten Sach Da Ton Tai. Nhap lai";
		goto nhapTenSach;
	}
	else{
		ConsoleProcess::gotoxy(72, 15);
		cout << "                                         ";
	}

	nhapsotrang:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(76, 7);
	ConsoleProcess::ShowCur(1);
	getline(cin, sotrang);
	if (checkNhapSo(sotrang) == 0 || sotrang == ""){
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "Vui long nhap dung dinh dang. Nhap lai";
		goto nhapsotrang;
	}
	else{
			ConsoleProcess::gotoxy(72, 15);
			cout << "                                        ";
	}

	nhaptacgia:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(76, 8);
	ConsoleProcess::ShowCur(1);
	getline(cin, ds.TacGia);
	if (checkNhapChu(ds.TacGia) == 0||ds.TacGia==""){
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "Vui long nhap dung dinh dang. Nhap lai";
		goto nhaptacgia;
	}
	else{
		ConsoleProcess::gotoxy(72, 15);
		cout << "                                        ";
	}

	namxuatban:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(100, 9);
	ConsoleProcess::ShowCur(1);
	getline(cin, namxuatban);
	if (checkNhapSo(namxuatban) == 0 || namxuatban == ""){
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "Vui long nhap dung dinh dang. Nhap lai";
		goto namxuatban;
	}
	else{
		int nam = stoi(namxuatban);
		if (nam > LayNamHienTai()){
			SetConsoleTextAttribute(hConsoleColor, 12);
			ConsoleProcess::gotoxy(72, 15);
			cout << "Vui long nhap nam nho hon nam hien tai. Nhap lai";
			goto namxuatban;
		}
		else{
			ConsoleProcess::gotoxy(72, 15);
			cout << "                                                     ";
		}
	}

	nhaptheloai:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(76, 10);
	ConsoleProcess::ShowCur(1);
	getline(cin, ds.TheLoai);
	if (checkNhapChu(ds.TheLoai) == 0 || ds.TheLoai==""){\
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "Vui long nhap dung dinh dang. Nhap lai";
		goto nhaptheloai;
	}
	else{
		ConsoleProcess::gotoxy(72, 15);
		cout << "                                        ";
	}

	ChuanHoaChuoi(ds.TenSach);
	ChuanHoaChuoiInHoa(ds.TacGia);
	ChuanHoaChuoi(ds.TheLoai);
	
	ds.SoTrang = stoi(sotrang);
	ds.NamXuatBan = stoi(namxuatban);

}

int ThemDauSach(LIST_DS &lds, int w[]){
	if (isFull(lds)) return 0;

	NodeDauSach *pp = new NodeDauSach;
	DauSach *ds = new DauSach;
	NhapThongTin1DauSach(lds, *ds, w, 1);
	pp->data = *ds;
	lds.ListDS[++lds.n] = pp;
	KhoiTaoDanhMucSach(lds.ListDS[lds.n]->listDMS);
	return 1;
	
}

void InDanhSachDauSach(LIST_DS lds, int w[]){
	
	InTieuDeDauSach(w);
	InDongDuLieuDauSach(lds, w);
}

void GhiThongTinDanhSachDauSach(LIST_DS lds, fstream &fileout){
	fileout << lds.n + 1 << endl;
	for (int i = 0; i < lds.n; i++)
	{
		fileout << lds.ListDS[i]->data.ISBN << endl;
		fileout << lds.ListDS[i]->data.TenSach << endl;
		fileout << lds.ListDS[i]->data.TacGia << endl;
		fileout << lds.ListDS[i]->data.TheLoai << endl;
		fileout << lds.ListDS[i]->data.SoTrang << endl;
		fileout << lds.ListDS[i]->data.NamXuatBan << endl;

		fileout << lds.ListDS[i]->listDMS.n << endl;
		for (NODE_DMS* p = lds.ListDS[i]->listDMS.pHead; p != NULL; p = p->pNext)
		{
			fileout << p->data.MaSach << endl;
			fileout << p->data.TrangThai << endl;
			fileout << p->data.ViTri << endl;
		}
		
	}
}

void LuuDuLieuDauSach(LIST_DS lds){
	fstream fileout;
	fileout.open(databasedausach, ios::out);
	if (fileout.is_open())
	{
		
		fileout << lds.n + 1 << endl;
		for (int i = 0; i <= lds.n; i++)
		{
			fileout << lds.ListDS[i]->data.ISBN << endl;
			fileout << lds.ListDS[i]->data.TenSach << endl;
			fileout << lds.ListDS[i]->data.TacGia << endl;
			fileout << lds.ListDS[i]->data.TheLoai << endl;
			fileout << lds.ListDS[i]->data.SoTrang << endl;
			fileout << lds.ListDS[i]->data.NamXuatBan << endl;
			fileout << lds.ListDS[i]->data.soluotmuon << endl;
		
			fileout << lds.ListDS[i]->listDMS.n << endl;
			for (NODE_DMS* p = lds.ListDS[i]->listDMS.pHead; p != NULL; p = p->pNext)
			{
				fileout << p->data.MaSach << endl;
				fileout << p->data.TrangThai << endl;
				fileout << p->data.ViTri << endl;
			}
		}
	}
	else cout << "Loi ket noi file! ";
	fileout.close();
}

void DocThongTin1DauSach(DauSach &ds, fstream &filein){
	
	getline(filein, ds.ISBN);
	getline(filein, ds.TenSach);
	getline(filein, ds.TacGia);
	getline(filein, ds.TheLoai);
	filein >> ds.SoTrang;
	filein >> ds.NamXuatBan;
	filein >> ds.soluotmuon;
}

void DocDuLieuDauSach(LIST_DS &lds){

	KhoiTaoDauSach(lds);

	fstream filein;
	int sodausach;
	int sodanhmucsach;
	
	filein.open(databasedausach, ios::in);
	if (filein.is_open()){

		string temp;
		filein >> sodausach;
		getline(filein, temp);

		for (int i = 0; i < sodausach; i++)
		{
			
			NodeDauSach *p = new NodeDauSach;
			DauSach *ds = new DauSach;
			if (p == NULL) continue;
			
			
			DocThongTin1DauSach(*ds, filein);
			p->data = *ds;

			filein >> sodanhmucsach;
			getline(filein, temp);
			KhoiTaoDanhMucSach(p->listDMS);
			for (int j = 0; j < sodanhmucsach; j++)
			{
				DanhMucSach *dms = new DanhMucSach;
				getline(filein, dms->MaSach);
				filein >> dms->TrangThai;
				getline(filein, temp);
				getline(filein, dms->ViTri);
				NODE_DMS *ndms = KhoiTaoNodeDMS(*dms);
				ThemVaoCuoi(p->listDMS, ndms);
				
			}
			
			lds.ListDS[++lds.n] = p;


			
		}
	}
	else cout << "Loi ket noi file! ";
	filein.close();
}

int TimKiemDauSach(LIST_DS lds, string ISBN){
	foru(i, 0, lds.n)
	if (lds.ListDS[i]->data.ISBN == ISBN)
		return i;
	return -1;
}

int XoaDauSach(LIST_DS &lds, int vitri){
	
	if (isEmpty(lds)) return 0;
	if (vitri == lds.n){
		delete lds.ListDS[lds.n];

		// tranh tinh trang con tro bi treo...
		lds.ListDS[lds.n--] = NULL;
		return 1;
	}

	delete lds.ListDS[vitri];

	for (int i = vitri + 1; i <= lds.n; i++) lds.ListDS[i - 1] = lds.ListDS[i];

	// tranh tinh trang con tro bi treo...
	lds.ListDS[lds.n--] = NULL;
	return 1;
}

void HieuChinhDauSach(LIST_DS &lds, DauSach &ds, int w[]){ 
	system("cls");
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "-------Thong tin dau sach dang hieu chinh--------" << endl;
	cout << "ISBN: " << ds.ISBN << endl;
	cout << "Ten Sach: " << ds.TenSach << endl;
	cout << "So Trang: " << ds.SoTrang << endl;
	cout << "Tac Gia: " << ds.TacGia << endl;
	cout << "Nam Xuat Ban: " << ds.NamXuatBan << endl;
	cout << "The Loai: " << ds.TheLoai << endl;

	

	cout << "---------Nhap thong tin can chinh sua--------" << endl;
	NhapThongTin1DauSach(lds,ds, w, 0);
}

int TimViTriDauSachTuMaSach(LIST_DS lds, string maSach){
	string ISBN;
	for (int i = 0; i < maSach.length(); i++){
		if (!(maSach[i] >= 48 && maSach[i] <= 57)){
			ISBN+=(maSach[i]);
		}
		else break;
	}
	return TimKiemDauSach(lds, ISBN);
}

boolean Check_DMS(NODE_DMS* nDMS)
{

	for (NODE_DMS* p = nDMS; p != NULL; p = p->pNext)
	{
		// sach da co nguoi muon.
		if (p->data.TrangThai == 1)
		{
			return true;
		}
	}
	return false;
}

void GiaiPhongBoNho(LIST_DS &lds){
	foru(i, 0, lds.n) delete lds.ListDS[i];
}

void CapNhatDanhSachDauSach(LIST_DS &lds){
	KhoiTaoDauSach(lds);
	DocDuLieuDauSach(lds);
	/// danh sach gom 6 cot ISBN,Ten Sach, So Trang, TacGia, Nam Xuat Ban, The Loai
	int w[7] = { 24, 10, 45, 10, 35, 18, 25 };
	Menu a(35, 80, 1);
	a.Set_Header("QUAN LY DAU SACH");
	a.add("1. In danh sach dau sach theo the loai va tang theo ten sach");
	a.add("2. Them dau sach");
	a.add("3. Sua dau sach");
	a.add("4. Xoa dau sach");
	a.add("5. Tim thong tin dau sach");
	a.add("6. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 6; 

	if (k == 6) return; 
	
	if (k == 1){
		InTieuDeDauSach(w);
		SapXepTheoTheLoaiVaTenSach(lds, w);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(60, 1);
		cout << "----DANH SACH DAU SACH THEO THE LOAI VA TEN SACH---\n";
		SetConsoleTextAttribute(hConsoleColor, 15);
		getch();
	}

	if (k == 2) {
		system("cls");
		int check = ThemDauSach(lds, w);
		if (check == 1){
			LuuDuLieuDauSach(lds);
			DocDuLieuDauSach(lds);
			ConsoleProcess::ThongBao(72, 15, "Them dau sach thanh cong", 1);
		}
		else ConsoleProcess::ThongBao(72, 15, "Them dau sach that bai", 0);
	}
	if (k == 3){
		InTieuDeDauSach(w);
		SapXepTheoTheLoaiVaTenSach(lds, w);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(75, 1);
		cout << "----DANH SACH DAU SACH THEO THE LOAI VA TEN SACH---\n";

		ConsoleProcess::CreateBoxTitle(29, 3, "Nhap ISBN can hieu chinh: ", 70);
		ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 70);

		string ISBN;
		nhapISBNhieuchinh:
		ConsoleProcess::gotoxy(62, 3);
		ConsoleProcess::ShowCur(1);
		getline(cin, ISBN);
		if (checkNhapISBN(ISBN) == 0 || ISBN == ""){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Du lieu khong hop le. Vui long nhap lai.\n";
			goto nhapISBNhieuchinh;
		}

		int vitri = TimKiemDauSach(lds, ISBN);
		if (vitri == -1) {
			ConsoleProcess::gotoxy(42, 6);
			cout << "Dau sach " << ISBN << " khong ton tai!";
			getch();
		}
		else{
			HieuChinhDauSach(lds, lds.ListDS[vitri]->data, w);
			LuuDuLieuDauSach(lds);
			DocDuLieuDauSach(lds);
			ConsoleProcess::ThongBao(72, 15, "Hieu chinh dau sach thanh cong", 1);
		}
		getch();
	}
	if (k == 4){
		InTieuDeDauSach(w);
		SapXepTheoTheLoaiVaTenSach(lds, w);

		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(75, 1);
		cout << "----DANH SACH DAU SACH THEO THE LOAI VA TEN SACH---\n";

		ConsoleProcess::CreateBoxTitle(29, 3, "Nhap ISBN can xoa: ", 50);
		ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 50);

		string ISBNxoa;
		nhapISBNxoa:
		ConsoleProcess::gotoxy(62, 3);
		ConsoleProcess::ShowCur(1);
		getline(cin, ISBNxoa);
		if (checkNhapISBN(ISBNxoa) == 0||ISBNxoa == ""){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Du lieu khong hop le. Vui long nhap lai.\n";
			goto nhapISBNxoa;
		}
		else{
			ConsoleProcess::gotoxy(42, 6);
			cout << "                                            ";
		}



		int vitri3 = TimKiemDauSach(lds, ISBNxoa);
		if (vitri3 == -1) {
			ConsoleProcess::gotoxy(42, 6);
			cout << "Dau sach " << ISBNxoa << " khong ton tai!";
			getch();
		}
		else{
			if (Check_DMS(lds.ListDS[vitri3]->listDMS.pHead)){
				ConsoleProcess::gotoxy(42, 6);
				cout << "Dau sach " << ISBNxoa << " da co doc gia muon. Khong xoa duoc!";
				getch();

			}
			else{
				int check = XoaDauSach(lds, vitri3);
				if (check == 1) {
					LuuDuLieuDauSach(lds);
					DocDuLieuDauSach(lds);
					ConsoleProcess::ThongBao(42, 6, "Xoa dau sach thanh cong", 1);
				}
				else ConsoleProcess::ThongBao(42, 6, "Xoa dau sach that bai. Danh sach Rong", 0);
			}
			
		}
	}
	if (k == 5){
		string tenSach;
		InTieuDeDauSach(w);
		SapXepTheoTheLoaiVaTenSach(lds, w);

		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(75, 1);
		cout << "----DANH SACH DAU SACH THEO THE LOAI VA TEN SACH---\n";

		ConsoleProcess::CreateBoxTitle(29, 3, "Nhap Ten Sach: ", 50);
		ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 50);


		nhapTenSach:
		ConsoleProcess::gotoxy(62, 3);
		ConsoleProcess::ShowCur(1);
		getline(cin, tenSach);
		if (tenSach == ""){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Vui long khong de trong. Nhap lai";
			goto nhapTenSach;
		}
		ChuanHoaChuoi(tenSach);

		InDongDuLieuDauSachTimKiem(lds, w, tenSach);
		getch();
	}
}
//---------------------------END process Dau Sach-----------------------------------------------


//------------------------------Start process Danh Muc Sach----------------------------------------
void InTieuDeDanhMucSach(int w[]){

	system("cls");
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	int sum = 0;
	foru(i, 1, 3) sum = sum + w[i];

	/// dong 1
	foru(i, 1, w[0] + 1) cout << " "; foru(i, 1, sum - 2) cout << "_"; cout << endl;

	/// dong 2
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
	foru(i, 2, 3){
		foru(j, 1, w[i] - 1)cout << " ";
		cout << "\xb3";
	}
	cout << endl;

	/// dong 3
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	ConsoleProcess::InTungPhanTu_XauMau("MA SACH", w[1] - 1, -1);
	ConsoleProcess::InTungPhanTu_XauMau("TRANG THAI", w[2], -1);
	ConsoleProcess::InTungPhanTu_XauMau("VI TRI", w[3], -1);
	cout << endl;

	/// dong 4
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
	foru(i, 2, 3){
		foru(j, 1, w[i] - 1)cout << "_";
		cout << "\xb3";
	}
	cout << endl;
}

void InDongDuLieuDanhMucSach(LIST_DMS l, int w[]){
	/// in cac dong sau
	if (l.pHead == NULL) return;
	for (NODE_DMS *k = l.pHead; k != NULL; k = k->pNext){
		/// in dong trang
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
		foru(i, 2, 3){
			foru(j, 1, w[i] - 1)cout << " ";
			cout << "\xb3";
		}
		cout << endl;

		/// in dong du lieu

		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		ConsoleProcess::InTungPhanTu_Xau(k->data.MaSach, w[1] - 1, -1);


		if (k->data.TrangThai == 0)
			ConsoleProcess::InTungPhanTu_Xau("Cho Muon Duoc", w[2], -1);
		if (k->data.TrangThai == 1)
			ConsoleProcess::InTungPhanTu_Xau("Da Co Doc Gia Muon", w[2], -1);
		if (k->data.TrangThai == 2)
			ConsoleProcess::InTungPhanTu_Xau("Sach Da Thanh Ly", w[2], -1);

		ConsoleProcess::InTungPhanTu_Xau(k->data.ViTri, w[3], -1);
		cout << endl;

		/// in dong _
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
		foru(i, 2, 3){
			foru(j, 1, w[i] - 1)cout << "_";
			cout << "\xb3";
		}
		cout << endl;
	}

}

void InDanhSachDanhMucSach(LIST_DMS l, int w[]){

	InTieuDeDanhMucSach(w);
	InDongDuLieuDanhMucSach(l, w);
}

void KhoiTaoDanhMucSach(LIST_DMS &l){
	l.n = 0;
	l.pHead = NULL;
	l.pTail = NULL;
}

NODE_DMS* KhoiTaoNodeDMS(DanhMucSach dms){
	NODE_DMS *p = new NODE_DMS;//Cap phat vung nho cho con tro
	if (p == NULL) {
		cout << "\nKhong du vung nho de cap phat";
		return NULL;
	}
	p->data = dms;
	p->pNext = NULL;
	return p;
}

NODE_DMS* TimKiemDanhMucSach(LIST_DMS &l, string maSach){
	if (l.pHead == NULL){
		return NULL;
	}
	for (NODE_DMS *k = l.pHead; k != NULL; k = k->pNext){
		if (k->data.MaSach == maSach){
			return k;
		}
	}
	return NULL;
}

void ThemVaoDau(LIST_DMS &l, NODE_DMS *p){

	//Danh sach dang rong
	if (l.pHead == NULL){
		l.pHead = l.pTail = p;
	}
	else{
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

void ThemVaoCuoi(LIST_DMS &l, NODE_DMS *p){

	//Danh sach dang rong
	if (l.pHead == NULL){
		l.pHead = l.pTail = p;
		l.n++;
		return;
	}
	else{
		l.pTail->pNext = p;
		l.pTail = p;
		l.n++;
		return;
	}
	
}

void XoaDau(LIST_DMS &l){

	if (l.pHead == NULL){
		return;
	}
	NODE_DMS *p = l.pHead; //node p là node sẽ xóa
	l.pHead = l.pHead->pNext;//cập nhật lại lpHead
	delete p;
}

void XoaCuoi(LIST_DMS &l){
	
	if (l.pHead == NULL){
		return;
	}
	//danh sach co 1 phan tu
	if (l.pHead->pNext == NULL){
		XoaDau(l);
		return;
	}
	for (NODE_DMS *k = l.pHead; k != NULL; k = k->pNext){
		if (k->pNext == l.pTail){
			delete l.pTail;
			k->pNext = NULL;
			l.pTail = k;
			return;
		}
	}
}

int XoaNodeCoKhoaBatKi(LIST_DMS &l, string maSach){

	if (l.pHead == NULL){
		return -1;
	}

	//Neu node nam dau danh sach
	if (l.pHead->data.MaSach == maSach){
		XoaDau(l);
		return 1;
	}
	//Neu node nam cuoi danh sach
	if (l.pTail->data.MaSach == maSach){
		XoaCuoi(l);
		return 1;
	}
	NODE_DMS *g = new NODE_DMS;
	for (NODE_DMS *k = l.pHead; k != NULL; k = k->pNext){
		//Tim duoc phan tu can xoa
		if (k->data.MaSach == maSach){
			
			g->pNext = k->pNext;//cap nhat moi lien ket
			delete k;
			return 1;
		}
		g = k; //cho node g tro den node k can xoa
	}
	return 0;
}

void NhapDanhMucSach(DanhMucSach &dms, string maSach){
	string trangthai;

	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, 11);


	ConsoleProcess::CreateBoxTitle(60, 3, "          NHAP THONG TIN DANH MUC SACH", 100);
	ConsoleProcess::CreateBoxAdd(60, 5, " Ma Sach: ", 100);
	ConsoleProcess::gotoxy(75, 5);
	cout << maSach;
	ConsoleProcess::CreateBoxAdd(60, 6, " Nhap trang thai(0: Cho muon duoc, 1: Da co doc gia muon, 2:Da thanh ly): ", 100);
	ConsoleProcess::CreateBoxAdd(60, 7, " Nhap Vi Tri Sach: ", 100);
	ConsoleProcess::CreateBoxEnd(60, 8, "", 100);
	ConsoleProcess::CreateBoxTitle(60, 15, "Thong Bao: ", 100);

	nhaptrangthaidms:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(133, 6);
	ConsoleProcess::ShowCur(1);
	getline(cin, trangthai);
	if (checkNhapSo0va1va2(trangthai) == 0 || trangthai==""){
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "Vui long nhap dung dinh dang. Nhap lai";
		goto nhaptrangthaidms;
	}
	else{
		ConsoleProcess::gotoxy(72, 15);
		cout << "                                          ";
	}


	nhapViTri:
	SetConsoleTextAttribute(hConsoleColor, Normal_Color);
	ConsoleProcess::gotoxy(80, 7);
	ConsoleProcess::ShowCur(1);
	getline(cin, dms.ViTri);
	if (dms.ViTri == ""){
		SetConsoleTextAttribute(hConsoleColor, 12);
		ConsoleProcess::gotoxy(72, 15);
		cout << "Vui long nhap dung dinh dang. Nhap lai";
		goto nhapViTri;
	}
	else{
		ConsoleProcess::gotoxy(72, 15);
		cout << "                                          ";
	}

	dms.MaSach = maSach;
	ChuanHoaChuoi(dms.ViTri);
	dms.TrangThai = stoi(trangthai);

}

void HieuChinhDanhMucSach(DanhMucSach &dms, int w[]){
	system("cls");
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "-------Thong tin danh muc sach ban dau--------" << endl;
	cout << "-------Ma Sach: " << dms.MaSach << endl;
	cout << "-------Trang Thai: " << dms.TrangThai << endl;
	cout << "-------Vi Tri: " << dms.ViTri << endl;
	cout << "------------------------------------------------\n";

	cout << "---------Nhap thong tin can chinh sua--------" << endl;
	NhapDanhMucSach(dms, dms.MaSach);
}

string NhapISBN(){
	string ISBN;
nhapISBNthem:
	ConsoleProcess::gotoxy(62, 3);
	ConsoleProcess::ShowCur(1);
	getline(cin, ISBN);
	if (checkNhapISBN(ISBN) == 0 || ISBN==""){
		ConsoleProcess::gotoxy(42, 6);
		cout << "Du lieu khong hop le. Vui long nhap lai.\n";
		goto nhapISBNthem;
	}
	return ISBN;
}

void GiaiPhongDanhSachLKD(LIST_DMS &l){
	NODE_DMS *k;
	while (l.pHead != NULL){
		k = l.pHead;
		l.pHead = l.pHead->pNext;
		delete k;
	}
}

int CapNhatDanhSachDanhMucSach(LIST_DS &lds, LIST_DMS &ldms, pNODEDAUSACH &p){

	/// danh sach gom 6 cot ISBN,Ten Sach, So Trang, TacGia, Nam Xuat Ban, The Loai
	int w[4] = { 27, 20, 35, 20 };
	Menu a(35, 60, 1);
	a.Set_Header("MENU LUA CHON");
	a.add("1. In danh sach danh muc sach");
	a.add("2. Them danh muc sach");
	a.add("3. Sua danh muc sach");
	a.add("4. Xoa danh muc sach");
	a.add("5. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 5;
	if (k == 5) return 5;
	if (k == 1){
		InDanhSachDanhMucSach(ldms, w);
		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(50, 1);
		cout << "----DANH SACH DANH MUC SACH---\n";
		SetConsoleTextAttribute(hConsoleColor, 15);
		getch();
	}
	if (k == 2){
		DanhMucSach *dms = new DanhMucSach;
		int stt = ldms.n;
		string maSach = p->data.ISBN + to_string(++stt);
		while (TimKiemDanhMucSach(ldms, maSach) != NULL)
		{
			stt++;
			maSach = p->data.ISBN + to_string(stt);
		}

		system("cls");
		NhapDanhMucSach(*dms, maSach);
		NODE_DMS *ndms = new NODE_DMS;
		ndms = KhoiTaoNodeDMS(*dms);
		ThemVaoCuoi(ldms, ndms);
		LuuDuLieuDauSach(lds);
		DocDuLieuDauSach(lds);
		ConsoleProcess::ThongBao(72, 15, "Them danh muc sach thanh cong", 1);
		//return 5;
	}

	if (k == 3) {
		InDanhSachDanhMucSach(ldms, w);

		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(60, 1);
		cout << "----DANH SACH DANH MUC SACH---\n";

		ConsoleProcess::CreateBoxTitle(29, 3, "Nhap ma sach can hieu chinh: ", 70);
		ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 70);

		string maSach;
		nhapmasachhc:
		ConsoleProcess::gotoxy(62, 3);
		ConsoleProcess::ShowCur(1);
		getline(cin, maSach);
		if (checkNhapMaSach(maSach) == 0||maSach==""){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
			goto nhapmasachhc;
		}
		NODE_DMS *pp = TimKiemDanhMucSach(ldms, maSach);
		if (pp == NULL) { 
			ConsoleProcess::gotoxy(42, 6);
			cout << "Ma Sach " << maSach << " khong ton tai!";
			getch();
		}
		else if (pp->data.TrangThai == 1){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Sach da co doc gia muon. Khong the hieu chinh!";
			getch();
		}
		else{
			HieuChinhDanhMucSach(pp->data, w);
			LuuDuLieuDauSach(lds);
			DocDuLieuDauSach(lds);
			ConsoleProcess::ThongBao(72, 15, "Hieu chinh dau sach thanh cong", 1);
			//return 5;
		}
	}
	if (k == 4){
		InDanhSachDanhMucSach(ldms, w);

		HANDLE hConsoleColor;
		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleColor, 6);
		ConsoleProcess::gotoxy(60, 1);
		cout << "----DANH SACH DANH MUC SACH---\n";

		ConsoleProcess::CreateBoxTitle(29, 3, "Nhap ma sach can xoa: ", 70);
		ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 70);

		string maSach;
		nhapmasachxoa:
		ConsoleProcess::gotoxy(62, 3);
		ConsoleProcess::ShowCur(1);
		getline(cin, maSach);
		if (checkNhapMaSach(maSach) == 0 || maSach==""){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
			goto nhapmasachxoa;
		}
		NODE_DMS *pp = TimKiemDanhMucSach(ldms, maSach);
		
		 if (pp == NULL){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Ma sach " << maSach << " khong ton tai!";
			getch();
		}
		 else if(pp->data.TrangThai == 1){
			ConsoleProcess::gotoxy(42, 6);
			cout << "Sach da co doc gia muon. Khong duoc xoa.";
			getch();

		}
		else{
			int check = XoaNodeCoKhoaBatKi(ldms, maSach);
			if (check == -1) ConsoleProcess::ThongBao(42, 6, "Danh Sach Rong", 0);
			else if (check == 1){
				ldms.n--;
				LuuDuLieuDauSach(lds);
				DocDuLieuDauSach(lds);
				ConsoleProcess::ThongBao(42, 6, "Xoa sach thanh cong", 1);
				//return 5;
			}

		}
	}
}

void LayViTriNodeDuocChon(LIST_DS &lds){
	int w[7] = { 20, 10, 45, 10, 35, 18, 25 };
	InTieuDeDauSach(w);
	SapXepTheoTheLoaiVaTenSach(lds, w);

	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, 6);
	ConsoleProcess::gotoxy(75, 1);
	cout << "----DANH SACH DAU SACH THEO THE LOAI VA TEN SACH---\n";

	ConsoleProcess::CreateBoxTitle(29, 3, "Nhap ISBN can quan ly: ", 50);
	ConsoleProcess::CreateBoxTitle(29, 6, "Thong Bao: ", 50);

	string ISBN = NhapISBN();
	int vitri = TimKiemDauSach(lds, ISBN);
	if (vitri == -1) {
		ConsoleProcess::gotoxy(42, 6);
		cout << "Dau sach " << ISBN << " khong ton tai!";
		getch();
	}

	/*else{
		NODEDAUSACH *p = lds.ListDS[vitri];
		if (p->listDMS.n == 0) KhoiTaoDanhMucSach(p->listDMS);
		int check;
		while (true){
			check = CapNhatDanhSachDanhMucSach(lds, p->listDMS, p);
			if (check == 5) {
				GiaiPhongDanhSachLKD(p->listDMS); 
				break;
			}
		}
	}*/
	else{
		//NODEDAUSACH *p = lds.ListDS[vitri];
		if (lds.ListDS[vitri]->listDMS.n == 0) KhoiTaoDanhMucSach(lds.ListDS[vitri]->listDMS);
		int check;
		while (true){
			check = CapNhatDanhSachDanhMucSach(lds,lds.ListDS[vitri]->listDMS,lds.ListDS[vitri]);
			if (check == 5) {
				//GiaiPhongDanhSachLKD(lds.ListDS[vitri]->listDMS);
				break;
			}
		}
	}
	return;
}

//-------------------------------END process Danh Muc Sach---------------------------------------

//-------------------------------IN DANH SACH QUA HAN---------------------------------------

void InTieuDeQuaHan(int w[]){
	system("cls");
	cout << endl;
	cout << endl;

	int sum = 0;
	foru(i, 1, 6) sum = sum + w[i];

	/// dong 1
	foru(i, 1, w[0] + 1) cout << " "; foru(i, 1, sum - 2) cout << "_"; cout << endl;

	/// dong 2
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
	foru(i, 2, 6){
		foru(j, 1, w[i] - 1)cout << " ";
		cout << "\xb3";
	}
	cout << endl;

	/// dong 3
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	ConsoleProcess::InTungPhanTu_XauMau("MA THE", w[1] - 1, -1);
	ConsoleProcess::InTungPhanTu_XauMau("HO TEN", w[2], -1);
	ConsoleProcess::InTungPhanTu_XauMau("MA SACH", w[3], -1);
	ConsoleProcess::InTungPhanTu_XauMau("TEN SACH", w[4], -1);
	ConsoleProcess::InTungPhanTu_XauMau("NGAY MUON", w[5], -1);
	ConsoleProcess::InTungPhanTu_XauMau("SO NGAY QUA HAN", w[6], -1);
	cout << endl;

	/// dong 4
	foru(i, 1, w[0]) cout << " "; cout << "\xb3";
	foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
	foru(i, 2, 6){
		foru(j, 1, w[i] - 1)cout << "_";
		cout << "\xb3";
	}
	cout << endl;
}

void AddListQuaHan2(TREE t, NODEQUAHANR *arr, int w[], Date d2){
	NODE_MUONTRA* pp = new NODE_MUONTRA;
	for (NODE_MUONTRA *p = t->listMuonTra.pHead; p != NULL; p = p->pNext){
		if (p->data.TrangThai == 0 && TinhKhoangCachNgay(p->data.NgayMuon, d2) >= 7){
			arr[index].MATHE = t->data.MATHE;
			arr[index].SoNgayQuaHan = TinhKhoangCachNgay(p->data.NgayMuon, d2);
			++index;
		}
	}
}

void QuickSortQuaHan2(NODEQUAHANR *arr, int q, int r){
	NODEQUAHANR temp;
	int i = q;
	int j = r;
	//Lấy phần tử giữa của dãy cần sắp thứ tự làm chốt
	int x = arr[(q + r) / 2].SoNgayQuaHan;
	do
	{  // Phân đoạn dãy con a[q],..., a[r]
		while (arr[i].SoNgayQuaHan > x)
			i++; //Tìm phần tử đầu tiên có trị nhỏ hơn hay bằng x
		while (arr[j].SoNgayQuaHan < x)
			j--;   //Tìm phần tử đầu tiên có trị lớn hơn hay bằng x

		if (i <= j)   // Hoan vi
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	if (q<j) 	// phần thứ nhất có từ 2 phần tử trở lên
		QuickSortQuaHan2(arr, q, j);
	if (i < r)   	// phần thứ ba có từ 2 phần tử trở lên
		QuickSortQuaHan2(arr, i, r);
}

void InDongDuLieuQuaHan2(TREE t, LIST_DS lds, NODEQUAHANR *arr, int w[], Date d2){
	
	for (int it = 0; it < index; it++){
		string ngaymuon;
		string hoten;
		string masach;
		string ms;
		int vitri5;
		string vitrisach;
		string ngayquahan;
		/// in dong trang
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
		foru(i, 2, 6){
			foru(j, 1, w[i] - 1)cout << " ";
			cout << "\xb3";
		}

		cout << endl;

		/// in dong du lieu

		foru(i, 1, w[0]) cout << " "; cout << "\xb3";

		ConsoleProcess::InTungPhanTu_Xau(ConsoleProcess::convert(arr[it].MATHE), w[1] - 1, -1);

		NODETHEDOCGIA* p = TimKiemDocGia(t, arr[it].MATHE);
		hoten.append(p->data.Ho);
		hoten.append(" ");
		hoten.append(p->data.Ten);

		for (NODE_MUONTRA *pp = p->listMuonTra.pHead; pp != NULL; pp = pp->pNext){
			if (pp->data.TrangThai == 0 && TinhKhoangCachNgay(pp->data.NgayMuon, d2) == arr[it].SoNgayQuaHan){

				masach.append(pp->data.MaSach);
				//masach.append(" ");
				ms = pp->data.MaSach;

				if (pp->data.NgayMuon.Ngay < 10) {
					ngaymuon.append("0");
					ngaymuon.append(ConsoleProcess::convert(pp->data.NgayMuon.Ngay));
					ngaymuon.append("/");
				}
				else {
					ngaymuon.append(ConsoleProcess::convert(pp->data.NgayMuon.Ngay));
					ngaymuon.append("/");
				}
				if (pp->data.NgayMuon.Thang < 10) {
					ngaymuon.append("0");
					ngaymuon.append(ConsoleProcess::convert(pp->data.NgayMuon.Thang));
					ngaymuon.append("/");
				}
				else {
					ngaymuon.append(ConsoleProcess::convert(pp->data.NgayMuon.Thang));
					ngaymuon.append("/");
				}
				ngaymuon.append(ConsoleProcess::convert(pp->data.NgayMuon.Nam));
				//ngaymuon.append(" ");
				break;

			}
		}

		//vitri5 = TimViTriDauSachTuMaSach(lds,ms);
		
		ConsoleProcess::InTungPhanTu_Xau(hoten, w[2], -1);
		ConsoleProcess::InTungPhanTu_Xau(masach, w[3], -1);
		ConsoleProcess::InTungPhanTu_Xau(TimTenSach(ms, lds, vitrisach), w[4], -1);
		ConsoleProcess::InTungPhanTu_Xau(ngaymuon, w[5], -1);
		ConsoleProcess::InTungPhanTu_Xau(ConsoleProcess::convert(arr[it].SoNgayQuaHan), w[6], -1);
		cout << endl;
		/// in dong _
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
		foru(i, 2, 6){
			foru(j, 1, w[i] - 1)cout << "_";
			cout << "\xb3";
		}
		cout << endl;
	}
}

void InDanhSachQuaHan2(TREE t, NODEQUAHANR *arr, int w[], Date d2){
	if (t != NULL){
		InDanhSachQuaHan2(t->pLeft, arr, w, d2);
		//InDongDuLieuQuaHan(t, lds, w, vitri, ngaymuon, hoten, mathe, d2);
		AddListQuaHan2(t, arr, w, d2);
		InDanhSachQuaHan2(t->pRight, arr, w, d2);
	}
}
//-----------------------------------------END DANH SACH QUA HAN-------------------------------------

//----------------------------------------LIET KE 10 DAU SACH CO LUOT MUON NHIU NHAT----------------

void InTieuDeLietKeDS(int w[]){
	

		system("cls");
		cout << endl;
		cout << endl;

		int sum = 0;
		foru(i, 1, 3) sum = sum + w[i];

		/// dong 1
		foru(i, 1, w[0] + 1) cout << " "; foru(i, 1, sum - 2) cout << "_"; cout << endl;

		/// dong 2
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
		foru(i, 2, 3){
			foru(j, 1, w[i] - 1)cout << " ";
			cout << "\xb3";
		}
		cout << endl;

		/// dong 3
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		ConsoleProcess::InTungPhanTu_XauMau("ISBN", w[1] - 1, -1);
		ConsoleProcess::InTungPhanTu_XauMau("TEN SACH", w[2], -1);
		ConsoleProcess::InTungPhanTu_XauMau("SO LUOT MUON", w[3], -1);
		
		cout << endl;

		/// dong 4
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
		foru(i, 2, 3){
			foru(j, 1, w[i] - 1)cout << "_";
			cout << "\xb3";
		}
		cout << endl;
}

void InDongDuLieuLietKeDS(LIST_DS lds, int w[], int max){

		/// in dong trang
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << " "; cout << "\xb3";
		foru(i, 2, 3){
			foru(j, 1, w[i] - 1)cout << " ";
			cout << "\xb3";
		}
		cout << endl;

		/// in dong du lieu

		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		ConsoleProcess::InTungPhanTu_Xau(lds.ListDS[max]->data.ISBN, w[1] - 1, -1);
		ConsoleProcess::InTungPhanTu_Xau(lds.ListDS[max]->data.TenSach, w[2], -1);
		ConsoleProcess::InTungPhanTu_Xau(ConsoleProcess::convert(lds.ListDS[max]->data.soluotmuon), w[3], -1);
		cout << endl;

		/// in dong _
		foru(i, 1, w[0]) cout << " "; cout << "\xb3";
		foru(i, 1, w[1] - 2) cout << "_"; cout << "\xb3";
		foru(i, 2, 3){
			foru(j, 1, w[i] - 1)cout << "_";
			cout << "\xb3";
		}
		cout << endl;
}

void SelectionSortVaIn10DauSach2(LIST_DS lds){
	int i, j, max_idx;
	int w[4] = { 20, 20, 20, 20 };
	system("cls");
	InTieuDeLietKeDS(w);
	// One by one move boundary of unsorted subarray  
	for (i = 0; i < lds.n; i++)
	{
		// Find the maximum element in unsorted array  
		max_idx = i;
		for (j = i + 1; j < lds.n +1; j++)
		if (lds.ListDS[j]->data.soluotmuon > lds.ListDS[max_idx]->data.soluotmuon)
			max_idx = j;

		// Swap the found maximum element with the first element  
		Swap(lds.ListDS[max_idx], lds.ListDS[i]);
		if (i == 10) break;
		InDongDuLieuLietKeDS(lds, w, i);
	}
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, 6);
	ConsoleProcess::gotoxy(32, 1);
	cout << "-------DAU SACH CO LUOT MUON NHIEU NHAT------\n";
	SetConsoleTextAttribute(hConsoleColor, 15);
}

//----------------------------------------END LIET KE---------------------------------------------
int LuaChon2(){
	Menu a(35, 80, 1);
	a.Set_Header("QUAN LY DAU SACH");
	a.add("1. Quan ly Dau Sach");
	a.add("2. Quan Ly Danh Muc Sach");
	a.add("3. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 3;
	return k;
}

int main2(LIST_DS &lds){
	
	ConsoleProcess::ShowCur(0);
	while (true){
		int k = LuaChon2();
		switch (k){
		case 1: CapNhatDanhSachDauSach(lds); break;///OK
		case 2:	LayViTriNodeDuocChon(lds); break;///OK
		case 3:  return 0; break;
		}
	}
	return 0;
}

int LuaChon(){
	Menu a(35, 80, 1);
	a.Set_Header("MENU LUA CHON");
	a.add("1. Quan ly The Doc Gia");
	a.add("2. Quan Ly Dau Sach");
	a.add("3. Quan ly Muon Tra Sach");
	a.add("4. Danh Sach Doc Gia Muon Sach Qua Han");
	a.add("5. Liet Ke 10 Dau Sach Muon Nhieu Nhat");
	a.add("6. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 6;
	return k;
}

int main()
{
	TREE t;
	LIST_DS lds;
	KhoiTaoDauSach(lds);
	DocDuLieuDauSach(lds);
	KhoiTaoCay(t);
	DocDuLieuDocGia(t);
	ConsoleProcess::ShowCur(0);
	while (true){
		int k = LuaChon();
		switch (k){
		case 1: CapNhatDanhSachCacDocGia(t); break;///OK
		case 2:	main2(lds); break;///OK
		case 3: LayViTriNodeDuocChonMuonTra(t,lds); break;
		case 4: {
				int w[7] = { 5, 10, 30, 30, 30, 40, 20 };
				string vitri;
				string ngaymuon;
				string hoten;
				string mathe;
				int sodocgia = DemSoDocGia(t);
				NODEQUAHANR *arr = new NODEQUAHANR[sodocgia*3];
				Date d2;
				d2.Ngay = LayNgayHienTai();
				d2.Thang = LayThangHienTai();
				d2.Nam = LayNamHienTai();
				HANDLE hConsoleColor;
				hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

				InTieuDeQuaHan(w);
				AddListQuaHan2(t, arr, w, d2);
				InDanhSachQuaHan2(t, arr, w, d2);
				QuickSortQuaHan2(arr, 0, index);
				InDongDuLieuQuaHan2(t, lds,arr,w, d2);

				SetConsoleTextAttribute(hConsoleColor, 6);
				ConsoleProcess::gotoxy(60, 1);
				cout << "----DANH SACH DOC GIA MUON SACH QUA HAN---\n";
				SetConsoleTextAttribute(hConsoleColor, 15);
				index = 0;
				getch();
				delete[] arr;
				break;
		}
		case 5:  SelectionSortVaIn10DauSach2(lds);
				getch(); 
				break;
		case 6:  return 0; break;
		}
	}
	GiaiPhongBoNho(lds);
	Free(t);
	system("pause");
	return 0;
}