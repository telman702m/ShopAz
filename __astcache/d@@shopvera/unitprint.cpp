// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitPrint.h"
#include "Print.h"
#include "TableCell.h"
#include "UnitProduct.h"
#include "UnitProductList.h"
#include "UnitGroupList.h"
#include "Shop.h"
#include "MoveProduct.h"
#include "SelectProduct.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//bool bPrivew = true;
bool bPrivew = false;


TFormPrint *FormPrint;

// ---------------------------------------------------------------------------
__fastcall TFormPrint::TFormPrint(TComponent* Owner)
	: TForm(Owner)
{

}
// ---------------------------------------------------------------------------
void __fastcall TFormPrint::FormCreate(TObject *Sender)
{

	if(bPrivew) {
		pw = FormPrint->ImagePreview->Width;
		ph = FormPrint->ImagePreview->Height;
		Canv = FormPrint->ImagePreview->Canvas;

		TmPrint::AssignCanv(Canv);
	}
	else {
		Prntr = Printer();
		Prntr->Orientation = poPortrait;

		pw = Prntr->PageWidth;
		ph = Prntr->PageHeight;
	}

	TmPrint::AssignPageWidth(pw);
	TmPrint::AssignPageHeight(ph);
}
//---------------------------------------------------------------------------
void __fastcall TFormPrint::FormShow(TObject *Sender)
{
	// Clear canvas
}

//---------------------------------------------------------------------------
void __fastcall TFormPrint::PrintSale(TMoveProduct *CurMoveProduct)
{
	if(bPrivew) {
		// Clear canvas
		Canv->Pen->Color = (TColor)RGB(255, 255, 255);
		Canv->Pen->Style = psSolid;
		Canv->Pen->Width = 1;
		Canv->Brush->Color = (TColor)RGB(255, 255, 255);
		Canv->Brush->Style = bsSolid;
		Canv->Rectangle(1, 1, pw, ph);
	} else {
		Prntr->BeginDoc();
		Canv = Prntr->Canvas;
		TmPrint::AssignCanv(Canv);
	}

	long LeftMarg = 14;
	long TopOffset = 15;

	PrintTicket(LeftMarg, TopOffset, CurMoveProduct);
	PrintTicket(LeftMarg + 450L, TopOffset, CurMoveProduct);

	if(bPrivew) {
		FormPrint->ShowModal();
	}else {
		Prntr->EndDoc();
	}
}

