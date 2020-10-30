#ifndef _LOGOSCENE_H_
#define _LOGOSCENE_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SoundManager.h"

// Declare namespace Game
namespace Game
{
    /// @brief Logoscene at the Start
    ///
    class CLogoScene
    {
    private:
        /// @brief If the intro has been played or not
        ///
        bool m_IntroPlayed;
        /// @brief Timer to handle Rotation
        ///
        float32 m_Time;
        /// @brief Rotation of the Logo
        ///
        float32 m_LogoRotation;
        /// @brief Size of the Logo
        ///
        PuRe_Vector3F m_LogoSize;
        /// @brief Camera used to display
        ///
        PuRe_Camera* m_pCamera;
        /// @brief Material used to display
        ///
        PuRe_IMaterial* m_pMaterial;
        /// @brief GA Logo
        ///
        PuRe_Sprite* m_pGALogo;
        /// @brief STUFF Logo
        ///
        PuRe_Sprite* m_pSTUFFLogo;
    public:
        /// @brief Constructor to Initialize the LogoScene
        ///
        /// @param Pointer to the Application to get more Informations
        ///
        CLogoScene(PuRe_Application* a_pWindow);
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

#endif /* _LOGOSCENE_H_ */