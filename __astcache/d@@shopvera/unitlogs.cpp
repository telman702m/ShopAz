//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitLogs.h"
#include "Shop.h"
#include "Logs.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitParentEsc"
#pragma resource "*.dfm"

const wchar_t *wTablesDB[] = {
	L"Группа продуктов",
	L"Продукты",
	L"Покупатели",
	L"Поставщики",
	L"Товарная операция",
	L"Выбор товара"
};
const wchar_t *wTableOperations[] = {
	L"Подключение",
	L"Отключение",
	L"Добавление",
	L"Корректировка",
	L"Удаление"
};
const wchar_t *wExitStatus[] = {
	L"Корректно",
	L"Аварийно",
	L"Онлайн"
};


TFormLogs *FormLogs;

//---------------------------------------------------------------------------
__fastcall TFormLogs::TFormLogs(TComponent* Owner)
	: TFormEsc(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormLogs::FormCreate(TObject *Sender)
{
//	RECT r;
//	ListView_GetItemRect(ListViewLogsData->Handle, 0, &r, LVIR_BOUNDS);
//	int ItemHeight = (r.bottom - r.top);
/*
	int ItemIndex = IndexSelected;
	int ScrollToIndex = IndexSelected;

	if((ItemIndex >= 0) && (ItemIndex < ListViewLogsData->Items->Count)) {
		TListItem *Item = ListViewLogsData->Items->Item[ItemIndex];
        Item->MakeVisible(false);

		if(ScrollToIndex > -1) {
			RECT r;
			ListView_GetItemRect(ListViewLogsData->Handle, ItemIndex, &r, LVIR_BOUNDS);
			int ItemHeight = (r.bottom - r.top);
			int TopIndex = ListView_GetTopIndex(ListViewLogsData->Handle);
			int ScrollAmount = ((TopIndex - ItemIndex + ScrollToIndex) * ItemHeight);
//            ListView_Scroll(ListViewLogsData->Handle, 0, -ScrollAmount);
			ListViewLogsData->Scroll(0, ScrollAmount);
		}
	}*/

	DateTimePicker1->Format = wDateTimePickerFormat;
	DateTimePicker2->Format = wDateTimePickerFormat;

	TDate dd = TDate::CurrentDate();
	DateTimePicker2->Date = dd;
	DateTimePicker2->Time = 0.999;
	DateTimePicker1->Date = dd;
	DateTimePicker1->Time = 0;


	if(TLogs::LoadFromDB(FormShop->FDQuery1, 0, DateTimePicker1->DateTime, DateTimePicker2->DateTime) == 0) {
		TLogs::GetCurrentDateFromDB(FormShop->FDQuery1);
	} else {
		TLogs::ParseLogs();
	}
	if(TLogs::SetFlagRefreshLastAccess() != 0) {
		TLogs::GetLastAccess(FormShop->FDQuery1);
	}
	TLogs::CheckAbnormalExit();
}
//---------------------------------------------------------------------------
void __fastcall TFormLogs::FormShow(TObject *Sender)
{
	Timer1->Enabled = true;

	LoadLogs(true);
}
//---------------------------------------------------------------------------
void __fastcall TFormLogs::Timer1Timer(TObject *Sender)
{
	LoadLogs(false);
}
//---------------------------------------------------------------------------
void __fastcall TFormLogs::LoadLogs(bool bDateFromServer)
{
	if(TLogs::LoadFromDB(FormShop->FDQuery1, TLogs::LastLogId, DateTimePicker1->DateTime, DateTimePicker2->DateTime) == 0) {
		if(bDateFromServer) {
			TLogs::GetCurrentDateFromDB(FormShop->FDQuery1);
		} else {
			TDateTime TimerInterval = EncodeTime(0, 0, Timer1->Interval / 1000, Timer1->Interval % 1000);
			TLogs::CurrentDate += TimerInterval;
		}
	} else {
		TLogs::ParseLogs();
	}

	if(TLogs::SetFlagRefreshLastAccess() != 0) {
		TLogs::GetLastAccess(FormShop->FDQuery1);
	}

	TLogs::CheckAbnormalExit();

	LabelCurrentDateTime->Caption = L"Текущие дата и время на сервере: ";
	LabelCurrentDateTime->Caption += TLogs::CurrentDate;
	ClearDetails();
	FillListLogsData();
}

//---------------------------------------------------------------------------
void __fastcall TFormLogs::FormClose(TObject *Sender, TCloseAction &Action)
{
	Timer1->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormLogs::FillListLogsData(void)
{
	TopIndex = ListView_GetTopIndex(ListViewLogsData->Handle);
	IndexSelected = ListViewLogsData->ItemIndex;

	ListViewLogsData->Clear();

	TListItem  *ListItem;
	ipp.clear();

	for(unsigned i=0; i < TLogs::VLogsData.size(); i++) {

		if((TLogs::VLogsData[i]->StartDate > DateTimePicker1->DateTime)
			&& (TLogs::VLogsData[i]->StartDate < DateTimePicker2->DateTime)
			&& !(CheckBoxActive->Checked && !TLogs::VLogsData[i]->ConnectStatus)) {

			TWorkers *CurWorker = TWorkers::GetWorkerById(TLogs::VLogsData[i]->IdWorker);

			ListItem = ListViewLogsData->Items->Add();
			ListItem->Caption = CurWorker->SumName;
			if(TLogs::VLogsData[i]->ConnectStatus) {
				ListItem->ImageIndex = 0;
			} else {
				ListItem->ImageIndex = 1;
			}

			ListItem->SubItems->Add(TObjectManager<TShopUnits>::GetList()[TLogs::VLogsData[i]->IdShopU-1]->Name);
			ListItem->SubItems->Add(TWorkers::PrivilegName[CurWorker->Privilege]);
			ListItem->SubItems->Add(TLogs::VLogsData[i]->StartDate);
			if(TLogs::VLogsData[i]->ConnectStatus) {
				ListItem->SubItems->Add(L" ");
			} else {
				ListItem->SubItems->Add(TLogs::VLogsData[i]->EndDate);
			}
			ListItem->SubItems->Add((TLogs::VLogsData[i]->LastAccess - TLogs::VLogsData[i]->StartDate).FormatString(L"hh:nn:ss"));
			ListItem->SubItems->Add(TLogs::VLogsData[i]->VLogDetails.size());
			ListItem->SubItems->Add(wExitStatus[TLogs::VLogsData[i]->ExitStatus]);

			ipp.push_back(i);
		}
	}

	try {
		if(IndexSelected != -1 && IndexSelected < ListViewLogsData->Items->Count) {
			ListViewLogsData->ItemIndex = IndexSelected;
			ListViewLogsData->Items->Item[IndexSelected]->Focused = true;

			RECT r;
			ListView_GetItemRect(ListViewLogsData->Handle, 0, &r, LVIR_BOUNDS);
			int ItemHeight = (r.bottom - r.top);
			ListViewLogsData->Scroll(0, TopIndex * ItemHeight);

			ListViewLogsDataClick(this);
		}

	} catch (...) {
//		TopIndex = 0;
//		IndexSelected = -1;

		ListViewLogsData->ItemIndex = -1;
		ListViewLogsDataClick(this);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormLogs::ListViewLogsDataClick(TObject *Sender)
{
	int index = ListViewLogsData->ItemIndex;
	if(index == -1) {
		ClearDetails();
    	return;
	}

	TWorkers *CurWorker = TWorkers::GetWorkerById(TLogs::VLogsData[ipp[index]]->IdWorker);

	LabelUser->Caption = CurWorker->SumName;
	LabelUnitShop->Caption = TObjectManager<TShopUnits>::GetList()[TLogs::VLogsData[ipp[index]]->IdShopU-1]->Name;
	LabelDuration->Caption = (TLogs::VLogsData[ipp[index]]->LastAccess - TLogs::VLogsData[ipp[index]]->StartDate).FormatString(L"hh:nn:ss");
	LabelActions->Caption = TLogs::VLogsData[ipp[index]]->VLogDetails.size();
	LabelExitStatus->Caption = wExitStatus[TLogs::VLogsData[ipp[index]]->ExitStatus];

	ListViewDetails->Clear();
	TListItem  *ListItem;

	for(unsigned i=0; i < TLogs::VLogsData[ipp[index]]->VLogDetails.size(); i++) {
		ListItem = ListViewDetails->Items->Add();
		ListItem->Caption = TLogs::VLogsData[ipp[index]]->VLogDetails[i]->DateTime;

		ListItem->SubItems->Add(wTablesDB[TLogs::VLogsData[ipp[index]]->VLogDetails[i]->IdTable]);
		ListItem->SubItems->Add(wTableOperations[TLogs::VLogsData[ipp[index]]->VLogDetails[i]->IdOperation]);
		ListItem->SubItems->Add(TLogs::VLogsData[ipp[index]]->VLogDetails[i]->CommandSQL);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormLogs::ClearDetails(void)
{
	LabelUser->Caption = L"";
	LabelUnitShop->Caption = L"";
	LabelDuration->Caption = L"";
	LabelActions->Caption = L"";
	LabelExitStatus->Caption = L"";

	ListViewDetails->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormLogs::ListViewLogsDataKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	ListViewLogsDataClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormLogs::CheckBoxActiveClick(TObject *Sender)
{
	FillListLogsData();
}
//---------------------------------------------------------------------------
void __fastcall TFormLogs::DateTimePicker1CloseUp(TObject *Sender)
{
	FormShow(Sender);
	FillListLogsData();
}
//---------------------------------------------------------------------------

