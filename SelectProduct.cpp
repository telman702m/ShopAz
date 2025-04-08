//---------------------------------------------------------------------------
#pragma hdrstop

#include "SelectProduct.h"
#include "Shop.h"
#include "Synchronize.h"
#include "UnitProgressBar.h"
#include "MoveProduct.h"
#include "TUtills.h"
#include <time.h>

#pragma package(smart_init)

const wchar_t *uSPIncorrectData[2] = {
	L"Некорректные данные в объекте [SelectProduct]! Запись в Базу Данных не будет осуществлен.",
	L"[SelectProduct] obyektda yalnış məlumatlar mövcüddür! İnformasiya Məlumat Bazada saxlanmıyacaq."
};
const wchar_t *uLostProduct[2] = {
	L"Объект [SelectProduct] ссылается на несуществующий товар!\nУдалить данный объект из Базы Данных?",
	L"[SelectProduct] obyekt mövcüd olmayan mala istinad edir!\nBu obyektı Məlumat Bazadan silinsin?"
};
const wchar_t *uLostSelectProduct[2] = {
	L"Объект [SelectProduct] отсутствует в какой либо операции!\nУдалить данный объект из Базы Данных?",
	L"[SelectProduct] obyekt mövcüd deyil hər hansı bir əməliyyətdə!\nBu obyektı Məlumat Bazadan silinsin?"
};

UnicodeString ProgressLoadSP[2] = {
	L"Загрузка данных о \"Товарах внутри операций\" с сервера",
	L"Serverdən \"Əməliyyətlərdə daxil olan mallar\" haqqında məlumatın yüklənməsi"
};


const double MIN_DATE_TIME = 25570.;    // 1970-01-02 00:00:00

int TSelectProduct::LastIdDb = 0;
bool TSelectProduct::bLoaded = false;
vector <TSelectProduct*> TSelectProduct::VSelectProduct;

const wchar_t *TSelectProduct::NameTableDB;
TDescFields **TSelectProduct::SelectProdFieldsTableDB = NULL;
int TSelectProduct::CountSelectProdFieldsTableDB = 0;

//---------------------------------------------------------------------------
__fastcall TSelectProduct::TSelectProduct(void) : TBaseData()
{
	VBaseData = (vector <TBaseData*> *)&VSelectProduct;
	Clear();
}
//---------------------------------------------------------------------------
__fastcall TSelectProduct::~TSelectProduct(void)
{
//
}

//---------------------------------------------------------------------------
bool TSelectProduct::GetFieldsDB(TMyFDQuery *FDQuery, const wchar_t *_NameTableDB)
{
	NameTableDB = _NameTableDB;
	return GetFieldsFromDB(FDQuery, NameTableDB, SelectProdFieldsTableDB, CountSelectProdFieldsTableDB);
}
//---------------------------------------------------------------------------
void __fastcall TSelectProduct::Clear(void)
{
	idMove = -1;                 			// id  on Sale
	SelectDateTime = MIN_DATE_TIME;   		// Time of selected product
	idProduct = -1;   			        	// idProduct
	IncomingPrice = 0;          			// Incoming Price product
	Price = 0;  							// Price product
	Count = 0;  		               		// Count Products

	Product = NULL;
	TotalPrice = 0;
	TotalCostPrice = 0;
}
//---------------------------------------------------------------------------
__fastcall TSelectProduct::TSelectProduct(const TSelectProduct &SelectProduct) : TBaseData(SelectProduct)
{
	idMove = SelectProduct.idMove;
	SelectDateTime = SelectProduct.SelectDateTime;
	idProduct = SelectProduct.idProduct;
	IncomingPrice = SelectProduct.IncomingPrice;
	Price = SelectProduct.Price;
	Count = SelectProduct.Count;

	Product = SelectProduct.Product;
	TotalPrice = SelectProduct.TotalPrice;
	TotalCostPrice = SelectProduct.TotalCostPrice;
}
//---------------------------------------------------------------------------
const TSelectProduct& __fastcall TSelectProduct::operator=(const TSelectProduct &SelectProduct)
{
	TBaseData::operator=(SelectProduct);
	idMove = SelectProduct.idMove;
	SelectDateTime = SelectProduct.SelectDateTime;
	idProduct = SelectProduct.idProduct;
	IncomingPrice = SelectProduct.IncomingPrice;
	Price = SelectProduct.Price;
	Count = SelectProduct.Count;

	Product = SelectProduct.Product;
	TotalPrice = SelectProduct.TotalPrice;
	TotalCostPrice = SelectProduct.TotalCostPrice;

	return *this;
}

