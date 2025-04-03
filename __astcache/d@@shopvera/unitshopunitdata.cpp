//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitShopUnitData.h"
#include "UnitShopUnitList.h"
#include "Shop.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TLabelCaption LabelCaptionsShopUnitData[] = {
	{{L"Тип объекта",	L"Obyektin növü"},	NULL},
	{{L"Название",		L"Adı"},			NULL},
	{{L"Адрес",			L"Ünvan"},			NULL},
	{{L"Телефон1",		L"Telefon1"},		NULL},
	{{L"Телефон2",		L"Telefon2"},		NULL},
	{{L"Описание",		L"Təsviri"},		NULL}
};
TCheckBoxCaption CheckBoxCaptionShopUnitData[] = {
	{{L"Активный", L"Aktiv"}, NULL}
};

TFormShopUnit *FormShopUnit;

//---------------------------------------------------------------------------
__fastcall TFormShopUnit::TFormShopUnit(TComponent* Owner)
	: TFormEsc(Owner)
{
	wFormCaptions[0] = L"Данные об объекте сети магазинов";
	wFormCaptions[1] = L"Mağazalar şəbəkəsinin obyekti haqqında informasiya";

	SizeLabelsData = sizeof(LabelCaptionsShopUnitData) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionsShopUnitData;

	SizeCheckBoxData = sizeof(CheckBoxCaptionShopUnitData) / sizeof(TLabelCaption);
	CheckBoxCaption = CheckBoxCaptionShopUnitData;
}
//---------------------------------------------------------------------------
void __fastcall TFormShopUnit::FormCreate(TObject *Sender)
{
	LabelsCaption[0].Label = LabelType;
	LabelsCaption[1].Label = LabelName;
	LabelsCaption[2].Label = LabelAddress;
	LabelsCaption[3].Label = LabelPhone1;
	LabelsCaption[4].Label = LabelPhone2;
	LabelsCaption[5].Label = LabelDescript;

	CheckBoxCaption[0].CheckBox = CheckBoxEnable;

	SetLanguage();

	TmpShopUnit = new TShopUnits();
}
//---------------------------------------------------------------------------
void __fastcall TFormShopUnit::FormShow(TObject *Sender)
{
	switch(FormShopUnitsList->ButtonAction) {
		case TButtonAction::BA_VIEW:
			*TmpShopUnit = *(TObjectManager<TShopUnits>::GetList()[FormShopUnitsList->MyListView->ipp[FormShopUnitsList->MyListView->ItemIndex]]);
			LoadFromObjectToForm(TmpShopUnit);
			ComponentsDisable();
			ButtonSave->Caption = wButSaveCaption[iLang];
			ButtonSave->Enabled = false;
			ButtonSave->OnClick = NULL;
			ButtonClose->Caption = wButCloseCaption[iLang];
			break;
		case TButtonAction::BA_EDIT:
			*TmpShopUnit = *(TObjectManager<TShopUnits>::GetList()[FormShopUnitsList->MyListView->ipp[FormShopUnitsList->MyListView->ItemIndex]]);
			LoadFromObjectToForm(TmpShopUnit);
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
			TmpShopUnit->Clear();
			break;
		default:
            break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormShopUnit::ButtonSaveClick(TObject *Sender)
{
	SaveAtFormToObject(TmpShopUnit);
	TmpShopUnit->SaveAtObjectToDb(FormShop->FDQuery1);

	*(TObjectManager<TShopUnits>::GetList()[FormShopUnitsList->MyListView->ipp[FormShopUnitsList->MyListView->ItemIndex]]) = *TmpShopUnit;
	FormShopUnitsList->MyListView->FillList();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormShopUnit::ButtonInsertClick(TObject *Sender)
{
	SaveAtFormToObject(TmpShopUnit);
	TmpShopUnit->InsertAtObjectToDb(FormShop->FDQuery1);

	TObjectManager<TShopUnits>::GetList().push_back(TmpShopUnit);
	TmpShopUnit = new TShopUnits();

	FormShopUnitsList->MyListView->FillList();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormShopUnit::ButtonCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormShopUnit::ClearFields(void)
{
	EditName->Text = L"";
	EditAddress->Text = L"";
	EditPhone1->Text = L"";
	EditPhone2->Text = L"";
	MemoDescription->Text = L"";
	CheckBoxEnable->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormShopUnit::ComponentsEnable(void)
{
	EditName->ReadOnly = false;
	EditAddress->ReadOnly = false;
	EditPhone1->ReadOnly = false;
	EditPhone2->ReadOnly = false;

	EditName->Enabled = true;
	EditAddress->Enabled = true;
	EditPhone1->Enabled = true;
	EditPhone2->Enabled = true;

	MemoDescription->Enabled = true;
	CheckBoxEnable->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormShopUnit::ComponentsDisable(void)
{
	EditName->ReadOnly = true;
	EditAddress->ReadOnly = true;
	EditPhone1->ReadOnly = true;
	EditPhone2->ReadOnly = true;

	EditName->Enabled = false;
	EditAddress->Enabled = false;
	EditPhone1->Enabled = false;
	EditPhone2->Enabled = false;

	MemoDescription->Enabled = false;
	CheckBoxEnable->Enabled = false;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void __fastcall TFormShopUnit::LoadFromObjectToForm(TShopUnits *CurShopUnits)
{
	ComboBoxType->ItemIndex = CurShopUnits->TypeUnit;
	EditName->Text = CurShopUnits->Name;
	EditAddress->Text = CurShopUnits->Address;
	EditPhone1->Text = CurShopUnits->Phone1;
	EditPhone2->Text = CurShopUnits->Phone2;
	MemoDescription->Text = CurShopUnits->Description;
	CheckBoxEnable->Checked = CurShopUnits->Enabled;
}

//---------------------------------------------------------------------------
void __fastcall TFormShopUnit::SaveAtFormToObject(TShopUnits *CurShopUnits)
{
	CurShopUnits->TypeUnit = TypeShopUnit(ComboBoxType->ItemIndex);
	CurShopUnits->Name = EditName->Text;
	CurShopUnits->Address = EditAddress->Text;
	CurShopUnits->Phone1 = EditPhone1->Text;
	CurShopUnits->Phone2 = EditPhone2->Text;
	CurShopUnits->Description = MemoDescription->Text;
	CurShopUnits->Enabled = CheckBoxEnable->Checked;
}
//---------------------------------------------------------------------------
