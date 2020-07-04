#include "Main.h"

CreateMoveFn oCreateMove;

#define flags g_Globals->LocalPlayer->GetFlags()

bool __stdcall Hooks::CreateMove(float flInputSampleTime, CUserCmd* pCmd)
{
	std::memcpy(&I::Panels->GetLatestViewMatrix(), &I::Engine->WorldToScreenMatrix(), sizeof(D3DMATRIX)); // I don't know, PT didn't work. Probably due to thread safe.

	auto bCreateMoveReturn = oCreateMove(flInputSampleTime, pCmd);

	if (!pCmd || !pCmd->command_number)
		return bCreateMoveReturn;

	g_Globals->LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	auto do_bunnyhop = [&](void)
	{
		static bool bReleased = true;
		if (pCmd->buttons & IN_JUMP) {
			if (bReleased == false)
			{
				if (!(flags & FL_ONGROUND))
					pCmd->buttons &= ~IN_JUMP;
			}
			else
				bReleased = false;
		}
		else if (bReleased == false)
			bReleased = true;
	};

	do_bunnyhop();

	return bCreateMoveReturn; // If you want silent aim, return false, but make sure to call SetViewAngles manually.
}


