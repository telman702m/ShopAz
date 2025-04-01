//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
//#include <iostream.h>

#pragma hdrstop

#include "Shop.h"
#include "UnitGroupProduct.h"
#include "UnitGroupList.h"
#include "UnitProduct.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TLabelCaption LabelCaptionsGroupProd[] = {
	{{L"Код группы товаров",		L"Mallar grupun kodu"},		NULL},
	{{L"Название группы товаров",   L"Mallar grupun adı"},		NULL},
	{{L"Описание группы товаров",	L"Mallar grupun təsviri"},	NULL}
};
TCheckBoxCaption CheckBoxCaptionGroupProd[] = {
	{{L"Активный", L"Aktiv"}, NULL}
};

TFormGroupProduct *FormGroupProduct;

//---------------------------------------------------------------------------
__fastcall TFormGroupProduct::TFormGroupProduct(TComponent* Owner)
	: TFormEsc(Owner)
{
	wFormCaptions[0] = L"Данные о группе товаров";
	wFormCaptions[1] = L"Mallar grupu haqqında məlumat";

	SizeLabelsData = sizeof(LabelCaptionsGroupProd) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionsGroupProd;

	SizeCheckBoxData = sizeof(CheckBoxCaptionGroupProd) / sizeof(TLabelCaption);
	CheckBoxCaption = CheckBoxCaptionGroupProd;
}
//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::FormCreate(TObject *Sender)
{
	LabelsCaption[0].Label = LabelGroupCode;
	LabelsCaption[1].Label = LabelGroupName;
	LabelsCaption[2].Label = LabelDescription;

	CheckBoxCaption[0].CheckBox = CheckBoxEnable;

	SetLanguage();

	TmpGroupProd = NULL;
//	TmpGroupProd = new TGroupProduct();
}
//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::FormClose(TObject *Sender, TCloseAction &Action)
{
//	AccessGroupProd = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::FormShow(TObject *Sender)
{
	switch(FormGroupList->ButtonAction) {
		case TButtonAction::BA_VIEW:
//			*TmpGroupProd = *(TGroupProduct::VGroupProduct[FormGroupList->MyListView->ItemIndex]);
			TmpGroupProd = TGroupProduct::VGroupProduct[FormGroupList->MyListView->ItemIndex];
			LoadFromObjectToForm(TmpGroupProd);
			ComponentsDisable();
			ButtonInsert->Caption = wButSaveCaption[iLang];
			ButtonInsert->Enabled = false;
			ButtonInsert->OnClick = NULL;
			ButtonClose->Caption = wButCloseCaption[iLang];
			break;
		case TButtonAction::BA_EDIT:
//			*TmpGroupProd = *(TGroupProduct::VGroupProduct[FormGroupList->MyListView->ItemIndex]);
			TmpGroupProd = TGroupProduct::VGroupProduct[FormGroupList->MyListView->ItemIndex];
			LoadFromObjectToForm(TmpGroupProd);
			ComponentsEnable();
			ButtonInsert->Caption = wButSaveCaption[iLang];
			ButtonInsert->Enabled = true;
			ButtonInsert->OnClick = ButtonSaveClick;
			ButtonClose->Caption = wButCancelCaption[iLang];
			break;
		case TButtonAction::BA_ADD:
			ComponentsEnable();
			ButtonInsert->Caption = wButInsertCaption[iLang];
			ButtonInsert->Enabled = true;
			ButtonInsert->OnClick = ButtonInsertClick;
			ButtonClose->Caption = wButCancelCaption[iLang];
			ClearFields();
			TmpGroupProd = new TGroupProduct();
			TmpGroupProd->Clear();
			break;
		default:
            break;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::ButtonCloseClick(TObject *Sender)
{
	if(FormGroupList->ButtonAction == TButtonAction::BA_ADD) {
		delete TmpGroupProd;
	}
	TmpGroupProd = NULL;

	Close();
}

//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::ButtonSaveClick(TObject *Sender)
{
	SaveAtFormToObject(TmpGroupProd);
	TmpGroupProd->SaveAtObjectToDb(FormShop->FDQuery1);

//	*(TGroupProduct::VGroupProduct[FormGroupList->MyListView->ItemIndex]) = *TmpGroupProd;

	FormGroupList->MyListView->FillList();

	LoadGroupsToCombo();

	Close();
}

//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::ButtonInsertClick(TObject *Sender)
{
	SaveAtFormToObject(TmpGroupProd);
	TmpGroupProd->InsertAtObjectToDb(FormShop->FDQuery1);

//	TGroupProduct::VGroupProduct.push_back(TmpGroupProd);
//	TmpGroupProd = new TGroupProduct();

	FormGroupList->MyListView->FillList();

	LoadGroupsToCombo();

	Close();
}

//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::LoadFromObjectToForm(TGroupProduct *CurGroupProd)
{
	EditCode->Text = CurGroupProd->GroupCode;
	EditName->Text = CurGroupProd->Name;
	MemoDescription->Text = CurGroupProd->Description;
	CheckBoxEnable->Checked = CurGroupProd->Enabled;
}

//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::SaveAtFormToObject(TGroupProduct *CurGroupProd)
{
	 CurGroupProd->GroupCode = EditCode->Text;
	 CurGroupProd->Name = EditName->Text;
	 CurGroupProd->Description = MemoDescription->Text;
	 CurGroupProd->Enabled = CheckBoxEnable->Checked;
}

//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::ClearFields(void)
{
	EditCode->Text = L"";
	EditName->Text = L"";
	MemoDescription->Text = L"";
	CheckBoxEnable->Checked = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::ComponentsEnable(void)
{
	EditCode->ReadOnly = false;
	EditName->ReadOnly = false;
	MemoDescription->ReadOnly = false;

	EditCode->Enabled = true;
	EditName->Enabled = true;
	MemoDescription->Enabled = true;
	CheckBoxEnable->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::ComponentsDisable(void)
{
	EditCode->ReadOnly = true;
	EditName->ReadOnly = true;
	MemoDescription->ReadOnly = true;

	EditCode->Enabled = false;
	EditName->Enabled = false;
	MemoDescription->Enabled = false;
	CheckBoxEnable->Enabled = false;
}

//---------------------------------------------------------------------------
void __fastcall TFormGroupProduct::LoadGroupsToCombo(void)
{
	FormProduct->ComboBoxGroup->Clear();
	for(int i=0; i < (int)TGroupProduct::VGroupProduct.size(); i++) {
		FormProduct->ComboBoxGroup->Items->Add(TGroupProduct::VGroupProduct[i]->Name);
	}
}
//---------------------------------------------------------------------------

