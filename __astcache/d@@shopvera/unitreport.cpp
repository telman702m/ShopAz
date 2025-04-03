//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.DateUtils.hpp>

#pragma hdrstop

#include "UnitReport.h"
#include "UnitMoveProduct.h"
#include "Shop.h"
#include "Provisioner.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TButton *PredefButtons[4];

TColumnsData ColumnsReport[] = {
	{{L"Объект сети магазинов",	L"Şəbəkənin mağazası"},	100,	taLeftJustify, 	true, 	false},
	{{L"Поступленя",			L"İdxal"},		  		100,	taRightJustify,	true, 	true},
	{{L"Приемка",				L"Qəbul"},  			100, 	taRightJustify,	true, 	true},
	{{L"Передача",				L"Köçurmək"}, 			100, 	taRightJustify, true, 	true},
	{{L"Продажа стоимость",		L"Satış dəyəri"}, 		100, 	taRightJustify, true, 	true},
	{{L"Продажа цена",			L"Satış"}, 				100, 	taRightJustify, true, 	true},
	{{L"Возврат",				L"Qayıdış"}, 			100, 	taRightJustify, true, 	true},
	{{L"Скидки",				L"Güzəşt"},				100, 	taRightJustify, true, 	true},
	{{L"Долг покуп.",			L"Borc alıcı."},		100, 	taRightJustify, true, 	true},
	{{L"Долг постав.",			L"Borc təciz."},		100, 	taRightJustify, true, 	true},
	{{L"Затраты",			   	L"Xərclər"},			100, 	taRightJustify, true, 	true},
	{{L"Касса",					L"Kassa"},				100, 	taRightJustify, true, 	true},
	{{L"Прибыль",				L"Mənfəət"},			100, 	taRightJustify, true, 	true},
	{{L"% прибыли",				L"Mənfəət %"},			100, 	taRightJustify, true, 	true},
	{{L"Остаток стоимость",	  	L"Qalıq dəyəri"},		100, 	taRightJustify, true, 	true},
	{{L"Остаток цена",			L"Qalıq giyməti"},		100, 	taRightJustify, true, 	true}
};
TLabelCaption LabelCaptionReport[] = {
	{{L"Начало",	L"Başlanğıc"},	NULL},
	{{L"Конец",		L"Son"},		NULL}
};
TButtonCaption ButtonCaptionReport[] = {
	{{L"За последний день",		L"Son gün üçün"},	NULL},
	{{L"За последнюю неделю",	L"Son həftə üçün"},	NULL},
	{{L"За последний месяц",	L"Son ay üçün"},	NULL},
	{{L"За последний год",		L"Son il üçün"},	NULL}
};
TGroupBoxCaption GroupBoxCaptionReport[] = {
	{{L"Диапазон дат для формирования отчета ",			L"Hesabatı formalaşdırmaq üçün tarix aralığı "},	NULL},
	{{L"Предустановленные диапазоны дат для отчета ",	L"Əvvəlcədən təyin edilmiş tarix aralığları "},		NULL}
};

TFormReport *FormReport;

//---------------------------------------------------------------------------
__fastcall TFormReport::TFormReport(TComponent* Owner)
	: TFormParent(Owner)
{
	wFormCaptions[0] = L"Отчет";
	wFormCaptions[1] = L"Hesabat";

	LocateMyListView.Left = 2;
	LocateMyListView.Top = 40;
	LocateMyListView.Width = 700;
	LocateMyListView.Height = 420;

	SizeColumnsData = sizeof(ColumnsReport) / sizeof(TColumnsData);
	ColumnsData = ColumnsReport;

	SizeLabelsData = sizeof(LabelCaptionReport) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionReport;

	SizeButtonsData = sizeof(ButtonCaptionReport) / sizeof(TButtonCaption);
	ButtonsCaption = ButtonCaptionReport;

	SizeGroupBoxData = sizeof(GroupBoxCaptionReport) / sizeof(TGroupBoxCaption);
	GroupBoxCaption = GroupBoxCaptionReport;
}

