//---------------------------------------------------------------------------
#pragma hdrstop

#include <typeinfo>

#include "Shop.h"
#include "TBaseData.h"
#include "Synchronize.h"
#include "TUtills.h"
#include "Buyer.h"
#include "Product.h"
#include "MoveProduct.h"
#include "Provisioner.h"
#include "SelectProduct.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TDateTime TBaseData::MaxUpdateDate;
char* TBaseData::pws[];
wchar_t* TBaseData::wpws[];
char* TBaseData::FileBuffer = NULL;
wchar_t* TBaseData::WFileBuffer = NULL;
unsigned long TBaseData::Offset;
unsigned long TBaseData::FileSize = 0;
bool TBaseData::bTimerSync = false;
//---------------------------------------------------------------------------
__fastcall TBaseData::TBaseData(void)
{
	VBaseData = NULL;
	id = -1;
	bDeleted = false;
}
//---------------------------------------------------------------------------
__fastcall TBaseData::TBaseData(const TBaseData &BaseData)
{
	id = BaseData.id;
	VBaseData = BaseData.VBaseData;
	bDeleted = BaseData.bDeleted;
}
//---------------------------------------------------------------------------
__fastcall TBaseData::~TBaseData(void)
{
//
}
//---------------------------------------------------------------------------
bool __fastcall TBaseData::GetFieldsFromDB(TMyFDQuery *FDQuery, const wchar_t *NameTableDB, ppTDescFields &DescFields, int &CountFields)
{
	UnicodeString uTmp;

	FDQuery->SQL->Text = uTmp.sprintf(L"desc %ls", NameTableDB);
//	FDQuery->SQL->Text += NameTableDB;
	FDQuery->Open();

	CountFields = FDQuery->RecordCount;

	if(CountFields > 0) {
		DescFields = new TDescFields*[CountFields];
		for (int i = 0; i < CountFields; i++) {
			DescFields[i] = new TDescFields;
		}
	} else {
        return false;
    }

	int size;
	int ip = 0;

	try {
		while (!FDQuery->Eof) {
			size = FDQuery->FieldByName(L"Field")->AsString.Length();
			DescFields[ip]->Field = new wchar_t[size + 1];
			wcscpy(DescFields[ip]->Field, FDQuery->FieldByName(L"Field")->AsString.w_str());
			DescFields[ip]->Field[size] = 0;

			size = FDQuery->FieldByName(L"Type")->AsString.Length();
			DescFields[ip]->Type = new wchar_t[size + 1];
			wcscpy(DescFields[ip]->Type, FDQuery->FieldByName(L"Type")->AsString.w_str());
			DescFields[ip]->Type[size] = 0;

			size = FDQuery->FieldByName(L"Null")->AsString.Length();
			DescFields[ip]->Null = new wchar_t[size + 1];
			wcscpy(DescFields[ip]->Null, FDQuery->FieldByName(L"Null")->AsString.w_str());
			DescFields[ip]->Null[size] = 0;

			size = FDQuery->FieldByName(L"Key")->AsString.Length();
			DescFields[ip]->Key = new wchar_t[size + 1];
			wcscpy(DescFields[ip]->Key, FDQuery->FieldByName(L"Key")->AsString.w_str());
			DescFields[ip]->Key[size] = 0;

			size = FDQuery->FieldByName(L"Default")->AsString.Length();
			DescFields[ip]->Default = new wchar_t[size + 1];
			wcscpy(DescFields[ip]->Default, FDQuery->FieldByName(L"Default")->AsString.w_str());
			DescFields[ip]->Default[size] = 0;

			size = FDQuery->FieldByName(L"Extra")->AsString.Length();
			DescFields[ip]->Extra = new wchar_t[size + 1];
			wcscpy(DescFields[ip]->Extra, FDQuery->FieldByName(L"Extra")->AsString.w_str());
			DescFields[ip]->Extra[size] = 0;

			ip++;
			FDQuery->Next();
		}

	} catch (...) {
		return false;
	}
	FDQuery->Close();

	if(CountFields != ip) {
		ShowMessage(L"Error CountFields != ip");
        return false;
    }

	return true;
}

