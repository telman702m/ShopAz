﻿// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdWship6.pas' rev: 35.00 (Windows)

#ifndef Idwship6HPP
#define Idwship6HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SyncObjs.hpp>
#include <IdGlobal.hpp>
#include <Winapi.Windows.hpp>
#include <IdWinsock2.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idwship6
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
#define Wship6_dll L"Wship6.dll"
#define iphlpapi_dll L"iphlpapi.dll"
#define fwpuclnt_dll L"Fwpuclnt.dll"
extern DELPHI_PACKAGE bool GIdIPv6FuncsAvailable _DEPRECATED_ATTRIBUTE0 ;
extern DELPHI_PACKAGE int __fastcall gaiErrorToWsaError(const int gaiError);
extern DELPHI_PACKAGE void __fastcall CloseLibrary(void);
extern DELPHI_PACKAGE void __fastcall InitLibrary(void);
}	/* namespace Idwship6 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDWSHIP6)
using namespace Idwship6;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idwship6HPP
