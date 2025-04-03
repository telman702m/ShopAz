//---------------------------------------------------------------------------
#ifndef UnitLanguageH
#define UnitLanguageH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "UnitParentEsc.h"

//---------------------------------------------------------------------------
class TFormLanguage : public TFormEsc
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *ComboBoxLang;
	TButton *ButtonOk;
	TButton *ButtonCancel;
	void __fastcall ButtonCancelClick(TObject *Sender);
	void __fastcall ButtonOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormLanguage(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLanguage *FormLanguage;
//---------------------------------------------------------------------------
#endif
