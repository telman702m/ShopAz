//---------------------------------------------------------------------------
#pragma hdrstop

#include "Synchronize.h"
#include "Shop.h"
#include "GroupProduct.h"
#include "Product.h"
#include "Buyer.h"
#include "Provisioner.h"
#include "MoveProduct.h"
#include "UnitGroupList.h"
#include "UnitProductList.h"
#include "UnitBuyerList.h"
#include "UnitProvisionerList.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

const wchar_t *uSyncLostConnectionSelect[2] = {
	L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: Select from Synchronize!\n Проверьте Интернет соединение.\n\n Повторить попытку?",
	L"MySql: Select from Synchronize! Əməliyyət zamanı Məlumat Bazaynan əlagə kəsilib \n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};
const wchar_t *uSyncLostConnectionSelectSync[2] = {
	L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: Select MAX(id) from Synchronize!\n Проверьте Интернет соединение.\n\n Повторить попытку?",
	L"MySql: Select MAX(id) from Synchronize! Əməliyyət zamanı Məlumat Bazaynan əlagə kəsilib \n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};

const wchar_t *uSyncLostConnectionInsert[2] = {
	L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: Insert into Synchronize!\n Проверьте Интернет соединение.\n\n Повторить попытку?",
	L"MySql: Insert into Synchronize! Əməliyyət zamanı Məlumat Bazaynan əlagə kəsilib \n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};
const wchar_t *uSyncLostConnectionDelete[2] = {
	L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: Delete Synchronize!\n Проверьте Интернет соединение.\n\n Повторить попытку?",
	L"MySql: Delete Synchronize! Əməliyyət zamanı Məlumat Bazaynan əlagə kəsilib \n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};
const wchar_t *uSyncLostConnectionCreate[2] = {
	L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: Create table Synchronize!\n Проверьте Интернет соединение.\n\n Повторить попытку?",
	L"MySql: Create table Synchronize! Əməliyyət zamanı Məlumat Bazaynan əlagə kəsilib \n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};

UnicodeString TSynchronize::SynchronizeDbFields[CountFieldsSynchronize][2] =
   {{L"id",              L" Int(11) Not Null Auto_increment, "},
	{L"idShop",       	 L" TINYINT(4) DEFAULT NULL, "},
	{L"idWorker",        L" TINYINT(4) DEFAULT NULL, "},
	{L"TableIndex",      L" TINYINT(4) DEFAULT NULL, "},
	{L"idRecord",        L" Int(11) DEFAULT NULL, "},
	{L"RecordType",      L" TINYINT(4) DEFAULT NULL, "},
	{L"RecDateTime", 	 L" TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, "}};

int TSynchronize::LastId = 0;
bool TSynchronize::bChangedAccess = false;
vector <TSynchronize*> TSynchronize::VSynchronize;

TBuyer* TSynchronize::TmpBuyer = new TBuyer();
TProvisioner* TSynchronize::TmpProvisioner = new TProvisioner();
TGroupProduct* TSynchronize::TmpGroupProd = new TGroupProduct();
TProduct* TSynchronize::TmpProduct = NULL;// = new TProduct();
TSelectProduct* TSynchronize::TmpSelectProduct = NULL; //new TSelectProduct();
TMoveProduct* TSynchronize::TmpMoveProduct = NULL; //new TMoveProduct();

//UnicodeString TSynchronize::TablesDBName[5] =
//   {L"GroupProducts", L"Products", L"Buyers", L"Provisioners", L"MoveProduct"};


//---------------------------------------------------------------------------
__fastcall TSynchronize::TSynchronize(void)
{
//	Clear();
}
//---------------------------------------------------------------------------
void __fastcall TSynchronize::InsertToDb(TMyFDQuery *FDQuery, TabDB TableIndex, int idRecord, TRecordType RecType)
{
	InsertToDb(FDQuery, FormShop->ShopUnit->id, TableIndex, idRecord, RecType);
}
//---------------------------------------------------------------------------
void __fastcall TSynchronize::InsertToDb(TMyFDQuery *FDQuery, int idShopUnit, TabDB TableIndex, int idRecord, TRecordType RecType)
{
	TBaseData::TimerSyncDisable();

	//  Delete last records
	TDateTime LimitDateTime = TDateTime::CurrentDateTime();
	LimitDateTime -= 1./24.;

	UnicodeString uTmp3;
	uTmp3.sprintf(L"delete from Synchronize where RecDateTime < '%s'", LimitDateTime.FormatString(L"yyyy-mm-dd hh:mm:ss").w_str());

	FDQuery->SQL->Text = uTmp3;

	bool bSuccess3 = false;

	while(!bSuccess3) {
		try {
			FDQuery->Execute();
			bSuccess3 = true;

	   } catch (...) {
			if(Application->MessageBox(uSyncLostConnectionDelete[iLang], uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess3 = false;
	   }
	}


	//  Insert new record
	UnicodeString uTmp1 = L", ", uTmp2 = L"', '";
	UnicodeString uTmp = L"Insert Into Synchronize (";

	uTmp += SynchronizeDbFields[1][0] + uTmp1;
	uTmp += SynchronizeDbFields[2][0] + uTmp1;
	uTmp += SynchronizeDbFields[3][0] + uTmp1;
	uTmp += SynchronizeDbFields[4][0] + uTmp1;
	uTmp += SynchronizeDbFields[5][0] + uTmp1;
	uTmp += SynchronizeDbFields[6][0] + L") Values ('";

	uTmp += idShopUnit;
	uTmp += uTmp2;
	uTmp += FormShop->Worker->id;
	uTmp += uTmp2;
	uTmp += TableIndex;
	uTmp += uTmp2;
	uTmp += idRecord;
	uTmp += uTmp2;
	uTmp += RecType;
	uTmp += uTmp2;
	uTmp += TDateTime::CurrentDateTime().FormatString(L"yyyy-mm-dd hh:mm:ss");
	uTmp += L"')";

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;

	while(!bSuccess) {
		try {
			FDQuery->Execute();
			bSuccess = true;

	   } catch (...) {
			if(Application->MessageBox(uSyncLostConnectionInsert[iLang], uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}

	TBaseData::TimerSyncRestore();
}

//---------------------------------------------------------------------------
void __fastcall TSynchronize::InitLastIdTables(TMyFDQuery *FDQuery)
{
	TmpProduct = new TProduct();
	TmpSelectProduct = new TSelectProduct();
	TmpMoveProduct = new TMoveProduct();

	UnicodeString uTmp = L"Select MAX(id) as MAX_ID from Synchronize";
	FDQuery->SQL->Text = uTmp;


	bool bSuccess = false;

	while(!bSuccess) {
		try {
			FDQuery->Open();
			uTmp = FDQuery->FieldByName(L"MAX_ID")->AsString;
			if(uTmp != L"") {
				LastId = uTmp.ToInt();
			} else {
                LastId = 0;
			}
            FDQuery->Close();

			bSuccess = true;
	   } catch (...) {
			if(Application->MessageBox(L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: Select MAX(id) from Synchronize!\n Проверьте Интернет соединение.\n\n Повторить попытку?", L"Предупреждение", MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}
}

//---------------------------------------------------------------------------
void __fastcall TSynchronize::LoadFromDB(TMyFDQuery *FDQuery, int idShop, int idWorker)
{
	UnicodeString uTmp;
	FDQuery->SQL->Text = uTmp.sprintf(L"Select * from Synchronize where id > %d and idWorker <> %d", LastId, idWorker);

	VSynchronize.clear();
	bool bSuccess = false;

	TBaseData::TimerSyncDisable();

	while(!bSuccess) {
		try {
			FDQuery->Open();

			while(!FDQuery->Eof) {
				TSynchronize *TmpSynchronize = new TSynchronize();

				TmpSynchronize->id = FDQuery->FieldByName(SynchronizeDbFields[0][0])->AsString.ToInt();
				TmpSynchronize->idShop = FDQuery->FieldByName(SynchronizeDbFields[1][0])->AsString.ToInt();
				TmpSynchronize->idWorker = FDQuery->FieldByName(SynchronizeDbFields[2][0])->AsString.ToInt();
				TmpSynchronize->TableDB = TabDB(FDQuery->FieldByName(SynchronizeDbFields[3][0])->AsString.ToInt());
				TmpSynchronize->idRecord = FDQuery->FieldByName(SynchronizeDbFields[4][0])->AsString.ToInt();
				TmpSynchronize->RecordType = TRecordType(FDQuery->FieldByName(SynchronizeDbFields[5][0])->AsString.ToInt());
				TmpSynchronize->RecDateTime = FDQuery->FieldByName(SynchronizeDbFields[6][0])->AsString;

				if(TmpSynchronize->id > LastId) {
					LastId = TmpSynchronize->id;
				}

				if(!bChangedAccess) {
					VSynchronize.push_back(TmpSynchronize);
				} else {
					delete TmpSynchronize;
				}

				FDQuery->Next();

				if(FDQuery->Eof) {
					bChangedAccess = false;
				}
			}
			FDQuery->Close();

			bSuccess = true;
	   } catch (...) {
			if(Application->MessageBox(uSyncLostConnectionSelect[iLang], uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
			FDQuery->Close();
	   }
	}

	TBaseData::TimerSyncRestore();
}

//---------------------------------------------------------------------------
void __fastcall TSynchronize::ApplySinc(void)
{
	bool bRecalc = false;

	for(unsigned i=0; i < VSynchronize.size(); i++) {
		switch(VSynchronize[i]->TableDB) {
			case TabDB::TB_GROUP:
				if(TmpGroupProd->ApplyBaseSyncronize(FormShop->FDQuery1, VSynchronize[i], FormGroupList)) {
					TmpGroupProd = new TGroupProduct();
				}
				if(FormProductList->Showing) {
					FormProductList->LoadGroupsToComboFilter();
				}
				break;
			case TabDB::TB_PROD:
				if(TmpProduct->ApplyBaseSyncronize(FormShop->FDQuery1, VSynchronize[i], FormProductList)) {
					TmpProduct = new TProduct();
				}
				break;
			case TabDB::TB_BUYER:
				if(TmpBuyer->ApplyBaseSyncronize(FormShop->FDQuery1, VSynchronize[i], FormBuyerList)) {
					TmpBuyer = new TBuyer();
				}
				break;
			case TabDB::TB_PROVIS:
				if(TmpProvisioner->ApplyBaseSyncronize(FormShop->FDQuery1, VSynchronize[i], FormProvisionerList)) {
					TmpProvisioner = new TProvisioner();
				}
				break;
			case TabDB::TB_SELECTP:
				if(TmpSelectProduct->ApplyBaseSyncronize(FormShop->FDQuery1, VSynchronize[i], NULL)) {
					TmpSelectProduct = new TSelectProduct();
				}
				bRecalc = true;
				break;
			case TabDB::TB_MOVEP:
				if(TmpMoveProduct->ApplyBaseSyncronize(FormShop->FDQuery1, VSynchronize[i], FormProductList)) {
					TmpMoveProduct = new TMoveProduct();
				}
				bRecalc = true;
				break;
			default:
                break;
		}
	}

	if(bRecalc) {
		TMoveProduct::CalcUnitsBalance();
		TMoveProduct::CalcDebts();

		FormShop->MoveList->FillList();
	}
}

//---------------------------------------------------------------------------
