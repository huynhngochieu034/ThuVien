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
	
};


struct NodeDauSach{
	DauSach data;
	LIST_DMS listDMS;/// chua danh sach cac danh muc sach cua danh muc sach do
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
int nDocGia=0;
int vitri=0;
void KhoiTaoDanhMucSach(LIST_DMS &l);
NODE_DMS* KhoiTaoNodeDMS(DanhMucSach dms);
void ThemVaoCuoi(LIST_DMS &l, NODE_DMS *p);
void Init(LIST_MUONTRA &l);
void AddTailMT(LIST_MUONTRA &l, NODE_MUONTRA *p);
string NhapISBN();
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
			cout << "Loi nhap so chu";
			return 0;
		}
	}
	else if (str.length() > 6){
		cout << "Loi lon hon";
		return 0;
	}

	return 1;
}

int checkNhapMaSach(string str){
	//check nhap chu khong dau space
	foru(i, 0, str.length())
	if (!(((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) || (str[i] >= 48 && str[i] <= 57))){
		if (str[i] != '\0'){
			cout << "Loi nhap so chu";
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

//-----------------END chuan hoa chuoi-------------------------


//--------------Start process cây tìm kiếm nhị phân Doc Gia-----------------

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
	getline(cin, phai);
	if (checkNhapSo0va1(phai) == 0){
		cout << "Vui long nhap dung du lieu.Nhap lai\n";
		goto nhapphai;
	}

	nhaptrangthai:
	cout << "Nhap trang thai(0: Khoa, 1: Hoat Dong): ";
	getline(cin, trangthai);
	if (checkNhapSo0va1(trangthai) == 0){
		cout << "Vui long nhap dung du lieu.Nhap lai\n";
		goto nhaptrangthai;
	}
	ChuanHoaChuoiInHoa(ho);
	ChuanHoaChuoiInHoa(ten);
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
	int soDocGia;
	int soSach;
	filein.open(databasedocgia, ios::in);

	if (filein.is_open()){
		string temp;
		filein >> soDocGia;
		for (int i = 0; i < soDocGia; i++)
		{
			NODETHEDOCGIA *p = new NODETHEDOCGIA;
			TheDocGia *tdg = new TheDocGia;
			filein >> tdg->MATHE;
			getline(filein, temp);
			getline(filein, tdg->Ho);
			getline(filein, tdg->Ten);
			filein >> tdg->Phai;
			filein >> tdg->TrangThai;
			ThemNodeVaoCay(t, *tdg);
			p = TimKiemDocGia(t, tdg->MATHE);

			filein >> soSach;
			getline(filein, temp);
			Init(p->listMuonTra);
			for (int j = 0; j < soSach; j++)
			{
				NODE_MUONTRA *nmt = new NODE_MUONTRA;
				MuonTra *mt = new MuonTra;
				getline(filein, mt->MaSach);
				filein >> mt->NgayMuon.Ngay;
				filein >> mt->NgayMuon.Thang;
				filein >> mt->NgayMuon.Nam;
				filein >> mt->NgayTra.Ngay;
				filein >> mt->NgayTra.Thang;
				filein >> mt->NgayTra.Nam;
				filein >> mt->TrangThai;
				nmt->data = *mt;

				// cap nhat du lieu vao
				AddTailMT(p->listMuonTra, nmt);
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
	if (_err) { 
		Free(t);
		k = 6;
	}
		
	if (k == 6)
	{
		Free(t);
		return;
	}
	if (k == 1){
		
		InTieuDe(w);
		InDanhSachDocGia(t,w);
		getch();
	}
	if (k == 2){
		TREE temp = NULL;
		InDanhSachDocGiaTheoTenHo(t, temp);
		InTieuDe(w);
		InDanhSachDocGia(temp, w);
		Free(temp);
		getch();
	}

	if (k == 3) {
		system("cls");
		unsigned int mathe = Random();
		TheDocGia *p = new TheDocGia;
		NhapDocGia(*p, w, mathe);
		int check = ThemNodeVaoCay(t, *p);
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
		string maDocGia;
		nhapmadocgiahieuchinh:
		cout << "Nhap ma doc gia can hieu chinh: ";
		getline(cin, maDocGia);
		if (checkNhapSo(maDocGia) == 0){
			cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
			goto nhapmadocgiahieuchinh;
		}
		NODETHEDOCGIA *p = TimKiemDocGia(t, stoi(maDocGia));
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
		string madocgia;
		nhapmadocgiaxoa:
		cout << "Nhap ma doc gia can xoa: ";
		getline(cin, madocgia);
		if (checkNhapSo(madocgia) == 0){
			cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
			goto nhapmadocgiaxoa;
		}
		int check = XoaDocGia(t, stoi(madocgia));
		if (check == 1){
			LuuDuLieuDocGia(t);
			DocDuLieuDocGia(t);
			ConsoleProcess::ThongBao(20, 2, "Xoa doc gia thanh cong", 1);
		}	
		else ConsoleProcess::ThongBao(20, 2, "Xoa doc gia that bai", 0);

		getch();
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

void AddTailMT(LIST_MUONTRA &l, NODE_MUONTRA *p){
	
	NODE_MUONTRA *mt = KhoiTaoNodeMT(p->data);
	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
		++l.n;
		return;
	}
	else
	{
		l.pTail->pNext = p;
		p->pPrev = l.pTail;
		l.pTail = p;
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
	int i;
	int dem = 0;
	NODE_DMS *dms;
	for (i = 0; i < lds.n; i++){
		dms = TimKiemDanhMucSach(lds.ListDS[i]->listDMS, maSach);
		if (dms != NULL){
			dem = i;
			vitri = dms->data.ViTri;
		}
			
	}
	
	return lds.ListDS[dem]->data.TenSach;
}

void MuonSach(LIST_MUONTRA &l, NODETHEDOCGIA* &dg, LIST_DS lds){
	int w[7] = { 20, 10, 45, 10, 35, 18, 25 };
	if (dg->data.TrangThai == 0) {
		ConsoleProcess::ThongBao(20, 2, "The Doc Gia Nay Da Bi Khoa. Khong duoc muon sach", 0);
		getch();
		return;
	}
	cout << endl;
	cout << "----------------THONG TIN DOC GIA-----------------\n";
	cout << "--------------------------------------------------\n";
	cout << "Ma Doc Gia: " << dg->data.MATHE << endl;
	cout << "--------------------------------------------------\n";
	cout << "Ho: " << dg->data.Ho << endl;
	cout << "--------------------------------------------------\n";
	cout << "Ten: " << dg->data.Ten << endl;
	cout << "--------------------------------------------------\n";
	cout << "Trang thai the: ";
	if (dg->data.TrangThai == 1)
		cout << "Dang hoat dong" << endl;
	cout << "--------------------------------------------------\n";
	cout << "--------------------------------------------------\n";
	cout << "---------------------Cac Sach Dang muon--------------------\n";
	string vitri;
	for (NODE_MUONTRA* p = dg->listMuonTra.pHead; p != NULL; p = p->pNext)
	{
		cout <<"Ma Sach: " << p->data.MaSach << endl;
		
		cout << "Ten Sach: " << TimTenSach(p->data.MaSach, lds, vitri) << endl;
		cout << "Ngay Muon: ";
		if (p->data.NgayMuon.Ngay < 10) cout<<"0"<<p->data.NgayMuon.Ngay <<"/";
		else cout << p->data.NgayMuon.Ngay << "/";
		if (p->data.NgayMuon.Thang < 10) cout << "0" << p->data.NgayMuon.Thang << "/";
		else cout << p->data.NgayMuon.Thang << "/";
		cout << p->data.NgayMuon.Nam << endl;

		cout << "Vi tri: "<< vitri << endl;
		cout << "--------------------------------------------------\n";
	}
	if (dg->listMuonTra.pHead == NULL && dg->listMuonTra.n <3){
		InDanhSachDauSach(lds, w);
		string ISBN = NhapISBN();
		int vitri = TimKiemDauSach(lds, ISBN);
		if (vitri == -1) ConsoleProcess::ThongBao(20, 2, "Khong tim thay dau sach vua nhap.", 0);
		else{
			InDanhSachDanhMucSach(lds.ListDS[vitri]->listDMS, w);
			string maSach;
			nhapmasachmuon:
			cout << "Nhap ma sach can muon: ";
			getline(cin, maSach);
			if (checkNhapMaSach(maSach) == 0){
				cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
				goto nhapmasachmuon;
			}
			NODE_DMS *pp = TimKiemDanhMucSach(lds.ListDS[vitri]->listDMS, maSach);
			if (pp == NULL) ConsoleProcess::ThongBao(20, 1, "Khong tim thay dau sach vua nhap.", 0);
			else{
				NODE_MUONTRA *nmt = new NODE_MUONTRA;
				MuonTra *mt = new MuonTra;
				mt->MaSach = maSach;
				mt->NgayMuon.Ngay;
				mt->NgayMuon.Thang;
				mt->NgayMuon.Nam;
				mt->NgayTra.Ngay=0;
				mt->NgayTra.Thang=0;
				mt->NgayTra.Nam=0;
				mt->TrangThai=0;
				nmt->data = *mt;
				AddTailMT(l, nmt);
				ConsoleProcess::ThongBao(20, 1, "Muon sach thanh cong", 1);
			}
		}
	}

}

int CapNhatMuonTra(TREE &t, LIST_MUONTRA &l, NODETHEDOCGIA* &dg, LIST_DS lds){
	
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
		
	}
	if (k == 2){
		
	}
	if (k == 3) {
		
	}
}

void LayViTriNodeDuocChonMuonTra(TREE &t,LIST_DS lds){
	int w[6] = { 20, 10, 30, 20, 35, 45 };
	InTieuDe(w);
	InDanhSachDocGia(t, w);
	string maDocGia;
	nhapmadocgiaduocchon:
	cout << "Nhap ma doc gia can cap nhat: ";
	getline(cin, maDocGia);
	if (checkNhapSo(maDocGia) == 0){
		cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
		goto nhapmadocgiaduocchon;
	}
	NODETHEDOCGIA *p = TimKiemDocGia(t, stoi(maDocGia));
	if (p == NULL) {
		ConsoleProcess::ThongBao(20, 2, "Ma doc gia vua nhap khong ton tai", 0);
		getch();
	}
	else{
		if (p->listMuonTra.n == 0) Init(p->listMuonTra);
		int check;
		while (true){
			check = CapNhatMuonTra(t, p->listMuonTra, p);
			if (check == 4) {
				GiaiPhongDanhSachLKK(p->listMuonTra);
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

void InTieuDeDauSach(int w[]){

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
	foru(it, 0, lds.n){
		if (lds.ListDS[it]->data.TenSach == TenSach){
			cout << endl;
			cout << "-----------THONG TIN SACH DA TIM KIEM-------------\n";
			cout << "--------------------------------------------------\n";
			cout << "ISBN: " << lds.ListDS[it]->data.ISBN << endl;
			cout << "--------------------------------------------------\n";
			cout << "Ten Sach: " << lds.ListDS[it]->data.TenSach << endl;
			cout << "--------------------------------------------------\n";
			cout << "So Trang: " << lds.ListDS[it]->data.SoTrang << endl;
			cout << "--------------------------------------------------\n";
			cout << "Tac Gia: " << lds.ListDS[it]->data.TacGia << endl;
			cout << "--------------------------------------------------\n";
			cout << "Nam Xuat Ban: " << lds.ListDS[it]->data.NamXuatBan << endl;
			cout << "--------------------------------------------------\n";
			cout << "The Loai: " << lds.ListDS[it]->data.TheLoai << endl;
			cout << "--------------------------------------------------\n";
			cout << "---------------------Cac Ma Sach--------------------\n";
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
	for (int i = 0; i < lds.n - 1; i++){
		for (j = 0; j < lds.n - i - 1; j++){
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

	if (isISBN == 1){
	nhapISBN:
		cout << "Nhap ISBN(gom 6 ki tu chu va so): ";
		getline(cin, ds.ISBN);
		if (checkNhapISBN(ds.ISBN) == 0){
			cout << "Vui long nhap dung dinh dang.Nhap lai\n";
			goto nhapISBN;
		}
		else if (KiemTraTonTaiISBN(lds, ds.ISBN) == 1){
			cout << "ISBN da ton tai trong he thong.Nhap lai\n";
			goto nhapISBN;
		}
	}
	
	cout << "Nhap Ten Sach: ";
	getline(cin, ds.TenSach);

	nhapsotrang:
	cout << "Nhap So Trang( < 1.000.000 ): ";
	getline(cin, sotrang);
	if (checkNhapSo(sotrang) == 0){
		cout << "Vui long nhap dung dinh dang.Nhap lai\n";
		goto nhapsotrang;
	}
	else{
		if (stoi(sotrang) > 1000000){
			cout << "Vui long nhap dung dinh dang.Nhap lai\n";
			goto nhapsotrang;
		}
	}

	nhaptacgia:
	cout << "Nhap Tac Gia: ";
	getline(cin, ds.TacGia);
	if (checkNhapChu(ds.TacGia) == 0){
		cout << "Vui long nhap dung dinh dang.Nhap lai\n";
		goto nhaptacgia;
	}

	namxuatban:
	cout << "Nhap Nam Xuat Ban( < hon nam hien tai): ";
	getline(cin, namxuatban);
	if (checkNhapSo(namxuatban) == 0){
		cout << "Vui long nhap dung dinh dang.Nhap lai\n";
		goto namxuatban;
	}
	else{
		cout << "Nam hien tai la: " << LayNamHienTai() << endl;
		int nam = stoi(namxuatban);
		if (nam > LayNamHienTai()){
			cout << "Vui long nhap dung dinh dang.Nhap lai\n";
			goto namxuatban;
		}
	}

	nhaptheloai:
	cout << "Nhap The Loai: ";
	getline(cin, ds.TheLoai);
	if (checkNhapChu(ds.TheLoai) == 0){
		cout << "Vui long nhap dung dinh dang.Nhap lai\n";
		goto nhaptheloai;
	}

	ChuanHoaChuoi(ds.TenSach);
	ChuanHoaChuoiInHoa(ds.TacGia);
	ChuanHoaChuoi(ds.TheLoai);
	
	ds.SoTrang = stoi(sotrang);
	ds.NamXuatBan = stoi(namxuatban);
	cout << ds.ISBN << endl;
	cout << ds.TenSach << endl;
	cout << ds.SoTrang << endl;
	cout << ds.TacGia << endl;
	cout << ds.NamXuatBan << endl;
	cout << ds.TheLoai << endl;
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

void GiaiPhongBoNho(LIST_DS &lds){
	foru(i, 0, lds.n) delete lds.ListDS[i];
}

void CapNhatDanhSachDauSach(LIST_DS &lds){
	KhoiTaoDauSach(lds);
	DocDuLieuDauSach(lds);
	/// danh sach gom 6 cot ISBN,Ten Sach, So Trang, TacGia, Nam Xuat Ban, The Loai
	int w[7] = { 20, 10, 45, 10, 35, 18, 25 };
	Menu a(35, 80, 1);
	a.Set_Header("MENU LUA CHON");
	a.add("1. In danh sach dau sach");
	a.add("2. In danh sach dau sach theo the loai va tang theo ten sach");
	a.add("3. Them dau sach");
	a.add("4. Sua dau sach");
	a.add("5. Xoa dau sach");
	a.add("6. Tim thong tin dau sach");
	a.add("7. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) { 
		GiaiPhongBoNho(lds);
		k = 7; 
	}

	if (k == 7) {
		GiaiPhongBoNho(lds);
		return; 
	}
	if (k == 1){
		InDanhSachDauSach(lds, w);
		getch();
	}
	if (k == 2){
		InTieuDeDauSach(w);
		SapXepTheoTheLoaiVaTenSach(lds, w);
		getch();
	}

	if (k == 3) {
		system("cls");
		int check = ThemDauSach(lds, w);
		if (check == 1){
			LuuDuLieuDauSach(lds);
			DocDuLieuDauSach(lds);
			ConsoleProcess::ThongBao(20, 2, "Them dau sach thanh cong", 1);
		}
		else ConsoleProcess::ThongBao(20, 2, "Them dau sach that bai", 0);
		getch();
	}
	if (k == 4){
		InTieuDeDauSach(w);
		InDanhSachDauSach(lds, w);
		string ISBN;
		nhapISBNhieuchinh:
		cout << "Nhap ISBN (gom 6 ki tu) can hieu chinh: ";
		getline(cin, ISBN);
		if (checkNhapISBN(ISBN) == 0){
			cout << "Vui long nhap dung dinh dang.Nhap lai\n";
			goto nhapISBNhieuchinh;
		}

		int vitri = TimKiemDauSach(lds, ISBN);
		if (vitri == -1) ConsoleProcess::ThongBao(20, 2, "Khong tim thay dau sach vua nhap.", 0);
		else{
			HieuChinhDauSach(lds, lds.ListDS[vitri]->data, w);
			LuuDuLieuDauSach(lds);
			DocDuLieuDauSach(lds);
			ConsoleProcess::ThongBao(20, 2, "Hieu chinh dau sach thanh cong", 1);
		}
		getch();
	}
	if (k == 5){
		InTieuDeDauSach(w);
		InDanhSachDauSach(lds, w);
		string ISBNxoa;
		nhapISBNxoa:
		cout << "Nhap ISBN (gom 6 ki tu) can xoa: ";
		getline(cin, ISBNxoa);
		if (checkNhapISBN(ISBNxoa) == 0){
			cout << "Vui long nhap dung dinh dang.Nhap lai\n";
			goto nhapISBNxoa;
		}
		int vitri = TimKiemDauSach(lds, ISBNxoa);
		if (vitri == -1) ConsoleProcess::ThongBao(20, 2, "Khong tim thay dau sach vua nhap.", 0);
		else{
			int check = XoaDauSach(lds, vitri);
			if (check == 1) {
				LuuDuLieuDauSach(lds);
				DocDuLieuDauSach(lds);
				ConsoleProcess::ThongBao(20, 2, "Xoa dau sach thanh cong", 1);
			}
			else ConsoleProcess::ThongBao(20, 2, "Xoa dau sach that bai. Danh sach Rong", 0);
		}
		getch();
	}
	if (k == 6){
		string tenSach;
		InTieuDeDauSach(w);
		InDanhSachDauSach(lds, w);
		cout << "Nhap Ten Sach: ";
		getline(cin, tenSach);
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
	nhaptrangthaidms:
	cout << "Nhap trang thai(0: Cho muon duoc, 1: Da co doc gia muon, 2:Da thanh ly): ";
	getline(cin, trangthai);
	if (checkNhapSo0va1va2(trangthai) == 0){
		cout << "Vui long nhap dung du lieu.Nhap lai\n";
		goto nhaptrangthaidms;
	}

	cout << "Nhap Vi Tri: ";
	getline(cin, dms.ViTri);

	dms.MaSach = maSach;
	ChuanHoaChuoi(dms.ViTri);
	dms.TrangThai = stoi(trangthai);

}

void HieuChinhDanhMucSach(DanhMucSach &dms, int w[]){
	system("cls");
	cout << "-------Thong tin danh muc sach ban dau--------" << endl;
	cout << "Ma Sach: " << dms.MaSach << endl;
	cout << "Trang Thai: " << dms.TrangThai << endl;
	cout << "Vi Tri: " << dms.ViTri << endl;



	cout << "---------Nhap thong tin can chinh sua--------" << endl;
	NhapDanhMucSach(dms, dms.MaSach);
}

string NhapISBN(){
	string ISBN;
	nhapISBNthem:
	cout << "Nhap ISBN (gom 6 ki tu) can cap nhat: ";
	getline(cin, ISBN);
	if (checkNhapISBN(ISBN) == 0){
		cout << "Vui long nhap dung dinh dang.Nhap lai\n";
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
	int w[4] = { 20, 20, 35, 20 };
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
		getch();
	}
	if (k == 2){
		DanhMucSach *dms = new DanhMucSach;
		int stt = ldms.n;
		string maSach = p->data.ISBN + to_string(++stt);
		NhapDanhMucSach(*dms, maSach);
		NODE_DMS *ndms = KhoiTaoNodeDMS(*dms);
		ThemVaoCuoi(ldms, ndms);
		LuuDuLieuDauSach(lds);
		DocDuLieuDauSach(lds);
		ConsoleProcess::ThongBao(20, 2, "Them danh muc sach thanh cong", 1);

		getch();


	}

	if (k == 3) {
		InDanhSachDanhMucSach(ldms, w);
		string maSach;
		nhapmasachhc:
		cout << "Nhap ma sach can hieu chinh: ";
		getline(cin, maSach);
		if (checkNhapMaSach(maSach) == 0){
			cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
			goto nhapmasachhc;
		}
		NODE_DMS *pp = TimKiemDanhMucSach(ldms, maSach);
		if (pp == NULL) ConsoleProcess::ThongBao(20, 2, "Khong tim thay dau sach vua nhap.", 0);
		else{
			HieuChinhDanhMucSach(pp->data, w);
			LuuDuLieuDauSach(lds);
			DocDuLieuDauSach(lds);
			ConsoleProcess::ThongBao(20, 2, "Hieu chinh dau sach thanh cong", 1);
		}
		getch();

	}
	if (k == 4){
		InDanhSachDanhMucSach(ldms, w);
		string maSach;
		nhapmasachxoa:
		cout << "Nhap ma sach can xoa: ";
		getline(cin, maSach);
		if (checkNhapMaSach(maSach) == 0){
			cout << "Du lieu tim kiem khong hop le. Vui long nhap lai.\n";
			goto nhapmasachxoa;
		}
		
		int check = XoaNodeCoKhoaBatKi(ldms, maSach);
		if (check == -1) ConsoleProcess::ThongBao(20, 2, "Danh Sach Rong", 0);
		else if (check == 1){
			ldms.n--;
			LuuDuLieuDauSach(lds);
			DocDuLieuDauSach(lds);
			ConsoleProcess::ThongBao(20, 2, "Xoa sach thanh cong", 1);
		}
		else ConsoleProcess::ThongBao(20, 2, "Khong tim thay ma sach vua nhap", 1);
		
		getch();
	}
}

void LayViTriNodeDuocChon(LIST_DS &lds){
	int w[7] = { 20, 10, 45, 10, 35, 18, 25 };
	InTieuDeDauSach(w);
	InDanhSachDauSach(lds, w);
	string ISBN = NhapISBN();
	int vitri = TimKiemDauSach(lds, ISBN);
	if (vitri == -1) {
		ConsoleProcess::ThongBao(20, 2, "Khong tim thay dau sach vua nhap.", 0);
		getch();
	}

	else{
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
	}
	return;
}

//-------------------------------END process Danh Muc Sach---------------------------------------

int LuaChon2(){
	Menu a(35, 80, 1);
	a.Set_Header("MENU LUA CHON");
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
	a.add("4. Thoat");
	int _err;
	int k = a.run(_err);
	if (_err) k = 4;
	return k;
}

int main()
{
	TREE t;
	KhoiTaoCay(t);
	DocDuLieuDocGia(t);
	LIST_DS lds;
	KhoiTaoDauSach(lds);
	DocDuLieuDauSach(lds);
	ConsoleProcess::ShowCur(0);
	while (true){
		int k = LuaChon();
		switch (k){
		case 1: CapNhatDanhSachCacDocGia(t); break;///OK
		case 2:	main2(lds); break;///OK
		case 3: LayViTriNodeDuocChonMuonTra(t,lds); break;
		case 4:  return 0; break;
		}
	}
	system("pause");
	return 0;
}