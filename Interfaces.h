#pragma once

#include "CHandle.h"
#include "IClientNetworkable.h"
#include "IBaseClientDLL.h"
#include "IVEngineClient.h"
#include "IEntity.h"
#include "Panels.h"
#include "ISurface.h"
#include "IVDebugOverlay.h"
#include "IPlayerInfoManager.h"

namespace I {
	extern IBaseClientDLL* Client;
	extern IVEngineClient* Engine;
	extern IClientEntityList* EntityList;
	extern IGlobalVars* Globals;
	extern IClientModeShared* ClientMode;
	extern Panel* Panels;
	extern ISurface* Surface;
	extern IVDebugOverlay* DebugOverlay;
	extern IPlayerInfoManager* PlayerInfo;
}

class Interfaces {
public:
	using original_fn = void* (*)(const char*, int*);
	template <typename t = void*>
	t get_interface(const char* module_name, const char* interface_name) {
		void*(*create_interface)(const char*, int*) = reinterpret_cast<original_fn>(GetProcAddress(
			GetModuleHandleA(module_name), "CreateInterface"));
		return reinterpret_cast< t >(create_interface(interface_name, nullptr));
	}
	void* brute_iface(const char* name, const char* interfacen, const char* ptr_name, const char* pinterface)
	{
		std::string string_interface = "";
		std::string interface_version = "0";

		for (int i = 0; i <= 99; i++)
		{
			string_interface = interfacen;
			string_interface += interface_version;
			string_interface += std::to_string(i);

			original_fn create_interface = (original_fn)GetProcAddress(GetModuleHandleA(pinterface), "CreateInterface");

			void* func_ptr { create_interface(string_interface.c_str(), NULL) };

			if ((DWORD)func_ptr != 0x0)
				return func_ptr;

			if (i >= 99 && interface_version == "0")
			{
				interface_version = "00";
				i = 0;
			}
			else if (i >= 99 && interface_version == "00") { printf("error"); }
		}
		return FALSE;
	}

	static void InitInterfaces();
private:
}; extern Interfaces* g_Interfaces;