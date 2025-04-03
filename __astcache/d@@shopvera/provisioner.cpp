//---------------------------------------------------------------------------
#pragma hdrstop

#include "Provisioner.h"
#include "UnitProvisionerList.h"
#include "MoveProduct.h"
#include "Shop.h"
#include "Synchronize.h"
#include "UnitProgressBar.h"
#include "TUtills.h"

#pragma package(smart_init)

UnicodeString ProgressLoadProvis[2] = {
	L"Загрузка данных о \"Поставщиках\" с сервера",
	L"Serverdən \"Təminatçılar\" haqqında məlumatın yüklənməsi"
};
UnicodeString UnknowProvis[2] = {
	L"Неизвестный",
	L"Naməlum"
};


TProvisioner* TProvisioner::Unknow;

const wchar_t *TProvisioner::NameTableDB;
TDescFields **TProvisioner::ProvisionerFieldsTableDB = NULL;
int TProvisioner::CountProvisionerFieldsTableDB = 0;

//---------------------------------------------------------------------------
__fastcall TProvisioner::TProvisioner(void) : TPerson()
{
	Clear();
}
//---------------------------------------------------------------------------
__fastcall TProvisioner::TProvisioner(const TProvisioner &Provisioner) : TPerson(Provisioner)
{
	Organization = Provisioner.Organization;
}
//---------------------------------------------------------------------------
bool TProvisioner::GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB)
{
	NameTableDB =_NameTableDB;
	return GetFieldsFromDB(FDQuery, NameTableDB, ProvisionerFieldsTableDB, CountProvisionerFieldsTableDB);
}
//---------------------------------------------------------------------------
const TProvisioner& __fastcall TProvisioner::operator=(const TProvisioner &Provisioner)
{
	TPerson::operator=(Provisioner);
	Organization = Provisioner.Organization;
	return *this;
}
//---------------------------------------------------------------------------
void __fastcall TProvisioner::Clear(void)
{
	TPerson::Clear();
	Organization = L"";
}

