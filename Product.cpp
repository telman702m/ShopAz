//---------------------------------------------------------------------------
#pragma hdrstop

#include "Product.h"
#include "UnitProductList.h"
#include "Shop.h"
#include "SelectProduct.h"
#include "Synchronize.h"
#include "UnitProgressBar.h"
#include "TUtills.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

const wchar_t *uProdLostGroupProd[2] = {
	L"Товар не входит ни в одну из группы товаров!",
	L"Mal heç bir mallar grupa daxil deyil!"
};

UnicodeString ProgressLoadProduct[2] = {
	L"Загрузка данных о \"Товарах\" с сервера",
	L"Serverdən \"Mallar\" haqqında məlumatın yüklənməsi"
};
UnicodeString ProgressLoadBalance[2] = {
	L"Загрузка данных о \"Остатках товара\" с сервера",
	L"Serverdən \"Qalıq malların\" haqqında məlumatın yüklənməsi"
};

/*const int CountFieldsProduct = 18;
wchar_t *ProductDbFields[CountFieldsProduct][2] =
   {{L"id",               L" Int(11) Not Null Auto_increment, "},
	{L"IdGroup",          L" Int(11) DEFAULT NULL, "},
	{L"Code",             L" Char(20) DEFAULT NULL, "},
	{L"Name",             L" Char(64) DEFAULT NULL, "},
	{L"Unit",             L" Char(10) DEFAULT NULL, "},
	{L"WholeUnit",        L" SmallInt(1) DEFAULT NULL, "},
	{L"PurchasePrice1",   L" Int(8) DEFAULT '0', "},
	{L"PurchasePrice2",   L" Int(2) DEFAULT '0', "},
	{L"SellingPrice1",    L" Int(8) DEFAULT '0', "},
	{L"SellingPrice2",    L" Int(2) DEFAULT '0', "},
	{L"DollarPrice1",     L" Int(8) DEFAULT '0', "},
	{L"DollarPrice2",     L" Int(2) DEFAULT '0', "},
	{L"WholePrice1",      L" Int(8) DEFAULT '0', "},
	{L"WholePrice2",      L" Int(2) DEFAULT '0', "},
	{L"Description",      L" Varchar(368) DEFAULT NULL, "},
	{L"Enable",      	  L" SmallInt(1) DEFAULT '0', "},
	{L"Deleted",		  L" Smallint(1) "},
	{L"LastUpdate",	  	  L" TIMESTAMP CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, "}
   };*/

vector <TProduct*> TProduct::VProduct;
int TProduct::LastIdDb = 0;

const wchar_t *TProduct::NameTableDB;
TDescFields **TProduct::ProductFieldsTableDB = NULL;
int TProduct::CountProductFieldsTableDB = 0;

//---------------------------------------------------------------------------
__fastcall TProduct::TProduct(void) : TBaseData()
{
	VBaseData = (vector <TBaseData*> *)&VProduct;

	CountBalance = new TCount[TShopUnits::CountUnits];
	Clear();
}
//---------------------------------------------------------------------------
bool TProduct::GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB)
{
	NameTableDB = _NameTableDB;
	return GetFieldsFromDB(FDQuery, NameTableDB, ProductFieldsTableDB, CountProductFieldsTableDB);
}
//---------------------------------------------------------------------------
void __fastcall TProduct::Clear(void)
{
	IdGroup = -1;
	Code = L"";
	Name = L"";
	Unit = L"";
	PurchaseCash = 0;
	SellingPrice = 0;
	DollarPrice = 0;
	WholePrice = 0;

	Description = L"";
	WholeUnit = false;

	GroupProd = NULL;

	for(int i=0; i < TShopUnits::CountUnits; i++) {
		CountBalance[i] = 0;
	}
	Enable = false;
}

//---------------------------------------------------------------------------
__fastcall TProduct::TProduct(const TProduct &Product) : TBaseData(Product)
{
	IdGroup = Product.IdGroup;
	Code = Product.Code;
	Name = Product.Name;
	Unit = Product.Unit;
	PurchaseCash = Product.PurchaseCash;
	SellingPrice = Product.SellingPrice;
	DollarPrice =  Product.DollarPrice;
	WholePrice = Product.WholePrice;

	Description = Product.Description;
	WholeUnit = Product.WholeUnit;

	GroupProd = Product.GroupProd;

	for(int i=0; i < TShopUnits::CountUnits; i++) {
		CountBalance[i] = Product.CountBalance[i];
	}
	Enable = Product.Enable;
}

