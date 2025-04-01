//---------------------------------------------------------------------------
#pragma hdrstop

#include "Workers.h"
#include "Shop.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

/*const int CountFieldsWorkers = 15;
wchar_t *WorkersDbFields[CountFieldsWorkers][2] =
   {{L"id",               L" Int(11) Not Null Auto_increment, "},
	{L"Surname",       	  L" Char(40) DEFAULT NULL, "},
	{L"Name",	          L" Char(40) DEFAULT NULL, "},
	{L"Patronymic",       L" Char(40) DEFAULT NULL, "},
	{L"Login",			  L" Char(30) NOT NULL, "},
	{L"Password", 		  L" Char(30) NOT NULL, "},
	{L"idUnitShop",		  L" Int(11) DEFAULT NULL, "},
	{L"Privilege",		  L" Tinyint(2) DEFAULT '100', "},
	{L"Address",          L" Char(80) DEFAULT NULL, "},
	{L"Phone1",           L" Char(24) DEFAULT NULL, "},
	{L"Phone2",           L" Char(24) DEFAULT NULL, "},
	{L"Description",      L" Varchar(368) DEFAULT NULL, "},
	{L"Enable",           L" Tinyint(2) DEFAULT NULL, "},
	{L"Deleted",		  L" Smallint(1) "},
	{L"LastUpdate",	  	  L" TIMESTAMP CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, "}
   };*/

UnicodeString TWorkers::PrivilegName[5] = {L"Супервизор", L"Администратор", L"Менеджер", L"Продавец", L"Неопределенный"};

vector <TWorkers*> TWorkers::VWorkers;

const wchar_t *TWorkers::NameTableDB;
TDescFields **TWorkers::WorkerFieldsTableDB = NULL;
int TWorkers::CountWorkerFieldsTableDB = 0;

//---------------------------------------------------------------------------
__fastcall TWorkers::TWorkers(void) : TPerson()
{
	VBaseData = (vector <TBaseData*> *)&VWorkers;

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
	return (TWorkers *)TBaseData::GetObjectById((vector <TBaseData*> *)&VWorkers, id);
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

				VWorkers.push_back(TmpWorkers);
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

	ExecSQL(FDQuery, FieldsValues, Count, NameTableDB, WorkerFieldsTableDB[0]->Field, TabDB::TB_UNDEF);
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
	ExecSQL(FDQuery, uQuery, NameTableDB, TabDB::TB_UNDEF, TRecordType::RT_UNDEF, LOGS::LG_UNDEF);
}

//---------------------------------------------------------------------------
void __fastcall TWorkers::DeleteObjectFromDb(TMyFDQuery *FDQuery)
{
	UnicodeString uQuery = FormationDeleteString(NameTableDB, WorkerFieldsTableDB[13]->Field);
	ExecSQL(FDQuery, uQuery, NameTableDB, TabDB::TB_UNDEF, TRecordType::RT_UNDEF, LOGS::LG_UNDEF);
}

//---------------------------------------------------------------------------
bool __fastcall TWorkers::LoadRecordId(TMyFDQuery *FDQuery)
{
	return true;
}
//---------------------------------------------------------------------------

