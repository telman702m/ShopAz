//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "MoveProduct.h"
#include "UnitMoveProduct.h"
#include "Shop.h"
#include "SelectProduct.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListAtom(void)
{
	TListItem  *ListItem;
	SmallImages = NULL;

	vector <TSelectProduct *>  AliasSelectProd;

	if(FormMoveProduct->Showing) {
		AliasSelectProd = FormMoveProduct->TmpMoveProduct->VSelectedProd;
	} else {
		AliasSelectProd = FormShop->MoveList->GetSelectMoveProduct()->VSelectedProd;
	}

	for(unsigned i=0; i < AliasSelectProd.size(); i++) {
		ListItem = Items->Add();

		ListItem->Caption = AliasSelectProd[i]->SelectDateTime.FormatString(wDateTimeFormat);

		AddSubItem(ListItem, AliasSelectProd[i]->Product->Code, ColumnsData[1].Visible);
		AddSubItem(ListItem, AliasSelectProd[i]->Product->Name, ColumnsData[2].Visible);

		if(AliasSelectProd[i]->Product->WholeUnit) {
			AddSubItem(ListItem, AliasSelectProd[i]->Product->Unit, ColumnsData[3].Visible);
		} else {
			UnicodeString uTmp = L"[" + AliasSelectProd[i]->Product->Unit + L"]";
			AddSubItem(ListItem, uTmp, ColumnsData[3].Visible);
		}

		AddSubItem(ListItem, AliasSelectProd[i]->IncomingPrice.StringFormat(), ColumnsData[4].Visible);
		AddSubItem(ListItem, AliasSelectProd[i]->Price.StringFormat(), ColumnsData[5].Visible);

		AddSubItem(ListItem, AliasSelectProd[i]->Count.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, AliasSelectProd[i]->TotalCostPrice.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, AliasSelectProd[i]->TotalPrice.StringFormat(), ColumnsData[8].Visible);

		ipp.push_back(i);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillAtomComponents(void)
{
//
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::AtomChangeList(TObject *Sender)
{
	if(FormMoveProduct->Showing) {
        FormMoveProduct->bChangeFromAtomList = true;
		FormMoveProduct->EditDiscountPrice1Change(Sender);
		FormMoveProduct->bChangeFromAtomList = false;
	}
}

