#ifndef _MENUSCENE_H_
#define _MENUSCENE_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SpriteReader.h"
#include "Player.h"
#include "SoundManager.h"
#include "Highscore.h"
#include "MenuFish.h"

#include "Map.h"

// Declare namespace Game
namespace Game
{
    /// @brief MenuScene to handle Menu
    ///
    class CMenuScene
    {
    public:
        /// @brief Emitter for Bubbles
        ///
        CBubbleEmitter* m_pBubbleEmitter;
        /// @brief Map in the Background
        ///
        CMap* m_pMap;
        /// @brief Whether the fish is mirrored or not
        ///
        bool m_FishMirror;
        /// @brief Position of the Fish
        ///
        PuRe_Vector3F m_FishPosition;
        /// @brief What kind of Fish appears
        ///
        int32 m_FishAppear;
        /// @brief Time for whitening effect
        ///
        float32 m_Time;
        /// @brief Which Option is used
        ///
        int32 m_Option;
        /// @brief Which screen to show
        ///
        int32 m_Screen;
        /// @brief Where in the Position we are at
        ///
        bool m_MenuSwitch;
        /// @brief Where in the Position we are at
        ///
        int32 m_MenuPosition;
        /// @brief Value that defines the Height of the Menu
        ///
        float32 m_StartHeight;
        /// @brief Font used when the button is deactive
        ///
        PuRe_Font* m_pDeactiveFont;
        /// @brief Font used when the button is active
        ///
        PuRe_Font* m_pActiveFont;
        /// @brief Camera Object
        ///
        PuRe_Camera* m_pCamera;
        /// @brief SpriteReader and Font Material
        ///
        PuRe_IMaterial* m_pFontMaterial;
        /// @brief Player Ship Sprites
        ///
        PuRe_Sprite* m_pPlayerSprite;
        /// @brief Sprite for the Menu
        ///
        CSpriteReader* m_pMenuSprite;
        /// @brief Player Array, in MainScene because we need access from Menu and Game
        ///
        CPlayer** m_ppPlayers;
        /// @brief bool so we stop the player from going through each ship without stop
        ///
        bool m_switchShip[4];
        /// @brief Highscore which is displayed when highscore is pressed
        ///
        CHighscore* m_pHighscore;
        /// @brief Fishes that appear in the menu
        ///
        CMenuFish* m_pMenuFish;
        /// @brief FishSprite
        ///
        PuRe_Sprite* m_pFishSprite;

        bool m_DisplayUI;
    public:
        /// @brief Constructor to Initialize the MenuScene

        /// @param Pointer to the Application to get more Informations
        /// @param Array of Players
        ///
        CMenuScene(PuRe_Application* a_pWindow, CPlayer** a_ppPlayers);
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
        /// @returns returns an integer that tells the state
        ///
        /// @remarks 0 = quit, 1 = running, 2 = gamestart
        ///
        int32 Update(PuRe_IGraphics* a_pGraphics, PuRe_IInput* a_pInput, PuRe_Timer* a_pTimer);

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

#endif /* _MENUSCENE_H_ */