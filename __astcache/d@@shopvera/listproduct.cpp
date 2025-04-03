//---------------------------------------------------------------------------
#pragma hdrstop

#include "GroupProduct.h"
#include "UnitGroupList.h"
#include "UnitProductList.h"
#include "Shop.h"
#include "MyListView.h"
#include "ObjectManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListProduct(void)
{
//	ColumnsCreat();

	TListItem  *ListItem;

	unsigned Count = TObjectManager<TProduct>::GetList().size();

	for(unsigned i=0; i < Count; i++) {
		if(FormProductList->FilteredProduct(i)) {
			ListItem = Items->Add();
			ListItem->Caption = TObjectManager<TProduct>::GetList()[i]->GroupProd->Name;
			ListItem->ImageIndex = -1;

			AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[i]->Code, ColumnsData[1].Visible);
			AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[i]->Name, ColumnsData[2].Visible);

			if(TObjectManager<TProduct>::GetList()[i]->WholeUnit) {
				AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[i]->Unit, ColumnsData[3].Visible);
			} else {
				UnicodeString uTmp = L"[" + TObjectManager<TProduct>::GetList()[i]->Unit + L"]";
				AddSubItem(ListItem, uTmp, ColumnsData[3].Visible);
			}
			AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[i]->PurchaseCash.StringFormat(), ColumnsData[4].Visible);
			AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[i]->DollarPrice.StringFormat(), ColumnsData[5].Visible);
			AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[i]->SellingPrice.StringFormat(), ColumnsData[6].Visible);
			AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[i]->WholePrice.StringFormat(), ColumnsData[7].Visible);

			for(unsigned j=0; j < TObjectManager<TShopUnits>::GetList().size(); j++) {
				AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[i]->CountBalance[TShopUnits::upp[j]].StringFormat(),
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
		ListItem->Caption = TObjectManager<TProduct>::GetList()[ii]->GroupProd->Name;
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[ii]->Code, ColumnsData[1].Visible);
		AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[ii]->Name, ColumnsData[2].Visible);

		if(TObjectManager<TProduct>::GetList()[ii]->WholeUnit) {
			AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[ii]->Unit, ColumnsData[3].Visible);
		} else {
			UnicodeString uTmp = L"[" + TObjectManager<TProduct>::GetList()[ii]->Unit + L"]";
			AddSubItem(ListItem, uTmp, ColumnsData[3].Visible);
		}
		AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[ii]->PurchaseCash.StringFormat(), ColumnsData[4].Visible);
		AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[ii]->DollarPrice.StringFormat(), ColumnsData[5].Visible);
		AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[ii]->SellingPrice.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[ii]->WholePrice.StringFormat(), ColumnsData[7].Visible);

		for(unsigned j=0; j < TObjectManager<TShopUnits>::GetList().size(); j++) {
			AddSubItem(ListItem, TObjectManager<TProduct>::GetList()[ii]->CountBalance[TShopUnits::upp[j]].StringFormat(),
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
					bSwap = TObjectManager<TProduct>::GetList()[ipp[i]]->GroupProd->Name < TObjectManager<TProduct>::GetList()[ipp[j]]->GroupProd->Name;
					break;
				case 1:
					bSwap = TObjectManager<TProduct>::GetList()[ipp[i]]->Code < TObjectManager<TProduct>::GetList()[ipp[j]]->Code;
					break;
				case 2:
					bSwap = TObjectManager<TProduct>::GetList()[ipp[i]]->Name < TObjectManager<TProduct>::GetList()[ipp[j]]->Name;
					break;
				case 3:
					bSwap = TObjectManager<TProduct>::GetList()[ipp[i]]->Unit < TObjectManager<TProduct>::GetList()[ipp[j]]->Unit;
					break;
				case 4:
					bSwap = TObjectManager<TProduct>::GetList()[ipp[i]]->PurchaseCash < TObjectManager<TProduct>::GetList()[ipp[j]]->PurchaseCash;
					break;
				case 5:
					bSwap = TObjectManager<TProduct>::GetList()[ipp[i]]->DollarPrice < TObjectManager<TProduct>::GetList()[ipp[j]]->DollarPrice;
					break;
				case 6:
					bSwap = TObjectManager<TProduct>::GetList()[ipp[i]]->SellingPrice < TObjectManager<TProduct>::GetList()[ipp[j]]->SellingPrice;
					break;
				case 7:
					bSwap = TObjectManager<TProduct>::GetList()[ipp[i]]->WholePrice < TObjectManager<TProduct>::GetList()[ipp[j]]->WholePrice;
					break;
				default:
					// Balance in units
					bSwap = TObjectManager<TProduct>::GetList()[ipp[i]]->CountBalance[TShopUnits::upp[iIndexColumnData - 8]] <
							TObjectManager<TProduct>::GetList()[ipp[j]]->CountBalance[TShopUnits::upp[iIndexColumnData - 8]];
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
	return TObjectManager<TProduct>::GetList()[ipp[ItemIndex]];
}
//---------------------------------------------------------------------------


