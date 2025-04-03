//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#include <Printers.hpp>
#pragma hdrstop

#include "Shop.h"
#include "UnitProductList.h"
#include "UnitGroupList.h"
#include "UnitProduct.h"
#include "UnitGroupProduct.h"
#include "UnitSelectProduct.h"
#include "UnitPrint.h"
#include "UnitProgressBar.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wAllGroups[] = {
	L"Все группы",
	L"Bütün gruplar"
};

const wchar_t *wDeleteProduct[] = {
	L"Данный товар присутствует в операции от даты %s!\nУдаление не допустимо!",
	L"Seçilmiş mal %s tarixdəki əməliyyətdə mövcüddür!\nSilmək mümkün deyil!"
};

const wchar_t *wExportExcel[] = {
	L"Экспорт данных о товарах в Excel",
	L"Mallar haqqında məlumatlarını Excel-ə köçürülməsi"
};
const wchar_t *wBalanceOwner[] = {
	L"Остаток", L"Qalıq"
};

TColumnsData ColumnsProducts[] = {
	{{L"Группа",	L"Grup"},			90,		taLeftJustify,  true,	false},
	{{L"Код",		L"Kodu"},			150,	taLeftJustify,  true, 	false},
	{{L"Название",	L"Adı"},			365, 	taLeftJustify,  true, 	false},
	{{L"Ед.изм.",	L"Ölçü"},			75, 	taCenter, 	    true, 	false},
	{{L"Стоимость",	L"Dəyəri"},			75, 	taRightJustify, false, 	true},
	{{L"Стоим. $",	L"Dəyəri $"},		75, 	taRightJustify, false, 	true},
	{{L"Цена",		L"Qiyməti"},		75,	   	taRightJustify, true, 	true},
	{{L"Опт.Цена", 	L"Top.Qiyməti"},	75,	   	taRightJustify, true, 	true}
};
TLabelCaption LabelCaptionProduct[] = {
	{{L"Группа",		   	L"Grup"},				NULL},
	{{L"Поиск по названию",	L"Adı ilə axtarış"},	NULL}
};
TCheckBoxCaption CheckBoxCaptionProdList[] = {
	{{L"Показать отсутствующие",	L"Olmayanları göstərmək"},	NULL},
	{{L"Скрыть стоимость", 		 	L"Dəyəri gizlətmək"},		NULL}
};

TFormProductList *FormProductList;

