//---------------------------------------------------------------------------
#ifndef LogsH
#define LogsH
//---------------------------------------------------------------------------
#include <vector>
//#include "MyDump.hpp"
#include "Declaration.h"
#include "LogsData.h"
#include "TBaseData.h"

const int CountFieldsLog = 9;

//---------------------------------------------------------------------------
class TLogs : public TObject
{
private:

public:
//	static UnicodeString LogsDbFields[CountFieldsLog][2];
	static TDescFields *LogsDbFields;
	static int CountFieldsLog;
	static bool __fastcall Init(TMyFDQuery *FDQuery);
	static void __fastcall ShowFields(void);

	static vector <TLogs*> VLogs;
	static vector <int> VRefreshIndexLastAccess;
	static int LastLogId;
	static unsigned LastParseIndex;
	static vector <TLogData*> VLogsData;
	static UnicodeString uRefreshes;

	static int __fastcall LoadFromDB(TMyFDQuery *FDQuery, int iLastId, TDateTime DateTime1, TDateTime DateTime2);
	static void __fastcall GetCurrentDateFromDB(TMyFDQuery *FDQuery);
	static void __fastcall ParseLogs(void);
	static int __fastcall GetLogDataByConnectedId(int id);
	static void __fastcall CheckAbnormalExit(void);
	static void __fastcall GetLastAccess(TMyFDQuery *FDQuery);
	static int __fastcall SetFlagRefreshLastAccess(void);

	static TDateTime CurrentDate;

	int id;
	int ConnectedId;
	TDateTime DateTime;
	TDateTime LastAccess;
	int IdShop;
	int IdWorker;
	TabDB IdTable;
	LOGS IdOperation;
	UnicodeString CommandSQL;

	// Additional fields

	__fastcall TLogs(void);
//	~TLogs(void);
//	TLogs(const TProduct &Logs);
//	const TLogs& operator=(const TLogs &Logs);
	void __fastcall Clear(void);
	void __fastcall Set(TabDB _IdTable, LOGS _IdOperation, UnicodeString _CommandSQL);

	void __fastcall InsertToDb(TMyFDQuery *FDQuery);
	void __fastcall UpdateToDb(TMyFDQuery *FDQuery);
	void __fastcall UpdateConnectedId(TMyFDQuery *FDQuery);
	void __fastcall DeleteFromDb(TMyFDQuery *FDQuery);
};
#endif
