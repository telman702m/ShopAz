//---------------------------------------------------------------------------
#ifndef UnitShopUnitListH
#define UnitShopUnitListH
//---------------------------------------------------------------------------

#include "UnitParent.h"
#include "MyListView.h"

//---------------------------------------------------------------------------
class TFormShopUnitsList : public TFormParent
{
__published:	// IDE-managed Components
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);

private:	// User declarations

public:		// User declarations
	__fastcall TFormShopUnitsList(TComponent* Owner);

	void __fastcall ToolButtonsClickAction(TButtonAction bAction);
	void __fastcall DeleteItem(void);
	void __fastcall SelectItem(void);

	TShopUnits *SelectedShopUnit;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormShopUnitsList *FormShopUnitsList;
//---------------------------------------------------------------------------
#endif
