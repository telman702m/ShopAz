//---------------------------------------------------------------------------
#ifndef UnitBuyerDataH
#define UnitBuyerDataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "UnitParentEsc.h"
#include "Buyer.h"

//---------------------------------------------------------------------------
class TFormBuyerData : public TFormEsc
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *LabelSurname;
	TLabel *LabelName;
	TLabel *LabelPatron;
	TLabel *LabelOrg;
	TLabel *LabelAddress;
	TLabel *LabelPhone1;
	TLabel *LabelPhone2;
	TLabel *LabelDescript;
	TCheckBox *CheckBoxEnable;
	TButton *ButtonSave;
	TButton *ButtonClose;
	TEdit *EditSurname;
	TEdit *EditName;
	TEdit *EditPatronymic;
	TEdit *EditOrganization;
	TEdit *EditAddress;
	TEdit *EditPhone1;
	TEdit *EditPhone2;
	TMemo *MemoDescription;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ClearFields(void);
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonInsertClick(TObject *Sender);
	void __fastcall ComponentsEnable(void);
	void __fastcall ComponentsDisable(void);
	void __fastcall LoadFromObjectToForm(TBuyer *CurBuyer);
	void __fastcall SaveAtFormToObject(TBuyer *CurBuyer);

private:	// User declarations

public:		// User declarations
	__fastcall TFormBuyerData(TComponent* Owner);

	TBuyer *TmpBuyer;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBuyerData *FormBuyerData;
//---------------------------------------------------------------------------
#endif
