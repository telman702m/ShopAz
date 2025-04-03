//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitSelectProduct.h"
#include "UnitProductList.h"
#include "UnitMoveProduct.h"
#include "Shop.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wLimitProdMess[] = {
	L"Указанное количество выбранного товара отсутствует в магазине!",
	L"Seçilmiş malın miqdarı mağazada yoxdur!"
};
const wchar_t *wIncorrectPrice[] = {
	L"Цена или стоимость выбранного товара не корректна!",
	L"Seçilmiş malın satış qiyməti və ya dəyəri düzgün deyil!"
};

TLabelCaption LabelCaptionSelectProd[] = {
	{{L"Код товара",					L"Malın kodu"},				NULL},
	{{L"Название",						L"Malın adı"},				NULL},
	{{L"Стоимость",						L"Dəyəri"},					NULL},
	{{L"Цена",							L"Qiyməti"},				NULL},
	{{L"Опт.Цена",						L"Top.Qiyməti"},			NULL},
	{{L"Количество товара в наличие: ",	L"Malın mövcud miqdarı"},	NULL},
	{{L"Количество",					L"Miqdarı"},				NULL},
	{{L"Сумм.стоим.",					L"Cəmi dəyəri"},			NULL},
	{{L"Сумма",							L"Cəmi məbləği"},			NULL},
};
TButtonCaption ButtonCaptionSelectProd[] = {
	{{L"Добавить",	L"Daxil"},	NULL},
	{{L"Отмена",	L"Cancel"},	NULL}
};

TFormSelectProd *FormSelectProd;

