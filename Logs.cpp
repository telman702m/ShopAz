//---------------------------------------------------------------------------
#pragma hdrstop

#include <System.DateUtils.hpp>

#include "Logs.h"
#include "Shop.h"
#include "UnitLogs.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

/*UnicodeString TLogs::LogsDbFields[CountFieldsLog][2] =
	{{L"id",              L" Int(11) Not Null Auto_increment, "},
	 {L"ConnectedId",     L" Int(11), "},
	 {L"DateTime",        L" TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, "},
	 {L"LastAccess",      L" TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, "},
	 {L"IdShop",  		  L" Int(2), "},
	 {L"IdUser",          L" Int(4), "},
	 {L"IdTable",  		  L" Int(4), "},
	 {L"IdOperation",     L" Int(4), "},
	 {L"CommandSQL",      L" Varchar(128), "}};*/

TDescFields *TLogs::LogsDbFields = NULL;
int TLogs::CountFieldsLog = 0;


vector <TLogs*> TLogs::VLogs;
vector <TLogData*> TLogs::VLogsData;
vector <int> TLogs::VRefreshIndexLastAccess;
UnicodeString TLogs::uRefreshes = L"";
int TLogs::LastLogId = 0;
unsigned TLogs::LastParseIndex = 0;
TDateTime TLogs::CurrentDate;


