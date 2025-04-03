//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitProvisionerData.h"
#include "UnitProvisionerList.h"
#include "Shop.h"
#include "SelectProduct.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TLabelCaption LabelCaptionsProvisData[] = {
	{{L"Фамилия",		L"Soyadı"},		NULL},
	{{L"Имя",			L"Adı"},		NULL},
	{{L"Отчество",		L"Atasının"},	NULL},
	{{L"Организация",	L"Təşkilat"},	NULL},
	{{L"Адрес",			L"Ünvan"},		NULL},
	{{L"Телефон1",		L"Telefon1"},	NULL},
	{{L"Телефон2",		L"Telefon2"},	NULL},
	{{L"Описание",		L"Təsvir"},		NULL}
};
TCheckBoxCaption CheckBoxCaptionProvisData[] = {
	{{L"Активный", L"Aktiv"}, NULL}
};

TFormProvisionerData *FormProvisionerData;

//---------------------------------------------------------------------------
__fastcall TFormProvisionerData::TFormProvisionerData(TComponent* Owner)
	: TFormEsc(Owner)
{
	SizeLabelsData = sizeof(LabelCaptionsProvisData) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionsProvisData;

	SizeCheckBoxData = sizeof(CheckBoxCaptionProvisData) / sizeof(TCheckBoxCaption);
	CheckBoxCaption = CheckBoxCaptionProvisData;
}
//---------------------------------------------------------------------------
void __fastcall TFormProvisionerData::FormCreate(TObject *Sender)
{
	wFormCaptions[0] = L"Данные о поставщике";
	wFormCaptions[1] = L"Təcizatçı haqqında məlumat";

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

//	TmpProvisioner = new TProvisioner();
	TmpProvisioner = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormProvisionerData::FormShow(TObject *Sender)
{
	switch(FormProvisionerList->ButtonAction) {
		case TButtonAction::BA_VIEW:
			TmpProvisioner = TObjectManager<TProvisioner>::GetList()[FormProvisionerList->MyListView->ipp[FormProvisionerList->MyListView->ItemIndex]];
			LoadFromObjectToForm(TmpProvisioner);
			ComponentsDisable();
			ButtonSave->Caption = wButSaveCaption[iLang];
			ButtonSave->Enabled = false;
			ButtonSave->OnClick = NULL;
			ButtonClose->Caption = wButCloseCaption[iLang];
			break;
		case TButtonAction::BA_EDIT:
			TmpProvisioner = TObjectManager<TProvisioner>::GetList()[FormProvisionerList->MyListView->ipp[FormProvisionerList->MyListView->ItemIndex]];
			LoadFromObjectToForm(TmpProvisioner);
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
			TmpProvisioner = new TProvisioner();
			TmpProvisioner->Clear();
			break;
		default:
            break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormProvisionerData::ButtonCloseClick(TObject *Sender)
{
	if(FormProvisionerList->ButtonAction == TButtonAction::BA_ADD) {
		delete TmpProvisioner;
	}
	TmpProvisioner = NULL;

	Close();
}

//---------------------------------------------------------------------------
void __fastcall TFormProvisionerData::ButtonSaveClick(TObject *Sender)
{
	SaveAtFormToObject(TmpProvisioner);
	TmpProvisioner->SaveAtObjectToDb(FormShop->FDQuery1);

//	TObjectManager<TProvisioner>::GetList()[FormProvisionerList->MyListView->ipp[FormProvisionerList->MyListView->ItemIndex]] = TmpProvisioner;
	FormProvisionerList->MyListView->FillList();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormProvisionerData::ButtonInsertClick(TObject *Sender)
{
	SaveAtFormToObject(TmpProvisioner);
	TmpProvisioner->InsertAtObjectToDb(FormShop->FDQuery1);

//	TObjectManager<TProvisioner>::GetList().push_back(TmpProvisioner);
//	TmpProvisioner = new TProvisioner();

	FormProvisionerList->MyListView->FillList();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormProvisionerData::ClearFields(void)
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
void __fastcall TFormProvisionerData::ComponentsEnable(void)
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
void __fastcall TFormProvisionerData::ComponentsDisable(void)
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
void __fastcall TFormProvisionerData::LoadFromObjectToForm(TProvisioner *CurProvisioner)
{
	EditSurname->Text = CurProvisioner->Surname;
	EditName->Text = CurProvisioner->Name;
	EditPatronymic->Text = CurProvisioner->Patronymic;
	EditOrganization->Text = CurProvisioner->Organization;
	EditAddress->Text = CurProvisioner->Address;
	EditPhone1->Text = CurProvisioner->Phone1;
	EditPhone2->Text = CurProvisioner->Phone2;
	MemoDescription->Text = CurProvisioner->Description;
	CheckBoxEnable->Checked = CurProvisioner->Enabled;
}

//---------------------------------------------------------------------------
void __fastcall TFormProvisionerData::SaveAtFormToObject(TProvisioner *CurProvisioner)
{
	CurProvisioner->Surname = EditSurname->Text;
	CurProvisioner->Name = EditName->Text;
	CurProvisioner->Patronymic = EditPatronymic->Text;
	CurProvisioner->Organization = EditOrganization->Text;
	CurProvisioner->Address = EditAddress->Text;
	CurProvisioner->Phone1 = EditPhone1->Text;
	CurProvisioner->Phone2 = EditPhone2->Text;
	CurProvisioner->Description = MemoDescription->Text;
    CurProvisioner->SetSumName();
	CurProvisioner->Enabled = CheckBoxEnable->Checked;
}
//---------------------------------------------------------------------------
