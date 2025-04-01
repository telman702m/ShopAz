//---------------------------------------------------------------------------
#ifndef UnitProductListH
#define UnitProductListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>

#include "Product.h"
#include "UnitParent.h"
#include "MyListView.h"
#include "ExportExel.h"
#include <ValEdit.hpp>

//---------------------------------------------------------------------------
class TFormProductList : public TFormParent
{
__published:	// IDE-managed Components
	TLabel *LabelGroup;
	TLabel *LabelSearchByName;
	TComboBox *ComboBoxFilter;
	TEdit *EditFind;
	TFileSaveDialog *FileSaveDialog1;
	TCheckBox *CheckBoxShowEmpty;
	TCheckBox *CheckBoxHidePrice;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall LoadGroupsToComboFilter(void);
	void __fastcall ComboBoxFilterChange(TObject *Sender);
	void __fastcall ButtonPrintClick(TObject *Sender);
	void __fastcall ButtonExportToExcelClick(TObject *Sender);
	bool __fastcall FilteredProduct(int i);
	int __fastcall GetIndexFromComboGroup(UnicodeString NameGroup);

	void __fastcall WriteToExcelCell(ExcelData *myExcel, UnicodeString uStr, bool bVisible);
	void __fastcall WriteToExcelCell(ExcelData *myExcel, double dValue, bool bVisible);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall EditFindChange(TObject *Sender);
	void __fastcall CheckBoxShowEmptyClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall CheckBoxHidePriceClick(TObject *Sender);
	void __fastcall ResetPriveleges(void);
	void __fastcall FillShopsName(void);

private:	// User declarations
	bool bHiddenCheckBox;

public:		// User declarations
	__fastcall TFormProductList(TComponent* Owner);

	void __fastcall ToolButtonsClickAction(TButtonAction bAction);
	void __fastcall DeleteItem(void);
	void __fastcall SelectItem(void);

	unsigned CountStatColumn;

	int IndexLastGroupProd;

    TProduct *SelectedProduct;
	TValueListEditor *ValueListEditorBalance;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormProductList *FormProductList;
//---------------------------------------------------------------------------
#endif
