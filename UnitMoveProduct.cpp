//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#include <stdio.h>

#pragma hdrstop

#include "Declaration.h"
#include "UnitMoveProduct.h"
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
#pragma resource "*.dfm"


const wchar_t *wCorrectField1Message[] = {
	L"Для неизвестного покупателя не может быть сформирован долг!",
	L"Naməlum alıcı üçün borc yaratmaq mümkün deyil!"
};
const wchar_t *wCorrectField2Message[] = {
	L"Для неизвестного поставщика не может быть сформирован долг!",
	L"Naməlum təcizatçı üçün borc yaratmaq mümkün deyil!"
};
const wchar_t *wSaveChangesMessage[] = {
	L"Данные текущей операции не были сохранены!\nСохранить?",
	L"Cari əməliyyətın verilənləri yaddaşda saxlanılmayıb!\nYaddaşda saxlamaq?"
};
TColumnsData ColumnsAtomMove[] = {
	{{L"Дата",				L"Tarix"},		89, 	taCenter,		true, 	false},
	{{L"Код товара",		L"Malın kodu"},	80,		taLeftJustify, 	true, 	false},
	{{L"Название товара",	L"Malın adı"},	184,	taLeftJustify, 	true, 	false},
	{{L"Ед.изм.",			L"Ölçü"},		59, 	taCenter, 		true, 	false},
	{{L"Стоимость",			L"Dəyəri"},		60, 	taRightJustify, false, 	false},
	{{L"Цена",				L"Qiymət"},		60, 	taRightJustify, true, 	false},
	{{L"Кол-во",			L"Miqdarı"},	60, 	taRightJustify, true, 	false},
	{{L"Сумм.Стоим.",		L"Üm.Dəyəri"},	67, 	taRightJustify, false, 	false},
	{{L"Сумма",				L"Məbləğ"},		67, 	taRightJustify, true, 	false}
};
TLabelCaption LabelCaptionMove[] = {
	{{L"Отправитель",			L"İxracçı"},		NULL},
	{{L"Имя",   				L"Adı"},			NULL},
	{{L"Получатель",			L"İdxalçı"},		NULL},
	{{L"Имя",   				L"Adı"},			NULL},
	{{L"Дата",					L"Tarix"},			NULL},
	{{L"№ чека",				L"Qaimə №"},		NULL},
	{{L"Общая сумма",			L"Ümumi məbləğ"},	NULL},
	{{L"манат",					L"manat"},			NULL},
	{{L"копеек",   				L"qəpik"},			NULL},
	{{L"Скидка",   				L"Güzəşt"},			NULL},
	{{L"манат",					L"manat"},			NULL},
	{{L"копеек",				L"qəpik"},			NULL},
	{{L"Сумма к оплате",		L"Ödəniş məbləği"},	NULL},
	{{L"манат",					L"manat"},			NULL},
	{{L"копеек",   				L"qəpik"},			NULL},
	{{L"Фактическая оплата",	L"Faktiki ödəniş"},	NULL},
	{{L"манат",					L"manat"},			NULL},
	{{L"копеек",   				L"qəpik"},			NULL},
	{{L"Оставшийся долг",		L"Qalan borc"},		NULL},
	{{L"манат",					L"manat"},			NULL},
	{{L"копеек",   				L"qəpik"},			NULL},
	{{L"Примечание",			L"Qeyd"},			NULL}
};
TButtonCaption ButtonCaptionMove[] = {
	{{L"Выполнить",	L"Əməl etmək"},	NULL},
	{{L"Отмена",	L"Cancel"},		NULL}
};

TFormMoveProduct *FormMoveProduct;

//---------------------------------------------------------------------------
__fastcall TFormMoveProduct::TFormMoveProduct(TComponent* Owner)
	: TFormParent(Owner)
{
	wFormCaptions[0] = L"";
	wFormCaptions[1] = L"";

	LocateMyListView.Left = 20;
	LocateMyListView.Top = 168;
	LocateMyListView.Width = 1120;
	LocateMyListView.Height = 255;

	SizeColumnsData = sizeof(ColumnsAtomMove)/sizeof(TColumnsData);
	ColumnsData = ColumnsAtomMove;

	SizeLabelsData = sizeof(LabelCaptionMove) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionMove;

	SizeButtonsData = sizeof(ButtonCaptionMove) / sizeof(TButtonCaption);
	ButtonsCaption = ButtonCaptionMove;
}

