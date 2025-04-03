﻿// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdCookieManager.pas' rev: 35.00 (Windows)

#ifndef IdcookiemanagerHPP
#define IdcookiemanagerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdCookie.hpp>
#include <IdHeaderList.hpp>
#include <IdURI.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idcookiemanager
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdCookieManager;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOnNewCookieEvent)(System::TObject* ASender, Idcookie::TIdCookie* ACookie, bool &VAccept);

typedef void __fastcall (__closure *TOnCookieManagerEvent)(System::TObject* ASender, Idcookie::TIdCookies* ACookieCollection);

typedef TOnCookieManagerEvent TOnCookieCreateEvent;

typedef TOnCookieManagerEvent TOnCookieDestroyEvent;

class PASCALIMPLEMENTATION TIdCookieManager : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
protected:
	TOnCookieManagerEvent FOnCreate;
	TOnCookieManagerEvent FOnDestroy;
	TOnNewCookieEvent FOnNewCookie;
	Idcookie::TIdCookies* FCookieCollection;
	void __fastcall CleanupCookieList();
	virtual void __fastcall DoOnCreate();
	virtual void __fastcall DoOnDestroy();
	virtual bool __fastcall DoOnNewCookie(Idcookie::TIdCookie* ACookie);
	virtual void __fastcall InitComponent();
	
public:
	__fastcall virtual ~TIdCookieManager();
	void __fastcall AddServerCookie(const System::UnicodeString ACookie, Iduri::TIdURI* AURL);
	void __fastcall AddServerCookies(System::Classes::TStrings* const ACookies, Iduri::TIdURI* AURL);
	void __fastcall AddCookies(TIdCookieManager* ASource);
	void __fastcall CopyCookie(Idcookie::TIdCookie* ACookie);
	void __fastcall GenerateClientCookies(Iduri::TIdURI* AURL, bool SecureOnly, Idheaderlist::TIdHeaderList* Headers);
	__property Idcookie::TIdCookies* CookieCollection = {read=FCookieCollection};
	
__published:
	__property TOnCookieManagerEvent OnCreate = {read=FOnCreate, write=FOnCreate};
	__property TOnCookieManagerEvent OnDestroy = {read=FOnDestroy, write=FOnDestroy};
	__property TOnNewCookieEvent OnNewCookie = {read=FOnNewCookie, write=FOnNewCookie};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdCookieManager(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdCookieManager()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idcookiemanager */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDCOOKIEMANAGER)
using namespace Idcookiemanager;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdcookiemanagerHPP
