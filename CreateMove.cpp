#include "Main.h"

CreateMoveFn oCreateMove;

bool __stdcall Hooks::CreateMove(float flInputSampleTime, CUserCmd* pCmd)
{
	auto bCreateMoveReturn = oCreateMove(flInputSampleTime, pCmd);

	if (!pCmd || !pCmd->command_number)
		return bCreateMoveReturn;

	g_Globals->LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	int iFlags = g_Globals->LocalPlayer->GetFlags();
	static bool bReleased = true;
	if (pCmd->buttons & IN_JUMP) {
		if (bReleased == false)
		{
			if (!(iFlags & FL_ONGROUND)) 
				pCmd->buttons &= ~IN_JUMP;
		} else
			bReleased = false;
	}
	else if (bReleased == false)
		bReleased = true;
	

	return false; 
}