//---------------------------------------------------------------------------
bool __fastcall TLogs::Init(TMyFDQuery *FDQuery)
{
	FDQuery->SQL->Text = L"desc Logs";
	FDQuery->Open();
	FDQuery->FetchAll();

	CountFieldsLog = FDQuery->RecordCount;

	if(CountFieldsLog > 0) {
		LogsDbFields = new TDescFields[CountFieldsLog];
	} else {
        return false;
    }

	int size;
	int ip = 0;

	try {
		while (!FDQuery->Eof) {
			size = FDQuery->FieldByName(L"Field")->AsString.Length();
			LogsDbFields[ip].Field = new wchar_t[size + 1];
			wcscpy(LogsDbFields[ip].Field, FDQuery->FieldByName(L"Field")->AsString.w_str());
			LogsDbFields[ip].Field[size] = 0;

			size = FDQuery->FieldByName(L"Type")->AsString.Length();
			LogsDbFields[ip].Type = new wchar_t[size + 1];
			wcscpy(LogsDbFields[ip].Type, FDQuery->FieldByName(L"Type")->AsString.w_str());
			LogsDbFields[ip].Type[size] = 0;

			size = FDQuery->FieldByName(L"Null")->AsString.Length();
			LogsDbFields[ip].Null = new wchar_t[size + 1];
			wcscpy(LogsDbFields[ip].Null, FDQuery->FieldByName(L"Null")->AsString.w_str());
			LogsDbFields[ip].Null[size] = 0;

			size = FDQuery->FieldByName(L"Key")->AsString.Length();
			LogsDbFields[ip].Key = new wchar_t[size + 1];
			wcscpy(LogsDbFields[ip].Key, FDQuery->FieldByName(L"Key")->AsString.w_str());
			LogsDbFields[ip].Key[size] = 0;

			size = FDQuery->FieldByName(L"Default")->AsString.Length();
			LogsDbFields[ip].Default = new wchar_t[size + 1];
			wcscpy(LogsDbFields[ip].Default, FDQuery->FieldByName(L"Default")->AsString.w_str());
			LogsDbFields[ip].Default[size] = 0;

			size = FDQuery->FieldByName(L"Extra")->AsString.Length();
			LogsDbFields[ip].Extra = new wchar_t[size + 1];
			wcscpy(LogsDbFields[ip].Extra, FDQuery->FieldByName(L"Extra")->AsString.w_str());
			LogsDbFields[ip].Extra[size] = 0;

            ip++;
			FDQuery->Next();
		}

	} catch (...) {
		return false;
	}
	FDQuery->Close();

	return true;
}
//---------------------------------------------------------------------------
void __fastcall TLogs::ShowFields(void)
{
	TStringList *SList;
	SList = new TStringList;

	UnicodeString uTmp = L"Field\tType\tNull\tKey\tDefault\tExtra";
	SList->Add(uTmp);

	for (int i = 0; i < CountFieldsLog; i++) {
		uTmp = LogsDbFields[i].Field;
		uTmp += L"\t";
		uTmp += LogsDbFields[i].Type;
		uTmp += L"\t";
		uTmp += LogsDbFields[i].Null;
		uTmp += L"\t";
		uTmp += LogsDbFields[i].Key;
		uTmp += L"\t";
		uTmp += LogsDbFields[i].Default;
		uTmp += L"\t";
		uTmp += LogsDbFields[i].Extra;
		SList->Add(uTmp);
	}

//	SList->SaveToFile(ExtractFilePath(Application->ExeName) + "LogsFields.txt");
    delete SList;
}
//---------------------------------------------------------------------------
__fastcall TLogs::TLogs(void)
{
	Clear();
}
//---------------------------------------------------------------------------
void __fastcall TLogs::Clear(void)
{
	id = -1;
	ConnectedId = -1;
	DateTime = 25570;
	LastAccess = 25570;
	IdShop = -1;
	IdWorker = -1;
	IdTable = TabDB::TB_UNDEF;
	IdOperation = LOGS::LG_UNDEF;
	CommandSQL = L"";
}
/*
//---------------------------------------------------------------------------
TLogs::~TLogs(void)
{
//
}
//---------------------------------------------------------------------------
TLogs::TLogs(const TLogs &Logs)
{
	id = Logs.id;
}
//---------------------------------------------------------------------------
const TLogs& TLogs::operator=(const TLogs &Logs)
{
	id = Logs.id;

	return *this;
}
*/
//---------------------------------------------------------------------------
void __fastcall TLogs::Set(TabDB _IdTable, LOGS _IdOperation, UnicodeString _CommandSQL)
{
	IdTable = _IdTable;
	IdOperation = _IdOperation;

	CommandSQL = StringReplace(_CommandSQL, L"'", L"\"", TReplaceFlags()<<rfReplaceAll);
}
//---------------------------------------------------------------------------
void __fastcall TLogs::InsertToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uStr[5];
	UnicodeString uTmps;

	uStr[0] = uTmps.sprintf(L"%d", ConnectedId);
	uStr[1] = uTmps.sprintf(L"%d", IdShop);
	uStr[2] = uTmps.sprintf(L"%d", IdWorker);
	uStr[3] = uTmps.sprintf(L"%d", IdTable);
	uStr[4] = uTmps.sprintf(L"%d", IdOperation);

	TFieldsValues FieldsValues[] = {
		{LogsDbFields[1].Field, uStr[0].w_str()},
		{LogsDbFields[2].Field,	L"current_timestamp()"},
		{LogsDbFields[4].Field,	uStr[1].w_str()},
		{LogsDbFields[5].Field,	uStr[2].w_str()},
		{LogsDbFields[6].Field, uStr[3].w_str()},
		{LogsDbFields[7].Field, uStr[4].w_str()},
		{LogsDbFields[8].Field, CommandSQL.w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	bool bSuccess = false;

	TBaseData::TimerSyncDisable();

	while(!bSuccess) {
		try {
			id = FDQuery->MyInsert2(L"Logs", LogsDbFields[0].Field, FieldsValues, Count);

			if(id != -1) bSuccess = true;
			else bSuccess = false;

	   } catch (...) {
			if(Application->MessageBox(L"Error on MySQL operation Insert Command", uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}

	TBaseData::TimerSyncRestore();
}
//---------------------------------------------------------------------------
void __fastcall TLogs::UpdateToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uTmp;
	uTmp.sprintf(L"Update Logs Set LastAccess = current_timestamp() where id=%d;", ConnectedId);

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;

	TBaseData::TimerSyncDisable();

	while(!bSuccess) {
		try {
			FDQuery->Execute();
			bSuccess = true;

	   } catch (...) {
			if(Application->MessageBox(L"Error on MySQL operation Update Command", uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}

	TBaseData::TimerSyncRestore();
}
//---------------------------------------------------------------------------
void __fastcall TLogs::UpdateConnectedId(TMyFDQuery *FDQuery)
{
	UnicodeString uTmp;
	uTmp.sprintf(L"Update Logs Set ConnectedId = %d where id=%d;", id, id);

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;

	TBaseData::TimerSyncDisable();

	while(!bSuccess) {
		try {
			FDQuery->Execute();
			bSuccess = true;

	   } catch (...) {
			if(Application->MessageBox(L"Error on MySQL operation UpdateConnectedId", uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}

	TBaseData::TimerSyncRestore();
}

//---------------------------------------------------------------------------
void __fastcall TLogs::DeleteFromDb(TMyFDQuery *FDQuery)
{
	UnicodeString uTmp = L"Delete from Logs Where id=";
	uTmp += id;

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;

	TBaseData::TimerSyncDisable();

	while(!bSuccess) {
		try {
			FDQuery->Execute();
			bSuccess = true;

	   } catch (...) {
			if(Application->MessageBox(L"Error on MySQL operation Delete Command", uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}

	TBaseData::TimerSyncRestore();
}
//---------------------------------------------------------------------------
void __fastcall TLogs::GetCurrentDateFromDB(TMyFDQuery *FDQuery)
{
	FDQuery->SQL->Text = L"Select now() as CurrentDate;";

	bool bSuccess = false;

	TBaseData::TimerSyncDisable();

	while(!bSuccess) {
		try {
			FDQuery->Open();

			while (!FDQuery->Eof) {
				CurrentDate = FDQuery->FieldByName(L"CurrentDate")->AsString;

				FDQuery->Next();
			}
			FDQuery->Close();

			bSuccess = true;

	   } catch (...) {
			if(Application->MessageBox(L"Error MySQL Load Logs", uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}

	TBaseData::TimerSyncRestore();
}
//---------------------------------------------------------------------------
int __fastcall TLogs::LoadFromDB(TMyFDQuery *FDQuery, int iLastId, TDateTime DateTime1, TDateTime DateTime2)
{
	int CountLoadedRows = 0;
	UnicodeString uTmp;
	uTmp.sprintf(L"Select *, now() as CurrentDate from Logs where id >= %d and DateTime >= '%s' and DateTime <= '%s'",
				 iLastId + 1, DateTime1.FormatString(L"yyyy-mm-dd hh:mm:ss").w_str(), DateTime2.FormatString(L"yyyy-mm-dd hh:mm:ss").w_str());

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;

	TBaseData::TimerSyncDisable();

	while(!bSuccess) {
		try {
			FDQuery->Open();
            FDQuery->FetchAll();

			while (!FDQuery->Eof) {

				TLogs *TmpLogs = new TLogs();

				// Load data from MySql Data Base
				TmpLogs->id = FDQuery->FieldByName(LogsDbFields[0].Field)->AsString.ToInt();
				TmpLogs->ConnectedId = FDQuery->FieldByName(LogsDbFields[1].Field)->AsString.ToInt();
				TmpLogs->DateTime = FDQuery->FieldByName(LogsDbFields[2].Field)->AsString;
				TmpLogs->LastAccess = FDQuery->FieldByName(LogsDbFields[3].Field)->AsString;
				TmpLogs->IdShop = FDQuery->FieldByName(LogsDbFields[4].Field)->AsString.ToInt();
				TmpLogs->IdWorker = FDQuery->FieldByName(LogsDbFields[5].Field)->AsString.ToInt();
				TmpLogs->IdTable = TabDB(FDQuery->FieldByName(LogsDbFields[6].Field)->AsString.ToInt());
				TmpLogs->IdOperation = LOGS(FDQuery->FieldByName(LogsDbFields[7].Field)->AsString.ToInt());
				TmpLogs->CommandSQL = FDQuery->FieldByName(LogsDbFields[8].Field)->AsString;
				CurrentDate = FDQuery->FieldByName(L"CurrentDate")->AsString;

				VLogs.push_back(TmpLogs);
				LastLogId = TmpLogs->id;

				CountLoadedRows++;

				FDQuery->Next();
			}
			FDQuery->Close();

			bSuccess = true;

	   } catch (...) {
			if(Application->MessageBox(L"Error MySQL Load Logs", uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}

	TBaseData::TimerSyncRestore();

	return CountLoadedRows;
}
//---------------------------------------------------------------------------
void __fastcall TLogs::GetLastAccess(TMyFDQuery *FDQuery)
{
	UnicodeString uTmp;
	uTmp.sprintf(L"Select LastAccess from Logs where id in (%s);", uRefreshes.w_str());

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;

	TBaseData::TimerSyncDisable();

	int Counter = 0;

	while(!bSuccess) {
		try {
			FDQuery->Open();
            FDQuery->FetchAll();

			while (!FDQuery->Eof) {

				VLogsData[VRefreshIndexLastAccess[Counter]]->LastAccess = FDQuery->FieldByName(L"LastAccess")->AsString;
				VLogsData[VRefreshIndexLastAccess[Counter]]->bRefreshLastAccess = false;
				Counter++;

				FDQuery->Next();
			}
			FDQuery->Close();

			bSuccess = true;

	   } catch (...) {
			if(Application->MessageBox(L"Error MySQL Load Logs", uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}

	TBaseData::TimerSyncRestore();
}
//---------------------------------------------------------------------------
void __fastcall TLogs::ParseLogs(void)
{
	int iFind;
	unsigned CountLogs = VLogs.size();

	for(unsigned i = LastParseIndex; i < CountLogs; i++) {
		if(VLogs[i]->IdOperation == LOGS::LG_CONNECT) {
			TLogData *TmpLogData = new TLogData();

			TmpLogData->ConnectedId = VLogs[i]->ConnectedId;
			TmpLogData->IdWorker = VLogs[i]->IdWorker;
			TmpLogData->IdShopU = VLogs[i]->IdShop;
			TmpLogData->StartDate = VLogs[i]->DateTime;
			TmpLogData->LastAccess = VLogs[i]->LastAccess;
			TmpLogData->EndDate = VLogs[i]->LastAccess;
			TmpLogData->ConnectStatus = true;
			TmpLogData->ExitStatus = MEXIT::UNDEFINE;

			VLogsData.push_back(TmpLogData);
		} else {
			iFind = GetLogDataByConnectedId(VLogs[i]->ConnectedId);

			if(iFind != -1) {
				VLogsData[iFind]->LastAccess = VLogs[i]->LastAccess;

				if(VLogs[i]->IdOperation == LOGS::LG_DISCONNECT) {
					VLogsData[iFind]->EndDate = VLogs[i]->LastAccess;
					VLogsData[iFind]->ConnectStatus = false;
					VLogsData[iFind]->ExitStatus = MEXIT::NORMAL;
				} else {
					TLogDetails *TmpLogDetails = new TLogDetails();

					TmpLogDetails->DateTime = VLogs[i]->DateTime;
					TmpLogDetails->IdTable = VLogs[i]->IdTable;
					TmpLogDetails->IdOperation = VLogs[i]->IdOperation;
					TmpLogDetails->CommandSQL = VLogs[i]->CommandSQL;

					VLogsData[iFind]->VLogDetails.push_back(TmpLogDetails);
				}
			}
		}
	}
	LastParseIndex = CountLogs;
}
//---------------------------------------------------------------------------
void __fastcall TLogs::CheckAbnormalExit(void)
{
	for(unsigned i = 0; i < VLogsData.size(); i++) {

		if(VLogsData[i]->ConnectStatus) {
			INT64 Interval = MilliSecondsBetween(CurrentDate, VLogsData[i]->LastAccess);

			if(Interval > INT64(FormShop->TimerSync->Interval * 5)) {
				VLogsData[i]->ConnectStatus = false;
				VLogsData[i]->ExitStatus = MEXIT::ABNORMAL;
			}
		}
	}
}
//---------------------------------------------------------------------------
int __fastcall TLogs::SetFlagRefreshLastAccess(void)
{
	int CountSetFlags = 0;

	VRefreshIndexLastAccess.clear();
	uRefreshes.SetLength(0);

	for(unsigned i = 0; i < VLogsData.size(); i++) {
		if(VLogsData[i]->ConnectStatus) {
			VLogsData[i]->bRefreshLastAccess = true;
			VRefreshIndexLastAccess.push_back(i);
			uRefreshes += UnicodeString(VLogsData[i]->ConnectedId) + L", ";

			CountSetFlags++;
		}
	}
	if(uRefreshes.Length() > 0) {
		uRefreshes.SetLength(uRefreshes.Length() - 2);
	}

	return CountSetFlags;
}
//---------------------------------------------------------------------------
int __fastcall TLogs::GetLogDataByConnectedId(int id)
{
	for(unsigned i=0; i < VLogsData.size(); i++) {
		if(VLogsData[i]->ConnectedId == id) {
			return i;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------