//---------------------------------------------------------------------------
void __fastcall TProvisioner::InsertAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uEnable = int(Enabled);

	TFieldsValues FieldsValues[] = {
		{ProvisionerFieldsTableDB[1]->Field, 	Surname.w_str()},
		{ProvisionerFieldsTableDB[2]->Field,	Name.w_str()},
		{ProvisionerFieldsTableDB[3]->Field,	Patronymic.w_str()},
		{ProvisionerFieldsTableDB[4]->Field,	Organization.w_str()},
		{ProvisionerFieldsTableDB[5]->Field,	Address.w_str()},
		{ProvisionerFieldsTableDB[6]->Field, 	Phone1.w_str()},
		{ProvisionerFieldsTableDB[7]->Field, 	Phone2.w_str()},
		{ProvisionerFieldsTableDB[8]->Field, 	Description.w_str()},
		{ProvisionerFieldsTableDB[9]->Field, 	uEnable.w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	ExecSQL_Managed<TProvisioner>(FDQuery, FieldsValues, Count, NameTableDB, ProvisionerFieldsTableDB[0]->Field, TabDB::TB_PROVIS);
}

//---------------------------------------------------------------------------
void __fastcall TProvisioner::SaveAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uEnable = int(Enabled);

	TFieldsValues FieldsValues[] = {
		{ProvisionerFieldsTableDB[1]->Field, 	Surname.w_str()},
		{ProvisionerFieldsTableDB[2]->Field,	Name.w_str()},
		{ProvisionerFieldsTableDB[3]->Field,	Patronymic.w_str()},
		{ProvisionerFieldsTableDB[4]->Field,	Organization.w_str()},
		{ProvisionerFieldsTableDB[5]->Field,	Address.w_str()},
		{ProvisionerFieldsTableDB[6]->Field, 	Phone1.w_str()},
		{ProvisionerFieldsTableDB[7]->Field, 	Phone2.w_str()},
		{ProvisionerFieldsTableDB[8]->Field, 	Description.w_str()},
		{ProvisionerFieldsTableDB[9]->Field, 	uEnable.w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	UnicodeString uQuery = FormationUpdateString(NameTableDB, FieldsValues, Count);
	ExecSQL_Managed<TProvisioner>(FDQuery, uQuery, NameTableDB, TabDB::TB_PROVIS, TRecordType::RT_UPDATE, LOGS::LG_UPDATE);
}

//---------------------------------------------------------------------------
void __fastcall TProvisioner::DeleteObjectFromDb(TMyFDQuery *FDQuery)
{
	UnicodeString uQuery = FormationDeleteString(NameTableDB, ProvisionerFieldsTableDB[10]->Field);
	ExecSQL_Managed<TProvisioner>(FDQuery, uQuery, NameTableDB, TabDB::TB_PROVIS, TRecordType::RT_DELETE, LOGS::LG_DELETE);
}

//---------------------------------------------------------------------------
void __fastcall TProvisioner::CreateUnknowProvisioner(void) {
	Unknow = new TProvisioner();
    Unknow->Clear();
	Unknow->Surname = UnknowProvis[iLang];
	Unknow->Organization = UnknowProvis[iLang];
	Unknow->Enabled = true;
	Unknow->SetSumName();
}
//---------------------------------------------------------------------------
TProvisioner* __fastcall TProvisioner::GetProvisionerById(int id)
{
	if(id == -1) {
		return Unknow;
	}

//	unsigned Count = VProvisioners.size();
//
//	for(unsigned i=0; i < Count; i++) {
//		if(VProvisioners[i]->id == id) {
//			return VProvisioners[i];
//		}
//	}
//	return Unknow;

//	return (TProvisioner *)TBaseData::GetObjectById((vector <TBaseData*> *)&VProvisioners, id);
	return TObjectManager<TProvisioner>::FindById(id);
}
//---------------------------------------------------------------------------
bool __fastcall TProvisioner::SaveDataToFile(char *FileNmae)
{
	FILE *fs = fopen(FileNmae, "wb");
	if(fs == NULL) {
		return false;
	}
	fseek(fs, 0, SEEK_SET);
	fwprintf(fs, L"%lc", ucs2);

	fwprintf(fs, L"'%s'\n", TDateTime::CurrentDate().FormatString(L"dd.mm.yyyy").w_str());

	for(unsigned i=0; i < TObjectManager<TProvisioner>::GetList().size(); i++) {
		fwprintf(fs, L"'%d'\t'%ls'\t'%ls'\t'%ls'\t'%ls'\t'%ls'\t'%ls'\t'%ls'\t'%ls'\t'%d'\n",
					 TObjectManager<TProvisioner>::GetList()[i]->id,
					 TObjectManager<TProvisioner>::GetList()[i]->Surname.w_str(),
					 TObjectManager<TProvisioner>::GetList()[i]->Name.w_str(),
					 TObjectManager<TProvisioner>::GetList()[i]->Patronymic.w_str(),
					 TObjectManager<TProvisioner>::GetList()[i]->Organization.w_str(),
					 TObjectManager<TProvisioner>::GetList()[i]->Address.w_str(),
					 TObjectManager<TProvisioner>::GetList()[i]->Phone1.w_str(),
					 TObjectManager<TProvisioner>::GetList()[i]->Phone2.w_str(),
					 TUtills::ReplaceSymbol(TUtills::ReplaceSymbol(TObjectManager<TProvisioner>::GetList()[i]->Description.w_str(), L'\r', wchar_t(27)), L'\n', wchar_t(28)),
					 TObjectManager<TProvisioner>::GetList()[i]->Enabled);
	}
	fclose(fs);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TProvisioner::LoadDataFromFile(char *FileName)
{
	if(!LoadFileToWBuffer(FileName)) {
		return false;
	}

	UnicodeString uTmp;
	int CountParseFields = CountProvisionerFieldsTableDB - 2;

	while(Offset < FileSize) {

		Offset += TUtills::ParseWstring(WFileBuffer + Offset, wpws, CountParseFields, FileSize - Offset);
		if(Offset == 0) {
			delete WFileBuffer;
			return false;
		}

		TProvisioner *TmpProvisioner = new TProvisioner();

		uTmp = wpws[0];
		TmpProvisioner->id = uTmp.ToInt();
		uTmp = wpws[1];
		TmpProvisioner->Surname = uTmp;
		uTmp = wpws[2];
		TmpProvisioner->Name = uTmp;
		uTmp = wpws[3];
		TmpProvisioner->Patronymic = uTmp;
		uTmp = wpws[4];
		TmpProvisioner->Organization = uTmp;
		uTmp = wpws[5];
		TmpProvisioner->Address = uTmp;
		uTmp = wpws[6];
		TmpProvisioner->Phone1 = uTmp;
		uTmp = wpws[7];
		TmpProvisioner->Phone2 = uTmp;
		uTmp = wpws[8];
		TmpProvisioner->Description = TUtills::ReplaceSymbol(TUtills::ReplaceSymbol(uTmp.w_str(), wchar_t(27), L'\r'), wchar_t(28), L'\n');
		uTmp = wpws[9];
		TmpProvisioner->Enabled = uTmp.ToInt();

//		if(TmpProvisioner->id > LastIdDb) {
//			LastIdDb = TmpProvisioner->id;
//		}

		// additional fields
		TmpProvisioner->SetSumName();

		TObjectManager<TProvisioner>::GetList().push_back(TmpProvisioner);
	}

	delete FileBuffer;
	FileBuffer = NULL;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TProvisioner::LoadFromDB(TMyFDQuery *FDQuery, bool bLoadAll)
{
	TObjectManager<TProvisioner>::GetList().clear();

	if(!bLoadAll) {
		AnsiString aTmp = FormShop->FDConnection1->Params->Database + "_Provisioners.txt";
		bLoadAll = !LoadDataFromFile(aTmp.c_str());
	}

	UnicodeString uFields;
	int CountFields = 10;
	if(!bLoadAll) {
		CountFields = 11;
	}
	for(int i=0; i < CountFields; i++) {
		uFields += ProvisionerFieldsTableDB[i]->Field;
		if(i < CountFields - 1) {
			uFields += L",";
		}
	}

	UnicodeString uTmp = "Select " + uFields + " from ";
	uTmp += NameTableDB;
	uTmp += " where ";
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
			FormProgressBar->Label1->Caption = ProgressLoadProvis[iLang];
			FormProgressBar->Update();
			FormProgressBar->Label1->Left = (FormProgressBar->ClientWidth - FormProgressBar->Label1->Width)/2;
			FormProgressBar->ProgressBar1->Position = 0;
			FormProgressBar->Update();
			FDQuery->Open();
            FDQuery->FetchAll();
			FormProgressBar->ProgressBar1->Max = FDQuery->RecordCount;

			while (!FDQuery->Eof)
			{
				TProvisioner *TmpProvisioner = new TProvisioner();

				// Load data from MySql Data Base
				TmpProvisioner->id = FDQuery->FieldByName(ProvisionerFieldsTableDB[0]->Field)->AsString.ToInt();
				TmpProvisioner->Surname = FDQuery->FieldByName(ProvisionerFieldsTableDB[1]->Field)->AsString;
				TmpProvisioner->Name = FDQuery->FieldByName(ProvisionerFieldsTableDB[2]->Field)->AsString;
				TmpProvisioner->Patronymic = FDQuery->FieldByName(ProvisionerFieldsTableDB[3]->Field)->AsString;
				TmpProvisioner->Organization = FDQuery->FieldByName(ProvisionerFieldsTableDB[4]->Field)->AsString;
				TmpProvisioner->Address = FDQuery->FieldByName(ProvisionerFieldsTableDB[5]->Field)->AsString;
				TmpProvisioner->Phone1 = FDQuery->FieldByName(ProvisionerFieldsTableDB[6]->Field)->AsString;
				TmpProvisioner->Phone2 = FDQuery->FieldByName(ProvisionerFieldsTableDB[7]->Field)->AsString;
				TmpProvisioner->Description = FDQuery->FieldByName(ProvisionerFieldsTableDB[8]->Field)->AsString;
				TmpProvisioner->Enabled = FDQuery->FieldByName(ProvisionerFieldsTableDB[9]->Field)->AsString.ToInt();

				TmpProvisioner->SetSumName();

				if(bLoadAll) {
					TObjectManager<TProvisioner>::GetList().push_back(TmpProvisioner);
				} else {
					iDel = FDQuery->FieldByName(ProvisionerFieldsTableDB[10]->Field)->AsString.ToInt();
					int iIndex = TmpProvisioner->GetArrayIndexById();

					if(iDel == 1) {
						if(iIndex != -1) {
							TObjectManager<TProvisioner>::GetList().erase(TObjectManager<TProvisioner>::GetList().begin() + iIndex);
						}
					} else {
						if(iIndex == -1) {
							int InsertIndex = TmpProvisioner->GetArrayIndexById(true);
							TObjectManager<TProvisioner>::GetList().insert(TObjectManager<TProvisioner>::GetList().begin()+InsertIndex, TmpProvisioner);
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
bool __fastcall TProvisioner::LoadRecordId(TMyFDQuery *FDQuery)
{
	UnicodeString *uProvisionerDbData = new UnicodeString[CountProvisionerFieldsTableDB - 2];
	if(LoadRecord(FDQuery, NameTableDB, ProvisionerFieldsTableDB, uProvisionerDbData, CountProvisionerFieldsTableDB)) {
		id = uProvisionerDbData[0].ToInt();
		Surname = uProvisionerDbData[1];
		Name = uProvisionerDbData[2];
		Patronymic = uProvisionerDbData[3];
		Organization = uProvisionerDbData[4];
		Address = uProvisionerDbData[5];
		Phone1 = uProvisionerDbData[6];
		Phone2 = uProvisionerDbData[7];
		Description = uProvisionerDbData[8];
		Enabled = uProvisionerDbData[9].ToInt();

		SetSumName();
		delete[] uProvisionerDbData;
		return true;
	} else {
		delete[] uProvisionerDbData;
		return false;
	}
}
//---------------------------------------------------------------------------

