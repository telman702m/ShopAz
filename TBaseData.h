//---------------------------------------------------------------------------
#ifndef TBaseDataH
#define TBaseDataH

#include <vcl.h>
#include <vector>
#include "Declaration.h"
#include "Synchronize.h"
#include "UnitParent.h"
#include "ObjectManager.h"


typedef struct _TDescFields
{
	wchar_t *Field;
	wchar_t *Type;
	wchar_t *Null;
	wchar_t *Key;
	wchar_t *Default;
	wchar_t *Extra;
} TDescFields;

typedef TDescFields** ppTDescFields;

//---------------------------------------------------------------------------
class TBaseData : public TObject
{
private:
	UnicodeString uTmp = L"";

public:
	static char *pws[32];
	static wchar_t *wpws[32];
	static TDateTime MaxUpdateDate;
	static char *FileBuffer;
	static wchar_t *WFileBuffer;
	static unsigned long Offset;
	static unsigned long FileSize;
	static bool bTimerSync;

	static bool __fastcall GetFieldsFromDB(TMyFDQuery *FDQuery, const wchar_t *NameDB, ppTDescFields &DescFields, int &CountFields);
	static void __fastcall ShowFields(TDescFields **DescFields, int CountFields);

	static bool __fastcall LoadFileToBuffer(char *FileName);
	static bool __fastcall LoadFileToWBuffer(char *FileName);
//	static int __fastcall GetArrayIndexById(vector <TBaseData*> *VBaseData, int id, bool bInsert = false);
	static TBaseData* __fastcall GetObjectById(vector <TBaseData*> *VBaseData, int id);
	static void __fastcall TimerSyncRestore(void);
	static void __fastcall TimerSyncDisable(void);
	static void __fastcall SetTimerSync(bool bStatus);

	__fastcall TBaseData(void);
	__fastcall TBaseData(const TBaseData &BaseData);
	__fastcall ~TBaseData(void);

	 const TBaseData& __fastcall operator=(const TBaseData &BaseData);

//	vector <TBaseData*> *VBaseData;
	int id;
	TabDB TypeTable;
    bool bDeleted;

//	int __fastcall GetArrayIndexById(bool bInsert = false);
	TBaseData* __fastcall GetObjectById(void);

//	UnicodeString __fastcall FormationInsertString(wchar_t *TableName, TDescFields **DescFields, UnicodeString DbData[], int CountDbFields);
	UnicodeString __fastcall FormationUpdateString(const wchar_t *TableName, TFieldsValues *FieldsValues, int Count);
	UnicodeString __fastcall FormationDeleteString(const wchar_t *TableName, wchar_t *DbField);

	bool __fastcall ExecOnlySQL(TMyFDQuery *FDQuery, UnicodeString &QuerySQL);
	bool __fastcall LoadRecord(TMyFDQuery *FDQuery, const wchar_t *TableName, TDescFields **DescFields, UnicodeString DbData[], int CountDbFields);
//	bool __fastcall CheckSortById(void);
//	void __fastcall CorrectVector(int index);
	void __fastcall CorrectVector(void);
	virtual bool __fastcall LoadRecordId(TMyFDQuery *FDQuery) = 0;

/*
	void __fastcall ExecSQL(TMyFDQuery *FDQuery, UnicodeString &QuerySQL,
							const wchar_t *TableName, TabDB TypeTableDB,
							TRecordType RecordType, LOGS Logs);

	void __fastcall ExecSQL(TMyFDQuery *FDQuery, TFieldsValues *FieldsValues,
							int Count, const wchar_t *TableName,
							wchar_t *AutoIncrement, TabDB TypeTableDB);

	bool __fastcall ApplyBaseSyncronize(TMyFDQuery *FDQuery, TSynchronize *SyncData, TFormParent *FormParent);
*/


	template <class T>
	void __fastcall ExecSQL_Managed(TMyFDQuery *FDQuery, UnicodeString &QuerySQL,
									const wchar_t *TableName, TabDB TypeTableDB,
									TRecordType RecordType, LOGS Logs);

	template <class T>
	void __fastcall ExecSQL_Managed(TMyFDQuery *FDQuery, TFieldsValues *FieldsValues,
									   int Count, const wchar_t *TableName,
									   wchar_t *AutoIncrement, TabDB TypeTableDB);




	template <class T>
	bool __fastcall ApplyBaseSyncronize_Managed(TMyFDQuery *FDQuery, TSynchronize *SyncData, TFormParent *FormParent);


	template <class T>
	bool __fastcall CheckSortById_Managed(const wchar_t* typeName);

};
#endif
