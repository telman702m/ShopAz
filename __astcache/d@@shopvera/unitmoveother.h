//---------------------------------------------------------------------------

#ifndef UnitMoveOtherH
#define UnitMoveOtherH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>

#include "UnitParentEsc.h"
#include "MoveProduct.h"

//---------------------------------------------------------------------------
class TFormMoveOther : public TFormEsc
{
__published:	// IDE-managed Components
	TGroupBox *GroupBoxSource;
	TLabel *LabelSourceUnit;
	TLabel *LabelSourcePerson;
	TEdit *EditSourceUnit;
	TEdit *EditSourcePerson;
	TGroupBox *GroupBoxCenter;
	TLabel *LabeluDate;
	TLabel *LabelDate;
	TMemo *MemoDescription;
	TButton *ButtonSubmit;
	TButton *ButtonCancel;
	TGroupBox *GroupBoxRight;
	TLabel *LabelActualPayment;
	TLabel *LabelPrice1;
	TLabel *LabelCent1;
	TEdit *EditActualPayment1;
	TEdit *EditActualPayment2;
	TLabel *LabelNote;
	TTimer *TimerDate;
	TGroupBox *GroupBox1;
	TLabel *LabelTargetUnit;
	TLabel *LabelTargetPerson;
	TEdit *EditTargetUnit;
	TEdit *EditTargetPerson;
	void __fastcall DesignForm(void);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall LoadFromObjectToForm(TMoveProduct *CurMoveProduct);
	void __fastcall SaveAtFormToObject(TMoveProduct *CurMoveProduct, bool bDate);
	void __fastcall ClearFields(void);
	bool __fastcall CheckCorrectFields(void);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonInsertClick(TObject *Sender);
	void __fastcall EditSourceUnitClick(TObject *Sender);
	void __fastcall TimerDateTimer(TObject *Sender);
	void __fastcall ButtonCancelClick(TObject *Sender);
	void __fastcall EditActualPayment1Change(TObject *Sender);

private:	// User declarations
	bool bChanged;

public:		// User declarations
	__fastcall TFormMoveOther(TComponent* Owner);

	TMoveProduct *TmpMoveProduct;
	TCalledObj CalledObj;

};
//---------------------------------------------------------------------------
extern PACKAGE TFormMoveOther *FormMoveOther;
//---------------------------------------------------------------------------
#endif
