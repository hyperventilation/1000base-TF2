#include "Main.h"

Color Visuals::GetTeamColor(C_BaseEntity* ent)
{
	// 2 red
	// 3 blu

	return (ent->GetTeamNum() == 2 ? Color(255, 102, 0, 255) : ent->GetTeamNum() == 3 ? Color(0, 102, 255, 255) : Color(255, 255, 255, 255));
}

void Visuals::ESP()
{
	if (I::Engine->IsInGame() && I::Engine->IsConnected()) { // Check if player has joined a game and is connected to the game.
		for (int i = 1; i <= I::Engine->GetMaxClients(); ++i) // Iteration starts at 1 because 0 is CWorld.
		{
			C_BaseEntity* Entity = I::EntityList->GetClientEntity(i);
			if (!Entity
				|| !Entity->GetLifeState() == 0
				|| !Entity->GetHealth() > 0
				|| I::EntityList->GetClientNetworkable(i)->IsDormant()
				|| Entity == g_Globals->LocalPlayer)
				continue;

			Vector vecBottom, vecScreenBottom, vecScreenOrigin;
			Vector vecOrigin = vecBottom = Entity->GetOrigin();
			vecBottom.z += (Entity->GetFlags() & FL_DUCKING) ? 54.f : 72.f;
			if (!g_Utils->WorldToScreen(vecBottom, vecScreenBottom) || !g_Utils->WorldToScreen(vecOrigin, vecScreenOrigin))
				continue;
			float lineHeight = (vecScreenOrigin.y - vecScreenBottom.y);
			float edgeWidth = lineHeight / 4;
			float lineWidth = edgeWidth;
			edgeWidth /= 1.5f;
			Vector leftUpCorn = Vector(vecScreenOrigin.x - lineWidth - LINE_WIDTH, vecScreenBottom.y, 0.f);
			Vector rightUpCorn = Vector(vecScreenOrigin.x + lineWidth, vecScreenBottom.y, 0.f);
			Vector leftDownCorn = Vector(vecScreenOrigin.x - lineWidth, vecScreenOrigin.y, 0.f);
			Vector rightDownCorn = Vector(vecScreenOrigin.x + lineWidth, vecScreenOrigin.y, 0.f);

			int screenWidth, screenHeight;
			I::Engine->GetScreenSize(screenWidth, screenHeight);
			if (g_Option.enable_esp)
			{
				PlayerInfo_t pInfo;
				if (I::Engine->GetPlayerInfo(i, &pInfo)) {
					g_ImRender->DrawEspBox(leftUpCorn, rightDownCorn, GetTeamColor(Entity), 2);
					g_ImRender->DrawString(g_Globals->Font1, rightUpCorn.x + 5, rightUpCorn.y - 2, GetTeamColor(Entity), "%s", pInfo.name);
					rightUpCorn.y += 12;
					g_ImRender->DrawString(g_Globals->Font1, rightUpCorn.x + 5, rightUpCorn.y - 2, GetTeamColor(Entity), "%i HP", Entity->GetHealth());
				}
			}
		}
	}
}