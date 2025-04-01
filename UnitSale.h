//---------------------------------------------------------------------------
#ifndef UnitSaleH
#define UnitSaleH

#include <vcl.h>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <System.ImageList.hpp>

#include "UnitParent.h"
#include "MyListView.h"
#include "MoveProduct.h"

#include <vector>


//---------------------------------------------------------------------------
class TFormSale : public TFormParent
{
__published:	// IDE-managed Components
	TGroupBox *GroupBoxSource;
	TGroupBox *GroupBoxTarget;
	TTimer *TimerDate;
	TMemo *MemoDescription;
	TLabel *LabeluDate;
	TLabel *LabelDiscount;
	TLabel *LabelPriceL;
	TLabel *LabelCentL;
	TLabel *LabelPercent;
	TLabel *LabelSum;
	TLabel *LabelPriceR;
	TLabel *LabelCentR;
	TLabel *LabelNote;
	TLabel *LabelTargetUnit;
	TLabel *LabelTargetPerson;
	TLabel *LabelSourceUnit;
	TLabel *LabelSourcePerson;
	TLabel *LabelDate;
	TButton *ButtonSubmit;
	TEdit *EditSourceUnit;
	TEdit *EditSourcePerson;
	TEdit *EditTargetUnit;
	TEdit *EditTargetPerson;
	TEdit *EditDiscountPrice1;
	TEdit *EditDiscountPrice2;
	TEdit *EditDiscountPercent;
	TEdit *EditBuyerPayment1;
	TEdit *EditBuyerPayment2;
	TButton *ButtonCancel;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonInsertClick(TObject *Sender);
	void __fastcall ClearFields(void);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall LoadFromObjectToForm(TMoveProduct *CurMoveProduct);
	void __fastcall SaveAtFormToObject(TMoveProduct *CurMoveProduct);
	void __fastcall TimerDateTimer(TObject *Sender);
	void __fastcall EditDiscountPrice1Change(TObject *Sender);
	void __fastcall EditSourceUnitClick(TObject *Sender);
	void __fastcall EditTargetUnitClick(TObject *Sender);
	void __fastcall DateTimePickerSaleChange(TObject *Sender);
	void __fastcall EditDiscountPercentChange(TObject *Sender);
	void __fastcall EditDiscountPercentKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall EditDiscountPercentKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DesignForm(void);
	void __fastcall ButtonCancelClick(TObject *Sender);

private:	// User declarations
	UnicodeString uEditPercent;
	bool bClose;

public:		// User declarations
	__fastcall TFormSale(TComponent* Owner);

	void DeleteItem(void);
	void ToolButtonsClickAction(TButtonAction bAction);

	static UnicodeString uButtonCaptions1[6];
	static UnicodeString uSelectMessage;
	static UnicodeString uDeleteMessage;

	TMoveProduct *TmpMoveProduct;
	MyListView *AtomList;

	TProductCount *TmpProdCountKeep;
	std::vector<TProductCount*> vProdCountKeep;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSale *FormSale;
//---------------------------------------------------------------------------
#endif
