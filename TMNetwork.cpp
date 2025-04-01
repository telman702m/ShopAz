//---------------------------------------------------------------------------
#pragma hdrstop

#include "TMNetwork.h"
#include <iphlpapi.h>
#include <winsock2.h>
#include <algorithm>
#include <sstream>
#include <iomanip>

#pragma comment(lib, "iphlpapi.lib")
//---------------------------------------------------------------------------
#pragma package(smart_init)


#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))


template <typename T>
static std::string HexToString(T uval)
{
	std::stringstream ss;
	ss << std::setw(sizeof(uval) * 2) << std::setfill('0') << std::hex << +uval;
	std::string strToConvert = ss.str();
	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);
	return strToConvert;
}

UnicodeString TMNetwork::MacAddress;
//---------------------------------------------------------------------------
void TMNetwork::GetMacAddress(void)
{
	MacAddress = L"";

    std::wstring result;
    unsigned int i;
	DWORD dwRetVal;
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    ULONG family = AF_INET;
    PIP_ADAPTER_ADDRESSES pAddresses;
    ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
    pAddresses = (IP_ADAPTER_ADDRESSES *)MALLOC(outBufLen);

    if (GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        FREE(pAddresses);
        pAddresses = (IP_ADAPTER_ADDRESSES *)MALLOC(outBufLen);
    }

    if (pAddresses == NULL)
		return;

    dwRetVal = GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);
    if (dwRetVal == NO_ERROR)
    {
        if (pAddresses->PhysicalAddressLength != 0)
        {
            std::string str;
            for (i = 0; i < pAddresses->PhysicalAddressLength; i++)
            {
                if (i == (pAddresses->PhysicalAddressLength - 1))
					str += HexToString((unsigned char)pAddresses->PhysicalAddress[i]);
				else
					str += HexToString((unsigned char)pAddresses->PhysicalAddress[i]) + ":";
			}
			result = std::wstring(str.begin(), str.end());
        }
    }
	FREE(pAddresses);

	MacAddress = MacAddress.sprintf(L"%s", result.c_str());
}
