//---------------------------------------------------------------------------
#ifndef UnitAboutH
#define UnitAboutH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "UnitParentEsc.h"
//---------------------------------------------------------------------------
class TFormAbout : public TFormEsc
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *LabelVersion;
	TLabel *Label3;
	TLabel *Label4;
private:	// User declarations
public:		// User declarations
	__fastcall TFormAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAbout *FormAbout;
//---------------------------------------------------------------------------
#endif
