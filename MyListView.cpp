//---------------------------------------------------------------------------
#pragma hdrstop

#include "MyListView.h"
#include "Shop.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

UnicodeString TMyListView::Arrows[3] = {L"", L"↓", L"↑"};

//---------------------------------------------------------------------------
//          Constructor
//---------------------------------------------------------------------------
__fastcall TMyListView::TMyListView(Classes::TComponent *AOwner, TWinControl *_Parent,
					   TColumnsData _ColumnsData[], int _CountColumn,
					   TLocate Locate, int Type, bool _bFoot)
	: TListView(AOwner)
{
	Parent = _Parent;

	EditsFoot = NULL;

	ListType = Type;
	iCountColumn = _CountColumn;
	ColumnsData = _ColumnsData;
	LocateList = Locate;
	bFoot = _bFoot;

	if(bFoot) {
		EditsFoot = new TEdit*[iCountColumn];
		UnicodeString uTmp;

		for(int i=0; i < iCountColumn; i++) {
			EditsFoot[i] = new TEdit(AOwner);

			EditsFoot[i]->Name = uTmp.sprintf(L"Edit_%s_%02d", AOwner->Name.w_str(), i);
			EditsFoot[i]->Parent = this->Parent;
			EditsFoot[i]->Color = TColor(RGB(247, 247, 255));
			EditsFoot[i]->ReadOnly = true;
			EditsFoot[i]->Font->Color = clBlack;
			EditsFoot[i]->Font->Style = TFontStyles() << fsBold;
            EditsFoot[i]->Alignment = taCenter;
		}

	}

	if(Type == TYPE_LIST::LS_MOVEPROD) {  // Load icons for list
		ImgList = FormShop->ImageList2;
	}

	FuncsAssign();
	SetVisualParameters();
	ColumnsCreat();
}
//---------------------------------------------------------------------------
//          Destructor
//---------------------------------------------------------------------------
__fastcall TMyListView::~TMyListView(void)
{
	delete bArrangeOrder;
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::SetVisualParameters(void)
{
	Left = LocateList.Left;
	Top = LocateList.Top;
	Width = LocateList.Width;
	if(bFoot) {
		Height = LocateList.Height - 25;
	} else {
		Height = LocateList.Height;
	}

	Color = TColor(0x00fafafa);
	GridLines = true;
	ReadOnly = true;
	RowSelect = true;
	TabOrder = 3;
	ViewStyle = vsReport;
	Visible = true;
	BorderWidth = 1;

	Font->Style = TFontStyles();
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = TColor(0x00500000);
	Font->Height = -13;
	Font->Name = L"Arial";
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::FuncsAssign(void)
{
	switch(ListType) {
		case LS_GROUP:
			FuncsFillList = FillListGroupProduct;
			FuncsFillArangeList = FillArangeListGroup;
			FuncsColumnClick = SortGroups;
			FuncsDoubleClick = NULL;
			FuncsClick = NULL;
			FuncsKeyDown = GroupsKeyDown;
			FuncsOnChange = NULL;
//			FuncsOnMouseDown = NULL;
			break;
		case LS_PROD:
			FuncsFillList = FillListProduct;
			FuncsFillArangeList = FillArangeListProduct;
			FuncsColumnClick = SortProducts;
			FuncsDoubleClick = ProductsDblClick;
			FuncsClick = NULL;
			FuncsKeyDown = ProductsKeyDown;
			FuncsOnChange = NULL;
//			FuncsOnMouseDown = ProductOnMouseDown;
			break;
		case LS_BUYER:
			FuncsFillList = FillListBuyer;
			FuncsFillArangeList = FillArangedListBuyer;
			FuncsColumnClick = SortBuyers;
			FuncsDoubleClick = BuyersDblClick;
			FuncsClick = NULL;
			FuncsKeyDown = BuyersKeyDown;
			FuncsOnChange = NULL;
//			FuncsOnMouseDown = NULL;
			break;
		case LS_MOVEPROD:
			FuncsFillList = FillListMoveProduct;
			FuncsFillArangeList = FillArangeListMoveProduct;
			FuncsColumnClick = SortMoveProduct;
			FuncsDoubleClick = NULL;
			FuncsClick = MoveProductClick;
			FuncsKeyDown = NULL;
			FuncsOnChange = NULL;
//			FuncsOnMouseDown = NULL;
			break;
		case LS_ATOM:
			FuncsFillList = FillListAtom;
			FuncsFillArangeList = NULL;
			FuncsColumnClick = NULL;
			FuncsDoubleClick = NULL;
			FuncsClick = NULL;
			FuncsKeyDown = NULL;
			FuncsOnChange = AtomChangeList;
//			FuncsOnMouseDown = NULL;
			break;
		case LS_SHOPUNIT:
			FuncsFillList = FillListShopUnit;
			FuncsFillArangeList = FillArangedListShopUnit;
			FuncsColumnClick = SortShopUnit;
			FuncsDoubleClick = ShopUnitDblClick;
			FuncsClick = NULL;
			FuncsKeyDown = ShopUnitKeyDown;
			FuncsOnChange = NULL;
//			FuncsOnMouseDown = NULL;
			break;
		case LS_PROVIS:
			FuncsFillList = FillListProvisioner;
			FuncsFillArangeList = FillArangedListProvisioner;
			FuncsColumnClick = SortProvisioners;
			FuncsDoubleClick = ProvisionersDblClick;
			FuncsClick = NULL;
			FuncsKeyDown = ProvisionersKeyDown;
			FuncsOnChange = NULL;
//			FuncsOnMouseDown = NULL;
			break;
		case LS_REPORTS:
			FuncsFillList = FillListReport;
			FuncsFillArangeList = FillArangedListReport;
			FuncsColumnClick = SortReports;
			FuncsDoubleClick = NULL;
			FuncsClick = NULL;
			FuncsKeyDown = NULL;
			FuncsOnChange = NULL;
//			FuncsOnMouseDown = NULL;
			break;
	}

	OnColumnClick = ColumnClick;
	OnDblClick = DoublClick;
	OnClick = ListClick;
	OnKeyDown = ListKeyDown;
	OnKeyUp = ListKeyUp;
	OnChange = ListOnChange;
	OnMouseDown = ListOnMouseDown;
    OnCustomDrawItem = ListViewDataCustomDrawItem;

	ipp.clear();
	bArrangeOrder = NULL;
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::ReloadColumns(TColumnsData _ColumnsData[])
{
	ColumnsData = _ColumnsData;
	ColumnsCreat();
}
//---------------------------------------------------------------------------
void __fastcall TMyListView::ColumnsCreat(void)
{
	if(bArrangeOrder == NULL) {
		bArrangeOrder = new bool[iCountColumn];
	}
	Columns->Clear();

	int SumLen = 0;
	for(int i=0; i < iCountColumn; i++) {
		if(ColumnsData[i].Visible) {
			SumLen += ColumnsData[i].Width;
		}
	}

	int CurLeft = Left;
	TListColumn  *NewColumn;
	for(int i=0; i < iCountColumn; i++) {
		if(ColumnsData[i].Visible) {
			NewColumn = Columns->Add();
			NewColumn->Caption = Arrows[0] + ColumnsData[i].Caption[iLang];
			NewColumn->Width = (ColumnsData[i].Width * (Width-22)) / SumLen;
			NewColumn->Alignment = ColumnsData[i].TMAlign;

			if(bFoot) {
//				EditsFoot[i]->Text = NewColumn->Caption;
				EditsFoot[i]->Text = L"";
				EditsFoot[i]->Visible = true;
				EditsFoot[i]->Height = 25;
				EditsFoot[i]->Top = Top + Height;
				EditsFoot[i]->Left = CurLeft;
				EditsFoot[i]->Width = NewColumn->Width + 1;
				CurLeft += EditsFoot[i]->Width;
			}
		} else {
			if(bFoot) {
				EditsFoot[i]->Visible = false;
			}
		}
		bArrangeOrder[i] = false;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::AddSubItem(TListItem* ListItem, UnicodeString uStr, bool bEnable)
{
	if(bEnable) {
        ListItem->SubItems->Add(uStr);
    }
}
//---------------------------------------------------------------------------
int __fastcall TMyListView::GetIndexColumnData(int ClickedColumn)
{
	int i = 0;
	int iSuccess = -1;
	int iRetIndex = -1;

	while(iSuccess < ClickedColumn) {
		if(ColumnsData[i].Visible) {
			iSuccess++;
		}
		iRetIndex++;
		i++;
	}
	return iRetIndex;
}
//---------------------------------------------------------------------------
int __fastcall TMyListView::GetItemIndexByColumnString(UnicodeString uName, int Column)
{
	for(int i=0; i < Items->Count; i++) {
		if(Column == 0) {
			if(Items->Item[i]->Caption == uName) {
				return i;
			}
		} else {
			if(Items->Item[i]->SubItems->Strings[Column - 1] == uName) {
				return i;
			}
		}
	}
	return -1;
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillList(void)
{
	if(FuncsFillList == NULL) {
		return;
	}

	Clear();
	ipp.clear();

	ColumnsCreat();
	FuncsFillList();

	if(bFoot) {
		int kShow = -1;
		for(int i=0; i < iCountColumn; i++) {
			if(ColumnsData[i].Visible) {
				kShow++;
				if(ColumnsData[i].bSum) {
					TPrice PriceTmp = 0;
					for(int j=0; j < Items->Count; j++) {
						PriceTmp += TPrice(Items->Item[j]->SubItems->Strings[kShow - 1]);
					}
					EditsFoot[i]->Text = PriceTmp.StringFormat();
				}
			}
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::FillArangedList(void)
{
	if(FuncsFillArangeList == NULL) {
		return;
	}

	Clear();
	FuncsFillArangeList();
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::ColumnClick(TObject *Sender, TListColumn *Column)
{
	if(FuncsColumnClick == NULL) {
		return;
	}

	FuncsColumnClick(Column->Index);

	int iColumn = Column->Index;
	for(int i=0; i < Columns->Count; i++) {
		int IndexColumnData = GetIndexColumnData(i);
		if(IndexColumnData == -1) {
			return;
        } else if(i == iColumn) {
			this->Column[i]->Caption = Arrows[bArrangeOrder[IndexColumnData]+1] + ColumnsData[IndexColumnData].Caption[iLang];
		} else {
			this->Column[i]->Caption = Arrows[0] + ColumnsData[IndexColumnData].Caption[iLang];
		}
	}
	FillArangedList();
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::DoublClick(TObject *Sender)
{
	if(FuncsDoubleClick == NULL) {
		return;
	}

   	FuncsDoubleClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::ListClick(TObject *Sender)
{
	if((FuncsClick != NULL) && (ItemIndex != -1)) {
		FuncsClick(ItemIndex);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::ListKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if((FuncsKeyDown != NULL) && (ItemIndex != -1 || Key == VK_INSERT)) {
		FuncsKeyDown(Sender, Key, ItemIndex);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::ListOnChange(TObject *Sender, TListItem *Item, TItemChange Change)
{
	if(FuncsOnChange != NULL) {
		FuncsOnChange(Sender);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMyListView::ListKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	ListClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMyListView::ListOnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(FuncsOnMouseDown != NULL) {
		FuncsOnMouseDown(Sender, Button, Shift, X, Y);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMyListView::MySwapIpp(int i, int j)
{
	int c = ipp[i];
	ipp[i] = ipp[j];
	ipp[j] = c;
}
//---------------------------------------------------------------------------
void __fastcall TMyListView::ListViewDataCustomDrawItem(TCustomListView *Sender,
		  TListItem *Item, TCustomDrawState State, bool &DefaultDraw)
{
	Sender->Canvas->Font->Color = TColor(int(Item->Data));
}
//---------------------------------------------------------------------------

