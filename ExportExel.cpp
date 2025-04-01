//---------------------------------------------------------------------------
#pragma hdrstop
#include <vcl.h>
#include "ExportExel.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ExcelData::ExcelData()
{
	fStarted = false;

	if(!fStarted) {
		try {
			vVarApp = CreateOleObject("Excel.Application");     // ������� ������ Excel.Application
			fStarted = true;
			vVarApp.OlePropertySet("Visible", true);            // ������� ���������� �������

			vVarBooks = vVarApp.OlePropertyGet("Workbooks");    // ���������� vVarBooks ������������� �������� Workbooks - �������� ������� Excel.Application, ���������� ����� ������� ���� Excel
			vVarApp.OlePropertySet("SheetsInNewWorkbook", 3);   // SheetsInNewWorkbook ������ ���������� ������ � ����������� �����, ����� � ������ ����� �� ����� 3
			vVarBooks.OleProcedure("Add");                      // ��������� ����� �� 3 ������ � ������ vVarBooks.

			vVarBook = vVarBooks.OlePropertyGet("Item", 1);     // ���������� vVarBook �������� ������ �� ������� �����. (����� ������� ����� 1)
			vVarSheets = vVarBook.OlePropertyGet("Worksheets"); // ���������� vVarSheets ����������� �������� Worksheets - �������� ������� Excel.Application, ���������� ����� ������� ����� Excel

			vVarSheet = vVarSheets.OlePropertyGet("Item", 1);
			vVarSheet.OlePropertySet("Name", WideString(L"Products List"));
		} catch(...) {
			Application->MessageBox(L"Error when open Excel", L"Error", MB_OK);
			return;
		}
	}
}
//---------------------------------------------------------------------------
__fastcall ExcelData::~ExcelData()
{
	if(fStarted) {
		vVarApp.OleProcedure("Quit");
	}
}

//---------------------------------------------------------------------------
/*
bool ExcelData::SetCurSheet(int NumbSheet)
{
	try {
//		ExcelSheet = ExcelApp.OlePropertyGet("WorkSheets", NumbSheet);
		ExcelSheet = ExcelBook.OlePropertyGet("WorkSheets", NumbSheet);
	} catch (...) {
		Application->MessageBox(L"Incorrect sheet number Microsoft Excel", L"Error", MB_OK+MB_ICONERROR);
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------
bool ExcelData::CreateFile(void)
{
	try {
		ExcelApp.OlePropertyGet("WorkBooks").OleProcedure("Add");
	} catch (...) {
		Application->MessageBox(L"Error on create file Microsoft Excel.", L"Error", MB_OK+MB_ICONERROR);
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------
bool ExcelData::OpenFile(char *file)
{
	try {
	   ExcelBook  = ExcelApp.OlePropertyGet("Workbooks").OlePropertyGet("Open", file);
	   ExcelSheet = ExcelBook.OlePropertyGet("Worksheets", 1);
	} catch (...) {
		Application->MessageBox(L"Error on open file Excel", L"Error", MB_OK+MB_ICONERROR);
		return false;
	}
	return true;
}
*/
//---------------------------------------------------------------------------
bool __fastcall ExcelData::SaveFile(AnsiString FileName)
{
	try {
		vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OleProcedure("SaveAs", WideString(FileName.c_str()));
	} catch (...) {
		Application->MessageBox(L"Error on save file Excel", L"Error", MB_OK+MB_ICONERROR);
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------
void __fastcall ExcelData::SetCellsParam(void)
{
	vVarCell = vVarSheet.OlePropertyGet("Range","A1:K1000");
	vVarCell.OlePropertySet("WrapText", true);
	vVarCell.OlePropertySet("ColumnWidth", 15);
}

//---------------------------------------------------------------------------
void __fastcall ExcelData::SetCellsAlignment(AnsiString CellStart, AnsiString CellEnd, CellAlign cAlign)
{
	AnsiString uTmp = CellStart + L":" + CellEnd;
	vVarSheet.OlePropertyGet("Range", WideString(uTmp.c_str())).OlePropertySet("HorizontalAlignment", WideString(cAlign));
}
//---------------------------------------------------------------------------
void __fastcall ExcelData::SetCellsWidth(AnsiString CellStart, AnsiString CellEnd, int cWidth)
{
	AnsiString uTmp = CellStart + L":" + CellEnd;
	vVarSheet.OlePropertyGet("Range", WideString(uTmp.c_str())).OlePropertySet("ColumnWidth", WideString(cWidth));
}
//---------------------------------------------------------------------------
void __fastcall ExcelData::SetCellsColor(AnsiString CellStart, AnsiString CellEnd, int ColorIndex)
{
	AnsiString uTmp = CellStart + L":" + CellEnd;
	vVarSheet.OlePropertyGet("Range", WideString(uTmp.c_str())).OlePropertyGet("Interior").OlePropertySet("ColorIndex", ColorIndex);
}
//---------------------------------------------------------------------------
void __fastcall ExcelData::SetCellsBorder(AnsiString CellStart, AnsiString CellEnd)
{
	AnsiString uTmp = CellStart + L":" + CellEnd;
	Variant range = vVarSheet.OlePropertyGet("Range", WideString(uTmp.c_str()));

	for(int i=1; i <= 4; i++) {
		range.OlePropertyGet("Borders").OlePropertyGet("Item", i).OlePropertySet("LineStyle", 1);
	}
}

//---------------------------------------------------------------------------
bool __fastcall ExcelData::SelectCurCell(int Row, int Col)
{
	try {
		vVarCell = vVarSheet.OlePropertyGet("Cells", Row, Col);
	} catch (...) {
		Application->MessageBox(L"Incorrect SelectCurCell Microsoft Excel", L"Error", MB_OK+MB_ICONERROR);
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------
void __fastcall ExcelData::SetCellProperty(CellFormat cf)
{
	switch(cf) {
		case CellFormat::TEXT:
			vVarCell.OlePropertySet("NumberFormat", WideString("@"));
			break;
		case CellFormat::DBLE:
			vVarCell.OlePropertySet("NumberFormat", WideString("0,00"));
			break;
	}
}

//---------------------------------------------------------------------------
bool __fastcall ExcelData::WriteToCurCell(UnicodeString uStr)
{
	try {
		vVarCell.OlePropertySet("Value", WideString(uStr));
	} catch (...) {
		Application->MessageBox(L"Excel error when writing to the cell", L"Error", MB_OK+MB_ICONERROR);
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------
bool __fastcall ExcelData::WriteToCurCell(double dValue)
{
	try {
		vVarCell.OlePropertySet("Value", dValue);
	} catch (...) {
		Application->MessageBox(L"Excel error when writing to the cell", L"Error", MB_OK+MB_ICONERROR);
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------
//UnicodeString ExcelData::ReadData(int Row, int Col)
//{

//	UnicodeString str = UnicodeString("E")+UnicodeString(Row);
//	wchar_t *columnPos = str.w_str();
//	return ExcelSheet.OlePropertyGet("Range", columnPos);
//}

//---------------------------------------------------------------------------

