﻿// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHTTP.pas' rev: 35.00 (Windows)

#ifndef IdhttpHPP
#define IdhttpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdException.hpp>
#include <IdExceptionCore.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdHeaderList.hpp>
#include <IdHTTPHeaderInfo.hpp>
#include <IdReplyRFC.hpp>
#include <IdSSL.hpp>
#include <IdZLibCompressorBase.hpp>
#include <IdTCPClient.hpp>
#include <IdURI.hpp>
#include <IdCookie.hpp>
#include <IdCookieManager.hpp>
#include <IdAuthentication.hpp>
#include <IdAuthenticationManager.hpp>
#include <IdMultipartFormData.hpp>
#include <IdGlobal.hpp>
#include <IdBaseComponent.hpp>
#include <IdUriUtils.hpp>
#include <IdTCPConnection.hpp>
#include <IdComponent.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idhttp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHTTPResponse;
class DELPHICLASS TIdHTTPRequest;
class DELPHICLASS TIdHTTPProtocol;
class DELPHICLASS TIdCustomHTTP;
class DELPHICLASS TIdHTTP;
class DELPHICLASS EIdUnknownProtocol;
class DELPHICLASS EIdHTTPProtocolException;
//-- type declarations -------------------------------------------------------
typedef System::UnicodeString TIdHTTPMethod;

enum DECLSPEC_DENUM TIdHTTPWhatsNext : unsigned char { wnGoToURL, wnJustExit, wnDontKnow, wnReadAndGo, wnAuthRequest };

enum DECLSPEC_DENUM TIdHTTPConnectionType : unsigned char { ctNormal, ctSSL, ctProxy, ctSSLProxy };

enum DECLSPEC_DENUM TIdHTTPOption : unsigned char { hoInProcessAuth, hoKeepOrigProtocol, hoForceEncodeParams, hoNonSSLProxyUseConnectVerb, hoNoParseMetaHTTPEquiv, hoWaitForUnexpectedData, hoTreat302Like303, hoNoProtocolErrorException, hoNoReadMultipartMIME, hoNoParseXmlCharset, hoWantProtocolErrorContent, hoNoReadChunked };

typedef System::Set<TIdHTTPOption, TIdHTTPOption::hoInProcessAuth, TIdHTTPOption::hoNoReadChunked> TIdHTTPOptions;

enum DECLSPEC_DENUM TIdHTTPProtocolVersion : unsigned char { pv1_0, pv1_1 };

typedef void __fastcall (__closure *TIdHTTPOnRedirectEvent)(System::TObject* Sender, System::UnicodeString &dest, int &NumRedirect, bool &Handled, System::UnicodeString &VMethod);

typedef void __fastcall (__closure *TIdHTTPOnHeadersAvailable)(System::TObject* Sender, Idheaderlist::TIdHeaderList* AHeaders, bool &VContinue);

typedef void __fastcall (__closure *TIdOnSelectAuthorization)(System::TObject* Sender, Idauthentication::TIdAuthenticationClass &AuthenticationClass, Idheaderlist::TIdHeaderList* AuthInfo);

typedef void __fastcall (__closure *TIdOnAuthorization)(System::TObject* Sender, Idauthentication::TIdAuthentication* Authentication, bool &Handled);

typedef void __fastcall (__closure *TIdOnChunkReceived)(System::TObject* Sender, Idglobal::TIdBytes &Chunk);

