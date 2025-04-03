//---------------------------------------------------------------------------
#ifndef TUtillsH
#define TUtillsH
//---------------------------------------------------------------------------

#include <vcl.h>

//const int MaxLen =

class TUtills
{
private:
	static unsigned long i;
	static unsigned j;
	static UnicodeString uStr;
	static wchar_t *wTmp;

public:
	static unsigned long ParseWstring(wchar_t *wStr, wchar_t **pws, unsigned Count, unsigned long MaxOffset);
	static unsigned long ParseString(char *Str, char **pws, unsigned Count, unsigned long MaxOffset);
	static wchar_t* ReplaceSymbol(wchar_t *wStr, wchar_t FindSymb, wchar_t ReplaceSymb);
	static wchar_t* ReplaceSymbol(wchar_t *wStr, wchar_t *FindStr, wchar_t *ReplaceStr);

};
#endif
