//---------------------------------------------------------------------------
#ifndef ProvisionerH
#define ProvisionerH

#include <vector>
#include "Declaration.h"
#include "Person.h"
#include "Price.h"
#include "Synchronize.h"
#include "TBaseData.h"

//---------------------------------------------------------------------------
class TProvisioner : public TPerson
{
private:

public:
	const static wchar_t *NameTableDB;
	static TDescFields **ProvisionerFieldsTableDB;
	static int CountProvisionerFieldsTableDB;
    static bool GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB);

	static TProvisioner* Unknow;

	static void __fastcall LoadFromDB(TMyFDQuery *FDQuery, bool bLoadAll);
	static TProvisioner* __fastcall GetProvisionerById(int id);
	static bool __fastcall LoadDataFromFile(char *FileNmae);
	static bool __fastcall SaveDataToFile(char *FileNmae);
	bool __fastcall LoadRecordId(TMyFDQuery *FDQuery);

	UnicodeString Organization;

	// ---- functions -----
	__fastcall TProvisioner(void);
	__fastcall TProvisioner(const TProvisioner &Provisioner);
	const TProvisioner& __fastcall operator=(const TProvisioner &Provisioner);
	void __fastcall Clear(void);

	void __fastcall InsertAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall SaveAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall DeleteObjectFromDb(TMyFDQuery *FDQuery);

	static void __fastcall CreateUnknowProvisioner(void);
};
//---------------------------------------------------------------------------
#endif
