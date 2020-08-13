#include "Main.h"

void CMenu::Menu() const
{
	ImGui::GetIO().MouseDrawCursor = g_Vars->Menu.Opened;
	if (g_Vars->Menu.Opened) {

		ImGui::Begin("1000base", &g_Vars->Menu.Opened, ImVec2(400, 300), 1.0f); {
			if (I::Engine->IsInGame() && I::Engine->IsConnected())
			{
				ImGui::Text("Local player has spawned!");
			}

			ImGui::PushFont(g_Globals->Font1);
			ImGui::Checkbox("Enable Visuals", &g_Option.enable_esp);
			ImGui::PopFont();
		}
		ImGui::End();
	}
}