//---------------------------------------------------------------------------
__fastcall TFormSelectProd::TFormSelectProd(TComponent* Owner)
	: TFormEsc(Owner)
{
	wFormCaptions[0] = L"Выбор товара";
	wFormCaptions[1] = L"Malın seçilməsi";

	SizeLabelsData = sizeof(LabelCaptionSelectProd) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionSelectProd;

	SizeButtonsData = sizeof(ButtonCaptionSelectProd) / sizeof(TButtonCaption);
	ButtonsCaption = ButtonCaptionSelectProd;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::SetLanguage(void)
{
	const wchar_t *wLabelMoneyCaptions[][2] = {
		{L"манат",							L"manat"},
		{L"копеек",							L"qəpik"}
	};
	TLabel *MyMoneyLabels[] = {
		LabelMoneyC,
		LabelCentC,
		LabelMoney,
		LabelCent,
		LabelMoneyW,
		LabelCentW,
		LabelMoneySumS,
		LabelCentSumS,
		LabelMoneySum,
		LabelCentSum
	};
	for(unsigned i=0; i < sizeof(MyMoneyLabels)/sizeof(TLabel*); i++) {
		MyMoneyLabels[i]->Caption = wLabelMoneyCaptions[i%2][iLang];
	}

	TFormEsc::SetLanguage();
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::FormCreate(TObject *Sender)
{
	LabelsCaption[0].Label = LabelProdCode;
	LabelsCaption[1].Label = LabelProdName;
	LabelsCaption[2].Label = LabelCost;
	LabelsCaption[3].Label = LabelPrice;
	LabelsCaption[4].Label = LabelWholePrice;
	LabelsCaption[5].Label = LabelInStock1;
	LabelsCaption[6].Label = LabelCount;
	LabelsCaption[7].Label = LabelSumS;
	LabelsCaption[8].Label = LabelSum;

	ButtonsCaption[0].Button = ButtonSubmit;
	ButtonsCaption[1].Button = ButtonCancel;

	SetLanguage();

	TmpSelectProd = new TSelectProduct();
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::ClearFields(void)
{
	EditCodeProd->Text = L"";
	EditNameProd->Text = L"";
	EditCost1->Text = L"";
	EditCost2->Text = L"";
	EditSalePrice1->Text = L"";
	EditSalePrice2->Text = L"";
	EditWholePrice1->Text = L"";
	EditWholePrice2->Text = L"";
	EditCount1->Text = L"";
	EditCount2->Text = L"";
	EditTotalPrice1->Text = L"";
	EditTotalPrice2->Text = L"";
	LabelCashBalance->Caption = L"";
	LabelUnit->Caption = L"";
	LabelUnit2->Caption = L"";
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::DesignForm(void)
{
	DesignInputCount(false, false);

	switch(FormMoveProduct->ButtonAction) {
		case TButtonAction::BA_VIEW:
			EditCodeProd->Enabled = false;
			EditNameProd->Enabled = false;
			EditCost1->Enabled = false;
			EditCost2->Enabled = false;
			EditCount1->Enabled = false;
			EditCount2->Enabled = false;
			break;
		case TButtonAction::BA_ADD:
		case TButtonAction::BA_EDIT:
			EditCodeProd->Enabled = true;
			EditNameProd->Enabled = true;
			EditCount1->Enabled = true;
			EditCount2->Enabled = true;
			break;
		default:
            break;
	}
	ButtonSubmit->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::DesignInputCount(bool bEnable, bool bWhole)
{
	EditCount1->Enabled = bEnable;
	EditCount2->Enabled = bEnable;

	if(bWhole) {
		EditCount2->Visible = false;
		LabelUnit->Left = 190;
	} else {
		EditCount2->Visible = true;
		LabelUnit->Left = 245;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::FormShow(TObject *Sender)
{
	bButtonAddCall = false;

	DesignForm();

	switch(FormMoveProduct->ButtonAction) {
		case TButtonAction::BA_VIEW:
			*TmpSelectProd = *(FormMoveProduct->TmpMoveProduct->VSelectedProd[FormMoveProduct->MyListView->ipp[FormMoveProduct->MyListView->ItemIndex]]);
			ButtonSubmit->OnClick = NULL;
			ButtonSubmit->Caption = L"";
			break;
		case TButtonAction::BA_EDIT:
			*TmpSelectProd = *(FormMoveProduct->TmpMoveProduct->VSelectedProd[FormMoveProduct->MyListView->ipp[FormMoveProduct->MyListView->ItemIndex]]);
			ButtonSubmit->OnClick = ButtonSaveClick;
			ButtonSubmit->Caption = wButSaveCaption[iLang];
			break;
		case TButtonAction::BA_ADD:
			TmpSelectProd->Clear();
			ClearFields();
			ButtonSubmit->OnClick = ButtonInsertClick;
			ButtonSubmit->Caption = wButInsertCaption[iLang];
			break;
		default:
			return;
	}
	iMult = FormMoveProduct->TmpMoveProduct->GetBalanceMult();
	LoadFromObjToForm(TmpSelectProd);

	if(FormMoveProduct->ButtonAction != TButtonAction::BA_VIEW) {
		EditCount1->SetFocus();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::FormActivate(TObject *Sender)
{
	if(FormMoveProduct->ButtonAction == TButtonAction::BA_ADD) {      // Add items button pressed
		EditNameProdClick(Sender);
	} else {
		EditCount1Change(Sender);
		EditCount1->SelectAll();
    }
}

//---------------------------------------------------------------------------
//    Select product from this form (click on edit field)
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::EditNameProdClick(TObject *Sender)
{
	if(TmpSelectProd->Product != NULL) {
		FormProductList->IndexLastGroupProd = FormProductList->GetIndexFromComboGroup(TmpSelectProd->Product->GroupProd->Name);
		FormProductList->ComboBoxFilter->ItemIndex = FormProductList->IndexLastGroupProd;
		FormProductList->uSelectItemString = TmpSelectProd->Product->Name;
		FormProductList->FindStringInColumn = 2;
	} else {
		EditCount1->Enabled = false;
		EditCount2->Enabled = false;
	}
	FormProductList->CalledObj = TCalledObj::OBJ_EXTERN;
	FormProductList->ShowModal();

	if(FormProductList->SelectedProduct != NULL) {
		if(TmpSelectProd->Product != NULL) {
			TmpSelectProd->Product->CountBalance[TShopUnits::upp[0]] -= TmpSelectProd->Count * iMult;
		}

		TmpSelectProd->Product = FormProductList->SelectedProduct;
		TmpSelectProd->idProduct = TmpSelectProd->Product->id;
		TmpSelectProd->IncomingPrice = TmpSelectProd->Product->PurchaseCash;
		TmpSelectProd->Price = TmpSelectProd->Product->SellingPrice;
		TmpSelectProd->Count = 0;

		LoadFromObjToForm(TmpSelectProd);

		EditCount1->Enabled = true;
		EditCount2->Enabled = true;
		EditCount1->SetFocus();
		EditCount1->SelectAll();
		EditCount1Change(Sender);
	} else if(TmpSelectProd->Product == NULL) {
		PostMessageW(FormSelectProd->Handle, WM_CLOSE, 0, 0);
	}

	if(CheckData()) {
		ButtonSubmit->Enabled = true;
	} else {
		ButtonSubmit->Enabled = false;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::EditCount1Change(TObject *Sender)
{
	if(TmpSelectProd->Product == NULL) {
        return;
    }

	CountInEdit.SetString(EditCount1->Text, EditCount2->Text);
	LabelCashBalance->Caption = (CountInStock + CountInEdit * iMult).StringFormat();

/*
	TPrice TmpPrice;
	switch(FormMoveProduct->TmpMoveProduct->MoveType) {
		case TMoveType::MOV_SALE:
		case TMoveType::MOV_RET:
		case TMoveType::MOV_INC:
			TmpPrice = TmpSelectProd->Product->SellingPrice;
			break;
		case TMoveType::MOV_OUT:
			TmpPrice = TmpSelectProd->Product->PurchaseCash;
			break;
	}
*/
	TPrice TmpPrice = TmpSelectProd->Product->SellingPrice;
	TmpPrice *= CountInEdit;
	TmpPrice.SetOnEdit(EditTotalPrice1, EditTotalPrice2);

	TmpPrice = TmpSelectProd->Product->PurchaseCash;
	TmpPrice *= CountInEdit;

	if(FormShop->Worker->Privilege < TPrivilege::PRV_MANAGER) {
		TmpPrice.SetOnEdit(EditTotalCost1, EditTotalCost2);
	} else {
		EditTotalCost1->Text = TPrice::uHidden;
		EditTotalCost2->Text = TPrice::uHidden;
	}

	if(CheckData()) {
		ButtonSubmit->Enabled = true;
	} else {
		ButtonSubmit->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::LoadFromObjToForm(TSelectProduct *CurSelectProd)
{
	if(CurSelectProd->Product == NULL) {
		ClearFields();
	} else {
		EditCodeProd->Text = CurSelectProd->Product->Code;
		EditNameProd->Text = CurSelectProd->Product->Name;
		LabelUnit->Caption = CurSelectProd->Product->Unit;
		LabelUnit2->Caption = LabelUnit->Caption;

		if(FormShop->Worker->Privilege < TPrivilege::PRV_MANAGER) {
			CurSelectProd->IncomingPrice.SetOnEdit(EditCost1, EditCost2);
		} else {
			EditCost1->Text = TPrice::uHidden;
			EditCost2->Text = TPrice::uHidden;
		}
		CurSelectProd->Price.SetOnEdit(EditSalePrice1, EditSalePrice2);
		CurSelectProd->Product->WholePrice.SetOnEdit(EditWholePrice1, EditWholePrice2);

		CountInEdit = CurSelectProd->Count;
		CountInStock = CurSelectProd->Product->CountBalance[TShopUnits::upp[0]] - CountInEdit * iMult;

		CountInEdit.SetOnEdit(EditCount1, EditCount2, CurSelectProd->Product->WholeUnit);

		DesignInputCount(true, CurSelectProd->Product->WholeUnit);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::SaveAtFormToObject(TSelectProduct *CurSelectProd)
{
	CurSelectProd->SelectDateTime = TDateTime::CurrentDateTime();

	CurSelectProd->Count.SetString(EditCount1->Text, EditCount2->Text);

	CurSelectProd->CalcTotalPrice();

	if(FormMoveProduct->TmpMoveProduct->MoveType == TMoveType::MOV_OUT) {
		CurSelectProd->TotalPrice = CurSelectProd->TotalCostPrice;
	}
}
//---------------------------------------------------------------------------
//               Save Item Select Product
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::ButtonSaveClick(TObject *Sender)
{
	if(!CheckValidProductPrice()) {
		return;
	}

	SaveAtFormToObject(TmpSelectProd);

	int IndexV = FormMoveProduct->TmpMoveProduct->GetIndexInVSelectById(TmpSelectProd->id);

	if(IndexV != -1) {
		FormMoveProduct->TmpMoveProduct->CorrectUnitsBalance(IndexV, iMult);
	}
	int IndexAtomList = FormMoveProduct->MyListView->ipp[FormMoveProduct->MyListView->ItemIndex];
	*(FormMoveProduct->TmpMoveProduct->VSelectedProd[IndexAtomList]) = *TmpSelectProd;

	if(IndexV != -1) {
		FormMoveProduct->TmpMoveProduct->CorrectUnitsBalance(IndexV, -iMult);
	}

	bButtonAddCall = true;
	Close();
}
//---------------------------------------------------------------------------
//               Insert Item Select Product
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::ButtonInsertClick(TObject *Sender)
{
	if(!CheckValidProductPrice()) {
		return;
	}

	SaveAtFormToObject(TmpSelectProd);

	TmpSelectProd->id = TSelectProduct::LastIdDb++;
	FormMoveProduct->TmpMoveProduct->VSelectedProd.push_back(TmpSelectProd);

	int IndexV = FormMoveProduct->TmpMoveProduct->GetIndexInVSelectById(TmpSelectProd->id);

	if(IndexV != -1) {
		FormMoveProduct->TmpMoveProduct->CorrectUnitsBalance(IndexV, -iMult);
	}

	TmpSelectProd = new TSelectProduct();

	bButtonAddCall = true;
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::ButtonCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectProd::EditCount1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN) {
		ButtonSubmit->Click();
    }
}
//---------------------------------------------------------------------------
bool __fastcall TFormSelectProd::CheckData(void)
{
	if(TmpSelectProd->idProduct == -1 || CountInEdit == 0) {
		return false;
	} else {
        return true;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TFormSelectProd::CheckValidProductPrice(void)
{
	if(TmpSelectProd->Product->SellingPrice == 0 || TmpSelectProd->Product->PurchaseCash == 0) {
		Application->MessageBox(wIncorrectPrice[iLang], uCaptionError[iLang]);
		return false;
	} else {
        return true;
    }
}
//---------------------------------------------------------------------------

