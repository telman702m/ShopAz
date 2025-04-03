//---------------------------------------------------------------------------
#ifndef UnitProvisionerListH
#define UnitProvisionerListH
//---------------------------------------------------------------------------
#include "UnitParent.h"
#include "MyListView.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>

//---------------------------------------------------------------------------
class TFormProvisionerList : public TFormParent
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
	__fastcall TFormProvisionerList(TComponent* Owner);

	void __fastcall ToolButtonsClickAction(TButtonAction bAction);
	void __fastcall DeleteItem(void);
	void __fastcall SelectItem(void);

	TProvisioner *SelectedProvisioner;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormProvisionerList *FormProvisionerList;
//---------------------------------------------------------------------------
#endif
