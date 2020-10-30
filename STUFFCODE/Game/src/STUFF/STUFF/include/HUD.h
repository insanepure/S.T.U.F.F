#ifndef _HUD_H_
#define _HUD_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SpriteReader.h"
#include "Player.h"
#include "HudEmitter.h"

// Declare namespace Game
namespace Game
{
    /// @brief HUD Class for ingame HUD display
    ///
    class CHUD
    {
    public:
        /// @brief Timer to handle revive
        ///
        float32 m_ReviveTimer;
        /// @brief If revive has started
        ///
        bool m_ReviveStart;
        /// @brief Timer to handle extralife
        ///
        float32 m_ExtraLifeTimer;
        /// @brief If extralife gain has started
        ///
        bool m_ExtraLifeStart;
    private:
        PuRe_IMaterial* m_pBulletMaterial;
        PuRe_IMaterial* m_pFontMaterial;
        /// @brief Emitter for hud's particles
        ///
        CHudEmitter* m_pHudEmitter;
        /// @brief Particle's Sprite
        ///
        PuRe_Sprite* m_pParticleSprite;
        /// @brief Game End's Sprite
        ///
        PuRe_Sprite* m_pGameEndSprite;
        /// @brief SpriteReader to display HUD
        ///
        CSpriteReader* m_pHudSprite;
        /// @brief Camera used for the HUD
        ///
        PuRe_Camera* m_pCamera;
        /// @brief Resolution
        ///
        PuRe_Vector2F m_Resolution;
        /// @brief Font used
        ///
        PuRe_Font* m_pFont;
        /// @brief Font used
        ///
        PuRe_Font* m_pDeactiveFont;
    public:
        /// @brief Constructor to initialize a Hud
        ///
        /// @param Resolution
        /// @param Graphic Object
        /// @param Font Material
        /// @param DeactiveFont Material
        ///
        CHUD(PuRe_Vector2F a_Resolution, PuRe_IGraphics* a_pGraphics, PuRe_IMaterial* a_pFontMaterial, PuRe_IMaterial* a_pBulletMaterial);
        /// @brief Destructor to destroy a Hud
        ///
        ~CHUD();
    public:
        /// @brief Draw the HUD
        ///
        /// @param Points of all players
        /// @param how many hearts they have
        /// @param how many Lifes the big one has
        /// @param how many extra life they have
        /// @param Pointer to the array of players
        /// @param Sprite used to render items
        /// @param Font Material
        ///
        void Draw(int32 a_Points, int32 a_Hearts, int32 BigLifes, bool a_ExtraLife, float32 a_Energy, float32 a_toEnergy, CPlayer** a_ppPlayers, PuRe_Sprite* a_pItemSprite, PuRe_IMaterial* a_pFontMaterial);
        /// @brief Draw the Game End
        ///
        /// @param Time for the menu to go down
        /// @param Material so gray is not assigned
        /// @param Material so gray is not assigned
        /// @param if he is currently at the left or right side
        ///
        void Draw(float32 a_GameEndTime, PuRe_IMaterial* a_pMaterial, PuRe_IMaterial* a_pFontMaterial, bool a_Left);
        /// @brief Draw the Pause Menu
        ///
        /// @param where in the menu he is at
        /// @param Material so gray is not assigned
        /// @param Material so gray is not assigned
        ///
        void Draw(int32 a_PauseWhere, PuRe_IMaterial* a_pMaterial, PuRe_IMaterial* a_pFontMaterial);
        /// @brief Update Extra Life and returns if done
        ///
        /// @param DeltaTime
        ///
        /// @returns true if extra life can be given
        ///
        bool ExtraLifeUpdate(float32 a_DeltaTime);
        /// @brief UpdateRevive and returns if done
        ///
        /// @param DeltaTime
        ///
        /// @returns true if revive can be done
        ///
        bool ReviveUpdate(float32 a_DeltaTime);
        /// @brief Update other stuffs such as particles in hud
        ///
        /// @param DeltaTime
        ///
        void Update(float32 a_DeltaTime);
    };
}

#endif /* _HUD_H_ */