class PASCALIMPLEMENTATION TIdHTTPResponse : public Idhttpheaderinfo::TIdResponseHeaderInfo
{
	typedef Idhttpheaderinfo::TIdResponseHeaderInfo inherited;
	
protected:
	TIdCustomHTTP* FHTTP;
	int FResponseCode;
	System::UnicodeString FResponseText;
	bool FKeepAlive;
	System::Classes::TStream* FContentStream;
	TIdHTTPProtocolVersion FResponseVersion;
	Idhttpheaderinfo::TIdMetaHTTPEquiv* FMetaHTTPEquiv;
	bool __fastcall GetKeepAlive();
	int __fastcall GetResponseCode();
	void __fastcall SetResponseText(const System::UnicodeString AValue);
	void __fastcall ProcessMetaHTTPEquiv();
	
public:
	__fastcall virtual TIdHTTPResponse(TIdCustomHTTP* AHTTP);
	__fastcall virtual ~TIdHTTPResponse();
	virtual void __fastcall Clear();
	__property bool KeepAlive = {read=GetKeepAlive, write=FKeepAlive, nodefault};
	__property Idhttpheaderinfo::TIdMetaHTTPEquiv* MetaHTTPEquiv = {read=FMetaHTTPEquiv};
	__property System::UnicodeString ResponseText = {read=FResponseText, write=SetResponseText};
	__property int ResponseCode = {read=GetResponseCode, write=FResponseCode, nodefault};
	__property TIdHTTPProtocolVersion ResponseVersion = {read=FResponseVersion, write=FResponseVersion, nodefault};
	__property System::Classes::TStream* ContentStream = {read=FContentStream, write=FContentStream};
};


