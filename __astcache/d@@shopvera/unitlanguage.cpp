//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitLanguage.h"
#include "Shop.h"
#include "MoveProduct.h"
#include "Provisioner.h"
#include "UnitProduct.h"
#include "UnitProductList.h"
#include "UnitGroupList.h"
#include "GroupProduct.h"
#include "UnitGroupProduct.h"
#include "UnitMoveProduct.h"
#include "UnitMoveOther.h"
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
#include "UnitShopUnitData.h"
#include "UnitProvisionerData.h"
#include "UnitProgressBar.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormLanguage *FormLanguage;
//---------------------------------------------------------------------------
__fastcall TFormLanguage::TFormLanguage(TComponent* Owner)
	: TFormEsc(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormLanguage::ButtonCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormLanguage::ButtonOkClick(TObject *Sender)
{
	if(ComboBoxLang->ItemIndex == -1) {
		ShowMessage(L"Выберите из списка язык программы!\nSiyahıdan program dilini seçin!");
	} else {
		iLang = ComboBoxLang->ItemIndex;
//		FormShop->SlistConfig->Strings[ListConfParam::LCP_LANG] = iLang;

		FormShop->SetLanguage();
		FormGroupProduct->SetLanguage();
		FormGroupList->SetLanguage();
		FormBuyerData->SetLanguage();
		FormBuyerList->SetLanguage();
		FormMoveProduct->SetLanguage();
		FormMoveOther->SetLanguage();
		FormProduct->SetLanguage();
		FormUpdate->SetLanguage();
		FormShopUnitsList->SetLanguage();
		FormShopUnit->SetLanguage();
		FormUserStatus->SetLanguage();
		FormProvisionerData->SetLanguage();
		FormProgressBar->SetLanguage();
		FormProductList->SetLanguage();
		FormSelectProd->SetLanguage();
		FormReport->SetLanguage();
		FormProvisionerList->SetLanguage();

		FormShop->MoveList->FillList();
		Close();
	}
}
//---------------------------------------------------------------------------
