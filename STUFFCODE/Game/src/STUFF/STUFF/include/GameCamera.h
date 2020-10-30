#ifndef _GAMECAMERA_H_
#define _GAMECAMERA_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "LuaReader.h"
#include "Player.h"

// Declare namespace Game
namespace Game
{
    /// @brief GameCamera Class to handle Camera Movement and Camera LUA Script 
    ///
    class CGameCamera
    {
    private:
        /// @brief Camera's Position
        ///
        PuRe_Vector3F m_Position;
        /// @brief Camera's Position which is aimed to
        ///
        PuRe_Vector3F m_ToPosition;
        /// @brief Lua Reader to read Camera's Lua Data
        ///
        CLuaReader* m_pLuaReader;
    public:
        /// @brief Constructor to initialize a Game Camera
        ///
        /// @param Path to the Lua File
        /// @param Camera to draw from
        ///
        CGameCamera(const char8* a_pLuaPath);
        /// @brief Destructor to destroy a Game Camera
        ///
        ~CGameCamera();
    public:
        /// @brief Update The Camera
        ///
        /// @param Position at the front
        /// @param Position between all players
        /// @param Speed of the player
        /// @param Resolution
        /// @param Levelend as float
        /// @param DeltaTime as float
        ///
        void Update(PuRe_Vector3F a_PlayerPosition, PuRe_Vector3F a_AveragePosition, float32 a_Speed, PuRe_Vector2F a_Resolution, float32 a_LevelEnd, float32 a_DeltaTime, PuRe_Camera* a_pCamera);
        /// @brief Return the Camera Position
        ///
        /// @returns Position of the Player
        ///
        PuRe_Vector3F GetPosition();
    };
}
#endif /* _GAMECAMERA_H_ */