#pragma once

class Visuals {
public:
	static Color GetTeamColor(C_BaseEntity* ent);
	static void ESP();
	void DrawPlayerESP(C_BaseEntity* Entity);
	void DrawDroppedESP(C_BaseEntity* Entity);
private:

}; extern Visuals* g_Visuals;