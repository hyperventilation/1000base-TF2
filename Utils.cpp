#include "Main.h"

void Utils::InitHooks()
{
	std::unique_ptr<CVMTHookManager> ClientMode;
	ClientMode = std::make_unique<CVMTHookManager>(I::ClientMode);
	std::unique_ptr<CVMTHookManager> Surface;
	Surface = std::make_unique<CVMTHookManager>(I::Surface);
	DWORD dwPresent = Utils::FindPatternIDA("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 DB") + 0x2;
	DWORD dwReset = Utils::FindPatternIDA("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18") + 0x2;

	oLockCursor = (LockCursorFn)Surface->dwHookMethod((DWORD)Hooks::LockCursor, 62);
	oCreateMove = (CreateMoveFn)ClientMode->dwHookMethod((DWORD)Hooks::CreateMove, 21);
	oPresent = (PresentFn)((new CVMTHookManager((PDWORD*)dwPresent))->dwHookMethod((DWORD)&Hooks::Present, 0));
	oReset = (ResetFn)((new CVMTHookManager((PDWORD*)dwReset))->dwHookMethod((DWORD)&Hooks::Reset, 0));
}

bool Utils::WorldToScreen(const Vector& origin, Vector& screen)
{
	int iScreenWidth, iScreenHeight;
	I::Engine->GetScreenSize(iScreenWidth, iScreenHeight);
	const VMatrix& worldToScreen = I::Engine->WorldToScreenMatrix(); 

	float w = worldToScreen[3][0] * origin[0] + worldToScreen[3][1] * origin[1] + worldToScreen[3][2] * origin[2] + worldToScreen[3][3]; 
	screen.z = 0; 

	if (w > 0.001) 
	{
		float fl1DBw = 1 / w; 
		screen.x = (iScreenWidth / 2) + (0.5 * ((worldToScreen[0][0] * origin[0] + worldToScreen[0][1] * origin[1] + worldToScreen[0][2] * origin[2] + worldToScreen[0][3]) * fl1DBw) * iScreenWidth + 0.5); 
		screen.y = (iScreenHeight / 2) - (0.5 * ((worldToScreen[1][0] * origin[0] + worldToScreen[1][1] * origin[1] + worldToScreen[1][2] * origin[2] + worldToScreen[1][3]) * fl1DBw) * iScreenHeight + 0.5); 
		return true;
	}

	return false;
}

DWORD Utils::FindPatternIDA(std::string moduleName, std::string pattern)
{
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo;
	K32GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}

	return NULL;
}