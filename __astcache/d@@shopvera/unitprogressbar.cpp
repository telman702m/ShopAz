//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Declaration.h"
#include "UnitProgressBar.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormProgressBar *FormProgressBar;
//---------------------------------------------------------------------------
__fastcall TFormProgressBar::TFormProgressBar(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormProgressBar::FormCreate(TObject *Sender)
{
	SetLanguage();
}
//---------------------------------------------------------------------------
void __fastcall TFormProgressBar::SetLanguage(void)
{
	const wchar_t *wFormCaptions[] = {L"Загрузка с Базы Данных", L"Məlumat Bazadan yüklənmə"};
	Caption = wFormCaptions[iLang];
}
//---------------------------------------------------------------------------

