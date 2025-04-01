//----------------------------------------------------------------------------
#ifndef PassWordDialogH
#define PassWordDialogH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
//----------------------------------------------------------------------------
//#include <vcl\Buttons.hpp>
//#include <vcl\StdCtrls.hpp>
//#include <vcl\Controls.hpp>
//#include <vcl\Forms.hpp>
//#include <vcl\Graphics.hpp>
//#include <vcl\Classes.hpp>
//#include <vcl\SysUtils.hpp>
//#include <vcl\Windows.hpp>
//#include <vcl\System.hpp>
//----------------------------------------------------------------------------
class TPasswordDlg : public TForm
{
__published:
	TLabel *Label1;
	TEdit *Password;
	TButton *OKBtn;
	TButton *CancelBtn;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OKBtnClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall PasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:
	UnicodeString uValidPasswd;

public:
	virtual __fastcall TPasswordDlg(TComponent* AOwner);

	bool bValidPasswd;
};
//----------------------------------------------------------------------------
extern PACKAGE TPasswordDlg *PasswordDlg;
//----------------------------------------------------------------------------
#endif    
