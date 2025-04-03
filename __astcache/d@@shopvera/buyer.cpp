//---------------------------------------------------------------------------
#pragma hdrstop

#include "Buyer.h"
#include "UnitBuyerList.h"
#include "MoveProduct.h"
#include "Shop.h"
#include "Synchronize.h"
#include "UnitProgressBar.h"
#include "TUtills.h"

#pragma package(smart_init)

UnicodeString UnknowBuyer[2] = {
	L"Неизвестный",
	L"Naməlum"
};
UnicodeString UncertainBuyer[2] = {
	L"Неопределен",
	L"Qeyri-müəyyən"
};
UnicodeString ProgressLoadBuyer[2] = {
	L"Загрузка данных о \"Покупателях\" с сервера",
	L"Serverdən \"Alıcılar\" haqqında məlumatın yüklənməsi"
};

TBuyer* TBuyer::Unknow;
TBuyer* TBuyer::Empty;

const wchar_t *TBuyer::NameTableDB;
TDescFields **TBuyer::BuyerFieldsTableDB = NULL;
int TBuyer::CountBuyerFieldsTableDB = 0;

//---------------------------------------------------------------------------
__fastcall TBuyer::TBuyer(void) : TPerson()
{
	Clear();
}
//---------------------------------------------------------------------------
bool TBuyer::GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB)
{
	NameTableDB = _NameTableDB;
	return GetFieldsFromDB(FDQuery, NameTableDB, BuyerFieldsTableDB, CountBuyerFieldsTableDB);
}
//---------------------------------------------------------------------------
void __fastcall TBuyer::Clear(void)
{
	TPerson::Clear();
	Organization = L"";
}
//---------------------------------------------------------------------------
__fastcall TBuyer::TBuyer(const TBuyer &Buyer) : TPerson(Buyer)
{
	Organization = Buyer.Organization;
}
//---------------------------------------------------------------------------
const TBuyer& __fastcall TBuyer::operator=(const TBuyer &Buyer)
{
	TPerson::operator = (Buyer);
	Organization = Buyer.Organization;
	return *this;
}

