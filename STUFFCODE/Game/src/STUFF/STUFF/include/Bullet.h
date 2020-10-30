#ifndef _BULLET_H_
#define _BULLET_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SpriteReader.h"
#include "LuaReader.h"
#include "Player.h"

// Declare namespace Game
namespace Game
{
    /// @brief Bullets that are shot 
    ///
    class CBullet
    {
    private:
        /// @brief LookAngle of the Bullet
        ///
        float32 m_LookAngle;
        /// @brief Angle of the Bullet
        ///
        float32 m_Angle;
        /// @brief Size of the Bullet
        ///
        float32 m_Size;
        /// @brief If the bullet collides with the map
        ///
        bool m_Collide;
        /// @brief If the bullet hits the player
        ///
        bool m_HitPlayer;
        /// @brief If the bullet is dead or not
        ///
        bool m_dead;
        /// @brief If and how many times he bounces
        ///
        int32 m_Bounce;
        /// @brief How fast the Bullet moves
        ///
        float32 m_Speed;
        /// @brief How much damage the bullet deals
        ///
        float32 m_Damage;
        /// @brief How long the bullet still stays
        ///
        float32 m_Stay;
        /// @brief Which Player shot the Bullet
        ///
        int32 m_PlayerNum;
        /// @brief Int Array used for LUA
        ///
        int32* m_pIntArray;
        /// @brief Size of Our Int Array
        ///
        int32 m_ArraySize;
        /// @brief Which Image is used
        ///
        int32 m_Type;
        /// @brief Which Image is used
        ///
        int32 m_Image;
        /// @brief Position of the Bullet
        ///
        PuRe_Vector3F m_Position;
        /// @brief BoundingBox for the Bullet
        ///
        PuRe_BoundingBox m_BoundingBox;
    public:
        /// @brief Initializes a Bullet Instance
        ///
        /// @param Bounding Box
        /// @param DrawPosition
        /// @param Which Image is used
        /// @param Type of the Bullet
        /// @param Size of the int array
        /// @param Player Index
        /// @param How long the bullet stays after death
        /// @param Damage dealt
        /// @param Speed
        /// @param If it bounces
        /// @param If it hits the player
        /// @param If it collides
        /// @param Angle it moves
        /// @param Angle it looks
        ///
        CBullet(
        PuRe_BoundingBox a_BoundingBox, 
        PuRe_Vector3F a_Position,
        int32 a_Image,
        int32 a_Type,
        int32 a_ArraySize,
        int32 a_PlayerNum,
        float32 a_Stay,
        float32 a_Damage,
        float32 a_Speed,
        int32 a_Bounce,
        bool a_HitPlayer,
        bool a_Collide,
        float32 a_Angle,
        float32 a_LookAngle
        );
        /// @brief Destroyes a Bullet Instance
        ///
        ~CBullet();
    public:
        /// @brief Returns Size
        ///
        /// @returns Size as float32
        ///
        float32 GetSize();
        /// @brief What happens when he dies
        ///
        /// @param LuaReader
        ///
        void OnDie(CLuaReader* a_pLuaReader);
        /// @brief Returns LookAngle
        ///
        /// @returns LookAngle as float32
        ///
        float32 GetLookAngle();
        /// @brief Returns Speed
        ///
        /// @returns Speed as float32
        ///
        float32 GetSpeed();
        /// @brief Returns Image Index
        ///
        /// @returns Image Index as int32
        ///
        int32 GetImage();
        /// @brief Returns Position
        ///
        /// @returns Position as Vector3F
        ///
        PuRe_Vector3F GetPosition();
        /// @brief Returns true if it should hit the player
        ///
        /// @returns true if it hits the player
        ///
        bool HitPlayer();
        /// @brief Returns Bounding Box
        ///
        /// @returns A Bounding Box
        ///
        PuRe_BoundingBox& GetBoundingBox();
        /// @brief Returns if he collides with the map or not
        ///
        /// @returns A boolean
        ///
        bool GetCollide();
        /// @brief Returns if he bounces with the map or not
        ///
        /// @returns A boolean
        ///
        bool GetBounce();
        /// @brief Returns damage the bullet deals
        ///
        /// @returns damage as float32
        ///
        float32 GetDamage();
        /// @brief Returns the index of the Player that shot
        ///
        /// @returns index as int32
        ///
        int32 GetPlayer();
        /// @brief If he dies when hit
        ///
        /// @returns true if he dies when hit
        ///
        bool DieHit();
        /// @brief Do Bounce Math
        ///
        void Bounce();
        /// @brief Update the Bullet
        ///
        /// @param LuaReader
        /// @param DeltaTime
        /// @param Player Array
        /// @param Position the bullet is aiming for
        ///
        /// @returns returns if it is dead or not
        ///
        bool Update(CLuaReader* a_pLuaReader, float32 a_DeltaTime, CPlayer** a_ppPlayers, PuRe_Vector3F a_Aim);
        /// @brief Update before the update of the bullet
        ///
        /// @param LuaReader
        /// @param DeltaTime
        /// @param Position the bullet is aiming for
        ///
        void PreUpdate(CLuaReader* a_pLuaReader, float32 a_DeltaTime, CPlayer** a_ppPlayers, PuRe_Vector3F a_Aim);
    };
}
#endif /* _BULLET_H_ */