//---------------------------------------------------------------------------
#ifndef UnitLogsH
#define UnitLogsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "UnitParentEsc.h"
#include <vector>

#include "Declaration.h"
#include "UnitParentEsc.h"

//---------------------------------------------------------------------------

class TFormLogs : public TFormEsc
{
__published:	// IDE-managed Components
	TListView *ListViewLogsData;
	TListView *ListViewDetails;
	TTimer *Timer1;
	TImageList *ImageList1;
	TGroupBox *GroupBoxControl;
	TLabel *LabelStart;
	TLabel *LabelEnd;
	TDateTimePicker *DateTimePicker1;
	TDateTimePicker *DateTimePicker2;
	TCheckBox *CheckBoxActive;
	TLabel *LabelCurrentDateTime;
	TGroupBox *GroupBox1;
	TLabel *LabelsUser;
	TLabel *LabelsUnitShop;
	TLabel *LabelsActions;
	TLabel *LabelsDuration;
	TLabel *LabelUser;
	TLabel *LabelsExitStatus;
	TLabel *LabelUnitShop;
	TLabel *LabelDuration;
	TLabel *LabelActions;
	TLabel *LabelExitStatus;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FillListLogsData(void);
	void __fastcall ListViewLogsDataClick(TObject *Sender);
	void __fastcall ListViewLogsDataKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CheckBoxActiveClick(TObject *Sender);
	void __fastcall DateTimePicker1CloseUp(TObject *Sender);
	void __fastcall ClearDetails(void);
	void __fastcall LoadLogs(bool bDateFromServer);

private:	// User declarations
	int TopIndex;
	int IndexSelected;
	int ItemHeight;

	vector <int> ipp;

public:		// User declarations
	__fastcall TFormLogs(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLogs *FormLogs;
//---------------------------------------------------------------------------
#endif