//---------------------------------------------------------------------------
bool __fastcall TSelectProduct::CheckCorrectData(void)
{
	if(TProduct::GetProductById(idProduct) == NULL) {
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------
void __fastcall TSelectProduct::InsertAtObjectToDb(TMyFDQuery *FDQuery)
{
	if(!CheckCorrectData()) {
		Application->MessageBox(uSPIncorrectData[iLang], uCaptionError[iLang], MB_OK);
		return;
	}

	UnicodeString uSelectDbData[] = {
		L"",
		idMove,
		SelectDateTime.FormatString(L"yyyy-mm-dd hh:mm:ss"),
		idProduct,
		IncomingPrice.GetMoney(),
		IncomingPrice.GetCent(),
		Price.GetMoney(),
		Price.GetCent(),
		Count.GetWhole(),
		Count.GetFractional()
	};
	TFieldsValues FieldsValues[] = {
		{SelectProdFieldsTableDB[1]->Field,		uSelectDbData[1].w_str()},
		{SelectProdFieldsTableDB[2]->Field,		uSelectDbData[2].w_str()},
		{SelectProdFieldsTableDB[3]->Field,		uSelectDbData[3].w_str()},
		{SelectProdFieldsTableDB[4]->Field,		uSelectDbData[4].w_str()},
		{SelectProdFieldsTableDB[5]->Field,		uSelectDbData[5].w_str()},
		{SelectProdFieldsTableDB[6]->Field, 	uSelectDbData[6].w_str()},
		{SelectProdFieldsTableDB[7]->Field, 	uSelectDbData[7].w_str()},
		{SelectProdFieldsTableDB[8]->Field, 	uSelectDbData[8].w_str()},
		{SelectProdFieldsTableDB[9]->Field, 	uSelectDbData[9].w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	ExecSQL(FDQuery, FieldsValues, Count, NameTableDB, SelectProdFieldsTableDB[0]->Field, TabDB::TB_SELECTP);
}
//---------------------------------------------------------------------------
void __fastcall TSelectProduct::SaveAtObjectToDb(TMyFDQuery *FDQuery)
{
	UnicodeString uSelectDbData[] = {
		L"",
		idMove,
		SelectDateTime.FormatString(L"yyyy-mm-dd hh:mm:ss"),
		idProduct,
		IncomingPrice.GetMoney(),
		IncomingPrice.GetCent(),
		Price.GetMoney(),
		Price.GetCent(),
		Count.GetWhole(),
		Count.GetFractional()
	};
	TFieldsValues FieldsValues[] = {
		{SelectProdFieldsTableDB[1]->Field,		uSelectDbData[1].w_str()},
		{SelectProdFieldsTableDB[2]->Field,		uSelectDbData[2].w_str()},
		{SelectProdFieldsTableDB[3]->Field,		uSelectDbData[3].w_str()},
		{SelectProdFieldsTableDB[4]->Field,		uSelectDbData[4].w_str()},
		{SelectProdFieldsTableDB[5]->Field,		uSelectDbData[5].w_str()},
		{SelectProdFieldsTableDB[6]->Field, 	uSelectDbData[6].w_str()},
		{SelectProdFieldsTableDB[7]->Field, 	uSelectDbData[7].w_str()},
		{SelectProdFieldsTableDB[8]->Field, 	uSelectDbData[8].w_str()},
		{SelectProdFieldsTableDB[9]->Field, 	uSelectDbData[9].w_str()}
	};
	int Count = sizeof(FieldsValues)/sizeof(TFieldsValues);

	UnicodeString uQuery = FormationUpdateString(NameTableDB, FieldsValues, Count);
	ExecSQL(FDQuery, uQuery, NameTableDB, TabDB::TB_SELECTP, TRecordType::RT_UPDATE, LOGS::LG_UPDATE);
}

//---------------------------------------------------------------------------
void __fastcall TSelectProduct::DeleteObjectFromDb(TMyFDQuery *FDQuery)
{
	UnicodeString uQuery = FormationDeleteString(NameTableDB, SelectProdFieldsTableDB[10]->Field);
	ExecSQL(FDQuery, uQuery, NameTableDB, TabDB::TB_SELECTP, TRecordType::RT_DELETE, LOGS::LG_DELETE);
}

//---------------------------------------------------------------------------
bool __fastcall TSelectProduct::SaveDataToFile(char *FileNmae)
{
	FILE *fs = fopen(FileNmae, "wt");
	if(fs == NULL) {
		return false;
	}
	fseek(fs, 0, SEEK_SET);

	fwprintf(fs, L"'%s'\n", TDateTime::CurrentDate().FormatString(L"dd.mm.yyyy").w_str());

	for(unsigned i=0; i < VSelectProduct.size(); i++) {
		fwprintf(fs, L"'%d'\t'%d'\t'%s'\t'%d'\t'%d'\t'%d'\t'%d'\t'%d'\t'%d'\t'%d'\t'%d'\n",
					 VSelectProduct[i]->id,
					 VSelectProduct[i]->idMove,
					 VSelectProduct[i]->SelectDateTime.FormatString(L"dd.mm.yyyy hh:nn:ss").w_str(),
					 VSelectProduct[i]->idProduct,
					 VSelectProduct[i]->IncomingPrice.GetMoney(),
					 VSelectProduct[i]->IncomingPrice.GetCent(),
					 VSelectProduct[i]->Price.GetMoney(),
					 VSelectProduct[i]->Price.GetCent(),
					 VSelectProduct[i]->Count.GetWhole(),
					 VSelectProduct[i]->Count.GetFractional(),
					 VSelectProduct[i]->bDeleted);
	}

	fclose(fs);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSelectProduct::LoadDataFromFile(char *FileName)
{
	if(!LoadFileToBuffer(FileName)) {
		return false;
	}

	UnicodeString uTmp;
	int CountParseFields = CountSelectProdFieldsTableDB - 1;

	while(Offset < FileSize) {

		Offset += TUtills::ParseString(FileBuffer + Offset, pws, CountParseFields, FileSize - Offset);
		if(Offset == 0) {
			delete FileBuffer;
			FileBuffer = NULL;
			return false;
		}

		TSelectProduct *TmpSelectProduct = new TSelectProduct();

		uTmp = pws[0];
		TmpSelectProduct->id = uTmp.ToInt();
		uTmp = pws[1];
		TmpSelectProduct->idMove = uTmp.ToInt();
		uTmp = pws[2];
		TmpSelectProduct->SelectDateTime = StrToDateTime(uTmp, FSet);
		uTmp = pws[3];
		TmpSelectProduct->idProduct = uTmp.ToInt();
		uTmp = pws[4];
		TmpSelectProduct->IncomingPrice.SetMoney(uTmp.ToInt());
		uTmp = pws[5];
		TmpSelectProduct->IncomingPrice.SetCent(uTmp.ToInt());
		uTmp = pws[6];
		TmpSelectProduct->Price.SetMoney(uTmp.ToInt());
		uTmp = pws[7];
		TmpSelectProduct->Price.SetCent(uTmp.ToInt());
		uTmp = pws[8];
		TmpSelectProduct->Count.SetWhole(uTmp.ToInt());
		uTmp = pws[9];
		TmpSelectProduct->Count.SetFractional(uTmp.ToInt());
		uTmp = pws[10];
		TmpSelectProduct->bDeleted = uTmp.ToInt();

		if(TmpSelectProduct->id > LastIdDb) {
			LastIdDb = TmpSelectProduct->id;
		}

		if(TmpSelectProduct->bDeleted) {
            continue;
        }
		// additional fields
		TmpSelectProduct->Product = TProduct::GetProductById(TmpSelectProduct->idProduct);
		if(TmpSelectProduct->Product == NULL) {
			if(Application->MessageBox(uLostProduct[iLang], uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == idYes) {
				TmpSelectProduct->DeleteObjectFromDb(FormShop->FDQuery1);
			}
			continue;
		}

		int indexMove = GetArrayIndexById((vector <TBaseData*> *)&TMoveProduct::VMoveProduct, TmpSelectProduct->idMove);
		if(indexMove != -1) {
			TmpSelectProduct->CalcTotalPrice();
			VSelectProduct.push_back(TmpSelectProduct);

			if(TmpSelectProduct->bDeleted == TMoveProduct::VMoveProduct[indexMove]->bDeleted) {
				TMoveProduct::VMoveProduct[indexMove]->VSelectedProd.push_back(TmpSelectProduct);
				TMoveProduct::VMoveProduct[indexMove]->CalcTotalPrice();
			}
/*		} else {
			// delete this record from DB
			if(Application->MessageBox(uLostSelectProduct[iLang], uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == idYes) {
				TmpSelectProduct->DeleteObjectFromDb(FormShop->FDQuery1);
			} else {
				TmpSelectProduct->CalcTotalPrice();
				VSelectProduct.push_back(TmpSelectProduct);
			} */
		}
	}

	delete FileBuffer;
	FileBuffer = NULL;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TSelectProduct::LoadFromDB(TMyFDQuery *FDQuery, bool bLoadAll)
{
	VSelectProduct.clear();

	if(!bLoadAll) {
		AnsiString aTmp = FormShop->FDConnection1->Params->Database + "_SelectProduct.txt";
		bLoadAll = !LoadDataFromFile(aTmp.c_str());
	}

	UnicodeString uFields;
	int CountFields = 11;

	for(int i=0; i < CountFields; i++) {
		uFields += SelectProdFieldsTableDB[i]->Field;
		if(i < CountFields - 1) {
			uFields += L",";
		}
	}

	UnicodeString uTmp = "Select " + uFields + " from ";
	uTmp += NameTableDB;
	uTmp += L" where DateTime >= '";
	uTmp += FormShop->ShopUnit->LoadDateData.FormatString("yyyy-mm-dd");

	if(bLoadAll) {
//		uTmp += L"' and Deleted = '0'";
		uTmp += L"'";
	} else {
		uTmp += L"' and LastUpdate > '" + MaxUpdateDate.FormatString("yyyy-mm-dd") + L"'";
	}

	FDQuery->SQL->Text = uTmp;

	bool bSuccess = false;
	int iDel;

	TimerSyncDisable();

	while(!bSuccess) {
		try {
			FormProgressBar->Show();
			FormProgressBar->Label1->Caption = ProgressLoadSP[iLang];
			FormProgressBar->Update();
			FormProgressBar->Label1->Left = (FormProgressBar->ClientWidth - FormProgressBar->Label1->Width)/2;
			FormProgressBar->ProgressBar1->Position = 0;
			FormProgressBar->Update();
			FDQuery->Open();
            FDQuery->FetchAll();
			FormProgressBar->ProgressBar1->Max = FDQuery->RecordCount;

			while (!FDQuery->Eof)
			{
				TSelectProduct *TmpSelectProduct = new TSelectProduct();

				// Load data from MySql Data Base
				TmpSelectProduct->id = FDQuery->FieldByName(SelectProdFieldsTableDB[0]->Field)->AsString.ToInt();
				TmpSelectProduct->idMove = FDQuery->FieldByName(SelectProdFieldsTableDB[1]->Field)->AsString.ToInt();
				TmpSelectProduct->SelectDateTime = FDQuery->FieldByName(SelectProdFieldsTableDB[2]->Field)->AsDateTime;
				TmpSelectProduct->idProduct = FDQuery->FieldByName(SelectProdFieldsTableDB[3]->Field)->AsString.ToInt();
				TmpSelectProduct->IncomingPrice.SetMoney(FDQuery->FieldByName(SelectProdFieldsTableDB[4]->Field)->AsString.ToInt());
				TmpSelectProduct->IncomingPrice.SetCent(FDQuery->FieldByName(SelectProdFieldsTableDB[5]->Field)->AsString.ToInt());
				TmpSelectProduct->Price.SetMoney(FDQuery->FieldByName(SelectProdFieldsTableDB[6]->Field)->AsString.ToInt());
				TmpSelectProduct->Price.SetCent(FDQuery->FieldByName(SelectProdFieldsTableDB[7]->Field)->AsString.ToInt());
				TmpSelectProduct->Count.SetWhole(FDQuery->FieldByName(SelectProdFieldsTableDB[8]->Field)->AsString.ToInt());
				TmpSelectProduct->Count.SetFractional(FDQuery->FieldByName(SelectProdFieldsTableDB[9]->Field)->AsString.ToInt());
				TmpSelectProduct->bDeleted = FDQuery->FieldByName(SelectProdFieldsTableDB[10]->Field)->AsString.ToInt();

				if(TmpSelectProduct->id > LastIdDb) {
					LastIdDb = TmpSelectProduct->id;
				}
				// additional fields
				TmpSelectProduct->Product = TProduct::GetProductById(TmpSelectProduct->idProduct);
				if(TmpSelectProduct->Product == NULL) {
//					TmpSelectProduct->DeleteObjectFromDb(FormShop->MyQuery2);
					FDQuery->Next();
					continue;
				}


				bool bPushed = false;

				if(bLoadAll) {
					TmpSelectProduct->CalcTotalPrice();
					VSelectProduct.push_back(TmpSelectProduct);
					bPushed = true;
				} else {
					int iIndex = TmpSelectProduct->GetArrayIndexById();

					if(TmpSelectProduct->bDeleted) {
//						if(iIndex != -1) {
//							VSelectProduct.erase(VSelectProduct.begin() + iIndex);
//						}
					} else {
						if(iIndex == -1) {
							TmpSelectProduct->CalcTotalPrice();

							int InsertIndex = TmpSelectProduct->GetArrayIndexById(true);
							VSelectProduct.insert(VSelectProduct.begin()+InsertIndex, TmpSelectProduct);
							bPushed = true;
						}

					}
				}

				if(bPushed) {
					int indexMove = GetArrayIndexById((vector <TBaseData*> *)&TMoveProduct::VMoveProduct, TmpSelectProduct->idMove);
					if(indexMove != -1) {
						if(TmpSelectProduct->bDeleted == TMoveProduct::VMoveProduct[indexMove]->bDeleted) {
							TMoveProduct::VMoveProduct[indexMove]->VSelectedProd.push_back(TmpSelectProduct);
							TMoveProduct::VMoveProduct[indexMove]->CalcTotalPrice();
						}
					} else {
                    	// delete this record from DB
					}
				}

				FDQuery->Next();

				FormProgressBar->ProgressBar1->Position++;
				FormProgressBar->Update();
			}
			LastIdDb++;
			FDQuery->Close();
			FormProgressBar->Close();

			bSuccess = true;

	   } catch (...) {
			FormProgressBar->Close();

			UnicodeString uTmp = uTmp.sprintf(wLostConnection[iLang], L"Select", NameTableDB);
			if(Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
	   }
	}
	bLoaded = true;

	if(FormProgressBar->Showing) {
		FormProgressBar->Close();
	}

	TimerSyncRestore();
}
//---------------------------------------------------------------------------
bool __fastcall TSelectProduct::LoadRecordId(TMyFDQuery *FDQuery)
{
	UnicodeString *uSelectProdDbData = new UnicodeString[CountSelectProdFieldsTableDB - 2];
	if(LoadRecord(FDQuery, NameTableDB, SelectProdFieldsTableDB, uSelectProdDbData, CountSelectProdFieldsTableDB)) {
		id = uSelectProdDbData[0].ToInt();
		idMove = uSelectProdDbData[1].ToInt();
		SelectDateTime = uSelectProdDbData[2];
		idProduct = uSelectProdDbData[3].ToInt();
		IncomingPrice.SetMoney(uSelectProdDbData[4].ToInt());
		IncomingPrice.SetCent(uSelectProdDbData[5].ToInt());
		Price.SetMoney(uSelectProdDbData[6].ToInt());
		Price.SetCent(uSelectProdDbData[7].ToInt());
		Count.SetWhole(uSelectProdDbData[8].ToInt());
		Count.SetFractional(uSelectProdDbData[9].ToInt());

		// additional fields
		Product = TProduct::GetProductById(idProduct);
		if(Product == NULL) {
			ShowMessage(L"Synchronize: Product in SelectProduct object not found in DB");
			delete[] uSelectProdDbData;
			return false;
		}
		CalcTotalPrice();
		UpdateMoveProduct();

		delete[] uSelectProdDbData;
		return true;
	} else {
		delete[] uSelectProdDbData;
		return false;
	}
}

//---------------------------------------------------------------------------
void __fastcall TSelectProduct::UpdateMoveProduct(void)
{
	int IndexMove = TMoveProduct::GetArrayIndexById((vector <TBaseData*> *)&TMoveProduct::VMoveProduct, idMove);

	if(IndexMove != -1) {
		TMoveProduct::VMoveProduct[IndexMove]->VSelectedProd.push_back(this);
		TMoveProduct::VMoveProduct[IndexMove]->CalcTotalPrice();

		TMoveProduct::CalcUnitsBalance();
		TMoveProduct::CalcDebts();
	}
}

//---------------------------------------------------------------------------
void __fastcall TSelectProduct::CalcTotalPrice(void)
{
	TotalPrice = Price * Count;
	TotalCostPrice = IncomingPrice * Count;
}

//---------------------------------------------------------------------------
void __fastcall TSelectProduct::DeleteObject(TSelectProduct *SelProd)
{
	unsigned Count = VSelectProduct.size();

	for(unsigned i=0; i < Count; i++) {
		if(VSelectProduct[i] == SelProd) {
			VSelectProduct.erase(VSelectProduct.begin() + i);
			return;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSelectProduct::CheckExcessObjects(void)
{
	int CountSelectProd = VSelectProduct.size();
	int CountExcess = 0;

	for(int i=0; i < CountSelectProd; i++) {
		if(GetArrayIndexById((vector <TBaseData*> *)&TMoveProduct::VMoveProduct, VSelectProduct[i]->idMove) == -1) {
//			ShowMessage(L"Excess SelectProduct object");
			CountExcess++;
		}
	}
	UnicodeString uTmp = L"CountExcess = ";
	uTmp += CountExcess;
	ShowMessage(uTmp);
}
//---------------------------------------------------------------------------

