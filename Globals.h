#pragma once

class Globals
{
public:
	HWND TF2Window;
	bool RenderInit;
	ImFont* Font1;
	ImFont* Font2;
	C_BaseEntity* LocalPlayer;
private:
}; extern Globals* g_Globals;