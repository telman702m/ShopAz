//---------------------------------------------------------------------------

#ifndef UnitGroupProductH
#define UnitGroupProductH
//---------------------------------------------------------------------------
#include "GroupProduct.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>

#include "UnitParentEsc.h"

//---------------------------------------------------------------------------
class TFormGroupProduct : public TFormEsc
{
__published:	// IDE-managed Components
	TLabel *LabelGroupCode;
	TLabel *LabelGroupName;
	TLabel *LabelDescription;
	TEdit *EditCode;
	TEdit *EditName;
	TButton *ButtonInsert;
	TButton *ButtonClose;
	TCheckBox *CheckBoxEnable;
	TMemo *MemoDescription;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ClearFields(void);
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonInsertClick(TObject *Sender);

	void __fastcall LoadFromObjectToForm(TGroupProduct *CurGroupProd);
	void __fastcall SaveAtFormToObject(TGroupProduct *CurGroupProd);
	void __fastcall LoadGroupsToCombo(void);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
	void __fastcall ComponentsEnable(void);
	void __fastcall ComponentsDisable(void);

public:		// User declarations
	__fastcall TFormGroupProduct(TComponent* Owner);

	TGroupProduct *TmpGroupProd;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGroupProduct *FormGroupProduct;
//---------------------------------------------------------------------------
#endif
