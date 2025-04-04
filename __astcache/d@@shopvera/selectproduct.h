//---------------------------------------------------------------------------
#ifndef SelectProductH
#define SelectProductH

#include <vcl.h>
#include "Declaration.h"
#include "Product.h"
#include "Price.h"
#include "TBaseData.h"
#include "ObjectManager.h"

class TMoveProduct;

//---------------------------------------------------------------------------
class TSelectProduct : public TBaseData
{

private:

public:
	const static wchar_t *NameTableDB;
	static TDescFields **SelectProdFieldsTableDB;
	static int CountSelectProdFieldsTableDB;
	static bool GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB);

	static bool __fastcall LoadDataFromFile(char *FileNmae);
	static bool __fastcall SaveDataToFile(char *FileNmae);
	static void __fastcall LoadFromDB(TMyFDQuery *FDQuery, bool bLoadAll);
	static void __fastcall DeleteObject(TSelectProduct *SelProd);
	static void __fastcall CheckExcessObjects(void);

	static int LastIdDb;
	static bool bLoaded;

	int idMove;                 // id  on Move
	TDateTime SelectDateTime;   // Time of selected product
	int idProduct;              // idProduct
	TPrice IncomingPrice;       // Incoming Price product
	TPrice Price;  				// Price product
	TCount Count;               // Count Products

	// Additional fields in memory
	TProduct *Product;
	TPrice TotalCostPrice;
	TPrice TotalPrice;

	// Constructor
	__fastcall TSelectProduct(void);
	__fastcall TSelectProduct(const TSelectProduct &SelectProduct);
	const TSelectProduct& __fastcall operator=(const TSelectProduct &SelectProduct);
	void __fastcall Clear(void);
	void __fastcall CalcTotalPrice(void);

	void __fastcall InsertAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall SaveAtObjectToDb(TMyFDQuery *FDQuery);
	void __fastcall DeleteObjectFromDb(TMyFDQuery *FDQuery);
	bool __fastcall CheckCorrectData(void);

	bool __fastcall LoadRecordId(TMyFDQuery *FDQuery);

	void __fastcall UpdateMoveProduct(void);
};
#endif

