//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>

#pragma hdrstop

#include "Shop.h"
#include "TMNetwork.h"
#include "MoveProduct.h"
#include "Provisioner.h"
#include "UnitProduct.h"
#include "UnitProductList.h"
#include "UnitGroupList.h"
#include "GroupProduct.h"
#include "UnitGroupProduct.h"
#include "UnitMoveProduct.h"
#include "UnitSelectProduct.h"
#include "UnitBuyerList.h"
#include "UnitUserStatus.h"
#include "UnitReport.h"
#include "Protect.h"
#include "Count.h"
#include "Synchronize.h"
#include "UnitShopUnitList.h"
#include "UnitProvisionerList.h"
#include "UnitPrint.h"
#include "UnitUpdater.h"
#include "UnitAbout.h"
#include "UnitLanguage.h"
#include "UnitMoveOther.h"
#include "UnitLogs.h"
#include "Price.h"
#include "TUtills.h"
#include "BaseDataTemplates.h"

#include <stdio.h>
#include <wchar.h>
#include <time.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitParentEsc"
#pragma resource "*.dfm"

const wchar_t *wErrorConfigFileRead[2] = {
	L"Поврежден конфигурационный файл программы \"Config.tshp\".\nНастройки будут сброшены!",
	L"\"Config.tshp\" proqramının konfiqurasiya faylı zədələnmişdir.\nKonfiqurasiya parametrları sıfırlanacaq!"
};

