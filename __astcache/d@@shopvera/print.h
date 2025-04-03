//---------------------------------------------------------------------------
#ifndef PrintH
#define PrintH

#include <vcl.h>

//---------------------------------------------------------------------------
class TmPrint : public TObject
{

protected:
	static long Mdiv;
	TFont *MyFont;
	int HeightFont;

private:


public:
	static TCanvas *Canvas;
	static int PgWidth;
	static int PgHeight;
	TRect rc;
	UnicodeString uText;


	__fastcall TmPrint(UnicodeString uTxt, UnicodeString FontName, int FontSize, TFontStyles FontStyle);
	__fastcall ~TmPrint(void);

	static void __fastcall AssignCanv(TCanvas *Canv) { Canvas = Canv;}
	static void __fastcall AssignPageWidth(int PWidth) { PgWidth = PWidth; }
	static void __fastcall AssignPageHeight(int PHeight) { PgHeight = PHeight; }
	static int __fastcall GetOrigX(long PercX) { return PgWidth * PercX / Mdiv; }
	static int __fastcall GetOrigY(long PercY) { return PgHeight * PercY / Mdiv; }
	static long __fastcall GetPercX(int X) { return Mdiv * X / PgWidth; }
	static long __fastcall GetPercY(int Y) { return Mdiv * Y / PgHeight; }

	void __fastcall SetFontStyle(TFontStyles FontStyle) { MyFont->Style = FontStyle; }
	void __fastcall SetText(UnicodeString uTxt);
	void __fastcall DrawText(int x, int y);
	void __fastcall DrawText(long x, int y);
	void __fastcall DrawText(int x, long y);
	void __fastcall DrawText(long x, long y);
	void __fastcall DrawTextIn(void);
	int __fastcall GetHeightFont(void) { return HeightFont; }

	bool __fastcall SplitText(UnicodeString &u1, UnicodeString &u2, int &wLen);
};
#endif