//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::FormCreate(TObject *Sender)
{
	bChangeFromAtomList = false;
	bExternLoad = false;

	TmpMoveProduct = new TMoveProduct();

	MyListView = new TMyListView(FormMoveProduct, FormMoveProduct, ColumnsData, SizeColumnsData, LocateMyListView, TYPE_LIST::LS_ATOM, false);
	MyListView->Name = L"AtomListInMove";

	LabelsCaption[0].Label = LabelSourceUnit;
	LabelsCaption[1].Label = LabelSourcePerson;
	LabelsCaption[2].Label = LabelTargetUnit;
	LabelsCaption[3].Label = LabelTargetPerson;
	LabelsCaption[4].Label = LabeluDate;
	LabelsCaption[5].Label = LabeluCashNumb;
	LabelsCaption[6].Label = LabelTotalPayment;
	LabelsCaption[7].Label = LabelPrice3;
	LabelsCaption[8].Label = LabelCent3;
	LabelsCaption[9].Label = LabelDiscount;
	LabelsCaption[10].Label = LabelPriceL;
	LabelsCaption[11].Label = LabelCentL;
	LabelsCaption[12].Label = LabelSum;
	LabelsCaption[13].Label = LabelPriceR;
	LabelsCaption[14].Label = LabelCentR;
	LabelsCaption[15].Label = LabelActualPayment;
	LabelsCaption[16].Label = LabelPrice1;
	LabelsCaption[17].Label = LabelCent1;
	LabelsCaption[18].Label = LabelDebt;
	LabelsCaption[19].Label = LabelPrice2;
	LabelsCaption[20].Label = LabelCent2;
	LabelsCaption[21].Label = LabelNote;

	ButtonsCaption[0].Button = ButtonSubmit;
	ButtonsCaption[1].Button = ButtonCancel;

	SetLanguage();
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::FormDestroy(TObject *Sender)
{
	delete TmpMoveProduct;
}

//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::DesignForm(void)
{
	//   Assign ToolButton Status
	DropVisibleStatus();

	bool bTmpStatus;
	if(FormShop->ButtonOperat == TButtonAction::BA_VIEW) {
		bTmpStatus = false;
	} else {
		bTmpStatus = true;
	}

	ToolBars[ToolBarStat::TS_VIEW].Visible = bTmpStatus;
	ToolBars[ToolBarStat::TS_EDIT].Visible = bTmpStatus;
	ToolBars[ToolBarStat::TS_ADD].Visible = bTmpStatus;
	ToolBars[ToolBarStat::TS_DEL].Visible = bTmpStatus;
//	ToolBars[ToolBarStat::TS_SEP1].Visible = bTmpStatus;

	MemoDescription->Enabled = bTmpStatus;
	ButtonSubmit->Enabled = bTmpStatus;


	//   Assign Edits Status
	TEdit *Edits[] = {EditSourceUnit, EditSourcePerson, EditTargetUnit, EditTargetPerson,
					  EditDiscountPrice1, EditDiscountPrice2, EditDiscountPercent,
					  EditActualPayment1, EditActualPayment2
					 };
	//                          SrUnit SrPers TrUnit TrPers Disc1  Disc2  DsPerc AcPay1 AcPay2
	bool bEditsStatus[6][9] = {{false, false, false, false, false, false, false, false, false},        //  BA_VIEW
							   {true,  true,  true,  true,  true,  true,  true,  true,  true},         //  BA_EDIT
							   {false, false, true,  true,  true,  true,  true,  true,  true},         //  BA_SALE
							   {true,  true,  false, false, true,  true,  true,  true,  true},         //  BA_RETURN
							   {true,  true,  false, false, true,  true,  true,  true,  true},         //  BA_INCOM
							   {false, false, true,  true,  false, false, false, true,  true}          //  BA_OUT
							  };
	const wchar_t *wCaptionsForm[][2] = {
		{L"Просмотр операции",			L"Əməliyyata baxış"},
		{L"Редактирование операции",	L"Əməliyyatın redaktəsi"},
		{L"Продажа товаров",			L"Malların satışı"},
		{L"Возврат товаров",			L"Malların qaydışı"},
		{L"Приемка товаров",			L"Malların qəbulu"},
		{L"Передача товаров",			L"Malların köçürülməsi"}
	};

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
				default:
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
		default:
            break;
	}
	for(int i=0; i < 9; i++) {
		Edits[i]->Enabled = bEditsStatus[index][i];
	}
	Caption = wCaptionsForm[index][iLang];
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::FormShow(TObject *Sender)
{
	TmpMoveProduct->Clear();
	ClearFields();

	switch(FormShop->ButtonOperat) {
		case TButtonAction::BA_VIEW:
			*TmpMoveProduct = *(TMoveProduct::VMoveProduct[FormShop->MoveList->ipp[FormShop->MoveList->ItemIndex]]);
//			TmpMoveProduct = TMoveProduct::VMoveProduct[FormShop->MoveList->ipp[FormShop->MoveList->ItemIndex]];
			ButtonSubmit->OnClick = NULL;
			TimerDate->Enabled = false;
			break;
		case TButtonAction::BA_EDIT:
			*TmpMoveProduct = *(TMoveProduct::VMoveProduct[FormShop->MoveList->ipp[FormShop->MoveList->ItemIndex]]);
//			TmpMoveProduct->MoveType = TMoveType::MOV_SALE;
			ButtonSubmit->OnClick = ButtonSaveClick;
			TimerDate->Enabled = false;
			break;
		case TButtonAction::BA_SALE:
			TmpMoveProduct->MoveType = TMoveType::MOV_SALE;
			TmpMoveProduct->SourceUnit = FormShop->ShopUnit;
			TmpMoveProduct->SourcePerson = FormShop->Worker;
			TmpMoveProduct->TargetUnit = TShopUnits::Buyer;
			TmpMoveProduct->TargetPerson = TBuyer::Unknow;
			TimerDate->Enabled = true;
			break;
		case TButtonAction::BA_OUT:
			TmpMoveProduct->MoveType = TMoveType::MOV_OUT;
			TmpMoveProduct->SourceUnit = FormShop->ShopUnit;
			TmpMoveProduct->SourcePerson = FormShop->Worker;
			TmpMoveProduct->TargetUnit = TShopUnits::Empty;
			TmpMoveProduct->TargetPerson = TBuyer::Unknow;
			TimerDate->Enabled = true;
			break;
		case TButtonAction::BA_INCOM:
			TmpMoveProduct->MoveType = TMoveType::MOV_INC;
			TmpMoveProduct->SourceUnit = TShopUnits::Provisioner;
			TmpMoveProduct->SourcePerson = TProvisioner::Unknow;
			TmpMoveProduct->TargetUnit = FormShop->ShopUnit;
			TmpMoveProduct->TargetPerson = FormShop->Worker;
			TimerDate->Enabled = true;
			break;
		case TButtonAction::BA_RETURN:
			TmpMoveProduct->MoveType = TMoveType::MOV_RET;
			TmpMoveProduct->SourceUnit = TShopUnits::Buyer;
			TmpMoveProduct->SourcePerson = TBuyer::Unknow;
			TmpMoveProduct->TargetUnit = FormShop->ShopUnit;
			TmpMoveProduct->TargetPerson = FormShop->Worker;
			TimerDate->Enabled = true;
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
	ClearToolBar();
	AddButtonToolBar();
	SetPositionCloseButton();

	MyListView->FillList();

	bChanged = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::FormResize(TObject *Sender)
{
	if(!bOnceRun) {
		bOnceRun = true;

		GroupBoxTarget->Left = ClientWidth - GroupBoxTarget->Width - 10;
		GroupBoxCenter->Left = (ClientWidth - GroupBoxCenter->Width) / 2;

		ButtonSubmit->Left = (ClientWidth - ButtonSubmit->Width) / 3;
		ButtonSubmit->Top = ClientHeight - ButtonSubmit->Height - HeightTaskBar - 4;
		ButtonCancel->Left = (ClientWidth - ButtonSubmit->Width) * 2 / 3;
		ButtonCancel->Top = ButtonSubmit->Top;

		MemoDescription->Width = ClientWidth - MemoDescription->Left - 10;
		MemoDescription->Top = ButtonSubmit->Top - MemoDescription->Height - 5;

		LabelNote->Left = (ClientWidth - LabelNote->Width) / 2;
		LabelNote->Top = MemoDescription->Top - LabelNote->Height - 1;

		GroupBoxLeft->Top = LabelNote->Top - GroupBoxLeft->Height - 1;
		GroupBoxRight->Top = GroupBoxLeft->Top;
		GroupBoxRight->Left = ClientWidth - GroupBoxRight->Width - 10;

		GroupBoxCenter2->Top = GroupBoxLeft->Top;
		GroupBoxCenter2->Left = (GroupBoxRight->Left - GroupBoxLeft->Left + GroupBoxLeft->Width - GroupBoxCenter2->Width) / 2;

		MyListView->Left = 10;
		MyListView->Width = ClientWidth - MyListView->Left - 10;
		MyListView->Top = GroupBoxSource->Top + GroupBoxSource->Height + 4;
		MyListView->Height = GroupBoxLeft->Top - MyListView->Top - 5;

		MyListView->ColumnsCreat();

		DesignForm();
		ClearToolBar();
		AddButtonToolBar();
//		SetPrivileges();
		SetPositionCloseButton();
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::FormClose(TObject *Sender, TCloseAction &Action)
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
//               Delete Item Select Product
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::DeleteItem(void)
{
	if(MyListView->ItemIndex != -1) {

		TSelectProduct *CurSelectedProduct = TmpMoveProduct->VSelectedProd[MyListView->ipp[MyListView->ItemIndex]];
		int IndexV = TmpMoveProduct->GetIndexInVSelectById(CurSelectedProduct->id);

		if(IndexV != -1) {
			FormMoveProduct->TmpMoveProduct->CorrectUnitsBalance(IndexV, -1);
		}

		vector <TSelectProduct*>::iterator it = TmpMoveProduct->VSelectedProd.begin() + IndexV;
		TmpMoveProduct->VSelectedProd.erase(it);

		MyListView->FillList();

	} else {
		Application->MessageBox(wSelectMessage[iLang], uCaptionWarning[iLang], MB_OK);
	}
}

//---------------------------------------------------------------------------
//      	Save Move Product
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::ButtonSaveClick(TObject *Sender)
{
	if(!CheckCorrectFields()) {
		return;
	}

	SaveAtFormToObject(TmpMoveProduct, false);
	if(!TmpMoveProduct->CheckCorrect()) {
		return;
	}

	ButtonSubmit->Enabled = false;

	// Delete old VSelect Product from DB
	TMoveProduct *OldMoveProduct = TMoveProduct::VMoveProduct[FormShop->MoveList->ipp[FormShop->MoveList->ItemIndex]];
	for(unsigned i=0; i < OldMoveProduct->VSelectedProd.size(); i++) {
		OldMoveProduct->VSelectedProd[i]->DeleteObjectFromDb(FormShop->FDQuery1);
	}
//	OldMoveProduct->ShowVectorMoveProduct();

	vector <TBaseData*> vAliasBaseData = *(OldMoveProduct->VBaseData);
	vector <TBaseData*> vAliasBaseData2 = *(TmpMoveProduct->VBaseData);
/**/
	delete OldMoveProduct;

//	OldMoveProduct->ShowVectorMoveProduct();

//	TmpMoveProduct->ShowVectorMoveProduct();

	TmpMoveProduct->SaveAtObjectToDb(FormShop->FDQuery1);

//	TmpMoveProduct->ShowVectorMoveProduct();


	// calc Total Price and balance
	TMoveProduct::CalcUnitsBalance();
	TMoveProduct::CalcDebts();

	switch(TmpMoveProduct->MoveType) {
		case TMoveType::MOV_SALE:
		case TMoveType::MOV_RET:
			FormBuyerList->bListUpdate = true;
			break;
		case TMoveType::MOV_INC:
			FormProvisionerList->bListUpdate = true;
			break;
		case TMoveType::MOV_OUT:
			break;
		default:
            break;
	}
	FormProductList->bListUpdate = true;

	TmpMoveProduct = new TMoveProduct();

	FormShop->MoveList->FillList();
	FormShop->AtomList->FillList();

	bChanged = false;

	Close();
}
//---------------------------------------------------------------------------
//      	Insert Move Product
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::ButtonInsertClick(TObject *Sender)
{
	if(!CheckCorrectFields()) {
		return;
	}

	SaveAtFormToObject(TmpMoveProduct, true);
	if(!TmpMoveProduct->CheckCorrect()) {
		return;
	}

	TmpMoveProduct->InsertAtObjectToDb(FormShop->FDQuery1);

	// calc Total Price and balance
	TMoveProduct::CalcUnitsBalance();
	TMoveProduct::CalcDebts();

	switch(TmpMoveProduct->MoveType) {
		case TMoveType::MOV_SALE:
		case TMoveType::MOV_RET:
			FormBuyerList->bListUpdate = true;
			break;
		case TMoveType::MOV_INC:
			FormProvisionerList->bListUpdate = true;
			break;
		case TMoveType::MOV_OUT:
			break;
		default:
            break;
	}
	FormProductList->bListUpdate = true;

	TmpMoveProduct = new TMoveProduct();

	FormShop->MoveList->FillList();
	FormShop->AtomList->FillList();

	bChanged = false;
	Close();
}
//---------------------------------------------------------------------------
//               Delete Move Product
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::DeleteMoveProduct(TMoveProduct *MoveProduct)
{
	MoveProduct->DeleteObjectFromDb(FormShop->FDQuery1);
}
//---------------------------------------------------------------------------
bool __fastcall TFormMoveProduct::CheckCorrectFields(void)
{
	switch(TmpMoveProduct->MoveType) {
		case TMoveType::MOV_SALE:
			if(TmpMoveProduct->TargetPerson == TBuyer::Unknow && TmpMoveProduct->ActualPayment != TmpMoveProduct->TotalPayment) {
				Application->MessageBox(wCorrectField1Message[iLang], uCaptionWarning[iLang], MB_OK);
				return false;
			}
			break;
		case TMoveType::MOV_OUT:
			break;
		case TMoveType::MOV_INC:
			if(TmpMoveProduct->SourcePerson == TProvisioner::Unknow && TmpMoveProduct->ActualPayment != TmpMoveProduct->TotalPayment) {
				Application->MessageBox(wCorrectField2Message[iLang], uCaptionWarning[iLang], MB_OK);
				return false;
			}
			break;
		case TMoveType::MOV_RET:
			if(TmpMoveProduct->SourcePerson == TBuyer::Unknow && TmpMoveProduct->ActualPayment != TmpMoveProduct->TotalPayment) {
				Application->MessageBox(wCorrectField1Message[iLang], uCaptionWarning[iLang], MB_OK);
				return false;
			}
			break;
		default:
			return false;
	}
	return true;
}

//---------------------------------------------------------------------------
//  ********     Buttons, whath location on top form  *******
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::ToolButtonsClickAction(TButtonAction bAction)
{
	if((MyListView->ItemIndex == -1) && (bAction != TButtonAction::BA_ADD)) {
		Application->MessageBox(wSelectMessage[iLang], uCaptionWarning[iLang], MB_OK);
		return;
	}

	FormSelectProd->ShowModal();

	MyListView->FillList();
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::TimerDateTimer(TObject *Sender)
{
	LabelDate->Caption = TDateTime::CurrentDateTime().FormatString(wDateTimeFormat);
}

//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::SetFloatToEdit(TEdit *Edit, double dValue)
{
	UnicodeString uTmp;
	uTmp.sprintf(L"%1.2f", dValue);
	int PosDot = uTmp.Pos(L".");

	wchar_t szSep[8];
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, szSep, 8);
	UnicodeString uDecimelSeparator = szSep;

	uTmp.Delete(PosDot,1);
	uTmp.Insert(uDecimelSeparator, PosDot);

	Edit->Text = uTmp;
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::EditDiscountPrice1Change(TObject *Sender)
{
	if(EditDiscountPercent->Focused() || bExternLoad) {
		return;
	}
	if(bChangeFromAtomList) {
		bExternLoad = true;
	}

//	bChanged = true;

	TmpMoveProduct->Discount.GetFromTEdit(EditDiscountPrice1, EditDiscountPrice2);
	TmpMoveProduct->CalcTotalPrice();
	TmpMoveProduct->TotalPrice.SetOnEdit(EditTotalPrice1, EditTotalPrice2);
	TmpMoveProduct->TotalPayment.SetOnEdit(EditBuyerPayment1, EditBuyerPayment2);

	// Calc percent
	UnicodeString uTmp;
	uTmp.sprintf(L"%1.2f", TmpMoveProduct->TotalPrice.GetPercent(TmpMoveProduct->Discount));
	int PosDot = uTmp.Pos(L".");

	wchar_t szSep[8];
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, szSep, 8);
	UnicodeString uDecimelSeparator = szSep;

	uTmp.Delete(PosDot,1);
	uTmp.Insert(uDecimelSeparator, PosDot);

	EditDiscountPercent->Text = uTmp;
	bExternLoad = false;
}

//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::EditDiscountPercentChange(TObject *Sender)
{
	if(EditDiscountPrice1->Focused() || EditDiscountPrice2->Focused()) {
		return;
	}

	bChanged = true;

	TmpMoveProduct->Discount = 0;
	TmpMoveProduct->CalcTotalPrice();

	double dPerc;

	if(EditDiscountPercent->Text != L"") {
		UnicodeString uPerc = EditDiscountPercent->Text;

		int iPosCursor = EditDiscountPercent->SelStart;
		try {
			dPerc = uPerc.ToDouble();
		} catch(...) {
			EditDiscountPercent->SelStart = iPosCursor - 1;
			return;
		}
		if(dPerc < 0. || dPerc > 100.) {
			EditDiscountPercent->SelStart = iPosCursor - 1;
			return;
		}
	} else {
		dPerc = 0.;
	}

	TmpMoveProduct->Discount = TmpMoveProduct->TotalPrice.SetPercent(dPerc);
	TmpMoveProduct->CalcTotalPrice();

	TmpMoveProduct->TotalPayment.SetOnEdit(EditBuyerPayment1, EditBuyerPayment2);
	TmpMoveProduct->Discount.SetOnEdit(EditDiscountPrice1, EditDiscountPrice2);
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::EditActualPayment1Change(TObject *Sender)
{
	TmpMoveProduct->ActualPayment = 0;
	TmpMoveProduct->ActualPayment.GetFromTEdit(EditActualPayment1, EditActualPayment2);

	TmpMoveProduct->Debt = TmpMoveProduct->TotalPayment - TmpMoveProduct->ActualPayment;
	TmpMoveProduct->Debt.SetOnEdit(EditDebt1, EditDebt2);

	bChanged = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::EditBuyerPayment1Change(TObject *Sender)
{
	TmpMoveProduct->Debt = TmpMoveProduct->TotalPayment - TmpMoveProduct->ActualPayment;
	TmpMoveProduct->Debt.SetOnEdit(EditDebt1, EditDebt2);

	bChanged = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::EditSourceUnitClick(TObject *Sender)
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
		default:
			return;
	}

	bChanged = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::EditTargetUnitClick(TObject *Sender)
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
		default:
			return;
	}

	bChanged = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::DisableEventsAction(void)
{
	EditDiscountPrice1->OnChange = NULL;
	EditDiscountPrice2->OnChange = NULL;
	EditDiscountPercent->OnChange = NULL;
	EditActualPayment1->OnChange = NULL;
	EditActualPayment2->OnChange = NULL;
	EditBuyerPayment1->OnChange = NULL;
	EditBuyerPayment2->OnChange = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::EnableEventsAction(void)
{
	EditDiscountPrice1->OnChange = EditDiscountPrice1Change;
	EditDiscountPrice2->OnChange = EditDiscountPrice1Change;
	EditDiscountPercent->OnChange = EditDiscountPercentChange;
	EditActualPayment1->OnChange = EditActualPayment1Change;
	EditActualPayment2->OnChange = EditActualPayment1Change;
	EditBuyerPayment1->OnChange = EditBuyerPayment1Change;
	EditBuyerPayment2->OnChange = EditBuyerPayment1Change;
}

//---------------------------------------------------------------------------
//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::LoadFromObjectToForm(TMoveProduct *CurMoveProduct)
{
	DisableEventsAction();  // off onchange events

	LabelDate->Caption = CurMoveProduct->DateTime.FormatString(wDateTimeFormat);
	LabelCashNumb->Caption = CurMoveProduct->id;
	EditSourceUnit->Text = CurMoveProduct->SourceUnit->Name;
	EditSourcePerson->Text = CurMoveProduct->SourcePerson->SumName;
	EditTargetUnit->Text = CurMoveProduct->TargetUnit->Name;
	EditTargetPerson->Text = CurMoveProduct->TargetPerson->SumName;

	CurMoveProduct->TotalPrice.SetOnEdit(EditTotalPrice1, EditTotalPrice2);
	CurMoveProduct->Discount.SetOnEdit(EditDiscountPrice1, EditDiscountPrice2);
	CurMoveProduct->TotalPayment.SetOnEdit(EditBuyerPayment1, EditBuyerPayment2);
	SetFloatToEdit(EditDiscountPercent, CurMoveProduct->dPercent);
	CurMoveProduct->ActualPayment.SetOnEdit(EditActualPayment1, EditActualPayment2);
	CurMoveProduct->Debt.SetOnEdit(EditDebt1, EditDebt2);
	MemoDescription->Text = CurMoveProduct->Description;

	CurMoveProduct->CalcTotalPrice();

	EnableEventsAction();  // on onchange events
}

//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::SaveAtFormToObject(TMoveProduct *CurMoveProduct, bool bDate)
{
	if(bDate) {
		CurMoveProduct->DateTime = TDateTime::CurrentDateTime();
	}

	CurMoveProduct->Description = MemoDescription->Text;

	CurMoveProduct->Discount.GetFromTEdit(EditDiscountPrice1, EditDiscountPrice2);
	CurMoveProduct->ActualPayment.GetFromTEdit(EditActualPayment1, EditActualPayment2);
	CurMoveProduct->CalcTotalPrice();
}


//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::ClearFields(void)
{
	EditTotalPrice1->OnChange = NULL;
	EditTotalPrice2->OnChange = NULL;
	EditDiscountPrice1->OnChange = NULL;
	EditDiscountPrice2->OnChange = NULL;
	EditDiscountPercent->OnChange = NULL;
	EditActualPayment1->OnChange = NULL;
	EditActualPayment2->OnChange = NULL;
	EditBuyerPayment1->OnChange = NULL;
	EditBuyerPayment2->OnChange = NULL;

	EditTotalPrice1->Text = L"";
	EditTotalPrice2->Text = L"";
	EditDiscountPrice1->Text = L"";
	EditDiscountPrice2->Text = L"";
	EditDiscountPercent->Text = L"";
	EditActualPayment1->Text = L"";
	EditActualPayment2->Text = L"";
	MemoDescription->Text = L"";
	EditBuyerPayment1->Text = L"";
	EditBuyerPayment2->Text = L"";
	EditActualPayment1->Text = L"";
	EditActualPayment2->Text = L"";
	EditDebt1->Text = L"";
	EditDebt2->Text = L"";

	MyListView->Clear();

//	EditTotalPrice1->OnChange = EditTotalPrice1Change;
//	EditTotalPrice2->OnChange = EditTotalPrice1Change;
	EditDiscountPrice1->OnChange = EditDiscountPrice1Change;
	EditDiscountPrice2->OnChange = EditDiscountPrice1Change;
	EditDiscountPercent->OnChange = EditDiscountPercentChange;
	EditActualPayment1->OnChange = EditActualPayment1Change;
	EditActualPayment2->OnChange = EditActualPayment1Change;
	EditBuyerPayment1->OnChange = EditBuyerPayment1Change;
	EditBuyerPayment2->OnChange = EditBuyerPayment1Change;
}

//---------------------------------------------------------------------------
void __fastcall TFormMoveProduct::ButtonCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

