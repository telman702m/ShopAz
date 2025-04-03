//---------------------------------------------------------------------------
#ifndef BaseDataTemplatesH
#define BaseDataTemplatesH
//---------------------------------------------------------------------------
#include "TBaseData.h"
#include "ObjectManager.h"
#include "Shop.h"
#include "Synchronize.h"
#include "Declaration.h"
#include "UnitParent.h"


template <class T>
void __fastcall TBaseData::ExecSQL_Managed(TMyFDQuery *FDQuery, UnicodeString &QuerySQL, const wchar_t *TableName,
								TabDB TypeTableDB, TRecordType RecordType, LOGS Logs)
{
	TimerSyncDisable();

	switch (RecordType) {
		case TRecordType::RT_INSERT:
			ShowMessage(L"Insert нельзя использовать через TBaseData");
			break;

		case TRecordType::RT_UPDATE:
		{
			T* found = TObjectManager<T>::FindById(id);
			if (found)
				*found = *static_cast<T*>(this);
			else
				ShowMessage(L"Не найден объект для обновления по ID");
			break;
		}

		case TRecordType::RT_DELETE:
		{
			T* found = TObjectManager<T>::FindById(id);
			if (found)
				found->bDeleted = true;
			else
				ShowMessage(L"Не найден объект для удаления по ID");
			break;
		}

		default:
			break;
	}

	bool bSuccess = ExecOnlySQL(FDQuery, QuerySQL);

	if (RecordType != TRecordType::RT_UNDEF)
		TSynchronize::InsertToDb(FDQuery, TypeTableDB, id, RecordType);

	if (Logs != LOGS::LG_UNDEF) {
		FormShop->CurrentLog->Set(TypeTableDB, Logs, QuerySQL);
		FormShop->CurrentLog->InsertToDb(FDQuery);
	}

	TimerSyncRestore();
}

//---------------------------------------------------------------------------
template <class T>
void __fastcall TBaseData::ExecSQL_Managed(TMyFDQuery *FDQuery, TFieldsValues *FieldsValues, int Count,
								const wchar_t *TableName, wchar_t *AutoIncrement, TabDB TypeTableDB)
{
	TimerSyncDisable();

	bool bSuccess = false;
	while (!bSuccess) {
		try {
			id = FDQuery->MyInsert(TableName, AutoIncrement, FieldsValues, Count);

			// добавляем объект в менеджер
			TObjectManager<T>::Add(static_cast<T*>(this));

			bSuccess = true;

		} catch (...) {
			uTmp = uTmp.sprintf(wLostConnection[iLang], wOperationName[TRecordType::RT_INSERT], TableName);
			if (Application->MessageBox(uTmp.w_str(), uCaptionWarning[iLang], MB_YESNO + MB_ICONQUESTION) == IDNO) {
				Application->Terminate();
				exit(1);
			}
			bSuccess = false;
		}
	}

	TSynchronize::InsertToDb(FDQuery, TypeTableDB, id, TRecordType::RT_INSERT);

	FormShop->CurrentLog->Set(TypeTableDB, LOGS::LG_INSERT, FDQuery->SQL->Text);
	FormShop->CurrentLog->InsertToDb(FDQuery);

	TimerSyncRestore();
}


//---------------------------------------------------------------------------
template <class T>
bool __fastcall TBaseData::ApplyBaseSyncronize_Managed(TMyFDQuery *FDQuery, TSynchronize *SyncData, TFormParent *FormParent)
{
	bool bCreateObject = false;
	id = SyncData->idRecord;

	switch (SyncData->RecordType)
	{
		case TRecordType::RT_INSERT:
		{
			if (LoadRecordId(FDQuery)) {
				TObjectManager<T>::Add(static_cast<T*>(this));
				bCreateObject = true;
			}
			break;
		}

		case TRecordType::RT_UPDATE:
		{
			T* existing = TObjectManager<T>::FindById(id);
			if (existing) {
				if (LoadRecordId(FDQuery)) {
					*existing = *static_cast<T*>(this);
					bCreateObject = true;
				}
			}
			break;
		}

		case TRecordType::RT_DELETE:
		{
			T* existing = TObjectManager<T>::FindById(id);
			if (existing) {
				TObjectManager<T>::DeleteAndFree(existing);
			}
			break;
		}

		default:
			break;
	}

	// Обновление визуального интерфейса
	if (FormParent != NULL) {
		FormParent->bListUpdate = true;
		if (FormParent->Showing) {
			FormParent->MyListView->FillList();
		}
	}

	return bCreateObject;
}

//---------------------------------------------------------------------------
template <class T>
bool __fastcall CheckSortById_Managed(const wchar_t* typeName)
{
	auto& list = TObjectManager<T>::GetList();

	for (size_t i = 1; i < list.size(); ++i)
	{
		if (list[i]->id <= list[i - 1]->id)
		{
			UnicodeString msg;
			msg = msg.sprintf(L"Нарушен порядок сортировки для объектов %s", typeName);
			Application->MessageBox(msg.w_str(), L"Ошибка", MB_OK);
			return false;
		}
	}

	return true;
}
//---------------------------------------------------------------------------
#endif
