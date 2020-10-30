#include "include/LuaReader.h"

namespace Game
{
    CLuaReader::CLuaReader(const char8* a_pLuaPath)
    {
        //init State
        this->m_pLuaState = luaL_newstate();
        //Open basic Lua Libs
        luaL_openlibs(this->m_pLuaState);
        //Open Lua File
        luaL_dofile(this->m_pLuaState, a_pLuaPath);
    }

    // **************************************************************************
    // **************************************************************************

    CLuaReader::~CLuaReader()
    {
        lua_close(this->m_pLuaState);
    }

    // **************************************************************************
    // **************************************************************************

    void CLuaReader::SetFunction(const char8* a_pFunctionName)
    {
        lua_getglobal(this->m_pLuaState, a_pFunctionName);
    }

    // **************************************************************************
    // **************************************************************************

    void CLuaReader::RegisterFunction(const char8* a_pFunctionName, lua_CFunction a_Function)
    {
        lua_register(this->m_pLuaState,a_pFunctionName,a_Function);
    }

    // **************************************************************************
    // **************************************************************************

    void CLuaReader::Push(int32 a_Value)
    {
        lua_pushnumber(this->m_pLuaState, a_Value);
    }

    // **************************************************************************
    // **************************************************************************

    void CLuaReader::Push(bool a_Value)
    {
        lua_pushboolean(this->m_pLuaState, a_Value);
    }

    // **************************************************************************
    // **************************************************************************

    void CLuaReader::Push(float32 a_Value)
    {
        lua_pushnumber(this->m_pLuaState, a_Value);
    }

    // **************************************************************************
    // **************************************************************************

    float32 CLuaReader::PopFloat()
    {
        float32 sum;
        //get value
        sum = (float32)lua_tonumber(this->m_pLuaState, -1);
        //remove value from Stack
        lua_pop(this->m_pLuaState, 1);

        return sum;
    }

    // **************************************************************************
    // **************************************************************************

    int32 CLuaReader::PopInt()
    {
        int32 sum;
        //get value
        sum = (int32)lua_tointeger(this->m_pLuaState, -1);
        //remove value from Stack
        lua_pop(this->m_pLuaState, 1);

        return sum;
    }

    // **************************************************************************
    // **************************************************************************

    bool CLuaReader::PopBool()
    {
        bool sum;
        //get value
        sum = lua_toboolean(this->m_pLuaState, -1) != 0;
        //remove value from Stack
        lua_pop(this->m_pLuaState, 1);

        return sum;
    }

    // **************************************************************************
    // **************************************************************************

    void CLuaReader::CallFunction(int32 a_Arguments, int32 a_Return)
    {
        int32 check = lua_pcall(this->m_pLuaState, a_Arguments, a_Return, 0);
        int32 test = lua_gettop(this->m_pLuaState);
        if (check != 0)
        {
            std::string error = lua_tostring(this->m_pLuaState, -1);
            lua_pop(this->m_pLuaState, 1);
        }
        //lua_call(this->m_pLuaState, a_Arguments, a_Return);
    }



}