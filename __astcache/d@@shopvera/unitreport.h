//---------------------------------------------------------------------------
#ifndef UnitReportH
#define UnitReportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>

#include "MyListView.h"
#include "UnitParent.h"
#include <Vcl.CheckLst.hpp>

//---------------------------------------------------------------------------
class TReport : public TObject
{
public:
	UnicodeString NameUnit;
	TPrice Incoming;
	TPrice Receive;
	TPrice Send;
	TPrice Sale;
	TPrice Return;
	TPrice Discount;
	TPrice DebtBuyers;
	TPrice DebtProvis;
	TPrice Expanses;
	TPrice Cashbox;
	TPrice Cost;
	TPrice Profit;
	TPrice PercentProfit;

	TPrice BalanceProductCost;
	TPrice BalanceProductPrice;

	__fastcall TReport(void) {};
	void __fastcall CalcProfitPercent(void);

	static TReport **Reports;
    static int CountReport;
	static void __fastcall InitReport(void);
	static void __fastcall DestructReport(void);
	static void __fastcall RestoreOrderShopsName(void);
	static void __fastcall CalcReport(void);
};

//---------------------------------------------------------------------------
class TFormReport : public TFormParent
{
__published:	// IDE-managed Components
	TGroupBox *GroupBoxDateRange;
	TLabel *LabelStartDate;
	TLabel *LabelEndDate;
	TDateTimePicker *DateTimePicker1;
	TDateTimePicker *DateTimePicker2;
	TGroupBox *GroupBoxPredefInterval;
	TButton *ButtonLastDay;
	TButton *ButtonLastWeek;
	TButton *ButtonLastMonth;
	TButton *ButtonLastYear;
	TGroupBox *GroupBoxStatistic;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall DateTimePicker1Change(TObject *Sender);
	void __fastcall DateTimePicker1CloseUp(TObject *Sender);
	void __fastcall DateTimePicker1Click(TObject *Sender);
	void __fastcall ButtonsPredefClick(TObject *Sender);

private:	// User declarations

public:		// User declarations
	__fastcall TFormReport(TComponent* Owner);

	bool bEventPicker;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormReport *FormReport;
//---------------------------------------------------------------------------
#endif
