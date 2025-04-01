//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "Provisioner.h"
#include "UnitProvisionerList.h"
#include "UnitProvisionerData.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListProvisioner(void)
{
	TListItem  *ListItem;
	UnicodeString uTmp;

	for(int i=0; i < (int)TProvisioner::VProvisioners.size(); i++) {

		bool bCond = true;

		if(FormProvisionerList->EditFindName->Text.Length() > 0) {
			bCond = (bCond && (TProvisioner::VProvisioners[i]->Surname.UpperCase().Pos(FormProvisionerList->EditFindName->Text.UpperCase()) ||
							   TProvisioner::VProvisioners[i]->Name.UpperCase().Pos(FormProvisionerList->EditFindName->Text.UpperCase()) ||
							   TProvisioner::VProvisioners[i]->Patronymic.UpperCase().Pos(FormProvisionerList->EditFindName->Text.UpperCase())) > 0);
		}
		if(FormProvisionerList->EditFindAttributs->Text.Length() > 0) {
			bCond = (bCond && (TProvisioner::VProvisioners[i]->Organization.UpperCase().Pos(FormProvisionerList->EditFindAttributs->Text.UpperCase()) ||
							   TProvisioner::VProvisioners[i]->Address.UpperCase().Pos(FormProvisionerList->EditFindAttributs->Text.UpperCase()) ||
							   TProvisioner::VProvisioners[i]->Phone1.UpperCase().Pos(FormProvisionerList->EditFindAttributs->Text.UpperCase()) ||
							   TProvisioner::VProvisioners[i]->Phone2.UpperCase().Pos(FormProvisionerList->EditFindAttributs->Text.UpperCase())) > 0);
		}

		if(bCond) {
			ListItem = Items->Add();
			ListItem->Caption = TProvisioner::VProvisioners[i]->Surname;
			ListItem->ImageIndex = -1;

			AddSubItem(ListItem, TProvisioner::VProvisioners[i]->Name, ColumnsData[1].Visible);
			AddSubItem(ListItem, TProvisioner::VProvisioners[i]->Patronymic, ColumnsData[2].Visible);
			AddSubItem(ListItem, TProvisioner::VProvisioners[i]->Organization, ColumnsData[3].Visible);
			AddSubItem(ListItem, TProvisioner::VProvisioners[i]->Address, ColumnsData[4].Visible);
			AddSubItem(ListItem, TProvisioner::VProvisioners[i]->Phone1, ColumnsData[5].Visible);
			AddSubItem(ListItem, TProvisioner::VProvisioners[i]->Phone2, ColumnsData[6].Visible);
			AddSubItem(ListItem, TProvisioner::VProvisioners[i]->TotalShoped.StringFormat(), ColumnsData[7].Visible);
			AddSubItem(ListItem, TProvisioner::VProvisioners[i]->TotalDiscount.StringFormat(), ColumnsData[8].Visible);
			AddSubItem(ListItem, TProvisioner::VProvisioners[i]->TotalDebt.StringFormat(), ColumnsData[9].Visible);

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
		ListItem->Caption = TProvisioner::VProvisioners[ii]->Surname;
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TProvisioner::VProvisioners[ii]->Name, ColumnsData[1].Visible);
		AddSubItem(ListItem, TProvisioner::VProvisioners[ii]->Patronymic, ColumnsData[2].Visible);
		AddSubItem(ListItem, TProvisioner::VProvisioners[ii]->Organization, ColumnsData[3].Visible);
		AddSubItem(ListItem, TProvisioner::VProvisioners[ii]->Address, ColumnsData[4].Visible);
		AddSubItem(ListItem, TProvisioner::VProvisioners[ii]->Phone1, ColumnsData[5].Visible);
		AddSubItem(ListItem, TProvisioner::VProvisioners[ii]->Phone2, ColumnsData[6].Visible);
		AddSubItem(ListItem, TProvisioner::VProvisioners[ii]->TotalShoped.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TProvisioner::VProvisioners[ii]->TotalDiscount.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TProvisioner::VProvisioners[ii]->TotalDebt.StringFormat(), ColumnsData[9].Visible);
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
					bSwap = TProvisioner::VProvisioners[ipp[i]]->Surname < TProvisioner::VProvisioners[ipp[j]]->Surname;
					break;
				case 1:
					bSwap = TProvisioner::VProvisioners[ipp[i]]->Name < TProvisioner::VProvisioners[ipp[j]]->Name;
					break;
				case 2:
					bSwap = TProvisioner::VProvisioners[ipp[i]]->Patronymic < TProvisioner::VProvisioners[ipp[j]]->Patronymic;
					break;
				case 3:
					bSwap = TProvisioner::VProvisioners[ipp[i]]->Organization < TProvisioner::VProvisioners[ipp[j]]->Organization;
					break;
				case 4:
					bSwap = TProvisioner::VProvisioners[ipp[i]]->Address < TProvisioner::VProvisioners[ipp[j]]->Address;
					break;
				case 5:
					bSwap = TProvisioner::VProvisioners[ipp[i]]->Phone1 < TProvisioner::VProvisioners[ipp[j]]->Phone1;
					break;
				case 6:
					bSwap = TProvisioner::VProvisioners[ipp[i]]->Phone2 < TProvisioner::VProvisioners[ipp[j]]->Phone2;
					break;
				case 7:
					bSwap = TProvisioner::VProvisioners[ipp[i]]->TotalShoped < TProvisioner::VProvisioners[ipp[j]]->TotalShoped;
					break;
				case 8:
					bSwap = TProvisioner::VProvisioners[ipp[i]]->TotalDiscount < TProvisioner::VProvisioners[ipp[j]]->TotalDiscount;
					break;
				case 9:
					bSwap = TProvisioner::VProvisioners[ipp[i]]->TotalDebt < TProvisioner::VProvisioners[ipp[j]]->TotalDebt;
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
	return TProvisioner::VProvisioners[ipp[ItemIndex]];
}
//---------------------------------------------------------------------------


