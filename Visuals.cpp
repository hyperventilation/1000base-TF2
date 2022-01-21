#include "Main.h"

Color Visuals::GetTeamColor(C_BaseEntity * ent)
{
	return (ent->GetTeamNum() == 2
		        ? Color(255, 102, 0, 255)
		        : ent->GetTeamNum() == 3
		        ? Color(0, 102, 255, 255)
		        : Color(255, 255, 255, 255));
}

constexpr auto DUCK{ 54.f };
constexpr auto STAND{ 72.f };
constexpr auto EWIDTH{ 1.5f };

void Visuals::ESP()
{
	if (I::Engine->IsInGame() && I::Engine->IsConnected())
	{
		// Check if player has joined a game and is connected to the game.
		for (auto i = 1; i <= I::Engine->GetMaxClients(); ++i) // Iteration starts at 1 because 0 is CWorld.
		{
			auto entity = I::EntityList->GetClientEntity(i);
			if (!entity
				|| !entity->GetLifeState() == 0
				|| !entity->GetHealth() > 0
				|| I::EntityList->GetClientNetworkable(i)->IsDormant()
				|| entity == g_Globals->LocalPlayer)
				continue;

			Vector vec_bottom;
			Vector vec_screen_bottom;
			Vector vec_screen_origin;
			auto vec_origin{ vec_bottom = entity->GetOrigin() };
			
			if ((entity->GetFlags() & FL_DUCKING)) 
				vec_bottom.z += DUCK;
			else vec_bottom.z += STAND;
			
			if (!g_Utils->WorldToScreen(vec_bottom, vec_screen_bottom) || !g_Utils->WorldToScreen(
				vec_origin, vec_screen_origin))
			{
				continue;
			}

			const auto line_height = (vec_screen_origin.y - vec_screen_bottom.y);
			auto edge_width = line_height / 4;
			const auto line_width = edge_width;
			
			edge_width /= EWIDTH;
			
			auto left_up_corn = Vector(vec_screen_origin.x - line_width - LINE_WIDTH, vec_screen_bottom.y, 0.f);
			auto right_up_corn = Vector(vec_screen_origin.x + line_width, vec_screen_bottom.y, 0.f);
			auto left_down_corn = Vector(vec_screen_origin.x - line_width, vec_screen_origin.y, 0.f);
			auto right_down_corn = Vector(vec_screen_origin.x + line_width, vec_screen_origin.y, 0.f);

			int screen_width;
			int screen_height;
			
			I::Engine->GetScreenSize(screen_width, screen_height);
			if (g_Option.enable_esp)
			{
				PlayerInfo_t p_info;
				if (I::Engine->GetPlayerInfo(i, &p_info))
				{
					g_ImRender->DrawEspBox(left_up_corn, right_down_corn, GetTeamColor(entity), 2);
					g_ImRender->DrawString(g_Globals->Font1, right_up_corn.x + 5, right_up_corn.y - 2, GetTeamColor(entity),
					                       "%s", p_info.name);
					right_up_corn.y += 12;
					g_ImRender->DrawString(g_Globals->Font1, right_up_corn.x + 5, right_up_corn.y - 2, GetTeamColor(entity),
					                       "%i HP", entity->GetHealth());
				}
			}
		}
	}
}
