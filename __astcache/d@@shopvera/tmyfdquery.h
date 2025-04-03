//---------------------------------------------------------------------------
#ifndef TMyFDQueryH
#define TMyFDQueryH

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

typedef struct _TFieldsValues {
	const wchar_t *Field;
	const wchar_t *Value;
}TFieldsValues;

const int MAX_COUNT_ATTEMPT = 16;

//---------------------------------------------------------------------------
class TMyFDQuery : public TFDQuery
{
private:

public:
	__fastcall TMyFDQuery(TComponent* Owner);

	int __fastcall MyInsert(const wchar_t *TableName, const wchar_t *AutoIncrementName, TFieldsValues *FieldsValues, const int Count);
	int __fastcall MyInsert2(const wchar_t *TableName, const wchar_t *AutoIncrementName, TFieldsValues *FieldsValues, const int Count);
};
#endif
