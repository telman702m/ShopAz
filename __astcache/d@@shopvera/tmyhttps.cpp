//---------------------------------------------------------------------------
#pragma hdrstop

#include "TMyHTTPS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TMyHTTPS::TMyHTTPS(TComponent *_AComponent)
{
	AComponent = _AComponent;

    IdSSLIOHandlerSocketOpenSSL1 = NULL;
	IdSSLIOHandlerSocketOpenSSL1 = new TIdSSLIOHandlerSocketOpenSSL(AComponent);
	IdSSLIOHandlerSocketOpenSSL1->Name = L"IdSSLIOHandlerSocketOpenSSL1";
	IdSSLIOHandlerSocketOpenSSL1->SSLOptions->Method = sslvSSLv23;
	IdSSLIOHandlerSocketOpenSSL1->SSLOptions->Mode = sslmUnassigned;
	IdSSLIOHandlerSocketOpenSSL1->SSLOptions->SSLVersions << sslvTLSv1 << sslvTLSv1_1 << sslvTLSv1_2;

	IdHTTP1 = NULL;
	IdHTTP1 = new TIdHTTP(AComponent);
	IdHTTP1->Name = L"IdHTTP1";
	IdHTTP1->IOHandler = IdSSLIOHandlerSocketOpenSSL1;

	IdHTTP1->Request->BasicAuthentication = true;
	IdHTTP1->Request->Username = "TShopUser";
	IdHTTP1->Request->Password = "Bydfhbfyn0726#$";
	IdHTTP1->HandleRedirects = true;
}
//---------------------------------------------------------------------------
__fastcall TMyHTTPS::~TMyHTTPS(void)
{
	if(IdSSLIOHandlerSocketOpenSSL1 != NULL) {
		delete IdSSLIOHandlerSocketOpenSSL1;
	}

	if(IdHTTP1 != NULL) {
		delete IdHTTP1;
	}
}
//---------------------------------------------------------------------------

