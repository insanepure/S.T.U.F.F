#ifndef _CREDITSCENE_H_
#define _CREDITSCENE_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "Highscore.h"
#include "Explosion.h"
#include "MenuFish.h"
#include "Map.h"
// Declare namespace Game
namespace Game
{
    /// @brief CreditScene for credits
    ///
    class CCreditScene
    {
    private:
        /// @brief Emitter for Bubbles
        ///
        CBubbleEmitter* m_pBubbleEmitter;
        /// @brief Map in the Background
        ///
        CMap* m_pMap;
        /// @brief List of Explosions
        ///
        PuRe_List<CExplosion*> m_Explosions;
        /// @brief List of Fishs
        ///
        PuRe_List<CMenuFish*> m_Fishs;
        /// @brief Timer until he gets bigger again
        ///
        float32 m_ShotTime[4];
        /// @brief Position of CrossHair
        ///
        PuRe_Vector3F m_CrossHairPosition[4];
        /// @brief CrossHair for shooting fishs
        ///
        PuRe_Sprite* m_pCrossHairSprite;
        /// @brief Explosion's Sprite
        ///
        CSpriteReader* m_pExplosionSprite;
        /// @brief FishSprite
        ///
        PuRe_Sprite* m_pFishSprite;
        /// @brief SpriteReader and Font Material
        ///
        PuRe_IMaterial* m_pFontMaterial;
        /// @brief Font used when the button is active
        ///
        PuRe_Font* m_pActiveFont;
        /// @brief Timer to handle Time when the text is displayed
        ///
        float32 m_DisplayTime;
        /// @brief Timer to handle Animations
        ///
        float32 m_Time;
        /// @brief Camera used to display
        ///
        PuRe_Camera* m_pCamera;
        /// @brief Material used to display
        ///
        PuRe_IMaterial* m_pMaterial;
        /// @brief Highscore
        ///
        CHighscore* m_pHighscore;
        /// @brief Sprite for the Menu
        ///
        CSpriteReader* m_pMenuSprite;
    public:
        /// @brief Constructor to Initialize the CreditScene
        ///
        /// @param Pointer to the Application to get more Informations
        ///
        CCreditScene(PuRe_Application* a_pWindow);
    public:
        /// @brief Initializes the scene.
        ///
        /// @param graphics The graphics interface.
        ///
        void Initialize(PuRe_IGraphics* a_pGraphics);

        /// @brief Updates the scene.
        ///
        /// @param The Graphic Object
        /// @param The input interface.
        /// @param The Time Object
        ///
        /// @returns if it is still running or not
        ///
        bool Update(PuRe_IGraphics* a_pGraphics, PuRe_IInput* a_pInput, PuRe_Timer* a_pTimer);

        /// @brief Renders the scene.
        ///
        /// @param graphics The graphics interface.
        ///
        void Render(PuRe_IGraphics* a_pGraphics);

        /// @brief Exists the scene.
        ///
        void Exit();
    };

}

#endif /* _CREDITSCENE_H_ */