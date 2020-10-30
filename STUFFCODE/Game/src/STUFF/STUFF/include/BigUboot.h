#ifndef _BIGUBOOT_H_
#define _BIGUBOOT_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "LuaReader.h"
#include "Player.h"

// Declare namespace Game
namespace Game
{
    class CBigUboot
    {
    public:
        /// @brief Whether he is used or not
        ///
        bool m_InUse;
        /// @brief Timer how long he has been in use
        ///
        float32 m_UseTimer;
    private:
        /// @brief FastSpeedUp
        ///
        float32 m_SpeedUp;
        /// @brief Time when a next Animation appears
        ///
        float32 m_AnimationSpeed;
        /// @brief Time for Animations
        ///
        float32 m_AnimationTime;
        /// @brief Animation that is Playing
        ///
        int32 m_AnimationFrame;
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
        /// @brief Int Array used for LUA
        ///
        int32* m_pIntArray;
        /// @brief Size of Our Int Array
        ///
        int32 m_ArraySize;
        /// @brief Size of one Ship
        ///
        PuRe_Vector2F m_ShipSize;
        /// @brief BoundingBox for the Player
        ///
        PuRe_BoundingBox m_BoundingBox;
        /// @brief Position he is at
        ///
        PuRe_Vector3F m_Position;
        /// @brief Player Array
        ///
        CPlayer** m_ppPlayers;
        /// @brief Sprite we use
        ///
        PuRe_Sprite* m_pSprite;
        /// @brief LuaReader
        ///
        CLuaReader* m_pLuaReader;
        /// @brief Positions inside of the ship
        ///
        int32 m_Positions[4];
    public:
        /// @brief Constructor to create a big uboot
        ///
        /// @param Pointer to the Lua reader
        /// @param Pointer to the player array
        /// @param Sprite to use
        ///
        CBigUboot(CLuaReader* a_pLuaReader, CPlayer** a_ppPlayers, PuRe_Sprite* a_pSprite);
        /// @brief Destroyes an instance of biguboot
        ///
        ~CBigUboot();
        /// @brief BigUboot is Hit, damage him
        ///
        void Hit();
        /// @brief Draw the Big Ship
        ///
        void Spawn(PuRe_Vector3F Position);
        /// @brief Draw the Big Ship
        ///
        /// @param Camera Object
        /// @param Sprite Object for the Player Sprites
        /// @param Sprite Object for the Shield Sprites
        /// @param Material for red/green/blue effects
        ///
        void Draw(PuRe_Camera* a_pCamera, PuRe_Sprite* a_pShieldSprite, PuRe_IMaterial* a_pMaterial);
        /// @brief Updates the Big Ship
        ///
        /// @param DeltaTime
        /// @param Input Pointer for Input Handling
        /// @param Position of the Camera
        /// @param energy to add
        ///
        void Update(float32 a_DeltaTime, PuRe_IInput* a_pInput, float32 a_Cam_X, int32& a_Energy);
        /// @brief Reset's the BigUboot's Position
        ///
        /// @param The new Position
        ///
        void ResetPosition(PuRe_Vector3F a_Position);
        /// @brief Return the BigUboot Position
        ///
        /// @returns Position of the BigUboot
        ///
        PuRe_Vector3F GetPosition();
        /// @brief Return the BigUboot Bounding Box
        ///
        /// @returns BoundingBox of the BigUboot
        ///
        PuRe_BoundingBox GetBox();
        /// @brief Return the BigUboot's Speed
        ///
        /// @returns BigUboot's Speed
        ///
        float32 GetSpeed();
        /// @brief Return the BigUboot's LookAngle
        ///
        /// @returns BigUboot's LookAngle
        ///
        float32 GetLookAngle();
        /// @brief Return the BigUboot's Lifes
        ///
        /// @returns BigUboot's Lifes as int32
        ///
        int32 GetLifes();
    };
}
#endif /* _BIGUBOOT_H_ */