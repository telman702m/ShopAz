//---------------------------------------------------------------------------
#pragma hdrstop

#include "Workers.h"
#include "Shop.h"
#include "BaseDataTemplates.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


UnicodeString TWorkers::PrivilegName[5] = {L"Супервизор", L"Администратор", L"Менеджер", L"Продавец", L"Неопределенный"};

const wchar_t *TWorkers::NameTableDB;
TDescFields **TWorkers::WorkerFieldsTableDB = NULL;
int TWorkers::CountWorkerFieldsTableDB = 0;

//---------------------------------------------------------------------------
__fastcall TWorkers::TWorkers(void) : TPerson()
{
	Privilege = TPrivilege::PRV_UNKNOW;
	Login = L"";
	Password = L"";
	idUnitShop = -1;
//	Clear();
}
//---------------------------------------------------------------------------
bool TWorkers::GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB)
{
	NameTableDB = _NameTableDB;
	return GetFieldsFromDB(FDQuery, NameTableDB, WorkerFieldsTableDB, CountWorkerFieldsTableDB);
}
//---------------------------------------------------------------------------
void __fastcall TWorkers::Clear(void)
{
	TPerson::Clear();
	Login = L"";
	Password = L"";
	idUnitShop = -1;
	Privilege = TPrivilege::PRV_UNKNOW;
}
//---------------------------------------------------------------------------
TWorkers* __fastcall TWorkers::GetWorkerById(int id)
{
	return TObjectManager<TWorkers>::FindById(id);
}
//---------------------------------------------------------------------------
void __fastcall TWorkers::LoadFromDB(TMyFDQuery *FDQuery)
{
	UnicodeString uTmp = "Select * from ";
	uTmp += NameTableDB;

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;

	while(!bSuccess) {
		try {
			FDQuery->Open();

			while (!FDQuery->Eof)
			{
				TWorkers *TmpWorkers = new TWorkers();

				// Load data from MySql Data Base
				TmpWorkers->id = FDQuery->FieldByName(WorkerFieldsTableDB[0]->Field)->AsString.ToInt();
				TmpWorkers->Surname = FDQuery->FieldByName(WorkerFieldsTableDB[1]->Field)->AsString;
				TmpWorkers->Name = FDQuery->FieldByName(WorkerFieldsTableDB[2]->Field)->AsString;
				TmpWorkers->Patronymic = FDQuery->FieldByName(WorkerFieldsTableDB[3]->Field)->AsString;
				TmpWorkers->Login = FDQuery->FieldByName(WorkerFieldsTableDB[4]->Field)->AsString;
				TmpWorkers->Password = FDQuery->FieldByName(WorkerFieldsTableDB[5]->Field)->AsString;
				TmpWorkers->idUnitShop = FDQuery->FieldByName(WorkerFieldsTableDB[6]->Field)->AsString.ToInt();
				TmpWorkers->Privilege = TPrivilege(FDQuery->FieldByName(WorkerFieldsTableDB[7]->Field)->AsString.ToInt());
				TmpWorkers->Address = FDQuery->FieldByName(WorkerFieldsTableDB[8]->Field)->AsString;
				TmpWorkers->Phone1 = FDQuery->FieldByName(WorkerFieldsTableDB[9]->Field)->AsString;
				TmpWorkers->Phone2 = FDQuery->FieldByName(WorkerFieldsTableDB[10]->Field)->AsString;
				TmpWorkers->Description = FDQuery->FieldByName(WorkerFieldsTableDB[11]->Field)->AsString;
				TmpWorkers->Enabled = FDQuery->FieldByName(WorkerFieldsTableDB[12]->Field)->AsString.ToInt();

				TmpWorkers->SetSumName();

				TObjectManager<TWorkers>::GetList().push_back(TmpWorkers);
				FDQuery->Next();
			}
			FDQuery->Close();

			bSuccess = true;

	   } catch (...) {
			UnicodeString uTmp = uTmp.sprintf(wLostConnection[iLang], L"Select", NameTableDB);
			if(Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}
}

//---------------------------------------------------------------------------
void __fastcall TWorkers::InsertAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uWorkerDbData[] = {
		L"",
		Surname,
		Name,
		Patronymic,
		Login,
		Password,
		idUnitShop,
		Privilege,
		Address,
		Phone1,
		Phone2,
		Description,
		int(Enabled)
	};
	TFieldsValues FieldsValues[] = {
		{WorkerFieldsTableDB[1]->Field, 	uWorkerDbData[1].w_str()},
		{WorkerFieldsTableDB[2]->Field,		uWorkerDbData[2].w_str()},
		{WorkerFieldsTableDB[3]->Field,		uWorkerDbData[3].w_str()},
		{WorkerFieldsTableDB[4]->Field,		uWorkerDbData[4].w_str()},
		{WorkerFieldsTableDB[5]->Field,		uWorkerDbData[5].w_str()},
		{WorkerFieldsTableDB[6]->Field, 	uWorkerDbData[6].w_str()},
		{WorkerFieldsTableDB[7]->Field, 	uWorkerDbData[7].w_str()},
		{WorkerFieldsTableDB[8]->Field, 	uWorkerDbData[8].w_str()},
		{WorkerFieldsTableDB[9]->Field, 	uWorkerDbData[9].w_str()},
		{WorkerFieldsTableDB[10]->Field, 	uWorkerDbData[10].w_str()},
		{WorkerFieldsTableDB[11]->Field, 	uWorkerDbData[11].w_str()},
		{WorkerFieldsTableDB[12]->Field,	uWorkerDbData[12].w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	ExecSQL_Managed<TWorkers>(FDQuery, FieldsValues, Count, NameTableDB, WorkerFieldsTableDB[0]->Field, TabDB::TB_UNDEF);
}

//---------------------------------------------------------------------------
void __fastcall TWorkers::SaveAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uWorkerDbData[] = {
		L"",
		Surname,
		Name,
		Patronymic,
		Login,
		Password,
		idUnitShop,
		Privilege,
		Address,
		Phone1,
		Phone2,
		Description,
		int(Enabled)
	};
	TFieldsValues FieldsValues[] = {
		{WorkerFieldsTableDB[1]->Field, 	uWorkerDbData[1].w_str()},
		{WorkerFieldsTableDB[2]->Field,		uWorkerDbData[2].w_str()},
		{WorkerFieldsTableDB[3]->Field,		uWorkerDbData[3].w_str()},
		{WorkerFieldsTableDB[4]->Field,		uWorkerDbData[4].w_str()},
		{WorkerFieldsTableDB[5]->Field,		uWorkerDbData[5].w_str()},
		{WorkerFieldsTableDB[6]->Field, 	uWorkerDbData[6].w_str()},
		{WorkerFieldsTableDB[7]->Field, 	uWorkerDbData[7].w_str()},
		{WorkerFieldsTableDB[8]->Field, 	uWorkerDbData[8].w_str()},
		{WorkerFieldsTableDB[9]->Field, 	uWorkerDbData[9].w_str()},
		{WorkerFieldsTableDB[10]->Field, 	uWorkerDbData[10].w_str()},
		{WorkerFieldsTableDB[11]->Field, 	uWorkerDbData[11].w_str()},
		{WorkerFieldsTableDB[12]->Field,	uWorkerDbData[12].w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	UnicodeString uQuery = FormationUpdateString(NameTableDB, FieldsValues, Count);
	ExecSQL_Managed<TWorkers>(FDQuery, uQuery, NameTableDB, TabDB::TB_UNDEF, TRecordType::RT_UNDEF, LOGS::LG_UNDEF);
}

//---------------------------------------------------------------------------
void __fastcall TWorkers::DeleteObjectFromDb(TMyFDQuery *FDQuery)
{
	UnicodeString uQuery = FormationDeleteString(NameTableDB, WorkerFieldsTableDB[13]->Field);
	ExecSQL_Managed<TWorkers>(FDQuery, uQuery, NameTableDB, TabDB::TB_UNDEF, TRecordType::RT_UNDEF, LOGS::LG_UNDEF);
}

//---------------------------------------------------------------------------
bool __fastcall TWorkers::LoadRecordId(TMyFDQuery *FDQuery)
{
	return true;
}
//---------------------------------------------------------------------------

