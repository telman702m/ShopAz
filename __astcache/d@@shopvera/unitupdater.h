//---------------------------------------------------------------------------
#ifndef UnitUpdaterH
#define UnitUpdaterH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "Declaration.h"
#include "TMyHTTPS.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.IdAntiFreeze.hpp>
#include <IdBaseComponent.hpp>
#include <IdAntiFreeze.hpp>
#include <IdAntiFreezeBase.hpp>

static const wchar_t *wServerURL = L"https://www.azintelm.az/TShop/";
static const wchar_t *wServerUpdateFileName = L"Update.txt";
//---------------------------------------------------------------------------
class TFormUpdate : public TForm
{
__published:	// IDE-managed Components
	TIdAntiFreeze *IdAntiFreeze1;
	TProgressBar *ProgressBar1;
	TLabel *LabelInfo;
	TButton *ButtonUpdate;
	TButton *ButtonCancel;

	bool __fastcall CheckUpdate(void);
	void __fastcall DownloadUpdateInfo(void);
	void __fastcall DownloadFile(UnicodeString uFileName);
	void __fastcall IdHTTP1WorkBegin(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCountMax);
	void __fastcall IdHTTP1Work(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCount);

	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ButtonUpdateClick(TObject *Sender);
	void __fastcall ButtonCancelClick(TObject *Sender);
	AnsiString __fastcall GetParameterFromSList(AnsiString Name);
	void __fastcall SetLanguage(void);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
	void __fastcall ParseProductVersion(wchar_t *wStr, TProductVersion *ProductVersion);
	bool __fastcall CheckIsNewVersion(void);

public:		// User declarations
	__fastcall TFormUpdate(TComponent* Owner);

	bool bRestart;
//	TIdHTTP *IdHTTP1;
	TMyHTTPS *MyHTTPS;

	TProductVersion Version;
	TProductVersion VersionNew;
	TSVersion UpdateVersion;
	TStringList *StringList;

};
//---------------------------------------------------------------------------
extern PACKAGE TFormUpdate *FormUpdate;
//---------------------------------------------------------------------------
#endif
