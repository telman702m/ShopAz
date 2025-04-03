//---------------------------------------------------------------------------
#ifndef TMyHTTPSH
#define TMyHTTPSH

#include <Vcl.h>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>


//---------------------------------------------------------------------------
class TMyHTTPS : public TObject
{
private:
	TComponent *AComponent;

public:
	TIdHTTP *IdHTTP1;
    TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL1;

    __fastcall TMyHTTPS(TComponent *_AComponent);
    __fastcall ~TMyHTTPS(void);
};
//---------------------------------------------------------------------------
#endif