//---------------------------------------------------------------------------
__fastcall TFormProductList::TFormProductList(TComponent* Owner)
	: TFormParent(Owner)
{
	SizeLabelsData = sizeof(LabelCaptionProduct) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionProduct;

	SizeCheckBoxData = sizeof(CheckBoxCaptionProdList) / sizeof(TCheckBoxCaption);
	CheckBoxCaption = CheckBoxCaptionProdList;
}
//---------------------------------------------------------------------------
void __fastcall TFormProductList::FormCreate(TObject *Sender)
{
	wFormCaptions[0] = L"Список наименований товаров";
	wFormCaptions[1] = L"Malların siyahısı";

	LocateMyListView.Left = 16;
	LocateMyListView.Top = 88;
	LocateMyListView.Width = 1145;
	LocateMyListView.Height = 545;

	CountStatColumn = sizeof(ColumnsProducts) / sizeof(TColumnsData);
	SizeColumnsData = CountStatColumn + TObjectManager<TShopUnits>::GetList().size();

	ColumnsData = new TColumnsData[SizeColumnsData];

	for(unsigned i=0; i < CountStatColumn; i++) {
		ColumnsData[i] = ColumnsProducts[i];
	}

	FillShopsName();

	LabelsCaption[0].Label = LabelGroup;
	LabelsCaption[1].Label = LabelSearchByName;

	CheckBoxCaption[0].CheckBox = CheckBoxShowEmpty;
	CheckBoxCaption[1].CheckBox = CheckBoxHidePrice;

	IndexLastGroupProd = FormShop->uLastGroupProd.ToInt();

	EditFind->Text = L"";
	bHiddenCheckBox = false;

	MyListView = new TMyListView(FormProductList, FormProductList, ColumnsData, SizeColumnsData, LocateMyListView, TYPE_LIST::LS_PROD, true);
	MyListView->Name = L"ListStock";

	SetLanguage();
}
//---------------------------------------------------------------------------
void __fastcall TFormProductList::FillShopsName(void)
{
	for(unsigned i=0; i < TObjectManager<TShopUnits>::GetList().size(); i++) {
		if(i==0) {
			ColumnsData[i + CountStatColumn].Caption[0] = wBalanceOwner[0];
			ColumnsData[i + CountStatColumn].Caption[1] = wBalanceOwner[1];
		} else {
			ColumnsData[i + CountStatColumn].Caption[0] = TObjectManager<TShopUnits>::GetList()[TShopUnits::upp[i]]->Name;
			ColumnsData[i + CountStatColumn].Caption[1] = TObjectManager<TShopUnits>::GetList()[TShopUnits::upp[i]]->Name;
		}
		ColumnsData[i + CountStatColumn].Width = 60;
		ColumnsData[i + CountStatColumn].TMAlign = taRightJustify;
		ColumnsData[i + CountStatColumn].Visible = true;
		ColumnsData[i + CountStatColumn].bSum = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormProductList::FormShow(TObject *Sender)
{

	if(bOnceRun) {
		LoadGroupsToComboFilter();

		MyListView->FillList();

		if(uSelectItemString != L"") {
			int SetSelectItem = MyListView->GetItemIndexByColumnString(uSelectItemString, FindStringInColumn);
			MyListView->Items->Item[SetSelectItem]->Selected = true;
			MyListView->SetFocus();
			uSelectItemString = L"";
		}

		MyListView->SetFocus();
		SelectedProduct = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormProductList::ResetPriveleges(void)
{
	DropVisibleStatus();
	switch(FormShop->Worker->Privilege) {
		case TPrivilege::PRV_SUPER:
		case TPrivilege::PRV_ADMIN:
			ToolBars[ToolBarStat::TS_EXL].Visible = true;
			ToolBars[ToolBarStat::TS_PRT].Visible = true;
			ToolBars[ToolBarStat::TS_SEP2].Visible = true;

			CheckBoxHidePrice->Visible = true;
			if(CheckBoxHidePrice->Checked) {
				ColumnsData[4].Visible = false;
				ColumnsData[5].Visible = false;
			} else {
				ColumnsData[4].Visible = true;
				ColumnsData[5].Visible = true;
			}
			break;
		case TPrivilege::PRV_MANAGER:
		case TPrivilege::PRV_SELLER:
		case TPrivilege::PRV_UNKNOW:
			CheckBoxHidePrice->Visible = false;
			break;
	}
	SetPrivileges();
	SetPositionCloseButton();
}
//---------------------------------------------------------------------------
void __fastcall TFormProductList::FormResize(TObject *Sender)
{
	if(!bOnceRun) {
		bOnceRun = true;
		SetLanguage();

		MyListView->Width = ClientWidth - 4;
		MyListView->Left = 2;
		MyListView->Height = ClientHeight - MyListView->Top - HeightTaskBar - 30;

		CheckBoxShowEmpty->Left = ClientWidth - CheckBoxShowEmpty->Width - 40;
		CheckBoxHidePrice->Left = CheckBoxShowEmpty->Left - CheckBoxHidePrice->Width - 20;

		LoadGroupsToComboFilter();
		MyListView->FillList();

		if(uSelectItemString != L"") {
			int SetSelectItem = MyListView->GetItemIndexByColumnString(uSelectItemString, FindStringInColumn);
			MyListView->Items->Item[SetSelectItem]->Selected = true;
			MyListView->SetFocus();
			uSelectItemString = L"";
		}
		MyListView->SetFocus();
		SelectedProduct = NULL;

		ResetPriveleges();
		TToolButton *TbTmp;
		if(FormShop->Worker->Privilege <= TPrivilege::PRV_ADMIN) {
			TbTmp = FormParent->GetToolButton(FormProductList->ToolBar1, L"ToolButtonToExcel");
			if(TbTmp != NULL) {
				TbTmp->OnClick = ButtonExportToExcelClick;
			}
			TbTmp = FormParent->GetToolButton(FormProductList->ToolBar1, L"ToolButtonPrint");
			if(TbTmp != NULL) {
				TbTmp->OnClick = ButtonPrintClick;
			}
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormProductList::ToolButtonsClickAction(TButtonAction bAction)
{
	if((MyListView->ItemIndex == -1) && (bAction != TButtonAction::BA_ADD)) {
		Application->MessageBox(wSelectMessage[iLang], uCaptionWarning[iLang], MB_OK);
		return;
	}

	FormProduct->ShowModal();
}

//---------------------------------------------------------------------------
void __fastcall TFormProductList::DeleteItem(void)
{
	if(MyListView->ItemIndex != -1) {
		// Check exists product in any operation
		for(unsigned i=0; i < TObjectManager<TMoveProduct>::GetList().size(); i++) {
			for(unsigned j=0; j < TObjectManager<TMoveProduct>::GetList()[i]->VSelectedProd.size(); j++) {
				if(TObjectManager<TMoveProduct>::GetList()[i]->VSelectedProd[j]->Product == TObjectManager<TProduct>::GetList()[MyListView->ipp[MyListView->ItemIndex]]) {
					uTmp.sprintf(wDeleteProduct[iLang], TObjectManager<TMoveProduct>::GetList()[i]->DateTime.FormatString(wDateTimeFormat).w_str());
					Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_OK);
					return;
				}
			}
		}

		if(Application->MessageBox(wDeleteMessage[iLang], uCaptionWarning[iLang], MB_YESNO) == IDYES) {

			TObjectManager<TProduct>::GetList()[MyListView->ipp[MyListView->ItemIndex]]->DeleteObjectFromDb(FormShop->FDQuery1);

			MyListView->DeleteSelected();
			MyListView->FillList();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormProductList::SelectItem(void)
{
	if(MyListView->ItemIndex != -1) {
		SelectedProduct = MyListView->GetSelectProduct();
		Close();
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormProductList::LoadGroupsToComboFilter(void)
{
	ComboBoxFilter->Clear();
	ComboBoxFilter->Items->Add(wAllGroups[iLang]);

	for(unsigned i=0; i < TObjectManager<TGroupProduct>::GetList().size(); i++) {
		ComboBoxFilter->Items->Add(TObjectManager<TGroupProduct>::GetList()[i]->Name);
	}
	ComboBoxFilter->ItemIndex = IndexLastGroupProd;
}
//---------------------------------------------------------------------------
int __fastcall TFormProductList::GetIndexFromComboGroup(UnicodeString NameGroup)
{
	for(int i=0; i < ComboBoxFilter->Items->Count; i++) {
		if(ComboBoxFilter->Items->Strings[i] == NameGroup) {
			return i;
        }
	}
	return 0;
}

//---------------------------------------------------------------------------
void __fastcall TFormProductList::ComboBoxFilterChange(TObject *Sender)
{
	IndexLastGroupProd = ComboBoxFilter->ItemIndex;
	FormShop->uLastGroupProd = IndexLastGroupProd;
	MyListView->FillList();
}

//---------------------------------------------------------------------------
void __fastcall TFormProductList::EditFindChange(TObject *Sender)
{
	MyListView->FillList();
}
//---------------------------------------------------------------------------
void __fastcall TFormProductList::CheckBoxShowEmptyClick(TObject *Sender)
{
	MyListView->FillList();
}
//---------------------------------------------------------------------------
void __fastcall TFormProductList::CheckBoxHidePriceClick(TObject *Sender)
{
	if(CheckBoxHidePrice->Checked) {
		ColumnsData[4].Visible = false;
		ColumnsData[5].Visible = false;
	} else {
		ColumnsData[4].Visible = true;
		ColumnsData[5].Visible = true;
	}
	MyListView->ReloadColumns(ColumnsData);
	MyListView->FillList();
}
//---------------------------------------------------------------------------
bool __fastcall TFormProductList::FilteredProduct(int i)
{
	if(ComboBoxFilter->ItemIndex != 0) {
		if(!(ComboBoxFilter->Text == TObjectManager<TProduct>::GetList()[i]->GroupProd->Name)) {
			return false;
        }
	}

	if(FormProductList->EditFind->Text.Length() > 0) {
		if(!((TObjectManager<TProduct>::GetList()[i]->Name.UpperCase().Pos(FormProductList->EditFind->Text.UpperCase()) ||
			 TObjectManager<TProduct>::GetList()[i]->Code.UpperCase().Pos(FormProductList->EditFind->Text.UpperCase())) > 0)) {
			return false;
		}
	}

	if(!CheckBoxShowEmpty->Checked) {
		if(!(TObjectManager<TProduct>::GetList()[i]->CountBalance[TShopUnits::upp[0]] > 0)) {
			return false;
        }
	}
	return true;
}

//---------------------------------------------------------------------------
void __fastcall TFormProductList::FormClose(TObject *Sender, TCloseAction &Action)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TFormProductList::ButtonPrintClick(TObject *Sender)
{
	int IdGroup;

	if(ComboBoxFilter->ItemIndex == 0) {
		IdGroup = -1;
	} else {
		IdGroup = TObjectManager<TGroupProduct>::GetList()[ComboBoxFilter->ItemIndex - 1]->id;
	}

	FormPrint->PrintProducts(IdGroup);
}

//---------------------------------------------------------------------------
//               Export to Excel
//---------------------------------------------------------------------------
void __fastcall TFormProductList::ButtonExportToExcelClick(TObject *Sender)
{
	ExcelData *myExcel = new ExcelData();

	FormProgressBar->Show();
	FormProgressBar->Label1->Caption = wExportExcel[iLang];
	FormProgressBar->Update();
	FormProgressBar->Label1->Left = (FormProgressBar->ClientWidth - FormProgressBar->Label1->Width)/2;
	FormProgressBar->ProgressBar1->Position = 0;
	FormProgressBar->Update();
	FormProgressBar->ProgressBar1->Max = TObjectManager<TProduct>::GetList().size();

	int CountRows = 0;

	for(unsigned i = 0; i < TObjectManager<TProduct>::GetList().size(); i++) {

		if(FilteredProduct(i)) {
			for(int j = 0; j < MyListView->iCountColumn; j++) {
				if(CountRows == 0) {
					myExcel->SelectCurCell(CountRows + 1, j + 1);
					myExcel->SetCellProperty(CellFormat::TEXT);
					myExcel->WriteToCurCell(MyListView->ColumnsData[j].Caption[iLang]);
				}

				myExcel->SelectCurCell(CountRows + 2, j + 1);

				switch(j) {
				case 0:
					// Group
					WriteToExcelCell(myExcel, TObjectManager<TProduct>::GetList()[i]->GroupProd->Name, MyListView->ColumnsData[j].Visible);
					break;
				case 1:
					// TProduct Code
					WriteToExcelCell(myExcel, TObjectManager<TProduct>::GetList()[i]->Code, MyListView->ColumnsData[j].Visible);
					break;
				case 2:
					// TProduct Name
					WriteToExcelCell(myExcel, TObjectManager<TProduct>::GetList()[i]->Name, MyListView->ColumnsData[j].Visible);
					break;
				case 3:
					// TProduct Unit
					WriteToExcelCell(myExcel, TObjectManager<TProduct>::GetList()[i]->Unit, MyListView->ColumnsData[j].Visible);
					break;
				case 4:
					// Cash Purchase
					WriteToExcelCell(myExcel, TObjectManager<TProduct>::GetList()[i]->PurchaseCash.GetValue(), MyListView->ColumnsData[j].Visible);
					break;
				case 5:
					// Cash Purchase in $
					WriteToExcelCell(myExcel, TObjectManager<TProduct>::GetList()[i]->DollarPrice.GetValue(), MyListView->ColumnsData[j].Visible);
					break;
				case 6:
					// Selling Purchase
					WriteToExcelCell(myExcel, TObjectManager<TProduct>::GetList()[i]->SellingPrice.GetValue(), MyListView->ColumnsData[j].Visible);
					break;
				case 7:
					// Whole Selling Purchase
					WriteToExcelCell(myExcel, TObjectManager<TProduct>::GetList()[i]->WholePrice.GetValue(), MyListView->ColumnsData[j].Visible);
					break;
				case 8:
					// Cash Balance
					WriteToExcelCell(myExcel, TObjectManager<TProduct>::GetList()[i]->CountBalance[TShopUnits::upp[0]].GetValue(), MyListView->ColumnsData[j].Visible);
					break;
				}
			}
			CountRows++;
		}
		FormProgressBar->ProgressBar1->Position++;
		FormProgressBar->Update();
	}
	FormProgressBar->Close();

	AnsiString uTmp;

	// set borders
	uTmp.sprintf("I%d", CountRows+1);
	myExcel->SetCellsBorder("A1", uTmp);

	// set 1-st row align
	myExcel->SetCellsAlignment(L"A1", L"I1", CellAlign::CENTER);
	myExcel->SetCellsColor(L"A1", L"I1", 6);

	// Group
	uTmp.sprintf("A%d", CountRows+1);
	myExcel->SetCellsWidth(L"A2", uTmp, 20);
	myExcel->SetCellsAlignment(L"A2", uTmp, CellAlign::LEFT);

	// Code
	uTmp.sprintf("B%d", CountRows+1);
	myExcel->SetCellsWidth(L"B2", uTmp, 30);
	myExcel->SetCellsAlignment(L"B2", uTmp, CellAlign::LEFT);

	// Name
	uTmp.sprintf("C%d", CountRows+1);
	myExcel->SetCellsWidth(L"C2", uTmp, 60);
	myExcel->SetCellsAlignment(L"C2", uTmp, CellAlign::LEFT);

	// Unit
	uTmp.sprintf("D%d", CountRows+1);
	myExcel->SetCellsWidth(L"D2", uTmp, 10);
	myExcel->SetCellsAlignment(L"D2", uTmp, CellAlign::CENTER);

	// Cash Purchase
	uTmp.sprintf("E%d", CountRows+1);
	myExcel->SetCellsWidth(L"E2", uTmp, 14);
	myExcel->SetCellsAlignment(L"E2", uTmp, CellAlign::RIGHT);

	// Cash Purchase in $
	uTmp.sprintf("F%d", CountRows+1);
	myExcel->SetCellsWidth(L"F2", uTmp, 14);
	myExcel->SetCellsAlignment(L"F2", uTmp, CellAlign::RIGHT);

	// Selling price
	uTmp.sprintf("G%d", CountRows+1);
	myExcel->SetCellsWidth(L"G2", uTmp, 14);
	myExcel->SetCellsAlignment(L"G2", uTmp, CellAlign::RIGHT);

	// Whole selling price
	uTmp.sprintf("H%d", CountRows+1);
	myExcel->SetCellsWidth(L"H2", uTmp, 14);
	myExcel->SetCellsAlignment(L"H2", uTmp, CellAlign::RIGHT);

	// Cash balance
	uTmp.sprintf("I%d", CountRows+1);
	myExcel->SetCellsWidth(L"I2", uTmp, 14);
	myExcel->SetCellsAlignment(L"I2", uTmp, CellAlign::RIGHT);


	if(FileSaveDialog1->Execute()) {
		myExcel->SaveFile(FileSaveDialog1->FileName);
	}

	delete myExcel;
}

//---------------------------------------------------------------------------
void __fastcall TFormProductList::WriteToExcelCell(ExcelData *myExcel, UnicodeString uStr, bool bVisible)
{
	if(bVisible) {
		myExcel->SetCellProperty(CellFormat::TEXT);
		myExcel->WriteToCurCell(uStr);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormProductList::WriteToExcelCell(ExcelData *myExcel, double dValue, bool bVisible)
{
	if(bVisible) {
		myExcel->SetCellProperty(CellFormat::DBLE);
		myExcel->WriteToCurCell(dValue);
	}
}
//---------------------------------------------------------------------------

