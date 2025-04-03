//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "UnitReport.h"
#include "ShopUnits.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillListReport(void)
{
	TListItem  *ListItem;
	UnicodeString uTmp;

	TReport::RestoreOrderShopsName();
	for(unsigned i=0; i < TShopUnits::VShopUnits.size(); i++) {

		ListItem = Items->Add();
		ListItem->Caption = TReport::Reports[i]->NameUnit;
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TReport::Reports[i]->Incoming.StringFormat(), ColumnsData[1].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->Receive.StringFormat(), ColumnsData[2].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->Send.StringFormat(), ColumnsData[3].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->Cost.StringFormat(), ColumnsData[4].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->Sale.StringFormat(), ColumnsData[5].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->Return.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->Discount.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->DebtBuyers.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->DebtProvis.StringFormat(), ColumnsData[9].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->Expanses.StringFormat(), ColumnsData[10].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->Cashbox.StringFormat(), ColumnsData[11].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->Profit.StringFormat(), ColumnsData[12].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->PercentProfit.StringFormat(), ColumnsData[13].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->BalanceProductCost.StringFormat(), ColumnsData[14].Visible);
		AddSubItem(ListItem, TReport::Reports[i]->BalanceProductPrice.StringFormat(), ColumnsData[15].Visible);

		ipp.push_back(i);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillArangedListReport(void)
{
	UnicodeString uTmp;
	TListItem  *ListItem;

	for(int i=0; i<(int)ipp.size(); i++) {
		int ii = ipp[i];
		ListItem = Items->Add();
		ListItem->Caption = TReport::Reports[ii]->NameUnit;
		ListItem->ImageIndex = -1;

		AddSubItem(ListItem, TReport::Reports[ii]->Incoming.StringFormat(), ColumnsData[1].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->Receive.StringFormat(), ColumnsData[2].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->Send.StringFormat(), ColumnsData[3].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->Cost.StringFormat(), ColumnsData[4].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->Sale.StringFormat(), ColumnsData[5].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->Return.StringFormat(), ColumnsData[6].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->Discount.StringFormat(), ColumnsData[7].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->DebtBuyers.StringFormat(), ColumnsData[8].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->DebtProvis.StringFormat(), ColumnsData[9].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->Expanses.StringFormat(), ColumnsData[10].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->Cashbox.StringFormat(), ColumnsData[11].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->Profit.StringFormat(), ColumnsData[12].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->PercentProfit.StringFormat(), ColumnsData[13].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->BalanceProductCost.StringFormat(), ColumnsData[14].Visible);
		AddSubItem(ListItem, TReport::Reports[ii]->BalanceProductPrice.StringFormat(), ColumnsData[15].Visible);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::SortReports(int iColumn)
{
	int iIndexColumnData = GetIndexColumnData(iColumn);
	bArrangeOrder[iIndexColumnData] = !bArrangeOrder[iIndexColumnData];

	bool bSwap;

	for(unsigned i=0; i < ipp.size(); i++) {
		for(unsigned j=i+1; j < ipp.size(); j++) {
			switch(iIndexColumnData) {
				case 0:
					bSwap = TReport::Reports[ipp[i]]->NameUnit < TReport::Reports[ipp[j]]->NameUnit;
					break;
				case 1:
					bSwap = TReport::Reports[ipp[i]]->Incoming < TReport::Reports[ipp[j]]->Incoming;
					break;
				case 2:
					bSwap = TReport::Reports[ipp[i]]->Receive < TReport::Reports[ipp[j]]->Receive;
					break;
				case 3:
					bSwap = TReport::Reports[ipp[i]]->Send < TReport::Reports[ipp[j]]->Send;
					break;
				case 4:
					bSwap = TReport::Reports[ipp[i]]->Cost < TReport::Reports[ipp[j]]->Cost;
					break;
				case 5:
					bSwap = TReport::Reports[ipp[i]]->Sale < TReport::Reports[ipp[j]]->Sale;
					break;
				case 6:
					bSwap = TReport::Reports[ipp[i]]->Return < TReport::Reports[ipp[j]]->Return;
					break;
				case 7:
					bSwap = TReport::Reports[ipp[i]]->Discount < TReport::Reports[ipp[j]]->Discount;
					break;
				case 8:
					bSwap = TReport::Reports[ipp[i]]->DebtBuyers < TReport::Reports[ipp[j]]->DebtBuyers;
					break;
				case 9:
					bSwap = TReport::Reports[ipp[i]]->DebtProvis < TReport::Reports[ipp[j]]->DebtProvis;
					break;
				case 10:
					bSwap = TReport::Reports[ipp[i]]->Expanses < TReport::Reports[ipp[j]]->Discount;
					break;
				case 11:
					bSwap = TReport::Reports[ipp[i]]->Cashbox < TReport::Reports[ipp[j]]->Cashbox;
					break;
				case 12:
					bSwap = TReport::Reports[ipp[i]]->Profit < TReport::Reports[ipp[j]]->Profit;
					break;
				case 13:
					bSwap = TReport::Reports[ipp[i]]->PercentProfit < TReport::Reports[ipp[j]]->PercentProfit;
					break;
				case 14:
					bSwap = TReport::Reports[ipp[i]]->BalanceProductCost < TReport::Reports[ipp[j]]->BalanceProductCost;
					break;
				case 15:
					bSwap = TReport::Reports[ipp[i]]->BalanceProductPrice < TReport::Reports[ipp[j]]->BalanceProductPrice;
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


