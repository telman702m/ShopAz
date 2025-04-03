//---------------------------------------------------------------------------
#ifndef UnitMoveProductH
#define UnitMoveProductH

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
class TFormMoveProduct : public TFormParent
{
__published:	// IDE-managed Components
	TGroupBox *GroupBoxSource;
	TGroupBox *GroupBoxTarget;
	TLabel *LabelTargetUnit;
	TLabel *LabelTargetPerson;
	TLabel *LabelSourceUnit;
	TLabel *LabelSourcePerson;
	TButton *ButtonSubmit;
	TEdit *EditSourceUnit;
	TEdit *EditSourcePerson;
	TEdit *EditTargetUnit;
	TEdit *EditTargetPerson;
	TButton *ButtonCancel;
	TGroupBox *GroupBoxLeft;
	TGroupBox *GroupBoxRight;
	TLabel *LabelDiscount;
	TEdit *EditDiscountPercent;
	TLabel *LabelPercent;
	TEdit *EditDiscountPrice1;
	TLabel *LabelPriceL;
	TEdit *EditDiscountPrice2;
	TLabel *LabelCentL;
	TLabel *LabelActualPayment;
	TEdit *EditActualPayment1;
	TLabel *LabelPrice1;
	TEdit *EditActualPayment2;
	TLabel *LabelCent1;
	TLabel *LabelDebt;
	TEdit *EditDebt1;
	TLabel *LabelPrice2;
	TEdit *EditDebt2;
	TLabel *LabelCent2;
	TGroupBox *GroupBoxCenter;
	TLabel *LabeluDate;
	TLabel *LabelDate;
	TTimer *TimerDate;
	TLabel *LabelNote;
	TMemo *MemoDescription;
	TGroupBox *GroupBoxCenter2;
	TLabel *LabelSum;
	TEdit *EditBuyerPayment1;
	TLabel *LabelPriceR;
	TEdit *EditBuyerPayment2;
	TLabel *LabelCentR;
	TLabel *LabelTotalPayment;
	TEdit *EditTotalPrice1;
	TLabel *LabelPrice3;
	TEdit *EditTotalPrice2;
	TLabel *LabelCent3;
	TLabel *LabeluCashNumb;
	TLabel *LabelCashNumb;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonInsertClick(TObject *Sender);
	void __fastcall DeleteMoveProduct(TMoveProduct *MoveAlias);

	bool __fastcall CheckCorrectFields(void);
	void __fastcall ClearFields(void);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall LoadFromObjectToForm(TMoveProduct *CurMoveProduct);
	void __fastcall SaveAtFormToObject(TMoveProduct *CurMoveProduct, bool bDate);
	void __fastcall TimerDateTimer(TObject *Sender);
	void __fastcall EditSourceUnitClick(TObject *Sender);
	void __fastcall EditTargetUnitClick(TObject *Sender);
	void __fastcall EditDiscountPrice1Change(TObject *Sender);
	void __fastcall EditDiscountPercentChange(TObject *Sender);
	void __fastcall EditBuyerPayment1Change(TObject *Sender);
	void __fastcall EditActualPayment1Change(TObject *Sender);

	void __fastcall DisableEventsAction(void);
	void __fastcall EnableEventsAction(void);
	void __fastcall SetFloatToEdit(TEdit *Edit, double dValue);

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DesignForm(void);
	void __fastcall ButtonCancelClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);

private:	// User declarations
	UnicodeString uEditPercent;
	bool bChanged;
	bool bExternLoad;

public:		// User declarations
	__fastcall TFormMoveProduct(TComponent* Owner);

	void __fastcall DeleteItem(void);
	void __fastcall ToolButtonsClickAction(TButtonAction bAction);

	TMoveProduct *TmpMoveProduct;
	bool bChangeFromAtomList;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMoveProduct *FormMoveProduct;
//---------------------------------------------------------------------------
#endif
