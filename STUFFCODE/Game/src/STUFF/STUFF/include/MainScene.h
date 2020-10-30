#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_
#define _CRT_SECURE_NO_WARNINGS

// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "LogoScene.h"
#include "CreditScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Player.h"
#include "SoundManager.h"

// Declare namespace Game
namespace Game
{
    /// @brief MainScene where the game functions are in, inherits from the Scene interface
    ///
    class CMainScene : public PuRe_IScene
    {
    public:
        /// @brief GameScene where the game is
        ///
        CGameScene* m_pGameScene;
        /// @brief Logo Scene at the start
        ///
        CLogoScene* m_pLogoScene;
        /// @brief Menu Scene to display Menu
        ///
        CMenuScene* m_pMenuScene;
        /// @brief Menu Scene to display Menu
        ///
        CCreditScene* m_pCreditScene;
        /// @brief Which Scene we use
        ///
        int32 m_Scene;
        /// @brief Player Array, in MainScene because we need access from Menu and Game
        ///
        CPlayer** m_ppPlayers;

        bool m_LogPerformance;

        bool m_LogGame;

        bool m_GameStop;
    public:
        /// @brief Constructor to Initialize the MainScene
        ///
        /// @param Pointer to the Application to get more Informations
        ///
        CMainScene(PuRe_Application* a_pWindow);
    public:
        /// @brief Initializes the scene.
        ///
        /// @param graphics The graphics interface.
        /// @param Soundplayer for sound playing.
        ///
        void Initialize(PuRe_Application* a_pApplication);

        /// @brief Updates the scene.
        ///
        /// @param The Graphic Object
        /// @param The Window Object
        /// @param The input interface.
        /// @param The Time Object
        /// @param Soundplayer for sound playing.
        ///
        /// @returns if it is still running or not
        ///
        int Update(PuRe_Application* a_pApplication);

        /// @brief Renders the scene.
        ///
        /// @param graphics The graphics interface.
        ///
        void Render(PuRe_Application* a_pApplication);

        /// @brief Exists the scene.
        ///
        void Exit();

        void ValidateLogging(PuRe_IInput* a_pInput);
    };

}

#endif /* _MAINSCENE_H_ */