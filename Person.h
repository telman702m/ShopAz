//---------------------------------------------------------------------------
#ifndef PersonH
#define PersonH

#include "Declaration.h"
//#include "MyDump.hpp"
#include "TBaseData.h"

//---------------------------------------------------------------------------
class TPerson : public TBaseData
{
private:

public:
//	int id;
	UnicodeString Surname;
	UnicodeString Name;
	UnicodeString Patronymic;

	UnicodeString Address;
	UnicodeString Phone1;
	UnicodeString Phone2;
	UnicodeString Description;
	bool Enabled;

	// Additional fields in memory
	UnicodeString SumName;

	TPrice TotalShoped;
	TPrice TotalReturn;
	TPrice TotalIncoming;
	TPrice TotalMoved;
	TPrice TotalDiscount;
	TPrice TotalDebt;
	TPrice TotalExpenses;

	// ---- functions -----
	__fastcall TPerson(void);
	__fastcall TPerson(const TPerson &Person);
	const TPerson& __fastcall operator=(const TPerson &Person);
//	const TPerson& operator=(const UnicodeString &uTmp);
	void __fastcall Clear(void);
	void __fastcall SetPricesZero();
	void __fastcall SetSumName(void);

	virtual void __fastcall InsertAtObjectToDb(TMyFDQuery *FDQuery) = 0;
	virtual void __fastcall SaveAtObjectToDb(TMyFDQuery *FDQuery) = 0;
	virtual void __fastcall DeleteObjectFromDb(TMyFDQuery *FDQuery) = 0;

//	virtual bool LoadRecordId(TMyQuery *SqlQuery);

};
//---------------------------------------------------------------------------
#endif
