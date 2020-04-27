#pragma once
#include "SDK.h"

class IPlayerInfoManager
{
public:
	IGlobalVars* GetGlobalVars()
	{
		typedef IGlobalVars* (__thiscall* OriginalFn)(PVOID);
		return g_Utils->get_vfunc<OriginalFn>(this, 1)(this);
	}
};