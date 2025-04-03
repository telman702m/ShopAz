//---------------------------------------------------------------------------
#ifndef WorkersH
#define WorkersH
//---------------------------------------------------------------------------

#include <vector>
#include "Declaration.h"
#include "Person.h"
//#include "MyDump.hpp"
#include "TBaseData.h"
#include "ObjectManager.h"

//---------------------------------------------------------------------------
class TWorkers : public TPerson
{
private:

public:
	static const wchar_t *NameTableDB;
	static TDescFields **WorkerFieldsTableDB;
	static int CountWorkerFieldsTableDB;
    static bool GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB);

	static UnicodeString PrivilegName[5];
//	static 	vector <TWorkers*> VWorkers;
	static TWorkers* __fastcall GetWorkerById(int id);
	static void __fastcall LoadFromDB(TMyFDQuery *FDQuery);

	UnicodeString Login;
	UnicodeString Password;
	int idUnitShop;
	TPrivilege Privilege;

	// ---- functions -----
	__fastcall TWorkers(void);
	void __fastcall Clear(void);

	void __fastcall InsertAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall SaveAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall DeleteObjectFromDb(TMyFDQuery *FDQuery);

	bool __fastcall LoadRecordId(TMyFDQuery *FDQuery);
};
#endif
