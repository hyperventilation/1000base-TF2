#pragma once
#include "Main.h"

class Panel
{
public:
	D3DMATRIX& GetLatestViewMatrix( void )
	{
		static D3DMATRIX m;
		return m;
	}
	unsigned int GetPanel(int type)
	{
		typedef unsigned int(__thiscall* tGetPanel)(void*, int type);
		return g_Utils->get_vfunc<tGetPanel>(this, 1)(this, type);
	}
	void SetMouseInputEnabled(unsigned int panel, bool state)
	{
		g_Utils->get_vfunc<void(__thiscall*)(void*, int, bool)>(this, 32)(this, panel, state);
	}
	void SetTopmostPopup(unsigned int panel, bool state)
	{
		g_Utils->get_vfunc<void(__thiscall*)(void*, int, bool)>(this, 59)(this, panel, state);
	}
	const char* GetName(unsigned int vguiPanel)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, unsigned int);
		return g_Utils->get_vfunc<OriginalFn>(this, 36)(this, vguiPanel);
	}
};