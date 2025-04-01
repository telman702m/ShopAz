//---------------------------------------------------------------------------
#ifndef UnitSelectProductH
#define UnitSelectProductH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>

#include "UnitParentEsc.h"
#include "SelectProduct.h"

//---------------------------------------------------------------------------
class TFormSelectProd : public TFormEsc
{
__published:	// IDE-managed Components
	TLabel *LabelProdCode;
	TLabel *LabelProdName;
	TLabel *LabelPrice;
	TLabel *LabelMoney;
	TLabel *LabelCent;
	TLabel *LabelCount;
	TLabel *LabelUnit;
	TLabel *LabelUnit2;
	TLabel *LabelCashBalance;
	TLabel *LabelInStock1;
	TLabel *LabelSum;
	TLabel *LabelMoneySum;
	TLabel *LabelCentSum;
	TLabel *LabelSumS;
	TLabel *LabelMoneySumS;
	TLabel *LabelCentSumS;
	TLabel *LabelCost;
	TLabel *LabelMoneyC;
	TLabel *LabelCentC;
	TLabel *LabelWholePrice;
	TLabel *LabelMoneyW;
	TLabel *LabelCentW;
	TButton *ButtonSubmit;
	TButton *ButtonCancel;
	TEdit *EditCodeProd;
	TEdit *EditNameProd;
	TEdit *EditSalePrice1;
	TEdit *EditSalePrice2;
	TEdit *EditCount1;
	TEdit *EditCount2;
	TEdit *EditTotalPrice1;
	TEdit *EditTotalPrice2;
	TEdit *EditTotalCost1;
	TEdit *EditTotalCost2;
	TEdit *EditCost1;
	TEdit *EditCost2;
	TEdit *EditWholePrice1;
	TEdit *EditWholePrice2;
	void __fastcall ClearFields(void);
	void __fastcall EditNameProdClick(TObject *Sender);
	void __fastcall EditCount1Change(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ButtonInsertClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ButtonCancelClick(TObject *Sender);
	void __fastcall LoadFromObjToForm(TSelectProduct *CurSelectProd);
	void __fastcall SaveAtFormToObject(TSelectProduct *CurSelectProd);
	void __fastcall EditCount1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DesignForm(void);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall DesignInputCount(bool bEnable, bool bWhole);
	bool __fastcall CheckData(void);
	bool __fastcall CheckValidProductPrice(void);
	void __fastcall SetLanguage(void);

private:	// User declarations

public:		// User declarations
	__fastcall TFormSelectProd(TComponent* Owner);

	TSelectProduct *TmpSelectProd;
	TCount CountInEdit;
	TCount CountInStock;
	int iMult;

	bool bButtonAddCall;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSelectProd *FormSelectProd;
//---------------------------------------------------------------------------
#endif
