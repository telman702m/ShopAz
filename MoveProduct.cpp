//---------------------------------------------------------------------------
#pragma hdrstop

#include "MoveProduct.h"
#include "Provisioner.h"
#include "Shop.h"
#include "Synchronize.h"
#include "UnitProgressBar.h"
#include "UnitProductList.h"
#include "MyListView.h"
#include "TUtills.h"
#include <time.h>
#include "UnitBuyerList.h"
#include "UnitProvisionerList.h"

#pragma package(smart_init)

const wchar_t *uIncorrectMoveType[2] = {
	L"Некорректный тип операции!\nУдалить из Базы Данных?",
	L"Yanlış əməliyyət növü!\nMəlumat Bazadan silinsin?"
};

UnicodeString ProgressLoadMoveProduct[2] = {
	L"Загрузка данных о \"Операциях\" с сервера",
	L"Serverdən \"Əməliyyətlar\" haqqında məlumatın yüklənməsi"
};

const wchar_t *LostTarget[2] = {
	L"Не указан объект (магазин, склад) назначения товаров!",
	L"Malların ünvanı (mağaza, ambar) qeyd olunmayıb!"
};
const wchar_t *LostProduct[2] = {
	L"Нет выбранных товаров!",
	L"Mallar seçilmayıb!"
};

const double MIN_DATE_TIME = 25570.;    // 1970-01-02 00:00:00

/*const int CountFieldsMoveProduct = 14;
wchar_t *MoveProductDbFields[CountFieldsMoveProduct][2] =
	{{L"id",              L" Int(11) Not Null Auto_increment, "},
	 {L"TypeOperation",   L" Smallint(1), "},                         // Discount Money
	 {L"idSource",        L" Int(11), "},                             // Discount Money
	 {L"idSourcePerson",  L" Int(11), "},                             // Discount Money
	 {L"idTarget",        L" Int(11), "},                             // Discount Money
	 {L"idTargetPerson",  L" Int(11), "},                             // Discount Money
	 {L"DateTime",        L" TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, "}, // Sale Time
	 {L"Discount1",       L" Int(8), "},                             // Discount Money
	 {L"Discount2",       L" Int(2), "},                             // Discount Cent
	 {L"ActualPayment1",  L" Int(8), "},                             // ActualPayment Money
	 {L"ActualPayment2",  L" Int(2), "},                             // ActualPayment Cent
	 {L"Description",     L" Varchar(368), "},                       // Description
	 {L"Deleted",		  L" Smallint(1) "},
	 {L"LastUpdate",	  L" TIMESTAMP CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, "}
	}; */

vector <TMoveProduct*> TMoveProduct::VMoveProduct;
int TMoveProduct::LastIdDb = 0;

const wchar_t *TMoveProduct::NameTableDB;
TDescFields **TMoveProduct::MoveFieldsTableDB = NULL;
int TMoveProduct::CountMoveFieldsTableDB = 0;