const wchar_t *uShopConnectionDB[2] = {
	L"Невозможно подключиться к Базе Данных на сервере!\nПроверьте Интернет соединение.\n\n Повторить попытку?",
	L"Mümkün deyil Məlumat Bazaya qoşulmaq!\n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};
const wchar_t *uShopUpdated[2] = {
	L"Программа Успешно обновлена",
	L"Program uğurla yeniləndi"
};
const wchar_t *uShopCrashOrder[2] = {
	L"Ошибка в работе программы (нарушен порядок сортировки данных)! Сообщите разработчику!\nПрограмма будет закрыта. Запустите программу снова убрав галочку 'Загрузить основные данные из локальных файлов'",
	L"Proqramdakı səhv (məlumatların çeşidlənməsi qaydası pozulub)! Geliştiriciyə deyin!\nProqram bağlanacaq. 'Əsas məlumatları lokal fayllardan yüklənilsin' checkboxu yığışdırıb, proqramı yenidən yükləyin"
};
const wchar_t *uShopPrivileg[2] = {
	L"У Вас недостаточно привилегий для выполнения этого действия!",
	L"Bu əməliyyat üçün sizin kifayət imtiyazınız yoxdur!"
};
const wchar_t *uShopSelectObject[2] = {
	L"Выберите элемент из списка!",
	L"Siyahıdan bir maddə seçin"
};
const wchar_t *uShopDeleteRecord[2] = {
	L"Выбранная запись об операции будет безвозвратно удалена!\nВы уверены?",
	L"Seçilmiş əməliyyat qaytarılmaz pozulacaq!\nƏminsiz?"
};
const wchar_t *wExitMessage[2] = {
	L"Программа TShop будет закрыта!\nВы уверены?",
	L"TShop programı bağlanacaq!\nSiz əminsiz?"
};

TTMenuItemCaption TMenuItemCaptionMain[] = {
	{{L"Файл", 							L"Fayl"},										NULL},
	{{L"Выход", 						L"Çıxış"},										NULL},

	{{L"Данные", 						L"İnformasiya"},								NULL},
	{{L"Просмотр", 						L"Baxış"},										NULL},
	{{L"Редактирование", 				L"Redaktə"},									NULL},
	{{L"Удаление", 						L"Silme"},										NULL},

	{{L"Базы", 							L"Bazalar"},									NULL},
	{{L"Группа товаров", 				L"Mallar grupu"},								NULL},
	{{L"Товары", 						L"Mallar"},										NULL},
	{{L"Покупатели", 					L"Alıcılar"},									NULL},
	{{L"Объекты сети", 					L"Şəbəkənin obyektləri"},						NULL},
	{{L"Поставщики", 					L"Təchizatçılar"},								NULL},

	{{L"Действия", 						L"Əməliyyətlar"},								NULL},
	{{L"Продажа", 						L"Satış"},										NULL},
	{{L"Возврат", 						L"Qayıdış"},									NULL},
	{{L"Приемка", 						L"Qəbul"},										NULL},
	{{L"Передача", 						L"Köçürmək"},									NULL},
	{{L"Оплата долга покупателя", 	  	L"Alıcının borcunun ödənişi"},					NULL},
	{{L"Затраты магазина", 				L"Mağazanın xərcləri"},							NULL},
	{{L"Оплата долга поставщикам", 		L"Təcizatçının borcunun ödənişi"},				NULL},

	{{L"Инструменты", 					L"Alətlər"},									NULL},
	{{L"Дамп Базы Данных", 				L"Bazasının Dampı"},							NULL},
	{{L"Восстановление Базы Данных", 	L"Bazasının bərpası"},							NULL},
	{{L"Создание пустых таблиц БД", 	L"Bazasının boş cədvəllərinin yaradılması"},	NULL},
	{{L"Установить языковую версию", 	L"Dil versiyasını seçmək"},						NULL},

	{{L"О программе", 					L"Programm haqqında"},							NULL}
};
TToolBarCaption ToolBarCaptionMain[] = {
	{{L"Просмотр", 						L"Baxış"},							NULL},
	{{L"Редактирование", 				L"Redaktə"},					   	NULL},
	{{L"Удаление", 						L"Silme"},							NULL},
	{{L"Группа товаров", 				L"Mallar grupu"},					NULL},
	{{L"Товары", 						L"Mallar"},							NULL},
	{{L"Покупатели", 					L"Alıcılar"},						NULL},
	{{L"Объекты сети", 					L"Şəbəkənin obyektləri"},			NULL},
	{{L"Поставщики", 					L"Təchizatçılar"},					NULL},
	{{L"Продажа", 						L"Satış"},							NULL},
	{{L"Возврат", 						L"Qayıdış"},						NULL},
	{{L"Приемка", 						L"Qəbul"},							NULL},
	{{L"Передача", 						L"Köçürmək"},						NULL},
	{{L"Оплата долга покупателя", 	  	L"Alıcının borcunun ödənişi"},		NULL},
	{{L"Затраты магазина", 				L"Mağazanın xərcləri"},				NULL},
	{{L"Оплата долга поставщикам", 		L"Təcizatçının borcunun ödənişi"},	NULL},
	{{L"Печать", 						L"Çap"},							NULL},
	{{L"Отчеты", 						L"Hesabatlar"},						NULL},
	{{L"Язык интерфейса", 				L"İnterfeysin dili"},				NULL},
	{{L"Закрыть", 						L"Bağlamaq"},						NULL}
};

TLabelCaption LabelCaptionsMain[] = {
	{{L"Начало", 			L"Başlanğıc"},				NULL},
	{{L"Конец", 			L"Son"},					NULL},
	{{L"Поиск по имени", 	L"Adı ilə axtarış"},		NULL},
	{{L"Поиск по товару", 	L"Mal ilə axtarış"},		NULL},
	{{L"Поиск по № чека", 	L"Qaimə № ilə axtarış"},	NULL},
	{{L"Магазин",			L"Mağaza"},					NULL},
	{{L"Статус", 			L"Status"},					NULL},
	{{L"Отправитель",		L"İxracçı"},				NULL},
	{{L"Имя",				L"Adı"},					NULL}
};
TCheckBoxCaption CheckBoxCaptionMain[] = {
	{{L"Продажи",				L"Satış"},					NULL},
	{{L"Возврат", 				L"Qayıdış"},				NULL},
	{{L"Приемка", 				L"Qəbul"},					NULL},
	{{L"Передача", 				L"Köçürmək"},				NULL},
	{{L"Оплата долга", 			L"Borcun ödənişi"},			NULL},
	{{L"Затраты", 				L"Xərclər"},				NULL},
	{{L"Оплата поставщикам",	L"Təcizatçılara ödəniş"},	NULL},
	{{L"Удаленные",				L"Silinmişlər"},			NULL}
};

UnicodeString TFormShop::uLastShopUnit = L"";
UnicodeString TFormShop::uLastWorkerName = L"";
UnicodeString TFormShop::uLastGroupProd = L"";

TColumnsData TFormShop::ColumnsDataSL[] = {
	{{L"Дата",			L"Tarix"},			150,	taCenter, 		true, 	false},
	{{L"№ чека",		L"Qaimə №"},		100, 	taCenter, 		true, 	false},
	{{L"Отправитель",	L"İxracçı"},		150, 	taLeftJustify, 	true, 	false},
	{{L"Имя",			L"Adı"},			200, 	taLeftJustify, 	true, 	false},
	{{L"Получатель",	L"İdxalçı"},		150, 	taLeftJustify, 	true, 	false},
	{{L"Имя",			L"Adı"},			200, 	taLeftJustify, 	true, 	false},
	{{L"Стоимость",		L"Dəyəri"},			100, 	taRightJustify, false,	true},
	{{L"Сумма",			L"Məbləğ"},			100, 	taRightJustify, true, 	true},
	{{L"Скидка",		L"Güzəşt"},			100, 	taRightJustify, true, 	true},
	{{L"Сумма оплаты",	L"Ödəniş məbləği"},	100, 	taRightJustify, true, 	true},
	{{L"Факт.Оплата",	L"Fakt. ödəniş"},	100, 	taRightJustify, true, 	true},
	{{L"Долг",			L"Borc"},			100, 	taRightJustify, true, 	true}
};

TColumnsData TFormShop::ColumnsDataAtom[] = {
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

TFormatSettings FSet;
bool bViewGaala = false;

TFormShop *FormShop;

//---------------------------------------------------------------------------
__fastcall TFormShop::TFormShop(TComponent* Owner)
	: TFormEsc(Owner)
{
	FSet = FSet.Create(L"ru-RU");
	FSet.ThousandSeparator = L' ';

	SizeLabelsData = sizeof(LabelCaptionsMain) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionsMain;

	SizeCheckBoxData = sizeof(CheckBoxCaptionMain) / sizeof(TCheckBoxCaption);
	CheckBoxCaption = CheckBoxCaptionMain;

	SizeToolBarsData = sizeof(ToolBarCaptionMain) / sizeof(TToolBarCaption);
	ToolBarsCaption = ToolBarCaptionMain;

	SizeMenuData = sizeof(TMenuItemCaptionMain) / sizeof(TTMenuItemCaption);
	MenuItemsCaption = TMenuItemCaptionMain;

	MenuEdit->ShortCut = vkF4;

	CurrentLog = new TLogs();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::WMSysCommand(TWMSysCommand &SC)
{
	if(SC.CmdType == 61458){      // SC_DRAGMOVE
		WindowState = wsMaximized;
		return;
	 }
	TForm::Dispatch(&SC);
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::WMNCLButtonDblClk(TWMNCHitTest &SC)
{
	WindowState = wsMaximized;
//   TForm::Dispatch(&SC);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TFormShop::SetLanguage(void)
{
	MoveList->ReloadColumns(ColumnsDataSL);
	AtomList->ReloadColumns(ColumnsDataAtom);

	TFormEsc::SetLanguage();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::FormCreate(TObject *Sender)
{
	if(ParamCount() > 0) {
		if(ParamStr(1) == L"Gaala") {
			bViewGaala = true;
//            ShowMessage(L"Gaala");
		}
	}


	DateTimePicker1->Format = wDateTimePickerFormat;
	DateTimePicker2->Format = wDateTimePickerFormat;

	// Labels assign
	TLabel *Labels[] = {LabelStart, LabelEnd, LabelSearchByName, LabelSearchByProd, LabelCashNumb,
						LabelUnit, LabelStatus, LabelSourceUnit, LabelTargetUnit, LabelTargetName};
	for(unsigned i=0; i < SizeLabelsData; i++) {
		LabelsCaption[i].Label = Labels[i];
	}

	// CheckBoxes assign
	TCheckBox *CheckBoxes[] = {CheckBoxSales, CheckBoxReturn, CheckBoxIncom, CheckBoxOut,
							   CheckBoxRetDebt, CheckBoxExpenses, CheckBoxDebtProvis, CheckBoxDeleted};
	for(unsigned i=0; i < SizeCheckBoxData; i++) {
		CheckBoxCaption[i].CheckBox = CheckBoxes[i];
	}

	// ToolButtons assign
	TToolButton *ToolButtons[] = {ToolButtonView, ToolButtonEdit, ToolButtonDelete, ToolButtonGroupsProd, ToolButtonProducts,
								  ToolButtonBuyers, ToolButtonShopUnits, ToolButtonProvisioners, ToolButtonSale, ToolButtonReturn,
								  ToolButtonIncom, ToolButtonOut, ToolButtonRetDebt, ToolButtonExpenses, ToolButtonRetDebtProvis,
								  ToolButtonPrint, ToolButtonReports, ToolButtonLang, ToolButtonClose};
	for(unsigned i=0; i < SizeToolBarsData; i++) {
		ToolBarCaptionMain[i].ToolButton = ToolButtons[i];
	}

	// Menues assign
	TMenuItem *MenuItems[] = {MenuFile, MenuClose, MenuData, MenuView, MenuEdit, MenuDelete, MenuDB, MenuGroup, MenuProduct,
							  MenuBuyer, MenuUnits, MenuProvisioner, MenuAction, MenuSale, MenuReturn, MenuIncoming, MenuOutgoing,
							  MenuRetDebt, MenuExpenses, MenuDebtProvis, MenuTools, MenuDumpDB, MenuRestoreDB, MenuCreateTablesDB,
							  MenuSetLanguage, MenuAbout};
	for(unsigned i=0; i < SizeMenuData; i++) {
		MenuItemsCaption[i].MenuItem = MenuItems[i];
	}


//	bCloseApplication = false;
	bResized = false;

	try {
		SlistConfig = new TStringList;
		SlistConfig->LoadFromFile(ExtractFilePath(Application->ExeName) + "Config.tshp");
		iLang = SlistConfig->Strings[ListConfParam::LCP_LANG].ToInt();
		uLastShopUnit = SlistConfig->Strings[ListConfParam::LCP_SHOP];
		uLastWorkerName = SlistConfig->Strings[ListConfParam::LCP_WORKER];
		uLastGroupProd = SlistConfig->Strings[ListConfParam::LCP_GROUP];
	} catch (...) {
		Application->MessageBox(wErrorConfigFileRead[iLang], uCaptionError[iLang], MB_OK);
		SlistConfig->Clear();
		iLang = 0;
		SlistConfig->Add(iLang);
		uLastShopUnit = L"0";
		SlistConfig->Add(uLastShopUnit);
		uLastWorkerName = L"";
		SlistConfig->Add(uLastWorkerName);
		uLastGroupProd = L"0";
		SlistConfig->Add(uLastGroupProd);
	}


	//------ Check protect ----------
	TProtect *Protect = new TProtect(3);
	if(!Protect->Gaala()) {
		Application->MessageBox(L"Not registration copy, application will be terminate!", uCaptionWarning[iLang], MB_OK);
		Application->Terminate();
		exit(1);
	}

   FDConnection1->DriverName = L"MySQL";
   FDConnection1->Params->Add(Protect->wParams[1]);
   FDConnection1->Params->Add(Protect->wParams[2]);
   FDConnection1->Params->Add(L"CharacterSet=Utf8");
   FDConnection1->Params->DriverID = L"MySQL";
   FDConnection1->Params->Database = Protect->wParams[3];
   FDConnection1->Params->UserName = Protect->wParams[4];
   FDConnection1->Params->Password = Protect->wParams[5];

	UnicodeString uPath = ExtractFilePath(Application->ExeName);
	uPath += L"libmysql.dll";
	FDPhysMySQLDriverLink1->VendorLib = uPath;

	FDQuery1 = new TMyFDQuery(FormShop);
	FDQuery1->Connection = FDConnection1;

	bool bConnect = false;
	while(!bConnect) {
		try {
			//------- Check Connect to DataBase ------
			FDConnection1->Connected = true;
			bConnect = true;

		} catch (Exception &exception) {
			if(Application->MessageBox(uShopConnectionDB[iLang], uCaptionError[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
            }
			bConnect = false;
		}
	}
	delete Protect;

	TFormParent::GetTaskBarHeight();

	// Cload Fields of Tables DB
	TGroupProduct::GetFieldsDB(FDQuery1, L"GroupProducts");
	TBuyer::GetFieldsDB(FDQuery1, L"Buyers");
	TMoveProduct::GetFieldsDB(FDQuery1, L"MoveProduct");
	TProduct::GetFieldsDB(FDQuery1, L"Products");
	TProvisioner::GetFieldsDB(FDQuery1, L"Provisioners");
	TSelectProduct::GetFieldsDB(FDQuery1, L"SelectProduct");
	TShopUnits::GetFieldsDB(FDQuery1, L"UnitShop");
	TWorkers::GetFieldsDB(FDQuery1, L"Workers");
//	TGroupProduct::ShowFields(TGroupProduct::FieldsTableDB, TGroupProduct::CountFieldsTableDB);

	// Create and load Shop Units & Workers
	TLogs::Init(FDQuery1);
	TLogs::ShowFields();

	ShopUnit = new TShopUnits();
	TShopUnits::LoadFromDB(FDQuery1);
	TReport::InitReport();

	TShopUnits::LoadShopNetNameFromDB(FDQuery1);

	Worker = new TWorkers();

	TShopUnits::CreateBuyerUnit();
	TShopUnits::CreateProvisionerUnit();
	TShopUnits::CreateExpensesUnit();
	TShopUnits::CreateEmptyUnit();

	TBuyer::CreateUnknowBuyer();
	TBuyer::CreateEmptyBuyer();
	TProvisioner::CreateUnknowProvisioner();

	TShopUnits::ArrangeUppArray(ShopUnit);
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::FormResize(TObject *Sender)
{
	if(!bResized) {
		ToolButtonSeparator6->Width = ToolBar1->Width - ToolButtonMonitoring->Left - ToolButtonMonitoring->Width - ToolButtonClose->Width;

		GroupBoxControl->Width = ClientWidth - GroupBoxControl->Left*2;
		GroupBoxMovProd->Width = GroupBoxControl->Width;
		GroupBoxAtom->Width = GroupBoxControl->Width;

		GroupBoxMovProd->Top = GroupBoxControl->Top + GroupBoxControl->Height + 2;
		GroupBoxMovProd->Height = (ClientHeight - GroupBoxMovProd->Top - TFormParent::HeightTaskBar) * 7/10;

		GroupBoxAtom->Top = GroupBoxMovProd->Top + GroupBoxMovProd->Height + 2;
		GroupBoxAtom->Height = ClientHeight - GroupBoxAtom->Top - TFormParent::HeightTaskBar - 5;
		GroupBoxTarget->Left = GroupBoxAtom->Width - GroupBoxTarget->Width;

		GroupBoxUserStatus->Left = GroupBoxControl->Width - GroupBoxUserStatus->Width - 2;

		LocateStockSL.Left = 2;
		LocateStockSL.Top = 2;
		LocateStockSL.Width = GroupBoxMovProd->Width - 4;
		LocateStockSL.Height = GroupBoxMovProd->Height - 4;

		LocateStockAtom.Left = 2;
		LocateStockAtom.Top = GroupBoxSource->Top + GroupBoxSource->Height;
		LocateStockAtom.Width = GroupBoxAtom->Width - 4;
		LocateStockAtom.Height = GroupBoxAtom->Height - LocateStockAtom.Top - 5;

		CreateListViews();

		SetLanguage();
		MoveList->FillList();

		FormProductList->LoadGroupsToComboFilter();

		bResized = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::MenuesEnable(bool bEnable)
{
	TMenuItem *MenuItems[] =
		{MenuFile, MenuData, MenuData, MenuDB, MenuClose, MenuAction, MenuView, MenuEdit, MenuDelete,
		 MenuGroup, MenuProduct, MenuBuyer, MenuUnits, MenuProvisioner, MenuSale, MenuReturn, MenuIncoming,
		 MenuOutgoing, MenuRetDebt, MenuExpenses, MenuDebtProvis, MenuTools, MenuDumpDB, MenuRestoreDB,
		 MenuCreateTablesDB, MenuSetLanguage, ReloadDatabases1, MenuAbout
		};

	for(unsigned i=0; i < sizeof(MenuItems) / sizeof(*MenuItems); i++) {
		MenuItems[i]->Enabled = bEnable;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::FormShow(TObject *Sender)
{
	if(ParamCount() > 0) {
		if(ParamStr(1) == L"Updated") {
			Application->MessageBox(uShopUpdated[iLang], uCaptionInform[iLang], MB_OK);
		} else if(ParamStr(1) == L"Gaala") {
			bViewGaala = true;
		}
	} else {
		FormUpdate->CheckUpdate();

		if(FormUpdate->bRestart) {
			Close();
        }
	}

	MenuesEnable(false);

	TWorkers::LoadFromDB(FDQuery1);

	FormUserStatus->ShowModal();

	if(FormUserStatus->bSuccess) {
		for(unsigned i=0; i < TObjectManager<TShopUnits>::GetList().size(); i++) {
			ComboBoxUShops->Items->Add(TObjectManager<TShopUnits>::GetList()[i]->Name);
		}
		ComboBoxUShops->ItemIndex = FormUserStatus->ComboBoxShopUnits->ItemIndex;
		LabelUserStatus->Caption = TWorkers::PrivilegName[Worker->Privilege];

		UnicodeString uTmp;
		Caption = uTmp.sprintf(L"\"%s\" mağaza şəbəkəsi               İstifadəçi: \"%s\"", TShopUnits::ShopNetName.w_str(), Worker->SumName.w_str());

		TSynchronize::InitLastIdTables(FDQuery1);

		bool bDataLoadType = !FormUserStatus->CheckBoxLoadType->Checked;

		TGroupProduct::LoadFromDB(FDQuery1);

		bool bValidOrder = true;

		TProduct::LoadFromDB(FDQuery1, bDataLoadType);
		if(bValidOrder && TObjectManager<TProduct>::GetList().size() > 0) {
			bValidOrder = CheckSortById_Managed<TProduct>(L"Product");
		}

		TBuyer::LoadFromDB(FDQuery1, bDataLoadType);
		if(bValidOrder && TObjectManager<TBuyer>::GetList().size() > 0) {
			bValidOrder = CheckSortById_Managed<TBuyer>(L"Buyer");
		}

		TProvisioner::LoadFromDB(FDQuery1, bDataLoadType);
		if(bValidOrder && TObjectManager<TProvisioner>::GetList().size() > 0) {
			bValidOrder = CheckSortById_Managed<TProvisioner>(L"Provisioner");
		}

		TMoveProduct::LoadFromDB(FDQuery1, bDataLoadType);
		if(bValidOrder && TObjectManager<TMoveProduct>::GetList().size() > 0) {
			bValidOrder = CheckSortById_Managed<TMoveProduct>(L"MoveProduct");
		}

		TSelectProduct::LoadFromDB(FDQuery1, bDataLoadType);
		if(bValidOrder && TObjectManager<TSelectProduct>::GetList().size() > 0) {
			bValidOrder = CheckSortById_Managed<TSelectProduct>(L"SelectProduct");
		}

		if(!bValidOrder) {
			Application->MessageBox(uShopCrashOrder[iLang], L"Error", MB_OK);
			Application->Terminate();
			exit(1);
        }

		TMoveProduct::CalcUnitsBalance();
		TMoveProduct::CalcDebts();
//		TMoveProduct::CorrectPaymentInOldDB(MyQuery1);
//		TSelectProduct::CheckExcessObjects();

		CurrentLog->IdShop = ShopUnit->id;
		CurrentLog->IdWorker = Worker->id;
		CurrentLog->Set(TabDB::TB_UNDEF, LOGS::LG_CONNECT, L" ");
		CurrentLog->InsertToDb(FDQuery1);
		CurrentLog->ConnectedId = CurrentLog->id;
		CurrentLog->UpdateConnectedId(FDQuery1);

		TBaseData::SetTimerSync(true);
	} else {
		Close();
	}
	SetPrivileges();

	FormMoveProduct->MyListView->ColumnsCreat();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::SetPrivileges(void)
{
	TShopUnits::ArrangeUppArray(ShopUnit);
	FormProductList->FillShopsName();
	FormProductList->TFormParent::SetLanguage();

	switch(Worker->Privilege) {
		case TPrivilege::PRV_SUPER:
			ToolButtonReports->Visible = true;
			MenuDumpDB->Visible = true;
			MenuRestoreDB->Visible = true;
			MenuCreateTablesDB->Visible = true;
            CheckBoxDeleted->Enabled = true;
		case TPrivilege::PRV_ADMIN:
			ColumnsDataSL[5].Visible = true;
			ColumnsDataAtom[4].Visible = true;
			ColumnsDataAtom[7].Visible = true;
			ToolButtonEdit->Visible = true;
			MenuEdit->Visible = true;
			ToolButtonDelete->Visible = true;
			MenuDelete->Visible = true;
		case TPrivilege::PRV_MANAGER:
			ToolButtonProvisioners->Visible = true;
			MenuProvisioner->Visible = true;
			ToolButtonIncom->Visible = true;
			MenuIncoming->Visible = true;
			ToolButtonOut->Visible = true;
			MenuOutgoing->Visible = true;
		case TPrivilege::PRV_SELLER:
		case TPrivilege::PRV_UNKNOW:
			break;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::CreateListViews(void)
{
	AtomList = new TMyListView(FormShop, GroupBoxAtom, ColumnsDataAtom, sizeof(ColumnsDataAtom)/sizeof(TColumnsData), LocateStockAtom, LS_ATOM, false);
	AtomList->Name = L"AtomList";

	MoveList = new TMyListView(FormShop, GroupBoxMovProd, ColumnsDataSL, sizeof(ColumnsDataSL)/sizeof(TColumnsData), LocateStockSL, LS_MOVEPROD, true);
	MoveList->Name = L"MoveList";

	DateTimePicker1->MinDate = ShopUnit->LoadDateData;
	DateTimePicker2->MinDate = ShopUnit->LoadDateData;

	TDate dd = TDate::CurrentDate();
	DateTimePicker2->Date = dd;
	DateTimePicker2->Time = 0.999;
//	dd -= 0;
	DateTimePicker1->Date = dd;
	DateTimePicker1->Time = 0;

	MoveList->ColumnsCreat();
//	MoveList->FillList();

	AtomList->ColumnsCreat();
	AtomList->Clear();

	if(MoveList->ItemIndex != -1) {
		AtomList->FillList();
	}

//	DateTimePicker1Change(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::FillPersonsData(TMoveProduct *MoveProduct)
{
	EditSourceUnit->Text = MoveProduct->SourceUnit->Name;
	EditSourcePerson->Text = MoveProduct->SourcePerson->SumName;
	EditTargetUnit->Text = MoveProduct->TargetUnit->Name;
	EditTargetPerson->Text = MoveProduct->TargetPerson->SumName;
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::DateTimePicker1CloseUp(TObject *Sender)
{
	MoveList->FillList();
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::ButtonGroupListClick(TObject *Sender)
{
	FormGroupList->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ButtonProductListClick(TObject *Sender)
{
	FormProductList->CalledObj = TCalledObj::OBJ_OWNER;
	FormProductList->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ButtonBuyerListClick(TObject *Sender)
{
	FormBuyerList->CalledObj = TCalledObj::OBJ_OWNER;

	FormBuyerList->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::FormClose(TObject *Sender, TCloseAction &Action)
{
//	bCloseApplication = true;

	SlistConfig->Strings[ListConfParam::LCP_LANG] = iLang;
	SlistConfig->Strings[ListConfParam::LCP_SHOP] = uLastShopUnit;
	SlistConfig->Strings[ListConfParam::LCP_WORKER] = uLastWorkerName;
	SlistConfig->Strings[ListConfParam::LCP_GROUP] = uLastGroupProd;
	SlistConfig->SaveToFile(ExtractFilePath(Application->ExeName) + "Config.tshp");

	CurrentLog->Set(TabDB::TB_UNDEF, LOGS::LG_DISCONNECT, L" ");
	CurrentLog->InsertToDb(FDQuery1);    // Insert disconnect logs

	delete FDQuery1;

	try {
		FDConnection1->Connected = false;
	} catch (Exception &exception) {
		 ShowMessage("Disconnect to MySQL");
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::ButtonReportClick(TObject *Sender)
{
	FormReport->DateTimePicker1->DateTime = DateTimePicker1->DateTime;
	FormReport->DateTimePicker2->DateTime = DateTimePicker2->DateTime;

	FormReport->ShowModal();
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::TimerSyncTimer(TObject *Sender)
{
	TBaseData::SetTimerSync(false);

	TSynchronize::LoadFromDB(FDQuery1, ShopUnit->id, Worker->id);
	TSynchronize::ApplySinc();

	CurrentLog->UpdateToDb(FDQuery1);

#ifdef CHECK_SORT_ORDER
	if(TBuyer::VBuyers.size() > 0) {
		TBuyer::VBuyers[0]->CheckSortById();
	}
	if(TProvisioner::VProvisioners.size() > 0) {
		TProvisioner::VProvisioners[0]->CheckSortById();
	}
	if(TProduct::VProduct.size() > 0) {
		TProduct::VProduct[0]->CheckSortById();
	}
	if(TSelectProduct::VSelectProduct.size() > 0) {
		TSelectProduct::VSelectProduct[0]->CheckSortById();
	}
	if(TMoveProduct::VMoveProduct.size() > 0) {
		TMoveProduct::VMoveProduct[0]->CheckSortById();
	}
#endif

	TBaseData::SetTimerSync(true);
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ToolButtonOperatClick(TObject *Sender)
{
	bool bAccess = true;
	bDebtForm = false;

	if(((TToolButton*)Sender)->Name == L"ToolButtonView" || ((TMenuItem*)Sender)->Name == L"MenuView") {
		ButtonOperat = TButtonAction::BA_VIEW;
		bAccess = CheckAccess();
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonEdit" || ((TMenuItem*)Sender)->Name == L"MenuEdit") {
		ButtonOperat = TButtonAction::BA_EDIT;
		bAccess = CheckAccess();
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonSale" || ((TMenuItem*)Sender)->Name == L"MenuSale") {
		ButtonOperat = TButtonAction::BA_SALE;
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonReturn" || ((TMenuItem*)Sender)->Name == L"MenuReturn") {
		ButtonOperat = TButtonAction::BA_RETURN;
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonIncom" || ((TMenuItem*)Sender)->Name == L"MenuIncoming") {
		ButtonOperat = TButtonAction::BA_INCOM;
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonOut" || ((TMenuItem*)Sender)->Name == L"MenuOutgoing") {
		ButtonOperat = TButtonAction::BA_OUT;
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonRetDebt" || ((TMenuItem*)Sender)->Name == L"MenuRetDebt") {
		ButtonOperat = TButtonAction::BA_DEBT;
		FormMoveOther->ShowModal();
		return;
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonExpenses" || ((TMenuItem*)Sender)->Name == L"MenuExpenses") {
		ButtonOperat = TButtonAction::BA_EXP;
		FormMoveOther->ShowModal();
		return;
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonRetDebtProvis" || ((TMenuItem*)Sender)->Name == L"MenuDebtProvis") {
		ButtonOperat = TButtonAction::BA_DEBT_PROVIS;
		FormMoveOther->ShowModal();
		return;
	}
	else {
		return;
	}


	if(bAccess) {
		if(bDebtForm) {
			FormMoveOther->CalledObj = TCalledObj::OBJ_OWNER;
			FormMoveOther->ShowModal();
		} else {
			FormMoveProduct->CalledObj = TCalledObj::OBJ_OWNER;
			FormMoveProduct->ShowModal();
		}
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormShop::CheckAccess(void)
{
	if(MoveList->ItemIndex == -1) {
		Application->MessageBox(uShopSelectObject[iLang], uCaptionWarning[iLang], MB_OK);
		return false;
	}

	int index = MoveList->ipp[MoveList->ItemIndex];
	TMoveProduct *TmpMoveProd = TObjectManager<TMoveProduct>::GetList()[index];

	switch(TmpMoveProd->MoveType) {
		case TMoveType::MOV_DEBT:
		case TMoveType::MOV_EXP:
		case TMoveType::MOV_DEBT_PROVIS:
			bDebtForm = true;
			break;
		default:
			bDebtForm = false;
	}

	if(Worker->Privilege < TmpMoveProd->Privilege || ButtonOperat == TButtonAction::BA_VIEW) {
		return true;
	}


	switch(TmpMoveProd->MoveType) {
		case TMoveType::MOV_SALE:
		case TMoveType::MOV_OUT:
		case TMoveType::MOV_EXP:
		case TMoveType::MOV_DEBT_PROVIS:
			if(Worker->id == TmpMoveProd->SourcePerson->id) {
				return true;
			}
			break;
		case TMoveType::MOV_RET:
		case TMoveType::MOV_INC:
		case TMoveType::MOV_DEBT:
			if(Worker->id == TmpMoveProd->TargetPerson->id) {
				return true;
			}
			break;
		default:
            break;
	}
	ShowMessage(uShopPrivileg[iLang]);
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::EditSearchNameChange(TObject *Sender)
{
	MoveList->FillList();
	AtomList->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ToolButtonDeleteClick(TObject *Sender)
{
	ButtonOperat = TButtonAction::BA_UNKNOW;
	if(!CheckAccess()) {
		return;
	}

	if(Application->MessageBox(uShopDeleteRecord[iLang], uCaptionWarning[iLang], MB_YESNO) == IDYES) {

		FormMoveProduct->DeleteMoveProduct(TObjectManager<TMoveProduct>::GetList()[MoveList->ipp[MoveList->ItemIndex]]);

		TMoveProduct::CalcUnitsBalance();
		TMoveProduct::CalcDebts();

		MoveList->DeleteSelected();
		AtomList->Clear();

		FormBuyerList->bListUpdate = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ToolButtonShopUnitsClick(TObject *Sender)
{
	FormShopUnitsList->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ToolButtonProvisionersClick(TObject *Sender)
{
	FormProvisionerList->CalledObj = TCalledObj::OBJ_OWNER;

	FormProvisionerList->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ButtonPrintClick(TObject *Sender)
{
	if(MoveList->ItemIndex != -1) {
		FormPrint->PrintSale(MoveList->GetSelectMoveProduct());
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::MenuToolsSubClick(TObject *Sender)
{
	if(((TMenuItem*)Sender)->Name == L"MenuDumpDB") {
		BuckupDB();
	} else if(((TMenuItem*)Sender)->Name == L"MenuRestoreDB") {
		RestoreDB();
	} else if(((TMenuItem*)Sender)->Name == L"MenuCreateTablesDB") {
		CreateTables();
	} else if(((TMenuItem*)Sender)->Name == L"MenuSetLanguage") {
		FormLanguage->ShowModal();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::MenuAboutClick(TObject *Sender)
{
	FormAbout->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::MenuCloseClick(TObject *Sender)
{
	ToolButtonCloseClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ToolButtonLangClick(TObject *Sender)
{
	FormLanguage->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ToolButtonCloseClick(TObject *Sender)
{
	wchar_t Esc = VK_ESCAPE;
	FormKeyPress(Sender, Esc);
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ComboBoxUShopsChange(TObject *Sender)
{
	TSynchronize::bChangedAccess = true;

	int iLastIndex = uLastShopUnit.ToInt();

	uLastShopUnit = ComboBoxUShops->ItemIndex;
	FormUserStatus->ComboBoxShopUnits->Enabled = false;

	// save log data before change shop or worker
	CurrentLog->IdShop = ShopUnit->id;
	CurrentLog->IdWorker = Worker->id;
	CurrentLog->Set(TabDB::TB_UNDEF, LOGS::LG_DISCONNECT, L" ");

	FormUserStatus->ShowModal();

	if(FormUserStatus->bSuccess) {
		LabelUserStatus->Caption = TWorkers::PrivilegName[Worker->Privilege];
//		LabelUserName->Caption = Worker->SumName;

		ToolButtonEdit->Visible = false;
		ToolButtonDelete->Visible = false;
		ToolButtonProvisioners->Visible = false;
		ToolButtonIncom->Visible = false;
		ToolButtonOut->Visible = false;
		ToolButtonReports->Visible = false;
		MenuEdit->Visible = false;
		MenuDelete->Visible = false;
		MenuProvisioner->Visible = false;
		MenuIncoming->Visible = false;
		MenuOutgoing->Visible = false;
		MenuDumpDB->Visible = false;
		MenuRestoreDB->Visible = false;
		MenuCreateTablesDB->Visible = false;
		ColumnsDataSL[5].Visible = false;
		ColumnsDataAtom[4].Visible = false;
		ColumnsDataAtom[7].Visible = false;

		SetPrivileges();
		ToolButtonSeparator6->Width = ToolBar1->Width - ToolButtonMonitoring->Left - ToolButtonMonitoring->Width - ToolButtonClose->Width;


		TForm *Forms[] = {
			FormGroupList,
			FormBuyerList,
			FormProvisionerList,
			FormShopUnitsList
		};
		for(unsigned i=0; i < sizeof(Forms)/sizeof(TForm*); i++) {
			((TFormParent*)Forms[i])->DropVisibleStatus();
			((TFormParent*)Forms[i])->SetPrivileges();
			((TFormParent*)Forms[i])->SetPositionCloseButton();
		}
		FormProductList->ResetPriveleges();
		FormProductList->SetLanguage();
		FormMoveProduct->ClearToolBar();
		FormMoveProduct->SetPositionCloseButton();

//		SlistConfig->Strings[1] = FormUserStatus->ComboBoxShopUnits->ItemIndex;
//		SlistConfig->Strings[2] = FormUserStatus->EditLogin->Text;
		uLastShopUnit = FormUserStatus->ComboBoxShopUnits->ItemIndex;
		uLastWorkerName = FormUserStatus->EditLogin->Text;

		MoveList->FillList();

		CurrentLog->InsertToDb(FDQuery1);    // Insert disconnect logs
		CurrentLog->ConnectedId = -1;
		CurrentLog->IdShop = ShopUnit->id;
		CurrentLog->IdWorker = Worker->id;
		CurrentLog->Set(TabDB::TB_UNDEF, LOGS::LG_CONNECT, L" ");
		CurrentLog->InsertToDb(FDQuery1);    // Insert newconnect logs
		CurrentLog->ConnectedId = CurrentLog->id;
		CurrentLog->UpdateConnectedId(FDQuery1);

	} else {
		ComboBoxUShops->ItemIndex = iLastIndex;
		uLastShopUnit = iLastIndex;
	}

}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ToolButtonMonitoringClick(TObject *Sender)
{
//	FormLogs->ShowModal();
//	PopupMenu1->Popup(100, 100);
//	ShowMoveProductsInDynamicList(this);
	SaveMoveProductsToFixedFile();
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_ESCAPE) {
		if(Application->MessageBox(wExitMessage[iLang], uCaptionWarning[iLang], MB_YESNO) == IDYES) {
			AnsiString aTmp;

			aTmp = FDConnection1->Params->Database + "_SelectProduct.txt";
			TSelectProduct::SaveDataToFile(aTmp.c_str());

			aTmp = FDConnection1->Params->Database + "_Product.txt";
			TProduct::SaveDataToFile(aTmp.c_str());

			aTmp = FDConnection1->Params->Database + "_MoveProduct.txt";
			TMoveProduct::SaveDataToFile(aTmp.c_str());

			aTmp = FDConnection1->Params->Database + "_Buyers.txt";
			TBuyer::SaveDataToFile(aTmp.c_str());

			aTmp = FDConnection1->Params->Database + "_Provisioners.txt";
			TProvisioner::SaveDataToFile(aTmp.c_str());


			TFormEsc::FormKeyPress(Sender, Key);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ReloadDatabases1Click(TObject *Sender)
{
	TSelectProduct::LoadFromDB(FDQuery1, true);
	TProduct::LoadFromDB(FDQuery1, true);
}
//---------------------------------------------------------------------------
//#include <Vcl.ComCtrls.hpp>  // Для TListView
//#include "MoveProduct.h"
//#include "ObjectManager.h"

void __fastcall TFormShop::ShowMoveProductsInDynamicList(TComponent* Owner)
{
	// Создаём форму динамически
	TForm* floatingForm = new TForm(Owner);
	floatingForm->Caption = L"Список перемещений";
	floatingForm->BorderStyle = bsSizeable;
	floatingForm->Position = poScreenCenter;
	floatingForm->Width = 800;
	floatingForm->Height = 400;

	// Создаём ListView внутри формы
	TListView* lv = new TListView(floatingForm);
	lv->Parent = floatingForm;
	lv->Align = alClient;
	lv->ViewStyle = vsReport;

	lv->Left = 20;
	lv->Top = 20;
	lv->Width = 600;
	lv->Height = 300;

	// Вид отображения и стили
	lv->ViewStyle = vsReport;
	lv->GridLines = true;
	lv->RowSelect = true;
	lv->HideSelection = false;
	lv->FullDrag = true;
	lv->TabOrder = 0;

	// Добавляем колонки
	lv->Columns->Add()->Caption = "ID";
	lv->Columns->Add()->Caption = "Дата/Время";
	lv->Columns->Add()->Caption = "Оплата";
	lv->Columns->Add()->Caption = "Описание";
	lv->Columns->Add()->Caption = "Deleted";

	// Заполняем объектами из менеджера
	auto& list = TObjectManager<TMoveProduct>::GetList();
	for (size_t i = 0; i < list.size(); ++i)
	{
		TMoveProduct* move = list[i];
		if (!move) continue;

		TListItem* item = lv->Items->Add();
		item->Caption = IntToStr(move->id);
		item->SubItems->Add(move->DateTime.FormatString(L"dd.mm.yyyy hh:nn"));
		item->SubItems->Add(move->ActualPayment.StringFormat());
		item->SubItems->Add(move->Description);
		item->SubItems->Add(IntToStr(move->bDeleted));
	}

    floatingForm->Show();
}


//---------------------------------------------------------------------------
void TFormShop::SaveMoveProductsToFixedFile(void)
{
	UnicodeString uTmpMove;

	TStrings *Strings = new TStringList();

	// Заполняем объектами из менеджера
	auto& list = TObjectManager<TMoveProduct>::GetList();
	for (size_t i = 0; i < list.size(); ++i)
	{
		TMoveProduct* move = list[i];
		if (!move) continue;

		uTmpMove = L"";
		uTmpMove += IntToStr(move->id) + L"\t";
		uTmpMove += move->DateTime.FormatString(L"dd.mm.yyyy hh:nn") + L"\t";
		uTmpMove += move->ActualPayment.StringFormat() + L"\t";
		uTmpMove += IntToStr(move->bDeleted) + L"\t";

		Strings->Add(uTmpMove);
	}

	Strings->SaveToFile(L"_MoveProducts.txt");
}

