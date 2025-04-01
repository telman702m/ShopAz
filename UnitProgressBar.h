//---------------------------------------------------------------------------
#ifndef UnitProgressBarH
#define UnitProgressBarH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

//---------------------------------------------------------------------------
class TFormProgressBar : public TForm
{
__published:	// IDE-managed Components
	TProgressBar *ProgressBar1;
	TLabel *Label1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SetLanguage(void);

private:	// User declarations

public:		// User declarations
	__fastcall TFormProgressBar(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormProgressBar *FormProgressBar;
//---------------------------------------------------------------------------
#endif
