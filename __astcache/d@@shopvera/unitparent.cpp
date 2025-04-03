//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitParent.h"
#include "Shop.h"
#include "Declaration.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t* TFormParent::wSelectMessage[2] = {
	L"Для выполнения операции необходимо выбрать элемент из списка!",
	L"Əməliyyatı həyata keçirilməsi üçün siyahıdan bir maddə seçilməlidir!"
};
const wchar_t* TFormParent::wDeleteMessage[2] = {
	L"Вы уверены?\nДанные будут безвозвратно удалены!",
	L"Əminsiz?\nİnformasiya qaytarılmaz pozulacaq!"
};


int TFormParent::HeightTaskBar = 0;

TFormParent *FormParent;
//---------------------------------------------------------------------------
__fastcall TFormParent::TFormParent(TComponent* Owner)
	: TForm(Owner)
{
	CalledObj = TCalledObj::OBJ_UNDEF;

	bOnceRun = false;
	bListUpdate = false;

	MyListView = NULL;

	MenuClose->ShortCut = vkEscape;

	ToolBarProperty TmpToolBars[] = {
		{L"ToolButtonSeparator0", 	L"|", {L"", 				L""}, 				-1, 8,  true},
		{L"ToolButtonView", 		L" ", {L"Просмотр", 		L"Baxış"},			 0, 0,  false},
		{L"ToolButtonEdit", 		L" ", {L"Редактировать", 	L"Redaktə"},		 1, 0,  false},
		{L"ToolButtonAdd", 			L" ", {L"Добавить", 		L"Əlavə etmək"},	 2, 0,  false},
		{L"ToolButtonDel", 			L" ", {L"Удалить", 			L"Silmək"},			 3, 0,  false},
		{L"ToolButtonSeparator1", 	L"|", {L"", 				L""}, 				-1, 61, true},
		{L"ToolButtonToExcel", 		L" ", {L"Экспорт в Excel", 	L"Excelə eksport"},	 4, 0,  false},
		{L"ToolButtonPrint", 	   	L" ", {L"Распечатать", 		L"Çap etmək"},		 5, 0,  false},
		{L"ToolButtonSeparator2", 	L"|", {L"", 				L""}, 				-1, 57, false},
		{L"ToolButtonClose", 	   	L" ", {L"Закрыть", 			L"Bağlamaq"},	  	 6, 0,  true},
	};

	for(unsigned i=0; i < sizeof(ToolBars)/sizeof(ToolBarProperty); i++) {
		ToolBars[i] = TmpToolBars[i];
	}

	wFormCaptions[0] = NULL;
	wFormCaptions[1] = NULL;

	SizeColumnsData = 0;
	ColumnsData = NULL;
	SizeLabelsData = 0;
	LabelsCaption = NULL;
	SizeButtonsData = 0;
	ButtonsCaption = NULL;
	SizeGroupBoxData = 0;
	GroupBoxCaption = NULL;
	SizeCheckBoxData = 0;
	CheckBoxCaption = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormParent::SetLanguage(void)
{
	unsigned j2 = 0;
	for(int i=0; i < ToolBar1->ButtonCount; i++) {
		if(ToolBar1->Buttons[i]->Style == tbsButton) {
			for(unsigned j=j2; j2 < sizeof(ToolBars)/sizeof(ToolBarProperty); j++) {
				if(ToolBar1->Buttons[i]->Name == ToolBars[j].Name) {
					ToolBar1->Buttons[i]->Hint = ToolBars[j].Hint[iLang];
					j2 = j + 1;
					break;
				}
			}
		}
	}

	Caption = wFormCaptions[iLang];

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

	MyListView->ReloadColumns(ColumnsData);
}
//---------------------------------------------------------------------------
void __fastcall TFormParent::ClearToolBar(void)
{
	for(int i = ToolBar1->ButtonCount; --i >= 0;) {
		TToolButton* button = ToolBar1->Buttons[i];
		// Remove "button" from "toolbar".
		ToolBar1->Perform(CM_CONTROLCHANGE, WPARAM(button), 0);
		delete button;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormParent::AddButtonToolBar(void)
{
  for(int i = sizeof(ToolBars)/sizeof(ToolBarProperty)-1; i >= 0; i--) {
	if(ToolBars[i].Visible) {
		TToolButton *TmButton = new TToolButton(ToolBar1);
		TmButton->Parent = ToolBar1;
		TmButton->Name = ToolBars[i].Name;
		TmButton->Caption = ToolBars[i].Caption;
		TmButton->ShowHint = true;
		TmButton->Hint = ToolBars[i].Hint[iLang];
		TmButton->OnClick = ToolButtonsClick;

		if(TmButton->Caption == "|") {
			TmButton->Style = tbsSeparator;
			TmButton->Width = ToolBars[i].Size;
		} else {
			TmButton->Style = tbsButton;
			TmButton->ImageIndex = ToolBars[i].ImageIndex;
		}
	}
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormParent::DropVisibleStatus(void)
{
	for(unsigned i=1; i < sizeof(ToolBars)/sizeof(ToolBarProperty) - 1; i++) {
		if(i != ToolBarStat::TS_SEP1) {
			ToolBars[i].Visible = false;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormParent::SetPrivileges(void)
{
	ClearToolBar();

	switch(FormShop->Worker->Privilege) {
		case TPrivilege::PRV_SUPER:
		case TPrivilege::PRV_ADMIN:
			ToolBars[ToolBarStat::TS_DEL].Visible = true;
			ToolBars[ToolBarStat::TS_EDIT].Visible = true;
		case TPrivilege::PRV_MANAGER:
			ToolBars[ToolBarStat::TS_ADD].Visible = true;
		case TPrivilege::PRV_SELLER:
			ToolBars[ToolBarStat::TS_VIEW].Visible = true;
		case TPrivilege::PRV_UNKNOW:
			break;
	}

	AddButtonToolBar();
}
//---------------------------------------------------------------------------
TToolButton* __fastcall TFormParent::GetToolButton(TToolBar *ToolBar, UnicodeString Name)
{
	for(int i=0; i < ToolBar->ButtonCount; i++) {
		if(ToolBar->Buttons[i]->Name == Name) {
			return ToolBar->Buttons[i];
		}
	}
	return NULL;
}

//---------------------------------------------------------------------------
void __fastcall TFormParent::SetPositionCloseButton(void)
{
	if(ToolBar1->ButtonCount > 1 && ToolBar1->Buttons[ToolBar1->ButtonCount-2]->Style == tbsSeparator) {
		ToolBar1->Buttons[ToolBar1->ButtonCount-2]->Width =
				ToolBar1->Width - ToolBar1->Buttons[ToolBar1->ButtonCount-3]->Left -
				ToolBar1->Buttons[ToolBar1->ButtonCount-3]->Width - ToolBar1->Buttons[ToolBar1->ButtonCount-1]->Width;
	}
}
//----------------------------------------------------------------------
void __fastcall TFormParent::GetTaskBarHeight(void)
{
	RECT rect;
	HWND taskBar = FindWindow(L"Shell_traywnd", NULL);

	if(taskBar && GetWindowRect(taskBar, &rect)) {
		HeightTaskBar = rect.bottom - rect.top;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFormParent::ToolButtonsClick(TObject *Sender)
{
	if(((TToolButton*)Sender)->Name == L"ToolButtonView") {
		if(CalledObj == TCalledObj::OBJ_EXTERN) {
			ButtonAction = TButtonAction::BA_SELECT;
			SelectItem();
			return;
		} else if(CalledObj == TCalledObj::OBJ_OWNER) {
			ButtonAction = TButtonAction::BA_VIEW;
		} else {
            return;
        }
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonEdit") {
		ButtonAction = TButtonAction::BA_EDIT;
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonAdd") {
		ButtonAction = TButtonAction::BA_ADD;
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonDel") {
		ButtonAction = TButtonAction::BA_DEL;
		DeleteItem();
		return;
	}
	else if(((TToolButton*)Sender)->Name == L"ToolButtonClose") {
		Close();
		return;
	}
	ToolButtonsClickAction(ButtonAction);
}
//---------------------------------------------------------------------------
void __fastcall TFormParent::WMSysCommand(TWMSysCommand &SC)
{
	if(SC.CmdType == 61458){
		WindowState = wsMaximized;
		return;
	 }
	TForm::Dispatch(&SC);
}
//---------------------------------------------------------------------------
void __fastcall TFormParent::WMNCLButtonDblClk(TWMNCHitTest &SC)
{
	WindowState = wsMaximized;
//   TForm::Dispatch(&SC);
}
//---------------------------------------------------------------------------
void __fastcall TFormParent::ToolButtonCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormParent::FormShow(TObject *Sender)
{
	if(bListUpdate) {
		MyListView->FillList();
		bListUpdate = false;
	}
}
//---------------------------------------------------------------------------

