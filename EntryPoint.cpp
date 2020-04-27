#include "Main.h"

// I`ll update this base when i have free time.

void Initialize() {
	while (!(g_Globals->TF2Window = FindWindowA("Valve001", NULL))) // Get TF2 window handle into global vars
		Sleep(200);

	Hooks::oldWindowProc = (WNDPROC)SetWindowLongPtr(g_Globals->TF2Window, GWL_WNDPROC, (LONG_PTR)Hooks::WndProc);
	g_Globals->isPanorama = GetModuleHandleA("client.dll");
	g_Interfaces->InitInterfaces(); // initialisation of interfaces
	g_pNetvars = new CNetVars(); // initialisation of NetVar manager
	g_Utils->InitHooks(); // initialisation of hooks
}

bool __stdcall DllMain(void* dll_instance, unsigned long reason_to_call, void* reserved) {
	switch (reason_to_call) {
	case DLL_PROCESS_ATTACH: // if DLL attached to CSGO
		DisableThreadLibraryCalls((HMODULE)dll_instance);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Initialize, dll_instance, 0, 0);
		break;
	}

	return true;
}