#ifndef _ITEM_H_
#define _ITEM_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

// Declare namespace Game
namespace Game
{
    /// @brief Items that can be used
    ///
    class CItem
    {
    public:
        /// @brief Time when a next Animation appears
        ///
        float32 m_AnimationSpeed;
        /// @brief Time for Animations
        ///
        float32 m_AnimationTime;
        /// @brief Animation that is Playing
        ///
        int32 m_Animation;
        /// @brief Type of the Item
        ///
        int32 m_Type;
        /// @brief Bounding Box
        ///
        PuRe_BoundingBox m_BoundingBox;
    public:
        /// @brief Constructor to initialize an Item
        ///
        /// @param Which Type we use
        /// @param Position of the Item
        ///
        CItem(int32 a_Type, PuRe_Vector2F a_Position);
        /// @brief Destructor to destroy an Item
        ///
        ~CItem();
    public:
        /// @brief Updates the Animation
        ///
        /// @param Delta time for frame independence
        ///
        void Update(float32 a_DeltaTime);
        /// @brief Draw the Item
        ///
        /// @param camera used
        /// @param which sprite we render from
        ///
        void Draw(PuRe_Camera* a_pCamera,PuRe_Sprite* a_pSprite, PuRe_IMaterial* a_pMaterial);
    };
}
#endif /* _ITEM_H_ */