//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitParentEsc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormEsc *FormEsc;
//---------------------------------------------------------------------------
__fastcall TFormEsc::TFormEsc(TComponent* Owner)
	: TForm(Owner)
{
	KeyPreview = true;

	wFormCaptions[0] = NULL;
	wFormCaptions[1] = NULL;

	SizeLabelsData = 0;
	LabelsCaption = NULL;
	SizeButtonsData = 0;
	ButtonsCaption = NULL;
	SizeGroupBoxData = 0;
	GroupBoxCaption = NULL;
	SizeCheckBoxData = 0;
	CheckBoxCaption = NULL;
	SizeToolBarsData = 0;
	ToolBarsCaption = NULL;
	SizeMenuData = 0;
	MenuItemsCaption = NULL;
}
//---------------------------------------------------------------------------/*
void __fastcall TFormEsc::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_ESCAPE) {
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormEsc::SetLanguage(void)
{
	if(wFormCaptions[iLang] != NULL) {
		Caption = wFormCaptions[iLang];
	}

	for(unsigned i=0; i < SizeLabelsData; i++) {
		LabelsCaption[i].Label->Caption = LabelsCaption[i].Caption[iLang];
	}
	for(unsigned i=0; i < SizeButtonsData; i++) {
		ButtonsCaption[i].Button->Caption = ButtonsCaption[i].Caption[iLang];
	}
	for(unsigned i=0; i < SizeGroupBoxData; i++) {
		GroupBoxCaption[i].GroupBox->Caption = GroupBoxCaption[i].Caption[iLang];
	}
	for(unsigned i=0; i < SizeCheckBoxData; i++) {
		CheckBoxCaption[i].CheckBox->Caption = CheckBoxCaption[i].Caption[iLang];
	}
	for(unsigned i=0; i < SizeToolBarsData; i++) {
		ToolBarsCaption[i].ToolButton->Hint = ToolBarsCaption[i].Caption[iLang];
	}
	for(unsigned i=0; i < SizeMenuData; i++) {
		MenuItemsCaption[i].MenuItem->Caption = MenuItemsCaption[i].Caption[iLang];
	}
}
//---------------------------------------------------------------------------

