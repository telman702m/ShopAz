//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "UnitBuyerList.h"
#include "UnitBuyerData.h"
#include "ObjectManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListBuyer(void)
{
	TListItem  *ListItem;
	UnicodeString uTmp;

	for(unsigned i=0; i < TObjectManager<TBuyer>::GetList().size(); i++) {

		bool bCond = true;

		if(FormBuyerList->EditFindName->Text.Length() > 0) {
			bCond = (bCond && (TObjectManager<TBuyer>::GetList()[i]->Surname.UpperCase().Pos(FormBuyerList->EditFindName->Text.UpperCase()) ||
							   TObjectManager<TBuyer>::GetList()[i]->Name.UpperCase().Pos(FormBuyerList->EditFindName->Text.UpperCase()) ||
							   TObjectManager<TBuyer>::GetList()[i]->Patronymic.UpperCase().Pos(FormBuyerList->EditFindName->Text.UpperCase())) > 0);
		}
		if(FormBuyerList->EditFindAttributs->Text.Length() > 0) {
			bCond = (bCond && (TObjectManager<TBuyer>::GetList()[i]->Organization.UpperCase().Pos(FormBuyerList->EditFindAttributs->Text.UpperCase()) ||
							   TObjectManager<TBuyer>::GetList()[i]->Address.UpperCase().Pos(FormBuyerList->EditFindAttributs->Text.UpperCase()) ||
							   TObjectManager<TBuyer>::GetList()[i]->Phone1.UpperCase().Pos(FormBuyerList->EditFindAttributs->Text.UpperCase()) ||
							   TObjectManager<TBuyer>::GetList()[i]->Phone2.UpperCase().Pos(FormBuyerList->EditFindAttributs->Text.UpperCase())) > 0);
		}

		if(bCond) {
			ListItem = Items->Add();
			ListItem->Caption = TObjectManager<TBuyer>::GetList()[i]->Surname;
			ListItem->ImageIndex = -1;

			AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[i]->Name, ColumnsData[1].Visible);
			AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[i]->Patronymic, ColumnsData[2].Visible);
			AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[i]->Organization, ColumnsData[3].Visible);
			AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[i]->Address, ColumnsData[4].Visible);
			AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[i]->Phone1, ColumnsData[5].Visible);
			AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[i]->Phone2, ColumnsData[6].Visible);
			AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[i]->TotalShoped.StringFormat(), ColumnsData[7].Visible);
			AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[i]->TotalReturn.StringFormat(), ColumnsData[8].Visible);
			AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[i]->TotalDiscount.StringFormat(), ColumnsData[9].Visible);
			AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[i]->TotalDebt.StringFormat(), ColumnsData[10].Visible);

			ipp.push_back(i);
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillArangedListBuyer(void)
{
	UnicodeString uTmp;
	TListItem  *ListItem;

	for(int i=0; i<(int)ipp.size(); i++) {
		int ii = ipp[i];
		ListItem = Items->Add();
		ListItem->Caption = TObjectManager<TBuyer>::GetList()[ii]->Surname;
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[ii]->Name, ColumnsData[1].Visible);
		AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[ii]->Patronymic, ColumnsData[2].Visible);
		AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[ii]->Organization, ColumnsData[3].Visible);
		AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[ii]->Address, ColumnsData[4].Visible);
		AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[ii]->Phone1, ColumnsData[5].Visible);
		AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[ii]->Phone2, ColumnsData[6].Visible);
		AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[ii]->TotalShoped.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[ii]->TotalReturn.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[ii]->TotalDiscount.StringFormat(), ColumnsData[9].Visible);
		AddSubItem(ListItem, TObjectManager<TBuyer>::GetList()[ii]->TotalDebt.StringFormat(), ColumnsData[10].Visible);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::SortBuyers(int iColumn)
{
	int iIndexColumnData = GetIndexColumnData(iColumn);
	bArrangeOrder[iIndexColumnData] = !bArrangeOrder[iIndexColumnData];

	bool bSwap;

	for(unsigned i=0; i < ipp.size(); i++) {
		for(unsigned j=i+1; j < ipp.size(); j++) {
			switch(iIndexColumnData) {
				case 0:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->Surname < TObjectManager<TBuyer>::GetList()[ipp[j]]->Surname;
					break;
				case 1:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->Name < TObjectManager<TBuyer>::GetList()[ipp[j]]->Name;
					break;
				case 2:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->Patronymic < TObjectManager<TBuyer>::GetList()[ipp[j]]->Patronymic;
					break;
				case 3:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->Organization < TObjectManager<TBuyer>::GetList()[ipp[j]]->Organization;
					break;
				case 4:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->Address < TObjectManager<TBuyer>::GetList()[ipp[j]]->Address;
					break;
				case 5:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->Phone1 < TObjectManager<TBuyer>::GetList()[ipp[j]]->Phone1;
					break;
				case 6:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->Phone2 < TObjectManager<TBuyer>::GetList()[ipp[j]]->Phone2;
					break;
				case 7:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->TotalShoped < TObjectManager<TBuyer>::GetList()[ipp[j]]->TotalShoped;
					break;
				case 8:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->TotalReturn < TObjectManager<TBuyer>::GetList()[ipp[j]]->TotalReturn;
					break;
				case 9:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->TotalDiscount < TObjectManager<TBuyer>::GetList()[ipp[j]]->TotalDiscount;
					break;
				case 10:
					bSwap = TObjectManager<TBuyer>::GetList()[ipp[i]]->TotalDebt < TObjectManager<TBuyer>::GetList()[ipp[j]]->TotalDebt;
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
void __fastcall TMyListView::BuyersDblClick(TObject *Sender)
{
	TToolButton *TbView = FormParent->GetToolButton(FormBuyerList->ToolBar1, L"ToolButtonView");
	if(TbView != NULL) {
		TbView->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMyListView::BuyersKeyDown(TObject *Sender, WORD &Key, int iIndex)
{
	switch(Key) {
		case VK_F3:
			FormBuyerList->ButtonAction = TButtonAction::BA_VIEW;
			break;
		case VK_F4:
			FormBuyerList->ButtonAction = TButtonAction::BA_EDIT;
			break;
		case VK_INSERT:
			FormBuyerList->ButtonAction = TButtonAction::BA_ADD;
			break;
		case VK_DELETE:
			FormBuyerList->ButtonAction = TButtonAction::BA_DEL;
			FormBuyerList->DeleteItem();
			return;
		default:
			return;
	}
	FormBuyerList->ToolButtonsClickAction(FormBuyerList->ButtonAction);
}

//---------------------------------------------------------------------------
TBuyer* __fastcall TMyListView::GetSelectBuyer(void)
{
	return TObjectManager<TBuyer>::GetList()[ipp[ItemIndex]];
}
//---------------------------------------------------------------------------


