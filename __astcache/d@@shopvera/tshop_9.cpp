//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

//#define MULT_TASK

//---------------------------------------------------------------------------
USEFORM("UnitGroupProduct.cpp", FormGroupProduct);
USEFORM("UnitGroupList.cpp", FormGroupList);
USEFORM("UnitBuyerList.cpp", FormBuyerList);
USEFORM("UnitLanguage.cpp", FormLanguage);
USEFORM("UnitMoveProduct.cpp", FormMoveProduct);
USEFORM("UnitMoveOther.cpp", FormMoveOther);
USEFORM("UnitLogs.cpp", FormLogs);
USEFORM("UnitBuyerData.cpp", FormBuyerData);
USEFORM("UnitAbout.cpp", FormAbout);
USEFORM("UnitParent.cpp", FormParent);
USEFORM("UnitShopUnitList.cpp", FormShopUnitsList);
USEFORM("UnitShopUnitData.cpp", FormShopUnit);
USEFORM("UnitSelectProduct.cpp", FormSelectProd);
USEFORM("UnitUpdater.cpp", FormUpdate);
USEFORM("UnitUserStatus.cpp", FormUserStatus);
USEFORM("UnitReport.cpp", FormReport);
USEFORM("UnitProduct.cpp", FormProduct);
USEFORM("UnitPrint.cpp", FormPrint);
USEFORM("UnitParentEsc.cpp", FormEsc);
USEFORM("UnitProductList.cpp", FormProductList);
USEFORM("UnitProvisionerList.cpp", FormProvisionerList);
USEFORM("UnitProvisionerData.cpp", FormProvisionerData);
USEFORM("UnitProgressBar.cpp", FormProgressBar);
USEFORM("Shop.cpp", FormShop);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
#ifndef MULT_TASK
	HANDLE Test_Present = CreateMutex(NULL, false, L"My_Program_Already_Present");
	if(GetLastError() == ERROR_ALREADY_EXISTS) {
		MessageBox(0, L"Programm ShopTM already runing!\nShopTM programı artıq işləyir!\nПрограмма ShopTM уже запущена!", NULL, MB_OK);
		return 0;
	}
#endif
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TFormShop), &FormShop);
		Application->CreateForm(__classid(TFormEsc), &FormEsc);
		Application->CreateForm(__classid(TFormShopUnit), &FormShopUnit);
		Application->CreateForm(__classid(TFormShopUnitsList), &FormShopUnitsList);
		Application->CreateForm(__classid(TFormParent), &FormParent);
		Application->CreateForm(__classid(TFormPrint), &FormPrint);
		Application->CreateForm(__classid(TFormProduct), &FormProduct);
		Application->CreateForm(__classid(TFormProductList), &FormProductList);
		Application->CreateForm(__classid(TFormProgressBar), &FormProgressBar);
		Application->CreateForm(__classid(TFormProvisionerData), &FormProvisionerData);
		Application->CreateForm(__classid(TFormMoveProduct), &FormMoveProduct);
		Application->CreateForm(__classid(TFormProvisionerList), &FormProvisionerList);
		Application->CreateForm(__classid(TFormSelectProd), &FormSelectProd);
		Application->CreateForm(__classid(TFormUserStatus), &FormUserStatus);
		Application->CreateForm(__classid(TFormGroupList), &FormGroupList);
		Application->CreateForm(__classid(TFormBuyerList), &FormBuyerList);
		Application->CreateForm(__classid(TFormGroupProduct), &FormGroupProduct);
		Application->CreateForm(__classid(TFormBuyerData), &FormBuyerData);
		Application->CreateForm(__classid(TFormReport), &FormReport);
		Application->CreateForm(__classid(TFormUpdate), &FormUpdate);
		Application->CreateForm(__classid(TFormLanguage), &FormLanguage);
		Application->CreateForm(__classid(TFormMoveOther), &FormMoveOther);
		Application->CreateForm(__classid(TFormAbout), &FormAbout);
		Application->CreateForm(__classid(TFormLogs), &FormLogs);
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

//	ShowMessage(L"Deleting Mutex");

#ifndef MULT_TASK
	CloseHandle(Test_Present);
	ReleaseMutex(Test_Present);
#endif
	return 0;
}
//---------------------------------------------------------------------------
