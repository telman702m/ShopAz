//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#include <Printers.hpp>
#include <stdio.h>

#pragma hdrstop

#include "Declaration.h"
#include "UnitSale.h"
#include "UnitProductList.h"
#include "Shop.h"
#include "UnitSelectProduct.h"
#include "UnitBuyerList.h"
#include "UnitPrint.h"
#include "UnitShopUnitList.h"
#include "UnitProvisionerList.h"
#include "Provisioner.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitParent"
#pragma link "UnitParent"
#pragma link "UnitParent"
#pragma link "UnitParent"
#pragma link "UnitParent"
#pragma resource "*.dfm"

TFormSale *FormSale;

TLocate LocateStockS = {24, 168, 865, 255};

UnicodeString TFormSale::uButtonCaptions1[6] = {
	L"View", L"Save", L"Sell", L"Take", L"Return", L"Delete"};

UnicodeString TFormSale::uSelectMessage = L"Для выполнения операции необходимо выбрать элемент из списка";
UnicodeString TFormSale::uDeleteMessage = L"Вы уверены? \n Данные будут удалены безвозвратно!";

//---------------------------------------------------------------------------
__fastcall TFormSale::TFormSale(TComponent* Owner)
	: TFormParent(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSale::FormCreate(TObject *Sender)
{
	TmpMoveProduct = new TMoveProduct();

	AtomList = new MyListView(FormSale, TFormShop::ColumnsDataAtom, sizeof(TFormShop::ColumnsDataAtom)/sizeof(TColumnsData), LocateStockS, LS_ATOM);
	AtomList->Parent = FormSale;
}
//---------------------------------------------------------------------------
void __fastcall TFormSale::FormDestroy(TObject *Sender)
{
	delete TmpMoveProduct;
}

//---------------------------------------------------------------------------
void __fastcall TFormSale::DesignForm(void)
{
	//   Assign ToolButton Status
	TToolButton *ToolButtons[] = {/*ToolButtonView,*/ ToolButtonAdd, ToolButtonEdit, ToolButtonDel};

	bool bTmpStatus;
	if(FormShop->ButtonOperat == TButtonAction::BA_VIEW) {
		bTmpStatus = false;
	} else {
		bTmpStatus = true;
	}
	for(unsigned i=0; i < sizeof(ToolButtons)/sizeof(TToolButton*); i++) {
		ToolButtons[i]->Visible = bTmpStatus;
	}
	MemoDescription->Enabled = bTmpStatus;
	ButtonSubmit->Enabled = bTmpStatus;


	//   Assign Edits Status
	TEdit *Edits[] = {EditSourceUnit, EditSourcePerson, EditTargetUnit, EditTargetPerson,
					  EditDiscountPrice1, EditDiscountPrice2, EditDiscountPercent
					 };
	//                          SrUnit SrPers TrUnit TrPers Disc1  Disc2  DsPerc
	bool bEditsStatus[6][7] = {{false, false, false, false, false, false, false},         //  BA_VIEW
							   {true,  true,  true,  true,  true,  true,  true },         //  BA_EDIT
							   {false, false, true,  true,  true,  true,  true },         //  BA_SALE
							   {true,  true,  false, false, true,  true,  true },         //  BA_RETURN
							   {true,  true,  false, false, false, false, false},         //  BA_INCOM
							   {false, false, true,  true,  false, false, false}          //  BA_OUT
							  };
	UnicodeString uCaptionsForm[] = {L"Просмотр операции", L"Редактирование операции",
									 L"Продажа товаров", L"Возврат товаров", L"Приемка товаров", L"Передача товаров"};

	int index;
	switch(FormShop->ButtonOperat) {
		case TButtonAction::BA_VIEW:
			index = 0;
			break;
		case TButtonAction::BA_EDIT:
			switch(TmpMoveProduct->MoveType) {
				case TMoveType::MOV_SALE:
					index = 2;
					break;
				case TMoveType::MOV_RET:
					index = 3;
					break;
				case TMoveType::MOV_INC:
					index = 4;
					break;
				case TMoveType::MOV_OUT:
					index = 5;
					break;
			}
			break;
		case TButtonAction::BA_SALE:
			index = 2;
			break;
		case TButtonAction::BA_RETURN:
			index = 3;
			break;
		case TButtonAction::BA_INCOM:
			index = 4;
			break;
		case TButtonAction::BA_OUT:
			index = 5;
			break;
	}
	for(int i=0; i < 7; i++) {
		Edits[i]->Enabled = bEditsStatus[index][i];
		Caption = uCaptionsForm[index];
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSale::FormShow(TObject *Sender)
{
//	TimerDate->Enabled = true;
	for(unsigned i=0; i < vProdCountKeep.size(); i++) {
		delete vProdCountKeep[i];
	}
	vProdCountKeep.clear();

	bClose = false;
	TmpMoveProduct->Clear();
	ClearFields();

	switch(FormShop->ButtonOperat) {
		case TButtonAction::BA_VIEW:
			TmpMoveProduct->Copy(TMoveProduct::VMoveProduct[FormShop->SaleList->ipp[FormShop->SaleList->ItemIndex]]);
			ButtonSubmit->OnClick = NULL;
			break;
		case TButtonAction::BA_EDIT:
			TmpMoveProduct->Copy(TMoveProduct::VMoveProduct[FormShop->SaleList->ipp[FormShop->SaleList->ItemIndex]]);
			ButtonSubmit->OnClick = ButtonSaveClick;
			break;

		case TButtonAction::BA_SALE:
			TmpMoveProduct->MoveType = TMoveType::MOV_SALE;

			TmpMoveProduct->SourceUnit = FormShop->ShopUnit;
			TmpMoveProduct->SourcePerson = FormShop->Worker;

			TmpMoveProduct->TargetUnit = TShopUnits::Buyer;
			TmpMoveProduct->TargetPerson = TBuyer::Unknow;
			break;

		case TButtonAction::BA_OUT:
			TmpMoveProduct->MoveType = TMoveType::MOV_OUT;

			TmpMoveProduct->SourceUnit = FormShop->ShopUnit;
			TmpMoveProduct->SourcePerson = FormShop->Worker;

			TmpMoveProduct->TargetUnit = TShopUnits::Empty;
			TmpMoveProduct->TargetPerson = TBuyer::Unknow;
			break;

		case TButtonAction::BA_INCOM:
			TmpMoveProduct->MoveType = TMoveType::MOV_INC;

			TmpMoveProduct->SourceUnit = TShopUnits::Provisioner;
			TmpMoveProduct->SourcePerson = TBuyer::Unknow;

			TmpMoveProduct->TargetUnit = FormShop->ShopUnit;
			TmpMoveProduct->TargetPerson = FormShop->Worker;
			break;

		case TButtonAction::BA_RETURN:
			TmpMoveProduct->MoveType = TMoveType::MOV_RET;

			TmpMoveProduct->SourceUnit = TShopUnits::Buyer;
			TmpMoveProduct->SourcePerson = TBuyer::Unknow;

			TmpMoveProduct->TargetUnit = FormShop->ShopUnit;
			TmpMoveProduct->TargetPerson = FormShop->Worker;
			break;

		default:
			ShowMessage(L"Error TButtonAction in UnitSale");
			return;
	}

	if(!(FormShop->ButtonOperat == TButtonAction::BA_VIEW || FormShop->ButtonOperat == TButtonAction::BA_EDIT)) {
		TmpMoveProduct->idSource = TmpMoveProduct->SourceUnit->id;
		TmpMoveProduct->idSourcePerson = TmpMoveProduct->SourcePerson->id;

		if(TmpMoveProduct->MoveType != TMoveType::MOV_OUT) {
			TmpMoveProduct->idTarget = TmpMoveProduct->TargetUnit->id;
			TmpMoveProduct->idTargetPerson = TmpMoveProduct->TargetPerson->id;
		}
		ButtonSubmit->OnClick = ButtonInsertClick;
	}

	LoadFromObjectToForm(TmpMoveProduct);

	DesignForm();

	AtomList->FillList();
}

//---------------------------------------------------------------------------
void __fastcall TFormSale::FormClose(TObject *Sender, TCloseAction &Action)
{
	TimerDate->Enabled = false;

	if(!bClose) {
		for(int i = vProdCountKeep.size() - 1; i >= 0; i--) {
			vProdCountKeep[i]->Product->CashBalance = vProdCountKeep[i]->BalanceCount;
		}
	}
}

//---------------------------------------------------------------------------
//      	Button Save
//---------------------------------------------------------------------------
void __fastcall TFormSale::ButtonSaveClick(TObject *Sender)
{
	SaveAtFormToObject(TmpMoveProduct);
	if(!TmpMoveProduct->CheckCorrect()) {
		return;
	}
	TmpMoveProduct->SaveAtObjectToDb(FormShop->MyQuery1);

	for(int i=0; i < (int)TmpMoveProduct->VSelectedProd.size(); i++) {
		if(TmpMoveProduct->VSelectedProd[i]->bInsToDB) {
			TmpMoveProduct->VSelectedProd[i]->idSale = TmpMoveProduct->id;      // set Sale id for Selected Product
			TmpMoveProduct->VSelectedProd[i]->InsertAtObjectToDb(FormShop->MyQuery1);
			TmpMoveProduct->VSelectedProd[i]->bInsToDB = false;  		  // reset flag
		} else {
			TmpMoveProduct->VSelectedProd[i]->SaveAtObjectToDb(FormShop->MyQuery1);
		}
    }

	TMoveProduct::VMoveProduct[FormShop->SaleList->ipp[FormShop->SaleList->ItemIndex]]->Copy(TmpMoveProduct);
	FormShop->SaleList->FillList();

	bClose = true;
	Close();
}
//---------------------------------------------------------------------------
//      	Button Sell
//---------------------------------------------------------------------------
void __fastcall TFormSale::ButtonInsertClick(TObject *Sender)
{
	SaveAtFormToObject(TmpMoveProduct);
	if(!TmpMoveProduct->CheckCorrect()) {
		return;
	}
	TmpMoveProduct->InsertAtObjectToDb(FormShop->MyQuery1);

	for(unsigned i=0; i < TmpMoveProduct->VSelectedProd.size(); i++) {
		TmpMoveProduct->VSelectedProd[i]->idSale = TmpMoveProduct->id;      // set Sale id for Selected Product
		TmpMoveProduct->VSelectedProd[i]->InsertAtObjectToDb(FormShop->MyQuery1);
		TmpMoveProduct->VSelectedProd[i]->bInsToDB = false;  		  // reset flag
	}

	TMoveProduct::VMoveProduct.push_back(TmpMoveProduct);
	TmpMoveProduct = new TMoveProduct();

	FormShop->SaleList->FillList();

	bClose = true;
	Close();
}


//---------------------------------------------------------------------------
//  ********     Buttons, whath location on top form  *******
//---------------------------------------------------------------------------
void TFormSale::ToolButtonsClickAction(TButtonAction bAction)
{
	if((AtomList->ItemIndex == -1) && (bAction != TButtonAction::BA_ADD)) {
		Application->MessageBox(uSelectMessage.w_str(), TFormShop::uWarning.w_str(), MB_OK);
		return;
	}

	FormSelectProd->ShowModal();

	AtomList->FillList();
}
//---------------------------------------------------------------------------
void TFormSale::DeleteItem(void)
{
	if(AtomList->ItemIndex != -1) {

		if(Application->MessageBox(uDeleteMessage.w_str(), TFormShop::uAttention.w_str(), MB_YESNO) == IDYES) {

			TmpMoveProduct->VSelectedProd[AtomList->ipp[AtomList->ItemIndex]]->DeleteObjectFromDb(FormShop->MyQuery1);

			std::vector <TSelectProduct*>::iterator it2 = TmpMoveProduct->VSelectedProd.begin() + AtomList->ItemIndex;
			TmpMoveProduct->VSelectedProd.erase(it2);

			FormSelectProd->TmpSelectProd = TmpMoveProduct->VSelectedProd[AtomList->ipp[AtomList->ItemIndex]];

			FormSelectProd->KeepProductCount();
			int Mult = TmpMoveProduct->GetBalanceMult();
			FormSelectProd->TmpSelectProd->Product->CashBalance -= FormSelectProd->TmpSelectProd->Count * Mult;

			int index = TSelectProduct::GetArrayIndexById(TmpMoveProduct->VSelectedProd[AtomList->ipp[AtomList->ItemIndex]]->id);
			std::vector <TSelectProduct*>::iterator it = TSelectProduct::VSelectProduct.begin() + index;
			TSelectProduct::VSelectProduct.erase(it);

			AtomList->DeleteSelected();
			AtomList->FillList();
		}
	} else {
		Application->MessageBox(uSelectMessage.w_str(), TFormShop::uWarning.w_str(), MB_OK);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSale::TimerDateTimer(TObject *Sender)
{
//	DateTimePickerSale->DateTime = TDateTime::CurrentDateTime();

}

//---------------------------------------------------------------------------
void __fastcall TFormSale::EditDiscountPrice1Change(TObject *Sender)
{
	if(EditDiscountPercent->Focused()) {
		return;
	}
	TmpMoveProduct->Discount.GetFromTEdit(EditDiscountPrice1, EditDiscountPrice2);
	TmpMoveProduct->CalcTotalPrice();
	TmpMoveProduct->TotalPrice.SetOnEdit(EditBuyerPayment1, EditBuyerPayment2);

	TPrice PriceAll = TmpMoveProduct->TotalPrice + TmpMoveProduct->Discount;

	UnicodeString uTmp;
	uTmp.sprintf(L"%1.2f", PriceAll.GetPercent(TmpMoveProduct->Discount));
	int PosDot = uTmp.Pos(L".");

	wchar_t szSep[8];
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, szSep, 8);
	UnicodeString uDecimelSeparator = szSep;

	uTmp.Delete(PosDot,1);
	uTmp.Insert(uDecimelSeparator, PosDot);

	EditDiscountPercent->Text = uTmp;

}
//---------------------------------------------------------------------------
void __fastcall TFormSale::EditDiscountPercentChange(TObject *Sender)
{
	if(EditDiscountPrice1->Focused() || EditDiscountPrice2->Focused()) {
		return;
	}
	TmpMoveProduct->Discount.Zero();
	TmpMoveProduct->CalcTotalPrice();

	double dPerc;

	if(EditDiscountPercent->Text != L"") {
		UnicodeString uPerc = EditDiscountPercent->Text;

		int iPosCursor = EditDiscountPercent->SelStart;
		try {
			dPerc = uPerc.ToDouble();
		} catch(...) {
			EditDiscountPercent->Text = uEditPercent;
			EditDiscountPercent->SelStart = iPosCursor - 1;
			return;
		}
		if(dPerc < 0. || dPerc > 100.) {
			EditDiscountPercent->Text = uEditPercent;
			EditDiscountPercent->SelStart = iPosCursor - 1;
			return;
		}
	} else {
        dPerc = 0.;
    }

	TmpMoveProduct->Discount = TmpMoveProduct->TotalPrice.SetPercent(dPerc);
	TmpMoveProduct->CalcTotalPrice();

	TmpMoveProduct->TotalPrice.SetOnEdit(EditBuyerPayment1, EditBuyerPayment2);
	TmpMoveProduct->Discount.SetOnEdit(EditDiscountPrice1, EditDiscountPrice2);
}

//---------------------------------------------------------------------------
void __fastcall TFormSale::EditSourceUnitClick(TObject *Sender)
{
	switch(TmpMoveProduct->MoveType) {
		case TMoveType::MOV_INC:
			FormProvisionerList->CalledObj = TCalledObj::OBJ_EXTERN;
			FormProvisionerList->SelectedProvisioner = (TProvisioner*)TmpMoveProduct->SourcePerson;
			FormProvisionerList->ShowModal();

			TmpMoveProduct->SourceUnit = TShopUnits::Provisioner;
			TmpMoveProduct->idSource = TmpMoveProduct->SourceUnit->id;

			TmpMoveProduct->SourcePerson = FormProvisionerList->SelectedProvisioner;
			TmpMoveProduct->idSourcePerson = TmpMoveProduct->SourcePerson->id;

			EditSourceUnit->Text = FormProvisionerList->SelectedProvisioner->Organization;
			EditSourcePerson->Text = FormProvisionerList->SelectedProvisioner->SumName;
			break;

		case TMoveType::MOV_RET:
			FormBuyerList->CalledObj = TCalledObj::OBJ_EXTERN;
			FormBuyerList->SelectedBuyer = (TBuyer*)TmpMoveProduct->SourcePerson;
			FormBuyerList->ShowModal();

			TmpMoveProduct->SourceUnit = TShopUnits::Buyer;
			TmpMoveProduct->idSource = TmpMoveProduct->SourceUnit->id;

			TmpMoveProduct->SourcePerson = FormBuyerList->SelectedBuyer;
			TmpMoveProduct->idSourcePerson = TmpMoveProduct->SourcePerson->id;

			EditSourceUnit->Text = FormBuyerList->SelectedBuyer->Organization;
			EditSourcePerson->Text = FormBuyerList->SelectedBuyer->SumName;
			break;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormSale::EditTargetUnitClick(TObject *Sender)
{
	switch(TmpMoveProduct->MoveType) {
		case TMoveType::MOV_SALE:
			FormBuyerList->CalledObj = TCalledObj::OBJ_EXTERN;
			FormBuyerList->SelectedBuyer = (TBuyer*)TmpMoveProduct->TargetPerson;
			FormBuyerList->ShowModal();

			TmpMoveProduct->TargetUnit = TShopUnits::Buyer;
			TmpMoveProduct->idTarget = TmpMoveProduct->TargetUnit->id;

			TmpMoveProduct->TargetPerson = FormBuyerList->SelectedBuyer;
			TmpMoveProduct->idTargetPerson = TmpMoveProduct->TargetPerson->id;

			EditTargetUnit->Text = FormBuyerList->SelectedBuyer->Organization;
			EditTargetPerson->Text = FormBuyerList->SelectedBuyer->SumName;
			break;

		case TMoveType::MOV_OUT:
			FormShopUnitsList->CalledObj = TCalledObj::OBJ_EXTERN;
			FormShopUnitsList->SelectedShopUnit = TmpMoveProduct->TargetUnit;
			FormShopUnitsList->ShowModal();

			TmpMoveProduct->TargetUnit = FormShopUnitsList->SelectedShopUnit;
			TmpMoveProduct->idTarget = TmpMoveProduct->TargetUnit->id;

			TmpMoveProduct->TargetPerson = TBuyer::Empty;
			TmpMoveProduct->idTargetPerson = TmpMoveProduct->TargetPerson->id;

			EditTargetUnit->Text = TmpMoveProduct->TargetUnit->Name;
			EditTargetPerson->Text = TBuyer::Empty->Name;
			break;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormSale::DateTimePickerSaleChange(TObject *Sender)
{
//	TimerDate->Enabled = false;
}


//---------------------------------------------------------------------------
//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//---------------------------------------------------------------------------
void __fastcall TFormSale::LoadFromObjectToForm(TMoveProduct *CurMoveProduct)
{
	LabelDate->Caption = CurMoveProduct->DateTime.FormatString(L"dd-mm-yyyy ");
	EditSourceUnit->Text = CurMoveProduct->SourceUnit->Name;
	EditSourcePerson->Text = CurMoveProduct->SourcePerson->SumName;
	EditTargetUnit->Text = CurMoveProduct->TargetUnit->Name;
	EditTargetPerson->Text = CurMoveProduct->TargetPerson->SumName;

	CurMoveProduct->Discount.SetOnEdit(EditDiscountPrice1, EditDiscountPrice2);
	MemoDescription->Text = CurMoveProduct->Description;

//	AtomList->FillList();

	TmpMoveProduct->CalcTotalPrice();
}

//---------------------------------------------------------------------------
void __fastcall TFormSale::SaveAtFormToObject(TMoveProduct *CurMoveProduct)
{
	CurMoveProduct->DateTime = TDateTime::CurrentDateTime();

	CurMoveProduct->Description = MemoDescription->Text;

	CurMoveProduct->Discount.GetFromTEdit(EditDiscountPrice1, EditDiscountPrice2);
	CurMoveProduct->CalcTotalPrice();
}


//---------------------------------------------------------------------------
void __fastcall TFormSale::ClearFields(void)
{
//	DateTimePickerSale->DateTime = TDateTime::CurrentDateTime();

//	EditDate->Text = TDateTime::CurrentDateTime().FormatString(L"dd mmmm yyyy    hh:nn");
//	EditBuyer->Text = L"";
	EditDiscountPrice1->Text = L"";
	EditDiscountPrice2->Text = L"";
	EditDiscountPercent->Text = L"";
	MemoDescription->Text = L"";
	EditBuyerPayment1->Text = L"";
	EditBuyerPayment2->Text = L"";

	AtomList->Clear();
}


//---------------------------------------------------------------------------
void __fastcall TFormSale::EditDiscountPercentKeyPress(TObject *Sender, wchar_t &Key)
{
	uEditPercent = EditDiscountPercent->Text;

//	UnicodeString uKey = Key;
//	if(uKey==L"0"||uKey==L"1"||uKey==L"2"||uKey==L"3"||uKey==L"4"||uKey==L"5"||
//		 uKey==L"6"||uKey==L"7"||uKey==L"8"||uKey==L"9"||uKey==L"."||uKey==L",") {
//		bValidPercSymb = true;
//	} else {
//		bValidPercSymb = false;
//	}

}
//---------------------------------------------------------------------------
void __fastcall TFormSale::EditDiscountPercentKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
//	if(!bValidPercSymb) {
//		EditDiscountPercent->Text = uEditPercent;
//	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSale::ButtonCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

