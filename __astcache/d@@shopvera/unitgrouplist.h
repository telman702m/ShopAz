//---------------------------------------------------------------------------
#ifndef UnitGroupListH
#define UnitGroupListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>

#include "UnitParent.h"
#include "MyListView.h"

//---------------------------------------------------------------------------
class TFormGroupList : public TFormParent
{
__published:	// IDE-managed Components

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);

private:	// User declarations

public:		// User declarations
	__fastcall TFormGroupList(TComponent* Owner);

	void __fastcall ToolButtonsClickAction(TButtonAction bAction);
	void __fastcall DeleteItem(void);

//	static UnicodeString AllGroups;
//	static UnicodeString uDeleteMessage;

//	TButtonAction ButActGroup;
//	TMyListView *GroupList;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGroupList *FormGroupList;
//---------------------------------------------------------------------------
#endif
