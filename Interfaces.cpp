#include "Main.h"

IBaseClientDLL* I::Client = nullptr;
IVEngineClient* I::Engine = nullptr;
IClientEntityList* I::EntityList = nullptr;
IGlobalVars* I::Globals = nullptr;
IClientModeShared* I::ClientMode = nullptr;
Panel* I::Panels = nullptr;
ISurface* I::Surface = nullptr;
IVDebugOverlay* I::DebugOverlay = nullptr;
IPlayerInfoManager* I::PlayerInfo = nullptr;

void Interfaces::InitInterfaces()
{
	I::Client = g_Interfaces->get_interface<IBaseClientDLL*>("client.dll", "VClient017");
	I::Engine = static_cast<IVEngineClient*>(g_Interfaces->brute_iface("EngineClient", "VEngineClient", "g_pEngine", "engine.dll"));
	I::EntityList = g_Interfaces->get_interface<IClientEntityList*>("client.dll", "VClientEntityList003");
	I::Panels = g_Interfaces->get_interface<Panel*>("vgui2.dll", "VGUI_Panel009");
	I::Surface = g_Interfaces->get_interface<ISurface*>("vguimatsurface.dll", "VGUI_Surface030");
	I::DebugOverlay = g_Interfaces->get_interface<IVDebugOverlay*>("engine.dll", "VDebugOverlay003");
	I::PlayerInfo = g_Interfaces->get_interface<IPlayerInfoManager*>("server.dll", "PlayerInfoManager002");

	auto dwCHLClientTable = reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(I::Client));
	I::ClientMode = **reinterpret_cast<IClientModeShared***>(static_cast<DWORD>(dwCHLClientTable[10]) + 0x05);
	I::Globals = I::PlayerInfo->GetGlobalVars();
}