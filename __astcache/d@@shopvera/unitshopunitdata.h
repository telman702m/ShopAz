//---------------------------------------------------------------------------
#ifndef UnitShopUnitDataH
#define UnitShopUnitDataH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>

#include "UnitParentEsc.h"
#include "ShopUnits.h"
//---------------------------------------------------------------------------
class TFormShopUnit : public TFormEsc
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *LabelName;
	TLabel *LabelType;
	TLabel *LabelAddress;
	TLabel *LabelPhone1;
	TLabel *LabelPhone2;
	TLabel *LabelDescript;
	TEdit *EditName;
	TEdit *EditAddress;
	TEdit *EditPhone1;
	TEdit *EditPhone2;
	TMemo *MemoDescription;
	TCheckBox *CheckBoxEnable;
	TComboBox *ComboBoxType;
	TButton *ButtonSave;
	TButton *ButtonClose;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonInsertClick(TObject *Sender);
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ClearFields(void);
	void __fastcall ComponentsEnable(void);
	void __fastcall ComponentsDisable(void);
	void __fastcall LoadFromObjectToForm(TShopUnits *CurShopUnits);
	void __fastcall SaveAtFormToObject(TShopUnits *CurShopUnits);

private:	// User declarations

public:		// User declarations
	__fastcall TFormShopUnit(TComponent* Owner);

	TShopUnits* TmpShopUnit;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormShopUnit *FormShopUnit;
//---------------------------------------------------------------------------
#endif
