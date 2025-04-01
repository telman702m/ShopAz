//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "GroupProduct.h"
#include "UnitGroupList.h"
#include "Shop.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListGroupProduct(void)
{
	TListItem  *ListItem;

	for(unsigned i=0; i < TGroupProduct::VGroupProduct.size(); i++) {
		ListItem = Items->Add();
		ListItem->Caption = TGroupProduct::VGroupProduct[i]->GroupCode;
		ListItem->ImageIndex = -1;

		ListItem->SubItems->Add(TGroupProduct::VGroupProduct[i]->Name);
		ListItem->SubItems->Add(TGroupProduct::VGroupProduct[i]->Description);

		ipp.push_back(i);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillArangeListGroup(void)
{
	UnicodeString uTmp;
	TListItem  *ListItem;

	for(int i=0; i<(int)ipp.size(); i++) {
		int ii = ipp[i];
		ListItem = Items->Add();
		ListItem->Caption = TGroupProduct::VGroupProduct[ii]->GroupCode;
		ListItem->ImageIndex = -1;

		ListItem->SubItems->Add(TGroupProduct::VGroupProduct[ii]->Name);
		ListItem->SubItems->Add(TGroupProduct::VGroupProduct[ii]->Description);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::SortGroups(int iColumn)
{
	bArrangeOrder[iColumn] = !bArrangeOrder[iColumn];

	bool bSwap;

	for(unsigned i=0; i < ipp.size(); i++) {
		for(unsigned j=i+1; j < ipp.size(); j++) {
			switch(iColumn) {
				case 0:
					bSwap = TGroupProduct::VGroupProduct[ipp[i]]->GroupCode < TGroupProduct::VGroupProduct[ipp[j]]->GroupCode;
					break;
				case 1:
					bSwap = TGroupProduct::VGroupProduct[ipp[i]]->Name < TGroupProduct::VGroupProduct[ipp[j]]->Name;
					break;
				case 2:
					bSwap = TGroupProduct::VGroupProduct[ipp[i]]->Description < TGroupProduct::VGroupProduct[ipp[j]]->Description;
					break;
			}
			if(bArrangeOrder[iColumn]) {
				bSwap = !bSwap;
			}
			if(bSwap) {
				swap(ipp[i], ipp[j]);
			}
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::GroupsKeyDown(TObject *Sender, WORD &Key, int iIndex)
{
	switch(Key) {
		case VK_F3:
			FormGroupList->ButtonAction = TButtonAction::BA_VIEW;
			break;
		case VK_F4:
			FormGroupList->ButtonAction = TButtonAction::BA_EDIT;
			break;
		case VK_INSERT:
			FormGroupList->ButtonAction = TButtonAction::BA_ADD;
			break;
		case VK_DELETE:
			FormGroupList->ButtonAction = TButtonAction::BA_DEL;
			FormGroupList->DeleteItem();
			return;
		default:
			return;
	}
	FormGroupList->ToolButtonsClickAction(FormGroupList->ButtonAction);
}
//---------------------------------------------------------------------------

