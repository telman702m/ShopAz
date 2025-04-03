//---------------------------------------------------------------------------
#ifndef DeclarationH
#define DeclarationH

//#define CHECK_SORT_ORDER
#include "TMyFDQuery.h"

#include <vcl.h>
#include "Count.h"

const int MaxBuffer = 4096;
const wchar_t ucs2 = 0xfeff;

extern wchar_t wBuffer[];
extern char cBuffer[];

extern int iLang;
extern TFormatSettings FSet;

extern const wchar_t *uInsert1;
extern const wchar_t *uInsert2;
extern const wchar_t *uUpdate1;
extern const wchar_t *uUpdate2;
extern const wchar_t *wLostConnection[2];
extern const wchar_t *wOperationName[3];
extern const wchar_t *uIllegalSymbol[2];

extern const wchar_t *wDateTimeFormat;
extern const wchar_t *wDateTimePickerFormat;
extern const wchar_t *uCaptionWarning[2];
extern const wchar_t *uCaptionError[2];
extern const wchar_t *uCaptionInform[2];
extern const wchar_t *uIllegalSymbol[2];

extern const wchar_t *wButSaveCaption[];
extern const wchar_t *wButInsertCaption[];
extern const wchar_t *wButCancelCaption[];
extern const wchar_t *wButCloseCaption[];
extern const wchar_t *wSaveChangesMessage[2];

using namespace std;

//const int CountShopUnit = 4;

enum ListConfParam {LCP_LANG=0, LCP_SHOP=1, LCP_WORKER=2, LCP_GROUP=3};

enum TypeShopUnit {SHP_UNKNOW=-1, SHP_STOCK=1, SHP_SHOP=2};
enum TPrivilege {PRV_SUPER=0, PRV_ADMIN=1, PRV_MANAGER=2, PRV_SELLER=3, PRV_UNKNOW=4};
enum TMoveType {MOV_UNKNOW=-1, MOV_SALE=0, MOV_RET=1, MOV_INC=2, MOV_OUT=3, MOV_DEBT=4, MOV_EXP=5, MOV_DEBT_PROVIS=6};

enum TButtonAction {BA_UNKNOW=-1 ,BA_VIEW=0, BA_SELECT=1, BA_EDIT=2, BA_DEL=3, BA_ADD=4,
					BA_SALE=5, BA_RETURN=6, BA_INCOM=7, BA_OUT=8, BA_DEBT=9, BA_EXP=10, BA_DEBT_PROVIS=11};  // use for buttons click

enum TCalledObj {OBJ_UNDEF=-1, OBJ_OWNER=0, OBJ_EXTERN=1};   // use for detect payment type

enum TYPE_LIST {LS_GROUP=0, LS_PROD=1, LS_MOVEPROD=2, LS_ATOM=3, LS_BUYER=4, LS_SHOPUNIT=5, LS_PROVIS=6, LS_REPORTS=7};
enum TabDB {TB_UNDEF=-1, TB_GROUP=0, TB_PROD=1, TB_BUYER=2, TB_PROVIS=3, TB_MOVEP=4, TB_SELECTP=5};
enum TRecordType {RT_UNDEF = -1, RT_INSERT = 0, RT_UPDATE=1, RT_DELETE=3};
enum ToolBarStat {TS_SEP0=0, TS_VIEW=1, TS_EDIT=2, TS_ADD=3, TS_DEL=4, TS_SEP1=5, TS_EXL=6, TS_PRT=7, TS_SEP2=8, TS_CLOS=9};
enum LOGS {LG_UNDEF=-1, LG_CONNECT=0, LG_DISCONNECT=1, LG_INSERT=2, LG_UPDATE=3, LG_DELETE=4};
enum MEXIT {NORMAL=0, ABNORMAL=1, UNDEFINE=2};

class MyListView;
class TBuyer;
class TMoveProduct;
class TSelectProduct;
class TProduct;
class TGroupProduct;
class TShopUnits;
class TProvisioner;
class TBaseData;

//---------------------------------------------------------------------------
/*typedef struct _TDescFields
{
	wchar_t *Field;
	wchar_t *Type;
	wchar_t *Null;
	wchar_t *Key;
	wchar_t *Default;
	wchar_t *Extra;
} TDescFields;*/

//---------------------------------------------------------------------------
typedef struct _TColumnsData
{
	UnicodeString Caption[2];
	int Width;
	TAlignment TMAlign;
	bool Visible;
	bool bSum;
} TColumnsData;

//---------------------------------------------------------------------------
typedef struct _TLocate
{
	int Left;
	int Top;
	int Width;
	int Height;
} TLocate;
//---------------------------------------------------------------------------
typedef struct _TProductCount
{
	TProduct *Product;
	TCount BalanceCount;
} TProductCount;
//---------------------------------------------------------------------------
typedef struct _TSVersion
{
	UnicodeString ProductName;
	UnicodeString FileVersion;
	UnicodeString LegalCopyright;
	UnicodeString CompanyName;
	UnicodeString UpdaterName;
} TSVersion;
//---------------------------------------------------------------------------
typedef struct _TProductVersion
{
	unsigned int AMajor;
	unsigned int AMinor;
	unsigned int ABuild;
} TProductVersion;

#endif

