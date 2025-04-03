//---------------------------------------------------------------------------
#ifndef ShopH
#define ShopH

#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.MySQL.hpp>
#include <FireDAC.Phys.MySQLDef.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <FireDAC.Phys.IB.hpp>
#include <FireDAC.Phys.IBBase.hpp>
#include <FireDAC.Phys.IBWrapper.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>

#include "ShopUnits.h"
#include "Workers.h"
#include "Logs.h"
#include "UnitParentEsc.h"


///---------------------------------------------------------------------------
class TFormShop : public TFormEsc
{
__published:	// IDE-managed Components
	TFDConnection *FDConnection1;
	TFDPhysMySQLDriverLink *FDPhysMySQLDriverLink1;
	TPrintDialog *PrintDialog1;
	TTimer *TimerSync;
	TToolBar *ToolBar1;
	TImageList *ImageList1;
	TToolButton *ToolButtonGroupsProd;
	TToolButton *ToolButtonProducts;
	TToolButton *ToolButtonBuyers;
	TToolButton *ToolButtonProvisioners;
	TToolButton *ToolButtonReports;
	TToolButton *ToolButtonPrint;
	TToolButton *ToolButtonSeparator1;
	TToolButton *ToolButtonSeparator2;
	TToolButton *ToolButtonSeparator3;
	TToolButton *ToolButtonSale;
	TToolButton *ToolButtonIncom;
	TToolButton *ToolButtonOut;
	TToolButton *ToolButtonReturn;
	TToolButton *ToolButtonSeparator4;
	TToolButton *ToolButtonView;
	TToolButton *ToolButtonEdit;
	TToolButton *ToolButtonDelete;
	TToolButton *ToolButtonMonitoring;
	TToolButton *ToolButtonRetDebtProvis;
	TToolButton *ToolButtonShopUnits;
	TToolButton *ToolButtonSeparator5;
	TToolButton *ToolButtonLang;
	TToolButton *ToolButtonSeparator6;
	TToolButton *ToolButtonClose;
	TToolButton *ToolButtonRetDebt;
	TToolButton *ToolButtonExpenses;
	TToolButton *ToolButtonSeparator4a;
	TMainMenu *MainMenu1;
	TMenuItem *MenuFile;
	TMenuItem *MenuData;
	TMenuItem *MenuDB;
	TMenuItem *MenuClose;
	TMenuItem *MenuAction;
	TMenuItem *MenuView;
	TMenuItem *MenuEdit;
	TMenuItem *MenuDelete;
	TMenuItem *MenuGroup;
	TMenuItem *MenuProduct;
	TMenuItem *MenuBuyer;
	TMenuItem *MenuUnits;
	TMenuItem *MenuProvisioner;
	TMenuItem *MenuSale;
	TMenuItem *MenuReturn;
	TMenuItem *MenuIncoming;
	TMenuItem *MenuOutgoing;
	TMenuItem *MenuRetDebt;
	TMenuItem *MenuExpenses;
	TMenuItem *MenuDebtProvis;
	TMenuItem *MenuTools;
	TMenuItem *MenuDumpDB;
	TMenuItem *MenuRestoreDB;
	TMenuItem *MenuCreateTablesDB;
	TMenuItem *MenuSetLanguage;
	TMenuItem *ReloadDatabases1;
	TMenuItem *MenuAbout;
	TGroupBox *GroupBoxControl;
	TLabel *LabelStart;
	TLabel *LabelEnd;
	TLabel *LabelSearchByName;
	TLabel *LabelSearchByProd;
	TDateTimePicker *DateTimePicker1;
	TDateTimePicker *DateTimePicker2;
	TEdit *EditSearchName;
	TCheckBox *CheckBoxSales;
	TCheckBox *CheckBoxReturn;
	TCheckBox *CheckBoxIncom;
	TCheckBox *CheckBoxOut;
	TCheckBox *CheckBoxRetDebt;
	TCheckBox *CheckBoxExpenses;
	TCheckBox *CheckBoxDebtProvis;
	TEdit *EditSearchProd;
	TGroupBox *GroupBoxMovProd;
	TGroupBox *GroupBoxAtom;
	TFileOpenDialog *FileOpenDlgRestorDB;
	TGroupBox *GroupBoxUserStatus;
	TLabel *LabelUnit;
	TLabel *LabelStatus;
	TLabel *LabelUserStatus;
	TGroupBox *GroupBoxSource;
	TGroupBox *GroupBoxTarget;
	TLabel *LabelSourceUnit;
	TEdit *EditSourceUnit;
	TLabel *LabelSourceName;
	TEdit *EditSourcePerson;
	TLabel *LabelTargetUnit;
	TEdit *EditTargetUnit;
	TLabel *LabelTargetName;
	TEdit *EditTargetPerson;
	TImageList *ImageList2;
	TLabel *LabelCashNumb;
	TEdit *EditSearchCashNumb;
	TComboBox *ComboBoxUShops;
	TCheckBox *CheckBoxDeleted;

