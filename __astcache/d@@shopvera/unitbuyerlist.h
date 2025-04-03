//---------------------------------------------------------------------------
#ifndef UnitBuyerListH
#define UnitBuyerListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>

#include "UnitParent.h"
#include "MyListView.h"

//---------------------------------------------------------------------------
class TFormBuyerList : public TFormParent
{
__published:	// IDE-managed Components
	TLabel *LabelSearchByName;
	TLabel *LabelSearchByattribute;
	TEdit *EditFindName;
	TEdit *EditFindAttributs;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall EditFindNameChange(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);

private:	// User declarations

public:		// User declarations
	__fastcall TFormBuyerList(TComponent* Owner);

	void __fastcall ToolButtonsClickAction(TButtonAction bAction);
	void __fastcall DeleteItem(void);
	void __fastcall SelectItem(void);

	TBuyer *SelectedBuyer;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBuyerList *FormBuyerList;
//---------------------------------------------------------------------------
#endif
