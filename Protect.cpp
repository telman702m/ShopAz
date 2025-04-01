//---------------------------------------------------------------------------
#pragma hdrstop

#include "Protect.h"
#include "Shop.h"
#include "Product.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

extern bool bViewGaala;

const wchar_t *TMT = L"ntkmv7ktcz26";
bool bInternet = true;

//---------------------------------------------------------------------------
__fastcall TProtect::TProtect(int x)
{
	uRegisterPath = L"Software\\Shop\\Gaala";

	myReg = NULL;
	myReg = new TRegistry;
	myReg->RootKey = HKEY_CURRENT_USER;

	StrStream = NULL;
	StrStream = new TStringStream();
	uServerInfo = L"";

	MyHTTPS = NULL;
	MyHTTPS = new TMyHTTPS(FormShop);

	CurDate = CurDate.CurrentDate();
}

//---------------------------------------------------------------------------
__fastcall TProtect::~TProtect(void)
{
	if(myReg != NULL) {
		delete myReg;
	}

	if(StrStream != NULL) {
		delete StrStream;
	}

	if(MyHTTPS != NULL) {
		delete MyHTTPS;
	}

    uTmp = L"";
}

//---------------------------------------------------------------------------
bool __fastcall TProtect::Gaala(void)
{
	//  Read data from register
	try {
		if(myReg->OpenKeyReadOnly(uRegisterPath)) {
			// Read Length of Path for Remote folder on Server
			if(myReg->ValueExists(L"LPTH")) {
				LenPath = myReg->ReadInteger(L"LPTH");
			} else {
				LenPath = 0;
			}
			// Read String of Path for Remote folder on Server
			if(myReg->ValueExists(L"PTH")) {
				myReg->ReadBinaryData(L"PTH", wPath, 2*LenPath);
				wPath[LenPath] = 0;
			} else {
				wPath[0] = 0;
			}
			// Read Licensiya Date
			if(myReg->ValueExists(L"LCDT")) {
				myReg->ReadBinaryData(L"LCDT", wDate, 20);
				wDate[10] = 0;
			} else {
				wDate[0] = 0;
			}
		} else {
			Application->MessageBox(L"Can not open key from registry.", L"Error", MB_OK);
			return false;
		}
		myReg->CloseKey();
	} catch (...) {
		Application->MessageBox(L"Register error", L"Warning", MB_OK);
		myReg->CloseKey();
		return false;
	}

    // Check Internet connection and read Licensia date
	UnicodeString uDate = Decode(wDate, 10);
	while(true) {
		if(bInternet && ReadFromServer()) {
			Code(LicensDate.FormatString(L"dd.mm.yyyy"), wDate);
			WriteDateToRg(wDate);
			if(CurDate < LicensDate) {
//				FormShop->MyConnection1->Password = L"azeriland";   // Set valid password for connect to DB
				FormShop->FDConnection1->Params->Password = L"tshop123";    // Set valid password for connect to DB
//				Product::ProdDbFields[9][0] = L"SellingPrice1";     // Set valid field name for DB Product
				return true;
			} else {
				Application->MessageBox(L"The license is not valid!\nRefer to developers.", L"Warning", MB_OK);
				return false;
			}
		} else {
			if(!ConvertStringToDate(uDate)) {
				return false;
			}
			if(CurDate < LicensDate) {
				FormShop->FDConnection1->Params->Password = L"azeriland";   // Set valid password for connect to DB
//				TProduct::ProductDbFields[9][0] = L"SellingPrice1";     // Set valid field name for DB TProduct
				return true;
			} else {
				if(Application->MessageBox(L"The license has expired!\nCheck the Internet connection to connect to the server.", L"Warning", MB_YESNO) == IDNO) {
					break;
				} else {
                    bInternet = true;
                }
			}
		}
	}
	return false;
}