//---------------------------------------------------------------------------
void __fastcall TBaseData::ShowFields(TDescFields **DescFields, int CountFields)
{
	TStringList *SList;
	SList = new TStringList;

	UnicodeString uTmp = L"Field\tType\tNull\tKey\tDefault\tExtra";
	SList->Add(uTmp);

	for (int i = 0; i < CountFields; i++) {
		uTmp = DescFields[i]->Field;
		uTmp += L"\t";
		uTmp += DescFields[i]->Type;
		uTmp += L"\t";
		uTmp += DescFields[i]->Null;
		uTmp += L"\t";
		uTmp += DescFields[i]->Key;
		uTmp += L"\t";
		uTmp += DescFields[i]->Default;
		uTmp += L"\t";
		uTmp += DescFields[i]->Extra;
		SList->Add(uTmp);
	}

	SList->SaveToFile(ExtractFilePath(Application->ExeName) + "Fields.txt");
    delete SList;
}

//---------------------------------------------------------------------------
const TBaseData& __fastcall TBaseData::operator=(const TBaseData &BaseData)
{
	id = BaseData.id;
	VBaseData = BaseData.VBaseData;
	bDeleted = BaseData.bDeleted;

	return *this;
}
//---------------------------------------------------------------------------
void __fastcall TBaseData::TimerSyncRestore(void)
{
	FormShop->TimerSync->Enabled = bTimerSync;
}
//---------------------------------------------------------------------------
void __fastcall TBaseData::TimerSyncDisable(void)
{
	FormShop->TimerSync->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TBaseData::SetTimerSync(bool bStatus)
{
	bTimerSync = bStatus;
	FormShop->TimerSync->Enabled = bTimerSync;
}
//---------------------------------------------------------------------------
bool __fastcall TBaseData::LoadFileToBuffer(char *FileName)
{
	FILE *fs = fopen(FileName, "rb");
	if(fs == NULL) {
		return false;
	}
	if(fseek(fs, 0, SEEK_END) != 0) {
		fclose(fs);
		return false;
	}
	FileSize = ftell(fs);
	if(long(FileSize) == -1L) {
		fclose(fs);
		return false;
	}

	FileBuffer = new char[FileSize + 1];
	if(FileBuffer == NULL) {
		fclose(fs);
		return false;
	}

	fseek(fs, 0, SEEK_SET);
	if(fread(FileBuffer, sizeof(char), FileSize, fs) != FileSize) {
		fclose(fs);
		return false;
	}
	fclose(fs);

	Offset = 0;
	UnicodeString uTmp;

	Offset = TUtills::ParseString(FileBuffer, pws, 1, 16);
	if(Offset == 0) {
		delete FileBuffer;
		FileBuffer = NULL;
		return false;
	}
	uTmp = pws[0];
	try {
		MaxUpdateDate = StrToDate(uTmp, FSet);
	} catch (...) {
		return false;
	}

	MaxUpdateDate--;

	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TBaseData::LoadFileToWBuffer(char *FileName)
{
	FILE *fs = fopen(FileName, "rb");
	if(fs == NULL) {
		return false;
	}
	if(fseek(fs, 0, SEEK_END) != 0) {
		fclose(fs);
		return false;
	}
	FileSize = ftell(fs) / 2;
	if(long(FileSize) == -1L) {
		fclose(fs);
		return false;
	}

	WFileBuffer = new wchar_t[FileSize + 1];
	if(WFileBuffer == NULL) {
		fclose(fs);
		return false;
	}

	fseek(fs, 0, SEEK_SET);
	if(fread(WFileBuffer, sizeof(wchar_t), FileSize, fs) != FileSize) {
		fclose(fs);
		return false;
	}
	fclose(fs);

	Offset = 0;
	UnicodeString uTmp;

	Offset = TUtills::ParseWstring(WFileBuffer, wpws, 1, 16);
	if(Offset == 0) {
		delete WFileBuffer;
		WFileBuffer = NULL;
		return false;
	}
	uTmp = wpws[0];
	try {
		MaxUpdateDate = StrToDate(uTmp, FSet);
	} catch (...) {
		return false;
	}

	MaxUpdateDate--;

	return true;
}

//---------------------------------------------------------------------------
int __fastcall TBaseData::GetArrayIndexById(vector <TBaseData*> *VBaseData, int id, bool bInsert)
{
	unsigned idC, idMin = -1, idMax = VBaseData->size();
	int fid;

	if((*VBaseData)[idMin + 1]->id == id) {
		return idMin + 1;
	}
	if((*VBaseData)[idMax - 1]->id == id) {
		return idMax - 1;
	}

	while((idMax - idMin) > 1) {
		idC = (idMin + idMax) / 2;
		fid = (*VBaseData)[idC]->id;

		if(fid == id) {
			return idC;
		} else if(fid > id) {
			idMax = idC;
		} else {
			idMin = idC;
		}
	}

	if(bInsert) {
		return idMax;
	} else {
		return -1;
	}
}
//---------------------------------------------------------------------------
int __fastcall TBaseData::GetArrayIndexById(bool bInsert)
{
	vector <TBaseData*> vAliasBaseData = *VBaseData;

	unsigned idC, idMin = -1, idMax = VBaseData->size();
	int fid;

	if(idMax > 0) {
		if((*VBaseData)[idMin + 1]->id == id) {
			return idMin + 1;
		}
		if((*VBaseData)[idMax - 1]->id == id) {
			return idMax - 1;
		}

		while((idMax - idMin) > 1) {
			idC = (idMin + idMax) / 2;
			fid = (*VBaseData)[idC]->id;

			if(fid == id) {
				return idC;
			} else if(fid > id) {
				idMax = idC;
			} else {
				idMin = idC;
			}
		}
	}

	if(bInsert) {
		return idMax;
	} else {
		return -1;
	}
}
//---------------------------------------------------------------------------
TBaseData* __fastcall TBaseData::GetObjectById(void)
{
	int index = GetArrayIndexById();

	if(index == -1) {
		return NULL;
	} else {
		return (*VBaseData)[index];
	}
}
//---------------------------------------------------------------------------
TBaseData* __fastcall TBaseData::GetObjectById(vector <TBaseData*> *VBaseData, int id)
{
	int index = GetArrayIndexById(VBaseData, id);

	if(index == -1) {
		return NULL;
	} else {
		return (*VBaseData)[index];
	}
}
//---------------------------------------------------------------------------
/*UnicodeString __fastcall TBaseData::FormationInsertString(wchar_t *TableName, TDescFields **DescFields, UnicodeString DbData[], int CountDbFields)
{
	UnicodeString uQuery;
	uQuery = uQuery.sprintf(L"Insert Into %ls (", TableName);

	for(int i = 1; i < CountDbFields - 3; i++) {
		uQuery += DescFields[i]->Field;
		uQuery += uInsert1;
	}
	uQuery += DescFields[CountDbFields - 3]->Field;
	uQuery += L") Values ('";

	for(int i = 1; i < CountDbFields - 3; i++) {
		uQuery += DbData[i];
		uQuery += uInsert2;
	}
	uQuery += DbData[CountDbFields - 3];
	uQuery += L"')";

	return uQuery;
}*/
//---------------------------------------------------------------------------
UnicodeString __fastcall TBaseData::FormationUpdateString(const wchar_t *TableName, TFieldsValues *FieldsValues, int Count)
{
	UnicodeString uQuery;
	uQuery = uQuery.sprintf(L"Update %ls Set ", TableName);

	for(int i = 1; i < Count - 1; i++) {
		uQuery += FieldsValues[i].Field;
		uQuery += uUpdate1;
		uQuery += FieldsValues[i].Value;
		uQuery += uUpdate2;
	}
	uQuery += FieldsValues[Count - 1].Field;
	uQuery += uUpdate1;
	uQuery += FieldsValues[Count - 1].Value;
	uQuery += L"' Where id = ";
	uQuery += id;

	return uQuery;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TBaseData::FormationDeleteString(const wchar_t *TableName, wchar_t *DbField)
{
	UnicodeString uQuery;
	uQuery = uQuery.sprintf(L"Update %ls Set ", TableName);

	uQuery += DbField;
	uQuery += L"='1'";
	uQuery += L" Where id = ";
	uQuery += id;

	return uQuery;
}
//---------------------------------------------------------------------------
bool __fastcall TBaseData::ExecOnlySQL(TMyFDQuery *FDQuery, UnicodeString &QuerySQL)
{
	FDQuery->SQL->Text = QuerySQL;

	while(true) {
		try {
			FDQuery->Execute();
			return true;

	   } catch (...) {
			if(Application->MessageBox(L"Error on ExecOnlySQL\n Retry?", uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
	   }
	}
}
//---------------------------------------------------------------------------
void __fastcall TBaseData::ExecSQL(TMyFDQuery *FDQuery, UnicodeString &QuerySQL, const wchar_t *TableName, TabDB TypeTableDB, TRecordType RecordType, LOGS Logs)
{
	vector <TBaseData*> vAliasBaseData = *VBaseData;

	TimerSyncDisable();

//	FDQuery->SQL->Text = QuerySQL;
//	bool bSuccess = ExecOnlySQL(FDQuery, QuerySQL);

	int idFind;

	switch(RecordType) {
		case TRecordType::RT_INSERT:
			ShowMessage(L"Wrond use Insert operation in TbaseData!");
			break;
		case TRecordType::RT_UPDATE:
			idFind = GetArrayIndexById();
			if(idFind != -1) {
				(*VBaseData)[idFind] = this;
			} else {
				ShowMessage(L"Error!!! Not found id in VBaseData!");
			}
			break;
		case TRecordType::RT_DELETE:
			idFind = GetArrayIndexById();
			if(idFind != -1) {
				(*VBaseData)[idFind]->bDeleted = true;
			} else {
				ShowMessage(L"Error!!! Not found id in VBaseData!");
			}
			break;
		default:
			break;
	}

	bool bSuccess = ExecOnlySQL(FDQuery, QuerySQL);

/*	bool bSuccess = false;
	while(!bSuccess) {
		try {
			FDQuery->Execute();
			int idFind;

			switch(RecordType) {
				case TRecordType::RT_INSERT:
					ShowMessage(L"Wrond use Insert operation in TbaseData!");
//					id = FDQuery->InsertId;
//					VBaseData->push_back(this);
					break;
				case TRecordType::RT_UPDATE:
					idFind = GetArrayIndexById();
					if(idFind != -1) {
						(*VBaseData)[idFind] = this;
					} else {
						// error
					}
					break;
				case TRecordType::RT_DELETE:
					idFind = GetArrayIndexById();
					if(idFind != -1) {
//						VBaseData->erase(VBaseData->begin() + idFind);
						(*VBaseData)[idFind]->bDeleted = true;
					} else {
						// error
					}
					break;
				default:
					break;
			}

			bSuccess = true;

	   } catch (...) {
			UnicodeString uTmp = uTmp.sprintf(wLostConnection[iLang], wOperationName[RecordType], TableName);
			if(Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}*/
	if(RecordType != TRecordType::RT_UNDEF) {
		TSynchronize::InsertToDb(FDQuery, TypeTableDB, id, RecordType);
	}

	if(Logs != LOGS::LG_UNDEF) {
		FormShop->CurrentLog->Set(TypeTableDB, Logs, QuerySQL);
		FormShop->CurrentLog->InsertToDb(FDQuery);
	}

	TimerSyncRestore();
}
//---------------------------------------------------------------------------
void __fastcall TBaseData::ExecSQL(TMyFDQuery *FDQuery, TFieldsValues *FieldsValues, int Count, const wchar_t *TableName, wchar_t *AutoIncrement, TabDB TypeTableDB)
{
	TimerSyncDisable();

	bool bSuccess = false;
	while(!bSuccess) {
		try {
			id = FDQuery->MyInsert(TableName, AutoIncrement, FieldsValues, Count);
			VBaseData->push_back(this);

			bSuccess = true;

	   } catch (...) {
			UnicodeString uTmp = uTmp.sprintf(wLostConnection[iLang], wOperationName[TRecordType::RT_INSERT], TableName);
			if(Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}

	TSynchronize::InsertToDb(FDQuery, TypeTableDB, id, TRecordType::RT_INSERT);

	FormShop->CurrentLog->Set(TypeTableDB, LOGS::LG_INSERT, FDQuery->SQL->Text);
	FormShop->CurrentLog->InsertToDb(FDQuery);

	TimerSyncRestore();
}
//---------------------------------------------------------------------------
bool __fastcall TBaseData::LoadRecord(TMyFDQuery *FDQuery, const wchar_t *TableName, TDescFields **DescFields, UnicodeString DbData[], int CountDbFields)
{
	UnicodeString uQuery;
	uQuery = uQuery.sprintf(L"Select * from %ls where id = %d", TableName, id);
	FDQuery->SQL->Text = uQuery;

	bool bSuccess = false;

	while(!bSuccess) {
		try {
//			FDQuery->Execute();
			FDQuery->Open();

			if(FDQuery->RecordCount == 1) {
				for(int i = 0; i < CountDbFields - 2; i++) {
					DbData[i] = FDQuery->FieldByName(DescFields[i]->Field)->AsString;
				}
			} else {
				return false;
			}
			bSuccess = true;
	   } catch (...) {
			UnicodeString uTmp = uTmp.sprintf(wLostConnection[iLang], L"Select", TableName);
			if(Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TBaseData::ApplyBaseSyncronize(TMyFDQuery *FDQuery, TSynchronize *SyncData, TFormParent *FormParent)
{
	bool bCreateObject = false;
	int indVec;
	id = SyncData->idRecord;

	switch(SyncData->RecordType) {
		case TRecordType::RT_INSERT:

			if(LoadRecordId(FDQuery)) {
				int InsertIndex = GetArrayIndexById(true);
				VBaseData->insert(VBaseData->begin()+InsertIndex, this);
				bCreateObject = true;
			}
			break;

		case TRecordType::RT_UPDATE:
			indVec = GetArrayIndexById();

			if(indVec != -1) {
				if(LoadRecordId(FDQuery)) {
					delete (*VBaseData)[indVec];
					(*VBaseData)[indVec] = this;
					bCreateObject = true;
				}
			}
			break;

		case TRecordType::RT_DELETE:
			indVec = GetArrayIndexById();

			if(indVec != -1) {
				CorrectVector(indVec);
				delete (*VBaseData)[indVec];
				VBaseData->erase(VBaseData->begin() + indVec);
			}
			break;
		default:
            break;
	}

	if(FormParent != NULL) {
		FormParent->bListUpdate = true;

		if(FormParent->Showing) {
			FormParent->MyListView->FillList();
		}
	}

	return bCreateObject;
}
//---------------------------------------------------------------------------
void __fastcall TBaseData::CorrectVector(int index)
{
	if(dynamic_cast<TBuyer *>(this)) {
		TypeTable = TabDB::TB_BUYER;
	} else if(dynamic_cast<TProduct *>(this)) {
		TypeTable = TabDB::TB_PROD;
	} else if(dynamic_cast<TProvisioner *>(this)) {
		TypeTable = TabDB::TB_PROVIS;
	} else if(dynamic_cast<TSelectProduct *>(this)) {
		TypeTable = TabDB::TB_SELECTP;

		TSelectProduct *TmpSelectProd = TSelectProduct::VSelectProduct[index];
		int indexMove = GetArrayIndexById((vector <TBaseData*> *)&TMoveProduct::VMoveProduct, TmpSelectProd->idMove);
		if(indexMove != -1) {
			TMoveProduct *TmpMoveProduct = TMoveProduct::VMoveProduct[indexMove];
			for(unsigned i=0; i < TmpMoveProduct->VSelectedProd.size(); i++) {
				if(TmpMoveProduct->VSelectedProd[i]->id == id) {
					TmpMoveProduct->VSelectedProd.erase(TmpMoveProduct->VSelectedProd.begin() + i);
				}
			}
		}
	} else if(dynamic_cast<TMoveProduct *>(this)) {
		TypeTable = TabDB::TB_MOVEP;
	} else {
		TypeTable = TabDB::TB_UNDEF;
	}
}

//---------------------------------------------------------------------------
bool __fastcall TBaseData::CheckSortById(void)
{
	return true;

	UnicodeString uTmp = L"Unknow object";

	int size = VBaseData->size();

//	const char *TypeName = typeid(this).name();

	if(dynamic_cast<TBuyer *>(this)) {
		uTmp = L"Buyer";
	} else if(dynamic_cast<TProduct *>(this)) {
		uTmp = L"Product";
	} else if(dynamic_cast<TProvisioner *>(this)) {
		uTmp = L"Provisioner";
	} else if(dynamic_cast<TSelectProduct *>(this)) {
		uTmp = L"SelectProduct";
	} else if(dynamic_cast<TMoveProduct *>(this)) {
		uTmp = L"MoveProduct";
	} else {
		Application->MessageBox(L"Error on definition type of DataBase when run function CheckSortById", L"Error", MB_OK);
		return false;
	}


	for(int i = 1; i < size; i++) {
		if((*VBaseData)[i]->id <= (*VBaseData)[i-1]->id) {
			UnicodeString uMess;
			uMess = uMess.sprintf(L"Нарушен порядок сортировки для объектов %s", uTmp.w_str());
			Application->MessageBox(uMess.w_str(), L"Error", MB_OK);
			return false;
		}
	}

	return true;
}
//---------------------------------------------------------------------------


