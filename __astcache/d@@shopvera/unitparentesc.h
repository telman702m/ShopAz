//---------------------------------------------------------------------------
#ifndef UnitParentEscH
#define UnitParentEscH

#include "UnitParent.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TFormEsc : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall SetLanguage(void);
private:	// User declarations
public:		// User declarations
	__fastcall TFormEsc(TComponent* Owner);

	const wchar_t *wFormCaptions[2];

	unsigned SizeLabelsData;
	TLabelCaption *LabelsCaption;
	unsigned SizeButtonsData;
	TButtonCaption *ButtonsCaption;
	unsigned SizeGroupBoxData;
	TGroupBoxCaption *GroupBoxCaption;
	unsigned SizeCheckBoxData;
	TCheckBoxCaption *CheckBoxCaption;
	unsigned SizeToolBarsData;
	TToolBarCaption *ToolBarsCaption;
	unsigned SizeMenuData;
	TTMenuItemCaption *MenuItemsCaption;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEsc *FormEsc;
//---------------------------------------------------------------------------
#endif
