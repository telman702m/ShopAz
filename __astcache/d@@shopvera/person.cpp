//---------------------------------------------------------------------------
#pragma hdrstop

#include "Person.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TPerson::TPerson(void) : TBaseData()
{
	Clear();
}
//---------------------------------------------------------------------------
void __fastcall TPerson::Clear(void)
{
	Surname = L"";
	Name = L"";
	Patronymic = L"";
	Address = L"";
	Phone1 = L"";
	Phone2 = L"";
	Description = L"";
	Enabled = false;

	SumName = L"";
	SetPricesZero();
}

//---------------------------------------------------------------------------
void __fastcall TPerson::SetPricesZero()
{
	TotalShoped = 0;
	TotalReturn = 0;
	TotalIncoming = 0;
	TotalMoved = 0;
	TotalDiscount = 0;
	TotalDebt = 0;
	TotalExpenses = 0;
}

//---------------------------------------------------------------------------
__fastcall TPerson::TPerson(const TPerson &Person) : TBaseData(Person)
{
	Surname = Person.Surname;
	Name = Person.Name;
	Patronymic = Person.Patronymic;

	Address = Person.Address;
	Phone1 = Person.Phone1;
	Phone2 = Person.Phone2;
	Description = Person.Description;
	Enabled = Person.Enabled;

	SumName = Person.SumName;

	TotalShoped = Person.TotalShoped;
	TotalReturn = Person.TotalReturn;
	TotalIncoming = Person.TotalIncoming;
	TotalMoved = Person.TotalMoved;
	TotalDiscount = Person.TotalDiscount;
	TotalDebt = Person.TotalDebt;
	TotalExpenses = Person.TotalExpenses;
}
//---------------------------------------------------------------------------
const TPerson& __fastcall TPerson::operator=(const TPerson &Person)
{
	TBaseData::operator = (Person);

	Surname = Person.Surname;
	Name = Person.Name;
	Patronymic = Person.Patronymic;

	Address = Person.Address;
	Phone1 = Person.Phone1;
	Phone2 = Person.Phone2;
	Description = Person.Description;
	Enabled = Person.Enabled;

	SumName = Person.SumName;

	TotalShoped = Person.TotalShoped;
	TotalReturn = Person.TotalReturn;
	TotalIncoming = Person.TotalIncoming;
	TotalMoved = Person.TotalMoved;
	TotalDiscount = Person.TotalDiscount;
	TotalDebt = Person.TotalDebt;
	TotalExpenses = Person.TotalExpenses;

	return *this;
}

//---------------------------------------------------------------------------
void __fastcall TPerson::SetSumName(void)
{
	SumName = Surname + L" " + Name + L" " + Patronymic;
}
//---------------------------------------------------------------------------



