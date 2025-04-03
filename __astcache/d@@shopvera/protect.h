//---------------------------------------------------------------------------
#ifndef ProtectH
#define ProtectH

#include "Registry.hpp"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "TMyHTTPS.h"

//---------------------------------------------------------------------------
class TProtect : public TObject
{
private:
	UnicodeString uTmp;

	TRegistry *myReg;
	TDateTime CurDate;
	TDateTime LicensDate;

	TMyHTTPS *MyHTTPS;

	TDateTime TmDT;
	int LenPath;
	wchar_t wPath[256];
	wchar_t wDate[16];

	TStringStream *StrStream;
    UnicodeString uRegisterPath;
	UnicodeString uServerInfo;

public:
    wchar_t *wParams[6];

	__fastcall TProtect(int);
	__fastcall ~TProtect(void);

	bool __fastcall Gaala(void);
	bool __fastcall ReadFromServer(void);
	bool __fastcall WriteDateToRg(wchar_t *wDate);
	bool __fastcall ParseForMySQL(UnicodeString uStr);
	bool __fastcall ConvertStringToDate(UnicodeString uStrDate);
	void __fastcall Code(UnicodeString uStr, wchar_t *wStr);
	UnicodeString __fastcall Decode(wchar_t *wStr, int Len);
};

#endif
