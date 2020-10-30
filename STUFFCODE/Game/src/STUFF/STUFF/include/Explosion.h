#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SpriteReader.h"

// Declare namespace Game
namespace Game
{
    /// @brief Explosion 
    ///
    class CExplosion
    {
    private:
        /// @brief Size of the Explosion
        ///
        float32 m_Size;
        /// @brief Time when a next Animation appears
        ///
        float32 m_AnimationSpeed;
        /// @brief Time for Animations
        ///
        float32 m_AnimationTime;
        /// @brief Animation that is Playing
        ///
        int32 m_Animation;
        /// @brief Position of the Explosion
        ///
        PuRe_Vector3F m_Position;
    public:
        /// @brief Initializes an Explosion
        ///
        /// @param Speed of one Animation
        /// @param Size of the Explosion from 0 to 1
        ///
        CExplosion(float32 a_AnimationSpeed, PuRe_Vector3F a_Position,float32 a_Size);
        /// @brief Destroyes an Explosion
        ///
        ~CExplosion();
    public:
        /// @brief Updates the Animation
        ///
        /// @param Seconds since last Frame
        ///
        /// @returns Whether the animation ended or not
        ///
        bool Update(float32 a_Seconds);
        /// @brief Draw the Explosion
        ///
        /// @param Sprite for the Explosion
        /// @param Camera used
        ///
        void Draw(CSpriteReader* a_pSprite, PuRe_Camera* a_pCamera);
    };
}
#endif /* _EXPLOSION_H_ */