//---------------------------------------------------------------------------
__fastcall TMoveProduct::TMoveProduct(void) : TBaseData()
{
/*	VBaseData = new vector<TBaseData*>;

	for (size_t i = 0; i < VMoveProduct.size(); ++i) {
		TMoveProduct *pMoveProduct = VMoveProduct[i];
		vAliasBaseData.push_back(pMoveProduct);
	}
	VBaseData = &vAliasBaseData;


	for (auto ptr : VMoveProduct)
		VBaseData->push_back(static_cast<TBaseData*>(ptr));
*/

	VBaseData = (vector <TBaseData*> *)&VMoveProduct;
	Clear();

//	vAliasBaseData = *((vector <TBaseData*>*)&VMoveProduct);
}
//---------------------------------------------------------------------------
bool TMoveProduct::GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB)
{
	NameTableDB = _NameTableDB;
	return GetFieldsFromDB(FDQuery, NameTableDB, MoveFieldsTableDB, CountMoveFieldsTableDB);
}
//---------------------------------------------------------------------------
void __fastcall TMoveProduct::Clear(void)
{
	MoveType = TMoveType::MOV_UNKNOW;
	idSource = -1;
	idSourcePerson = -1;
	idTarget = -1;
	idTargetPerson = -1;
	DateTime = MIN_DATE_TIME;
	Discount = 0;
	ActualPayment = 0;
	Debt = 0;
	Description = L"";
//    bDeleted = false;

	SourceUnit = NULL;
	SourcePerson = NULL;
	TargetUnit = NULL;
	TargetPerson = NULL;
	TotalCostPrice = 0;
	TotalPayment = 0;
	TotalPrice = 0;
	dPercent = 0.;

	DeleteVectorSelectProduct();
}
//---------------------------------------------------------------------------
__fastcall TMoveProduct::~TMoveProduct(void)
{
	DeleteVectorSelectProduct();
//	ShowVectorMoveProduct();
}
//---------------------------------------------------------------------------
void __fastcall TMoveProduct::DeleteVectorSelectProduct(void)
{
	for(unsigned i=0; i < VSelectedProd.size(); i++) {
		if(VSelectedProd[i] != NULL) {
			delete VSelectedProd[i];
			VSelectedProd[i] = NULL;
		}
	}
	VSelectedProd.clear();
}
//---------------------------------------------------------------------------
__fastcall TMoveProduct::TMoveProduct(const TMoveProduct &MoveProduct) : TBaseData(MoveProduct)
{
	MoveType = MoveProduct.MoveType;
	idSource = MoveProduct.idSource;
	idSourcePerson = MoveProduct.idSourcePerson;
	idTarget = MoveProduct.idTarget;
	idTargetPerson = MoveProduct.idTargetPerson;
	DateTime = MoveProduct.DateTime;
	Discount = MoveProduct.Discount;
	ActualPayment = MoveProduct.ActualPayment;
	Debt = MoveProduct.Debt;
	Description = MoveProduct.Description;

	SourceUnit = MoveProduct.SourceUnit;
	SourcePerson = MoveProduct.SourcePerson;
	TargetUnit = MoveProduct.TargetUnit;
	TargetPerson = MoveProduct.TargetPerson;
	TotalCostPrice = MoveProduct.TotalCostPrice;
	TotalPayment = MoveProduct.TotalPayment;
	TotalPrice = MoveProduct.TotalPrice;
	dPercent = MoveProduct.dPercent;

	DeleteVectorSelectProduct();
	TSelectProduct *TmpSelectProduct;
	for(unsigned i=0; i < MoveProduct.VSelectedProd.size(); i++) {
		TmpSelectProduct = new TSelectProduct;
		*TmpSelectProduct = *(MoveProduct.VSelectedProd[i]);
		VSelectedProd.push_back(TmpSelectProduct);
	}
}
//---------------------------------------------------------------------------
const TMoveProduct& __fastcall TMoveProduct::operator=(const TMoveProduct &MoveProduct)
{
	if(this == &MoveProduct) {
		return *this;
	}
	TBaseData::operator=(MoveProduct);
	MoveType = MoveProduct.MoveType;
	idSource = MoveProduct.idSource;
	idSourcePerson = MoveProduct.idSourcePerson;
	idTarget = MoveProduct.idTarget;
	idTargetPerson = MoveProduct.idTargetPerson;
	DateTime = MoveProduct.DateTime;
	Discount = MoveProduct.Discount;
	ActualPayment = MoveProduct.ActualPayment;
	Debt = MoveProduct.Debt;
	Description = MoveProduct.Description;

	SourceUnit = MoveProduct.SourceUnit;
	SourcePerson = MoveProduct.SourcePerson;
	TargetUnit = MoveProduct.TargetUnit;
	TargetPerson = MoveProduct.TargetPerson;
	TotalCostPrice = MoveProduct.TotalCostPrice;
	TotalPayment = MoveProduct.TotalPayment;
	TotalPrice = MoveProduct.TotalPrice;
	dPercent = MoveProduct.dPercent;

	DeleteVectorSelectProduct();
	TSelectProduct *TmpSelectProduct;
	for(unsigned i=0; i < MoveProduct.VSelectedProd.size(); i++) {
		TmpSelectProduct = new TSelectProduct;
		*TmpSelectProduct = *(MoveProduct.VSelectedProd[i]);
		VSelectedProd.push_back(TmpSelectProduct);
	}

	return *this;
}

