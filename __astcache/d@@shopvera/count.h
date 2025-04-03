//---------------------------------------------------------------------------
#ifndef CountH
#define CountH

#include "Price.h"
#include <vcl.h>

class TPrice;

//---------------------------------------------------------------------------
class TCount
{
public:
	static INT64 PW;

private:
	int Whole;
	int Fractional;
	int Sign;

	INT64 Val;

	bool bWhole;

public:
	TCount(int _Whole);
	TCount(void) { Whole = 0; Fractional = 0; Sign = 1; Val = 0; bWhole = true; }
	TCount(int _Whole, int _Fractional, int _Sign);
	void ValToPrice(void);

	const TCount& operator=(const TCount& TCount);

	bool operator>(const TCount &Count);
	bool operator>=(const TCount &Count);
	bool operator<(const TCount &Count);
	bool operator<=(const TCount &Count);
	bool operator==(const TCount &Count);
	bool operator!=(const TCount &Count);

	TCount operator+(const int &Scalar);
	TCount operator-(const int &Scalar);
	TCount operator*(const int &Scalar);
	TCount operator+(const TCount &Price2);
	TCount operator-(const TCount &Price2);
//	TCount operator/(const TCount &Price2);
	TCount& operator+=(const int &Scalar);
	TCount& operator-=(const int &Scalar);
	TCount& operator*=(const int &Scalar);
	TCount& operator+=(const TCount &Price2);
	TCount& operator-=(const TCount &Price2);

	TPrice operator*(const TPrice &Price);

	double GetValue(void);
//	void Normalize(void);
	UnicodeString StringFormat(void);
	void SetOnEdit(TEdit *Edit1, TEdit *Edit2);
	void SetOnEdit(TEdit *Edit1, TEdit *Edit2, bool bHide);
	void SetFloat(double dValue);
	void SetString(UnicodeString uWhole, UnicodeString uFractional);

	int GetWhole(void) { return Whole; }
	int GetFractional(void) { return Fractional; }
	bool IsWhole(void) { return bWhole; }
	void SetWhole(int _Whole) { Whole = _Whole; Val = INT64(Sign) * (INT64(Whole) * PW + INT64(Fractional));}
	void SetFractional(int _Fractional);
};

//---------------------------------------------------------------------------
#endif
