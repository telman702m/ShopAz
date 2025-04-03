//---------------------------------------------------------------------------
#ifndef MyListViewH
#define MyListViewH
//---------------------------------------------------------------------------

#include <ComCtrls.hpp>
#include <vector>

#include "Declaration.h"

//const int COUNT_FUNC = 5;
//---------------------------------------------------------------------------
//                MyListView
//---------------------------------------------------------------------------
class TMyListView : public TListView
{
public:
	static UnicodeString Arrows[3];
	static UnicodeString uTypeOperation[3];

	int iCountColumn;
	TColumnsData *ColumnsData;

private:
	TLocate LocateList;
	int ListType;
	TImageList *ImgList;

public:
	bool *bArrangeOrder;
	vector <int> ipp;

	bool bFoot;
	TEdit **EditsFoot;

public:
	__fastcall TMyListView(Classes::TComponent*, TWinControl *_Parent, TColumnsData[], int, TLocate Locate, int Type, bool _bFoot);
	__fastcall ~TMyListView();

	void __fastcall SetVisualParameters(void);
	void __fastcall FuncsAssign(void);
	void __fastcall ColumnsCreat(void);
	void __fastcall ReloadColumns(TColumnsData _ColumnsData[]);
	void __fastcall AddSubItem(TListItem* ListItem, UnicodeString uStr, bool bEnable);
	int __fastcall GetIndexColumnData(int ClickedColumn);

	void __fastcall (__closure*FuncsFillList)(void);
	void __fastcall FillListGroupProduct(void);
	void __fastcall FillListProduct(void);
	void __fastcall FillListMoveProduct(void);
	void __fastcall FillListAtom(void);
	void __fastcall FillListBuyer(void);
	void __fastcall FillListShopUnit(void);
	void __fastcall FillListProvisioner(void);
	void __fastcall FillListReport(void);

	void __fastcall (__closure*FuncsFillArangeList)(void);
	void __fastcall FillArangeListGroup(void);
	void __fastcall FillArangeListProduct(void);
	void __fastcall FillArangeListMoveProduct(void);
	void __fastcall FillArangedListBuyer(void);
	void __fastcall FillArangedListShopUnit(void);
	void __fastcall FillArangedListProvisioner(void);
	void __fastcall FillArangedListReport(void);

	void __fastcall (__closure*FuncsColumnClick)(int);
	void __fastcall SortGroups(int iColumn);
	void __fastcall SortProducts(int iColumn);
	void __fastcall SortMoveProduct(int iColumn);
	void __fastcall SortBuyers(int iColumn);
	void __fastcall SortShopUnit(int iColumn);
	void __fastcall SortProvisioners(int iColumn);
	void __fastcall SortReports(int iColumn);

	void __fastcall (__closure*FuncsDoubleClick)(TObject *Sender);
	void __fastcall ProductsDblClick(TObject *Sender);
	void __fastcall BuyersDblClick(TObject *Sender);
	void __fastcall ShopUnitDblClick(TObject *Sender);
	void __fastcall ProvisionersDblClick(TObject *Sender);

	void __fastcall (__closure*FuncsClick)(int);
	void __fastcall MoveProductClick(int iIndex);

	void __fastcall (__closure*FuncsKeyDown)(TObject *Sender, WORD &Key, int iIndex);
	void __fastcall GroupsKeyDown(TObject *Sender, WORD &Key, int iIndex);
	void __fastcall ProductsKeyDown(TObject *Sender, WORD &Key, int iIndex);
	void __fastcall BuyersKeyDown(TObject *Sender, WORD &Key, int iIndex);
	void __fastcall ShopUnitKeyDown(TObject *Sender, WORD &Key, int iIndex);
	void __fastcall ProvisionersKeyDown(TObject *Sender, WORD &Key, int iIndex);

	void __fastcall (__closure*FuncsOnChange)(TObject *Sender);
	void __fastcall AtomChangeList(TObject *Sender);

	void __fastcall (__closure*FuncsOnMouseDown)(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
//	void __fastcall ProductOnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

	void __fastcall ListKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

__published:	// IDE-managed Components
	void __fastcall FillList(void);
	void __fastcall FillArangedList(void);
	void __fastcall ColumnClick(TObject *Sender, TListColumn *Column);
	void __fastcall DoublClick(TObject *Sender);
	void __fastcall ListClick(TObject *Sender);
	void __fastcall ListKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ListOnChange(TObject *Sender, TListItem *Item, TItemChange Change);
	void __fastcall ListOnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall ListViewDataCustomDrawItem(TCustomListView *Sender, TListItem *Item, TCustomDrawState State, bool &DefaultDraw);


	TProduct* __fastcall GetSelectProduct(void);
	TMoveProduct* __fastcall GetSelectMoveProduct(void);
	TBuyer* __fastcall GetSelectBuyer(void);
	TShopUnits* __fastcall GetSelectShopUnit(void);
	TProvisioner* __fastcall GetSelectProvisioner(void);
	void __fastcall FillAtomComponents(void);

	int __fastcall GetItemIndexByColumnString(UnicodeString uName, int Column);

	void __fastcall MySwapIpp(int i, int j);
};

#endif
