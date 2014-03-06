#ifndef CW_LUAENUM_H
#define CW_LUAENUM_H
#include "cw_singleton.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
struct lua_State;
const int MAX_SET_NAME_LEN = 32;
class CScriptEnum : public Singleton<CScriptEnum>
{
public:
	void		Init(lua_State* L){ m_pState = L; }

	void		RegisterAll();
	void		BeginRegisterEnum(const char* pSetName);

	void		RegisterEnum(const char* pEnumName, int nEnumVal);
protected:
private:
	char		m_SetName[MAX_SET_NAME_LEN];
	lua_State*	m_pState;
};

#define BEGIN_REG_ENUM(Type) CScriptEnum::GetSingleton().BeginRegisterEnum(Type)
#define REG_ENUM(value, name) CScriptEnum::GetSingleton().RegisterEnum(name, value)
#define END_REG_ENUM
#endif