//---------------------------------------------------------------------------
#ifndef UnitParentH
#define UnitParentH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>

#include "Declaration.h"
#include <System.ImageList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Menus.hpp>

#include "MyListView.h"

typedef struct _ToolBarProperty {
	const wchar_t *Name;
	const wchar_t *Caption;
	const wchar_t *Hint[2];
	int ImageIndex;
	int Size;
	bool Visible;
} ToolBarProperty;

typedef struct _TColumnName {
	const wchar_t *Name[2];
} TColumnName;

typedef struct _TLabelCaption {
	const wchar_t *Caption[2];
	TLabel *Label;
} TLabelCaption;

typedef struct _TButtonCaption {
	const wchar_t *Caption[2];
	TButton *Button;
} TButtonCaption;

typedef struct _GroupBoxCaption {
	const wchar_t *Caption[2];
	TGroupBox *GroupBox;
} TGroupBoxCaption;

typedef struct _TCheckBoxCaption {
	const wchar_t *Caption[2];
	TCheckBox *CheckBox;
} TCheckBoxCaption;

typedef struct _TToolBarCaption {
	const wchar_t *Caption[2];
	TToolButton *ToolButton;
} TToolBarCaption;

typedef struct _TTMenuItemCaption {
	const wchar_t *Caption[2];
	TMenuItem *MenuItem;
} TTMenuItemCaption;

//---------------------------------------------------------------------------
class TFormParent : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TImageList *ImageList1;
	TMainMenu *MainMenu1;
	TMenuItem *MenuClose;

	void __fastcall SetPositionCloseButton(void);
	void __fastcall ToolButtonsClick(TObject *Sender);
	void __fastcall DropVisibleStatus(void);
	void __fastcall SetPrivileges(void);
	void __fastcall SetLanguage(void);
	void __fastcall ClearToolBar(void);
	void __fastcall AddButtonToolBar(void);
	void __fastcall ToolButtonCloseClick(TObject *Sender);
//	void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
	TToolButton* __fastcall GetToolButton(TToolBar *ToolBar, UnicodeString Name);
	void __fastcall FormShow(TObject *Sender);

private:	// User declarations
public:		// User declarations

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_SYSCOMMAND, TWMSysCommand, WMSysCommand)
		VCL_MESSAGE_HANDLER(WM_NCLBUTTONDBLCLK, TWMNCHitTest, WMNCLButtonDblClk)

//		MESSAGE_HANDLER(WM_HOTKEY, TWMHotKey, WMHotKey)
	END_MESSAGE_MAP(TForm)

	void __fastcall WMSysCommand(TWMSysCommand &SC);
	void __fastcall WMNCLButtonDblClk(TWMNCHitTest &SC);
//	void __fastcall WMHotKey(TWMHotKey &Message);

	__fastcall TFormParent(TComponent* Owner);

	virtual void __fastcall ToolButtonsClickAction(TButtonAction bAct) = 0;
	virtual void __fastcall DeleteItem(void) = 0;
	virtual void __fastcall SelectItem(void) = 0;
//	virtual void __fastcall ToolButtonClick(TObject *Sender) = 0;

	static int HeightTaskBar;
	static void __fastcall GetTaskBarHeight(void);
	bool bOnceRun;
	bool bListUpdate;
	static const wchar_t *wSelectMessage[2];

	TButtonAction ButtonAction;
	TCalledObj CalledObj;
	UnicodeString uSelectItemString;
	int FindStringInColumn;
	UnicodeString uTmp;
	ToolBarProperty ToolBars[10];


	static const wchar_t *wDeleteMessage[2];
	const wchar_t *wFormCaptions[2];

	unsigned SizeColumnsData;
	TColumnsData *ColumnsData;
	unsigned SizeLabelsData;
	TLabelCaption *LabelsCaption;
	unsigned SizeButtonsData;
	TButtonCaption *ButtonsCaption;
	unsigned SizeGroupBoxData;
	TGroupBoxCaption *GroupBoxCaption;
	unsigned SizeCheckBoxData;
	TCheckBoxCaption *CheckBoxCaption;

	TLocate LocateMyListView;
	TMyListView *MyListView;
};

//---------------------------------------------------------------------------
extern PACKAGE TFormParent *FormParent;
//---------------------------------------------------------------------------
#endif
