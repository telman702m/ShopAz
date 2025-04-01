//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitShopUnitList.h"
#include "UnitShopUnitData.h"
#include "Shop.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wIllegalOperation[] = {L"Недопустимая операция!", L"Icazəsiz əməliyyat!"};

TColumnsData ColumnsShopUnits[] = {
	{{L"Тип объекта",	L"Obyektin növü"},	110,	taLeftJustify, 	true, 	false},
	{{L"Название",		L"Adı"},  			150,	taLeftJustify, 	true, 	false},
	{{L"Адрес",			L"Ünvan"},  		180, 	taLeftJustify, 	true, 	false},
	{{L"Телефон1",		L"Telefon1"}, 		130, 	taCenter, 		true, 	false},
	{{L"Телефон2",		L"Telefon2"}, 		130, 	taCenter, 		true, 	false},
	{{L"Описание", 		L"Təsviri"}, 		180, 	taLeftJustify,  true, 	false},
	{{L"Приемки", 		L"İdxal"},			70, 	taRightJustify, false, 	false},
	{{L"Передачи", 		L"İxrac"},			70, 	taRightJustify, false, 	false},
	{{L"Продажи", 		L"Satış"},			70, 	taRightJustify, false, 	false},
	{{L"Возвраты", 		L"Qayıdış"},		70, 	taRightJustify, false, 	false},
	{{L"Скидки", 		L"Güzəşt"},			70, 	taRightJustify, false, 	false},
	{{L"Долг", 			L"Borc"},			70, 	taRightJustify, false, 	false}
};

TFormShopUnitsList *FormShopUnitsList;

//---------------------------------------------------------------------------
__fastcall TFormShopUnitsList::TFormShopUnitsList(TComponent* Owner)
	: TFormParent(Owner)
{
	wFormCaptions[0] = L"Список объектов сети магазинов";
	wFormCaptions[1] = L"Mağazalar şəbəkəsinin obyektlərin siyahısı";

	LocateMyListView.Left = 2;
	LocateMyListView.Top = 40;
	LocateMyListView.Width = 700;
	LocateMyListView.Height = 420;

	SizeColumnsData = sizeof(ColumnsShopUnits) / sizeof(TColumnsData);
	ColumnsData = ColumnsShopUnits;
}
//---------------------------------------------------------------------------
void __fastcall TFormShopUnitsList::FormCreate(TObject *Sender)
{
	MyListView = new TMyListView(FormShopUnitsList, FormShopUnitsList, ColumnsData, SizeColumnsData, LocateMyListView, TYPE_LIST::LS_SHOPUNIT, false);
	MyListView->Name = L"ShopUnitList";

	SetLanguage();
}
//---------------------------------------------------------------------------
void __fastcall TFormShopUnitsList::FormResize(TObject *Sender)
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
void __fastcall TFormShopUnitsList::ToolButtonsClickAction(TButtonAction bAction)
{
	if(bAction == TButtonAction::BA_ADD || bAction == TButtonAction::BA_DEL) {
		Application->MessageBox(wIllegalOperation[iLang], uCaptionWarning[iLang], MB_OK);
		return;
	}

	if((MyListView->ItemIndex == -1) && (bAction != TButtonAction::BA_ADD)) {
		Application->MessageBox(wSelectMessage[iLang], uCaptionWarning[iLang], MB_OK);
		return;
	}

	FormShopUnit->ShowModal();
}

//---------------------------------------------------------------------------
void __fastcall TFormShopUnitsList::DeleteItem(void)
{
	if(MyListView->ItemIndex != -1) {
		Application->MessageBox(wIllegalOperation[iLang], uCaptionWarning[iLang], MB_OK);
		return;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormShopUnitsList::SelectItem(void)
{
	if(MyListView->ItemIndex != -1) {
		SelectedShopUnit = MyListView->GetSelectShopUnit();
		Close();
	}
}
//---------------------------------------------------------------------------
/*void __fastcall TFormShopUnits::EditFindNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN) {
		MyListView->FillList();
	}
} */
//---------------------------------------------------------------------------

