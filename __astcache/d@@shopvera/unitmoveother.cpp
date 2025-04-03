//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitMoveOther.h"
#include "Shop.h"
#include "MyListView.h"
#include "UnitBuyerList.h"
#include "UnitProvisionerList.h"
#include "Provisioner.h"
#include "SelectProduct.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wCorrectField1OtherMessage[] = {
	L"Для неизвестного покупателя оплата долга невозможно!",
	L"Naməlum alıcı üçün borc qaytarmaq mümkün deyil!"
};
TLabelCaption LabelCaptionsMoveOther[] = {
	{{L"Плательщик",		L"Ödəyəci"},			NULL},
	{{L"Имя",   			L"Adı"},				NULL},
	{{L"Получатель",		L"Alıcı"},				NULL},
	{{L"Имя",   			L"Adı"},				NULL},
	{{L"Дата",				L"Tarix"},				NULL},
	{{L"Вносимая сумма",	L"Ödənilən məbləğ"},	NULL},
	{{L"манат",				L"manat"},				NULL},
	{{L"копеек",   			L"qəpik"},				NULL},
	{{L"Примечание",		L"Qeyd"},				NULL}
};
TButtonCaption ButtonCaptionMoveOther[] = {
	{{L"Выполнить",	L"Əməl etmək"},	NULL},
	{{L"Отмена",	L"Cancel"},		NULL}
};

