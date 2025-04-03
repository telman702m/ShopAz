//---------------------------------------------------------------------------
#ifndef UnitProvisionerDataH
#define UnitProvisionerDataH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>

#include "UnitParentEsc.h"
#include "Provisioner.h"

//---------------------------------------------------------------------------
class TFormProvisionerData : public TFormEsc
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *LabelName;
	TLabel *LabelSurname;
	TLabel *LabelPatron;
	TLabel *LabelAddress;
	TLabel *LabelPhone1;
	TLabel *LabelPhone2;
	TLabel *LabelDescript;
	TLabel *LabelOrg;
	TEdit *EditName;
	TEdit *EditSurname;
	TEdit *EditPatronymic;
	TEdit *EditAddress;
	TEdit *EditPhone1;
	TEdit *EditPhone2;
	TMemo *MemoDescription;
	TCheckBox *CheckBoxEnable;
	TEdit *EditOrganization;
	TButton *ButtonSave;
	TButton *ButtonClose;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

	void __fastcall ClearFields(void);
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonInsertClick(TObject *Sender);
	void __fastcall ComponentsEnable(void);
	void __fastcall ComponentsDisable(void);
	void __fastcall LoadFromObjectToForm(TProvisioner *CurProvisioner);
	void __fastcall SaveAtFormToObject(TProvisioner *CurProvisioner);

private:	// User declarations

public:		// User declarations
	__fastcall TFormProvisionerData(TComponent* Owner);

	TProvisioner *TmpProvisioner;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormProvisionerData *FormProvisionerData;
//---------------------------------------------------------------------------
#endif