//---------------------------------------------------------------------------
void __fastcall TMoveProduct::InsertAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uMoveDbData[] = {
		L"",
		MoveType,
		idSource,
		idSourcePerson,
		idTarget,
		idTargetPerson,
		DateTime.FormatString(L"yyyy-mm-dd hh:mm:ss"),
		Discount.GetMoney(),
		Discount.GetCent(),
		ActualPayment.GetMoney(),
		ActualPayment.GetCent(),
		Description,
	};

	TFieldsValues FieldsValues[] = {
		{MoveFieldsTableDB[1]->Field, 	uMoveDbData[1].w_str()},
		{MoveFieldsTableDB[2]->Field,	uMoveDbData[2].w_str()},
		{MoveFieldsTableDB[3]->Field,	uMoveDbData[3].w_str()},
		{MoveFieldsTableDB[4]->Field,	uMoveDbData[4].w_str()},
		{MoveFieldsTableDB[5]->Field,	uMoveDbData[5].w_str()},
		{MoveFieldsTableDB[6]->Field, 	uMoveDbData[6].w_str()},
		{MoveFieldsTableDB[7]->Field, 	uMoveDbData[7].w_str()},
		{MoveFieldsTableDB[8]->Field, 	uMoveDbData[8].w_str()},
		{MoveFieldsTableDB[9]->Field, 	uMoveDbData[9].w_str()},
		{MoveFieldsTableDB[10]->Field, 	uMoveDbData[10].w_str()},
		{MoveFieldsTableDB[11]->Field, 	uMoveDbData[11].w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	ExecSQL(FDQuery, FieldsValues, Count, NameTableDB, MoveFieldsTableDB[0]->Field, TabDB::TB_MOVEP);


	for(unsigned i=0; i < VSelectedProd.size(); i++) {
		VSelectedProd[i]->idMove = id;
		VSelectedProd[i]->InsertAtObjectToDb(FDQuery);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMoveProduct::SaveAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uMoveDbData[] = {
		L"",
		MoveType,
		idSource,
		idSourcePerson,
		idTarget,
		idTargetPerson,
		DateTime.FormatString(L"yyyy-mm-dd hh:mm:ss"),
		Discount.GetMoney(),
		Discount.GetCent(),
		ActualPayment.GetMoney(),
		ActualPayment.GetCent(),
		Description,
	};

	TFieldsValues FieldsValues[] = {
		{MoveFieldsTableDB[1]->Field, 	uMoveDbData[1].w_str()},
		{MoveFieldsTableDB[2]->Field,	uMoveDbData[2].w_str()},
		{MoveFieldsTableDB[3]->Field,	uMoveDbData[3].w_str()},
		{MoveFieldsTableDB[4]->Field,	uMoveDbData[4].w_str()},
		{MoveFieldsTableDB[5]->Field,	uMoveDbData[5].w_str()},
		{MoveFieldsTableDB[6]->Field, 	uMoveDbData[6].w_str()},
		{MoveFieldsTableDB[7]->Field, 	uMoveDbData[7].w_str()},
		{MoveFieldsTableDB[8]->Field, 	uMoveDbData[8].w_str()},
		{MoveFieldsTableDB[9]->Field, 	uMoveDbData[9].w_str()},
		{MoveFieldsTableDB[10]->Field, 	uMoveDbData[10].w_str()},
		{MoveFieldsTableDB[11]->Field, 	uMoveDbData[11].w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);


	UnicodeString uQuery = FormationUpdateString(NameTableDB, FieldsValues, Count);
	ExecSQL(FDQuery, uQuery, NameTableDB, TabDB::TB_MOVEP, TRecordType::RT_UPDATE, LOGS::LG_UPDATE);

//	ShowVectorMoveProduct();

	for(unsigned i=0; i < VSelectedProd.size(); i++) {
		VSelectedProd[i]->idMove = id;
		VSelectedProd[i]->InsertAtObjectToDb(FDQuery);
	}

//	ShowVectorMoveProduct();
}

//---------------------------------------------------------------------------
void __fastcall TMoveProduct::DeleteObjectFromDb(TMyFDQuery *FDQuery)
{
	for(unsigned i=0; i < VSelectedProd.size(); i++) {
		VSelectedProd[i]->DeleteObjectFromDb(FDQuery);
	}
//	VSelectedProd.clear();       // clear selected product vector in Sale

	UnicodeString uQuery = FormationDeleteString(NameTableDB, MoveFieldsTableDB[12]->Field);
	ExecSQL(FDQuery, uQuery, NameTableDB, TabDB::TB_MOVEP, TRecordType::RT_DELETE, LOGS::LG_DELETE);
}
//---------------------------------------------------------------------------
bool __fastcall TMoveProduct::SaveDataToFile(char *FileNmae)
{
	FILE *fs = fopen(FileNmae, "wb");
	if(fs == NULL) {
		return false;
	}
	fseek(fs, 0, SEEK_SET);
	fwprintf(fs, L"%lc", ucs2);

	fwprintf(fs, L"'%s'\n", TDateTime::CurrentDate().FormatString(L"dd.mm.yyyy").w_str());

	for(unsigned i=0; i < VMoveProduct.size(); i++) {
		fwprintf(fs, L"'%d'\t'%d'\t'%d'\t'%d'\t'%d'\t'%d'\t'%s'\t'%d'\t'%d'\t'%d'\t'%d'\t'%s'\t'%d'\n",
					 VMoveProduct[i]->id,
					 VMoveProduct[i]->MoveType,
					 VMoveProduct[i]->idSource,
					 VMoveProduct[i]->idSourcePerson,
					 VMoveProduct[i]->idTarget,
					 VMoveProduct[i]->idTargetPerson,
					 VMoveProduct[i]->DateTime.FormatString(L"dd.mm.yyyy hh:nn:ss").w_str(),
					 VMoveProduct[i]->Discount.GetMoney(),
					 VMoveProduct[i]->Discount.GetCent(),
					 VMoveProduct[i]->ActualPayment.GetMoney(),
					 VMoveProduct[i]->ActualPayment.GetCent(),
					 TUtills::ReplaceSymbol(TUtills::ReplaceSymbol(VMoveProduct[i]->Description.w_str(), L'\r', wchar_t(27)), L'\n', wchar_t(28)),
					 VMoveProduct[i]->bDeleted);
	}

	fclose(fs);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TMoveProduct::LoadDataFromFile(char *FileName)
{
	if(!LoadFileToWBuffer(FileName)) {
		return false;
	}

	UnicodeString uTmp;
//	int counter = 0, CountDelete = 0;
	int CountParseFields = CountMoveFieldsTableDB - 1;

	while(Offset < FileSize) {

		Offset += TUtills::ParseWstring(WFileBuffer + Offset, wpws, CountParseFields, FileSize - Offset);
		if(Offset == 0) {
			delete WFileBuffer;
			return false;
		}

		TMoveProduct *TmpMoveProduct = new TMoveProduct();

		uTmp = wpws[0];
		TmpMoveProduct->id = uTmp.ToInt();
		uTmp = wpws[1];
		TmpMoveProduct->MoveType = TMoveType(uTmp.ToInt());
		uTmp = wpws[2];
		TmpMoveProduct->idSource = uTmp.ToInt();
		uTmp = wpws[3];
		TmpMoveProduct->idSourcePerson = uTmp.ToInt();
		uTmp = wpws[4];
		TmpMoveProduct->idTarget = uTmp.ToInt();
		uTmp = wpws[5];
		TmpMoveProduct->idTargetPerson = uTmp.ToInt();
		uTmp = wpws[6];
		TmpMoveProduct->DateTime = StrToDateTime(uTmp, FSet);
		uTmp = wpws[7];
		TmpMoveProduct->Discount.SetMoney(uTmp.ToInt());
		uTmp = wpws[8];
		TmpMoveProduct->Discount.SetCent(uTmp.ToInt());
		uTmp = wpws[9];
		TmpMoveProduct->ActualPayment.SetMoney(uTmp.ToInt());
		uTmp = wpws[10];
		TmpMoveProduct->ActualPayment.SetCent(uTmp.ToInt());
		uTmp = wpws[11];
		TmpMoveProduct->Description = TUtills::ReplaceSymbol(TUtills::ReplaceSymbol(uTmp.w_str(), wchar_t(27), L'\r'), wchar_t(28), L'\n');
		uTmp = wpws[12];
		TmpMoveProduct->bDeleted = uTmp.ToInt();

		// assign Units
		if(!TmpMoveProduct->AssignUnits()) {
			continue;
		}

		VMoveProduct.push_back(TmpMoveProduct);

//		counter++;
	}

	delete FileBuffer;
	FileBuffer = NULL;
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TMoveProduct::AssignUnits(void)
{
	TWorkers *Worker;

	switch(MoveType) {
		case TMoveType::MOV_SALE:
			SourceUnit = TShopUnits::GetUnitById(idSource);
			Worker = TWorkers::GetWorkerById(idSourcePerson);
			SourcePerson = Worker;
			Privilege = Worker->Privilege;

			TargetUnit = TShopUnits::Buyer;
			TargetPerson = TBuyer::GetBuyerById(idTargetPerson);
			if(TargetPerson == NULL) {
                TargetPerson = TBuyer::Unknow;
            }
			break;

		case TMoveType::MOV_OUT:
			SourceUnit = TShopUnits::GetUnitById(idSource);
			Worker = TWorkers::GetWorkerById(idSourcePerson);
			SourcePerson = Worker;
			Privilege = Worker->Privilege;

			TargetUnit = TShopUnits::GetUnitById(idTarget);
			TargetPerson = TBuyer::Empty;

			Privilege = TWorkers::GetWorkerById(idSourcePerson)->Privilege;
			break;

		case TMoveType::MOV_INC:
			TargetUnit = TShopUnits::GetUnitById(idTarget);
			Worker = TWorkers::GetWorkerById(idTargetPerson);
			TargetPerson = Worker;
			Privilege = Worker->Privilege;

			SourceUnit = TShopUnits::Provisioner;
			SourcePerson = TProvisioner::GetProvisionerById(idSourcePerson);
			break;

		case TMoveType::MOV_RET:
		case TMoveType::MOV_DEBT:
			TargetUnit = TShopUnits::GetUnitById(idTarget);
			Worker = TWorkers::GetWorkerById(idTargetPerson);
			TargetPerson = Worker;
			Privilege = Worker->Privilege;

			SourceUnit = TShopUnits::Buyer;
			SourcePerson = TBuyer::GetBuyerById(idSourcePerson);
			break;

		case TMoveType::MOV_EXP:
			TargetUnit = TShopUnits::Expenses;
			TargetPerson = TBuyer::Unknow;

			SourceUnit = TShopUnits::GetUnitById(idSource);
			Worker = TWorkers::GetWorkerById(idSourcePerson);
			SourcePerson = Worker;
			Privilege = Worker->Privilege;
			break;

		case TMoveType::MOV_DEBT_PROVIS:
			SourceUnit = TShopUnits::GetUnitById(idSource);
			Worker = TWorkers::GetWorkerById(idSourcePerson);
			SourcePerson = Worker;
			Privilege = Worker->Privilege;

			TargetUnit = TShopUnits::Provisioner;
			TargetPerson = TProvisioner::GetProvisionerById(idTargetPerson);
			if(TargetPerson == NULL) {
                TargetPerson = TProvisioner::Unknow;
            }
			break;

		default:
			return false;
	}

	return true;
}
//---------------------------------------------------------------------------
void __fastcall TMoveProduct::LoadFromDB(TMyFDQuery *FDQuery, bool bLoadAll)
{
	VMoveProduct.clear();

	if(!bLoadAll) {
		AnsiString aTmp = FormShop->FDConnection1->Params->Database + "_MoveProduct.txt";
		bLoadAll = !LoadDataFromFile(aTmp.c_str());
	}

	UnicodeString uFields;
	int CountFields = 13;

	for(int i=0; i < CountFields; i++) {
		uFields += MoveFieldsTableDB[i]->Field;
		if(i < CountFields - 1) {
			uFields += L",";
		}
	}

	UnicodeString uTmp = "Select ";
	uTmp += uFields;
	uTmp += " from ";
	uTmp += NameTableDB;
	uTmp += L" where DateTime >= '";
	uTmp += FormShop->ShopUnit->LoadDateData.FormatString("yyyy-mm-dd");

	if(bLoadAll) {
		uTmp += L"'";
	} else {
		uTmp += L"' and LastUpdate > '";
		uTmp += MaxUpdateDate.FormatString("yyyy-mm-dd") + L"'";
	}

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;
	int iDel;

	TimerSyncDisable();

	while(!bSuccess) {
		try {
			FormProgressBar->Show();
			FormProgressBar->Label1->Caption = ProgressLoadMoveProduct[iLang];
			FormProgressBar->Update();
			FormProgressBar->Label1->Left = (FormProgressBar->ClientWidth - FormProgressBar->Label1->Width)/2;
			FormProgressBar->ProgressBar1->Position = 0;
			FormProgressBar->Update();
			FDQuery->Open();
            FDQuery->FetchAll();
			FormProgressBar->ProgressBar1->Max = FDQuery->RecordCount;

			while (!FDQuery->Eof) {

				TMoveProduct *TmpMoveProduct = new TMoveProduct();

				// Load data from MySql Data Base
				TmpMoveProduct->id = FDQuery->FieldByName(MoveFieldsTableDB[0]->Field)->AsString.ToInt();
				TmpMoveProduct->MoveType = TMoveType(FDQuery->FieldByName(MoveFieldsTableDB[1]->Field)->AsString.ToInt());
				TmpMoveProduct->idSource = FDQuery->FieldByName(MoveFieldsTableDB[2]->Field)->AsString.ToInt();
				TmpMoveProduct->idSourcePerson = FDQuery->FieldByName(MoveFieldsTableDB[3]->Field)->AsString.ToInt();
				TmpMoveProduct->idTarget = FDQuery->FieldByName(MoveFieldsTableDB[4]->Field)->AsString.ToInt();
				TmpMoveProduct->idTargetPerson = FDQuery->FieldByName(MoveFieldsTableDB[5]->Field)->AsString.ToInt();
				TmpMoveProduct->DateTime = FDQuery->FieldByName(MoveFieldsTableDB[6]->Field)->AsDateTime;
				TmpMoveProduct->Discount.SetMoney(FDQuery->FieldByName(MoveFieldsTableDB[7]->Field)->AsString.ToInt());
				TmpMoveProduct->Discount.SetCent(FDQuery->FieldByName(MoveFieldsTableDB[8]->Field)->AsString.ToInt());
				TmpMoveProduct->ActualPayment.SetMoney(FDQuery->FieldByName(MoveFieldsTableDB[9]->Field)->AsString.ToInt());
				TmpMoveProduct->ActualPayment.SetCent(FDQuery->FieldByName(MoveFieldsTableDB[10]->Field)->AsString.ToInt());
				TmpMoveProduct->Description = FDQuery->FieldByName(MoveFieldsTableDB[11]->Field)->AsString;
				TmpMoveProduct->bDeleted = FDQuery->FieldByName(MoveFieldsTableDB[12]->Field)->AsString.ToInt();

				// assign Units
				if(!TmpMoveProduct->AssignUnits()) {
					FDQuery->Next();
					continue;
				}

				if(bLoadAll) {
					VMoveProduct.push_back(TmpMoveProduct);
				} else {
					int iIndex = TmpMoveProduct->GetArrayIndexById();

					if(TmpMoveProduct->bDeleted) {
//						if(iIndex != -1) {
//							VMoveProduct.erase(VMoveProduct.begin() + iIndex);
//						}
					} else {
						if(iIndex == -1) {
							int InsertIndex = TmpMoveProduct->GetArrayIndexById(true);
							VMoveProduct.insert(VMoveProduct.begin()+InsertIndex, TmpMoveProduct);
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
bool __fastcall TMoveProduct::IsContainId(int id)
{
	for(unsigned i=0; i < VMoveProduct.size(); i++) {
		if(VMoveProduct[i]->id == id) {
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------
bool __fastcall TMoveProduct::LoadRecordId(TMyFDQuery *FDQuery)
{
	UnicodeString *uMoveDbData = new UnicodeString[CountMoveFieldsTableDB - 2];
	if(LoadRecord(FDQuery, NameTableDB, MoveFieldsTableDB, uMoveDbData, CountMoveFieldsTableDB)) {
		id = uMoveDbData[0].ToInt();
		MoveType = TMoveType(uMoveDbData[1].ToInt());
		idSource = uMoveDbData[2].ToInt();
		idSourcePerson = uMoveDbData[3].ToInt();
		idTarget = uMoveDbData[4].ToInt();
		idTargetPerson = uMoveDbData[5].ToInt();
		DateTime = uMoveDbData[6];
		Discount.SetMoney(uMoveDbData[7].ToInt());
		Discount.SetCent(uMoveDbData[8].ToInt());
		ActualPayment.SetMoney(uMoveDbData[9].ToInt());
		ActualPayment.SetCent(uMoveDbData[10].ToInt());
		Description = uMoveDbData[8];

		if(AssignUnits()) {
			CalcTotalPrice();

//			CalcUnitsBalance();
//			CalcDebts();
			delete[] uMoveDbData;
			return true;
		} else {
			delete[] uMoveDbData;
			return false;
		}

	} else {
		return false;
	}
}
//---------------------------------------------------------------------------
int __fastcall TMoveProduct::GetBalanceMult(void)
{
	switch(MoveType) {
		case TMoveType::MOV_SALE:
			return -1;
		case TMoveType::MOV_OUT:
			if(SourceUnit == FormShop->ShopUnit) {
				return -1;
			} else {
				return 1;
			}
		case TMoveType::MOV_RET:
		case TMoveType::MOV_INC:
			return 1;
		default:
			return 0;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMoveProduct::CalcTotalPrice(void)
{
	TotalCostPrice = 0;
	TotalPrice = 0;

	for(unsigned i=0; i < VSelectedProd.size(); i++) {
		if(MoveType == TMoveType::MOV_INC) {
			VSelectedProd[i]->TotalPrice = VSelectedProd[i]->TotalCostPrice;
		}
		TotalCostPrice += VSelectedProd[i]->TotalCostPrice;
		TotalPrice += VSelectedProd[i]->TotalPrice;
	}
//	if(MoveType == TMoveType::MOV_INC) {
//		TotalPrice = TotalCostPrice;
//	}

	switch(MoveType) {
		case TMoveType::MOV_DEBT:
		case TMoveType::MOV_EXP:
		case TMoveType::MOV_DEBT_PROVIS:
			dPercent = 0.;
			TotalPrice = 0;
			TotalPayment = 0;
			Debt = 0;
			break;

		default:
			dPercent = TotalPrice.GetPercent(Discount);
			TotalPayment = TotalPrice - Discount;
			Debt = TotalPayment - ActualPayment;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMoveProduct::CalcUnitsBalance(void)
{
	unsigned CountProduct = TProduct::VProduct.size();
	unsigned CountShop = TShopUnits::VShopUnits.size();

	for(unsigned i=0; i < CountProduct; i++) {
		for(unsigned j=0; j < CountShop; j++) {
			TProduct::VProduct[i]->CountBalance[j] = 0;
		}
	}

	unsigned CountMove = TMoveProduct::VMoveProduct.size();

	for(unsigned i=0; i < CountMove; i++) {
		TMoveProduct::VMoveProduct[i]->CalcObjectUnitsBalance();
	}

	FormBuyerList->bListUpdate = true;
	FormProvisionerList->bListUpdate = true;
}
//---------------------------------------------------------------------------
void __fastcall TMoveProduct::CalcObjectUnitsBalance(void)
{
	if(bDeleted) return;

	int iSource;
	int iTarget;

	switch(MoveType) {
		case TMoveType::MOV_SALE:
			iSource = TShopUnits::GetIndexUnitById(idSource);
			if(iSource != -1) {
				for(unsigned j=0; j < VSelectedProd.size(); j++) {
					VSelectedProd[j]->Product->CountBalance[iSource] -= VSelectedProd[j]->Count;
				}
			}
			break;
		case TMoveType::MOV_OUT:
			iSource = TShopUnits::GetIndexUnitById(idSource);
			iTarget = TShopUnits::GetIndexUnitById(idTarget);
			if(iSource != -1 && iTarget != -1) {
				for(unsigned j=0; j < VSelectedProd.size(); j++) {
					VSelectedProd[j]->Product->CountBalance[iSource] -= VSelectedProd[j]->Count;
					VSelectedProd[j]->Product->CountBalance[iTarget] += VSelectedProd[j]->Count;
				}
			}
			break;
		case TMoveType::MOV_INC:
			iTarget = TShopUnits::GetIndexUnitById(idTarget);
			if(iTarget != -1) {
				for(unsigned j=0; j < VSelectedProd.size(); j++) {
					VSelectedProd[j]->Product->CountBalance[iTarget] += VSelectedProd[j]->Count;
				}
			}
			break;
		case TMoveType::MOV_RET:
			iTarget = TShopUnits::GetIndexUnitById(idTarget);
			if(iTarget != -1) {
				for(unsigned j=0; j < VSelectedProd.size(); j++) {
					VSelectedProd[j]->Product->CountBalance[iTarget] += VSelectedProd[j]->Count;
				}
			}
			break;
		default:
			break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMoveProduct::CorrectUnitsBalance(int Index, int iMult)
{
	int iSource;
	int iTarget;

	switch(MoveType) {
		case TMoveType::MOV_SALE:
			iSource = TShopUnits::GetIndexUnitById(idSource);
			if(iSource != -1) {
				VSelectedProd[Index]->Product->CountBalance[iSource] -= VSelectedProd[Index]->Count * iMult;
			}
			break;
		case TMoveType::MOV_OUT:
			iSource = TShopUnits::GetIndexUnitById(idSource);
			iTarget = TShopUnits::GetIndexUnitById(idTarget);
			if(iSource != -1 && iTarget != -1) {
				VSelectedProd[Index]->Product->CountBalance[iSource] -= VSelectedProd[Index]->Count * iMult;
				VSelectedProd[Index]->Product->CountBalance[iTarget] += VSelectedProd[Index]->Count * iMult;
			}
			break;
		case TMoveType::MOV_INC:
			iTarget = TShopUnits::GetIndexUnitById(idTarget);
			if(iTarget != -1) {
				VSelectedProd[Index]->Product->CountBalance[iTarget] += VSelectedProd[Index]->Count * iMult;
			}
			break;
		case TMoveType::MOV_RET:
			iTarget = TShopUnits::GetIndexUnitById(idTarget);
			if(iTarget != -1) {
				VSelectedProd[Index]->Product->CountBalance[iTarget] += VSelectedProd[Index]->Count * iMult;
			}
			break;
		default:
			break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMoveProduct::CalcDebts(void)
{
	unsigned CountBuyer = TBuyer::VBuyers.size();
	for(unsigned i=0; i < CountBuyer; i++) {
		TBuyer::VBuyers[i]->SetPricesZero();
	}

	unsigned CountProvisioner = TProvisioner::VProvisioners.size();
	for(unsigned i=0; i < CountProvisioner; i++) {
		TProvisioner::VProvisioners[i]->SetPricesZero();
	}

	unsigned CountShop = TShopUnits::VShopUnits.size();
	for(unsigned i=0; i < CountShop; i++) {
		TShopUnits::VShopUnits[i]->SetPricesZero();
	}

	unsigned CountMove = TMoveProduct::VMoveProduct.size();
	for(unsigned i=0; i < CountMove; i++) {
		TMoveProduct::VMoveProduct[i]->CalcObjectDebts();
	}

	FormBuyerList->bListUpdate = true;
	FormProvisionerList->bListUpdate = true;
}
//---------------------------------------------------------------------------
void __fastcall TMoveProduct::CalcObjectDebts(void)
{
	if(bDeleted) return;

	int iSource;
	int iTarget;
	TBuyer *Buyer;
	TShopUnits *ShopUnit;
	TProvisioner *Provisioner;

	switch(MoveType) {
		case TMoveType::MOV_SALE:
			// Buyer balance
			Buyer = TBuyer::GetBuyerById(idTargetPerson);
			if(Buyer != NULL) {
				Buyer->TotalShoped += TotalPrice;
				Buyer->TotalDiscount += Discount;
				Buyer->TotalDebt += Debt;
			}
			// ShopUnit balance
			ShopUnit = TShopUnits::GetUnitById(idSource);
			if(ShopUnit != NULL) {
				ShopUnit->TotalShoped += TotalPrice;
				ShopUnit->TotalDiscount += Discount;
				ShopUnit->TotalDebt -= Debt;
			}
			break;
		case TMoveType::MOV_RET:
			// Buyer balance
			Buyer = TBuyer::GetBuyerById(idSourcePerson);
			if(Buyer != NULL) {
				Buyer->TotalReturn += TotalPrice;
				Buyer->TotalDiscount -= Discount;
				Buyer->TotalDebt -= Debt;
			}
			// ShopUnit balance
			ShopUnit = TShopUnits::GetUnitById(idTarget);
			if(ShopUnit != NULL) {
				ShopUnit->TotalReturn += TotalPrice;
				ShopUnit->TotalDiscount -= Discount;
				ShopUnit->TotalDebt += Debt;
			}
			break;
		case TMoveType::MOV_INC:
			// Provisioner balance
			Provisioner = TProvisioner::GetProvisionerById(idSourcePerson);
			if(Provisioner != NULL) {
				Provisioner->TotalShoped += TotalPrice;
				Provisioner->TotalDiscount += Discount;
				Provisioner->TotalDebt -= Debt;
			}
			// ShopUnit balance
			ShopUnit = TShopUnits::GetUnitById(idTarget);
			if(ShopUnit != NULL) {
				ShopUnit->TotalIncoming += TotalPrice;
//				ShopUnit->TotalDiscount += Discount;
//				ShopUnit->TotalDebt += Debt;
			}
			break;
		case TMoveType::MOV_OUT:
			// ShopUnit balance
			ShopUnit = TShopUnits::GetUnitById(idSource);
			if(ShopUnit != NULL) {
				ShopUnit->TotalMoved += TotalPrice;
//				ShopUnit->TotalDiscount += Discount;
//				ShopUnit->TotalDebt -= Debt;
			}
			// ShopUnit balance
			ShopUnit = TShopUnits::GetUnitById(idTarget);
			if(ShopUnit != NULL) {
				ShopUnit->TotalIncoming += TotalPrice;
//				ShopUnit->TotalDiscount += Discount;
//				ShopUnit->TotalDebt += Debt;
			}
			break;
		case TMoveType::MOV_DEBT:
			// Buyer balance
			Buyer = TBuyer::GetBuyerById(idSourcePerson);
			if(Buyer != NULL) {
				Buyer->TotalDebt -= ActualPayment;
			}
			// ShopUnit balance
			ShopUnit = TShopUnits::GetUnitById(idTarget);
			if(ShopUnit != NULL) {
				ShopUnit->TotalDebt += ActualPayment;
			}
			break;
		case TMoveType::MOV_EXP:
			// ShopUnit balance
			ShopUnit = TShopUnits::GetUnitById(idSource);
			if(ShopUnit != NULL) {
				ShopUnit->TotalExpenses += ActualPayment;
			}
			break;
		case TMoveType::MOV_DEBT_PROVIS:
			// Provisioner balance
			Provisioner = TProvisioner::GetProvisionerById(idTargetPerson);
			if(Provisioner != NULL) {
				Provisioner->TotalDebt += ActualPayment;
			}
			// ShopUnit balance
			ShopUnit = TShopUnits::GetUnitById(idSource);
			if(ShopUnit != NULL) {
				ShopUnit->TotalDebt -= ActualPayment;
			}
			break;
		default:
			break;
	}
}

//---------------------------------------------------------------------------
bool __fastcall TMoveProduct::IsContainProduct(UnicodeString uProdName)
{
	for(unsigned i=0; i < VSelectedProd.size(); i++) {
		if(VSelectedProd[i]->Product->Name.UpperCase().Pos(uProdName) > 0) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------
int __fastcall TMoveProduct::GetIndexInVSelectById(int id)
{
	for(unsigned i=0; i < VSelectedProd.size(); i++) {
		if(VSelectedProd[i]->id == id) {
			return i;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------
bool __fastcall TMoveProduct::CheckCorrect(void)
{
	if(MoveType == TMoveType::MOV_OUT && idTarget == -1) {
		ShowMessage(LostTarget[iLang]);
		return false;
	}

	if(VSelectedProd.size() == 0) {
		ShowMessage(LostProduct[iLang]);
		return false;
	}

    return true;
}
//---------------------------------------------------------------------------
void __fastcall TMoveProduct::ShowVectorMoveProduct(void)
{
	UnicodeString uTmp = L"", uMess = L"Vector VSelectedProd\n";

	for (size_t i = 0; i < VSelectedProd.size(); i++) {
		uMess += uTmp.sprintf(L"Price=%s  Count=%s\n",
								VSelectedProd[i]->Price.StringFormat().w_str(),
								VSelectedProd[i]->Count.StringFormat().w_str());
	}
	ShowMessage(uMess);
//	uMess += L"!";
}
//---------------------------------------------------------------------------


