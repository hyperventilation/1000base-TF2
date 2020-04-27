#pragma once

#include "CHandle.h"
#include "IClientNetworkable.h"
#include "IBaseClientDLL.h"
#include "IVEngineClient.h"
#include "IEntity.h"
#include "ISurface.h"
#include "IPlayerInfoManager.h"

namespace I {
	extern IBaseClientDLL* Client;
	extern IVEngineClient* Engine;
	extern IClientEntityList* EntityList;
	extern IGlobalVars* Globals;
	extern IClientModeShared* ClientMode;
	extern ISurface* Surface;
	extern IPlayerInfoManager* PlayerInfo;
}

class Interfaces {
public:
	template <typename t = void*>
	t get_interface(const char* module_name, const char* interface_name) {
		using original_fn = void*(*)(const char*, int*);
		original_fn create_interface = (original_fn)GetProcAddress(GetModuleHandleA(module_name), "CreateInterface");
		return reinterpret_cast< t >(create_interface(interface_name, nullptr));
	}

	void InitInterfaces();

private:
}; extern Interfaces* g_Interfaces;