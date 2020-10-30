#ifndef _MENUFISH_H_
#define _MENUFISH_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

// Declare namespace Game
namespace Game
{
    /// @brief Fish which appears randomly in Menu and Credits
    ///
    class CMenuFish
    {
    public:
        /// @brief Bounding Box for Collision
        ///
        PuRe_BoundingBox m_pBoundingBox;
        /// @brief Position of the Fish
        ///
        PuRe_Vector3F m_Position;
        /// @brief Whether they Swim right or Left
        ///
        bool m_SwimRight;
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
    public:
        /// @brief Initializes a Fish
        ///
        /// @param Speed of one Animation
        ///
        CMenuFish(float32 a_AnimationSpeed);
        /// @brief Destroyes a Fish
        ///
        ~CMenuFish();
    public:
        /// @brief Updates the Animation
        ///
        /// @param Seconds since last Frame
        ///
        void Update(float32 a_Seconds);
        /// @brief Draw the Fish
        ///
        /// @param Sprite for the Fish
        /// @param Camera used
        /// @param Position the Fish is at
        /// @param whether the fish is mirrored or not
        ///
        void Draw(PuRe_Sprite* a_pFishSprite,PuRe_Camera* a_pCamera,PuRe_Vector3F a_Position,bool a_Mirror, PuRe_IMaterial* a_pMaterial);
    };
}
#endif /* _MENUFISH_H_ */