//---------------------------------------------------------------------------
#pragma hdrstop

#include "Declaration.h"
#include "Price.h"
#include "Math.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)

INT64 TPrice::PW = INT64(100);
UnicodeString TPrice::uHidden = L"*****";

//---------------------------------------------------------------------------
TPrice::TPrice(int _Money)
{
	Money = _Money;
	Cent = 0;
	Sign = sgn(Money);
	Val = INT64(Sign) * (INT64(Money) * PW + INT64(Cent));
}
//---------------------------------------------------------------------------
TPrice::TPrice(double dPrice)
{
	Money = int(dPrice);
	Sign = sgn(Money);

	Cent = Round(dPrice - double(Money)) * PW;

	Money *= Sign;
	Cent *= Sign;

	Val = INT64(Sign) * (INT64(Money) * PW + INT64(Cent));
}
//---------------------------------------------------------------------------
TPrice::TPrice(UnicodeString uStr)
{
	unsigned len = uStr.Length();
	wchar_t *wTmp = uStr.w_str();
	wchar_t *wRez = new wchar_t[len + 2];

	unsigned j = 0;
	for(unsigned i=0; i < len; i++) {
		if(wTmp[i] != FSet.ThousandSeparator) {
			wRez[j++] = wTmp[i];
		}
	}
	wRez[j] = 0;

	double d = StrToFloat(wRez, FSet);
	delete[] wRez;

	*this = TPrice(d);
}

//---------------------------------------------------------------------------
TPrice::TPrice(const TPrice &Price)
{
  Money = Price.Money;
  Cent = Price.Cent;
  Sign = Price.Sign;
  Val = Price.Val;
}
//---------------------------------------------------------------------------
const TPrice& TPrice::operator=(const TPrice& Price)
{
  Money = Price.Money;
  Cent = Price.Cent;
  Sign = Price.Sign;
  Val = Price.Val;

  return *this;
}
//---------------------------------------------------------------------------
void TPrice::ValToPrice(void)
{
	if(Val < 0) {
		Sign = -1;
		Money = -Val / PW;
		Cent = -Val % PW;
	} else {
		Sign = 1;
		Money = Val / PW;
		Cent = Val % PW;
	}
}
//---------------------------------------------------------------------------
double TPrice::Round(double x, int precision)
{
	int mul = 10;

	for (int i = 0; i < precision; i++) {
		mul *= mul;
	}
	if(x > 0) {
		return floor(x * mul + 0.5) / mul;
	} else {
		return ceil(x * mul - 0.5) / mul;
	}
}
//---------------------------------------------------------------------------
double TPrice::Round(double x)
{
	int mul = 100;

	if(x > 0) {
		return floor(x * mul + 0.5) / mul;
	} else {
		return ceil(x * mul - 0.5) / mul;
	}
}
//---------------------------------------------------------------------------
TPrice TPrice::operator*(const int &Scalar)
{
	TPrice temp;

	temp.Val = Val * INT64(Scalar);

	temp.ValToPrice();

	return temp;
}

//---------------------------------------------------------------------------
TPrice& TPrice::operator*=(const int &Scalar)
{
	Val *= INT64(Scalar);

	ValToPrice();

	return *this;
}

//---------------------------------------------------------------------------
TPrice TPrice::operator+(const TPrice &Price2)
{
	TPrice temp;

	temp.Val = Val + Price2.Val;
	temp.ValToPrice();

	return temp;
}
//---------------------------------------------------------------------------
TPrice TPrice::operator-(const TPrice &Price2)
{
	TPrice temp;

	temp.Val = Val - Price2.Val;
	temp.ValToPrice();

	return temp;
}
//---------------------------------------------------------------------------
TPrice& TPrice::operator+=(const TPrice &Price2)
{
	Val += Price2.Val;
    ValToPrice();

	return *this;
}
//---------------------------------------------------------------------------
TPrice& TPrice::operator-=(const TPrice &Price2)
{
	Val -= Price2.Val;
    ValToPrice();

	return *this;
}

//---------------------------------------------------------------------------
bool TPrice::operator>(const TPrice &Price)
{
	return Val > Price.Val;
}
//---------------------------------------------------------------------------
bool TPrice::operator<(const TPrice &Price)
{
	return Val < Price.Val;
}
//---------------------------------------------------------------------------
bool TPrice::operator==(const TPrice &Price)
{
	return Val == Price.Val;
}
//---------------------------------------------------------------------------
bool TPrice::operator!=(const TPrice &Price)
{
	return Val != Price.Val;
}

//---------------------------------------------------------------------------
double TPrice::GetValue(void)
{
	return double(Sign) * (double(Money) + double(Cent) / double(PW));
}

//---------------------------------------------------------------------------
UnicodeString TPrice::StringFormat(void)
{
	double dValue = GetValue();

	return FormatFloat(L"#,##0.00", dValue, FSet);
}

//---------------------------------------------------------------------------
void TPrice::SetOnEdit(TEdit *Edit1, TEdit *Edit2)
{
	UnicodeString uTmp = L"";
	if(Sign == -1) {
		uTmp = L"-";
	}
	uTmp += Money;

	Edit1->Text = uTmp;
	Edit2->Text = Cent;
}

//---------------------------------------------------------------------------
void TPrice::SetString(UnicodeString uMoney, UnicodeString uCent)
{
	Money = uMoney.ToInt();
	Cent = uCent.ToInt();

	Sign = 1;
	Val = INT64(Sign) * (INT64(Money) * PW + INT64(Cent));
}
//---------------------------------------------------------------------------
void TPrice::GetFromTEdit(TEdit *Edit1, TEdit *Edit2)
{
	*this = 0;

	if(Edit1->Text != L"") {
		Money = Edit1->Text.ToInt();
	}
	if(Edit2->Text != L"") {
		Cent = Edit2->Text.ToInt();
	}

	if(Money < 0) {
		Sign = -1;
		Money = -Money;
	} else {
		Sign = 1;
    }
	Val = INT64(Sign) * (INT64(Money) * PW + INT64(Cent));
}
//---------------------------------------------------------------------------
TPrice TPrice::SetPercent(double dPercent)
{
	TPrice PriceTmp;

	double dTmp = GetValue() * dPercent / 100.;

	PriceTmp = dTmp;

	return PriceTmp;
}

//---------------------------------------------------------------------------
double TPrice::GetPercent(TPrice &Price2)
{
	if(GetValue() != 0.) {
		return Price2.GetValue() * 100. / GetValue();
	} else {
		return 0.;
    }
}


//---------------------------------------------------------------------------
TPrice TPrice::operator*(const TCount &Count)
{
	TCount temp = Count;

	return temp * (*this);
}

//---------------------------------------------------------------------------
TPrice& TPrice::operator*=(const TCount &Count)
{
	*this = (*this) * Count;

	return *this;
}
//---------------------------------------------------------------------------
UnicodeString TPrice::SpaceDelimeterClear(UnicodeString uStr)
{
	unsigned len = uStr.Length();
	wchar_t *wTmp = uStr.w_str();
	wchar_t *wRez = new wchar_t[len];

	unsigned j = 0;
	for(unsigned i=0; i < len; i++) {
		if(wTmp[i] != L' ' && wTmp[i] != 0x00a0) {
			wRez[j++] = wTmp[i];
		}
    }
	wRez[j] = 0;
	UnicodeString uRez(wRez);
	return uRez;
}
//---------------------------------------------------------------------------
void TPrice::SpaceDelimeterClear2(UnicodeString uStr)
{
	unsigned len = uStr.Length();
	wchar_t *wTmp = uStr.w_str();
	wchar_t *wRez = new wchar_t[len];

	unsigned j = 0;
	for(unsigned i=0; i < len; i++) {
		if(wTmp[i] != L' ') {
			wRez[j++] = wTmp[i];
		}
    }
	wRez[j] = 0;
	uStr = wRez;
}

//---------------------------------------------------------------------------

