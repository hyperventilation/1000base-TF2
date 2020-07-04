#pragma once

class Visuals {
public:
	Color GetTeamColor(C_BaseEntity* ent);
	void ESP();
	void DrawPlayerESP(C_BaseEntity* Entity);
	void DrawDroppedESP(C_BaseEntity* Entity);
private:

}; extern Visuals* g_Visuals;