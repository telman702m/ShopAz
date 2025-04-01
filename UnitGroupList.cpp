//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>

#pragma hdrstop

#include "Shop.h"
#include "UnitGroupList.h"
#include "UnitGroupProduct.h"
#include "UnitProduct.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wGroupProductNotemptyMessage[] = {
	L"В данной группе присутствуют продукты!\nУдаление не допустипо!",
	L"Bu grupda mallar mövcüddür!\nSilmək mümkün deyil!"
};

TColumnsData ColumnsGroup[] = {
	{{L"Код",				L"Kod"},			60,		taLeftJustify, true, 	false},
	{{L"Название группы",	L"Grupun adı"},		195, 	taLeftJustify, true, 	false},
	{{L"Описание группы",	L"Grupun təsviri"},	190, 	taLeftJustify, true, 	false}
};
//wchar_t *ColumnsNameGroup[][2] = {
//	{L"Код",				L"Kod"},
//	{L"Название группы",	L"Grupun adı"},
//	{L"Описание группы",	L"Grupun təsviri"}
//};

TFormGroupList *FormGroupList;

//---------------------------------------------------------------------------
__fastcall TFormGroupList::TFormGroupList(TComponent* Owner)
	: TFormParent(Owner)
{
	wFormCaptions[0] = L"Список групп товаров";
	wFormCaptions[1] = L"Mallar grupların siyahısı";

	LocateMyListView.Left = 24;
	LocateMyListView.Top = 52;
	LocateMyListView.Width = 521;
	LocateMyListView.Height = 225;

	SizeColumnsData = sizeof(ColumnsGroup) / sizeof(TColumnsData);
	ColumnsData = ColumnsGroup;
}
//---------------------------------------------------------------------------
void __fastcall TFormGroupList::FormCreate(TObject *Sender)
{
	MyListView = new TMyListView(FormGroupList, FormGroupList, ColumnsData, SizeColumnsData, LocateMyListView, TYPE_LIST::LS_GROUP, false);
	MyListView->Name = L"ListGroupProduct";

	SetLanguage();
}
//---------------------------------------------------------------------------
void __fastcall TFormGroupList::FormResize(TObject *Sender)
{
	if(!bOnceRun) {
		bOnceRun = true;

		MyListView->Width = ClientWidth - 4;
		MyListView->Left = 2;
		MyListView->Height = ClientHeight - MyListView->Top - HeightTaskBar - 4;

		MyListView->ColumnsCreat();
		MyListView->FillList();

		DropVisibleStatus();
		SetPrivileges();
		SetPositionCloseButton();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGroupList::ToolButtonsClickAction(TButtonAction bAction)
{
	if((MyListView->ItemIndex == -1) && (bAction != TButtonAction::BA_ADD)) {
		Application->MessageBox(wSelectMessage[iLang], uCaptionWarning[iLang], MB_OK);
		return;
	}

	FormGroupProduct->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormGroupList::DeleteItem(void)
{
	if(MyListView->ItemIndex != -1) {
		// Check if group empty
		for(unsigned i=0; i < TProduct::VProduct.size(); i++) {
			if(TProduct::VProduct[i]->GroupProd == TGroupProduct::VGroupProduct[MyListView->ipp[MyListView->ItemIndex]]) {
				Application->MessageBox(wGroupProductNotemptyMessage[iLang], uCaptionWarning[iLang], MB_OK);
				return;
			}
		}

		if(Application->MessageBox(wDeleteMessage[iLang], uCaptionWarning[iLang], MB_YESNO) == IDYES) {

			TGroupProduct::VGroupProduct[MyListView->ipp[MyListView->ItemIndex]]->DeleteObjectFromDb(FormShop->FDQuery1);

			MyListView->DeleteSelected();
			MyListView->FillList();
		}
	}
}
//---------------------------------------------------------------------------
/*void __fastcall TFormGroupList::ListView1MouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
	int x = Mouse->CursorPos.x - ListView1->Left;
	int y = Mouse->CursorPos.y - ListView1->Top;

	int z = x + y;
//	ListView1->Columns->Items[1]->Width;

	TListItem *pListItem = ListView1->GetItemAt(X, Y);
	if(pListItem) {
		ListView1->Hint = pListItem->SubItems->Strings[0];
	}

//	ShowMessage(pListItem->SubItems[1].Text);
//	ShowMessage(pListItem->Caption);
}
//---------------------------------------------------------------------------

void __fastcall TFormGroupList::ListView1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	TListItem *pListItem = ListView1->GetItemAt(X, Y);
	if(pListItem) {
		int i;
		int sum1 = ListView1->Columns->Items[0]->Width;
		int sum2 = sum1;
		for(i=1; i < ListView1->Columns->Count; i++) {
			sum2 += ListView1->Columns->Items[i]->Width;
			if(X > sum1 && X < sum2) {
				ShowMessage(pListItem->SubItems->Strings[i-1]);
				break;
			}
		}
//		ListView1->Hint = pListItem->SubItems->Strings[i];
	}

}*/
//---------------------------------------------------------------------------

