//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Shop.h"
#include "UnitBuyerList.h"
#include "UnitBuyerData.h"
#include "UnitMoveProduct.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wBuyerExistsMessage[] = {
	L"Данный покупатель присутствует в операции от даты %s!\nУдаление не допустипо!",
	L"Bu müştəri %s tarixdəki əməliyyətdə mövcüddür!\nSilmək mümkün deyil!"
};

TColumnsData ColumnsBuyers[] = {
	{{L"Фамилия",		L"Soyadı"},		174,	taLeftJustify, 	true, 	false},
	{{L"Имя",			L"Adı"},		170,	taLeftJustify, 	true, 	false},
	{{L"Отчество",		L"Atasının"},	120, 	taLeftJustify, 	true, 	false},
	{{L"Организация",	L"Təşkilat"},	118, 	taLeftJustify, 	true, 	false},
	{{L"Адрес",			L"Ünvan"},		152, 	taLeftJustify, 	true, 	false},
	{{L"Телефон1",		L"Telefon1"},	93, 	taCenter, 		true, 	false},
	{{L"Телефон2",		L"Telefon2"},	90, 	taCenter, 		true, 	false},
	{{L"Покупки", 		L"Alış"},		75, 	taRightJustify,	true, 	true},
	{{L"Возвраты", 		L"Qayıdış"},	70, 	taRightJustify, true, 	true},
	{{L"Скидки", 		L"Güzəşt"},		70, 	taRightJustify, true, 	true},
	{{L"Долг", 			L"Borc"},		70, 	taRightJustify, true, 	true}
};
TLabelCaption LabelCaptionBuyers[] = {
	{{L"Поиск по имени",		L"Adı ilə axtarış"},		NULL},
	{{L"Поиск по аттрибутам",	L"Attributu ilə axtarış"},	NULL}
};

TFormBuyerList *FormBuyerList;

//---------------------------------------------------------------------------
__fastcall TFormBuyerList::TFormBuyerList(TComponent* Owner)
	: TFormParent(Owner)
{
	wFormCaptions[0] = L"Список покупателей";
	wFormCaptions[1] = L"Alıcılar siyahısı";

	LocateMyListView.Left = 16;
	LocateMyListView.Top = 93;
	LocateMyListView.Width = 1153;
	LocateMyListView.Height = 500;

	SizeColumnsData = sizeof(ColumnsBuyers) / sizeof(TColumnsData);
	ColumnsData = ColumnsBuyers;

	SizeLabelsData = sizeof(LabelCaptionBuyers) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionBuyers;
}
//---------------------------------------------------------------------------
void __fastcall TFormBuyerList::FormCreate(TObject *Sender)
{
	MyListView = new TMyListView(FormBuyerList, FormBuyerList, ColumnsData, SizeColumnsData, LocateMyListView, TYPE_LIST::LS_BUYER, true);
	MyListView->Name = L"BuyerList";

	LabelsCaption[0].Label = LabelSearchByName;
	LabelsCaption[1].Label = LabelSearchByattribute;

	SetLanguage();
}
//---------------------------------------------------------------------------
void __fastcall TFormBuyerList::FormResize(TObject *Sender)
{
	if(!bOnceRun) {
		bOnceRun = true;

		MyListView->Width = ClientWidth - 4;
		MyListView->Left = 2;
		MyListView->Height = ClientHeight - MyListView->Top - HeightTaskBar - 30;

		MyListView->ColumnsCreat();
		MyListView->FillList();

		DropVisibleStatus();
		SetPrivileges();
		SetPositionCloseButton();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormBuyerList::ToolButtonsClickAction(TButtonAction bAction)
{
	if((MyListView->ItemIndex == -1) && (bAction != TButtonAction::BA_ADD)) {
		Application->MessageBox(wSelectMessage[iLang], uCaptionWarning[iLang], MB_OK);
		return;
	}

	FormBuyerData->ShowModal();
}

//---------------------------------------------------------------------------
void __fastcall TFormBuyerList::DeleteItem(void)
{
	if(MyListView->ItemIndex != -1) {
		// Check Buyer include in any MoveProduct
		for(unsigned i=0; i < TMoveProduct::VMoveProduct.size(); i++) {
			if(TMoveProduct::VMoveProduct[i]->SourcePerson == TBuyer::VBuyers[MyListView->ipp[MyListView->ItemIndex]] ||
			   TMoveProduct::VMoveProduct[i]->TargetPerson == TBuyer::VBuyers[MyListView->ipp[MyListView->ItemIndex]]) {
					uTmp.sprintf(wBuyerExistsMessage[iLang], TMoveProduct::VMoveProduct[i]->DateTime.FormatString(wDateTimeFormat).w_str());
					Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_OK);
					return;
			   }
		}

		if(Application->MessageBox(wDeleteMessage[iLang], uCaptionWarning[iLang], MB_YESNO) == IDYES) {

			TBuyer::VBuyers[MyListView->ipp[MyListView->ItemIndex]]->DeleteObjectFromDb(FormShop->FDQuery1);;

			MyListView->DeleteSelected();
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormBuyerList::SelectItem(void)
{
	if(MyListView->ItemIndex != -1) {
		SelectedBuyer = MyListView->GetSelectBuyer();
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormBuyerList::EditFindNameChange(TObject *Sender)
{
	MyListView->FillList();
}
//---------------------------------------------------------------------------

