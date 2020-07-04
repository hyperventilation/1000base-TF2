#pragma once

class C_BaseCombatWeapon;

class C_BaseEntity
{
private:
	template<class T>
	T GetValue(const int offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}
public:
	bool Dormant()
	{
		PVOID Networkable = (PVOID)(this + 0x8); // I don't have IClientNetworkable here so we do this and ezpz fixed
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return g_Utils->get_vfunc<OriginalFn>(Networkable, 8)(Networkable);
	}
	bool GetLifeState()
	{
		static int m_lifeState = g_pNetvars->GetOffset("DT_BasePlayer", "m_lifeState");
		return GetValue<bool>(m_lifeState);
	}

	int GetHealth()
	{
		static int m_iHealth = g_pNetvars->GetOffset("DT_BasePlayer", "m_iHealth");
		return GetValue<int>(m_iHealth);
	}
	//	"DT_BaseEntity", "m_iTeamNum"
	int GetTeamNum()
	{
		static int m_iTeamNum = g_pNetvars->GetOffset("DT_BaseEntity", "m_iTeamNum");
		return GetValue<int>(m_iTeamNum);
	}
	Vector GetOrigin()
	{
		static int m_vecOrigin = g_pNetvars->GetOffset("DT_BaseEntity", "m_vecOrigin");
		return GetValue<Vector>(m_vecOrigin);
	}
	int GetClassNum()
	{
		static int m_PlayerClass = g_pNetvars->GetOffset("DT_TFPlayer", "m_PlayerClass");
		static int m_iClass = g_pNetvars->GetOffset("DT_TFPlayerClassShared", "m_iClass");
		static int offset = m_PlayerClass + m_iClass;
		return GetValue<int>(offset);
	}
	int GetCondition()
	{
		static int m_nPlayerCond = g_pNetvars->GetOffset("DT_TFPlayer", "m_Shared", "m_nPlayerCond");
		return GetValue<int>(m_nPlayerCond);
	}
	int GetFlags()
	{
		static int m_fFlags = g_pNetvars->GetOffset("DT_BasePlayer", "m_fFlags");
		return GetValue<int>(m_fFlags);
	}
};


class C_BaseCombatWeapon : public C_BaseEntity
{
private:

public:

};

struct SpatializationInfo_t;
class IClientEntity
{
public:
	// Delete yourself.
	virtual void			Release(void) = 0;

	// Network origin + angles
	virtual const Vector& GetAbsOrigin(void) const = 0;
	virtual const QAngle& GetAbsAngles(void) const = 0;

	virtual DWORD* GetMouth(void) = 0;

	// Retrieve sound spatialization info for the specified sound on this entity
	// Return false to indicate sound is not audible
	virtual bool			GetSoundSpatialization(SpatializationInfo_t& info) = 0;
};

class IClientEntityList
{
public:
	virtual IClientNetworkable* GetClientNetworkable(int entnum) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle(CBaseHandle hEnt) = 0;
	virtual IClientUnknown* GetClientUnknownFromHandle(CBaseHandle hEnt) = 0;
	virtual C_BaseEntity* GetClientEntity(int entnum) = 0;
	virtual IClientEntity* GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int					GetHighestEntityIndex(void) = 0;
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
};