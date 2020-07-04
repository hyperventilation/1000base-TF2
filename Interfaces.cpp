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
	I::Engine = g_Interfaces->get_interface<IVEngineClient*>("engine.dll", "VEngineClient013");
	I::EntityList = g_Interfaces->get_interface<IClientEntityList*>("client.dll", "VClientEntityList003");
	I::Panels = g_Interfaces->get_interface<Panel*>("vgui2.dll", "VGUI_Panel009");
	I::Surface = g_Interfaces->get_interface<ISurface*>("vguimatsurface.dll", "VGUI_Surface030");
	I::DebugOverlay = g_Interfaces->get_interface<IVDebugOverlay*>("engine.dll", "VDebugOverlay003");
	I::PlayerInfo = g_Interfaces->get_interface<IPlayerInfoManager*>("server.dll", "PlayerInfoManager002");

	DWORD dwClientModeAddress = g_Utils->FindPatternIDA("client.dll", "8B 0D ? ? ? ? 8B 02 D9 05");
	I::ClientMode = **(IClientModeShared***)( dwClientModeAddress + 2);  
	I::Globals = I::PlayerInfo->GetGlobalVars();
}