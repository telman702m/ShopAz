//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Declaration.h"
#include "UnitUserStatus.h"
#include "Shop.h"
#include "ShopUnits.h"
#include "Workers.h"
#include "SelectProduct.h"
#include "UnitLogs.h"
#include "ObjectManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const wchar_t *wSelectUnit[] = {
	L"Выберите объект сети магазинов",
	L"Mağazalar şəbəkədən obyekt seçin"
};

const wchar_t *wStartLoadBD[] = {
	L"Загрузка с Базы Данных будет осуществлена начиная с даты %s",
	L"Məlumat Bazadan informasiya yüklənəcək başlıyaraq %s tarixindən"
};
const wchar_t *wNotPrivileg[] = {
	L"Вы не обладаете привилегией для изменения даты загрузки данных с БД: загрузка будет с %s",
	L"Məlumat Bazadan informasiyanın başlancıq yüklənmə tarixini dəyişmək üçün sizin kifayət imtiyazınız yoxdur. Yüklənmə %s tarixindən başlıyacaq"
};
const wchar_t *wDataLoadType[] = {
	L"Загрузить основные данные из локальных файлов",
	L"Əsas məlumatları lokal fayllardan yüklənilsin"
};
const wchar_t *wConnectInfo[] = {
	L"%s %s %s, Вы подключились к объекту %s.\n%s",
	L"%s %s %s, Siz %s obyektinə qoşulmusunuz.\n%s"
};
const wchar_t *wIncorrectLoginPasswd[] = {
	L"Неверный логин или пароль!",
	L"Login və yə parol səhvdir!"
};
const wchar_t *wExistUser[] = {
	L"В системе уже присутствует данный пользователь, подключенный к указанному объекту магазинов!",
	L"Bu adlı istifadəçi artıq mövcüddur sistemdə (qoşulub qeyd etdiyiniz obyekta mağazalar şəbəkəsində)!"
};

TLabelCaption LabelCaptionsUserStatus[] = {
	{{L"Выбор объекта",	L"Obyektin seçməsi"},	NULL},
	{{L"Login:",		L"Login:"},				NULL},
	{{L"Password",		L"Parol"},				NULL},
	{{L"Дата загрузки",	L"Yükləmə tarixi"},		NULL}
};
TButtonCaption ButtonCaptionUserStatus[] = {
	{{L"Ok",		L"Ok"},		NULL},
	{{L"Отмена",	L"Cancel"},	NULL}
};

TFormUserStatus *FormUserStatus;

