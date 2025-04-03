﻿// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdStreamVCL.pas' rev: 35.00 (Windows)

#ifndef IdstreamvclHPP
#define IdstreamvclHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idstreamvcl
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdStreamHelperVCL;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdStreamHelperVCL : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod int __fastcall ReadBytes(System::Classes::TStream* const AStream, Idglobal::TIdBytes &VBytes, const int ACount = 0xffffffff, const int AOffset = 0x0);
	__classmethod int __fastcall Write(System::Classes::TStream* const AStream, const Idglobal::TIdBytes ABytes, const int ACount = 0xffffffff, const int AOffset = 0x0);
	__classmethod __int64 __fastcall Seek(System::Classes::TStream* const AStream, const __int64 AOffset, const System::Classes::TSeekOrigin AOrigin);
public:
	/* TObject.Create */ inline __fastcall TIdStreamHelperVCL() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdStreamHelperVCL() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idstreamvcl */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSTREAMVCL)
using namespace Idstreamvcl;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdstreamvclHPP
