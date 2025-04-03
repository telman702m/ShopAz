//---------------------------------------------------------------------------
#include <vcl.h>
//#include "System.SysUtils.hpp"

#pragma hdrstop

#include "UnitUpdater.h"
#include "UnitAbout.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wErrorUpdate[] = {
	L"Ошибка в процессе обновленя!\nПроцесс обновления не осуществлен.",
	L"Yenilənmə zamanı səhv baş verdi!\nYenilənmə baş tutmadı."
};
const wchar_t *wNewVersion[] = {
	L"Имеется новая версия (Version %s) программы TShop.\nСкачать и обновить?",
	L"TShop programın yeni versiyası mövcüddür (Version %s).\nYükləmək və yeniləmək?"
};
const wchar_t *wDownloadFile[] = {
	L"Идеи процесс скачивания файла %s",
	L"%s faylın yükləmə prosesi"
};


TFormUpdate *FormUpdate;
//---------------------------------------------------------------------------
__fastcall TFormUpdate::TFormUpdate(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormUpdate::SetLanguage(void)
{
	const wchar_t *wFormCaptions[] = {L"Обновление программы", L"Programin yenilənməsi"};
	Caption = wFormCaptions[iLang];

	const wchar_t *wButtonCaptions[][2] = {
		{L"Обновить сейчас",	L"İndi yenilə"},
		{L"Нет не сейчас",		L"Xeyr, indi lazım deyil"}
	};
	TButton *MyButtons[] = {
		ButtonUpdate,
		ButtonCancel
	};
	for(unsigned i=0; i < sizeof(MyButtons)/sizeof(TButton*); i++) {
		MyButtons[i]->Caption = wButtonCaptions[i][iLang];
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormUpdate::FormCreate(TObject *Sender)
{
	SetLanguage();

	bRestart = false;

	MyHTTPS = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormUpdate::FormShow(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TFormUpdate::DownloadUpdateInfo(void)
{
	UnicodeString URL_DOWNLOAD = wServerURL;
	URL_DOWNLOAD += wServerUpdateFileName;

	TFileStream *FS = new TFileStream(wServerUpdateFileName, fmCreate | fmOpenWrite);

	MyHTTPS->IdHTTP1->Get(URL_DOWNLOAD, FS);
	delete FS;

	StringList = new TStringList;
	StringList->LoadFromFile(wServerUpdateFileName);

	UpdateVersion.FileVersion = GetParameterFromSList(L"Version");
	UpdateVersion.ProductName = GetParameterFromSList(L"ExeFile");
	UpdateVersion.UpdaterName = GetParameterFromSList(L"UpdaterName");

	StringList->Clear();
	UnicodeString uTmp;

	UnicodeString uPathExe = Application->ExeName;
	UnicodeString uWorkDir = ExtractFilePath(uPathExe);
	UnicodeString uExeName = uPathExe.SubString(uWorkDir.Length() + 1, 100);

	StringList->Add(uTmp.sprintf(L"OldExeFileName <%s>", uExeName.w_str()));
	StringList->Add(uTmp.sprintf(L"NewExeFileName <%s>", UpdateVersion.ProductName.w_str()));

	StringList->SaveToFile(L"Updater.txt");
	StringList->Clear();

	delete StringList;
	StringList = NULL;
//	MyHTTPS->IdHTTP1->Disconnect();
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormUpdate::GetParameterFromSList(AnsiString Name)
{
	int i1, i2;
	for(int i=0; i < StringList->Count; i++) {
		if(StringList->Strings[i].Pos(Name) > 0) {
			i1 = StringList->Strings[i].Pos(L"<");
			i2 = StringList->Strings[i].Pos(L">");
			if(i1 > 0 && i2 > 0) {
				return StringList->Strings[i].SubString(i1+1, i2-i1-1);
			}
		}
	}
	return "";
}
//---------------------------------------------------------------------------
void __fastcall TFormUpdate::ParseProductVersion(wchar_t *wStr, TProductVersion *ProductVersion)
{
	int Len = wcslen(wStr);
	wchar_t *wTmp = new wchar_t[Len + 1];
	wcscpy(wTmp, wStr);

	unsigned int *pVer[3] = {&(ProductVersion->AMajor), &(ProductVersion->AMinor), &(ProductVersion->ABuild)};
	int iv = 0;
	int i = 0;
	wchar_t *psz = wTmp;

	while(i < Len) {
		if(wTmp[i] == '.') {
			wTmp[i] = 0;
			*(pVer[iv++]) = _wtoi(psz);

			i++;
			psz = wTmp + i;
		}
		i++;
	}

    delete[] wTmp;
}
//---------------------------------------------------------------------------
bool __fastcall TFormUpdate::CheckIsNewVersion(void)
{
	if(VersionNew.AMajor > Version.AMajor) {
		return true;
	} else if(VersionNew.AMajor == Version.AMajor) {
		if(VersionNew.AMinor > Version.AMinor) {
			return true;
		} else if(VersionNew.AMinor == Version.AMinor) {
			if(VersionNew.ABuild > Version.ABuild) {
				return true;
			}
		}
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall TFormUpdate::CheckUpdate(void)
{
	if(!GetProductVersion(Application->ExeName, Version.AMajor, Version.AMinor, Version.ABuild)) {
		return false;
	}

	UnicodeString uTmp;
	FormAbout->LabelVersion->Caption = uTmp.sprintf(L"Version:  %u.%u.%u", Version.AMajor, Version.AMinor, Version.ABuild);

	MyHTTPS = new TMyHTTPS(FormUpdate);
	DownloadUpdateInfo();

	if(UpdateVersion.FileVersion == "" || UpdateVersion.ProductName == "" || UpdateVersion.UpdaterName == "") {
		Application->MessageBox(wErrorUpdate[iLang], uCaptionError[iLang], MB_OK);
		Close();
	}

	ParseProductVersion(UpdateVersion.FileVersion.w_str(), &VersionNew);

	if(CheckIsNewVersion()) {
		LabelInfo->Caption = uTmp.sprintf(wNewVersion[iLang], UpdateVersion.FileVersion.w_str());
		LabelInfo->Left = (ClientWidth - LabelInfo->Width)/2;

		ShowModal();
	} else {
        Close();
    }

	return false;
}

//---------------------------------------------------------------------------
void __fastcall TFormUpdate::ButtonUpdateClick(TObject *Sender)
{
	ButtonUpdate->Enabled = false;
	ButtonCancel->Enabled = false;

	DownloadFile(UpdateVersion.ProductName);
	DownloadFile(UpdateVersion.UpdaterName);

	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;

//	ShowMessage(L"Now will be Create proccess Updater.exe");
	WinExec(AnsiString(UpdateVersion.UpdaterName).c_str(), SW_SHOW);
//	CreateProcess(UpdateVersion.UpdaterName.w_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi);

	bRestart = true;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormUpdate::ButtonCancelClick(TObject *Sender)
{
	delete MyHTTPS;
    MyHTTPS = NULL;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormUpdate::DownloadFile(UnicodeString uFileName)
{
	UnicodeString uTmp;

	LabelInfo->Caption = uTmp.sprintf(wDownloadFile[iLang], uFileName.w_str());
	LabelInfo->Left = (ClientWidth - LabelInfo->Width)/2;

	UnicodeString URL_DOWNLOAD = wServerURL;
	URL_DOWNLOAD += uFileName;

	TFileStream* FS = new TFileStream(uFileName, fmCreate | fmOpenWrite);

	MyHTTPS->IdHTTP1->OnWorkBegin = IdHTTP1WorkBegin;
	MyHTTPS->IdHTTP1->OnWork = IdHTTP1Work;

	IdAntiFreeze1->Active = true;
	MyHTTPS->IdHTTP1->Get(URL_DOWNLOAD, FS);
	IdAntiFreeze1->Active = false;
	delete FS;

//	IdHTTP1->Disconnect();
//    ShowMessage(L"Download complete");

	MyHTTPS->IdHTTP1->OnWorkBegin = NULL;
	MyHTTPS->IdHTTP1->OnWork = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormUpdate::IdHTTP1WorkBegin(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCountMax)
{
	ProgressBar1->Max = AWorkCountMax;
}
//---------------------------------------------------------------------------
void __fastcall TFormUpdate::IdHTTP1Work(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCount)
{
	ProgressBar1->Position = AWorkCount;
}
//---------------------------------------------------------------------------
void __fastcall TFormUpdate::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete MyHTTPS;
    MyHTTPS = NULL;
}
//---------------------------------------------------------------------------

