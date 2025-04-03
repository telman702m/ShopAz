//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitProvisionerList.h"
#include "Shop.h"
#include "UnitProvisionerData.h"
#include "UnitMoveProduct.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wProvisionerExistsMessage[] = {
	L"Данный поставщик присутствует в операции от даты %s!\nУдаление не допустипо!",
	L"Bu təcizatçı %s tarixdəki əməliyyətdə mövcüddür!\nSilmək mümkün deyil!"
};

TColumnsData ColumnsProvisioner[] = {
	{{L"Фамилия",		L"Soyadı"},		174,	taLeftJustify, 	true,	false},
	{{L"Имя",			L"Adı"}, 		170,	taLeftJustify, 	true,	false},
	{{L"Отчество",		L"Atasının"}, 	120, 	taLeftJustify, 	true,	false},
	{{L"Организация",	L"Təşkilat"},	118, 	taLeftJustify, 	true,	false},
	{{L"Адрес",			L"Ünvan"},  	152, 	taLeftJustify, 	true,	false},
	{{L"Телефон1",		L"Telefon1"}, 	93, 	taCenter, 		true,	false},
	{{L"Телефон2",		L"Telefon2"}, 	90, 	taCenter, 		true,	false},
	{{L"Поставки", 		L"Təcizat"},	70, 	taRightJustify, true, 	true},
	{{L"Скидки", 		L"Güzəşt"},		70, 	taRightJustify, true, 	true},
	{{L"Долг", 			L"Borc"},		70, 	taRightJustify, true, 	true}
};
TLabelCaption LabelCaptionProvis[] = {
	{{L"Поиск по имени",		L"Adı ilə axtarış"},		NULL},
	{{L"Поиск по аттрибутам",	L"Attributu ilə axtarış"},	NULL}
};

TFormProvisionerList *FormProvisionerList;

//---------------------------------------------------------------------------
__fastcall TFormProvisionerList::TFormProvisionerList(TComponent* Owner)
	: TFormParent(Owner)
{
	wFormCaptions[0] = L"Список поставщиков";
	wFormCaptions[1] = L"Təcizatçıların siyahısı";

	LocateMyListView.Left = 16;
	LocateMyListView.Top = 93;
	LocateMyListView.Width = 1153;
	LocateMyListView.Height = 500;

	SizeColumnsData = sizeof(ColumnsProvisioner) / sizeof(TColumnsData);
	ColumnsData = ColumnsProvisioner;

	SizeLabelsData = sizeof(LabelCaptionProvis) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionProvis;
}
//---------------------------------------------------------------------------
void __fastcall TFormProvisionerList::FormCreate(TObject *Sender)
{
	MyListView = new TMyListView(FormProvisionerList, FormProvisionerList, ColumnsData, SizeColumnsData, LocateMyListView, TYPE_LIST::LS_PROVIS, true);
	MyListView->Name = L"ProvisionerList";

	LabelsCaption[0].Label = LabelSearchByName;
	LabelsCaption[1].Label = LabelSearchByattribute;

	SetLanguage();
}

//---------------------------------------------------------------------------
void __fastcall TFormProvisionerList::FormResize(TObject *Sender)
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
void __fastcall TFormProvisionerList::ToolButtonsClickAction(TButtonAction bAction)
{
	if((MyListView->ItemIndex == -1) && (bAction != TButtonAction::BA_ADD)) {
		Application->MessageBox(wSelectMessage[iLang], uCaptionWarning[iLang], MB_OK);
		return;
	}

	FormProvisionerData->ShowModal();
}

//---------------------------------------------------------------------------
void __fastcall TFormProvisionerList::DeleteItem(void)
{
	if(MyListView->ItemIndex != -1) {
		// Check Provisioner include in any MoveProduct
		for(unsigned i=0; i < TObjectManager<TMoveProduct>::GetList().size(); i++) {
			if(TObjectManager<TMoveProduct>::GetList()[i]->SourcePerson == TObjectManager<TProvisioner>::GetList()[MyListView->ipp[MyListView->ItemIndex]] ||
			   TObjectManager<TMoveProduct>::GetList()[i]->TargetPerson == TObjectManager<TProvisioner>::GetList()[MyListView->ipp[MyListView->ItemIndex]]) {
					uTmp.sprintf(wProvisionerExistsMessage[iLang], TObjectManager<TMoveProduct>::GetList()[i]->DateTime.FormatString(wDateTimeFormat).w_str());
					Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_OK);
					return;
			   }
		}

		if(Application->MessageBox(wDeleteMessage[iLang], uCaptionWarning[iLang], MB_YESNO) == IDYES) {

			TObjectManager<TProvisioner>::GetList()[MyListView->ipp[MyListView->ItemIndex]]->DeleteObjectFromDb(FormShop->FDQuery1);;

			MyListView->DeleteSelected();
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormProvisionerList::SelectItem(void)
{
	if(MyListView->ItemIndex != -1) {
		SelectedProvisioner = MyListView->GetSelectProvisioner();
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormProvisionerList::EditFindNameChange(TObject *Sender)
{
	MyListView->FillList();
}
//---------------------------------------------------------------------------