//---------------------------------------------------------------------------
//				New Print Format
//---------------------------------------------------------------------------
long __fastcall TFormPrint::PrintTicket(long LeftMarg, long TopOffset, TMoveProduct *CurMoveProduct)
{
	long CurLeftMarg = LeftMarg, LeftPosPhoneText;
	// ------------------ First line -------------------
	//  Text Shop
	TmPrint *TextShop = new TmPrint(L"Mağaza:", NULL, 10, TFontStyles());
	TextShop->DrawText(CurLeftMarg, TopOffset);
	delete TextShop;
	//  Shop Name
	TmPrint *UnitShop = new TmPrint(FormShop->ShopUnit->Name, NULL, 10, TFontStyles());
	UnitShop->SetFontStyle(TFontStyles() << fsBold);
	CurLeftMarg = LeftMarg + 68L;
	UnitShop->DrawText(CurLeftMarg, TopOffset);
	delete UnitShop;

	// Gaime Number
	//  Text ticket
	TmPrint *TextTicket = new TmPrint(L"Satış Qaiməsi:", NULL, 10, TFontStyles());
	CurLeftMarg = LeftMarg + 260L;
	TextTicket->DrawText(CurLeftMarg, TopOffset);
	delete TextTicket;
	// Number ticket
	UnicodeString GaimeNumb;
	GaimeNumb.sprintf(L"№ %2d", CurMoveProduct->id);
	TmPrint *GaimeNumber = new TmPrint(GaimeNumb, NULL, 10, TFontStyles());
	GaimeNumber->SetFontStyle(TFontStyles() << fsBold);
	CurLeftMarg = LeftMarg + 365L;
	GaimeNumber->DrawText(CurLeftMarg, TopOffset);

	//  Text address
/*	TmPrint TextAddress(L"Ünvan:", NULL, 10, TFontStyles());
	TextAddress.SetFontStyle(TFontStyles() << fsBold);
//	CurLeftMarg += Canv->TextWidth(UnitShop.uText);
	CurLeftMarg = LeftMarg + 200L;
	TextAddress.DrawText(CurLeftMarg, TopOffset);
	//  Shop address
	TmPrint ShopAddress(FormShop->ShopUnit->Address, NULL, 10, TFontStyles());
//	CurLeftMarg += Canv->TextWidth(TextAddress.uText);
	CurLeftMarg = LeftMarg + 240L;
	ShopAddress.DrawText(CurLeftMarg, TopOffset); */

	// ------------------ Second line -------------------
	//  Text telefon
	TmPrint *TextPhones = new TmPrint(L"Telefon:", NULL, 10, TFontStyles());
	CurLeftMarg = LeftMarg;
	TextPhones->DrawText(CurLeftMarg, int(GaimeNumber->rc.Bottom));
	delete TextPhones;

	//  Phone1 number
	TmPrint *Phones1 = new TmPrint(FormShop->ShopUnit->Phone1, NULL, 10, TFontStyles());
	Phones1->SetFontStyle(TFontStyles() << fsBold);
	CurLeftMarg = LeftMarg + 68L;
	Phones1->DrawText(CurLeftMarg, int(GaimeNumber->rc.Bottom));
	//  Phone2 number
	TmPrint *Phones2 = new TmPrint(FormShop->ShopUnit->Phone2, NULL, 10, TFontStyles());
	Phones2->SetFontStyle(TFontStyles() << fsBold);
	CurLeftMarg = LeftMarg + 68L;
	Phones2->DrawText(CurLeftMarg, int(Phones1->rc.Bottom));

	//  Text Date
	TmPrint *TextDate = new TmPrint(L"Tarix:", NULL, 10, TFontStyles());
	CurLeftMarg = LeftMarg + 300L;
	TextDate->DrawText(CurLeftMarg, int(GaimeNumber->rc.Bottom));
	delete TextDate;
	// Date & Time
	TmPrint *SaleDateTime = new TmPrint(CurMoveProduct->DateTime.DateString(), NULL, 10, TFontStyles());
	SaleDateTime->SetFontStyle(TFontStyles() << fsBold);
	CurLeftMarg = LeftMarg + 350L;
	SaleDateTime->DrawText(CurLeftMarg, int(GaimeNumber->rc.Bottom));

	SaleDateTime->SetText(CurMoveProduct->DateTime.TimeString());
	CurLeftMarg = LeftMarg + 365L;
	SaleDateTime->DrawText(CurLeftMarg, int(Phones1->rc.Bottom));
	delete SaleDateTime;
	delete GaimeNumber;
	delete Phones1;

/*
	// ------------------ Third line -------------------
	//  Text Name Buyer
	TmPrint TextBuyer(L"Müştərinin adı:", NULL, 10, TFontStyles());
	TextBuyer.SetFontStyle(TFontStyles() << fsBold);
	CurLeftMarg = LeftMarg;
	TextBuyer.DrawText(CurLeftMarg, int(TextDate.rc.Bottom));
	// Name Buyer
	TmPrint NameBuyer(CurMoveProduct->TargetPerson->SumName, NULL, 11, TFontStyles());
//	CurLeftMarg += Canv->TextWidth(TextBuyer.uText);
	CurLeftMarg = LeftMarg + 115L;
	NameBuyer.DrawText(CurLeftMarg, int(TextDate.rc.Bottom));
*/
	// --------------- Print Product list -----------------
	Canv->Brush->Color = (TColor)RGB(245, 245, 245);
	Canv->Brush->Style = bsSolid;
	Canv->Pen->Color = clBlack;
	Canv->Pen->Style = psSolid;
	Canv->Pen->Width = 1;

	const int CountColumn = 4;
	TColumnsData ColumnsData[CountColumn] = {
		{{L"Название товара",	L"Malın adı"},		220, 	taLeftJustify, 	true, 	false},
		{{L"Количество", 		L"Sayı"},	 		50, 	taCenter, 		true, 	false},
		{{L"Цена", 				L"Qiyməti"}, 		80, 	taRightJustify, true, 	false},
		{{L"Сумма", 			L"Cəmi"}, 			80, 	taRightJustify, true, 	false}
	};
	TRect rcMargins[CountColumn] = {
		TRect(40, 25, 25, 25),
		TRect(25, 25, 25, 25),
		TRect(25, 25, 100, 25),
		TRect(25, 25, 100, 25)
	};

	long ColumnPos[CountColumn + 1];
	ColumnPos[0] = LeftMarg;
	for(int i=1; i < CountColumn+1; i++) {
		ColumnPos[i] = ColumnPos[i-1] + ColumnsData[i-1].Width;
	}

	// draw table rows captions
	long TblTop = TmPrint::GetPercY(Phones2->rc.Bottom) + 5;
//	long TblTop = Phones2.rc.Bottom;
	delete Phones2;

	TableCell *TbCell = new TableCell(L" ", NULL, 8, TFontStyles() << fsBold);

	for(int i = 0; i < CountColumn; i++) {
		TbCell->SetPosition(ColumnPos[i], TblTop, ColumnPos[i + 1]);
		TbCell->SetText(ColumnsData[i].Caption[iLang]);
		TbCell->SetMargins(rcMargins[i]);
		TbCell->SplitText();
		if(i==0) {
			TbCell->SetBottomByText();
		}
		TbCell->DrawBorders();
		TbCell->DrawText(taCenter);
	}

	Canv->Brush->Style = bsClear;
	TbCell->SetFontStyle(TFontStyles());

	int RowBot = TbCell->Bottom;
	UnicodeString uTmp;

	for(unsigned i = 0; i < CurMoveProduct->VSelectedProd.size(); i++) {
		for(int j = 0; j < CountColumn; j++) {
			switch(j) {
			case 0:
				uTmp = CurMoveProduct->VSelectedProd[i]->Product->Name;
				break;
			case 1:
				if(CurMoveProduct->VSelectedProd[i]->Product->WholeUnit) {
					uTmp.sprintf(L"%2d", CurMoveProduct->VSelectedProd[i]->Count.GetWhole());
				} else {
					uTmp.sprintf(L"%1.2f", CurMoveProduct->VSelectedProd[i]->Count.GetValue());
				}
				break;
			case 2:
				uTmp = CurMoveProduct->VSelectedProd[i]->Price.StringFormat();
				break;
			case 3:
				uTmp = CurMoveProduct->VSelectedProd[i]->TotalPrice.StringFormat();
				break;
			}
			TbCell->SetPosition(ColumnPos[j], RowBot, ColumnPos[j + 1]);
			TbCell->SetText(uTmp);
			TbCell->SetMargins(rcMargins[j]);
			TbCell->SplitText();
			if(j==0) {
				TbCell->SetBottomByText();
			}
			TbCell->DrawBorders();
			TbCell->DrawText(ColumnsData[j].TMAlign);
		}
		RowBot = TbCell->Bottom;
	}

	TbCell->SetFontStyle(TFontStyles() << fsBold);
	// draw cell "Cəmi məbləği"
	Canv->Brush->Color = (TColor)RGB(245, 245, 245);
	Canv->Brush->Style = bsSolid;
	TbCell->SetPosition(ColumnPos[0], RowBot, ColumnPos[CountColumn - 1]);
	TbCell->SetText(L"Cəmi məbləği");
	TbCell->SetMargins(500, 30, 25, 30);
	TbCell->SplitText();
	TbCell->SetBottomByText();
	TbCell->DrawBorders();
	TbCell->DrawText(taLeftJustify);
	// draw cell TotalPrice
	TbCell->SetPosition(ColumnPos[CountColumn - 1], RowBot, ColumnPos[CountColumn]);
	TbCell->SetText(CurMoveProduct->TotalPrice.StringFormat());
	TbCell->SetMargins(rcMargins[CountColumn - 1]);
	TbCell->SplitText();
	TbCell->DrawBorders();
	TbCell->DrawText(taRightJustify);

	// draw cell "Endirim"
	Canv->Brush->Style = bsClear;
	Canv->Brush->Color = (TColor)RGB(255, 255, 255);
	Canv->Brush->Style = bsSolid;
	RowBot = TbCell->Bottom;
	TbCell->SetPosition(ColumnPos[0], RowBot, ColumnPos[CountColumn - 1]);
	TbCell->SetText(L"Endirim");
	TbCell->SetMargins(500, 30, 25, 30);
	TbCell->SplitText();
	TbCell->SetBottomByText();
	TbCell->DrawBorders();
	TbCell->DrawText(taLeftJustify);
	// draw cell Discount
	TbCell->SetPosition(ColumnPos[CountColumn - 1], RowBot, ColumnPos[CountColumn]);
	TbCell->SetText(CurMoveProduct->Discount.StringFormat());
	TbCell->SetMargins(rcMargins[CountColumn - 1]);
	TbCell->SplitText();
	TbCell->DrawBorders();
	TbCell->DrawText(taRightJustify);

	// draw cell "Cəmi ödəniş məbləği:"
	Canv->Brush->Color = (TColor)RGB(245, 245, 245);
	Canv->Brush->Style = bsSolid;
	RowBot = TbCell->Bottom;
	TbCell->SetPosition(ColumnPos[0], RowBot, ColumnPos[CountColumn - 1]);
	TbCell->SetText(L"Cəmi ödəniş məbləği:");
	TbCell->SetMargins(500, 30, 25, 30);
	TbCell->SplitText();
	TbCell->SetBottomByText();
	TbCell->DrawBorders();
	TbCell->DrawText(taLeftJustify);
	// draw cell Total
	TbCell->SetPosition(ColumnPos[CountColumn - 1], RowBot, ColumnPos[CountColumn]);
	TbCell->SetText(CurMoveProduct->TotalPayment.StringFormat());
	TbCell->SetMargins(rcMargins[CountColumn - 1]);
	TbCell->SplitText();
	TbCell->DrawBorders();
	TbCell->DrawText(taRightJustify);

	// draw cell "Faktiki ödəniş"
	Canv->Brush->Style = bsClear;
	Canv->Brush->Color = (TColor)RGB(255, 255, 255);
	Canv->Brush->Style = bsSolid;
	RowBot = TbCell->Bottom;
	TbCell->SetPosition(ColumnPos[0], RowBot, ColumnPos[CountColumn - 1]);
	TbCell->SetText(L"Faktiki ödəniş:");
	TbCell->SetMargins(500, 30, 25, 30);
	TbCell->SplitText();
	TbCell->SetBottomByText();
	TbCell->DrawBorders();
	TbCell->DrawText(taLeftJustify);
	// draw cell Actual payment
	TbCell->SetPosition(ColumnPos[CountColumn - 1], RowBot, ColumnPos[CountColumn]);
	TbCell->SetText(CurMoveProduct->ActualPayment.StringFormat());
	TbCell->SetMargins(rcMargins[CountColumn - 1]);
	TbCell->SplitText();
	TbCell->DrawBorders();
	TbCell->DrawText(taRightJustify);

	// draw cell "Borc"
	Canv->Brush->Color = (TColor)RGB(245, 245, 245);
	Canv->Brush->Style = bsSolid;
	RowBot = TbCell->Bottom;
	TbCell->SetPosition(ColumnPos[0], RowBot, ColumnPos[CountColumn - 1]);
	TbCell->SetText(L"Borc:");
	TbCell->SetMargins(500, 30, 25, 30);
	TbCell->SplitText();
	TbCell->SetBottomByText();
	TbCell->DrawBorders();
	TbCell->DrawText(taLeftJustify);
	// draw cell Debt
	TbCell->SetPosition(ColumnPos[CountColumn - 1], RowBot, ColumnPos[CountColumn]);
	TbCell->SetText(CurMoveProduct->Debt.StringFormat());
	TbCell->SetMargins(rcMargins[CountColumn - 1]);
	TbCell->SplitText();
	TbCell->DrawBorders();
	TbCell->DrawText(taRightJustify);

	Canv->Brush->Style = bsClear;
	// Name Seller
	long CurTop = TmPrint::GetPercY(TbCell->Bottom) + 15;
	TmPrint *Seller = new TmPrint(L"Satıcı: ", NULL, 11, TFontStyles());
	Seller->DrawText(LeftMarg, CurTop);

	Seller->SetFontStyle(TFontStyles() << fsBold);
	Seller->SetText(CurMoveProduct->SourcePerson->SumName);
	Seller->DrawText(int(Seller->rc.Right), CurTop);

	Seller->SetFontStyle(TFontStyles());
	Seller->SetText(L"_____________");
	Seller->DrawText(int(Seller->rc.Right), CurTop);

	CurTop = TmPrint::GetPercY(Seller->rc.Bottom) + 15;
	Seller->SetText(L"Müştəri: ");
//	Seller->DrawText(int(Seller->rc.Right) - Canv->TextWidth(Seller->uText), CurTop);
	Seller->DrawText(LeftMarg, CurTop);

	Seller->SetFontStyle(TFontStyles() << fsBold);
	Seller->SetText(CurMoveProduct->TargetPerson->SumName);
	Seller->DrawText(int(Seller->rc.Right), CurTop);

	Seller->SetFontStyle(TFontStyles());
	Seller->SetText(L"_____________");
	Seller->DrawText(int(Seller->rc.Right), CurTop);

	// Note
	TmPrint *Note = new TmPrint(L"QEYD: Alınan mallar 14 qün ərzində dəyişdirilə və ya 10 faiz",
			NULL, 9, TFontStyles());
	CurTop = TmPrint::GetPercY(Seller->rc.Bottom) + 10L;
	Note->DrawText(LeftMarg, CurTop);

	Note->SetText(L"tutulmaqla qaytarıla bilər. Aradoldurucular, yapışdırıcılar və");
	CurTop = TmPrint::GetPercY(Note->rc.Bottom);
	Note->DrawText(LeftMarg, CurTop);

	Note->SetText(L"sifarişə gələn mallar ümümiyyətlə geriyə qaytarılmır.");
	CurTop = TmPrint::GetPercY(Note->rc.Bottom);
	Note->DrawText(LeftMarg, CurTop);

	delete Note;
	delete TbCell;
    delete Seller;
	return 0;
}