//---------------------------------------------------------------------------
const TProduct& __fastcall TProduct::operator=(const TProduct &Product)
{
	TBaseData::operator=(Product);
	IdGroup = Product.IdGroup;
	Code = Product.Code;
	Name = Product.Name;
	Unit = Product.Unit;
	PurchaseCash = Product.PurchaseCash;
	SellingPrice = Product.SellingPrice;
	DollarPrice =  Product.DollarPrice;
	WholePrice = Product.WholePrice;

	Description = Product.Description;
	WholeUnit = Product.WholeUnit;

	GroupProd = Product.GroupProd;

	for(int i=0; i < TShopUnits::CountUnits; i++) {
		CountBalance[i] = Product.CountBalance[i];
	}
	Enable = Product.Enable;

	return *this;
}

//---------------------------------------------------------------------------
void __fastcall TProduct::InsertAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uProductDbData[] = {
		L"",
		IdGroup,
		Code,
		Name,
		Unit,
		int(WholeUnit),
		PurchaseCash.GetMoney(),
		PurchaseCash.GetCent(),
		SellingPrice.GetMoney(),
		SellingPrice.GetCent(),
		DollarPrice.GetMoney(),
		DollarPrice.GetCent(),
		WholePrice.GetMoney(),
		WholePrice.GetCent(),
		Description,
		int(Enable)
	};
	TFieldsValues FieldsValues[] = {
		{ProductFieldsTableDB[1]->Field, 	uProductDbData[1].w_str()},
		{ProductFieldsTableDB[2]->Field,	uProductDbData[2].w_str()},
		{ProductFieldsTableDB[3]->Field,	uProductDbData[3].w_str()},
		{ProductFieldsTableDB[4]->Field,	uProductDbData[4].w_str()},
		{ProductFieldsTableDB[5]->Field,	uProductDbData[5].w_str()},
		{ProductFieldsTableDB[6]->Field, 	uProductDbData[6].w_str()},
		{ProductFieldsTableDB[7]->Field, 	uProductDbData[7].w_str()},
		{ProductFieldsTableDB[8]->Field, 	uProductDbData[8].w_str()},
		{ProductFieldsTableDB[9]->Field, 	uProductDbData[9].w_str()},
		{ProductFieldsTableDB[10]->Field, 	uProductDbData[10].w_str()},
		{ProductFieldsTableDB[11]->Field, 	uProductDbData[11].w_str()},
		{ProductFieldsTableDB[12]->Field,	uProductDbData[12].w_str()},
		{ProductFieldsTableDB[13]->Field,	uProductDbData[13].w_str()},
		{ProductFieldsTableDB[14]->Field,	uProductDbData[14].w_str()},
		{ProductFieldsTableDB[15]->Field,	uProductDbData[15].w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	ExecSQL(FDQuery, FieldsValues, Count, NameTableDB, ProductFieldsTableDB[0]->Field, TabDB::TB_PROD);
//	UnicodeString uQuery = FormationInsertString(NameTableDB, ProductFieldsTableDB, uProductDbData, CountProductFieldsTableDB);
//	ExecSQL(FDQuery, uQuery, NameTableDB, TabDB::TB_PROD, TRecordType::RT_INSERT, LOGS::LG_INSERT);
}

//---------------------------------------------------------------------------
void __fastcall TProduct::SaveAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uProductDbData[] = {
		L"",
		IdGroup,
		Code,
		Name,
		Unit,
		int(WholeUnit),
		PurchaseCash.GetMoney(),
		PurchaseCash.GetCent(),
		SellingPrice.GetMoney(),
		SellingPrice.GetCent(),
		DollarPrice.GetMoney(),
		DollarPrice.GetCent(),
		WholePrice.GetMoney(),
		WholePrice.GetCent(),
		Description,
		int(Enable)
	};
	TFieldsValues FieldsValues[] = {
		{ProductFieldsTableDB[1]->Field, 	uProductDbData[1].w_str()},
		{ProductFieldsTableDB[2]->Field,	uProductDbData[2].w_str()},
		{ProductFieldsTableDB[3]->Field,	uProductDbData[3].w_str()},
		{ProductFieldsTableDB[4]->Field,	uProductDbData[4].w_str()},
		{ProductFieldsTableDB[5]->Field,	uProductDbData[5].w_str()},
		{ProductFieldsTableDB[6]->Field, 	uProductDbData[6].w_str()},
		{ProductFieldsTableDB[7]->Field, 	uProductDbData[7].w_str()},
		{ProductFieldsTableDB[8]->Field, 	uProductDbData[8].w_str()},
		{ProductFieldsTableDB[9]->Field, 	uProductDbData[9].w_str()},
		{ProductFieldsTableDB[10]->Field, 	uProductDbData[10].w_str()},
		{ProductFieldsTableDB[11]->Field, 	uProductDbData[11].w_str()},
		{ProductFieldsTableDB[12]->Field,	uProductDbData[12].w_str()},
		{ProductFieldsTableDB[13]->Field,	uProductDbData[13].w_str()},
		{ProductFieldsTableDB[14]->Field,	uProductDbData[14].w_str()},
		{ProductFieldsTableDB[15]->Field,	uProductDbData[15].w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	UnicodeString uQuery = FormationUpdateString(NameTableDB, FieldsValues, Count);
	ExecSQL(FDQuery, uQuery, NameTableDB, TabDB::TB_PROD, TRecordType::RT_UPDATE, LOGS::LG_UPDATE);
}
//---------------------------------------------------------------------------
void __fastcall TProduct::DeleteObjectFromDb(TMyFDQuery *FDQuery)
{
	UnicodeString uQuery = FormationDeleteString(NameTableDB, ProductFieldsTableDB[16]->Field);
	ExecSQL(FDQuery, uQuery, NameTableDB, TabDB::TB_PROD, TRecordType::RT_DELETE, LOGS::LG_DELETE);
}

//---------------------------------------------------------------------------
TProduct* __fastcall TProduct::GetProductById(int id)
{
	return (TProduct *)TBaseData::GetObjectById((vector <TBaseData*> *)&VProduct, id);
}
//---------------------------------------------------------------------------
bool __fastcall TProduct::SaveDataToFile(char *FileNmae)
{
	FILE *fs = fopen(FileNmae, "wb");
	if(fs == NULL) {
		return false;
	}
	fseek(fs, 0, SEEK_SET);
	fwprintf(fs, L"%lc", ucs2);

	fwprintf(fs, L"'%s'\n", TDateTime::CurrentDate().FormatString(L"dd.mm.yyyy").w_str());

	for(unsigned i=0; i < VProduct.size(); i++) {
		fwprintf(fs, L"'%d'\t'%d'\t'%ls'\t'%ls'\t'%ls'\t'%d'\t'%d'\t'%d'\t'%d'\t'%d'\t'%d'\t'%d'\t'%d'\t'%d'\t'%ls'\t'%d'\n",
					 VProduct[i]->id,
					 VProduct[i]->IdGroup,
					 VProduct[i]->Code.w_str(),
					 VProduct[i]->Name.w_str(),
					 VProduct[i]->Unit.w_str(),
					 VProduct[i]->WholeUnit,
					 VProduct[i]->PurchaseCash.GetMoney(),
					 VProduct[i]->PurchaseCash.GetCent(),
					 VProduct[i]->SellingPrice.GetMoney(),
					 VProduct[i]->SellingPrice.GetCent(),
					 VProduct[i]->DollarPrice.GetMoney(),
					 VProduct[i]->DollarPrice.GetCent(),
					 VProduct[i]->WholePrice.GetMoney(),
					 VProduct[i]->WholePrice.GetCent(),
					 TUtills::ReplaceSymbol(TUtills::ReplaceSymbol(VProduct[i]->Description.w_str(), L'\r', wchar_t(27)), L'\n', wchar_t(28)),
					 VProduct[i]->Enable);
	}
	fclose(fs);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TProduct::LoadDataFromFile(char *FileName)
{
	if(!LoadFileToWBuffer(FileName)) {
		return false;
	}


	UnicodeString uTmp;
//	int counter = 0;
	int CountParseFields = CountProductFieldsTableDB - 2;

	while(Offset < FileSize) {

		Offset += TUtills::ParseWstring(WFileBuffer + Offset, wpws, CountParseFields, FileSize - Offset);
		if(Offset == 0) {
			delete WFileBuffer;
			return false;
		}

		TProduct *TmpProduct = new TProduct();

		uTmp = wpws[0];
		TmpProduct->id = uTmp.ToInt();
		uTmp = wpws[1];
		TmpProduct->IdGroup = uTmp.ToInt();
		uTmp = wpws[2];
		TmpProduct->Code = uTmp;
		uTmp = wpws[3];
		TmpProduct->Name = uTmp;
		uTmp = wpws[4];
		TmpProduct->Unit = uTmp;
		uTmp = wpws[5];
		TmpProduct->WholeUnit = uTmp.ToInt();
		uTmp = wpws[6];
		TmpProduct->PurchaseCash.SetMoney(uTmp.ToInt());
		uTmp = wpws[7];
		TmpProduct->PurchaseCash.SetCent(uTmp.ToInt());
		uTmp = wpws[8];
		TmpProduct->SellingPrice.SetMoney(uTmp.ToInt());
		uTmp = wpws[9];
		TmpProduct->SellingPrice.SetCent(uTmp.ToInt());
		uTmp = wpws[10];
		TmpProduct->DollarPrice.SetMoney(uTmp.ToInt());
		uTmp = wpws[11];
		TmpProduct->DollarPrice.SetCent(uTmp.ToInt());
		uTmp = wpws[12];
		TmpProduct->WholePrice.SetMoney(uTmp.ToInt());
		uTmp = wpws[13];
		TmpProduct->WholePrice.SetCent(uTmp.ToInt());
		uTmp = wpws[14];
		TmpProduct->Description = TUtills::ReplaceSymbol(TUtills::ReplaceSymbol(uTmp.w_str(), wchar_t(27), L'\r'), wchar_t(28), L'\n');
		uTmp = wpws[15];
		TmpProduct->Enable = uTmp.ToInt();

		if(TmpProduct->id > LastIdDb) {
			LastIdDb = TmpProduct->id;
		}
		// additional fields
		TmpProduct->GroupProd = TGroupProduct::GetGroupProdById(TmpProduct->IdGroup);

		if(TmpProduct->GroupProd == NULL) {
			Application->MessageBox(uProdLostGroupProd[iLang], uCaptionError[iLang], MB_OK);
			continue;
		}

		VProduct.push_back(TmpProduct);
//		counter++;
	}

	delete FileBuffer;
	FileBuffer = NULL;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TProduct::LoadFromDB(TMyFDQuery *FDQuery, bool bLoadAll)
{
	VProduct.clear();

	if(!bLoadAll) {
		AnsiString aTmp = FormShop->FDConnection1->Params->Database + "_Product.txt";
		bLoadAll = !LoadDataFromFile(aTmp.c_str());
	}

	UnicodeString uFields;
	int CountFields = 16;
	if(!bLoadAll) {
		CountFields = 17;
	}
	for(int i=0; i < CountFields; i++) {
		uFields += ProductFieldsTableDB[i]->Field;
		if(i < CountFields - 1) {
			uFields += L",";
		}
	}

	UnicodeString uTmp = "Select " + uFields + " from ";
	uTmp += NameTableDB;
	uTmp += L" where ";
	if(bLoadAll) {
		uTmp += L"Deleted = '0'";
	} else {
		uTmp += L"LastUpdate > '" + MaxUpdateDate.FormatString("yyyy-mm-dd") + L"'";
	}

	FDQuery->SQL->Text = uTmp;
	bool bSuccess = false;
	int iDel;

	TimerSyncDisable();

	while(!bSuccess) {
		try {
			FormProgressBar->Show();
			FormProgressBar->Label1->Caption = ProgressLoadProduct[iLang];
			FormProgressBar->Update();
			FormProgressBar->Label1->Left = (FormProgressBar->ClientWidth - FormProgressBar->Label1->Width)/2;
			FormProgressBar->ProgressBar1->Position = 0;
			FormProgressBar->Update();
			FDQuery->Open();
            FDQuery->FetchAll();
			FormProgressBar->ProgressBar1->Max = FDQuery->RecordCount;

			while(!FDQuery->Eof) {
				TProduct *TmpProd = new TProduct();

				// Load data from MySql Data Base
				TmpProd->id = FDQuery->FieldByName(ProductFieldsTableDB[0]->Field)->AsString.ToInt();
				TmpProd->IdGroup = FDQuery->FieldByName(ProductFieldsTableDB[1]->Field)->AsString.ToInt();
				TmpProd->Code = FDQuery->FieldByName(ProductFieldsTableDB[2]->Field)->AsString;
				TmpProd->Name = FDQuery->FieldByName(ProductFieldsTableDB[3]->Field)->AsString;
				TmpProd->Unit = FDQuery->FieldByName(ProductFieldsTableDB[4]->Field)->AsString;
				TmpProd->WholeUnit = FDQuery->FieldByName(ProductFieldsTableDB[5]->Field)->AsString.ToInt();
				TmpProd->PurchaseCash.SetMoney(FDQuery->FieldByName(ProductFieldsTableDB[6]->Field)->AsString.ToInt());
				TmpProd->PurchaseCash.SetCent(FDQuery->FieldByName(ProductFieldsTableDB[7]->Field)->AsString.ToInt());
				TmpProd->SellingPrice.SetMoney(FDQuery->FieldByName(ProductFieldsTableDB[8]->Field)->AsString.ToInt());
				TmpProd->SellingPrice.SetCent(FDQuery->FieldByName(ProductFieldsTableDB[9]->Field)->AsString.ToInt());
				TmpProd->DollarPrice.SetMoney(FDQuery->FieldByName(ProductFieldsTableDB[10]->Field)->AsString.ToInt());
				TmpProd->DollarPrice.SetCent(FDQuery->FieldByName(ProductFieldsTableDB[11]->Field)->AsString.ToInt());
				TmpProd->WholePrice.SetMoney(FDQuery->FieldByName(ProductFieldsTableDB[12]->Field)->AsString.ToInt());
				TmpProd->WholePrice.SetCent(FDQuery->FieldByName(ProductFieldsTableDB[13]->Field)->AsString.ToInt());
				TmpProd->Description = FDQuery->FieldByName(ProductFieldsTableDB[14]->Field)->AsString;

				// Calc & fill additional fields
				TmpProd->GroupProd = TGroupProduct::GetGroupProdById(TmpProd->IdGroup);

				if(TmpProd->GroupProd == NULL) {
					Application->MessageBox(uProdLostGroupProd[iLang], uCaptionError[iLang], MB_OK);
				}

				if(bLoadAll) {
					VProduct.push_back(TmpProd);
				} else {
					iDel = FDQuery->FieldByName(ProductFieldsTableDB[16]->Field)->AsString.ToInt();
					int iIndex = TmpProd->GetArrayIndexById();

					if(iDel == 1) {
						if(iIndex != -1) {
							VProduct.erase(VProduct.begin() + iIndex);
						}
					} else {
						if(iIndex == -1) {
							int InsertIndex = TmpProd->GetArrayIndexById(true);
							VProduct.insert(VProduct.begin()+InsertIndex, TmpProd);
//							VProduct.push_back(TmpProd);
						}

					}
				}

				FDQuery->Next();

				FormProgressBar->ProgressBar1->Position++;
				FormProgressBar->Update();
			}
			FDQuery->Close();
			FormProgressBar->Close();

			bSuccess = true;

	   } catch (...) {
			FormProgressBar->Close();

			UnicodeString uTmp = uTmp.sprintf(wLostConnection[iLang], L"Select", NameTableDB);
			if(Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}
	if(FormProgressBar->Showing) {
		FormProgressBar->Close();
	}

	TimerSyncRestore();
}

//---------------------------------------------------------------------------
void __fastcall TProduct::ZeroBalance(void)
{
	for(unsigned i=0; i < VProduct.size(); i++) {
		for(int j=0; j < TShopUnits::CountUnits; j++) {
			VProduct[i]->CountBalance[j] = 0;
		}
	}
}
//---------------------------------------------------------------------------
bool __fastcall TProduct::LoadRecordId(TMyFDQuery *FDQuery)
{
	UnicodeString *uProductDbData = new UnicodeString[CountProductFieldsTableDB - 2];
	if(LoadRecord(FDQuery, NameTableDB, ProductFieldsTableDB, uProductDbData, CountProductFieldsTableDB)) {
		id = uProductDbData[0].ToInt();
		IdGroup = uProductDbData[1].ToInt();
		Code = uProductDbData[2];
		Name = uProductDbData[3];
		Unit = uProductDbData[4];
		WholeUnit = uProductDbData[5].ToInt();
		PurchaseCash.SetMoney(uProductDbData[6].ToInt());
		PurchaseCash.SetCent(uProductDbData[7].ToInt());
		SellingPrice.SetMoney(uProductDbData[8].ToInt());
		SellingPrice.SetCent(uProductDbData[9].ToInt());
		DollarPrice.SetMoney(uProductDbData[10].ToInt());
		DollarPrice.SetCent(uProductDbData[11].ToInt());
		WholePrice.SetMoney(uProductDbData[12].ToInt());
		WholePrice.SetCent(uProductDbData[13].ToInt());
		Description = uProductDbData[14];

		// Calc & fill additional fields
		GroupProd = TGroupProduct::GetGroupProdById(IdGroup);

		if(GroupProd == NULL) {
			Application->MessageBox(uProdLostGroupProd[iLang], uCaptionError[iLang], MB_OK);
		}
		delete[] uProductDbData;
		return true;
	} else {
		delete[] uProductDbData;
		return false;
	}
}
//---------------------------------------------------------------------------



