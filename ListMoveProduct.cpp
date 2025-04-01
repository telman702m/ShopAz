//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "Shop.h"
#include "UnitMoveProduct.h"

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

	for(int i=0; i < (int)TMoveProduct::VMoveProduct.size(); i++) {

		bool bCond = (TMoveProduct::VMoveProduct[i]->DateTime > FormShop->DateTimePicker1->DateTime)
				  && (TMoveProduct::VMoveProduct[i]->DateTime < FormShop->DateTimePicker2->DateTime)
				  && CheckBoxes[TMoveProduct::VMoveProduct[i]->MoveType]->Checked
				  && (FormShop->CheckBoxDeleted->Checked || !TMoveProduct::VMoveProduct[i]->bDeleted)
				  && (TMoveProduct::VMoveProduct[i]->SourceUnit == FormShop->ShopUnit || TMoveProduct::VMoveProduct[i]->TargetUnit == FormShop->ShopUnit);

		if(bCond) {
			if(FormShop->EditSearchName->Text.Length() > 0) {
				bCond = bCond && ((TMoveProduct::VMoveProduct[i]->TargetPerson->SumName.UpperCase().Pos(FormShop->EditSearchName->Text.UpperCase()) > 0)
								||(TMoveProduct::VMoveProduct[i]->SourcePerson->SumName.UpperCase().Pos(FormShop->EditSearchName->Text.UpperCase()) > 0));
			}

			if(FormShop->EditSearchProd->Text.Length() > 0) {
				bCond = bCond && TMoveProduct::VMoveProduct[i]->IsContainProduct(FormShop->EditSearchProd->Text.UpperCase());
			}

			if(FormShop->EditSearchCashNumb->Text.Length() > 0) {
				bCond = bCond && (TMoveProduct::VMoveProduct[i]->id == FormShop->EditSearchCashNumb->Text.ToInt());
			}
		}

		if(bCond) {
			ListItem = Items->Add();
			if(TMoveProduct::VMoveProduct[i]->bDeleted) {
				ListItem->Data = Pointer(ColorLV[7]);
			} else {
				ListItem->Data = Pointer(ColorLV[TMoveProduct::VMoveProduct[i]->MoveType]);
			}

			ListItem->Caption = TMoveProduct::VMoveProduct[i]->DateTime.FormatString(wDateTimeFormat);

			if(TMoveProduct::VMoveProduct[i]->MoveType == TMoveType::MOV_OUT) {

				if(TMoveProduct::VMoveProduct[i]->SourceUnit == FormShop->ShopUnit) {
					ListItem->ImageIndex = TMoveType::MOV_OUT;
				} else {
					ListItem->ImageIndex = TMoveType::MOV_INC;
				}

			} else {
				ListItem->ImageIndex = TMoveProduct::VMoveProduct[i]->MoveType;
			}
			AddSubItem(ListItem, FloatToStrF(TMoveProduct::VMoveProduct[i]->id, ffNumber, 20, 0), ColumnsData[1].Visible);
			AddSubItem(ListItem, TMoveProduct::VMoveProduct[i]->SourceUnit->Name, ColumnsData[2].Visible);
			AddSubItem(ListItem, TMoveProduct::VMoveProduct[i]->SourcePerson->SumName, ColumnsData[3].Visible);
			AddSubItem(ListItem, TMoveProduct::VMoveProduct[i]->TargetUnit->Name, ColumnsData[4].Visible);
			AddSubItem(ListItem, TMoveProduct::VMoveProduct[i]->TargetPerson->SumName, ColumnsData[5].Visible);
			AddSubItem(ListItem, TMoveProduct::VMoveProduct[i]->TotalCostPrice.StringFormat(), ColumnsData[6].Visible);
			AddSubItem(ListItem, TMoveProduct::VMoveProduct[i]->TotalPrice.StringFormat(), ColumnsData[7].Visible);
			AddSubItem(ListItem, TMoveProduct::VMoveProduct[i]->Discount.StringFormat(), ColumnsData[8].Visible);
			AddSubItem(ListItem, TMoveProduct::VMoveProduct[i]->TotalPayment.StringFormat(), ColumnsData[9].Visible);
			AddSubItem(ListItem, TMoveProduct::VMoveProduct[i]->ActualPayment.StringFormat(), ColumnsData[10].Visible);
			AddSubItem(ListItem, TMoveProduct::VMoveProduct[i]->Debt.StringFormat(), ColumnsData[11].Visible);

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

		ListItem->Caption = TMoveProduct::VMoveProduct[ii]->DateTime.FormatString(wDateTimeFormat);

		if(TMoveProduct::VMoveProduct[ii]->MoveType == TMoveType::MOV_OUT) {
			if(TMoveProduct::VMoveProduct[ii]->SourceUnit == FormShop->ShopUnit) {
				ListItem->ImageIndex = TMoveType::MOV_OUT;
			} else {
				ListItem->ImageIndex = TMoveType::MOV_INC;
			}
		} else {
			ListItem->ImageIndex = TMoveProduct::VMoveProduct[ii]->MoveType;
		}

		if(TMoveProduct::VMoveProduct[ii]->bDeleted) {
			ListItem->Data = Pointer(ColorLV[7]);
		} else {
			ListItem->Data = Pointer(ColorLV[TMoveProduct::VMoveProduct[ii]->MoveType]);
		}

		AddSubItem(ListItem, FloatToStrF(TMoveProduct::VMoveProduct[ii]->id, ffNumber, 20, 0), ColumnsData[1].Visible);
		AddSubItem(ListItem, TMoveProduct::VMoveProduct[ii]->SourceUnit->Name, ColumnsData[2].Visible);
		AddSubItem(ListItem, TMoveProduct::VMoveProduct[ii]->SourcePerson->SumName, ColumnsData[3].Visible);
		AddSubItem(ListItem, TMoveProduct::VMoveProduct[ii]->TargetUnit->Name, ColumnsData[4].Visible);
		AddSubItem(ListItem, TMoveProduct::VMoveProduct[ii]->TargetPerson->SumName, ColumnsData[5].Visible);
		AddSubItem(ListItem, TMoveProduct::VMoveProduct[ii]->TotalCostPrice.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, TMoveProduct::VMoveProduct[ii]->TotalPrice.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TMoveProduct::VMoveProduct[ii]->Discount.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TMoveProduct::VMoveProduct[ii]->TotalPayment.StringFormat(), ColumnsData[9].Visible);
		AddSubItem(ListItem, TMoveProduct::VMoveProduct[ii]->ActualPayment.StringFormat(), ColumnsData[10].Visible);
		AddSubItem(ListItem, TMoveProduct::VMoveProduct[ii]->Debt.StringFormat(), ColumnsData[11].Visible);
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
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->DateTime < TMoveProduct::VMoveProduct[ipp[j]]->DateTime;
					break;
				case 1:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->id < TMoveProduct::VMoveProduct[ipp[j]]->id;
					break;
				case 2:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->SourceUnit->Name < TMoveProduct::VMoveProduct[ipp[j]]->SourceUnit->Name;
					break;
				case 3:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->SourcePerson->SumName < TMoveProduct::VMoveProduct[ipp[j]]->SourcePerson->SumName;
					break;
				case 4:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->TargetUnit->Name < TMoveProduct::VMoveProduct[ipp[j]]->TargetUnit->Name;
					break;
				case 5:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->TargetPerson->SumName < TMoveProduct::VMoveProduct[ipp[j]]->TargetPerson->SumName;
					break;
				case 6:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->TotalCostPrice.GetValue() < TMoveProduct::VMoveProduct[ipp[j]]->TotalCostPrice.GetValue();
					break;
				case 7:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->TotalPrice.GetValue() < TMoveProduct::VMoveProduct[ipp[j]]->TotalPrice.GetValue();
					break;
				case 8:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->Discount.GetValue() < TMoveProduct::VMoveProduct[ipp[j]]->Discount.GetValue();
					break;
				case 9:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->TotalPayment.GetValue() < TMoveProduct::VMoveProduct[ipp[j]]->TotalPayment.GetValue();
					break;
				case 10:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->ActualPayment.GetValue() < TMoveProduct::VMoveProduct[ipp[j]]->ActualPayment.GetValue();
					break;
				case 11:
					bSwap = TMoveProduct::VMoveProduct[ipp[i]]->Debt.GetValue() < TMoveProduct::VMoveProduct[ipp[j]]->Debt.GetValue();
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
		FormShop->FillPersonsData(TMoveProduct::VMoveProduct[ipp[iIndex]]);
	}
}

//---------------------------------------------------------------------------
TMoveProduct* __fastcall TMyListView::GetSelectMoveProduct(void)
{
	return TMoveProduct::VMoveProduct[ipp[ItemIndex]];
}
