#include "Main.h"

CreateMoveFn oCreateMove;

#define FLAGS g_Globals->LocalPlayer->GetFlags()

bool __stdcall Hooks::CreateMove(float flInputSampleTime, CUserCmd * pCmd)
{
	std::memcpy(&I::Panels->GetLatestViewMatrix(), &I::Engine->WorldToScreenMatrix(), sizeof(D3DMATRIX)); // I don't know, PT didn't work. Probably due to thread safe.

	const auto b_create_move_return = oCreateMove(flInputSampleTime, pCmd);

	if (!pCmd || !pCmd->command_number)
	{
		return b_create_move_return;
	}

	g_Globals->LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	auto do_bunnyhop = [&]()
	{
		static bool b_released = true;
		if (pCmd->buttons & IN_JUMP) {
			if (!b_released)
			{
				if (!(FLAGS & FL_ONGROUND))
					pCmd->buttons &= ~(1 << 1);
			}
			else
				b_released = false;
		}
		else if (!b_released)
			b_released = true;
	};

	do_bunnyhop();
	return b_create_move_return; // If you want silent aim, return false, but make sure to call SetViewAngles manually.
}


