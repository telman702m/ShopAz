//---------------------------------------------------------------------------
#ifndef GroupProductH
#define GroupProductH

#include <vector>
#include <vector>
#include "Declaration.h"
#include "Synchronize.h"
#include "TBaseData.h"

//---------------------------------------------------------------------------
class TGroupProduct : public TBaseData
{
private:

public:
	static const wchar_t *NameTableDB;
	static TDescFields **GroupProdFieldsTableDB;
	static int CountGroupProdFieldsTableDB;
    static bool GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB);

	static void __fastcall LoadFromDB(TMyFDQuery *FDQuery);
	static TGroupProduct* __fastcall GetGroupProdById(int id);
	static TGroupProduct* __fastcall GetGroupProdByName(UnicodeString Name);
	bool __fastcall LoadRecordId(TMyFDQuery *FDQuery);

	UnicodeString GroupCode;
	UnicodeString Name;
	UnicodeString Description;
	bool Enabled;

	__fastcall TGroupProduct(void);
	__fastcall TGroupProduct(const TGroupProduct &GroupProduct);
	TGroupProduct& __fastcall operator=(const TGroupProduct &GroupProduct);

	void __fastcall Clear(void);

	void __fastcall InsertAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall SaveAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall DeleteObjectFromDb(TMyFDQuery *FDQuery);

};

#endif
