//---------------------------------------------------------------------------
#pragma hdrstop

#include "Print.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

long TmPrint::Mdiv = 1000;
TCanvas* TmPrint::Canvas = NULL;
int TmPrint::PgWidth = 0;
int TmPrint::PgHeight = 0;

//---------------------------------------------------------------------------
__fastcall TmPrint::TmPrint(UnicodeString uTxt, UnicodeString FontName, int FontSize, TFontStyles FontStyle)
{
	MyFont = new TFont;

	if(FontName == NULL) {
		MyFont->Name = L"Times New Roman";
	} else {
		MyFont->Name = FontName;
	}

	MyFont->Style = FontStyle;
	MyFont->Size = FontSize;

	SetText(uTxt);

	rc.Left = 0;
	rc.Right = 0;
	rc.Top = 0;
	rc.Bottom = 0;
}
//---------------------------------------------------------------------------
__fastcall TmPrint::~TmPrint(void)
{
    delete MyFont;
}

//---------------------------------------------------------------------------
void __fastcall TmPrint::SetText(UnicodeString uTxt)
{
	uText = uTxt;
	Canvas->Font = MyFont;
	HeightFont = Canvas->TextHeight(L"Ğg");
}

//---------------------------------------------------------------------------
void __fastcall TmPrint::DrawText(int x, int y)
{
	rc.Left = x;
	rc.Top = y;
	DrawTextIn();
}
//---------------------------------------------------------------------------
void __fastcall TmPrint::DrawText(long pcX, int y)
{
	rc.Left = pcX * PgWidth / Mdiv;
	rc.Top = y;
	DrawTextIn();
}
//---------------------------------------------------------------------------
void __fastcall TmPrint::DrawText(int x, long pcY)
{
	rc.Left = x;
	rc.Top = pcY * PgHeight / Mdiv;
	DrawTextIn();
}
//---------------------------------------------------------------------------
void __fastcall TmPrint::DrawText(long pcX, long pcY)
{
	rc.Left = pcX * PgWidth / Mdiv;
	rc.Top = pcY * PgHeight / Mdiv;
	DrawTextIn();
}

//---------------------------------------------------------------------------
void __fastcall TmPrint::DrawTextIn(void)
{
	Canvas->Font = MyFont;

	Canvas->TextOut(rc.Left, rc.Top, uText);
	rc.Right = rc.Left + Canvas->TextWidth(uText);
	rc.Bottom = rc.Top + Canvas->TextHeight(uText);
}
//---------------------------------------------------------------------------




