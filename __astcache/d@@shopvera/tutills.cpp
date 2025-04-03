//---------------------------------------------------------------------------

#pragma hdrstop

#include "TUtills.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

unsigned long TUtills::i;
unsigned TUtills::j;
UnicodeString TUtills::uStr;
wchar_t* TUtills::wTmp;

//---------------------------------------------------------------------------
unsigned long TUtills::ParseWstring(wchar_t *wStr, wchar_t **pws, unsigned Count, unsigned long MaxOffset)
{
	i = 0;
	j = 0;

	while(i < MaxOffset) {
		if(wStr[i] == L'\n') {
			i += 1;
			break;
		}

		while(i < MaxOffset) {
			if(wStr[i++] == L'\'') {
				break;
			}
		}

		if(!(j < Count)) {
			return 0;
		}
		pws[j++] = wStr + i;

		while(i < MaxOffset) {
			if(wStr[i++] == L'\'') {
				wStr[i - 1] = 0;
				break;
			}
		}
	}

	if(j == Count) {
		return i;
	} else {
		return 0;
	}
}
//---------------------------------------------------------------------------
unsigned long TUtills::ParseString(char *Str, char **pws, unsigned Count, unsigned long MaxOffset)
{
	i = 0;
	j = 0;

	while(i < MaxOffset) {
		if(Str[i] == '\r' && Str[i+1] == '\n') {
			i += 2;
			break;
		}

		while(i < MaxOffset) {
			if(Str[i++] == '\'') {
				break;
			}
		}

		if(!(j < Count)) {
			return 0;
		}
		pws[j++] = Str + i;

		while(i < MaxOffset) {
			if(Str[i++] == '\'') {
				Str[i - 1] = 0;
				break;
			}
		}
	}

	if(j == Count) {
		return i;
	} else {
		return 0;
	}
}
//---------------------------------------------------------------------------
wchar_t* TUtills::ReplaceSymbol(wchar_t *wStr, wchar_t FindSymb, wchar_t ReplaceSymb)
{
	uStr = wStr;
	wTmp = uStr.w_str();

	unsigned len = wcslen(wStr);

	for(i = 0; i < len; i++) {
		if(wTmp[i] == FindSymb) {
			wTmp[i] = ReplaceSymb;
		}
	}

	return wTmp;
}
//---------------------------------------------------------------------------
wchar_t* TUtills::ReplaceSymbol(wchar_t *wStr, wchar_t *FindStr, wchar_t *ReplaceStr)
{
	uStr = wStr;
	StringReplace(uStr, FindStr, ReplaceStr, TReplaceFlags() << rfReplaceAll);

	return uStr.w_str();

/*	uStr = wStr;
	wTmp = uStr.w_str();

	len = wcslen(wStr);
	unsigned lenF = wcslen(FindStr);
	unsigned lenR = wcslen(ReplaceStr);

	for(i = 0; i < len; i++) {
		for(j = 0; j <
		if(wTmp[i] == FindSymb) {
			wTmp[i] = ReplaceSymb;
		}
	}

	return wTmp;    */
}
//---------------------------------------------------------------------------

