﻿// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdZLibCompressorBase.pas' rev: 35.00 (Windows)

#ifndef IdzlibcompressorbaseHPP
#define IdzlibcompressorbaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdStream.hpp>
#include <IdIOHandler.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idzlibcompressorbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdZLibCompressorBase;
//-- type declarations -------------------------------------------------------
typedef System::Int8 TIdCompressionLevel;

class PASCALIMPLEMENTATION TIdZLibCompressorBase : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
protected:
	virtual bool __fastcall GetIsReady();
	
public:
	virtual void __fastcall DeflateStream(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream, const TIdCompressionLevel ALevel = (TIdCompressionLevel)(0x0)) = 0 ;
	virtual void __fastcall InflateStream(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream) = 0 ;
	virtual void __fastcall CompressStream(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream, const TIdCompressionLevel ALevel, const int AWindowBits, const int AMemLevel, const int AStrategy) = 0 ;
	virtual void __fastcall DecompressStream(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream, const int AWindowBits) = 0 ;
	virtual void __fastcall DecompressDeflateStream(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream);
	void __fastcall CompressFTPDeflate(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream, const int ALevel, const int AWindowBits, const int AMemLevel, const int AStrategy);
	virtual void __fastcall CompressFTPToIO(System::Classes::TStream* AInStream, Idiohandler::TIdIOHandler* AIOHandler, const int ALevel, const int AWindowBits, const int AMemLevel, const int AStrategy) = 0 ;
	virtual void __fastcall DecompressFTPFromIO(Idiohandler::TIdIOHandler* AIOHandler, System::Classes::TStream* AOutputStream, const int AWindowBits) = 0 ;
	void __fastcall DecompressFTPDeflate(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream, const int AWindowBits);
	void __fastcall CompressHTTPDeflate(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream, const TIdCompressionLevel ALevel);
	void __fastcall DecompressHTTPDeflate(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream);
	virtual void __fastcall DecompressGZipStream(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream);
	__property bool IsReady = {read=GetIsReady, nodefault};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdZLibCompressorBase(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdZLibCompressorBase()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdZLibCompressorBase() { }
	
};


#ifndef _WIN64
typedef System::TMetaClass* TIdZLibCompressorBaseClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TIdZLibCompressorBaseClass);
#endif /* _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idzlibcompressorbase */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDZLIBCOMPRESSORBASE)
using namespace Idzlibcompressorbase;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdzlibcompressorbaseHPP
