#include "Main.h"

void Utils::InitHooks()
{
	std::unique_ptr<CVMTHookManager> client_mode = std::make_unique<CVMTHookManager>(I::ClientMode);
	std::unique_ptr<CVMTHookManager> panel = std::make_unique<CVMTHookManager>(I::Panels);
	std::unique_ptr<CVMTHookManager> surface = std::make_unique<CVMTHookManager>(I::Surface);

	const auto dwPresent = Utils::FindPatternIDA("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 DB") + 0x2;
	const auto dwReset = Utils::FindPatternIDA("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18") + 0x2;

	oCreateMove = reinterpret_cast<CreateMoveFn>(client_mode->dwHookMethod(
		reinterpret_cast<DWORD>(Hooks::CreateMove), 21));
	
	oPaintTraverse = reinterpret_cast<PaintTraverseFn>(panel->dwHookMethod(
		reinterpret_cast<DWORD>(Hooks::PaintTraverse), 41));
	
	oLockCursor = reinterpret_cast<LockCursorFn>(surface->dwHookMethod(reinterpret_cast<DWORD>(Hooks::LockCursor), 62));
	
	oPresent = reinterpret_cast<PresentFn>((new CVMTHookManager(reinterpret_cast<DWORD**>(dwPresent)))->dwHookMethod(
		reinterpret_cast<DWORD>(&Hooks::Present), 0));
	
	oReset = reinterpret_cast<ResetFn>((new CVMTHookManager(reinterpret_cast<DWORD**>(dwReset)))->dwHookMethod(
		reinterpret_cast<DWORD>(&Hooks::Reset), 0));
}

bool Utils::WorldToScreen(const Vector& origin, Vector& screen)
{
	const auto screen_transform = [&origin, &screen]() -> bool
	{
		const auto & w2_s_matrix = static_cast<D3DMATRIX>(I::Panels->GetLatestViewMatrix());

		screen.x = w2_s_matrix.m[0][0] * origin.x + w2_s_matrix.m[0][1] * origin.y + w2_s_matrix.m[0][2] * origin.z + w2_s_matrix.m[0][3];
		screen.y = w2_s_matrix.m[1][0] * origin.x + w2_s_matrix.m[1][1] * origin.y + w2_s_matrix.m[1][2] * origin.z + w2_s_matrix.m[1][3];
		screen.z = 0.0f;

		const auto w = w2_s_matrix.m[3][0] * origin.x + w2_s_matrix.m[3][1] * origin.y + w2_s_matrix.m[3][2] * origin.z + w2_s_matrix.m[3][3];

		if (w < 0.001f)
		{
			screen.x *= 100000;
			screen.y *= 100000;
			return true;
		}

		const float invw = 1.f / w;
		screen.x *= invw;
		screen.y *= invw;

		return false;
	};

	if (!screen_transform())
	{
		int i_screen_width;
		int i_screen_height;
		I::Engine->GetScreenSize(i_screen_width, i_screen_height);

		screen.x = (i_screen_width * 0.5f) + (screen.x * i_screen_width) * 0.5f;
		screen.y = (i_screen_height * 0.5f) - (screen.y * i_screen_height) * 0.5f;

		return true;
	}
	return false;
}

DWORD Utils::FindPatternIDA(std::string moduleName, const std::string & pattern)
{
	auto pat = pattern.c_str();
	DWORD first_match = 0;
	const auto range_start = DWORD(GetModuleHandleA(moduleName.c_str()));
	MODULEINFO miModInfo;
	K32GetModuleInformation(GetCurrentProcess(), HMODULE(range_start), &miModInfo, sizeof(MODULEINFO));
	const auto range_end = range_start + miModInfo.SizeOfImage;
	for (auto p_cur = range_start; p_cur < range_end; p_cur++)
	{
		if (!*pat)
			return first_match;

		if (*(PBYTE)pat == '\?' || *(BYTE*)p_cur == getByte(pat))
		{
			if (!first_match)
				first_match = p_cur;

			if (!pat[2])
				return first_match;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = pattern.c_str();
			first_match = 0;
		}
	}

	return NULL;
}