#include "Template.h"

/// cac phim bam
#define Normal_Color 15
#define Special_Color 159
#define Control_Enter 13
#define Control_Up 72
#define Control_Down 80
#define Control_Left 75
#define Control_Right 77
#define Control 224
#define Control_Esc 27
#define Control_BackSpace 8
#define Control_Ctrl 17
#define Control_Tab 9
#define CanLe 27
#define database "data.txt"

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

