//---------------------------------------------------------------------------
#ifndef PriceH
#define PriceH

#include "Count.h"
#include <vcl.h>

template <class T>
inline int
sgn(T v) {
	return (v >= T(0)) - (v < T(0));
}

class TCount;
//---------------------------------------------------------------------------

class TPrice
{
private:
	int Money;
	int Cent;
	int Sign;

	INT64 Val;

public:
	static INT64 PW;
	static UnicodeString uHidden;

	TPrice(void) { Money = 0; Cent = 0; Sign = 1; Val = 0;}
	TPrice(int _Money, int _Cent, int _Sign) { Money = _Money; Cent = _Cent; Sign = _Sign;
											   Val = INT64(Sign) * (INT64(Money) * PW + INT64(Cent));
											 }
	TPrice(int _Money);
	TPrice(double dPrice);
	TPrice(UnicodeString uStr);

	TPrice(const TPrice &Price);
	const TPrice& operator=(const TPrice& Price);

	void ValToPrice(void);
	static double Round(double x, int precision);
	static double Round(double x);

	TPrice operator*(const int &Scalar);
	TPrice operator+(const TPrice &Price2);
	TPrice operator-(const TPrice &Price2);
	TPrice& operator*=(const int &Scalar);
	TPrice& operator+=(const TPrice &Price2);
	TPrice& operator-=(const TPrice &Price2);

	TPrice operator*(const TCount &Count);
	TPrice& operator*=(const TCount &Count);
	bool operator>(const TPrice &Price);
	bool operator<(const TPrice &Price);
	bool operator==(const TPrice &Price);
	bool operator!=(const TPrice &Price);

	double GetValue(void);
	UnicodeString StringFormat(void);
	void SetOnEdit(TEdit *Edit1, TEdit *Edit2);
//	void SetFloat(double dValue);
	void SetString(UnicodeString uMoney, UnicodeString uCent);
	void GetFromTEdit(TEdit *Edit1, TEdit *Edit2);
	TPrice SetPercent(double dPercent);
	double GetPercent(TPrice &Price2);

	int GetMoney(void) const { return Money; }
	int GetCent(void) const { return Cent; }
	void SetMoney(int _Money) { Money = _Money; Val = INT64(Sign) * (INT64(Money) * PW + INT64(Cent));}
	void SetCent(int _Cent) { Cent = _Cent; Val = INT64(Sign) * (INT64(Money) * PW + INT64(Cent));}
	INT64 getVal(void) const { return Val; }
	void setVal (INT64 _Val) { Val = _Val; }

	static UnicodeString SpaceDelimeterClear(UnicodeString uStr);
	static void SpaceDelimeterClear2(UnicodeString uStr);

};

#endif
