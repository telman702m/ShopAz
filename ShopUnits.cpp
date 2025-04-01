//---------------------------------------------------------------------------
#pragma hdrstop
#include "ShopUnits.h"
#include "Shop.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

const wchar_t *uShopLostConnectionUpdateStartDate[2] = {
	L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: Update start date for load data!\n Проверьте Интернет соединение.\n\n Повторить попытку?",
	L"MySql: Update start date for load data! Əməliyyət zamanı Məlumat Bazaynan əlagə kəsilib \n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};

UnicodeString uSeller[2] = {
	L"Покупатель",
	L"Alıcı"
};
UnicodeString uProvisioner[2] = {
	L"Поставщик",
	L"Təminatçı"
};
UnicodeString uExpenses[2] = {
	L"Прочие затраты",
	L"Digər xərclər"
};
UnicodeString UncertainShop[2] = {
	L"Неопределен",
	L"Qeyri-müəyyən"
};


/*const int CountFieldsShopUnits = 11;
wchar_t *ShopUnitsDbFields[CountFieldsShopUnits][2] =
   {{L"id",               L" Int(11) Not Null Auto_increment, "},
	{L"Name",	          L" Char(40) DEFAULT NULL, "},
	{L"Type",		      L" TINYINT(4) DEFAULT NULL, "},
	{L"Address", 	      L" Char(80) DEFAULT NULL, "},
	{L"Phone1",		      L" Char(24) DEFAULT NULL, "},
	{L"Phone2",		      L" Char(24) DEFAULT NULL, "},
	{L"Description",      L" Varchar(368) DEFAULT NULL, "},
	{L"Enable",		      L" SmallInt(1) DEFAULT NULL, "},
	{L"LastLoadDate",     L" DATE DEFAULT NULL, "},
	{L"Deleted",		  L" Smallint(1) "},
	{L"LastUpdate",	  	  L" TIMESTAMP CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, "}
   };*/

vector <TShopUnits*> TShopUnits::VShopUnits;
int* TShopUnits::upp;
int TShopUnits::CountUnits = 0;
TShopUnits* TShopUnits::Buyer;
TShopUnits* TShopUnits::Provisioner;
TShopUnits* TShopUnits::Expenses;
TShopUnits* TShopUnits::Empty;
UnicodeString TShopUnits::ShopNetName;

const wchar_t *TShopUnits::NameTableDB;
TDescFields **TShopUnits::ShopUnitsFieldsTableDB = NULL;
int TShopUnits::CountShopUnitsFieldsTableDB = 0;

//---------------------------------------------------------------------------
__fastcall TShopUnits::TShopUnits(void) : TPerson()
{
	VBaseData = (vector <TBaseData*> *)&VShopUnits;
	Clear();
}
//---------------------------------------------------------------------------
bool TShopUnits::GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB)
{
	NameTableDB =_NameTableDB;
	return GetFieldsFromDB(FDQuery, NameTableDB, ShopUnitsFieldsTableDB, CountShopUnitsFieldsTableDB);
}
//---------------------------------------------------------------------------
void __fastcall TShopUnits::Clear(void)
{
	TPerson::Clear();
	TypeUnit = TypeShopUnit::SHP_UNKNOW;
}
//---------------------------------------------------------------------------
__fastcall TShopUnits::TShopUnits(const TShopUnits &ShopUnits) : TPerson(ShopUnits)
{
	TypeUnit = ShopUnits.TypeUnit;
	LoadDateData = ShopUnits.LoadDateData;
}
//---------------------------------------------------------------------------
const TShopUnits& __fastcall TShopUnits::operator=(const TShopUnits &ShopUnits)
{
	TPerson::operator=(ShopUnits);
	TypeUnit = ShopUnits.TypeUnit;
	LoadDateData = ShopUnits.LoadDateData;
	return *this;
}