//---------------------------------------------------------------------------
void __fastcall TFormReport::FormCreate(TObject *Sender)
{
	DateTimePicker1->Format = wDateTimePickerFormat;
	DateTimePicker2->Format = wDateTimePickerFormat;

//	DateTimePicker1->Date = Date().CurrentDate();
//	DateTimePicker1->Time = 0;
//	DateTimePicker2->Date = Date().CurrentDate();
//	DateTimePicker2->Time = 0.999;

	MyListView = new TMyListView(FormReport, FormReport, ColumnsData, SizeColumnsData, LocateMyListView, TYPE_LIST::LS_REPORTS, true);
	MyListView->Name = L"ReportList";

	LabelsCaption[0].Label = LabelStartDate;
	LabelsCaption[1].Label = LabelEndDate;

	PredefButtons[0] = ButtonLastDay;
	PredefButtons[1] = ButtonLastWeek;
	PredefButtons[2] = ButtonLastMonth;
	PredefButtons[3] = ButtonLastYear;

	ButtonsCaption[0].Button = ButtonLastDay;
	ButtonsCaption[1].Button = ButtonLastWeek;
	ButtonsCaption[2].Button = ButtonLastMonth;
	ButtonsCaption[3].Button = ButtonLastYear;

	GroupBoxCaption[0].GroupBox = GroupBoxDateRange;
	GroupBoxCaption[1].GroupBox = GroupBoxPredefInterval;

	SetLanguage();
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::FormShow(TObject *Sender)
{
	DateTimePicker1->MinDate = FormShop->ShopUnit->LoadDateData;
	DateTimePicker2->MinDate = FormShop->ShopUnit->LoadDateData;

	bEventPicker = false;

	if(bOnceRun) {
		TReport::CalcReport();
	}
/*
	if(bOnceRun) {
		MyListView->ColumnsCreat();
		TReport::CalcReport();

		ToolButtonSeparator0->Width = 8;
		TFormParent::SetPositionCloseButton();
	}*/
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::FormResize(TObject *Sender)
{
	if(!bOnceRun) {
		bOnceRun = true;

		DateTimePicker1->Date = Date().CurrentDate();
		DateTimePicker1->Time = 0;
		DateTimePicker2->Date = Date().CurrentDate();
		DateTimePicker2->Time = 0.999;

		GroupBoxDateRange->Top = ToolBar1->Height + 5;
		GroupBoxPredefInterval->Top = GroupBoxDateRange->Top;
		GroupBoxPredefInterval->Left = ClientWidth - 2 * GroupBoxDateRange->Left - GroupBoxPredefInterval->Width;

		MyListView->Left = 4;
		MyListView->Width = ClientWidth - MyListView->Left - 4;
		MyListView->Top = GroupBoxDateRange->Top + GroupBoxDateRange->Height + 4;
		MyListView->Height = (ClientHeight - MyListView->Top - HeightTaskBar) / 2;

		GroupBoxStatistic->Left = 4;
		GroupBoxStatistic->Top = MyListView->Top + MyListView->Height + 10;
		GroupBoxStatistic->Width = MyListView->Width;
		GroupBoxStatistic->Height = ClientHeight - GroupBoxStatistic->Top - HeightTaskBar - 10;

		MyListView->ColumnsCreat();
		TReport::CalcReport();

		DropVisibleStatus();
		ClearToolBar();
		AddButtonToolBar();
		SetPositionCloseButton();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::DateTimePicker1Change(TObject *Sender)
{
	if(!bEventPicker) {
		TReport::CalcReport();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::DateTimePicker1CloseUp(TObject *Sender)
{
	TReport::CalcReport();
	bEventPicker = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::DateTimePicker1Click(TObject *Sender)
{
	bEventPicker = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormReport::ButtonsPredefClick(TObject *Sender)
{
	TButton *Button = dynamic_cast<TButton*>(Sender);
	int iButton;

	for(iButton = 0; iButton < 4; iButton++) {
		if(Button == PredefButtons[iButton]) {
			break;
		}
	}

	TDateTime DateNow = Date().CurrentDate();
	TDateTime DateStart;

	switch(iButton) {
		case 0:
			DateStart = IncDay(DateNow, -1);
			break;
		case 1:
			DateStart = IncWeek(DateNow, -1);
			break;
		case 2:
			DateStart = IncMonth(DateNow, -1);
			break;
		case 3:
			DateStart = IncYear(DateNow, -1);
			break;
		default:
			return;
	}

	DateTimePicker1->Date = DateStart;
	DateTimePicker1->Time = 0;
	DateTimePicker2->Date = DateNow;
	DateTimePicker2->Time = 0.999;

	TReport::CalcReport();
}
//---------------------------------------------------------------------------

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//---------------------------------------------------------------------------
TReport** TReport::Reports;
int TReport::CountReport;

//---------------------------------------------------------------------------
void __fastcall TReport::InitReport(void)
{
	CountReport = TShopUnits::VShopUnits.size();
	Reports = new TReport*[CountReport];
	for (int i = 0; i < CountReport; i++) {
		Reports[i] = new TReport();
	}
}
//---------------------------------------------------------------------------
void __fastcall TReport::DestructReport(void)
{
	for (int i = 0; i < CountReport; i++) {
		delete Reports[i];
	}
	delete[] Reports;
}
//---------------------------------------------------------------------------
void __fastcall TReport::RestoreOrderShopsName(void)
{
	for(unsigned i=0; i < TShopUnits::VShopUnits.size(); i++) {
		Reports[i]->NameUnit = TShopUnits::VShopUnits[i]->Name;
	}
}
//---------------------------------------------------------------------------
void __fastcall TReport::CalcReport(void)
{
	for(unsigned i=0; i < TShopUnits::VShopUnits.size(); i++) {
		Reports[i]->Incoming = 0;
		Reports[i]->Receive = 0;
		Reports[i]->Send = 0;
		Reports[i]->Sale = 0;
		Reports[i]->Return = 0;
		Reports[i]->Discount = 0;
		Reports[i]->DebtBuyers = 0;
		Reports[i]->DebtProvis = 0;
		Reports[i]->Expanses = 0;
		Reports[i]->Cashbox = 0;
		Reports[i]->Cost = 0;
		Reports[i]->Profit = 0;
		Reports[i]->PercentProfit = 0;
		Reports[i]->BalanceProductCost = 0;
		Reports[i]->BalanceProductPrice = 0;
	}

	vector <TMoveProduct *> &VMoves = TMoveProduct::VMoveProduct;   // alias
	int iSource, iTarget;

	unsigned CountMove = VMoves.size();
	for(unsigned i=0; i < CountMove; i++) {

		if((VMoves[i]->DateTime >= FormReport->DateTimePicker1->DateTime) &&
		   (VMoves[i]->DateTime <= FormReport->DateTimePicker2->DateTime) &&
		   !VMoves[i]->bDeleted) {

			switch(VMoves[i]->MoveType) {
				case TMoveType::MOV_SALE:
					iSource = TShopUnits::GetIndexUnitById(VMoves[i]->idSource);
					if(iSource != -1) {
						Reports[iSource]->Sale += VMoves[i]->TotalPrice;
						Reports[iSource]->Cost += VMoves[i]->TotalCostPrice;
						Reports[iSource]->Discount += VMoves[i]->Discount;
						Reports[iSource]->DebtBuyers -= VMoves[i]->Debt;
					}
					break;
				case TMoveType::MOV_RET:
					iTarget = TShopUnits::GetIndexUnitById(VMoves[i]->idTarget);
					if(iTarget != -1) {
						Reports[iTarget]->Return += VMoves[i]->TotalPrice;
						Reports[iTarget]->Cost -= VMoves[i]->TotalCostPrice;
						Reports[iTarget]->Discount -= VMoves[i]->Discount;
						Reports[iTarget]->DebtBuyers += VMoves[i]->Debt;
					}
					break;
				case TMoveType::MOV_INC:
					iTarget = TShopUnits::GetIndexUnitById(VMoves[i]->idTarget);
					if(iTarget != -1) {
						Reports[iTarget]->Incoming += VMoves[i]->TotalPrice;
//						Reports[iTarget]->Discount -= VMoves[i]->Discount;
						Reports[iTarget]->DebtProvis += VMoves[i]->Debt;
					}
					break;
				case TMoveType::MOV_OUT:
					iSource = TShopUnits::GetIndexUnitById(VMoves[i]->idSource);
					if(iSource != -1) {
						Reports[iSource]->Send += VMoves[i]->TotalPrice;
//						Reports[iSource]->TotalDiscount += VMoves[i]->Discount;
//						Reports[iSource]->Debt -= VMoves[i]->Debt;
					}
					iTarget = TShopUnits::GetIndexUnitById(VMoves[i]->idTarget);
					if(iTarget != -1) {
						Reports[iTarget]->Receive += VMoves[i]->TotalPrice;
//						Reports[iTarget]->TotalDiscount += VMoves[i]->Discount;
//						Reports[iTarget]->Debt += VMoves[i]->Debt;
					}
					break;
				case TMoveType::MOV_DEBT:  // source - Buyer    target - Shop
					iTarget = TShopUnits::GetIndexUnitById(VMoves[i]->idTarget);
					if(iTarget != -1) {
						Reports[iTarget]->DebtBuyers += VMoves[i]->ActualPayment;
					}
					break;
				case TMoveType::MOV_EXP:
					iSource = TShopUnits::GetIndexUnitById(VMoves[i]->idSource);
					if(iSource != -1) {
						Reports[iSource]->Expanses += VMoves[i]->ActualPayment;
					}
					break;
				case TMoveType::MOV_DEBT_PROVIS:  // source - Shop    target - Provisioner
					iSource = TShopUnits::GetIndexUnitById(VMoves[i]->idSource);
					if(iSource != -1) {
						Reports[iSource]->DebtProvis -= VMoves[i]->ActualPayment;
					}
/*
					iTarget = (TProvisioner::GetProvisionerById(VMoves[i]->idTarget))->id;
					if(iTarget != -1) {
						Reports[iTarget]->DebtProvis -= VMoves[i]->ActualPayment;
					}*/
					break;
				default:
					break;
			}

		}
	}

	for(unsigned i=0; i < TShopUnits::VShopUnits.size(); i++) {
		Reports[i]->Cashbox = Reports[i]->Sale - Reports[i]->Return - Reports[i]->Discount + Reports[i]->DebtBuyers - Reports[i]->Expanses;
		Reports[i]->Profit = Reports[i]->Cashbox - Reports[i]->Cost - Reports[i]->DebtBuyers;
		Reports[i]->CalcProfitPercent();
	}


	//  Calc product balance
	unsigned Count = TProduct::VProduct.size();

	for(unsigned i=0; i < Count; i++) {
		for(unsigned j=0; j < TShopUnits::VShopUnits.size(); j++) {
			if(TProduct::VProduct[i]->CountBalance[j] > 0) {
				Reports[j]->BalanceProductCost += TProduct::VProduct[i]->PurchaseCash * TProduct::VProduct[i]->CountBalance[j];
				Reports[j]->BalanceProductPrice += TProduct::VProduct[i]->SellingPrice * TProduct::VProduct[i]->CountBalance[j];
			}
		}
	}

	FormReport->MyListView->FillList();
}

//---------------------------------------------------------------------------
void __fastcall TReport::CalcProfitPercent(void)
{
	double profit = Profit.GetValue();// double(Profit.GetMoney())*100. + double(Profit.GetCent());
	double cost = Cost.GetValue(); // double(Cost.GetMoney())*100. + double(Cost.GetCent());

	if(profit <=0. || cost <= 0.) {
		PercentProfit = 0;
	} else {
		PercentProfit = profit / cost * 100.;
	}
}

//---------------------------------------------------------------------------