class PASCALIMPLEMENTATION TIdHTTPRequest : public Idhttpheaderinfo::TIdRequestHeaderInfo
{
	typedef Idhttpheaderinfo::TIdRequestHeaderInfo inherited;
	
protected:
	TIdCustomHTTP* FHTTP;
	System::UnicodeString FURL;
	System::UnicodeString FMethod;
	System::Classes::TStream* FSourceStream;
	TIdHTTPConnectionType FUseProxy;
	Idglobal::TIdIPVersion FIPVersion;
	System::UnicodeString FDestination;
	
public:
	__fastcall virtual TIdHTTPRequest(TIdCustomHTTP* AHTTP);
	__property System::UnicodeString URL = {read=FURL, write=FURL};
	__property System::UnicodeString Method = {read=FMethod, write=FMethod};
	__property System::Classes::TStream* Source = {read=FSourceStream, write=FSourceStream};
	__property TIdHTTPConnectionType UseProxy = {read=FUseProxy, nodefault};
	__property Idglobal::TIdIPVersion IPVersion = {read=FIPVersion, write=FIPVersion, nodefault};
	__property System::UnicodeString Destination = {read=FDestination, write=FDestination};
public:
	/* TIdRequestHeaderInfo.Destroy */ inline __fastcall virtual ~TIdHTTPRequest() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdHTTPProtocol : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TIdCustomHTTP* FHTTP;
	TIdHTTPRequest* FRequest;
	TIdHTTPResponse* FResponse;
	
public:
	__fastcall TIdHTTPProtocol(TIdCustomHTTP* AConnection);
	__fastcall virtual ~TIdHTTPProtocol();
	TIdHTTPWhatsNext __fastcall ProcessResponse(short *AIgnoreReplies, const int AIgnoreReplies_High);
	void __fastcall BuildAndSendRequest(Iduri::TIdURI* AURI);
	void __fastcall RetrieveHeaders(int AMaxHeaderCount);
	__property TIdHTTPRequest* Request = {read=FRequest};
	__property TIdHTTPResponse* Response = {read=FResponse};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIdCustomHTTP : public Idtcpclient::TIdTCPClientCustom
{
	typedef Idtcpclient::TIdTCPClientCustom inherited;
	
protected:
	int FAuthRetries;
	int FAuthProxyRetries;
	Idcookiemanager::TIdCookieManager* FCookieManager;
	Idzlibcompressorbase::TIdZLibCompressorBase* FCompressor;
	bool FImplicitCookieManager;
	int FMaxAuthRetries;
	int FMaxHeaderLines;
	bool FAllowCookies;
	Idauthenticationmanager::TIdAuthenticationManager* FAuthenticationManager;
	TIdHTTPProtocolVersion FProtocolVersion;
	int FRedirectCount;
	int FRedirectMax;
	bool FHandleRedirects;
	TIdHTTPOptions FOptions;
	Iduri::TIdURI* FURI;
	TIdHTTPProtocol* FHTTPProto;
	Idhttpheaderinfo::TIdProxyConnectionInfo* FProxyParameters;
	TIdHTTPOnHeadersAvailable FOnHeadersAvailable;
	TIdHTTPOnRedirectEvent FOnRedirect;
	TIdOnSelectAuthorization FOnSelectAuthorization;
	TIdOnSelectAuthorization FOnSelectProxyAuthorization;
	TIdOnAuthorization FOnAuthorization;
	TIdOnAuthorization FOnProxyAuthorization;
	TIdOnChunkReceived FOnChunkReceived;
	virtual void __fastcall DoRequest(const System::UnicodeString AMethod, System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent, short *AIgnoreReplies, const int AIgnoreReplies_High);
	virtual TIdHTTPProtocol* __fastcall CreateProtocol();
	virtual void __fastcall InitComponent();
	System::UnicodeString __fastcall InternalReadLn();
	void __fastcall SetAuthenticationManager(Idauthenticationmanager::TIdAuthenticationManager* Value);
	void __fastcall SetCookieManager(Idcookiemanager::TIdCookieManager* ACookieManager);
	void __fastcall SetAllowCookies(bool AValue);
	int __fastcall GetResponseCode();
	System::UnicodeString __fastcall GetResponseText();
	virtual bool __fastcall DoOnAuthorization(TIdHTTPRequest* ARequest, TIdHTTPResponse* AResponse);
	virtual bool __fastcall DoOnProxyAuthorization(TIdHTTPRequest* ARequest, TIdHTTPResponse* AResponse);
	virtual bool __fastcall DoOnRedirect(System::UnicodeString &Location, System::UnicodeString &VMethod, int RedirectCount);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall ProcessCookies(TIdHTTPRequest* ARequest, TIdHTTPResponse* AResponse);
	TIdHTTPConnectionType __fastcall SetHostAndPort();
	void __fastcall SetCookies(Iduri::TIdURI* AURL, TIdHTTPRequest* ARequest);
	void __fastcall ReadResult(TIdHTTPRequest* ARequest, TIdHTTPResponse* AResponse);
	void __fastcall PrepareRequest(TIdHTTPRequest* ARequest);
	void __fastcall ConnectToHost(TIdHTTPRequest* ARequest, TIdHTTPResponse* AResponse);
	HIDESBASE TIdHTTPResponse* __fastcall GetResponse();
	TIdHTTPRequest* __fastcall GetRequest();
	Idhttpheaderinfo::TIdMetaHTTPEquiv* __fastcall GetMetaHTTPEquiv();
	void __fastcall SetRequest(TIdHTTPRequest* Value);
	void __fastcall SetProxyParams(Idhttpheaderinfo::TIdProxyConnectionInfo* AValue);
	System::UnicodeString __fastcall SetRequestParams(System::Classes::TStrings* ASource, Idglobal::_di_IIdTextEncoding AByteEncoding);
	void __fastcall CheckAndConnect(TIdHTTPRequest* ARequest, TIdHTTPResponse* AResponse);
	virtual void __fastcall DoOnDisconnected();
	
public:
	__fastcall virtual ~TIdCustomHTTP();
	void __fastcall Delete(System::UnicodeString AURL, System::Classes::TStream* AResponseContent)/* overload */;
	System::UnicodeString __fastcall Delete(System::UnicodeString AURL)/* overload */;
	void __fastcall Options(System::UnicodeString AURL, System::Classes::TStream* AResponseContent)/* overload */;
	System::UnicodeString __fastcall Options(System::UnicodeString AURL)/* overload */;
	void __fastcall Get(System::UnicodeString AURL, System::Classes::TStream* AResponseContent)/* overload */;
	void __fastcall Get(System::UnicodeString AURL, System::Classes::TStream* AResponseContent, short *AIgnoreReplies, const int AIgnoreReplies_High)/* overload */;
	System::UnicodeString __fastcall Get(System::UnicodeString AURL)/* overload */;
	System::UnicodeString __fastcall Get(System::UnicodeString AURL, short *AIgnoreReplies, const int AIgnoreReplies_High)/* overload */;
	void __fastcall Trace(System::UnicodeString AURL, System::Classes::TStream* AResponseContent)/* overload */;
	System::UnicodeString __fastcall Trace(System::UnicodeString AURL)/* overload */;
	void __fastcall Head(System::UnicodeString AURL);
	System::UnicodeString __fastcall Post(System::UnicodeString AURL, const System::UnicodeString ASourceFile)/* overload */;
	System::UnicodeString __fastcall Post(System::UnicodeString AURL, System::Classes::TStrings* ASource, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	System::UnicodeString __fastcall Post(System::UnicodeString AURL, System::Classes::TStream* ASource)/* overload */;
	System::UnicodeString __fastcall Post(System::UnicodeString AURL, Idmultipartformdata::TIdMultiPartFormDataStream* ASource)/* overload */;
	void __fastcall Post(System::UnicodeString AURL, const System::UnicodeString ASourceFile, System::Classes::TStream* AResponseContent)/* overload */;
	void __fastcall Post(System::UnicodeString AURL, System::Classes::TStrings* ASource, System::Classes::TStream* AResponseContent, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	void __fastcall Post(System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent)/* overload */;
	void __fastcall Post(System::UnicodeString AURL, Idmultipartformdata::TIdMultiPartFormDataStream* ASource, System::Classes::TStream* AResponseContent)/* overload */;
	System::UnicodeString __fastcall Put(System::UnicodeString AURL, System::Classes::TStream* ASource)/* overload */;
	void __fastcall Put(System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent)/* overload */;
	void __fastcall Patch(System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent)/* overload */;
	System::UnicodeString __fastcall Patch(System::UnicodeString AURL, System::Classes::TStream* ASource)/* overload */;
	__property Idzlibcompressorbase::TIdZLibCompressorBase* Compressor = {read=FCompressor, write=FCompressor};
	__property int ResponseCode = {read=GetResponseCode, nodefault};
	__property System::UnicodeString ResponseText = {read=GetResponseText};
	__property TIdHTTPResponse* Response = {read=GetResponse};
	__property Idhttpheaderinfo::TIdMetaHTTPEquiv* MetaHTTPEquiv = {read=GetMetaHTTPEquiv};
	__property Iduri::TIdURI* URL = {read=FURI};
	__property int AuthRetries = {read=FAuthRetries, nodefault};
	__property int AuthProxyRetries = {read=FAuthProxyRetries, nodefault};
	__property int MaxAuthRetries = {read=FMaxAuthRetries, write=FMaxAuthRetries, default=3};
	__property bool AllowCookies = {read=FAllowCookies, write=SetAllowCookies, default=1};
	__property bool HandleRedirects = {read=FHandleRedirects, write=FHandleRedirects, default=0};
	__property TIdHTTPProtocolVersion ProtocolVersion = {read=FProtocolVersion, write=FProtocolVersion, default=1};
	__property int RedirectCount = {read=FRedirectCount, nodefault};
	__property int RedirectMaximum = {read=FRedirectMax, write=FRedirectMax, default=15};
	__property int MaxHeaderLines = {read=FMaxHeaderLines, write=FMaxHeaderLines, default=255};
	__property Idhttpheaderinfo::TIdProxyConnectionInfo* ProxyParams = {read=FProxyParameters, write=SetProxyParams};
	__property TIdHTTPRequest* Request = {read=GetRequest, write=SetRequest};
	__property TIdHTTPOptions HTTPOptions = {read=FOptions, write=FOptions, nodefault};
	__property TIdHTTPOnHeadersAvailable OnHeadersAvailable = {read=FOnHeadersAvailable, write=FOnHeadersAvailable};
	__property TIdHTTPOnRedirectEvent OnRedirect = {read=FOnRedirect, write=FOnRedirect};
	__property TIdOnSelectAuthorization OnSelectAuthorization = {read=FOnSelectAuthorization, write=FOnSelectAuthorization};
	__property TIdOnSelectAuthorization OnSelectProxyAuthorization = {read=FOnSelectProxyAuthorization, write=FOnSelectProxyAuthorization};
	__property TIdOnAuthorization OnAuthorization = {read=FOnAuthorization, write=FOnAuthorization};
	__property TIdOnAuthorization OnProxyAuthorization = {read=FOnProxyAuthorization, write=FOnProxyAuthorization};
	__property TIdOnChunkReceived OnChunkReceived = {read=FOnChunkReceived, write=FOnChunkReceived};
	__property Idcookiemanager::TIdCookieManager* CookieManager = {read=FCookieManager, write=SetCookieManager};
	__property Idauthenticationmanager::TIdAuthenticationManager* AuthenticationManager = {read=FAuthenticationManager, write=SetAuthenticationManager};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdCustomHTTP(System::Classes::TComponent* AOwner)/* overload */ : Idtcpclient::TIdTCPClientCustom(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdCustomHTTP()/* overload */ : Idtcpclient::TIdTCPClientCustom() { }
	
};


class PASCALIMPLEMENTATION TIdHTTP : public TIdCustomHTTP
{
	typedef TIdCustomHTTP inherited;
	
__published:
	__property MaxAuthRetries = {default=3};
	__property AllowCookies = {default=1};
	__property HandleRedirects = {default=0};
	__property ProtocolVersion = {default=1};
	__property RedirectMaximum = {default=15};
	__property ProxyParams;
	__property Request;
	__property HTTPOptions;
	__property OnHeadersAvailable;
	__property OnRedirect;
	__property OnSelectAuthorization;
	__property OnSelectProxyAuthorization;
	__property OnAuthorization;
	__property OnProxyAuthorization;
	__property OnChunkReceived;
	__property CookieManager;
	__property Compressor;
public:
	/* TIdCustomHTTP.Destroy */ inline __fastcall virtual ~TIdHTTP() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdHTTP(System::Classes::TComponent* AOwner)/* overload */ : TIdCustomHTTP(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdHTTP()/* overload */ : TIdCustomHTTP() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdUnknownProtocol : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdUnknownProtocol(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdUnknownProtocol(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdUnknownProtocol(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdUnknownProtocol(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdUnknownProtocol(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdUnknownProtocol(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdUnknownProtocol(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdUnknownProtocol(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdUnknownProtocol(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdUnknownProtocol(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdUnknownProtocol(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdUnknownProtocol(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdUnknownProtocol() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdHTTPProtocolException : public Idreplyrfc::EIdReplyRFCError
{
	typedef Idreplyrfc::EIdReplyRFCError inherited;
	
protected:
	System::UnicodeString FErrorMessage;
	
public:
	__fastcall virtual EIdHTTPProtocolException(const int anErrCode, const System::UnicodeString asReplyMessage, const System::UnicodeString asErrorMessage);
	__property System::UnicodeString ErrorMessage = {read=FErrorMessage};
public:
	/* EIdException.Create */ inline __fastcall virtual EIdHTTPProtocolException(const System::UnicodeString AMsg)/* overload */ : Idreplyrfc::EIdReplyRFCError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdHTTPProtocolException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idreplyrfc::EIdReplyRFCError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdHTTPProtocolException(NativeUInt Ident)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdHTTPProtocolException(System::PResStringRec ResStringRec)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdHTTPProtocolException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdHTTPProtocolException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdHTTPProtocolException(const System::UnicodeString Msg, int AHelpContext) : Idreplyrfc::EIdReplyRFCError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdHTTPProtocolException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idreplyrfc::EIdReplyRFCError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdHTTPProtocolException(NativeUInt Ident, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdHTTPProtocolException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdHTTPProtocolException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdHTTPProtocolException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdHTTPProtocolException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define Id_HTTPMethodHead L"HEAD"
#define Id_HTTPMethodGet L"GET"
#define Id_HTTPMethodPost L"POST"
#define Id_HTTPMethodOptions L"OPTIONS"
#define Id_HTTPMethodTrace L"TRACE"
#define Id_HTTPMethodPut L"PUT"
#define Id_HTTPMethodDelete L"DELETE"
#define Id_HTTPMethodConnect L"CONNECT"
#define Id_HTTPMethodPatch L"PATCH"
static const TIdHTTPProtocolVersion Id_TIdHTTP_ProtocolVersion = (TIdHTTPProtocolVersion)(1);
static const System::Int8 Id_TIdHTTP_RedirectMax = System::Int8(0xf);
static const System::Byte Id_TIdHTTP_MaxHeaderLines = System::Byte(0xff);
static const bool Id_TIdHTTP_HandleRedirects = false;
static const System::Int8 Id_TIdHTTP_MaxAuthRetries = System::Int8(0x3);
}	/* namespace Idhttp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHTTP)
using namespace Idhttp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdhttpHPP
