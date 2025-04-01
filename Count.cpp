//---------------------------------------------------------------------------
#pragma hdrstop

#include "Declaration.h"
#include "Count.h"
#include "Math.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)

INT64 TCount::PW = INT64(1000000);

//---------------------------------------------------------------------------
TCount::TCount(int _Whole)
{
	Whole = _Whole;
	Fractional = 0;
	Sign = sgn(_Whole);
	Val = INT64(Sign) * (INT64(Whole) * PW + INT64(Fractional));
	bWhole = true;
}
//---------------------------------------------------------------------------
const TCount& TCount::operator=(const TCount& Count)
{
  Whole = Count.Whole;
  Fractional = Count.Fractional;
  Sign = Count.Sign;
  Val = Count.Val;
  bWhole = Count.bWhole;

  return *this;
}
//---------------------------------------------------------------------------
TCount::TCount(int _Whole, int _Fractional, int _Sign)
{
	Whole = _Whole;
	Fractional = _Fractional;
	Sign = _Sign;

	Val = INT64(Sign) * (INT64(Whole) * PW + INT64(Fractional));

	if(Fractional > 0) {
		bWhole = false;
	} else {
		bWhole = true;
	}
}

//---------------------------------------------------------------------------
void TCount::ValToPrice(void)
{
	if(Val < 0) {
		Sign = -1;
		Whole = -Val / PW;
		Fractional = -Val % PW;
	} else {
		Sign = 1;
		Whole = Val / PW;
		Fractional = Val % PW;
	}

	if(Fractional > 0) {
		bWhole = false;
	} else {
		bWhole = true;
	}
}

//---------------------------------------------------------------------------
double TCount::GetValue(void)
{
	return double(Sign) * (double(Whole) + double(Fractional) / double(PW));
}

//---------------------------------------------------------------------------
UnicodeString TCount::StringFormat(void)
{
	double dValue = GetValue();

	return FormatFloat(L"#,##0.00", dValue, FSet);
}

//---------------------------------------------------------------------------
void TCount::SetOnEdit(TEdit *Edit1, TEdit *Edit2)
{
	UnicodeString uTmp = L"";

	if(Sign < 0) {
		uTmp = L"-";
	}
	uTmp += Whole;

	Edit1->Text = uTmp;

	if(Edit2 != NULL) {
		uTmp.sprintf(L"%06d", Fractional);
		uTmp.SetLength(uTmp.Length() - 3);

		Edit2->Text = uTmp;
	}
}
//---------------------------------------------------------------------------
void TCount::SetOnEdit(TEdit *Edit1, TEdit *Edit2, bool bHide)
{
	SetOnEdit(Edit1, Edit2);

	if(bHide) {
		Edit2->Visible = false;
	} else {
		Edit2->Visible = true;
    }
}


//---------------------------------------------------------------------------
void TCount::SetFloat(double dValue)
{
	Val = INT64(dValue) * PW;

    ValToPrice();
}
//---------------------------------------------------------------------------
void TCount::SetString(UnicodeString uWhole, UnicodeString uFractional)
{
	if(uWhole == L"") {
		Whole = 0;
		if(uFractional == L"") {
			Fractional = 0;
			Sign = 1;
			Val = 0;
			return;
		}
	} else {
		Whole = uWhole.ToInt();
	}

	int LenDig;
	if(uFractional.SubString1(1, 1) == L"-") {
		LenDig = 7;
	} else {
    	LenDig = 6;
	}

	UnicodeString uTmp = L"";

	if(uFractional.Length() < LenDig) {
		uTmp = uFractional + UnicodeString::StringOfChar(L'0', LenDig - uFractional.Length());
	} else {
		uTmp = uFractional.SetLength(LenDig);
	}

	Fractional = uTmp.ToInt();

	if(Fractional < 0) {
		Sign = -1;
		Whole = 0;
		Fractional = -Fractional;
	} else if(Whole < 0) {
		Sign = -1;
		Whole = -Whole;
	} else {
		Sign = 1;
	}
	Val = INT64(Sign) * (INT64(Whole) * PW + INT64(Fractional));

	if(Fractional == 0) {
		bWhole = true;
	} else {
        bWhole = false;
    }
}
//---------------------------------------------------------------------------
void TCount::SetFractional(int _Fractional)
{
	Fractional = _Fractional;

	Val = INT64(Sign) * (INT64(Whole) * PW + INT64(Fractional));

	if(Fractional == 0) {
		bWhole = true;
	} else {
		bWhole = false;
	}
}


//---------------------------------------------------------------------------
bool TCount::operator>(const TCount &Count)
{
	return Val > Count.Val;
}
//---------------------------------------------------------------------------
bool TCount::operator>=(const TCount &Count)
{
	return Val >= Count.Val;
}
//---------------------------------------------------------------------------
bool TCount::operator<(const TCount &Count)
{
	return Val < Count.Val;
}
//---------------------------------------------------------------------------
bool TCount::operator<=(const TCount &Count)
{
	return Val <= Count.Val;
}

//---------------------------------------------------------------------------
bool TCount::operator==(const TCount &Count)
{
	return Val == Count.Val;
}
//---------------------------------------------------------------------------
bool TCount::operator!=(const TCount &Count)
{
	return Val != Count.Val;
}
//---------------------------------------------------------------------------
TCount TCount::operator+(const int &Scalar)
{
	TCount temp;

	temp.Val = Val + INT64(Scalar) * PW;

	temp.ValToPrice();

	return temp;
}

//---------------------------------------------------------------------------
TCount TCount::operator-(const int &Scalar)
{
	TCount temp;

	temp.Val = Val - INT64(Scalar) * PW;

	temp.ValToPrice();

	return temp;
}

//---------------------------------------------------------------------------
TCount TCount::operator*(const int &Scalar)
{
	TCount temp;

	temp.Val = Val * INT64(Scalar);

	temp.ValToPrice();

	return temp;
}

//---------------------------------------------------------------------------
TPrice TCount::operator*(const TPrice &Price)
{
	TPrice temp;

	temp.setVal(Val * Price.getVal() / PW);

	temp.ValToPrice();

	return temp;
}

//---------------------------------------------------------------------------
TCount& TCount::operator+=(const int &Scalar)
{
	Val += INT64(Scalar);

	ValToPrice();

	return *this;
}

//---------------------------------------------------------------------------
TCount& TCount::operator-=(const int &Scalar)
{
	Val -= INT64(Scalar);

	ValToPrice();

	return *this;
}

//---------------------------------------------------------------------------
TCount& TCount::operator*=(const int &Scalar)
{
	Val *= INT64(Scalar);

	ValToPrice();

	return *this;
}

//---------------------------------------------------------------------------
TCount TCount::operator+(const TCount &Count2)
{
	TCount temp;

	temp.Val = Val + Count2.Val;

	temp.ValToPrice();

	return temp;
}
//---------------------------------------------------------------------------
TCount TCount::operator-(const TCount &Count2)
{
	TCount temp;

	temp.Val = Val - Count2.Val;

	temp.ValToPrice();

	return temp;
}
//---------------------------------------------------------------------------
TCount& TCount::operator+=(const TCount &Count2)
{
	Val += Count2.Val;

	ValToPrice();

	return *this;
}
//---------------------------------------------------------------------------
TCount& TCount::operator-=(const TCount &Count2)
{
	Val -= Count2.Val;

	ValToPrice();

	return *this;
}

//---------------------------------------------------------------------------


