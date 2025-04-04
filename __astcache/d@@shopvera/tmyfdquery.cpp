//---------------------------------------------------------------------------
#pragma hdrstop

#include <vcl.h>
#include "TMyFDQuery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TMyFDQuery::TMyFDQuery(TComponent* Owner)
	: TFDQuery(Owner)
{

}
//---------------------------------------------------------------------------
int __fastcall TMyFDQuery::MyInsert(const wchar_t *TableName, const wchar_t *AutoIncrementName, TFieldsValues *FieldsValues, const int Count)
{
	UnicodeString uTmp;

	SQL->Text = uTmp.sprintf(L"select max(%ls) from %ls", AutoIncrementName, TableName);
	Open();
	int InsertId = Fields->Fields[0]->AsInteger + 1;
	Close();

	bool bSuccess = false;
	int CountAttempt = 0;

	UnicodeString uSQL;
	while(!bSuccess && CountAttempt < MAX_COUNT_ATTEMPT) {
		uSQL = uTmp.sprintf(L"Insert Into %ls (%ls,", TableName, AutoIncrementName);

		for (int i = 0; i < Count; i++) {
			uSQL += FieldsValues[i].Field;
			if(i != Count - 1) {
				uSQL += L",";
			}
		}
		uSQL += uTmp.sprintf(L") Values ('%d',", InsertId);
		for (int i = 0; i < Count; i++) {

			if(i != Count - 1) {
				uSQL += uTmp.sprintf(L"'%ls',", FieldsValues[i].Value);
			} else {
				uSQL += uTmp.sprintf(L"'%ls')", FieldsValues[i].Value);
			}
		}

		SQL->Text = uSQL;

		try {
			Execute();
			bSuccess = true;
		} catch (...) {
			bSuccess = false;
			ShowMessage(SQL->Text);
			InsertId++;
			CountAttempt++;
		}
	}

	if(bSuccess) return InsertId;
    else return -1;
}
//---------------------------------------------------------------------------
int __fastcall TMyFDQuery::MyInsert2(const wchar_t *TableName, const wchar_t *AutoIncrementName, TFieldsValues *FieldsValues, const int Count)
{
	UnicodeString uTmp;

	SQL->Text = uTmp.sprintf(L"select max(%ls) from %ls", AutoIncrementName, TableName);
	Open();
	int InsertId = Fields->Fields[0]->AsInteger + 1;
	Close();

	bool bSuccess = false;
	int CountAttempt = 0;

	UnicodeString uSQL;
	wchar_t wt;

	while(!bSuccess && CountAttempt < MAX_COUNT_ATTEMPT) {
		uSQL = uTmp.sprintf(L"Insert Into %ls (%ls,", TableName, AutoIncrementName);

		for (int i = 0; i < Count; i++) {
			uSQL += FieldsValues[i].Field;
			if(i != Count - 1) {
				uSQL += L",";
			}
		}
		uSQL += uTmp.sprintf(L") Values ('%d',", InsertId);

		for (int i = 0; i < Count; i++) {
			if(wcscmp(FieldsValues[i].Value, L"current_timestamp()") == 0) {
				wt = L' ';
			} else {
                wt = L'\'';
			}

			if(i != Count - 1) {
				uSQL += uTmp.sprintf(L"%c%ls%c,", wt, FieldsValues[i].Value, wt);
			} else {
				uSQL += uTmp.sprintf(L"%c%ls%c)", wt, FieldsValues[i].Value, wt);
			}
		}

		SQL->Text = uSQL;

		try {
			Execute();
			bSuccess = true;
		} catch (...) {
			bSuccess = false;
			ShowMessage(SQL->Text);
			InsertId++;
			CountAttempt++;
		}
	}

	if(bSuccess) return InsertId;
    else return -1;
}
//---------------------------------------------------------------------------


