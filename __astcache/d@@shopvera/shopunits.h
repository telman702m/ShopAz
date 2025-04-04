//---------------------------------------------------------------------------
#ifndef ShopUnitsH
#define ShopUnitsH

#include <vector>
#include "Declaration.h"
#include "Person.h"
#include "TBaseData.h"
#include "ObjectManager.h"

//---------------------------------------------------------------------------
class TShopUnits : public TPerson
{
private:
    UnicodeString uTmp;
public:
	const static wchar_t *NameTableDB;
	static TDescFields **ShopUnitsFieldsTableDB;
	static int CountShopUnitsFieldsTableDB;
    static bool GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB);

	static int *upp;
	static int CountUnits;
	static TShopUnits* Buyer;
	static TShopUnits* Provisioner;
	static TShopUnits* Expenses;
	static TShopUnits* Empty;
	static UnicodeString ShopNetName;

	static void __fastcall LoadShopNetNameFromDB(TMyFDQuery *FDQuery);
	static void __fastcall LoadFromDB(TMyFDQuery *FDQuery);
	static int __fastcall GetArrayIndexForIdBuyer(int IdBuyer);

	static TShopUnits* __fastcall GetUnitById(int id);
	static int __fastcall GetIndexUnitById(int id);

	TypeShopUnit TypeUnit;
	TDate LoadDateData;

	// ---- functions -----
	__fastcall TShopUnits(void);
	__fastcall TShopUnits(const TShopUnits &ShopUnits);
	const TShopUnits& __fastcall operator=(const TShopUnits &ShopUnits);
	void __fastcall Clear(void);

	void __fastcall InsertAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall SaveAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall DeleteObjectFromDb(TMyFDQuery *FDQuery);

	void __fastcall UpdateStartDate(TMyFDQuery *FDQuery, TDate NewDate, int id);

	static void __fastcall CreateBuyerUnit(void);
	static void __fastcall CreateProvisionerUnit(void);
	static void __fastcall CreateExpensesUnit(void);
	static void __fastcall CreateEmptyUnit(void);
	static void __fastcall ArrangeUppArray(TShopUnits *ThisShopUnit);

	bool __fastcall LoadRecordId(TMyFDQuery *FDQuery);
};
#endif
