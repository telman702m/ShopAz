//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "UnitShopUnitList.h"
#include "ShopUnits.h"
#include "UnitShopUnitData.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListShopUnit(void)
{
	TListItem  *ListItem;
	UnicodeString uTmp;

	for(unsigned i=0; i < TShopUnits::VShopUnits.size(); i++) {

		ListItem = Items->Add();
		ListItem->Caption = FormShopUnit->ComboBoxType->Items->Strings[TShopUnits::VShopUnits[i]->TypeUnit];
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->Name, ColumnsData[1].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->Address, ColumnsData[2].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->Phone1, ColumnsData[3].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->Phone2, ColumnsData[4].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->Description, ColumnsData[5].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->TotalIncoming.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->TotalMoved.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->TotalShoped.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->TotalReturn.StringFormat(), ColumnsData[9].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->TotalDiscount.StringFormat(), ColumnsData[10].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[i]->TotalDebt.StringFormat(), ColumnsData[11].Visible);

		ipp.push_back(i);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillArangedListShopUnit(void)
{
	UnicodeString uTmp;
	TListItem  *ListItem;

	for(int i=0; i<(int)ipp.size(); i++) {
		int ii = ipp[i];
		ListItem = Items->Add();
		ListItem->Caption = FormShopUnit->ComboBoxType->Items->Strings[TShopUnits::VShopUnits[ii]->TypeUnit];
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->Name, ColumnsData[1].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->Address, ColumnsData[2].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->Phone1, ColumnsData[3].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->Phone2, ColumnsData[4].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->Description, ColumnsData[5].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->TotalIncoming.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->TotalMoved.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->TotalShoped.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->TotalReturn.StringFormat(), ColumnsData[9].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->TotalDiscount.StringFormat(), ColumnsData[10].Visible);
		AddSubItem(ListItem, TShopUnits::VShopUnits[ii]->TotalDebt.StringFormat(), ColumnsData[11].Visible);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::SortShopUnit(int iColumn)
{
	int iIndexColumnData = GetIndexColumnData(iColumn);
	bArrangeOrder[iIndexColumnData] = !bArrangeOrder[iIndexColumnData];

	bool bSwap;

	for(unsigned i=0; i < ipp.size(); i++) {
		for(unsigned j=i+1; j < ipp.size(); j++) {
			switch(iIndexColumnData) {
				case 0:
					bSwap = FormShopUnit->ComboBoxType->Items->Strings[TShopUnits::VShopUnits[ipp[i]]->TypeUnit] < FormShopUnit->ComboBoxType->Items->Strings[TShopUnits::VShopUnits[ipp[j]]->TypeUnit];
					break;
				case 1:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->Name < TShopUnits::VShopUnits[ipp[j]]->Name;
					break;
				case 2:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->Address < TShopUnits::VShopUnits[ipp[j]]->Address;
					break;
				case 3:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->Phone1 < TShopUnits::VShopUnits[ipp[j]]->Phone1;
					break;
				case 4:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->Phone2 < TShopUnits::VShopUnits[ipp[j]]->Phone2;
					break;
				case 5:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->Description < TShopUnits::VShopUnits[ipp[j]]->Description;
					break;
				case 6:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->TotalIncoming < TShopUnits::VShopUnits[ipp[j]]->TotalIncoming;
					break;
				case 7:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->TotalMoved < TShopUnits::VShopUnits[ipp[j]]->TotalMoved;
					break;
				case 8:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->TotalShoped < TShopUnits::VShopUnits[ipp[j]]->TotalShoped;
					break;
				case 9:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->TotalReturn < TShopUnits::VShopUnits[ipp[j]]->TotalReturn;
					break;
				case 10:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->TotalDiscount < TShopUnits::VShopUnits[ipp[j]]->TotalDiscount;
					break;
				case 11:
					bSwap = TShopUnits::VShopUnits[ipp[i]]->TotalDebt < TShopUnits::VShopUnits[ipp[j]]->TotalDebt;
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
void __fastcall TMyListView::ShopUnitDblClick(TObject *Sender)
{
	TToolButton *TbView = FormParent->GetToolButton(FormShopUnitsList->ToolBar1, L"ToolButtonView");
	if(TbView != NULL) {
		TbView->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMyListView::ShopUnitKeyDown(TObject *Sender, WORD &Key, int iIndex)
{
	switch(Key) {
		case VK_F3:
			FormShopUnitsList->ButtonAction = TButtonAction::BA_VIEW;
			break;
		case VK_F4:
			FormShopUnitsList->ButtonAction = TButtonAction::BA_EDIT;
			break;
		case VK_INSERT:
			FormShopUnitsList->ButtonAction = TButtonAction::BA_ADD;
			break;
		case VK_DELETE:
			FormShopUnitsList->ButtonAction = TButtonAction::BA_DEL;
			FormShopUnitsList->DeleteItem();
			return;
		default:
			return;
	}
	FormShopUnitsList->ToolButtonsClickAction(FormShopUnitsList->ButtonAction);
}

//---------------------------------------------------------------------------
TShopUnits* __fastcall TMyListView::GetSelectShopUnit(void)
{
	return TShopUnits::VShopUnits[ipp[ItemIndex]];
}
//---------------------------------------------------------------------------


