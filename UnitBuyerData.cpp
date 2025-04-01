//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Shop.h"
#include "UnitMoveProduct.h"
#include "UnitBuyerList.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wButSaveCaption[] = {L"Сохранить", L"Saxlamaq"};
const wchar_t *wButInsertCaption[] = {L"Вставить", L"Daxil"};
const wchar_t *wButCancelCaption[] = {L"Отмена", L"Cancel"};
const wchar_t *wButCloseCaption[] = {L"Закрыть", L"Bağlamaq"};

TLabelCaption LabelCaptionsBuyerData[] = {
	{{L"Фамилия",		L"Soyadı"},		NULL},
	{{L"Имя",			L"Adı"},		NULL},
	{{L"Отчество",		L"Atasının"},	NULL},
	{{L"Организация",	L"Təşkilat"},	NULL},
	{{L"Адрес",			L"Ünvan"},		NULL},
	{{L"Телефон1",		L"Telefon1"},	NULL},
	{{L"Телефон2",		L"Telefon2"},	NULL},
	{{L"Описание",		L"Təsviri"},	NULL}
};
TCheckBoxCaption CheckBoxCaptionBuyerData[] = {
	{{L"Активный", L"Aktiv"}, NULL}
};

TFormBuyerData *FormBuyerData;

//---------------------------------------------------------------------------
__fastcall TFormBuyerData::TFormBuyerData(TComponent* Owner)
	: TFormEsc(Owner)
{
	wFormCaptions[0] = L"Данные о покупателе";
	wFormCaptions[1] = L"Alıcı haqqında məlumat";

	SizeLabelsData = sizeof(LabelCaptionsBuyerData) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionsBuyerData;

	SizeCheckBoxData = sizeof(CheckBoxCaptionBuyerData) / sizeof(TLabelCaption);
	CheckBoxCaption = CheckBoxCaptionBuyerData;
}
//---------------------------------------------------------------------------
void __fastcall TFormBuyerData::FormCreate(TObject *Sender)
{
	LabelsCaption[0].Label = LabelSurname;
	LabelsCaption[1].Label = LabelName;
	LabelsCaption[2].Label = LabelPatron;
	LabelsCaption[3].Label = LabelOrg;
	LabelsCaption[4].Label = LabelAddress;
	LabelsCaption[5].Label = LabelPhone1;
	LabelsCaption[6].Label = LabelPhone2;
	LabelsCaption[7].Label = LabelDescript;

	CheckBoxCaption[0].CheckBox = CheckBoxEnable;

	SetLanguage();

	TmpBuyer = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormBuyerData::FormShow(TObject *Sender)
{
	switch(FormBuyerList->ButtonAction) {
		case TButtonAction::BA_VIEW:
			TmpBuyer = TBuyer::VBuyers[FormBuyerList->MyListView->ipp[FormBuyerList->MyListView->ItemIndex]];
			LoadFromObjectToForm(TmpBuyer);
			ComponentsDisable();
			ButtonSave->Caption = wButSaveCaption[iLang];
			ButtonSave->Enabled = false;
			ButtonSave->OnClick = NULL;
			ButtonClose->Caption = wButCloseCaption[iLang];
			break;
		case TButtonAction::BA_EDIT:
			TmpBuyer = TBuyer::VBuyers[FormBuyerList->MyListView->ipp[FormBuyerList->MyListView->ItemIndex]];
			LoadFromObjectToForm(TmpBuyer);
			ComponentsEnable();
			ButtonSave->Caption = wButSaveCaption[iLang];
			ButtonSave->Enabled = true;
			ButtonSave->OnClick = ButtonSaveClick;
			ButtonClose->Caption = wButCancelCaption[iLang];
			break;
		case TButtonAction::BA_ADD:
			ComponentsEnable();
			ButtonSave->Caption = wButInsertCaption[iLang];
			ButtonSave->Enabled = true;
			ButtonSave->OnClick = ButtonInsertClick;
			ButtonClose->Caption = wButCancelCaption[iLang];
			ClearFields();
			TmpBuyer = new TBuyer();
			TmpBuyer->Clear();
			break;
		default:
            break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormBuyerData::ButtonCloseClick(TObject *Sender)
{
	if(FormBuyerList->ButtonAction == TButtonAction::BA_ADD) {
		delete TmpBuyer;
	}
	TmpBuyer = NULL;

	Close();
}

//---------------------------------------------------------------------------
void __fastcall TFormBuyerData::ButtonSaveClick(TObject *Sender)
{
	SaveAtFormToObject(TmpBuyer);
	TmpBuyer->SaveAtObjectToDb(FormShop->FDQuery1);

	FormBuyerList->MyListView->FillList();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormBuyerData::ButtonInsertClick(TObject *Sender)
{
	SaveAtFormToObject(TmpBuyer);
	TmpBuyer->InsertAtObjectToDb(FormShop->FDQuery1);

	FormBuyerList->MyListView->FillList();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormBuyerData::ClearFields(void)
{
	EditSurname->Text = L"";
	EditName->Text = L"";
	EditPatronymic->Text = L"";
	EditOrganization->Text = L"";
	EditAddress->Text = L"";
	EditPhone1->Text = L"";
	EditPhone2->Text = L"";
	MemoDescription->Text = L"";
	CheckBoxEnable->Checked = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormBuyerData::ComponentsEnable(void)
{
	EditSurname->ReadOnly = false;
	EditName->ReadOnly = false;
	EditPatronymic->ReadOnly = false;
	EditOrganization->ReadOnly = false;
	EditAddress->ReadOnly = false;
	EditPhone1->ReadOnly = false;
	EditPhone2->ReadOnly = false;

	EditSurname->Enabled = true;
	EditName->Enabled = true;
	EditPatronymic->Enabled = true;
	EditOrganization->Enabled = true;
	EditAddress->Enabled = true;
	EditPhone1->Enabled = true;
	EditPhone2->Enabled = true;

	MemoDescription->Enabled = true;
	CheckBoxEnable->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormBuyerData::ComponentsDisable(void)
{
	EditSurname->ReadOnly = true;
	EditName->ReadOnly = true;
	EditPatronymic->ReadOnly = true;
	EditOrganization->ReadOnly = true;
	EditAddress->ReadOnly = true;
	EditPhone1->ReadOnly = true;
	EditPhone2->ReadOnly = true;

	EditSurname->Enabled = false;
	EditName->Enabled = false;
	EditPatronymic->Enabled = false;
	EditOrganization->Enabled = false;
	EditAddress->Enabled = false;
	EditPhone1->Enabled = false;
	EditPhone2->Enabled = false;

	MemoDescription->Enabled = false;
	CheckBoxEnable->Enabled = false;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void __fastcall TFormBuyerData::LoadFromObjectToForm(TBuyer *CurBuyer)
{
	EditSurname->Text = CurBuyer->Surname;
	EditName->Text = CurBuyer->Name;
	EditPatronymic->Text = CurBuyer->Patronymic;
	EditOrganization->Text = CurBuyer->Organization;
	EditAddress->Text = CurBuyer->Address;
	EditPhone1->Text = CurBuyer->Phone1;
	EditPhone2->Text = CurBuyer->Phone2;
	MemoDescription->Text = CurBuyer->Description;
	CheckBoxEnable->Checked = CurBuyer->Enabled;
}

//---------------------------------------------------------------------------
void __fastcall TFormBuyerData::SaveAtFormToObject(TBuyer *CurBuyer)
{
	CurBuyer->Surname = EditSurname->Text;
	CurBuyer->Name = EditName->Text;
	CurBuyer->Patronymic = EditPatronymic->Text;
	CurBuyer->Organization = EditOrganization->Text;
	CurBuyer->Address = EditAddress->Text;
	CurBuyer->Phone1 = EditPhone1->Text;
	CurBuyer->Phone2 = EditPhone2->Text;
	CurBuyer->Description = MemoDescription->Text;
    CurBuyer->SetSumName();
	CurBuyer->Enabled = CheckBoxEnable->Checked;
}

//---------------------------------------------------------------------------

