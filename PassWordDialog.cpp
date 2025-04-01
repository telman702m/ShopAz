//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PassWordDialog.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TPasswordDlg *PasswordDlg;
//---------------------------------------------------------------------
__fastcall TPasswordDlg::TPasswordDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPasswordDlg::FormCreate(TObject *Sender)
{
	uValidPasswd = L"fpthbktyl726";
}
//---------------------------------------------------------------------
void __fastcall TPasswordDlg::FormShow(TObject *Sender)
{
	uValidPasswd = L"fpthbktyl726";
	bValidPasswd = false;

	Password->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TPasswordDlg::OKBtnClick(TObject *Sender)
{
	if(Password->Text == uValidPasswd) {
		bValidPasswd = true;
		Close();
	} else {
		Application->MessageBox(L"Invalid password", L"Warning", MB_OK);
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TPasswordDlg::PasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN) {
		OKBtnClick(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TPasswordDlg::CancelBtnClick(TObject *Sender)
{
	bValidPasswd = false;
	return;
//	Close();
}
//---------------------------------------------------------------------------

