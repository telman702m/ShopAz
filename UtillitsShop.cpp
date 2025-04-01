//---------------------------------------------------------------------------
#pragma hdrstop

#include "Shop.h"
#include "GroupProduct.h"
#include "Product.h"
#include "Buyer.h"
#include "MoveProduct.h"
#include "Provisioner.h"
#include "ShopUnits.h"
#include "Workers.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

const wchar_t *uUtillitLostConnectionCreate[2] = {
	L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: Create table Balance!\n Проверьте Интернет соединение.\n\n Повторить попытку?",
	L"MySql: Create table Balance! Əməliyyət zamanı Məlumat Bazaynan əlagə kəsilib \n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};
const wchar_t *uUtillitLostConnectionDumpDB[2] = {
	L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: Dump Backup Database!\n Проверьте Интернет соединение.\n\n Повторить попытку?",
	L"MySql: Dump Backup Database! Əməliyyət zamanı Məlumat Bazaynan əlagə kəsilib \n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};
const wchar_t *uUtillitLostConnectionRestorDB[2] = {
	L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: Restore Database!\n Проверьте Интернет соединение.\n\n Повторить попытку?",
	L"MySql: Restore Database! Əməliyyət zamanı Məlumat Bazaynan əlagə kəsilib \n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};
const wchar_t *uUtillitBuckedDB[2] = {
	L"Создана резервная копия Базы Данных.",
	L"Məlumat Bazasının ehtiyat kopiyası yaradılmışdır."
};
const wchar_t *uUtillitRestoredDB[2] = {
	L"Текущая База Данных будет восстановлена (заменена) из файла %s. Данные текущей БД будут утеряны. Приложение будет перезагружено. Продолжить?",
	L"Mövcüd Məlumat Bazası %s fayldan bərpa olunacaq (dəyişiləcək). Mövcüd MB-nın informasiyası itəcək. Program restart olunacaq. Davam etmək?",
};


//---------------------------------------------------------------------------
void __fastcall TFormShop::CreateTables(void)
{
//	MyXML::CreateTableSettings(MyQuery1);      // Settings Table

/*
	TShopUnits::CreateTable(MyQuery1);         // Таблица персон
	TWorkers::CreateTable(MyQuery1);           // Таблица персон
	TGroupProduct::CreateTable(MyQuery1);      // Таблица групп товаров
	TProduct::CreateTable(MyQuery1);           // Таблица товаров
	TBuyer::CreateTable(MyQuery1);             // Таблица персон
	TProvisioner::CreateTable(MyQuery1);       // Таблица персон
	TMoveProduct::CreateTable(MyQuery1);       // Таблица операций продаж и приема
	TSelectProduct::CreateTable(MyQuery1);     // Таблица выбранных товаров в операциях продаж, приема, возврата

	TSynchronize::CreateTable(MyQuery1);       // Таблица Synchronize

    CreateTableBalance();*/
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::CreateTableBalance(void)
{
UnicodeString uTmp =
	L"CREATE TABLE If Not Exists `Balance` ("
	L"`id` int(11) NOT NULL AUTO_INCREMENT,"
	L"`idProduct` int(11) DEFAULT NULL,"
	L"`idShop` int(11) DEFAULT NULL,"
	L"`Count1` int(8) DEFAULT '0',"
	L"`Count2` int(6) DEFAULT '0',"
	L"PRIMARY KEY (`id`),"
	L"KEY `idx_Balance_idProduct` (`idProduct`),"
	L"KEY `idx_Balance_idShop` (`idShop`)"
	L") ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=ucs2";

	FDQuery1->SQL->Text = uTmp;

	bool bSuccess = false;

	while(!bSuccess) {
		try {
			FDQuery1->Execute();
			bSuccess = true;
	   } catch (...) {
			if(Application->MessageBox(uUtillitLostConnectionCreate[iLang], uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::BuckupDB(void)
{
/*	TDate DTBuckup;
	DTBuckup = DTBuckup.CurrentDateTime();
	UnicodeString uFileBuckup;
	uFileBuckup.sprintf(L"BackupPrefix_%s.sql", DTBuckup.FormatString(L"yyyy-mm-dd_hh-mm-ss").c_str());

	bool bSuccess = false;

	while(!bSuccess) {
		try {
			MyDump1->BackupToFile(uFileBuckup);

			bSuccess = true;
	   } catch (...) {

			if(Application->MessageBox(uUtillitLostConnectionDumpDB[iLang], uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}
	MyDump1->BackupToFile(uFileBuckup);

	if(!IsDebuggerPresent()) {
		Application->MessageBox(uUtillitBuckedDB[iLang], uCaptionInform[iLang], MB_OK);
	} */
}

//---------------------------------------------------------------------------
void __fastcall TFormShop::RestoreDB(void)
{
/*	FileOpenDlgRestorDB->DefaultFolder = ExtractFilePath(Application->ExeName);
	if(FileOpenDlgRestorDB->Execute()) {
		UnicodeString uTmp;
		uTmp.sprintf(uUtillitRestoredDB[iLang], FileOpenDlgRestorDB->FileName.c_str());

		if(Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_YESNO) == IDYES) {
			MyDump1->Connection = FDConnection1;
			try {
				MyDump1->RestoreFromFile(FileOpenDlgRestorDB->FileName);
			} catch (...) {
				ShowMessage(uUtillitLostConnectionRestorDB[iLang]);
			}
		}
	} */
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::ClearFilesSQL(void)
{
	// Clear excess files from folder
	TDateTime DateNow = TDateTime::CurrentDate();
	vector <TSearchRec> vBakFiles;

	UnicodeString uPath = ExtractFilePath(Application->ExeName) + L"*.sql";
	TSearchRec sr;
	int iAttributes = faArchive;

	int done = FindFirst(uPath, iAttributes, sr);
	while(!done) {
		vBakFiles.push_back(sr);
		done = FindNext(sr);
	}
	FindClose(sr);

	// Cycle on Months
	for(int i=1; i < 12; i++) {
		bool bFinded = false;
		TDateTime CompareDate = IncMonth(DateNow, -i);
		unsigned short DayComp, MonthComp, YearComp;
		CompareDate.DecodeDate(&YearComp, &MonthComp, &DayComp);

		for(unsigned i=0; i < vBakFiles.size(); i++) {
			TDateTime DateFile = FileDateToDateTime(vBakFiles[i].TimeStamp);

			unsigned short DayFile, MonthFile, YearFile;
			DateFile.DecodeDate(&YearFile, &MonthFile, &DayFile);

			if(YearFile == YearComp && MonthFile == MonthComp) {
				if(bFinded) {
					DeleteFile(vBakFiles[i].Name);
				} else {
					bFinded = true;
                }
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormShop::SetLanguage(void)
{
//	MyXML::ApplayLangClick(MyQuery1);
}

//	String __fastcall PrintMACaddress(BYTE *addr);
//	String __fastcall GetMACaddress();
//---------------------------------------------------------------------------
/*	FormShop->MyQuery1->SQL->Text = L"set @Balance = 0; call Balance(3, 1347, @Balance); select @Balance;";
	FormShop->MyQuery1->Open();

	while(!FormShop->MyQuery1->Eof) {
		Edit1->Text = FormShop->MyQuery1->FieldByName(L"@Balance")->AsString;
		FormShop->MyQuery1->Next();
	}
	FormShop->MyQuery1->Close(); */

//---------------------------------------------------------------------------

/*
//---------------------------------------------------------------------------
String __fastcall TFormShop::PrintMACaddress(BYTE *addr)
{
  String result = "";
  for (int i = 0; i < 6; ++i)
	result += IntToHex(*addr++, 2) + ((i < 5) ? "-" : "\n");
  return result;
}
//---------------------------------------------------------------------------
String __fastcall TFormShop::GetMACaddress()
{
  IP_ADAPTER_INFO AdapterInfo[16];        // информация о 16 адаптерах макс
  DWORD dwBufLen = sizeof (AdapterInfo);  // кол-во байт в буффере

  DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
  if (dwStatus != ERROR_SUCCESS)
  {
	ShowMessage("GetAdaptersInfo failed. err=" + String(GetLastError()));
	return 0;
  }

  PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;  // информация о текущем адаптере
  String address = "";
  while (pAdapterInfo)                          // пока есть информация об адаптерах
  {
	if (pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET)
	{
	  address = PrintMACaddress(pAdapterInfo->Address);  // печатаем MAC
//      break;
	}
	pAdapterInfo = pAdapterInfo->Next;  // переходим к информации о следующем адаптере
  }

  return address;
}
//---------------------------------------------------------------------------
*/
