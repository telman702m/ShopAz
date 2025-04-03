//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "Shop.h"
#include "UnitMoveProduct.h"
#include "ObjectManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

const TColor ColorLV[] = {
	clWindowText,	//TColor(0x00417812),     //  Покупка
	clWindowText,		//TColor(0x000073a6),     //  Возврат
	clWindowText,		//TColor(0x006b3e04),     //  Приемка
	clWindowText,	//TColor(0x00a5620b),     //  Передача
	clWindowText,		//TColor(0x00377500),     //  Оплата долга
	clWindowText,	//TColor(0x0030749f),     //  Затраты
	clWindowText,		//TColor(0x00006d96),     //  Оплата поставщикам
	clRed 		//TColor(0x000000ff)      //  Удаленные операции
};

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListMoveProduct(void)
{
	TListItem  *ListItem;
	SmallImages = ImgList;
	TCheckBox *CheckBoxes[] = {FormShop->CheckBoxSales, 	FormShop->CheckBoxReturn,
							   FormShop->CheckBoxIncom, 	FormShop->CheckBoxOut,
							   FormShop->CheckBoxRetDebt,	FormShop->CheckBoxExpenses,
							   FormShop->CheckBoxDebtProvis};

	for(unsigned i=0; i < TObjectManager<TMoveProduct>::GetList().size(); i++) {

		bool bCond = (TObjectManager<TMoveProduct>::GetList()[i]->DateTime > FormShop->DateTimePicker1->DateTime)
				  && (TObjectManager<TMoveProduct>::GetList()[i]->DateTime < FormShop->DateTimePicker2->DateTime)
				  && CheckBoxes[TObjectManager<TMoveProduct>::GetList()[i]->MoveType]->Checked
				  && (FormShop->CheckBoxDeleted->Checked || !TObjectManager<TMoveProduct>::GetList()[i]->bDeleted)
				  && (TObjectManager<TMoveProduct>::GetList()[i]->SourceUnit == FormShop->ShopUnit || TObjectManager<TMoveProduct>::GetList()[i]->TargetUnit == FormShop->ShopUnit);

		if(bCond) {
			if(FormShop->EditSearchName->Text.Length() > 0) {
				bCond = bCond && ((TObjectManager<TMoveProduct>::GetList()[i]->TargetPerson->SumName.UpperCase().Pos(FormShop->EditSearchName->Text.UpperCase()) > 0)
								||(TObjectManager<TMoveProduct>::GetList()[i]->SourcePerson->SumName.UpperCase().Pos(FormShop->EditSearchName->Text.UpperCase()) > 0));
			}

			if(FormShop->EditSearchProd->Text.Length() > 0) {
				bCond = bCond && TObjectManager<TMoveProduct>::GetList()[i]->IsContainProduct(FormShop->EditSearchProd->Text.UpperCase());
			}

			if(FormShop->EditSearchCashNumb->Text.Length() > 0) {
				bCond = bCond && (TObjectManager<TMoveProduct>::GetList()[i]->id == FormShop->EditSearchCashNumb->Text.ToInt());
			}
		}

		if(bCond) {
			ListItem = Items->Add();
			if(TObjectManager<TMoveProduct>::GetList()[i]->bDeleted) {
				ListItem->Data = Pointer(ColorLV[7]);
			} else {
				ListItem->Data = Pointer(ColorLV[TObjectManager<TMoveProduct>::GetList()[i]->MoveType]);
			}

			ListItem->Caption = TObjectManager<TMoveProduct>::GetList()[i]->DateTime.FormatString(wDateTimeFormat);

			if(TObjectManager<TMoveProduct>::GetList()[i]->MoveType == TMoveType::MOV_OUT) {

				if(TObjectManager<TMoveProduct>::GetList()[i]->SourceUnit == FormShop->ShopUnit) {
					ListItem->ImageIndex = TMoveType::MOV_OUT;
				} else {
					ListItem->ImageIndex = TMoveType::MOV_INC;
				}

			} else {
				ListItem->ImageIndex = TObjectManager<TMoveProduct>::GetList()[i]->MoveType;
			}
			AddSubItem(ListItem, FloatToStrF(TObjectManager<TMoveProduct>::GetList()[i]->id, ffNumber, 20, 0), ColumnsData[1].Visible);
			AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[i]->SourceUnit->Name, ColumnsData[2].Visible);
			AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[i]->SourcePerson->SumName, ColumnsData[3].Visible);
			AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[i]->TargetUnit->Name, ColumnsData[4].Visible);
			AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[i]->TargetPerson->SumName, ColumnsData[5].Visible);
			AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[i]->TotalCostPrice.StringFormat(), ColumnsData[6].Visible);
			AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[i]->TotalPrice.StringFormat(), ColumnsData[7].Visible);
			AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[i]->Discount.StringFormat(), ColumnsData[8].Visible);
			AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[i]->TotalPayment.StringFormat(), ColumnsData[9].Visible);
			AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[i]->ActualPayment.StringFormat(), ColumnsData[10].Visible);
			AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[i]->Debt.StringFormat(), ColumnsData[11].Visible);

			ipp.push_back(i);
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillArangeListMoveProduct(void)
{
	TListItem  *ListItem;

	for(int i=0; i<(int)ipp.size(); i++) {
		int ii = ipp[i];

		ListItem = Items->Add();

		ListItem->Caption = TObjectManager<TMoveProduct>::GetList()[ii]->DateTime.FormatString(wDateTimeFormat);

		if(TObjectManager<TMoveProduct>::GetList()[ii]->MoveType == TMoveType::MOV_OUT) {
			if(TObjectManager<TMoveProduct>::GetList()[ii]->SourceUnit == FormShop->ShopUnit) {
				ListItem->ImageIndex = TMoveType::MOV_OUT;
			} else {
				ListItem->ImageIndex = TMoveType::MOV_INC;
			}
		} else {
			ListItem->ImageIndex = TObjectManager<TMoveProduct>::GetList()[ii]->MoveType;
		}

		if(TObjectManager<TMoveProduct>::GetList()[ii]->bDeleted) {
			ListItem->Data = Pointer(ColorLV[7]);
		} else {
			ListItem->Data = Pointer(ColorLV[TObjectManager<TMoveProduct>::GetList()[ii]->MoveType]);
		}

		AddSubItem(ListItem, FloatToStrF(TObjectManager<TMoveProduct>::GetList()[ii]->id, ffNumber, 20, 0), ColumnsData[1].Visible);
		AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[ii]->SourceUnit->Name, ColumnsData[2].Visible);
		AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[ii]->SourcePerson->SumName, ColumnsData[3].Visible);
		AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[ii]->TargetUnit->Name, ColumnsData[4].Visible);
		AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[ii]->TargetPerson->SumName, ColumnsData[5].Visible);
		AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[ii]->TotalCostPrice.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[ii]->TotalPrice.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[ii]->Discount.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[ii]->TotalPayment.StringFormat(), ColumnsData[9].Visible);
		AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[ii]->ActualPayment.StringFormat(), ColumnsData[10].Visible);
		AddSubItem(ListItem, TObjectManager<TMoveProduct>::GetList()[ii]->Debt.StringFormat(), ColumnsData[11].Visible);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMyListView::SortMoveProduct(int iColumn)
{
	int iIndexColumnData = GetIndexColumnData(iColumn);
	bArrangeOrder[iIndexColumnData] = !bArrangeOrder[iIndexColumnData];

	bool bSwap;

	for(unsigned i=0; i < ipp.size(); i++) {
		for(unsigned j=i+1; j < ipp.size(); j++) {

			switch(iIndexColumnData) {
				case 0:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->DateTime < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->DateTime;
					break;
				case 1:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->id < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->id;
					break;
				case 2:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->SourceUnit->Name < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->SourceUnit->Name;
					break;
				case 3:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->SourcePerson->SumName < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->SourcePerson->SumName;
					break;
				case 4:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->TargetUnit->Name < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->TargetUnit->Name;
					break;
				case 5:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->TargetPerson->SumName < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->TargetPerson->SumName;
					break;
				case 6:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->TotalCostPrice.GetValue() < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->TotalCostPrice.GetValue();
					break;
				case 7:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->TotalPrice.GetValue() < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->TotalPrice.GetValue();
					break;
				case 8:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->Discount.GetValue() < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->Discount.GetValue();
					break;
				case 9:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->TotalPayment.GetValue() < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->TotalPayment.GetValue();
					break;
				case 10:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->ActualPayment.GetValue() < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->ActualPayment.GetValue();
					break;
				case 11:
					bSwap = TObjectManager<TMoveProduct>::GetList()[ipp[i]]->Debt.GetValue() < TObjectManager<TMoveProduct>::GetList()[ipp[j]]->Debt.GetValue();
					break;
			}
			if(bArrangeOrder[iIndexColumnData]) {
				bSwap = !bSwap;
            }
			if(bSwap) {
				swap(ipp[i], ipp[j]);
			}
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::MoveProductClick(int iIndex)
{
	if(ItemIndex != -1) {
		FormShop->AtomList->FillList();
//		UnicodeString uTmp;
//		ShowMessage(uTmp.sprintf(L"iIndex = %d ipp[iIndex] = %d", iIndex, ipp[iIndex]));
		FormShop->FillPersonsData(TObjectManager<TMoveProduct>::GetList()[ipp[iIndex]]);
	}
}

//---------------------------------------------------------------------------
TMoveProduct* __fastcall TMyListView::GetSelectMoveProduct(void)
{
	return TObjectManager<TMoveProduct>::GetList()[ipp[ItemIndex]];
}
