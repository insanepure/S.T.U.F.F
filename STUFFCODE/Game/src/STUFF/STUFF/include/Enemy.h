#ifndef _ENEMY_H_
#define _ENEMY_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "LuaReader.h"
#include "SoundManager.h"

// Declare namespace Game
namespace Game
{
    class CEnemy
    {
    public:
        /// @brief which type the enemy has
        ///
        int32 m_Type;
    private:
        /// @brief Time when a next Animation appears
        ///
        float32 m_AnimationSpeed;
        /// @brief Time for Animations
        ///
        float32 m_AnimationTime;
        /// @brief Animation that is Playing
        ///
        int32 m_AnimationFrame;
        /// @brief Angle the Enemy moves at
        ///
        float32 m_Angle;
        /// @brief Angle the Enemy looks at
        ///
        float32 m_LookAngle;
        /// @brief Delete the Enemy
        ///
        bool m_DeleteHim;
        /// @brief Position where to draw
        //
        PuRe_Vector3F m_Position;
        /// @brief Which Animation we use
        ///
        int32 m_Animation;
        /// @brief Speed of the Enemy
        ///
        float32 m_Speed;
        /// @brief Size of the Enemy
        ///
        float32 m_Size;
        /// @brief Lua Reader to call lua functions
        ///
        CLuaReader* m_pLuaReader;
        /// @brief Radius in which damage is done
        ///
        float32 m_DamageRadius;
        /// @brief if he dies on collide or not
        ///
        bool m_DieOnCollide;
        /// @brief how many damage he does on collide
        ///
        int32 m_CollideDamage;
        /// @brief size of his array
        ///
        int32 m_ArraySize;
        /// @brief His Array
        ///
        int32* m_pIntArray;
        /// @brief Point he gives on death
        ///
        int32 m_Points;
        /// @brief Life he has
        ///
        float32 m_Lifes;
        /// @brief Height he has
        ///
        float32 m_Height;
        /// @brief Width he has
        ///
        float32 m_Width;
        /// @brief max speed he can move
        ///
        float32 m_MaxSpeed;
        /// @brief how fast he can turn
        ///
        float32 m_AngleSpin;
        /// @brief Bounding Box used
        ///
        PuRe_BoundingBox m_BoundingBox;
        /// @brief if he is flipped or not
        ///
        bool m_Flip;
        /// @brief time used for flashing
        ///
        float32 m_HitTime;
     
    public:
        /// @brief Constructor to initialize an enemy
        ///
        /// @param LuaReader to rread the specific lua file
        /// @param Type of the Enemy
        /// @param X Position of the Enemy
        /// @param Y Position of the Enemy
        /// @param Life Increase
        /// @param Size Increase
        ///
        CEnemy(CLuaReader* a_pLuaReader, int32 Type, float32 X, float32 Y, float32 a_Lifes, int32 a_Size);
        /// @brief Destructor to destroy an enemy
        ///
        ~CEnemy();
    public:
        /// @brief cast when enemy is updated
        ///
        /// @param delta time
        /// @param Speed of the Player
        /// @param Position of the Player
        /// @param Position of the Camera
        /// @param Screen Resolution
        ///
        bool Update(float32 a_DeltaTime, float32 a_PlayerSpeed, PuRe_Vector3F a_PlayerPosition, PuRe_Vector3F a_CamPosition, PuRe_Vector2F a_Resolution);
        /// @brief draw the enemy
        ///
        /// @param Camera Object
        /// @param Sprites used
        /// @param Material used
        ///
        void Draw(PuRe_Camera* a_pCamera, PuRe_Sprite** a_ppSprite, PuRe_IMaterial* a_pMaterial);
        /// @brief Return the Player Bounding Box
        ///
        /// @returns BoundingBox of the Player
        ///
        PuRe_BoundingBox GetBox();
        /// @brief Deals Damage to the enemy
        ///
        /// @param Damage dealed
        ///
        /// @returns if he is now dead or not
        ///
        bool DealDamage(float32 a_Damage);
        /// @brief Updates the Boss Animation
        ///
        /// @param Which Frame should be drawn
        ///
        void BossAnimation(int32 Frame);
        /// @brief Returns points he gives
        ///
        /// @returns points as int32
        ///
        int32 GetPoints();
        /// @brief Returns the radius in which the explosions deals damage
        ///
        /// @returns radius as float32
        ///
        float32 GetDamageRadius();
        /// @brief Returns the Size
        ///
        /// @returns Size as float32
        ///
        float32 GetSize();
        /// @brief Returns if he dies once collided or not
        ///
        /// @returns true if he dies false if not
        ///
        bool DieCollide();
        /// @brief If he deals damage once collide
        ///
        /// @returns true if he deals damage on collide false if not
        ///
        bool CollideDamage();
    };
}

#endif /* _ENEMY_H_ */