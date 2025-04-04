//---------------------------------------------------------------------------
#ifndef ProductH
#define ProductH

#include <vector>
#include "Declaration.h"

#include "GroupProduct.h"
#include "UnitGroupProduct.h"
#include "Price.h"
#include "TBaseData.h"
#include "ObjectManager.h"

//---------------------------------------------------------------------------
class TProduct : public TBaseData
{
private:

public:
	const static wchar_t *NameTableDB;
	static TDescFields **ProductFieldsTableDB;
	static int CountProductFieldsTableDB;
    static bool GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB);

	static TProduct* __fastcall GetProductById(int id);
	static bool __fastcall LoadDataFromFile(char *FileNmae);
	static bool __fastcall SaveDataToFile(char *FileNmae);
	static void __fastcall LoadFromDB(TMyFDQuery *FDQuery, bool bLoadAll);
	static void __fastcall ZeroBalance(void);
	bool __fastcall LoadRecordId(TMyFDQuery *FDQuery);

	static int LastIdDb;

	int IdGroup;
	UnicodeString Code;
	UnicodeString Name;
	UnicodeString Unit;
	bool WholeUnit;
	TPrice PurchaseCash;
	TPrice DollarPrice;
	TPrice WholePrice;
	TPrice SellingPrice;
	UnicodeString Description;

	// Additional fields
	TGroupProduct *GroupProd;
	TCount *CountBalance;
	bool Enable;

	__fastcall TProduct(void);
	__fastcall TProduct(const TProduct &Product);
	const TProduct& __fastcall operator=(const TProduct &Product);
	void __fastcall Clear(void);

	void __fastcall InsertAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall SaveAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall DeleteObjectFromDb(TMyFDQuery *FDQuery);
};

#endif
