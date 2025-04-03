//---------------------------------------------------------------------------
#ifndef LogsDetailsH
#define LogsDetailsH
//---------------------------------------------------------------------------
#include "Declaration.h"

//---------------------------------------------------------------------------
class TLogDetails
{
private:

public:
	TDateTime DateTime;
	TabDB IdTable;
	LOGS IdOperation;
	UnicodeString CommandSQL;
};
#endif
