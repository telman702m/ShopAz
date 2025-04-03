//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Shop.h"
#include "UnitProduct.h"
#include "UnitProductList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wUndefinedCaption[] = {L"Неопределен", L"Nəməlum"};

const wchar_t *wCheckField1[] = {
	L"Не выбрана группа из списка <Группа товаров>! Выберите из списка <Группа товаров>!",
	L"<Mallar grupu> siyahısından heç bit grup seçilmayıb! Seçim edin <Mallar grupu> siyahısından!"
};
const wchar_t *wCheckField2[] = {
	L"Не заполнено поле <Код продукта>!",
	L"<Malın kodu> xanəsi doldurulmayıb!"
};
const wchar_t *wCheckField3[] = {
	L"Не заполнено поле <Название продукта>!",
	L"<Malın adı> xanəsi doldurulmayıb!"
};
const wchar_t *wCheckField4[] = {
	L"Не заполнено поле <Стоимость продукта>!",
	L"<Malın dəyəri> xanəsi doldurulmayıb!"
};
const wchar_t *wCheckField5[] = {
	L"Не заполнено поле <Цена продукта>!",
	L"<Malın qiyməti> xanəsi doldurulmayıb!"
};
const wchar_t *wCheckField6[] = {
	L"Не заполнено поле <Единица измерения>!",
	L"<Ölçü vahidi> xanəsi doldurulmayıb!"
};

const wchar_t *wWholeField1[] = {
	L"Количество данного товара в операциях будет принимать только целочисленные значения!",
	L"Əməliyyatlarda bu malın miqdarı ancaq tam rəqəmlər ala biləcək!"
};
const wchar_t *wWholeField2[] = {
	L"Количество данного товара в операциях может принимать любые вещественные значения!",
	L"Əməliyyatlarda bu malın miqdarı ixtiyarı rəqəmlər ala biləcək!"
};

TLabelCaption LabelCaptionsProduct[] = {
	{{L"Группа товаров",	L"Mallar grupu"},			NULL},
	{{L"Код Товара",   		L"Malın kodu"},				NULL},
	{{L"Название товара",	L"Malın adı"},				NULL},
	{{L"Стоимость",   		L"Dəyəri"},					NULL},
	{{L"Стоимость $",		L"Dəyəri $"},				NULL},
	{{L"Цена",   			L"Qiymət"},					NULL},
	{{L"Оптовая цена",		L"Topdansatış qiyməti"},	NULL},
	{{L"Единица измерения",	L"Ölçü vahidi"},			NULL},
	{{L"манат",				L"manat"},					NULL},
	{{L"копеек",   			L"qəpik"},					NULL},
	{{L"доллар",			L"dollar"},					NULL},
	{{L"цент",   			L"sent"},					NULL},
	{{L"манат",				L"manat"},					NULL},
	{{L"копеек",   			L"qəpik"},					NULL},
	{{L"манат",				L"manat"},					NULL},
	{{L"копеек",   			L"qəpik"},					NULL},
	{{L"Описание товара",	L"Malın təsviri"},			NULL}
};
TCheckBoxCaption CheckBoxCaptionProduct[] = {
	{{L"штучный",	L"dənəli"},	NULL},
	{{L"Активный",	L"Aktiv"},	NULL}
};

TFormProduct *FormProduct;

