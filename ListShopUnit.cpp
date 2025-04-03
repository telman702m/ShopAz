//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "UnitShopUnitList.h"
#include "ShopUnits.h"
#include "UnitShopUnitData.h"
#include "ObjectManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListShopUnit(void)
{
	TListItem  *ListItem;
	UnicodeString uTmp;

	for(unsigned i=0; i < TObjectManager<TShopUnits>::GetList().size(); i++) {

		ListItem = Items->Add();
		ListItem->Caption = FormShopUnit->ComboBoxType->Items->Strings[TObjectManager<TShopUnits>::GetList()[i]->TypeUnit];
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->Name, ColumnsData[1].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->Address, ColumnsData[2].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->Phone1, ColumnsData[3].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->Phone2, ColumnsData[4].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->Description, ColumnsData[5].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->TotalIncoming.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->TotalMoved.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->TotalShoped.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->TotalReturn.StringFormat(), ColumnsData[9].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->TotalDiscount.StringFormat(), ColumnsData[10].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[i]->TotalDebt.StringFormat(), ColumnsData[11].Visible);

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
		ListItem->Caption = FormShopUnit->ComboBoxType->Items->Strings[TObjectManager<TShopUnits>::GetList()[ii]->TypeUnit];
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->Name, ColumnsData[1].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->Address, ColumnsData[2].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->Phone1, ColumnsData[3].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->Phone2, ColumnsData[4].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->Description, ColumnsData[5].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->TotalIncoming.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->TotalMoved.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->TotalShoped.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->TotalReturn.StringFormat(), ColumnsData[9].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->TotalDiscount.StringFormat(), ColumnsData[10].Visible);
		AddSubItem(ListItem, TObjectManager<TShopUnits>::GetList()[ii]->TotalDebt.StringFormat(), ColumnsData[11].Visible);
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
					bSwap = FormShopUnit->ComboBoxType->Items->Strings[TObjectManager<TShopUnits>::GetList()[ipp[i]]->TypeUnit] < FormShopUnit->ComboBoxType->Items->Strings[TObjectManager<TShopUnits>::GetList()[ipp[j]]->TypeUnit];
					break;
				case 1:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->Name < TObjectManager<TShopUnits>::GetList()[ipp[j]]->Name;
					break;
				case 2:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->Address < TObjectManager<TShopUnits>::GetList()[ipp[j]]->Address;
					break;
				case 3:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->Phone1 < TObjectManager<TShopUnits>::GetList()[ipp[j]]->Phone1;
					break;
				case 4:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->Phone2 < TObjectManager<TShopUnits>::GetList()[ipp[j]]->Phone2;
					break;
				case 5:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->Description < TObjectManager<TShopUnits>::GetList()[ipp[j]]->Description;
					break;
				case 6:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->TotalIncoming < TObjectManager<TShopUnits>::GetList()[ipp[j]]->TotalIncoming;
					break;
				case 7:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->TotalMoved < TObjectManager<TShopUnits>::GetList()[ipp[j]]->TotalMoved;
					break;
				case 8:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->TotalShoped < TObjectManager<TShopUnits>::GetList()[ipp[j]]->TotalShoped;
					break;
				case 9:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->TotalReturn < TObjectManager<TShopUnits>::GetList()[ipp[j]]->TotalReturn;
					break;
				case 10:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->TotalDiscount < TObjectManager<TShopUnits>::GetList()[ipp[j]]->TotalDiscount;
					break;
				case 11:
					bSwap = TObjectManager<TShopUnits>::GetList()[ipp[i]]->TotalDebt < TObjectManager<TShopUnits>::GetList()[ipp[j]]->TotalDebt;
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
	return TObjectManager<TShopUnits>::GetList()[ipp[ItemIndex]];
}
//---------------------------------------------------------------------------