//---------------------------------------------------------------------------
__fastcall TFormUserStatus::TFormUserStatus(TComponent* Owner)
	: TFormEsc(Owner)
{
	wFormCaptions[0] = L"Статус пользователя";
	wFormCaptions[1] = L"İstifadəçinin statusu";

	SizeLabelsData = sizeof(LabelCaptionsUserStatus) / sizeof(TLabelCaption);
	LabelsCaption = LabelCaptionsUserStatus;

	SizeButtonsData = sizeof(ButtonCaptionUserStatus) / sizeof(TButtonCaption);
	ButtonsCaption = ButtonCaptionUserStatus;

	bStartDateChanged = false;
	bSuccess = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormUserStatus::FormCreate(TObject *Sender)
{
	DateTimePickerStartData->Format = wDateTimePickerFormat;

	LabelsCaption[0].Label = LabelUnitShop;
	LabelsCaption[1].Label = LabelLogin;
	LabelsCaption[2].Label = LabelPassword;
	LabelsCaption[3].Label = LabelLastLoadDate;

	ButtonsCaption[0].Button = ButtonOk;
	ButtonsCaption[1].Button = ButtonCancel;

	SetLanguage();
}
//---------------------------------------------------------------------------
void __fastcall TFormUserStatus::FormShow(TObject *Sender)
{
	bSuccess = false;

	ComboBoxShopUnits->Clear();
	for(unsigned i=0; i < TObjectManager<TShopUnits>::GetList().size(); i++) {
		ComboBoxShopUnits->Items->Add(TObjectManager<TShopUnits>::GetList()[i]->Name);
	}

	CheckBoxLoadType->Caption = wDataLoadType[iLang];

	if(FormShop->uLastShopUnit != L"") {
		ComboBoxShopUnits->ItemIndex = FormShop->uLastShopUnit.ToInt();
	} else {
		ComboBoxShopUnits->Text = wSelectUnit[iLang];
	}

	EditLogin->Text = FormShop->uLastWorkerName;

	ComboBoxShopUnitsChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormUserStatus::ComboBoxShopUnitsChange(TObject *Sender)
{
	EditPassword->Text = L"";
	EditPassword->Text = L"";

	if(ComboBoxShopUnits->ItemIndex != -1) {
		LabelLogin->Enabled = true;
		EditLogin->Enabled = true;
		LabelPassword->Enabled = true;
		EditPassword->Enabled = true;
		LabelLastLoadDate->Enabled = true;
		DateTimePickerStartData->Enabled = true;

		FormShop->ShopUnit = TObjectManager<TShopUnits>::GetList()[ComboBoxShopUnits->ItemIndex];
		DateTimePickerStartData->Time = 0;
		DateTimePickerStartData->Date = FormShop->ShopUnit->LoadDateData;

		EditPassword->SetFocus();
	}

}
//---------------------------------------------------------------------------
void __fastcall TFormUserStatus::ButtonOkClick(TObject *Sender)
{
/*	bool bSaveConfig = false;

	if(ComboBoxShopUnits->ItemIndex != FormShop->uLastShopUnit.ToInt()) {
		FormShop->SlistConfig->Strings[1] = ComboBoxShopUnits->ItemIndex;
		bSaveConfig = true;
	}

	if(EditLogin->Text != FormShop->uLastWorkerName) {
		FormShop->SlistConfig->Strings[2] = EditLogin->Text;
		bSaveConfig = true;
	}
	if(bSaveConfig) {
		FormShop->SlistConfig->SaveToFile(ExtractFilePath(Application->ExeName) + "Config.tshp");
	}
*/
	FormShop->uLastShopUnit = ComboBoxShopUnits->ItemIndex;
	FormShop->uLastWorkerName = EditLogin->Text;


	UnicodeString uTmp = L"", uTmp2 = L" ";
	bSuccess = false;

	for(unsigned i=0; i < TObjectManager<TWorkers>::GetList().size(); i++) {
		if(TObjectManager<TWorkers>::GetList()[i]->idUnitShop == FormShop->ShopUnit->id) {

			if(EditLogin->Text == TObjectManager<TWorkers>::GetList()[i]->Login && EditPassword->Text == TObjectManager<TWorkers>::GetList()[i]->Password) {
					FormShop->Worker = TObjectManager<TWorkers>::GetList()[i];

					if(DateTimePickerStartData->Date != FormShop->ShopUnit->LoadDateData) {
						if(FormShop->Worker->Privilege < TPrivilege::PRV_MANAGER) {

							FormShop->ShopUnit->UpdateStartDate(FormShop->FDQuery1, DateTimePickerStartData->Date, FormShop->ShopUnit->id);
							FormShop->ShopUnit->LoadDateData = DateTimePickerStartData->Date;

							uTmp2.sprintf(wStartLoadBD[iLang], FormShop->ShopUnit->LoadDateData.DateString().w_str());
						} else {
							uTmp2.sprintf(wNotPrivileg[iLang], FormShop->ShopUnit->LoadDateData.DateString().w_str());
						}
					}
					// Check exists identical user in system
					FormLogs->LoadLogs(true);

					for(unsigned j=0; j < TLogs::VLogsData.size(); j++) {

						if(TLogs::VLogsData[j]->ConnectStatus &&
						   TLogs::VLogsData[j]->IdWorker == FormShop->Worker->id &&
						   TLogs::VLogsData[j]->IdShopU == FormShop->Worker->idUnitShop) {
								ShowMessage(wExistUser[iLang]);
								return;
						   }
					}

                    FormShop->MenuesEnable(true);
					bSuccess = true;
					Close();
					return;
			   }
			}
	}
	ShowMessage(wIncorrectLoginPasswd[iLang]);
}
//---------------------------------------------------------------------------
void __fastcall TFormUserStatus::EditPasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN) {
		ButtonOkClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormUserStatus::ButtonCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormUserStatus::DateTimePickerStartDataChange(TObject *Sender)
{
	bStartDateChanged = true;
}
//---------------------------------------------------------------------------

