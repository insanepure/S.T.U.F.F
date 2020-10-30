#ifndef _KRAKEN_H_
#define _KRAKEN_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SpriteReader.h"

// Declare namespace Game
namespace Game
{
    /// @brief Kraken in the background 
    ///
    class CKraken
    {
    private:
        /// @brief Time when a next Animation appears
        ///
        float32 m_AnimationSpeed;
        /// @brief Time for Animations
        ///
        float32 m_AnimationTime;
        /// @brief Animation that is Playing
        ///
        int32 m_Animation;
        /// @brief Position of the Kraken
        ///
        PuRe_Vector3F m_Position;
    public:
        /// @brief Initializes a Kraken
        ///
        /// @param Speed of one Animation
        ///
        CKraken(float32 a_AnimationSpeed, PuRe_Vector3F a_Position);
        /// @brief Destroyes an Explosion
        ///
        ~CKraken();
    public:
        /// @brief Updates the Animation
        ///
        /// @param Seconds since last Frame
        /// @param Screen Resolution
        ///
        /// @returns Whether the animation ended or not
        ///
        void Update(float32 a_Seconds, PuRe_Vector2F a_Resolution);
        /// @brief Draw the Explosion
        ///
        /// @param Sprite for the Kraken
        /// @param Camera used
        /// @param Camera position
        ///
        void Draw(CSpriteReader* a_pSprite, PuRe_Camera* a_pCamera, PuRe_Vector3F a_CamPosition);
    };
}
#endif /* _KRAKEN_H_ */