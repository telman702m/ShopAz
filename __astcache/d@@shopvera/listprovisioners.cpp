//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "Provisioner.h"
#include "UnitProvisionerList.h"
#include "UnitProvisionerData.h"
#include "ObjectManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListProvisioner(void)
{
	TListItem  *ListItem;
	UnicodeString uTmp;

	for(unsigned i=0; i < TObjectManager<TProvisioner>::GetList().size(); i++) {

		bool bCond = true;

		if(FormProvisionerList->EditFindName->Text.Length() > 0) {
			bCond = (bCond && (TObjectManager<TProvisioner>::GetList()[i]->Surname.UpperCase().Pos(FormProvisionerList->EditFindName->Text.UpperCase()) ||
							   TObjectManager<TProvisioner>::GetList()[i]->Name.UpperCase().Pos(FormProvisionerList->EditFindName->Text.UpperCase()) ||
							   TObjectManager<TProvisioner>::GetList()[i]->Patronymic.UpperCase().Pos(FormProvisionerList->EditFindName->Text.UpperCase())) > 0);
		}
		if(FormProvisionerList->EditFindAttributs->Text.Length() > 0) {
			bCond = (bCond && (TObjectManager<TProvisioner>::GetList()[i]->Organization.UpperCase().Pos(FormProvisionerList->EditFindAttributs->Text.UpperCase()) ||
							   TObjectManager<TProvisioner>::GetList()[i]->Address.UpperCase().Pos(FormProvisionerList->EditFindAttributs->Text.UpperCase()) ||
							   TObjectManager<TProvisioner>::GetList()[i]->Phone1.UpperCase().Pos(FormProvisionerList->EditFindAttributs->Text.UpperCase()) ||
							   TObjectManager<TProvisioner>::GetList()[i]->Phone2.UpperCase().Pos(FormProvisionerList->EditFindAttributs->Text.UpperCase())) > 0);
		}

		if(bCond) {
			ListItem = Items->Add();
			ListItem->Caption = TObjectManager<TProvisioner>::GetList()[i]->Surname;
			ListItem->ImageIndex = -1;

			AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[i]->Name, ColumnsData[1].Visible);
			AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[i]->Patronymic, ColumnsData[2].Visible);
			AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[i]->Organization, ColumnsData[3].Visible);
			AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[i]->Address, ColumnsData[4].Visible);
			AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[i]->Phone1, ColumnsData[5].Visible);
			AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[i]->Phone2, ColumnsData[6].Visible);
			AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[i]->TotalShoped.StringFormat(), ColumnsData[7].Visible);
			AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[i]->TotalDiscount.StringFormat(), ColumnsData[8].Visible);
			AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[i]->TotalDebt.StringFormat(), ColumnsData[9].Visible);

			ipp.push_back(i);
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillArangedListProvisioner(void)
{
	UnicodeString uTmp;
	TListItem  *ListItem;

	for(int i=0; i<(int)ipp.size(); i++) {
		int ii = ipp[i];
		ListItem = Items->Add();
		ListItem->Caption = TObjectManager<TProvisioner>::GetList()[ii]->Surname;
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[ii]->Name, ColumnsData[1].Visible);
		AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[ii]->Patronymic, ColumnsData[2].Visible);
		AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[ii]->Organization, ColumnsData[3].Visible);
		AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[ii]->Address, ColumnsData[4].Visible);
		AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[ii]->Phone1, ColumnsData[5].Visible);
		AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[ii]->Phone2, ColumnsData[6].Visible);
		AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[ii]->TotalShoped.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[ii]->TotalDiscount.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TObjectManager<TProvisioner>::GetList()[ii]->TotalDebt.StringFormat(), ColumnsData[9].Visible);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::SortProvisioners(int iColumn)
{
	int iIndexColumnData = GetIndexColumnData(iColumn);
	bArrangeOrder[iIndexColumnData] = !bArrangeOrder[iIndexColumnData];

	bool bSwap;

	for(unsigned i=0; i < ipp.size(); i++) {
		for(unsigned j=i+1; j < ipp.size(); j++) {
			switch(iIndexColumnData) {
				case 0:
					bSwap = TObjectManager<TProvisioner>::GetList()[ipp[i]]->Surname < TObjectManager<TProvisioner>::GetList()[ipp[j]]->Surname;
					break;
				case 1:
					bSwap = TObjectManager<TProvisioner>::GetList()[ipp[i]]->Name < TObjectManager<TProvisioner>::GetList()[ipp[j]]->Name;
					break;
				case 2:
					bSwap = TObjectManager<TProvisioner>::GetList()[ipp[i]]->Patronymic < TObjectManager<TProvisioner>::GetList()[ipp[j]]->Patronymic;
					break;
				case 3:
					bSwap = TObjectManager<TProvisioner>::GetList()[ipp[i]]->Organization < TObjectManager<TProvisioner>::GetList()[ipp[j]]->Organization;
					break;
				case 4:
					bSwap = TObjectManager<TProvisioner>::GetList()[ipp[i]]->Address < TObjectManager<TProvisioner>::GetList()[ipp[j]]->Address;
					break;
				case 5:
					bSwap = TObjectManager<TProvisioner>::GetList()[ipp[i]]->Phone1 < TObjectManager<TProvisioner>::GetList()[ipp[j]]->Phone1;
					break;
				case 6:
					bSwap = TObjectManager<TProvisioner>::GetList()[ipp[i]]->Phone2 < TObjectManager<TProvisioner>::GetList()[ipp[j]]->Phone2;
					break;
				case 7:
					bSwap = TObjectManager<TProvisioner>::GetList()[ipp[i]]->TotalShoped < TObjectManager<TProvisioner>::GetList()[ipp[j]]->TotalShoped;
					break;
				case 8:
					bSwap = TObjectManager<TProvisioner>::GetList()[ipp[i]]->TotalDiscount < TObjectManager<TProvisioner>::GetList()[ipp[j]]->TotalDiscount;
					break;
				case 9:
					bSwap = TObjectManager<TProvisioner>::GetList()[ipp[i]]->TotalDebt < TObjectManager<TProvisioner>::GetList()[ipp[j]]->TotalDebt;
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
void __fastcall TMyListView::ProvisionersDblClick(TObject *Sender)
{
	TToolButton *TbView = FormParent->GetToolButton(FormProvisionerList->ToolBar1, L"ToolButtonView");
	if(TbView != NULL) {
		TbView->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMyListView::ProvisionersKeyDown(TObject *Sender, WORD &Key, int iIndex)
{
	switch(Key) {
		case VK_F3:
			FormProvisionerList->ButtonAction = TButtonAction::BA_VIEW;
			break;
		case VK_F4:
			FormProvisionerList->ButtonAction = TButtonAction::BA_EDIT;
			break;
		case VK_INSERT:
			FormProvisionerList->ButtonAction = TButtonAction::BA_ADD;
			break;
		case VK_DELETE:
			FormProvisionerList->ButtonAction = TButtonAction::BA_DEL;
			FormProvisionerList->DeleteItem();
			return;
		default:
			return;
	}
	FormProvisionerList->ToolButtonsClickAction(FormProvisionerList->ButtonAction);
}

//---------------------------------------------------------------------------
TProvisioner* __fastcall TMyListView::GetSelectProvisioner(void)
{
	return TObjectManager<TProvisioner>::GetList()[ipp[ItemIndex]];
}
//---------------------------------------------------------------------------


