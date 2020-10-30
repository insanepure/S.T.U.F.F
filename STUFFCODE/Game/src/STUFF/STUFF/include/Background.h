#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SpriteReader.h"
#include "Kraken.h"

// Declare namespace Game
namespace Game
{
    /// @brief Sprites in the Background with Parallax
    ///
    class CBackground
    {
    public:
        /// @brief Used Material
        ///
        static PuRe_IMaterial* m_pMaterial;
        /// @brief Sprite Reader for the Godrays
        ///
        static CSpriteReader* m_pLights;
        /// @brief SpriteReader for the Background
        ///
        static CSpriteReader* m_pBackground;
        /// @brief SpriteReader for the Kraken
        ///
        static CSpriteReader* m_pKrakenSprite;
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
        /// @brief Screen Resolution
        ///
        PuRe_Vector2F m_Resolution;
        /// @brief Screen Resolution
        ///
        CKraken* m_pKraken;
    public:
        /// @brief Constructor to initialize a Background
        ///
        /// @param Graphic Object
        /// @param Material used
        /// @param Graphic Resolution
        ///
        CBackground(PuRe_IGraphics* a_pGraphics, PuRe_Vector2F a_Resolution);
        /// @brief Destructor to destroy a Game Camera
        ///
        ~CBackground();
    public:
        /// @brief Draw the Background
        ///
        /// @param Camera Object
        /// @param Actual Camera Position
        /// @param Maximal Position in X Axis
        /// @param Maximal Position in Y Axis
        ///
        void Draw(PuRe_Camera* a_pCamera, PuRe_Vector3F a_CamPosition, PuRe_Vector2F a_MinMax_X, PuRe_Vector2F a_MinMax_Y);
        /// @brief Update Map's Data
        ///
        /// @param Delta time
        ///
        void Update(float32 a_DeltaTime);
    };
}
#endif /* _BACKGROUND_H_ */