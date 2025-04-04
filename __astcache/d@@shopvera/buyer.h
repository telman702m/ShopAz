//---------------------------------------------------------------------------
#ifndef BuyerH
#define BuyerH

#include <vector>
#include "Declaration.h"
#include "Person.h"
//#include "MyDump.hpp"
#include "Price.h"
#include "Synchronize.h"
#include "TBaseData.h"

//---------------------------------------------------------------------------
class TBuyer : public TPerson
{
private:
//    static TDescFields **DescFields;
public:
	static const wchar_t *NameTableDB;
	static TDescFields **BuyerFieldsTableDB;
	static int CountBuyerFieldsTableDB;
    static bool GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB);

	static TBuyer* Unknow;
	static TBuyer* Empty;

	static void __fastcall CreateUnknowBuyer(void);
	static void __fastcall CreateEmptyBuyer(void);
	static void __fastcall LoadFromDB(TMyFDQuery *FDQuery, bool bLoadAll);
	static TBuyer* __fastcall GetBuyerById(int id);
	static bool __fastcall LoadDataFromFile(char *FileNmae);
	static bool __fastcall SaveDataToFile(char *FileNmae);

	UnicodeString Organization;

	// ---- functions -----
	__fastcall TBuyer(void);
	__fastcall TBuyer(const TBuyer &Buyer);
	const TBuyer& __fastcall operator=(const TBuyer &Buyer);

	void __fastcall Clear(void);
	bool __fastcall LoadRecordId(TMyFDQuery *FDQuery);
	void __fastcall InsertAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall SaveAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall DeleteObjectFromDb(TMyFDQuery *FDQuery);

};
#endif
