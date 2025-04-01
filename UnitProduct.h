//---------------------------------------------------------------------------
#ifndef UnitProductH
#define UnitProductH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>

#include "UnitParentEsc.h"
#include "Product.h"
///---------------------------------------------------------------------------
class TFormProduct : public TFormEsc
{
__published:	// IDE-managed Components
	TLabel *LabelGroup;
	TLabel *LabelCode;
	TLabel *LabelName;
	TLabel *LabelCash;
	TLabel *LabelRetail;
	TLabel *LabelUnit;
	TLabel *LabelDescription;
	TLabel *LabelDollar1;
	TLabel *LabelDollar3;
	TLabel *LabelCent1;
	TLabel *LabelCent3;
	TLabel *LabelPurchaseDollar1;
	TLabel *LabelDollar2;
	TLabel *LabelCent2;
	TLabel *LabelWholePrice;
	TLabel *LabelDollar4;
	TLabel *LabelCent4;
	TCheckBox *CheckBoxWholeUnit;
	TCheckBox *CheckBoxEnable;
	TButton *ButtonSave;
	TButton *ButtonClose;
	TComboBox *ComboBoxGroup;
	TEdit *EditGroup;
	TEdit *EditCode;
	TEdit *EditName;
	TEdit *EditUnit;
	TEdit *EditPurchasePrice1;
	TEdit *EditPurchasePrice2;
	TEdit *EditPurchaseDollar1;
	TEdit *EditPurchaseDollar2;
	TEdit *EditSellingPrice1;
	TEdit *EditSellingPrice2;
	TEdit *EditWholePrice1;
	TEdit *EditWholePrice2;
	TMemo *MemoDescription;
	void __fastcall ClearFields(void);
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonInsertClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LoadFromObjectToForm(TProduct *CurProd);
	void __fastcall SaveAtFormToObject(TProduct *CurProd);
	bool __fastcall CheckFields(void);
	void __fastcall ComponentsEnable(void);
	void __fastcall ComponentsDisable(void);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CheckBoxWholeUnitClick(TObject *Sender);

private:	// User declarations
	int __fastcall GetComboBoxIndex(UnicodeString Name);

	TProduct *TmpProduct;

public:		// User declarations

	__fastcall TFormProduct(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormProduct *FormProduct;
//---------------------------------------------------------------------------
#endif
