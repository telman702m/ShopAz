//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "UnitBuyerList.h"
#include "UnitBuyerData.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListBuyer(void)
{
	TListItem  *ListItem;
	UnicodeString uTmp;

	for(unsigned i=0; i < TBuyer::VBuyers.size(); i++) {

		bool bCond = true;

		if(FormBuyerList->EditFindName->Text.Length() > 0) {
			bCond = (bCond && (TBuyer::VBuyers[i]->Surname.UpperCase().Pos(FormBuyerList->EditFindName->Text.UpperCase()) ||
							   TBuyer::VBuyers[i]->Name.UpperCase().Pos(FormBuyerList->EditFindName->Text.UpperCase()) ||
							   TBuyer::VBuyers[i]->Patronymic.UpperCase().Pos(FormBuyerList->EditFindName->Text.UpperCase())) > 0);
		}
		if(FormBuyerList->EditFindAttributs->Text.Length() > 0) {
			bCond = (bCond && (TBuyer::VBuyers[i]->Organization.UpperCase().Pos(FormBuyerList->EditFindAttributs->Text.UpperCase()) ||
							   TBuyer::VBuyers[i]->Address.UpperCase().Pos(FormBuyerList->EditFindAttributs->Text.UpperCase()) ||
							   TBuyer::VBuyers[i]->Phone1.UpperCase().Pos(FormBuyerList->EditFindAttributs->Text.UpperCase()) ||
							   TBuyer::VBuyers[i]->Phone2.UpperCase().Pos(FormBuyerList->EditFindAttributs->Text.UpperCase())) > 0);
		}

		if(bCond) {
			ListItem = Items->Add();
			ListItem->Caption = TBuyer::VBuyers[i]->Surname;
			ListItem->ImageIndex = -1;

			AddSubItem(ListItem, TBuyer::VBuyers[i]->Name, ColumnsData[1].Visible);
			AddSubItem(ListItem, TBuyer::VBuyers[i]->Patronymic, ColumnsData[2].Visible);
			AddSubItem(ListItem, TBuyer::VBuyers[i]->Organization, ColumnsData[3].Visible);
			AddSubItem(ListItem, TBuyer::VBuyers[i]->Address, ColumnsData[4].Visible);
			AddSubItem(ListItem, TBuyer::VBuyers[i]->Phone1, ColumnsData[5].Visible);
			AddSubItem(ListItem, TBuyer::VBuyers[i]->Phone2, ColumnsData[6].Visible);
			AddSubItem(ListItem, TBuyer::VBuyers[i]->TotalShoped.StringFormat(), ColumnsData[7].Visible);
			AddSubItem(ListItem, TBuyer::VBuyers[i]->TotalReturn.StringFormat(), ColumnsData[8].Visible);
			AddSubItem(ListItem, TBuyer::VBuyers[i]->TotalDiscount.StringFormat(), ColumnsData[9].Visible);
			AddSubItem(ListItem, TBuyer::VBuyers[i]->TotalDebt.StringFormat(), ColumnsData[10].Visible);

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
		ListItem->Caption = TBuyer::VBuyers[ii]->Surname;
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TBuyer::VBuyers[ii]->Name, ColumnsData[1].Visible);
		AddSubItem(ListItem, TBuyer::VBuyers[ii]->Patronymic, ColumnsData[2].Visible);
		AddSubItem(ListItem, TBuyer::VBuyers[ii]->Organization, ColumnsData[3].Visible);
		AddSubItem(ListItem, TBuyer::VBuyers[ii]->Address, ColumnsData[4].Visible);
		AddSubItem(ListItem, TBuyer::VBuyers[ii]->Phone1, ColumnsData[5].Visible);
		AddSubItem(ListItem, TBuyer::VBuyers[ii]->Phone2, ColumnsData[6].Visible);
		AddSubItem(ListItem, TBuyer::VBuyers[ii]->TotalShoped.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TBuyer::VBuyers[ii]->TotalReturn.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TBuyer::VBuyers[ii]->TotalDiscount.StringFormat(), ColumnsData[9].Visible);
		AddSubItem(ListItem, TBuyer::VBuyers[ii]->TotalDebt.StringFormat(), ColumnsData[10].Visible);
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
					bSwap = TBuyer::VBuyers[ipp[i]]->Surname < TBuyer::VBuyers[ipp[j]]->Surname;
					break;
				case 1:
					bSwap = TBuyer::VBuyers[ipp[i]]->Name < TBuyer::VBuyers[ipp[j]]->Name;
					break;
				case 2:
					bSwap = TBuyer::VBuyers[ipp[i]]->Patronymic < TBuyer::VBuyers[ipp[j]]->Patronymic;
					break;
				case 3:
					bSwap = TBuyer::VBuyers[ipp[i]]->Organization < TBuyer::VBuyers[ipp[j]]->Organization;
					break;
				case 4:
					bSwap = TBuyer::VBuyers[ipp[i]]->Address < TBuyer::VBuyers[ipp[j]]->Address;
					break;
				case 5:
					bSwap = TBuyer::VBuyers[ipp[i]]->Phone1 < TBuyer::VBuyers[ipp[j]]->Phone1;
					break;
				case 6:
					bSwap = TBuyer::VBuyers[ipp[i]]->Phone2 < TBuyer::VBuyers[ipp[j]]->Phone2;
					break;
				case 7:
					bSwap = TBuyer::VBuyers[ipp[i]]->TotalShoped < TBuyer::VBuyers[ipp[j]]->TotalShoped;
					break;
				case 8:
					bSwap = TBuyer::VBuyers[ipp[i]]->TotalReturn < TBuyer::VBuyers[ipp[j]]->TotalReturn;
					break;
				case 9:
					bSwap = TBuyer::VBuyers[ipp[i]]->TotalDiscount < TBuyer::VBuyers[ipp[j]]->TotalDiscount;
					break;
				case 10:
					bSwap = TBuyer::VBuyers[ipp[i]]->TotalDebt < TBuyer::VBuyers[ipp[j]]->TotalDebt;
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
	return TBuyer::VBuyers[ipp[ItemIndex]];
}
//---------------------------------------------------------------------------