//---------------------------------------------------------------------------
void __fastcall TShopUnits::CreateBuyerUnit(void)
{
	Buyer = new TShopUnits();
	Buyer->Clear();
	Buyer->Name = uSeller[iLang];
}
//---------------------------------------------------------------------------
void __fastcall TShopUnits::CreateProvisionerUnit(void)
{
	Provisioner = new TShopUnits();
	Provisioner->Clear();
	Provisioner->Name = uProvisioner[iLang];
}
//---------------------------------------------------------------------------
void __fastcall TShopUnits::CreateExpensesUnit(void)
{
	Expenses = new TShopUnits();
	Expenses->Clear();
	Expenses->Name = uExpenses[iLang];
}
//---------------------------------------------------------------------------
void __fastcall TShopUnits::CreateEmptyUnit(void)
{
	Empty = new TShopUnits();
	Empty->Clear();
	Empty->Name = UncertainShop[iLang];
}
//---------------------------------------------------------------------------
void __fastcall TShopUnits::LoadShopNetNameFromDB(TMyFDQuery *FDQuery)
{
	FDQuery->SQL->Text = "Select * from Settings where id=1";
	bool bSuccess = false;

	while(!bSuccess) {
		try {
			FDQuery->Open();

			while(!FDQuery->Eof)
			{
				ShopNetName = FDQuery->FieldByName(L"Name")->AsString;
				FDQuery->Next();
			}
			FDQuery->Close();
			bSuccess = true;
	   } catch (...) {
			UnicodeString uTmp;
			uTmp.sprintf(wLostConnection[iLang], L"Select", L"Settings");
			if(Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}
}
//---------------------------------------------------------------------------
void __fastcall TShopUnits::LoadFromDB(TMyFDQuery *FDQuery)
{
	UnicodeString uTmp = "Select * from ";
	uTmp += NameTableDB;

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;

	while(!bSuccess) {
		try {
			FDQuery->Open();

			while(!FDQuery->Eof)
			{
				TShopUnits *TmpShopUnits = new TShopUnits();

				// Load data from MySql Data Base
				TmpShopUnits->id = FDQuery->FieldByName(ShopUnitsFieldsTableDB[0]->Field)->AsString.ToInt();
				TmpShopUnits->Name = FDQuery->FieldByName(ShopUnitsFieldsTableDB[1]->Field)->AsString;
				TmpShopUnits->TypeUnit = TypeShopUnit(FDQuery->FieldByName(ShopUnitsFieldsTableDB[2]->Field)->AsString.ToInt());
				TmpShopUnits->Address = FDQuery->FieldByName(ShopUnitsFieldsTableDB[3]->Field)->AsString;
				TmpShopUnits->Phone1 = FDQuery->FieldByName(ShopUnitsFieldsTableDB[4]->Field)->AsString;
				TmpShopUnits->Phone2 = FDQuery->FieldByName(ShopUnitsFieldsTableDB[5]->Field)->AsString;
				TmpShopUnits->Description = FDQuery->FieldByName(ShopUnitsFieldsTableDB[6]->Field)->AsString;
				TmpShopUnits->Enabled = FDQuery->FieldByName(ShopUnitsFieldsTableDB[7]->Field)->AsString.ToInt();
				TmpShopUnits->LoadDateData = FDQuery->FieldByName(ShopUnitsFieldsTableDB[8]->Field)->AsDateTime;

//				StrToDate(L"12.11.21", FSet);
//				if(uDate == L"") {
//					TmpShopUnits->LoadDateData = TDate::CurrentDate();
//				} else {
//					TmpShopUnits->LoadDateData = TFormShop::MyStrToDate(uDate);
//				}

				VShopUnits.push_back(TmpShopUnits);
				FDQuery->Next();
			}
			FDQuery->Close();

			bSuccess = true;
			CountUnits = VShopUnits.size();

	   } catch (...) {
			UnicodeString uTmp;
			uTmp.sprintf(wLostConnection[iLang], L"Select", NameTableDB);
			if(Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}

	// Create array for pointers
	upp = new int[VShopUnits.size()];
}
//---------------------------------------------------------------------------
void __fastcall TShopUnits::ArrangeUppArray(TShopUnits *ThisShopUnit)
{
	int ii = 1;
	bool bFind = false;

	for(unsigned i=0; i < VShopUnits.size(); i++) {
		if(VShopUnits[i]->Name == ThisShopUnit->Name) {
			upp[0] = i;
			bFind = true;
		} else {
			upp[ii++] = i;
		}
	}

	if(!bFind) {
		for(unsigned i=0; i < VShopUnits.size(); i++) {
			upp[i] = i;
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TShopUnits::InsertAtObjectToDb(TMyFDQuery *FDQuery)
{
	return;
}
//---------------------------------------------------------------------------
void __fastcall TShopUnits::SaveAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uShopUnitDbData[] = {
		L"",
		Name,
		TypeUnit,
		Address,
		Phone1,
		Phone2,
		Description,
		int(Enabled),
		LoadDateData.FormatString(L"yyyy-mm-dd hh:mm:ss")
	};
	TFieldsValues FieldsValues[] = {
		{ShopUnitsFieldsTableDB[1]->Field,		uShopUnitDbData[1].w_str()},
		{ShopUnitsFieldsTableDB[2]->Field,		uShopUnitDbData[2].w_str()},
		{ShopUnitsFieldsTableDB[3]->Field,		uShopUnitDbData[3].w_str()},
		{ShopUnitsFieldsTableDB[4]->Field,		uShopUnitDbData[4].w_str()},
		{ShopUnitsFieldsTableDB[5]->Field,		uShopUnitDbData[5].w_str()},
		{ShopUnitsFieldsTableDB[6]->Field, 	uShopUnitDbData[6].w_str()},
		{ShopUnitsFieldsTableDB[7]->Field, 	uShopUnitDbData[7].w_str()},
		{ShopUnitsFieldsTableDB[8]->Field, 	uShopUnitDbData[8].w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	UnicodeString uQuery = FormationUpdateString(NameTableDB, FieldsValues, Count);
	ExecSQL(FDQuery, uQuery, NameTableDB, TabDB::TB_UNDEF, TRecordType::RT_UNDEF, LOGS::LG_UNDEF);
}
//---------------------------------------------------------------------------
void __fastcall TShopUnits::DeleteObjectFromDb(TMyFDQuery *FDQuery)
{
	return;
}

//---------------------------------------------------------------------------
TShopUnits* __fastcall TShopUnits::GetUnitById(int id)
{
	unsigned Count = VShopUnits.size();

	for(unsigned i=0; i < Count; i++) {
		if(VShopUnits[i]->id == id) {
			return VShopUnits[i];
		}
	}
	return NULL;
}
//---------------------------------------------------------------------------
int __fastcall TShopUnits::GetIndexUnitById(int id)
{
	unsigned Count = VShopUnits.size();

	for(unsigned i=0; i < Count; i++) {
		if(VShopUnits[i]->id == id) {
			return i;
		}
	}
	return -1;
}

//---------------------------------------------------------------------------
void __fastcall TShopUnits::UpdateStartDate(TMyFDQuery *FDQuery, TDate NewDate, int id)
{
	UnicodeString uTmp;
	uTmp.sprintf(L"Update %s Set LastLoadDate = '%s' Where id = %d", NameTableDB, NewDate.FormatString(L"yyyy-mm-dd").w_str(), id);

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;

	while(!bSuccess) {
		try {
			FDQuery->Execute();
			bSuccess = true;

	   } catch (...) {
			if(Application->MessageBox(uShopLostConnectionUpdateStartDate[iLang], uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}
}
//---------------------------------------------------------------------------
bool __fastcall TShopUnits::LoadRecordId(TMyFDQuery *FDQuery)
{
	return true;
}
//---------------------------------------------------------------------------


