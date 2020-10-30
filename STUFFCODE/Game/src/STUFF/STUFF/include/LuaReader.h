#ifndef _LUAREADER_H_
#define _LUAREADER_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SpriteReader.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// Declare namespace Game
namespace Game
{
    /// @brief LuaReader which can read Lua files 
    ///
    class CLuaReader
    {
    private:
        /// @brief Lua interpreter
        ///
        lua_State* m_pLuaState;
    public:
        /// @brief Initializes a LuaReader Object
        ///
        /// @param Path to the Lua file
        ///
        CLuaReader(const char8* a_pLuaPath);
        /// @brief Destroyes a LuaReader Object
        ///
        ~CLuaReader();
    public:
        /// @brief Register a Function
        ///
        /// @param Name of the Function
        /// @param The Function Pointer
        ///
        void RegisterFunction(const char8* a_pFunctionName,lua_CFunction a_Function);
        /// @brief Sets a Function
        ///
        /// @param Name of the Function
        ///
        void SetFunction(const char8* a_pFunctionName);
        /// @brief Calls a Function
        ///
        /// @param Amount of Arguments
        /// @param Amount of Returns
        ///
        /// @remarks SetFunction has to be called before
        ///
        void CallFunction(int32 a_Arguments, int32 a_Return);
        /// @brief Push an Argument into a Function
        ///
        /// @param Value as Integer
        ///
        /// @remarks SetFunction has to be called before
        ///
        void Push(int32 a_Value);
        /// @brief Push an Argument into a Function
        ///
        /// @param Value as Boolean
        ///
        /// @remarks SetFunction has to be called before
        ///
        void Push(bool a_Value);
        /// @brief Push an Argument into a Function
        ///
        /// @param Value as Float
        ///
        /// @remarks SetFunction has to be called before
        ///
        void Push(float32 a_Value);
        /// @brief Pop a returned Value
        ///
        /// @returns Value as Float
        ///
        /// @remarks CallFunction has to be called before
        ///
        float32 PopFloat();
        /// @brief Pop a returned Value
        ///
        /// @returns Value as Integer
        ///
        /// @remarks CallFunction has to be called before
        ///
        int32 PopInt();
        /// @brief Pop a returned Value
        ///
        /// @returns Value as Bool
        ///
        /// @remarks CallFunction has to be called before
        ///
        bool PopBool();
    };
}

#endif /* _LUAREADER_H_ */