#include "include/SoundManager.h"

namespace Game
{
    static int MainChannel = 0;

    int CSoundManager::PlaySound(lua_State* a_pLuaState)
    {
        int32 soundID = (int32)lua_tointeger(a_pLuaState, 1);
        CSoundManager::m_pSoundPlayer->PlaySound(std::to_string(soundID).c_str(),false,true,CSoundManager::m_SoundVolume);
        lua_pop(a_pLuaState, 1);
        return 0;
    }

    void CSoundManager::StopMainSound()
    {
        CSoundManager::m_pSoundPlayer->StopSound(MainChannel);
    }

    void CSoundManager::PlayMainSound(std::string text, bool loop, bool stop, float Volume)
    {
        MainChannel = CSoundManager::m_pSoundPlayer->PlaySound(text.c_str(), loop, stop, Volume);
    }
}