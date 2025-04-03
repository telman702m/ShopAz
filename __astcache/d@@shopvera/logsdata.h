//---------------------------------------------------------------------------
#ifndef LogsDataH
#define LogsDataH
//---------------------------------------------------------------------------
#include <vector>
#include "Declaration.h"
#include "LogsDetails.h"

//---------------------------------------------------------------------------
class TLogData
{
private:

public:
	int ConnectedId;
	int IdWorker;
	int IdShopU;
	TPrivilege Privilege;
	TDateTime StartDate;
	TDateTime EndDate;

	TDateTime LastAccess;
	bool bRefreshLastAccess;

	bool ConnectStatus;
	MEXIT ExitStatus;

	vector <TLogDetails*> VLogDetails;
};
#endif
