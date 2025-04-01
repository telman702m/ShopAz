//---------------------------------------------------------------------------
#ifndef SynchronizeH
#define SynchronizeH

#include <vector>

//#include "MyDump.hpp"
#include "Declaration.h"

const int CountFieldsSynchronize = 7;

//---------------------------------------------------------------------------
class TSynchronize : public TObject
{
private:

public:
	static 	vector <TSynchronize*> VSynchronize;
	static int LastId;
	static bool bChangedAccess;

	static TBuyer *TmpBuyer;
	static TProvisioner *TmpProvisioner;
	static TGroupProduct *TmpGroupProd;
	static TProduct *TmpProduct;
	static TSelectProduct *TmpSelectProduct;
	static TMoveProduct *TmpMoveProduct;

	int id;
	int idShop;
	int idWorker;
	TabDB TableDB;
	int idRecord;
	TRecordType RecordType;
	TDateTime RecDateTime;

	static UnicodeString SynchronizeDbFields[CountFieldsSynchronize][2];

	static void __fastcall InitLastIdTables(TMyFDQuery *FDQuery);
	static void __fastcall InsertToDb(TMyFDQuery *FDQuery, int idShopUnit, TabDB TableIndex, int idRecord, TRecordType RecType);
	static void __fastcall InsertToDb(TMyFDQuery *FDQuery, TabDB TableIndex, int idRecord, TRecordType RecType);
	static void __fastcall LoadFromDB(TMyFDQuery *FDQuery, int idShop, int idWorker);
	static void __fastcall ApplySinc(void);

	__fastcall TSynchronize(void);
};
#endif
