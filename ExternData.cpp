#include "Declaration.h"

wchar_t wBuffer[MaxBuffer];
char cBuffer[MaxBuffer];

int iLang = 0;

const wchar_t *wDateTimeFormat = L"dd.mm.yyyy  hh:nn";
const wchar_t *wDateTimePickerFormat = L"dd.MM.yyyy";

const wchar_t *uCaptionWarning[2] = {
	L"Предупреждение",
	L"Xəbərdarlıq"
};
const wchar_t *uCaptionError[2] = {
	L"Ошибка",
	L"Səhv"
};
const wchar_t *uCaptionInform[2] = {
	L"Информация",
	L"Məlumat"
};

const wchar_t *uInsert1 = L", ";
const wchar_t *uInsert2 = L"', '";
const wchar_t *uUpdate1 = L"='";
const wchar_t *uUpdate2 = L"', ";

const wchar_t *wLostConnection[2] = {
	L"Потеряна связь с Базой Данных на сервере при выполнении операции MySql: '%ls'  таблица: '%ls'!\n Проверьте Интернет соединение.\n\n Повторить попытку?",
	L"MySql sorğu zamanı Məlumat Bazaynan əlagə kəsilib: Əməliyyət '%ls'  cədvəl: '%ls'!\n İnternetə qoşulması yoxlayın.\n\n Təkrar cəhd etmək?"
};
const wchar_t *wOperationName[3] = {
	L"Insert",
	L"Update",
	L"Delete"
};
const wchar_t *uIllegalSymbol[2] = {
	L"Недопустимый символ в тексте: < ' >\nИспользуйте другой символ!",
	L"Mətndə yararsız symvol mövcüddür: < ' >\nBaşqa symvoldan istifadə edin!"
};