//---------------------------------------------------------------------------
bool __fastcall TProtect::ReadFromServer(void)
{
	try {
/*		if(MyHTTPS->IdHTTP1->Connected()) {
			MyHTTPS->IdHTTP1->Disconnect();
		}*/
		UnicodeString URL_DOWNLOAD = Decode(wPath, LenPath/2);
//		URL_DOWNLOAD = L"https://azintelm.az/TShop/TelmanTest";
		if(bViewGaala) {
			uTmp += L"wPath = ";
			uTmp += wPath;
			uTmp += L"\n";
		}


		MyHTTPS->IdHTTP1->Get(URL_DOWNLOAD, StrStream);
		MyHTTPS->IdHTTP1->Disconnect();

	} catch (EIdSocketError &e1) {
		if(IsDebuggerPresent()) {
			Application->MessageBox(e1.ToString().w_str(), L"Error", MB_OK);
		}
		return false;
	} catch (EIdHTTPProtocolException &e2) {
		Application->MessageBox(e2.ToString().w_str(), L"Error", MB_OK);
		return false;
	} catch (...) {
		Application->MessageBox(L"Unknown error on read from server", L"Error", MB_OK);
		return false;
	}

	uServerInfo = StrStream->DataString;
	if(!ConvertStringToDate(uServerInfo)) {
		return false;
	}

	ParseForMySQL(uServerInfo);

	if(bViewGaala) {
		UnicodeString uprn;
		for (int i = 0; i < 6; i++) {
			uTmp += uprn.sprintf(L"wParams[%d] = %s\n", i, wParams[i]);
		}

		ShowMessage(uTmp);
	}

	return true;
}

//---------------------------------------------------------------------------
bool __fastcall TProtect::ParseForMySQL(UnicodeString uStr)
{
	int Length = uStr.Length();
	wchar_t *wStr = uStr.w_str();

	int ip = 0;
	int iLast = 0;
	for (int i = 0; i < Length; i++) {
		if(wStr[i] == 0x0a) {
			wParams[ip++] = wStr + iLast;
			wStr[i] = 0;
			iLast = i + 1;
		}
	}

	return true;
}

//---------------------------------------------------------------------------
bool __fastcall TProtect::ConvertStringToDate(UnicodeString uStrDate)
{
	try {
		int LicensDay = uStrDate.SubString(1, 2).ToInt();
		int LicensMonth = uStrDate.SubString(4, 2).ToInt();
		int LicensYear = uStrDate.SubString(7, 4).ToInt();
		LicensDate = EncodeDate(LicensYear, LicensMonth, LicensDay);
//	} catch (EConvertError eConv) {
//		Application->MessageBoxA(L"Ошибка конвертации в число", L"Error", MB_OK);
//		return false;
	} catch (...) {
		Application->MessageBox(L"Unknow error", L"Error", MB_OK);
		return false;
	}

   return true;
}

//---------------------------------------------------------------------------
void __fastcall TProtect::Code(UnicodeString uStr, wchar_t *wStr)
{
	int j = 0;
	unsigned k = 0;
	int iLen = uStr.Length();

	while(j < iLen) {
		wStr[j] = uStr.w_str()[j] ^ TMT[k++];
		if(!(k < wcslen(TMT))) {
			k = 0;
		}
		j++;
	}
	wStr[j] = 0;
}

//---------------------------------------------------------------------------
UnicodeString __fastcall TProtect::Decode(wchar_t *wStr, int Len)
{
	int j = 0;
	unsigned k = 0;

	while(j < Len) {
		wStr[j] ^= TMT[k++];
		if(!(k < wcslen(TMT))) {
			k = 0;
		}
		j++;
	}
	wStr[j] = 0;
	return wStr;
}

//---------------------------------------------------------------------------
bool __fastcall TProtect::WriteDateToRg(wchar_t *wDate)
{
	myReg->Access = KEY_ALL_ACCESS;

	if(myReg->OpenKey(uRegisterPath, false)) {
		myReg->WriteBinaryData(L"LCDT", wDate, 20);
		myReg->CloseKey();
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------