	void __fastcall FormCreate(TObject *Sender);
//	void __fastcall SetLanguage(void);
	void __fastcall ButtonProductListClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ButtonGroupListClick(TObject *Sender);
	void __fastcall ButtonBuyerListClick(TObject *Sender);
	void __fastcall ButtonReportClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall CreateTables(void);
	void __fastcall CreateTableBalance(void);
	void __fastcall BuckupDB(void);
	void __fastcall RestoreDB(void);
	void __fastcall SetLanguage(void);
	void __fastcall ClearFilesSQL(void);

	void __fastcall TimerSyncTimer(TObject *Sender);
	void __fastcall ButtonPrintClick(TObject *Sender);

	void __fastcall CreateListViews(void);
	void __fastcall FillPersonsData(TMoveProduct *MoveProduct);
	void __fastcall ToolButtonOperatClick(TObject *Sender);
	void __fastcall DateTimePicker1CloseUp(TObject *Sender);
	void __fastcall EditSearchNameChange(TObject *Sender);
	void __fastcall ToolButtonDeleteClick(TObject *Sender);
	void __fastcall ToolButtonShopUnitsClick(TObject *Sender);
	void __fastcall ToolButtonProvisionersClick(TObject *Sender);

	bool __fastcall CheckAccess(void);
	void __fastcall MenuToolsSubClick(TObject *Sender);
	void __fastcall MenuAboutClick(TObject *Sender);
	void __fastcall ToolButtonLangClick(TObject *Sender);
	void __fastcall ToolButtonCloseClick(TObject *Sender);
	void __fastcall MenuCloseClick(TObject *Sender);
	void __fastcall ComboBoxUShopsChange(TObject *Sender);
	void __fastcall SetPrivileges(void);
	void __fastcall ToolButtonMonitoringClick(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ReloadDatabases1Click(TObject *Sender);
	void __fastcall MenuesEnable(bool bEnable);

private:	// User declarations
public:		// User declarations
	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_SYSCOMMAND, TWMSysCommand, WMSysCommand)
		VCL_MESSAGE_HANDLER(WM_NCLBUTTONDBLCLK, TWMNCHitTest,   WMNCLButtonDblClk)
	END_MESSAGE_MAP(TForm)

	void __fastcall WMSysCommand(TWMSysCommand &SC);
	void __fastcall WMNCLButtonDblClk(TWMNCHitTest &SC);

	__fastcall TFormShop(TComponent* Owner);

	static UnicodeString uLastShopUnit;
	static UnicodeString uLastWorkerName;
	static UnicodeString uLastGroupProd;

    TMyFDQuery *FDQuery1;

	TStrings *SlistConfig;

//	bool bCloseApplication;
	bool bResized;

	TWorkers *Worker;
	TShopUnits *ShopUnit;

	TMyListView *MoveList;
	TMyListView *AtomList;

	static TColumnsData ColumnsDataSL[12];
	static TColumnsData ColumnsDataAtom[9];
	TLocate LocateStockSL;
	TLocate LocateStockAtom;

	TButtonAction ButtonOperat;
	bool bDebtForm;

	TLogs *CurrentLog;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormShop *FormShop;
//---------------------------------------------------------------------------
#endif