//---------------------------------------------------------------------------
void __fastcall TBuyer::InsertAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uEnable = int(Enabled);

	TFieldsValues FieldsValues[] = {
		{BuyerFieldsTableDB[1]->Field, 	Surname.w_str()},
		{BuyerFieldsTableDB[2]->Field,	Name.w_str()},
		{BuyerFieldsTableDB[3]->Field,	Patronymic.w_str()},
		{BuyerFieldsTableDB[4]->Field,	Organization.w_str()},
		{BuyerFieldsTableDB[5]->Field,	Address.w_str()},
		{BuyerFieldsTableDB[6]->Field, 	Phone1.w_str()},
		{BuyerFieldsTableDB[7]->Field, 	Phone2.w_str()},
		{BuyerFieldsTableDB[8]->Field, 	Description.w_str()},
		{BuyerFieldsTableDB[9]->Field, 	uEnable.w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	ExecSQL_Managed<TBuyer>(FDQuery, FieldsValues, Count, NameTableDB, BuyerFieldsTableDB[0]->Field, TabDB::TB_BUYER);
}

//---------------------------------------------------------------------------
void __fastcall TBuyer::SaveAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uEnable = int(Enabled);

	TFieldsValues FieldsValues[] = {
		{BuyerFieldsTableDB[1]->Field, 	Surname.w_str()},
		{BuyerFieldsTableDB[2]->Field,	Name.w_str()},
		{BuyerFieldsTableDB[3]->Field,	Patronymic.w_str()},
		{BuyerFieldsTableDB[4]->Field,	Organization.w_str()},
		{BuyerFieldsTableDB[5]->Field,	Address.w_str()},
		{BuyerFieldsTableDB[6]->Field, 	Phone1.w_str()},
		{BuyerFieldsTableDB[7]->Field, 	Phone2.w_str()},
		{BuyerFieldsTableDB[8]->Field, 	Description.w_str()},
		{BuyerFieldsTableDB[9]->Field, 	uEnable.w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	UnicodeString uQuery = FormationUpdateString(NameTableDB, FieldsValues, Count);
	ExecSQL_Managed<TBuyer>(FDQuery, uQuery, NameTableDB, TabDB::TB_BUYER, TRecordType::RT_UPDATE, LOGS::LG_UPDATE);
}

//---------------------------------------------------------------------------
void __fastcall TBuyer::DeleteObjectFromDb(TMyFDQuery *FDQuery)
{
	UnicodeString uQuery = FormationDeleteString(NameTableDB, BuyerFieldsTableDB[10]->Field);
	ExecSQL_Managed<TBuyer>(FDQuery, uQuery, NameTableDB, TabDB::TB_BUYER, TRecordType::RT_DELETE, LOGS::LG_DELETE);
}

//---------------------------------------------------------------------------
void __fastcall TBuyer::CreateUnknowBuyer(void) {
	Unknow = new TBuyer();
    Unknow->Clear();
	Unknow->Surname = UnknowBuyer[iLang];
	Unknow->Organization = UnknowBuyer[iLang];
	Unknow->Enabled = true;
	Unknow->SetSumName();
}
//---------------------------------------------------------------------------
void __fastcall TBuyer::CreateEmptyBuyer(void) {
	Empty = new TBuyer();
	Empty->Clear();
	Empty->Surname = UncertainBuyer[iLang];
	Empty->Enabled = true;
	Empty->SetSumName();
}
//---------------------------------------------------------------------------
TBuyer* __fastcall TBuyer::GetBuyerById(int id)
{
	if(id == -1) {
		return Unknow;
	}

//	return (TBuyer *)TBaseData::GetObjectById((vector <TBaseData*> *)&VBuyers, id);
	return TObjectManager<TBuyer>::FindById(id);
}
//---------------------------------------------------------------------------
bool __fastcall TBuyer::SaveDataToFile(char *FileNmae)
{
	FILE *fs = fopen(FileNmae, "wb");
	if(fs == NULL) {
		return false;
	}
	fseek(fs, 0, SEEK_SET);
	fwprintf(fs, L"%lc", ucs2);

	fwprintf(fs, L"'%s'\n", TDateTime::CurrentDate().FormatString(L"dd.mm.yyyy").w_str());

	for(unsigned i=0; i < TObjectManager<TBuyer>::GetList().size(); i++) {
		fwprintf(fs, L"'%d'\t'%ls'\t'%ls'\t'%ls'\t'%ls'\t'%ls'\t'%ls'\t'%ls'\t'%ls'\t'%d'\n",
					 TObjectManager<TBuyer>::GetList()[i]->id,
					 TObjectManager<TBuyer>::GetList()[i]->Surname.w_str(),
					 TObjectManager<TBuyer>::GetList()[i]->Name.w_str(),
					 TObjectManager<TBuyer>::GetList()[i]->Patronymic.w_str(),
					 TObjectManager<TBuyer>::GetList()[i]->Organization.w_str(),
					 TObjectManager<TBuyer>::GetList()[i]->Address.w_str(),
					 TObjectManager<TBuyer>::GetList()[i]->Phone1.w_str(),
					 TObjectManager<TBuyer>::GetList()[i]->Phone2.w_str(),
					 TUtills::ReplaceSymbol(TUtills::ReplaceSymbol(TObjectManager<TBuyer>::GetList()[i]->Description.w_str(), L'\r', wchar_t(27)), L'\n', wchar_t(28)),
					 TObjectManager<TBuyer>::GetList()[i]->Enabled);
	}
	fclose(fs);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TBuyer::LoadDataFromFile(char *FileName)
{
	if(!LoadFileToWBuffer(FileName)) {
		return false;
	}

	UnicodeString uTmp;
	int CountParseFields = CountBuyerFieldsTableDB - 2;

	while(Offset < FileSize) {

		Offset += TUtills::ParseWstring(WFileBuffer + Offset, wpws, CountParseFields, FileSize - Offset);
		if(Offset == 0) {
			delete WFileBuffer;
			return false;
		}

		TBuyer *TmpBuyer = new TBuyer();

		uTmp = wpws[0];
		TmpBuyer->id = uTmp.ToInt();
		uTmp = wpws[1];
		TmpBuyer->Surname = uTmp;
		uTmp = wpws[2];
		TmpBuyer->Name = uTmp;
		uTmp = wpws[3];
		TmpBuyer->Patronymic = uTmp;
		uTmp = wpws[4];
		TmpBuyer->Organization = uTmp;
		uTmp = wpws[5];
		TmpBuyer->Address = uTmp;
		uTmp = wpws[6];
		TmpBuyer->Phone1 = uTmp;
		uTmp = wpws[7];
		TmpBuyer->Phone2 = uTmp;
		uTmp = wpws[8];
		TmpBuyer->Description = TUtills::ReplaceSymbol(TUtills::ReplaceSymbol(uTmp.w_str(), wchar_t(27), L'\r'), wchar_t(28), L'\n');
		uTmp = wpws[9];
		TmpBuyer->Enabled = uTmp.ToInt();

//		if(TmpBuyer->id > LastIdDb) {
//			LastIdDb = TmpBuyer->id;
//		}

		// additional fields
		TmpBuyer->SetSumName();

		TObjectManager<TBuyer>::GetList().push_back(TmpBuyer);
	}

	delete FileBuffer;
	FileBuffer = NULL;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TBuyer::LoadFromDB(TMyFDQuery *FDQuery, bool bLoadAll)
{
	TObjectManager<TBuyer>::GetList().clear();

	if(!bLoadAll) {
		AnsiString aTmp = FormShop->FDConnection1->Params->Database + "_Buyers.txt";
		bLoadAll = !LoadDataFromFile(aTmp.c_str());
	}

	UnicodeString uFields;
	int CountFields = 10;
	if(!bLoadAll) {
		CountFields = 11;
	}
	for(int i=0; i < CountFields; i++) {
		uFields += BuyerFieldsTableDB[i]->Field;
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
			FormProgressBar->Label1->Caption = ProgressLoadBuyer[iLang];
			FormProgressBar->Update();
			FormProgressBar->Label1->Left = (FormProgressBar->ClientWidth - FormProgressBar->Label1->Width)/2;
			FormProgressBar->ProgressBar1->Position = 0;
			FormProgressBar->Update();
			FDQuery->Open();
            FDQuery->FetchAll();
			FormProgressBar->ProgressBar1->Max = FDQuery->RecordCount;

			while (!FDQuery->Eof) {
				TBuyer *TmpBuyer = new TBuyer();

				// Load data from MySql Data Base
				TmpBuyer->id = FDQuery->FieldByName(BuyerFieldsTableDB[0]->Field)->AsString.ToInt();
				TmpBuyer->Surname = FDQuery->FieldByName(BuyerFieldsTableDB[1]->Field)->AsString;
				TmpBuyer->Name = FDQuery->FieldByName(BuyerFieldsTableDB[2]->Field)->AsString;
				TmpBuyer->Patronymic = FDQuery->FieldByName(BuyerFieldsTableDB[3]->Field)->AsString;
				TmpBuyer->Organization = FDQuery->FieldByName(BuyerFieldsTableDB[4]->Field)->AsString;
				TmpBuyer->Address = FDQuery->FieldByName(BuyerFieldsTableDB[5]->Field)->AsString;
				TmpBuyer->Phone1 = FDQuery->FieldByName(BuyerFieldsTableDB[6]->Field)->AsString;
				TmpBuyer->Phone2 = FDQuery->FieldByName(BuyerFieldsTableDB[7]->Field)->AsString;
				TmpBuyer->Description = FDQuery->FieldByName(BuyerFieldsTableDB[8]->Field)->AsString;
				TmpBuyer->Enabled = FDQuery->FieldByName(BuyerFieldsTableDB[9]->Field)->AsString.ToInt();

				TmpBuyer->SetSumName();

				if(bLoadAll) {
					TObjectManager<TBuyer>::GetList().push_back(TmpBuyer);
				} else {
					iDel = FDQuery->FieldByName(BuyerFieldsTableDB[10]->Field)->AsString.ToInt();
					int iIndex = TmpBuyer->GetArrayIndexById();

					if(iDel == 1) {
						if(iIndex != -1) {
							TObjectManager<TBuyer>::GetList().erase(TObjectManager<TBuyer>::GetList().begin() + iIndex);
						}
					} else {
						if(iIndex == -1) {
							int InsertIndex = TmpBuyer->GetArrayIndexById(true);
							TObjectManager<TBuyer>::GetList().insert(TObjectManager<TBuyer>::GetList().begin()+InsertIndex, TmpBuyer);
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
bool __fastcall TBuyer::LoadRecordId(TMyFDQuery *FDQuery)
{
	UnicodeString *uBuyerDbData = new UnicodeString[CountBuyerFieldsTableDB - 2];
	if(LoadRecord(FDQuery, NameTableDB, BuyerFieldsTableDB, uBuyerDbData, CountBuyerFieldsTableDB)) {
		id = uBuyerDbData[0].ToInt();
		Surname = uBuyerDbData[1];
		Name = uBuyerDbData[2];
		Patronymic = uBuyerDbData[3];
		Organization = uBuyerDbData[4];
		Address = uBuyerDbData[5];
		Phone1 = uBuyerDbData[6];
		Phone2 = uBuyerDbData[7];
		Description = uBuyerDbData[8];
		Enabled = uBuyerDbData[9].ToInt();

		SetSumName();
		delete[] uBuyerDbData;
		return true;
	} else {
		delete[] uBuyerDbData;
		return false;
	}
}
//---------------------------------------------------------------------------

