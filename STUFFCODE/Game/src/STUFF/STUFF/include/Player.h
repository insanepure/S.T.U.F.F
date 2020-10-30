#ifndef _PLAYER_H_
#define _PLAYER_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "LuaReader.h"
#include "SoundManager.h"
#include <cmath>

// Declare namespace Game
namespace Game
{
    /// @brief A Player that plays the Game
    ///
    class CPlayer
    {
    public:
        /// @brief Whether he is ready to start or not
        ///
        bool m_Ready;
        /// @brief Which ship he used, range from 0 to 3
        ///
        int32 m_Ship;
        /// @brief Which Position he is in the big ship
        ///
        int32 m_BigPosition;
        /// @brief whether the Player is playing or not
        ///
        bool m_IsPlaying;
        /// @brief Points achieved by this Player
        ///
        int32 m_Points;
        /// @brief Item the Player has
        ///
        int32 m_Item;
    private:
        /// @brief Time he blinks
        ///
        float32 m_BlinkTime;
        /// @brief Time the FireRate is on
        ///
        float32 m_FireRateTime;
        /// @brief How many Lifes he still has
        ///
        int32 m_Lifes;
        /// @brief Shield and how strong it is
        ///
        int32 m_Shield;
        /// @brief RGB Value for shader effects
        ///
        float32 m_R, m_G, m_B;
        /// @brief Speed of the Player
        ///
        float32 m_Speed;
        /// @brief Angle the Ship is looking
        ///
        float32 m_LookAngle;
        /// @brief Angle the Ship is moving
        ///
        float32 m_Angle;
        /// @brief Which PlayerNum/Index we are
        ///
        int32 m_Index;
        /// @brief Int Array used for LUA
        ///
        int32* m_pIntArray;
        /// @brief Size of Our Int Array
        ///
        int32 m_ArraySize;
        /// @brief Size of one Ship
        ///
        PuRe_Vector2F m_ShipSize;
        /// @brief Position of the Player
        ///
        PuRe_Vector3F m_Position;
        /// @brief BoundingBox for the Player
        ///
        PuRe_BoundingBox m_BoundingBox;
    public:
        /// @brief Constructor to initialize a Player
        ///
        CPlayer(int32 m_Index);
        /// @brief Destructor to destroy a Player
        ///
        ~CPlayer();
    public:
        /// @brief Initialize a Player, Resets his Variables
        ///
        /// @param Pointer to the Lua reader
        /// @param Position where to start
        ///
        void Init(CLuaReader* a_pLuaReader, PuRe_Vector3F a_Position);
        /// @brief Updates the Player
        ///
        /// @param Pointer to the Lua reader
        /// @param DeltaTime
        /// @param Input Pointer for Input Handling
        /// @param Position of the Camera
        /// @param if he used a bomb or not
        /// @param if he used energy or not
        ///
        void Update(CLuaReader* a_pLuaReader, float32 a_DeltaTime, PuRe_IInput* a_pInput, float32 a_Cam_X, bool& a_bomb, bool& a_Energy);
        /// @brief Draw the Player
        ///
        /// @param Camera Object
        /// @param Sprite Object for the Player Sprites
        /// @param Sprite Object for the Shield Sprites
        /// @param Material for red/green/blue effects
        ///
        void Draw(PuRe_Camera* a_pCamera, PuRe_Sprite* a_pSprite, PuRe_Sprite* a_pShieldSprite, PuRe_IMaterial* a_pMaterial);
        /// @brief Player is Hit, damage him
        ///
        void Hit();
        /// @brief Move Player to another Position
        ///
        /// @param The Position we move to, this is added to the player position
        ///
        void Move(PuRe_Vector3F a_AddPosition);
        /// @brief Player is healed
        ///
        /// @param The new Position he moves to if he dies
        ///
        void Heal(PuRe_Vector3F a_Position);
        /// @brief Reset's the Player's Position
        ///
        /// @param The new Position
        ///
        void ResetPosition(PuRe_Vector3F a_Position);
        /// @brief Return the Player Position
        ///
        /// @returns Position of the Player
        ///
        PuRe_Vector3F GetPosition();
        /// @brief Return the Player Bounding Box
        ///
        /// @returns BoundingBox of the Player
        ///
        PuRe_BoundingBox GetBox();
        /// @brief Return the Player's Speed
        ///
        /// @returns Player's Speed
        ///
        float32 GetSpeed();
        /// @brief Return the Player's LookAngle
        ///
        /// @returns Player's LookAngle
        ///
        float32 GetLookAngle();
        /// @brief Return the Player's Lifes
        ///
        /// @returns Player's Lifes as int32
        ///
        int32 GetLifes();
    };
}
#endif /* _PLAYER_H_ */