TFormMoveOther *FormMoveOther;
//---------------------------------------------------------------------------
__fastcall TFormMoveOther::TFormMoveOther(TComponent* Owner)
	: TFormEsc(Owner)
{
	SizeLabelsData = sizeof(LabelCaptionsMoveOther) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionsMoveOther;

	SizeButtonsData = sizeof(ButtonCaptionMoveOther) / sizeof(TButtonCaption);
	ButtonsCaption = ButtonCaptionMoveOther;
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::FormCreate(TObject *Sender)
{
	LabelsCaption[0].Label = LabelSourceUnit;
	LabelsCaption[1].Label = LabelSourcePerson;
	LabelsCaption[2].Label = LabelTargetUnit;
	LabelsCaption[3].Label = LabelTargetPerson;
	LabelsCaption[4].Label = LabeluDate;
	LabelsCaption[5].Label = LabelActualPayment;
	LabelsCaption[6].Label = LabelPrice1;
	LabelsCaption[7].Label = LabelCent1;
	LabelsCaption[8].Label = LabelNote;

	ButtonsCaption[0].Button = ButtonSubmit;
	ButtonsCaption[1].Button = ButtonCancel;

	SetLanguage();

	TmpMoveProduct = new TMoveProduct();
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::FormDestroy(TObject *Sender)
{
	delete TmpMoveProduct;
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::DesignForm(void)
{
	if(FormShop->ButtonOperat == TButtonAction::BA_VIEW) {
		MemoDescription->Enabled = false;
		ButtonSubmit->Enabled = false;
	} else {
		MemoDescription->Enabled = true;
		ButtonSubmit->Enabled = true;
	}

	//   Assign Edits Status
	TEdit *Edits[] = {EditSourceUnit, EditSourcePerson,
					  EditTargetUnit, EditTargetPerson,
					  EditActualPayment1, EditActualPayment2};
	//                          SrUnit SrPers TrUnit TrPers AcPay1 AcPay2
	bool bEditsStatus[5][6] = {{false, false, false, false, false, false},         //  BA_VIEW
							   {true,  true,  true,  true,  true,  true},          //  BA_EDIT
							   {true,  true,  false, false, true,  true},          //  BA_DEBT
							   {false, false, false, false, true,  true},          //  BA_EXP
							   {false, false, true,  true,  true,  true}           //  BA_DEBT_PROVIS
							  };
	const wchar_t *wCaptionsForm[][2] = {
		{L"Просмотр операции",				L"Əməliyyata baxış"},
		{L"Редактирование операции",		L"Əməliyyatın redaktəsi"},
		{L"Погашение долга покупателя",		L"Alıcının borcunun ödənişi"},
		{L"Прочие затраты магазина",		L"Mağazanın digər xərcləri"},
		{L"Погашение долга поставщикам",	L"Təcizatçının borcunun ödənişi"}
	};

	int index;
	switch(FormShop->ButtonOperat) {
		case TButtonAction::BA_VIEW:
			index = 0;
			break;
		case TButtonAction::BA_EDIT:
			if(TmpMoveProduct->MoveType == TMoveType::MOV_EXP) {
				index = 3;
			} else {
				index = 1;
			}
			break;
		case TButtonAction::BA_DEBT:
			index = 2;
			break;
		case TButtonAction::BA_EXP:
			index = 3;
			break;
		case TButtonAction::BA_DEBT_PROVIS:
			index = 4;
			break;
		default:
            break;
	}
	for(unsigned i=0; i < sizeof(Edits)/sizeof(TEdit*); i++) {
		Edits[i]->Enabled = bEditsStatus[index][i];
	}
	Caption = wCaptionsForm[index][iLang];
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::FormShow(TObject *Sender)
{
	bChanged = false;

	TmpMoveProduct->Clear();

	ClearFields();
	TimerDate->Enabled = true;

	switch(FormShop->ButtonOperat) {
		case TButtonAction::BA_VIEW:
			*TmpMoveProduct = *(TObjectManager<TMoveProduct>::GetList()[FormShop->MoveList->ipp[FormShop->MoveList->ItemIndex]]);
			ButtonSubmit->OnClick = NULL;
			ButtonSubmit->Enabled = false;
			TimerDate->Enabled = false;
			break;
		case TButtonAction::BA_EDIT:
			*TmpMoveProduct = *(TObjectManager<TMoveProduct>::GetList()[FormShop->MoveList->ipp[FormShop->MoveList->ItemIndex]]);
			ButtonSubmit->OnClick = ButtonSaveClick;
			ButtonSubmit->Enabled = true;
			TimerDate->Enabled = false;
			break;
		case TButtonAction::BA_DEBT:  // source - Buyer    target - Shop
			TmpMoveProduct->MoveType = TMoveType::MOV_DEBT;
			TmpMoveProduct->SourceUnit = TShopUnits::Buyer;
			TmpMoveProduct->SourcePerson = TBuyer::Unknow;
			TmpMoveProduct->idTarget = FormShop->ShopUnit->id;
			TmpMoveProduct->idTargetPerson = FormShop->Worker->id;
			TmpMoveProduct->TargetUnit = FormShop->ShopUnit;
			TmpMoveProduct->TargetPerson = FormShop->Worker;

			ButtonSubmit->OnClick = ButtonInsertClick;
			ButtonSubmit->Enabled = true;
			TimerDate->Enabled = true;

			EditSourceUnit->OnClick = EditSourceUnitClick;
			EditSourcePerson->OnClick = EditSourceUnitClick;
			EditTargetUnit->OnClick = NULL;
			EditTargetPerson->OnClick = NULL;
			break;
		case TButtonAction::BA_EXP:
			TmpMoveProduct->MoveType = TMoveType::MOV_EXP;
			TmpMoveProduct->SourceUnit = FormShop->ShopUnit;
			TmpMoveProduct->SourcePerson = FormShop->Worker;
			TmpMoveProduct->idSource = FormShop->ShopUnit->id;
			TmpMoveProduct->idSourcePerson = FormShop->Worker->id;
			TmpMoveProduct->TargetUnit = TShopUnits::Expenses;
			TmpMoveProduct->TargetPerson = TBuyer::Unknow;

			ButtonSubmit->OnClick = ButtonInsertClick;
			ButtonSubmit->Enabled = true;
			TimerDate->Enabled = true;

			EditSourceUnit->OnClick = NULL;
			EditSourcePerson->OnClick = NULL;
			EditTargetUnit->OnClick = NULL;
			EditTargetPerson->OnClick = NULL;
			break;
		case TButtonAction::BA_DEBT_PROVIS:  // source - Shop    target - Provisioner
			TmpMoveProduct->MoveType = TMoveType::MOV_DEBT_PROVIS;
			TmpMoveProduct->idSource = FormShop->ShopUnit->id;
			TmpMoveProduct->idSourcePerson = FormShop->Worker->id;
			TmpMoveProduct->SourceUnit = FormShop->ShopUnit;
			TmpMoveProduct->SourcePerson = FormShop->Worker;
			TmpMoveProduct->TargetUnit = TShopUnits::Provisioner;
			TmpMoveProduct->TargetPerson = TProvisioner::Unknow;

			ButtonSubmit->OnClick = ButtonInsertClick;
			ButtonSubmit->Enabled = true;
			TimerDate->Enabled = true;

			EditSourceUnit->OnClick = NULL;
			EditSourcePerson->OnClick = NULL;
			EditTargetUnit->OnClick = EditSourceUnitClick;
			EditTargetPerson->OnClick = EditSourceUnitClick;
			break;
		default:
			ShowMessage(L"Error TButtonAction in UnitSale");
			return;
	}

	LoadFromObjectToForm(TmpMoveProduct);

	DesignForm();

	bChanged = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::FormClose(TObject *Sender, TCloseAction &Action)
{
	TimerDate->Enabled = false;

	if(bChanged) {
		if(Application->MessageBox(wSaveChangesMessage[iLang], uCaptionWarning[iLang], MB_YESNO) == IDYES) {
			ButtonSubmit->Click();
		} else {
			// calc Total Price and balance
			TMoveProduct::CalcUnitsBalance();
			TMoveProduct::CalcDebts();
		}
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::LoadFromObjectToForm(TMoveProduct *CurMoveProduct)
{
	LabelDate->Caption = CurMoveProduct->DateTime.FormatString(wDateTimeFormat);
	EditSourceUnit->Text = CurMoveProduct->SourceUnit->Name;
	EditSourcePerson->Text = CurMoveProduct->SourcePerson->SumName;
	EditTargetUnit->Text = CurMoveProduct->TargetUnit->Name;
	EditTargetPerson->Text = CurMoveProduct->TargetPerson->SumName;
	CurMoveProduct->ActualPayment.SetOnEdit(EditActualPayment1, EditActualPayment2);
	MemoDescription->Text = CurMoveProduct->Description;

	CurMoveProduct->CalcTotalPrice();
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::SaveAtFormToObject(TMoveProduct *CurMoveProduct, bool bDate)
{
	if(bDate) {
		CurMoveProduct->DateTime = TDateTime::CurrentDateTime();
	}

	CurMoveProduct->Description = MemoDescription->Text;
	CurMoveProduct->ActualPayment.GetFromTEdit(EditActualPayment1, EditActualPayment2);

	CurMoveProduct->CalcTotalPrice();
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::ClearFields(void)
{
	EditSourceUnit->Text = L"";
	EditSourcePerson->Text = L"";
	EditTargetUnit->Text = L"";
	EditTargetPerson->Text = L"";
	MemoDescription->Text = L"";
	EditActualPayment1->Text = L"";
	EditActualPayment2->Text = L"";
}
//---------------------------------------------------------------------------
bool __fastcall TFormMoveOther::CheckCorrectFields(void)
{
	if(TmpMoveProduct->SourcePerson == TBuyer::Unknow) {
		Application->MessageBox(wCorrectField1OtherMessage[iLang], uCaptionWarning[iLang], MB_OK);
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::ButtonSaveClick(TObject *Sender)
{
	if(!CheckCorrectFields()) {
		return;
	}

	SaveAtFormToObject(TmpMoveProduct, false);
	TmpMoveProduct->SaveAtObjectToDb(FormShop->FDQuery1);

//	*(TObjectManager<TMoveProduct>::GetList()[FormShop->MoveList->ipp[FormShop->MoveList->ItemIndex]]) = *TmpMoveProduct;

	// calc Total Price and balance
//	TMoveProduct::CalcUnitsBalance();
	TMoveProduct::CalcDebts();

    FormBuyerList->bListUpdate = true;
	FormProvisionerList->bListUpdate = true;

	TmpMoveProduct = new TMoveProduct();

	FormShop->MoveList->FillList();

	bChanged = false;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::ButtonInsertClick(TObject *Sender)
{
	if(!CheckCorrectFields()) {
		return;
	}

	SaveAtFormToObject(TmpMoveProduct, true);
	TmpMoveProduct->InsertAtObjectToDb(FormShop->FDQuery1);

//	TObjectManager<TMoveProduct>::GetList().push_back(TmpMoveProduct);

	// calc Total Price and balance
//	TMoveProduct::CalcUnitsBalance();
	TMoveProduct::CalcDebts();

/*	switch(TmpMoveProduct->MoveType) {
		case TMoveType::MOV_DEBT:
			FormBuyerList->bListUpdate = true;
		case TMoveType::MOV_EXP:
			break;
		case TMoveType::MOV_DEBT_PROVIS:
			FormProvisionerList->bListUpdate = true;
			break;
	} */
	FormBuyerList->bListUpdate = true;
	FormProvisionerList->bListUpdate = true;

	TmpMoveProduct = new TMoveProduct();

	FormShop->MoveList->FillList();

	bChanged = false;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::EditSourceUnitClick(TObject *Sender)
{
	switch(TmpMoveProduct->MoveType) {
		case TMoveType::MOV_DEBT:
			FormBuyerList->CalledObj = TCalledObj::OBJ_EXTERN;
			FormBuyerList->SelectedBuyer = (TBuyer*)TmpMoveProduct->SourcePerson;
			FormBuyerList->ShowModal();

			TmpMoveProduct->SourceUnit = TShopUnits::Buyer;
			TmpMoveProduct->idSource = TmpMoveProduct->SourceUnit->id;

			TmpMoveProduct->SourcePerson = FormBuyerList->SelectedBuyer;
			TmpMoveProduct->idSourcePerson = TmpMoveProduct->SourcePerson->id;

			EditSourceUnit->Text = ((TBuyer*)TmpMoveProduct->SourcePerson)->Organization;
			EditSourcePerson->Text = TmpMoveProduct->SourcePerson->SumName;
			break;
		case TMoveType::MOV_EXP:
			break;
		case TMoveType::MOV_DEBT_PROVIS:
			FormProvisionerList->CalledObj = TCalledObj::OBJ_EXTERN;
			FormProvisionerList->SelectedProvisioner = (TProvisioner*)TmpMoveProduct->SourcePerson;
			FormProvisionerList->ShowModal();

			TmpMoveProduct->TargetUnit = TShopUnits::Provisioner;
			TmpMoveProduct->idTarget = TmpMoveProduct->TargetUnit->id;

			TmpMoveProduct->TargetPerson = FormProvisionerList->SelectedProvisioner;
			TmpMoveProduct->idTargetPerson = TmpMoveProduct->TargetPerson->id;

			EditTargetUnit->Text = ((TProvisioner*)TmpMoveProduct->TargetPerson)->Organization;
			EditTargetPerson->Text = TmpMoveProduct->TargetPerson->SumName;
			break;
		default:
			return;
	}

	bChanged = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::TimerDateTimer(TObject *Sender)
{
	LabelDate->Caption = TDateTime::CurrentDateTime().FormatString(wDateTimeFormat);
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::ButtonCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveOther::EditActualPayment1Change(TObject *Sender)
{
	bChanged = true;
}
//---------------------------------------------------------------------------

