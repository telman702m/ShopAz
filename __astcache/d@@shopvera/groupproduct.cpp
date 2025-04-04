//---------------------------------------------------------------------------
#pragma hdrstop

#include "GroupProduct.h"
#include "UnitProductList.h"
#include "Shop.h"
#include "UnitGroupList.h"
#include "UnitProgressBar.h"
#include "BaseDataTemplates.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

UnicodeString ProgressLoadGroupProduct[2] = {
	L"Загрузка данных о \"Группе товаров\" с сервера",
	L"Serverdən \"Malların Qruplar\" haqqında məlumatın yüklənməsi"
};


const wchar_t *TGroupProduct::NameTableDB;
TDescFields **TGroupProduct::GroupProdFieldsTableDB = NULL;
int TGroupProduct::CountGroupProdFieldsTableDB = 0;

//---------------------------------------------------------------------------
__fastcall TGroupProduct::TGroupProduct(void) : TBaseData()
{
	Clear();
}
//---------------------------------------------------------------------------
bool TGroupProduct::GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB)
{
	NameTableDB = _NameTableDB;
	return GetFieldsFromDB(FDQuery, NameTableDB, GroupProdFieldsTableDB, CountGroupProdFieldsTableDB);
}
//---------------------------------------------------------------------------
void __fastcall TGroupProduct::Clear(void)
{
	GroupCode = L"";
	Name = L"";
	Description = L"";
	Enabled = false;
}
//---------------------------------------------------------------------------
__fastcall TGroupProduct::TGroupProduct(const TGroupProduct &GroupProduct) : TBaseData(GroupProduct)
{
	GroupCode = GroupProduct.GroupCode;
	Name = GroupProduct.Name;
	Description = GroupProduct.Description;
	Enabled = GroupProduct.Enabled;
}
//---------------------------------------------------------------------------
TGroupProduct& __fastcall TGroupProduct::operator=(const TGroupProduct &GroupProduct)
{
	TBaseData::operator = (GroupProduct);

	GroupCode = GroupProduct.GroupCode;
	Name = GroupProduct.Name;
	Description = GroupProduct.Description;
	Enabled = GroupProduct.Enabled;

	return *this;
}

//---------------------------------------------------------------------------
void __fastcall TGroupProduct::InsertAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uEnable = int(Enabled);

	TFieldsValues FieldsValues[] = {
		{GroupProdFieldsTableDB[1]->Field, 	GroupCode.w_str()},
		{GroupProdFieldsTableDB[2]->Field,	Name.w_str()},
		{GroupProdFieldsTableDB[3]->Field,	Description.w_str()},
		{GroupProdFieldsTableDB[4]->Field,	uEnable.w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	ExecSQL_Managed<TGroupProduct>(FDQuery, FieldsValues, Count, NameTableDB, GroupProdFieldsTableDB[0]->Field, TabDB::TB_GROUP);
}

//---------------------------------------------------------------------------
void __fastcall TGroupProduct::SaveAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uEnable = int(Enabled);

	TFieldsValues FieldsValues[] = {
		{GroupProdFieldsTableDB[1]->Field, 	GroupCode.w_str()},
		{GroupProdFieldsTableDB[2]->Field,	Name.w_str()},
		{GroupProdFieldsTableDB[3]->Field,	Description.w_str()},
		{GroupProdFieldsTableDB[4]->Field,	uEnable.w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	UnicodeString uQuery = FormationUpdateString(NameTableDB, FieldsValues, Count);
	ExecSQL_Managed<TGroupProduct>(FDQuery, uQuery, NameTableDB, TabDB::TB_GROUP, TRecordType::RT_UPDATE, LOGS::LG_UPDATE);
}

//---------------------------------------------------------------------------
void __fastcall TGroupProduct::DeleteObjectFromDb(TMyFDQuery *FDQuery)
{
	UnicodeString uQuery = FormationDeleteString(NameTableDB, GroupProdFieldsTableDB[5]->Field);
	ExecSQL_Managed<TGroupProduct>(FDQuery, uQuery, NameTableDB, TabDB::TB_GROUP, TRecordType::RT_DELETE, LOGS::LG_DELETE);
}

//---------------------------------------------------------------------------
TGroupProduct* __fastcall TGroupProduct::GetGroupProdById(int id)
{
	return TObjectManager<TGroupProduct>::FindById(id);
}
//---------------------------------------------------------------------------
TGroupProduct* __fastcall TGroupProduct::GetGroupProdByName(UnicodeString Name)
{
	unsigned Count = TObjectManager<TGroupProduct>::GetList().size();

	for(unsigned i=0; i < Count; i++) {
		if(TObjectManager<TGroupProduct>::GetList()[i]->Name == Name) {
			return TObjectManager<TGroupProduct>::GetList()[i];
		}
	}
	return NULL;
}

//---------------------------------------------------------------------------
void __fastcall TGroupProduct::LoadFromDB(TMyFDQuery *FDQuery)
{
	UnicodeString uTmp = "Select * from ";
	uTmp += NameTableDB;

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;

	TimerSyncDisable();

	while(!bSuccess) {
		try {
			FormProgressBar->Show();
			FormProgressBar->Label1->Caption = ProgressLoadGroupProduct[iLang];
			FormProgressBar->Update();
			FormProgressBar->Label1->Left = (FormProgressBar->ClientWidth - FormProgressBar->Label1->Width)/2;
			FormProgressBar->ProgressBar1->Position = 0;
			FormProgressBar->Update();
			FDQuery->Open();
            FDQuery->FetchAll();
			FormProgressBar->ProgressBar1->Max = FDQuery->RecordCount;

			while (!FDQuery->Eof)
			{
				TGroupProduct *TmpGroupProd = new TGroupProduct();

				TmpGroupProd->id = FDQuery->FieldByName(GroupProdFieldsTableDB[0]->Field)->AsString.ToInt();
				TmpGroupProd->GroupCode = FDQuery->FieldByName(GroupProdFieldsTableDB[1]->Field)->AsString;
				TmpGroupProd->Name = FDQuery->FieldByName(GroupProdFieldsTableDB[2]->Field)->AsString;
				TmpGroupProd->Description = FDQuery->FieldByName(GroupProdFieldsTableDB[3]->Field)->AsString;
				TmpGroupProd->Enabled = FDQuery->FieldByName(GroupProdFieldsTableDB[4]->Field)->AsString.ToInt();

				TObjectManager<TGroupProduct>::GetList().push_back(TmpGroupProd);
				FDQuery->Next();

				FormProgressBar->ProgressBar1->Position++;
				FormProgressBar->Update();
			}
			FDQuery->Close();
			FormProgressBar->Close();

			bSuccess = true;

	   } catch (...) {
			FormProgressBar->Close();

			UnicodeString uTmp;
			uTmp.sprintf(wLostConnection[iLang], L"Select", NameTableDB);
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
bool __fastcall TGroupProduct::LoadRecordId(TMyFDQuery *FDQuery)
{
	UnicodeString *uGroupDbData = new UnicodeString[CountGroupProdFieldsTableDB - 2];
	if(LoadRecord(FDQuery, NameTableDB, GroupProdFieldsTableDB, uGroupDbData, CountGroupProdFieldsTableDB)) {
		id = uGroupDbData[0].ToInt();
		GroupCode = uGroupDbData[1];
		Name = uGroupDbData[2];
		Description = uGroupDbData[3];
		Enabled = uGroupDbData[4].ToInt();

		delete[] uGroupDbData;
		return true;
	} else {
		delete[] uGroupDbData;
		return false;
	}
}
//---------------------------------------------------------------------------


