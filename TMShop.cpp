//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("UnitParent.cpp", FormParent);
USEFORM("UnitGroupProduct.cpp", FormGroupProduct);
USEFORM("UnitGroupList.cpp", FormGroupList);
USEFORM("UnitProduct.cpp", FormProduct);
USEFORM("UnitPrint.cpp", FormPrint);
USEFORM("UnitPassword.cpp", FormPasswd);
USEFORM("UnitBuyerList.cpp", FormBuyerList);
USEFORM("UnitBuyerData.cpp", FormBuyerData);
USEFORM("UnitBalanceProdUnits.cpp", FormBalanceProdUnits);
USEFORM("UnitShopUnitData.cpp", FormShopUnit);
USEFORM("UnitSelectProduct.cpp", FormSelectProd);
USEFORM("UnitSaleList.cpp", FormSaleList);
USEFORM("UnitUserStatus.cpp", FormUserStatus);
USEFORM("UnitShopUnitList.cpp", FormShopUnitsList);
USEFORM("UnitProvisionerData.cpp", FormProvisionerData);
USEFORM("UnitProgressBar.cpp", FormProgressBar);
USEFORM("UnitProductList.cpp", FormProductList);
USEFORM("UnitSale.cpp", FormSale);
USEFORM("UnitReport.cpp", FormReport);
USEFORM("UnitProvisionerList.cpp", FormProvisionerList);
USEFORM("Shop.cpp", FormShop);
//---------------------------------------------------------------------------
#include "Shop.h"
#include "GroupProduct.h"
#include "Product.h"
#include "MoveProduct.h"
#include "SelectProduct.h"
#include "LoadXML.h"


//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = "Shop";
		Application->CreateForm(__classid(TFormShop), &FormShop);
		Application->CreateForm(__classid(TFormGroupList), &FormGroupList);
		Application->CreateForm(__classid(TFormGroupProduct), &FormGroupProduct);
		Application->CreateForm(__classid(TFormProduct), &FormProduct);
		Application->CreateForm(__classid(TFormBuyerList), &FormBuyerList);
		Application->CreateForm(__classid(TFormBuyerData), &FormBuyerData);
		Application->CreateForm(__classid(TFormSale), &FormSale);
		Application->CreateForm(__classid(TFormSelectProd), &FormSelectProd);
		Application->CreateForm(__classid(TFormReport), &FormReport);
		Application->CreateForm(__classid(TFormPrint), &FormPrint);
		Application->CreateForm(__classid(TFormUserStatus), &FormUserStatus);
		Application->CreateForm(__classid(TFormPasswd), &FormPasswd);
		Application->CreateForm(__classid(TFormProductList), &FormProductList);
		Application->CreateForm(__classid(TFormProductList), &FormProductList);
		Application->CreateForm(__classid(TFormProgressBar), &FormProgressBar);
		Application->CreateForm(__classid(TFormProvisionerData), &FormProvisionerData);
		Application->CreateForm(__classid(TFormProvisionerList), &FormProvisionerList);
		Application->CreateForm(__classid(TFormShopUnit), &FormShopUnit);
		Application->CreateForm(__classid(TFormShopUnitsList), &FormShopUnitsList);
		Application->CreateForm(__classid(TFormBalanceProdUnits), &FormBalanceProdUnits);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
