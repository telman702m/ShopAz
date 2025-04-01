//---------------------------------------------------------------------------
#ifndef ExportExelH
#define ExportExelH

#include <comobj.hpp>

enum CellFormat {TEXT=1, DBLE=2};
enum CellAlign {LEFT=2, CENTER=3, RIGHT=4};

//---------------------------------------------------------------------------
class ExcelData : public TObject
{
	private:
		Variant  vVarApp, vVarBooks, vVarBook, vVarSheets, vVarSheet, vVarCell;
		bool fStarted;

	public:
		__fastcall ExcelData();
		__fastcall ~ExcelData();

//		bool CreateFile(void);
//		bool OpenFile(char *FileName);
		bool __fastcall SaveFile(AnsiString FileName);
//		bool SetCurSheet(int NumbSheet);
		bool __fastcall SelectCurCell(int Row, int Col);
		void __fastcall SetCellProperty(CellFormat cf);
		void __fastcall SetCellsColor(AnsiString CellStart, AnsiString CellEnd, int ColorIndex);
		void __fastcall SetCellsBorder(AnsiString CellStart, AnsiString CellEnd);
		void __fastcall SetCellsWidth(AnsiString CellStart, AnsiString CellEnd, int cWidth);
		void __fastcall SetCellsAlignment(AnsiString CellStart, AnsiString CellEnd, CellAlign cAlign);

//		UnicodeString ReadData(int Row, int Col);
		void __fastcall SetCellsParam(void);
		bool __fastcall WriteToCurCell(UnicodeString uStr);
		bool __fastcall WriteToCurCell(double dValue);
};

#endif
