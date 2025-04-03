//---------------------------------------------------------------------------
#ifndef UnitPrintH
#define UnitPrintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "UnitMoveProduct.h"

//---------------------------------------------------------------------------
class TFormPrint : public TForm
{
__published:	// IDE-managed Components
	TImage *ImagePreview;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

	void __fastcall PrintSale(TMoveProduct *CurMoveProduct);
	long __fastcall PrintTicket(long LeftMarg, long TopOffset, TMoveProduct *CurMoveProduct);

	void __fastcall PrintProducts(int IdGroup);
	void __fastcall DrawTbProdCaption(void);
private:	// User declarations
public:		// User declarations
	__fastcall TFormPrint(TComponent* Owner);

	int pw, ph;
	TCanvas *Canv;
	TPrinter *Prntr;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPrint *FormPrint;
//---------------------------------------------------------------------------
#endif
