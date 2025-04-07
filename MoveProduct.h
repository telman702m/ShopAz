//---------------------------------------------------------------------------
#ifndef MoveProductH
#define MoveProductH

#include <vector>
//#include "MyDump.hpp"
#include "Declaration.h"

#include "SelectProduct.h"
#include "UnitBuyerData.h"
#include "UnitProduct.h"
#include "ShopUnits.h"
#include "Synchronize.h"
#include "TBaseData.h"

//---------------------------------------------------------------------------
class TMoveProduct  : public TBaseData
{

private:

public:
	const static wchar_t *NameTableDB;
	static TDescFields **MoveFieldsTableDB;
	static int CountMoveFieldsTableDB;
    static bool GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB);

	static vector <TMoveProduct*> VMoveProduct;

	static void __fastcall LoadFromDB(TMyFDQuery *FDQuery, bool bLoadAll);
	static bool __fastcall LoadDataFromFile(char *FileNmae);
	static bool __fastcall SaveDataToFile(char *FileNmae);
//	static void ApplySyncronizeMove(TMyFDQuery *FDQuery, TSynchronize *SyncData);
	static void __fastcall CalcUnitsBalance(void);
	static void __fastcall CalcDebts(void);

	static void __fastcall CorrectPaymentInOldDB(TMyFDQuery *FDQuery);   // temporary method
	static bool __fastcall IsContainId(int id);
	bool __fastcall LoadRecordId(TMyFDQuery *FDQuery);
	bool __fastcall AssignUnits(void);

	static int LastIdDb;

	// Fields for DB
	TMoveType MoveType;
	int idSource;
	int idSourcePerson;
	int idTarget;
	int idTargetPerson;
	TDateTime DateTime;
	TPrice Discount;
	TPrice ActualPayment;
	TPrice Debt;
	UnicodeString Description;

	// Additional fields in memory
	TShopUnits *SourceUnit;
	TPerson *SourcePerson;

	TShopUnits *TargetUnit;
	TPerson *TargetPerson;

	TPrivilege Privilege;

	TPrice TotalCostPrice;
	TPrice TotalPrice;
	TPrice TotalPayment;
	double dPercent;

	vector <TSelectProduct*> VSelectedProd;


	// Metods
	__fastcall TMoveProduct(void);
	__fastcall ~TMoveProduct(void);
	__fastcall TMoveProduct(const TMoveProduct &MoveProduct);
	const TMoveProduct& __fastcall operator=(const TMoveProduct &MoveProduct);

	void __fastcall DeleteVectorSelectProduct(void);
	void __fastcall Clear(void);
	void __fastcall CalcTotalPrice(void);
	void __fastcall CalcObjectUnitsBalance(void);
	void __fastcall CorrectUnitsBalance(int Index, int iMult);
	void __fastcall CalcObjectDebts(void);

	void __fastcall InsertAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall SaveAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall DeleteObjectFromDb(TMyFDQuery *FDQuery);

	bool __fastcall IsContainProduct(UnicodeString uProdName);
	int __fastcall GetIndexInVSelectById(int id);
	int __fastcall GetBalanceMult(void);

	bool __fastcall CheckCorrect(void);

	void __fastcall ShowVectorMoveProduct(void);
};

#endif
