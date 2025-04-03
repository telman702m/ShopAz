//---------------------------------------------------------------------------
#ifndef TableCellH
#define TableCellH

#include <vcl.h>
#include <vector>
#include "Declaration.h"

#include "Print.h"

//---------------------------------------------------------------------------
class TableCell : public TmPrint
{
public:
	int Left;
	int Top;
	int Right;
	int Bottom;
	bool bGeometry;

	vector <UnicodeString> vUstr;
	int HeightStrings;

private:
	int LeftMargin;
	int TopMargin;
	int RightMargin;
	int BottomMargin;

public:
	__fastcall TableCell(UnicodeString uTxt, UnicodeString FontName, int FontSize, TFontStyles FontStyle);
	__fastcall ~TableCell(void);

	void __fastcall SetPosition(int _Left, int _Top, int _Right, int _Bottom);
	void __fastcall SetPosition(long _Left, long _Top, long _Right, long _Bottom = -1);
	void __fastcall SetPosition(long _Left, int _Top, long _Right, int _Bottom = -1);
	void __fastcall SetMargins(int LMarg, int TMarg, int RMarg, int BMarg);
	void __fastcall SetMargins(TRect rcMargins);
	void __fastcall SetBottomByText(void) { Bottom = Top + TopMargin + HeightStrings + BottomMargin; }
	void __fastcall SetBottomByText(int HeightStr) { Bottom = Top + TopMargin + HeightStr + BottomMargin; }
	void __fastcall SetBottom(int _Bottom) { Bottom = _Bottom; }
	void __fastcall DrawBorders(void);

	void __fastcall DrawText(TAlignment HzAlign);
	void __fastcall SplitText(void);

};
#endif
