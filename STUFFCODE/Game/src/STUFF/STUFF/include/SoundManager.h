#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "LuaReader.h"

// Declare namespace Game
namespace Game
{
    /// @brief Manager to manage Sounds
    ///
    class CSoundManager
    {
    public:
        /// @brief SoundPlayer
        ///
        static PuRe_SoundPlayer* m_pSoundPlayer;
        /// @brief Volume of Musics
        ///
        static float32 m_MusicVolume;
        /// @brief Volume of Sounds
        ///
        static float32 m_SoundVolume;
    public:
        /// @brief Function to play a sound fron lua
        ///
        /// @param LuaState
        ///
        static int PlaySound(lua_State* a_pLuaState);

        static void StopMainSound();

        static void PlayMainSound(std::string text, bool loop, bool stop, float Volume);
    };
}
#endif /* _SOUNDMANAGER_H_ */