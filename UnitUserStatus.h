//---------------------------------------------------------------------------
#ifndef UnitUserStatusH
#define UnitUserStatusH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>

#include "UnitParentEsc.h"

//---------------------------------------------------------------------------
class TFormUserStatus : public TFormEsc
{
__published:	// IDE-managed Components
	TLabel *LabelPassword;
	TLabel *LabelUnitShop;
	TLabel *LabelLogin;
	TLabel *LabelLastLoadDate;
	TComboBox *ComboBoxShopUnits;
	TEdit *EditPassword;
	TButton *ButtonOk;
	TButton *ButtonCancel;
	TEdit *EditLogin;
	TDateTimePicker *DateTimePickerStartData;
	TCheckBox *CheckBoxLoadType;
	void __fastcall ComboBoxShopUnitsChange(TObject *Sender);
	void __fastcall ButtonOkClick(TObject *Sender);
	void __fastcall ButtonCancelClick(TObject *Sender);
	void __fastcall EditPasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DateTimePickerStartDataChange(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private:	// User declarations

public:		// User declarations
	__fastcall TFormUserStatus(TComponent* Owner);

	bool bStartDateChanged;
	bool bSuccess;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormUserStatus *FormUserStatus;
//---------------------------------------------------------------------------
#endif
