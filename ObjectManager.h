#ifndef ObjectManagerH
#define ObjectManagerH

#include <vector>
#include <algorithm>
#include "TBaseData.h"

// ”ниверсальный менеджер объектов

template <class T>
class TObjectManager
{
public:
	static std::vector<T*>& GetList() {
		static std::vector<T*> VList;
		return VList;
	}

	static void Add(T* obj) {
		GetList().push_back(obj);
	}

	static bool Delete(T* obj) {
		auto& VList = GetList();
		auto it = std::find(VList.begin(), VList.end(), obj);
		if (it != VList.end()) {
			VList.erase(it);
			return true;
		}
		return false;
	}

	static void DeleteAndFree(T* obj) {
		if (Delete(obj)) delete obj;
	}

	static T* FindById(int id) {
		for (auto* obj : GetList()) {
			if (obj->id == id)
				return obj;
		}
		return nullptr;
	}

	static void Clear() {
		for (auto* obj : GetList()) delete obj;
		GetList().clear();
	}

	static size_t Count() {
		return GetList().size();
	}
};

#endif