// ---------------------------------------------------------------------------
//    @@@@@@@@@@@@@@@@@@@@@   Print Products   @@@@@@@@@@@@@@@@@@@@@@@@
// ---------------------------------------------------------------------------
	const int CountColumn = 6;
	TColumnsData ColumnsData[CountColumn] = {
		{{L"№", 		L"№"},			30,		taRightJustify, true, 	false},
		{{L"Код",		L"Kod"},		180, 	taLeftJustify, 	true, 	false},
		{{L"Название", 	L"Adı"},		520, 	taLeftJustify, 	true, 	false},
		{{L"Стоимость",	L"Dəyəri"}, 	60, 	taRightJustify, true, 	false},
		{{L"Цена",	   	L"Qiyməti"},	60, 	taRightJustify, true, 	false},
		{{L"Остаток",  	L"Qalıq"},		60, 	taRightJustify, true, 	false}
	};

	int ColumnPos[CountColumn + 1];
	int TblTop;
	int TblHeight;
// ---------------------------------------------------------------------------
void __fastcall TFormPrint::PrintProducts(int IdGroup)
{
	if(bPrivew) {
		// Clear canvas
		Canv->Pen->Color = (TColor)RGB(255, 255, 255);
		Canv->Pen->Style = psSolid;
		Canv->Pen->Width = 1;
		Canv->Brush->Color = (TColor)RGB(255, 255, 255);
		Canv->Brush->Style = bsSolid;
		Canv->Rectangle(1, 1, pw, ph);
	} else {
		Prntr->BeginDoc();
		Canv = Prntr->Canvas;
		TmPrint::AssignCanv(Canv);
	}

	ColumnPos[0] = 10;
	for(int i=1; i < CountColumn+1; i++) {
		ColumnPos[i] = ColumnPos[i-1] + ColumnsData[i-1].Width;
	}

	TblTop = TmPrint::GetOrigY(20);

	DrawTbProdCaption();

	// Print Product list
	Canv->Brush->Color = (TColor)RGB(255, 255, 255);

	UnicodeString uTmp;
	int iFinded = 0;
//	int PageNumber = 1;
//	int RowsInPage = 42;

	TableCell *TbCell = new TableCell(L" ", NULL, 8, TFontStyles());

	for(unsigned i = 0; i < TObjectManager<TProduct>::GetList().size(); i++) {

		if(FormProductList->FilteredProduct(i)) {
			for(int j = 0; j < CountColumn; j++) {
				int MaxHeight;
				UnicodeString uTmp2;

				switch(j) {
				case 0:
					// detect max height for cell in row
					MaxHeight = 0;
					for(int k = 1; k < 3; k++) {
						switch(k) {
						case 1:
							uTmp2 = TObjectManager<TProduct>::GetList()[i]->Code;
							break;
						case 2:
							uTmp2 = TObjectManager<TProduct>::GetList()[i]->Name;
							break;
						}
						TbCell->SetPosition(ColumnPos[k], TblTop, ColumnPos[k + 1]);
						TbCell->SetMargins(40, 30, 40, 30);
						TbCell->SetText(uTmp2);
						TbCell->SplitText();
						if(TbCell->HeightStrings > MaxHeight) {
							MaxHeight = TbCell->HeightStrings;
						}
					}
					uTmp.sprintf(L"%2d", ++iFinded);
					break;
				case 1:
					uTmp = TObjectManager<TProduct>::GetList()[i]->Code;
					break;
				case 2:
					uTmp = TObjectManager<TProduct>::GetList()[i]->Name;
					break;
				case 3:
					uTmp = TObjectManager<TProduct>::GetList()[i]->PurchaseCash.StringFormat();
					break;
				case 4:
					uTmp = TObjectManager<TProduct>::GetList()[i]->SellingPrice.StringFormat();
					break;
				case 5:
//					uTmp.sprintf(L"%7d", TObjectManager<TProduct>::GetList()[i]->CountBalance[TShopUnits::upp[0]]);
					uTmp = TObjectManager<TProduct>::GetList()[i]->CountBalance[TShopUnits::upp[0]].StringFormat();
					break;
				}
				TbCell->SetPosition(ColumnPos[j], TblTop, ColumnPos[j + 1]);
				TbCell->SetMargins(40, 30, 40, 30);
				TbCell->SetText(uTmp);
				TbCell->SplitText();
				TbCell->SetBottomByText(MaxHeight);
				TbCell->DrawBorders();
				TbCell->DrawText(ColumnsData[j].TMAlign);
			}
			TblTop = TbCell->Bottom;
			if(TblTop >= ph - TmPrint::GetOrigY(20)) {
				if(!bPrivew) {
					Printer()->NewPage();
//					PageNumber++;
					TblTop = TmPrint::GetOrigY(20);
					DrawTbProdCaption();
					Canv->Brush->Color = (TColor)RGB(255, 255, 255);
				} else {
					break;
				}
			}
		}
	}

    delete TbCell;

	if(bPrivew) {
		FormPrint->ShowModal();
	} else {
		Prntr->EndDoc();
	}
}
// ---------------------------------------------------------------------------
void __fastcall TFormPrint::DrawTbProdCaption(void)
{
	Canv->Brush->Color = (TColor)RGB(245, 245, 245);
	Canv->Pen->Color = (TColor)RGB(100, 100, 100);
	Canv->Pen->Style = psSolid;
	Canv->Pen->Width = 1;

	// draw table rows captions
	TableCell *TbCell = new TableCell(L" ", NULL, 10, TFontStyles() << fsBold);
	for(int i = 0; i < CountColumn; i++) {
		TbCell->SetPosition(ColumnPos[i], TblTop, ColumnPos[i + 1]);
		TbCell->SetText(ColumnsData[i].Caption[iLang]);
		TbCell->SetMargins(25, 25, 25, 25);
		TbCell->SplitText();
		if(i==0) {
			TbCell->SetBottomByText();
		}
		TbCell->DrawBorders();
		TbCell->DrawText(taCenter);
	}
	TblTop = TbCell->Bottom;
	delete TbCell;
}
// ---------------------------------------------------------------------------

