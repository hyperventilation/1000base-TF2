#include "Main.h"

CreateMoveFn oCreateMove;

bool __stdcall Hooks::CreateMove(float flInputSampleTime, CUserCmd* pCmd)
{
	auto bCreateMoveReturn = oCreateMove(flInputSampleTime, pCmd); // Cause that`s fix a lot of bugs w/ this hook

	if (!pCmd || !pCmd->command_number)
		return bCreateMoveReturn;

	g_Globals->LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
    static int ticks_jump;
	if (pCmd->buttons & IN_JUMP)
	{
        if (ticks_jump++ >= 9)
            pCmd->buttons = pCmd->buttons & ~IN_JUMP;
	}
    if (!(pCmd->buttons & IN_JUMP))
		ticks_jump = 0;

	return false;
}
