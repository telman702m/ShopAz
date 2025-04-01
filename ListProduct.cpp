//---------------------------------------------------------------------------
#pragma hdrstop

#include "GroupProduct.h"
#include "UnitGroupList.h"
#include "UnitProductList.h"
#include "Shop.h"
#include "MyListView.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListProduct(void)
{
//	ColumnsCreat();

	TListItem  *ListItem;

	unsigned Count = TProduct::VProduct.size();

	for(unsigned i=0; i < Count; i++) {
		if(FormProductList->FilteredProduct(i)) {
			ListItem = Items->Add();
			ListItem->Caption = TProduct::VProduct[i]->GroupProd->Name;
			ListItem->ImageIndex = -1;

			AddSubItem(ListItem, TProduct::VProduct[i]->Code, ColumnsData[1].Visible);
			AddSubItem(ListItem, TProduct::VProduct[i]->Name, ColumnsData[2].Visible);

			if(TProduct::VProduct[i]->WholeUnit) {
				AddSubItem(ListItem, TProduct::VProduct[i]->Unit, ColumnsData[3].Visible);
			} else {
				UnicodeString uTmp = L"[" + TProduct::VProduct[i]->Unit + L"]";
				AddSubItem(ListItem, uTmp, ColumnsData[3].Visible);
			}
			AddSubItem(ListItem, TProduct::VProduct[i]->PurchaseCash.StringFormat(), ColumnsData[4].Visible);
			AddSubItem(ListItem, TProduct::VProduct[i]->DollarPrice.StringFormat(), ColumnsData[5].Visible);
			AddSubItem(ListItem, TProduct::VProduct[i]->SellingPrice.StringFormat(), ColumnsData[6].Visible);
			AddSubItem(ListItem, TProduct::VProduct[i]->WholePrice.StringFormat(), ColumnsData[7].Visible);

			for(unsigned j=0; j < TShopUnits::VShopUnits.size(); j++) {
				AddSubItem(ListItem, TProduct::VProduct[i]->CountBalance[TShopUnits::upp[j]].StringFormat(),
						   ColumnsData[FormProductList->CountStatColumn + j].Visible);
			}

			ipp.push_back(i);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TMyListView::FillArangeListProduct(void)
{
	TListItem  *ListItem;

	unsigned Count = ipp.size();

	for(unsigned i=0; i < Count; i++) {
		int ii = ipp[i];
		ListItem = Items->Add();
		ListItem->Caption = TProduct::VProduct[ii]->GroupProd->Name;
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TProduct::VProduct[ii]->Code, ColumnsData[1].Visible);
		AddSubItem(ListItem, TProduct::VProduct[ii]->Name, ColumnsData[2].Visible);

		if(TProduct::VProduct[ii]->WholeUnit) {
			AddSubItem(ListItem, TProduct::VProduct[ii]->Unit, ColumnsData[3].Visible);
		} else {
			UnicodeString uTmp = L"[" + TProduct::VProduct[ii]->Unit + L"]";
			AddSubItem(ListItem, uTmp, ColumnsData[3].Visible);
		}
		AddSubItem(ListItem, TProduct::VProduct[ii]->PurchaseCash.StringFormat(), ColumnsData[4].Visible);
		AddSubItem(ListItem, TProduct::VProduct[ii]->DollarPrice.StringFormat(), ColumnsData[5].Visible);
		AddSubItem(ListItem, TProduct::VProduct[ii]->SellingPrice.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, TProduct::VProduct[ii]->WholePrice.StringFormat(), ColumnsData[7].Visible);

		for(unsigned j=0; j < TShopUnits::VShopUnits.size(); j++) {
			AddSubItem(ListItem, TProduct::VProduct[ii]->CountBalance[TShopUnits::upp[j]].StringFormat(),
					   ColumnsData[FormProductList->CountStatColumn + j].Visible);
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::SortProducts(int iColumn)
{
	int iIndexColumnData = GetIndexColumnData(iColumn);
	bArrangeOrder[iIndexColumnData] = !bArrangeOrder[iIndexColumnData];

	bool bSwap;

	for(unsigned i=0; i < ipp.size(); i++) {
		for(unsigned j=i+1; j < ipp.size(); j++) {
			switch(iIndexColumnData) {
				case 0:
					bSwap = TProduct::VProduct[ipp[i]]->GroupProd->Name < TProduct::VProduct[ipp[j]]->GroupProd->Name;
					break;
				case 1:
					bSwap = TProduct::VProduct[ipp[i]]->Code < TProduct::VProduct[ipp[j]]->Code;
					break;
				case 2:
					bSwap = TProduct::VProduct[ipp[i]]->Name < TProduct::VProduct[ipp[j]]->Name;
					break;
				case 3:
					bSwap = TProduct::VProduct[ipp[i]]->Unit < TProduct::VProduct[ipp[j]]->Unit;
					break;
				case 4:
					bSwap = TProduct::VProduct[ipp[i]]->PurchaseCash < TProduct::VProduct[ipp[j]]->PurchaseCash;
					break;
				case 5:
					bSwap = TProduct::VProduct[ipp[i]]->DollarPrice < TProduct::VProduct[ipp[j]]->DollarPrice;
					break;
				case 6:
					bSwap = TProduct::VProduct[ipp[i]]->SellingPrice < TProduct::VProduct[ipp[j]]->SellingPrice;
					break;
				case 7:
					bSwap = TProduct::VProduct[ipp[i]]->WholePrice < TProduct::VProduct[ipp[j]]->WholePrice;
					break;
				default:
					// Balance in units
					bSwap = TProduct::VProduct[ipp[i]]->CountBalance[TShopUnits::upp[iIndexColumnData - 8]] <
							TProduct::VProduct[ipp[j]]->CountBalance[TShopUnits::upp[iIndexColumnData - 8]];
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
void __fastcall TMyListView::ProductsDblClick(TObject *Sender)
{
	TToolButton *TbView = FormParent->GetToolButton(FormProductList->ToolBar1, L"ToolButtonView");
	if(TbView != NULL) {
		TbView->Click();
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::ProductsKeyDown(TObject *Sender, WORD &Key, int iIndex)
{
	switch(Key) {
		case VK_F3:
			FormProductList->ButtonAction = TButtonAction::BA_VIEW;
			break;
		case VK_F4:
			FormProductList->ButtonAction = TButtonAction::BA_EDIT;
			break;
		case VK_INSERT:
			FormProductList->ButtonAction = TButtonAction::BA_ADD;
			break;
		case VK_DELETE:
			FormProductList->ButtonAction = TButtonAction::BA_DEL;
			FormProductList->DeleteItem();
			return;
		default:
			return;
	}
	FormProductList->ToolButtonsClickAction(FormProductList->ButtonAction);
}

//---------------------------------------------------------------------------
TProduct* __fastcall TMyListView::GetSelectProduct(void)
{
	return TProduct::VProduct[ipp[ItemIndex]];
}
//---------------------------------------------------------------------------


