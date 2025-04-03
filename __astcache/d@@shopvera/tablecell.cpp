//---------------------------------------------------------------------------
#pragma hdrstop

#include "TableCell.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TableCell::TableCell(UnicodeString uTxt, UnicodeString FontName, int FontSize, TFontStyles FontStyle)
  : TmPrint(uTxt, FontName, FontSize, FontStyle)
{
	Left = Right = Top = Bottom = 0;
	LeftMargin = RightMargin = TopMargin = BottomMargin = 0;
	bGeometry = false;
	vUstr.clear();
	HeightStrings = 0;
}

//---------------------------------------------------------------------------
__fastcall TableCell::~TableCell(void)
{

}
//---------------------------------------------------------------------------
void __fastcall TableCell::SetPosition(int _Left, int _Top, int _Right, int _Bottom)
{
	Left = _Left;
	Top = _Top;
	Right = _Right;
	Bottom = _Bottom;

	bGeometry = true;
}
//---------------------------------------------------------------------------
void __fastcall TableCell::SetPosition(long _Left, long _Top, long _Right, long _Bottom)
{
	Left = _Left * PgWidth / Mdiv;
	Right = _Right * PgWidth / Mdiv;
	Top = _Top * PgHeight / Mdiv;
	if(_Bottom != -1) {
		Bottom = _Bottom * PgHeight / Mdiv;
	}

	bGeometry = true;
}
//---------------------------------------------------------------------------
void __fastcall TableCell::SetPosition(long _Left, int _Top, long _Right, int _Bottom)
{
	Left = _Left * PgWidth / Mdiv;
	Right = _Right * PgWidth / Mdiv;
	Top = _Top;
	if(_Bottom != -1) {
		Bottom = _Bottom;
	}

	bGeometry = true;
}
//---------------------------------------------------------------------------
void __fastcall TableCell::SetMargins(int LMarg, int TMarg, int RMarg, int BMarg)
{
	LeftMargin = HeightFont * LMarg / 100;
	TopMargin = HeightFont * TMarg / 100;
	RightMargin = HeightFont * RMarg / 100;
	BottomMargin = HeightFont * BMarg / 100;
}
//---------------------------------------------------------------------------
void __fastcall TableCell::SetMargins(TRect rcMargins)
{
	LeftMargin = HeightFont * rcMargins.Left / 100;
	TopMargin = HeightFont * rcMargins.Top / 100;
	RightMargin = HeightFont * rcMargins.Right / 100;
	BottomMargin = HeightFont * rcMargins.Bottom / 100;
}

//---------------------------------------------------------------------------
void __fastcall TableCell::DrawText(TAlignment HzAlign)
{
	int h = Bottom - Top - TopMargin - BottomMargin;
	int w = Right - Left - LeftMargin - RightMargin;
	int x1;
	int y1 = Top + TopMargin + (h - HeightStrings)/2;

	for(unsigned i=0; i < vUstr.size(); i++) {
		switch(HzAlign) {
			case taLeftJustify:
				x1 = Left + LeftMargin;
				break;
			case taCenter:
				x1 = Left + (w - Canvas->TextWidth(vUstr[i]))/2;
				break;
			case taRightJustify:
				x1 = Right - RightMargin - Canvas->TextWidth(vUstr[i]);
				break;
		}
		Canvas->TextOut(x1, y1, vUstr[i]);
		y1 += Canvas->TextHeight(vUstr[i]);
	}
}

//---------------------------------------------------------------------------
void __fastcall TableCell::SplitText(void)
{
	if(!bGeometry) {
		return;
	}

	int WidthSpace = Right - Left - LeftMargin - RightMargin;
	int WidthAnalys;
	int pos = -1;
	UnicodeString uAnalys = uText;
	UnicodeString uPart = uText;
	UnicodeString uOstatok = L"";

	Canvas->Font = MyFont;
	vUstr.clear();
	HeightStrings = 0;
	do {
		WidthAnalys = Canvas->TextWidth(uPart);
		if(WidthAnalys <= WidthSpace || pos == 0) {
			vUstr.push_back(uPart);
			HeightStrings += Canvas->TextHeight(uPart);

			if(uOstatok.Length() == 0) {
				return;
			} else {
				uAnalys = uOstatok;
				uPart = uOstatok;
				uOstatok = L"";
				pos = -1;
            }
		} else {
			pos = uPart.LastDelimiter(L" ");
			if(pos != 0) {
				uPart = uPart.SubString(1, pos-1);
				uOstatok = uAnalys.SubString(pos+1, uAnalys.Length());
			}
		}
	} while(true);
}

//---------------------------------------------------------------------------
void __fastcall TableCell::DrawBorders(void)
{
	Canvas->Rectangle(Left, Top, Right, Bottom);
}
//---------------------------------------------------------------------------