//---------------------------------------------------------------------------
__fastcall TFormProduct::TFormProduct(TComponent* Owner)
	: TFormEsc(Owner)
{
	SizeLabelsData = sizeof(LabelCaptionsProduct) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionsProduct;

	SizeCheckBoxData = sizeof(CheckBoxCaptionProduct) / sizeof(TCheckBoxCaption);
	CheckBoxCaption = CheckBoxCaptionProduct;
}
//---------------------------------------------------------------------------
void __fastcall TFormProduct::FormCreate(TObject *Sender)
{
	wFormCaptions[0] = L"Характеристики товара";
	wFormCaptions[1] = L"Malın xüsusiyyətləri";

	LabelsCaption[0].Label = LabelGroup;
	LabelsCaption[1].Label = LabelCode;
	LabelsCaption[2].Label = LabelName;
	LabelsCaption[3].Label = LabelCash;
	LabelsCaption[4].Label = LabelPurchaseDollar1;
	LabelsCaption[5].Label = LabelRetail;
	LabelsCaption[6].Label = LabelWholePrice;
	LabelsCaption[7].Label = LabelUnit;
	LabelsCaption[8].Label = LabelDollar1;
	LabelsCaption[9].Label = LabelCent1;
	LabelsCaption[10].Label = LabelDollar2;
	LabelsCaption[11].Label = LabelCent2;
	LabelsCaption[12].Label = LabelDollar3;
	LabelsCaption[13].Label = LabelCent3;
	LabelsCaption[14].Label = LabelDollar4;
	LabelsCaption[15].Label = LabelCent4;
	LabelsCaption[16].Label = LabelDescription;

	CheckBoxCaption[0].CheckBox = CheckBoxWholeUnit;
	CheckBoxCaption[1].CheckBox = CheckBoxEnable;

	SetLanguage();

//	TmpProduct = new TProduct();
//	TmpProduct->Clear();
	TmpProduct = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormProduct::FormClose(TObject *Sender, TCloseAction &Action)
{
//	AccessProduct = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormProduct::FormShow(TObject *Sender)
{
	CheckBoxWholeUnit->OnClick = NULL;

	FormGroupProduct->LoadGroupsToCombo();

	switch(FormProductList->ButtonAction) {
		case TButtonAction::BA_VIEW:
//			*TmpProduct = *(TProduct::VProduct[FormProductList->MyListView->ipp[FormProductList->MyListView->ItemIndex]]);
			TmpProduct = TProduct::VProduct[FormProductList->MyListView->ipp[FormProductList->MyListView->ItemIndex]];
			LoadFromObjectToForm(TmpProduct);
			ComponentsDisable();
			ButtonSave->Caption = wButSaveCaption[iLang];
			ButtonSave->Enabled = false;
			ButtonSave->OnClick = NULL;
			ButtonClose->Caption = wButCloseCaption[iLang];
			break;
		case TButtonAction::BA_EDIT:
//			*TmpProduct = *(TProduct::VProduct[FormProductList->MyListView->ipp[FormProductList->MyListView->ItemIndex]]);
			TmpProduct = TProduct::VProduct[FormProductList->MyListView->ipp[FormProductList->MyListView->ItemIndex]];
			ComponentsEnable();
			ButtonSave->Caption = wButSaveCaption[iLang];
			ButtonSave->Enabled = true;
			ButtonSave->OnClick = ButtonSaveClick;
			ButtonClose->Caption = wButCancelCaption[iLang];
			LoadFromObjectToForm(TmpProduct);
			break;
		case TButtonAction::BA_ADD:
			TmpProduct = new TProduct();
			TmpProduct->Clear();
			ClearFields();
			ComponentsEnable();
			ButtonSave->Caption = wButInsertCaption[iLang];
			ButtonSave->Enabled = true;
			ButtonSave->OnClick = ButtonInsertClick;
			ButtonClose->Caption = wButCancelCaption[iLang];
//			ComboBoxGroup->ItemIndex = FormProductList->ComboBoxFilter->ItemIndex - 1;
			ComboBoxGroup->ItemIndex = GetComboBoxIndex(FormProductList->ComboBoxFilter->Text);
			break;
		default:
            break;
	}
	CheckBoxWholeUnit->OnClick = CheckBoxWholeUnitClick;
}

//---------------------------------------------------------------------------
void __fastcall TFormProduct::ButtonCloseClick(TObject *Sender)
{
	if(FormProductList->ButtonAction == TButtonAction::BA_ADD) {
		delete TmpProduct;
	}
	TmpProduct = NULL;

	Close();
}

//---------------------------------------------------------------------------
void __fastcall TFormProduct::ButtonSaveClick(TObject *Sender)
{
	if(CheckFields()) {
		SaveAtFormToObject(TmpProduct);
		TmpProduct->SaveAtObjectToDb(FormShop->FDQuery1);

//		*(TProduct::VProduct[FormProductList->MyListView->ipp[FormProductList->MyListView->ItemIndex]]) = *TmpProduct;
		FormProductList->MyListView->FillList();
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormProduct::ButtonInsertClick(TObject *Sender)
{
	if(CheckFields()) {
		SaveAtFormToObject(TmpProduct);
		TmpProduct->InsertAtObjectToDb(FormShop->FDQuery1);

//		TProduct::VProduct.push_back(TmpProduct);
//		TmpProduct = new TProduct();

		FormProductList->MyListView->FillList();
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormProduct::LoadFromObjectToForm(TProduct *CurProd)
{
//	int index = TGroupProduct::GetArrayIndexForIdGroup(CurProd->IdGroup);
	int index = GetComboBoxIndex(CurProd->GroupProd->Name);
	if(index != -1) {
		ComboBoxGroup->ItemIndex = index;
	} else {
		ComboBoxGroup->ItemIndex = -1;
		ComboBoxGroup->Text = wUndefinedCaption[iLang];
	}
	EditGroup->Text = CurProd->GroupProd->Name;
	EditCode->Text = CurProd->Code;
	EditName->Text = CurProd->Name;
	EditUnit->Text = CurProd->Unit;

	if(FormShop->Worker->Privilege < TPrivilege::PRV_MANAGER) {
		EditPurchasePrice1->Text = CurProd->PurchaseCash.GetMoney();
		EditPurchasePrice2->Text = CurProd->PurchaseCash.GetCent();
		EditPurchaseDollar1->Text = CurProd->DollarPrice.GetMoney();
		EditPurchaseDollar2->Text = CurProd->DollarPrice.GetCent();
	} else {
		EditPurchasePrice1->Text = TPrice::uHidden;
		EditPurchasePrice2->Text = TPrice::uHidden;
		EditPurchaseDollar1->Text = TPrice::uHidden;
		EditPurchaseDollar2->Text = TPrice::uHidden;
	}
	EditWholePrice1->Text = CurProd->WholePrice.GetMoney();
	EditWholePrice2->Text = CurProd->WholePrice.GetCent();
	EditSellingPrice1->Text = CurProd->SellingPrice.GetMoney();
	EditSellingPrice2->Text = CurProd->SellingPrice.GetCent();
	MemoDescription->Text = CurProd->Description;
	CheckBoxWholeUnit->Checked = CurProd->WholeUnit;
	CheckBoxEnable->Checked = CurProd->Enable;
}

//---------------------------------------------------------------------------
void __fastcall TFormProduct::SaveAtFormToObject(TProduct *CurProd)
{
	CurProd->GroupProd = TGroupProduct::GetGroupProdByName(ComboBoxGroup->Text);
	CurProd->IdGroup = CurProd->GroupProd->id;
	CurProd->Code = EditCode->Text;
	CurProd->Name = EditName->Text;
	CurProd->Unit = EditUnit->Text;

	CurProd->PurchaseCash.GetFromTEdit(EditPurchasePrice1, EditPurchasePrice2);
	CurProd->DollarPrice.GetFromTEdit(EditPurchaseDollar1, EditPurchaseDollar2);
	CurProd->SellingPrice.GetFromTEdit(EditSellingPrice1, EditSellingPrice2);
	CurProd->WholePrice.GetFromTEdit(EditWholePrice1, EditWholePrice2);

	CurProd->Description = MemoDescription->Text;
	CurProd->WholeUnit = CheckBoxWholeUnit->Checked;

	CurProd->Enable = CheckBoxEnable->Checked;
}

//---------------------------------------------------------------------------
bool __fastcall TFormProduct::CheckFields(void)
{
	UnicodeString uTmp = L"";

	if(ComboBoxGroup->ItemIndex == -1) {
		uTmp = wCheckField1[iLang];
	} else if(EditCode->Text == L"") {
		uTmp = wCheckField2[iLang];
	} else if(EditCode->Text.Pos(L"'") > 0) {
		uTmp = uIllegalSymbol[iLang];
	} else if(EditName->Text == L"") {
		uTmp = wCheckField3[iLang];
	} else if(EditName->Text.Pos(L"'") > 0) {
		uTmp = uIllegalSymbol[iLang];
	} else if(EditPurchasePrice1->Text == L"" && EditPurchasePrice2->Text == L"") {
		uTmp = wCheckField4[iLang];
	} else if(EditSellingPrice1->Text == L"" && EditSellingPrice2->Text == L"") {
		uTmp = wCheckField5[iLang];
	} else if(EditUnit->Text == L"") {
		uTmp = wCheckField6[iLang];
	} else if(EditUnit->Text.Pos(L"'") > 0) {
		uTmp = uIllegalSymbol[iLang];
	} else if(MemoDescription->Text.Pos(L"'") > 0) {
		uTmp = uIllegalSymbol[iLang];
	}

	if(uTmp != L"") {
		Application->MessageBox(uTmp.w_str(), uCaptionError[iLang], MB_OK);
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormProduct::ClearFields(void)
{
	ComboBoxGroup->ItemIndex = -1;
	EditCode->Text = L"";
	EditName->Text = L"";
	EditUnit->Text = L"";
	EditPurchasePrice1->Text = L"";
	EditPurchasePrice2->Text = L"";
	EditPurchaseDollar1->Text = L"";
	EditPurchaseDollar2->Text = L"";
	EditSellingPrice1->Text = L"";
	EditSellingPrice2->Text = L"";
	EditWholePrice1->Text = L"";
	EditWholePrice2->Text = L"";
	MemoDescription->Text = L"";
	CheckBoxWholeUnit->Checked = false;
	CheckBoxEnable->Checked = false;
}

//---------------------------------------------------------------------------
void __fastcall TFormProduct::ComponentsEnable(void)
{
	EditGroup->ReadOnly = false;
	EditCode->ReadOnly = false;
	EditName->ReadOnly = false;
	EditUnit->ReadOnly = false;

	if(FormShop->Worker->Privilege < TPrivilege::PRV_MANAGER) {
		EditPurchasePrice1->ReadOnly = false;
		EditPurchasePrice2->ReadOnly = false;
		EditPurchaseDollar1->ReadOnly = false;
		EditPurchaseDollar2->ReadOnly = false;
	} else {
		EditPurchasePrice1->ReadOnly = true;
		EditPurchasePrice2->ReadOnly = true;
		EditPurchaseDollar1->ReadOnly = true;
		EditPurchaseDollar2->ReadOnly = true;
	}
	EditSellingPrice1->ReadOnly = false;
	EditSellingPrice2->ReadOnly = false;
	EditWholePrice1->ReadOnly = false;
	EditWholePrice2->ReadOnly = false;

	EditGroup->Enabled = true;
	ComboBoxGroup->Enabled = true;
	EditCode->Enabled = true;
	EditName->Enabled = true;
	EditUnit->Enabled = true;

	if(FormShop->Worker->Privilege < TPrivilege::PRV_MANAGER) {
		EditPurchasePrice1->Enabled = true;
		EditPurchasePrice2->Enabled = true;
		EditPurchaseDollar1->Enabled = true;
		EditPurchaseDollar2->Enabled = true;
	} else {
		EditPurchasePrice1->Enabled = false;
		EditPurchasePrice2->Enabled = false;
		EditPurchaseDollar1->Enabled = false;
		EditPurchaseDollar2->Enabled = false;
	}
	EditSellingPrice1->Enabled = true;
	EditSellingPrice2->Enabled = true;
	EditWholePrice1->Enabled = true;
	EditWholePrice2->Enabled = true;

	MemoDescription->Enabled = true;
	CheckBoxWholeUnit->Enabled = true;

	EditGroup->Visible = false;
	ComboBoxGroup->Visible = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormProduct::ComponentsDisable(void)
{
	EditGroup->ReadOnly = true;
	EditCode->ReadOnly = true;
	EditName->ReadOnly = true;
	EditUnit->ReadOnly = true;
	EditPurchasePrice1->ReadOnly = true;
	EditPurchasePrice2->ReadOnly = true;
	EditPurchaseDollar1->ReadOnly = true;
	EditPurchaseDollar2->ReadOnly = true;
	EditSellingPrice1->ReadOnly = true;
	EditSellingPrice2->ReadOnly = true;
	EditWholePrice1->ReadOnly = true;
	EditWholePrice2->ReadOnly = true;

	EditGroup->Enabled = false;
	ComboBoxGroup->Enabled = false;
	EditCode->Enabled = false;
	EditName->Enabled = false;
	EditUnit->Enabled = false;
	EditPurchasePrice1->Enabled = false;
	EditPurchasePrice2->Enabled = false;
	EditPurchaseDollar1->Enabled = false;
	EditPurchaseDollar2->Enabled = false;
	EditSellingPrice1->Enabled = false;
	EditSellingPrice2->Enabled = false;
	EditWholePrice1->Enabled = false;
	EditWholePrice2->Enabled = false;

	MemoDescription->Enabled = false;
	CheckBoxWholeUnit->Enabled = false;

	EditGroup->Visible = true;
	ComboBoxGroup->Visible = false;
}

//---------------------------------------------------------------------------
void __fastcall TFormProduct::CheckBoxWholeUnitClick(TObject *Sender)
{
	if(CheckBoxWholeUnit->Checked) {
		ShowMessage(wWholeField1[iLang]);
	} else {
		ShowMessage(wWholeField2[iLang]);
	}
}
//---------------------------------------------------------------------------
int __fastcall TFormProduct::GetComboBoxIndex(UnicodeString Name)
{
	for(int i=0; i < ComboBoxGroup->Items->Count; i++) {
		if(ComboBoxGroup->Items->Strings[i] == Name) {
			return i;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------

