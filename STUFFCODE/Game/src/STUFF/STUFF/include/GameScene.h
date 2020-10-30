#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "Player.h"
#include "Map.h"
#include "LuaReader.h"
#include "GameCamera.h"
#include "Bullet.h"
#include "BubbleEmitter.h"
#include "Enemy.h"
#include "HUD.h"
#include "Item.h"
#include "Explosion.h"
#include "SoundManager.h"
#include "BigUboot.h"
#include "Laser.h"
#include "Highscore.h"

// Declare namespace Game
namespace Game
{
    /// @brief GameScene where the Game happens
    ///
    class CGameScene
    {
    private:
        /// @brief How many deaths happend
        ///
        int32 m_Deaths;
        /// @brief Highscore which is displayed when highscore is pressed
        ///
        CHighscore* m_pHighscore;
        /// @brief If they are comining or not
        ///
        bool m_Combining;
        /// @brief big uboot which players can combine into
        ///
        CBigUboot* m_pBigUboot;
        /// @brief timer for explosions at the end
        ///
        float32 m_BossTimer;
        /// @brief true if boss has been killed
        ///
        bool m_BossKilled;
        /// @brief Explosion's Sprite
        ///
        CSpriteReader* m_pExplosionSprite;
        /// @brief List of Explosions
        ///
        PuRe_List<CExplosion*> m_Explosions;
        /// @brief Energy we aim for
        ///
        float32 m_ToEnergy;
        /// @brief Energy we have
        ///
        float32 m_Energy;
        /// @brief Pause switch so it does not run wild
        ///
        bool m_PauseSwitch;
        /// @brief Where in the Pause Menu he is at
        ///
        int32 m_PauseWhere;
        /// @brief If the game has been paused or not
        ///
        bool m_GamePaused;
        /// @brief If left is choosen or not
        ///
        bool m_GameEndLeft;
        /// @brief Time for the menu to come down
        ///
        float32 m_GameEndTime;
        /// @brief Game ended (all dead) or not
        ///
        bool m_GameEnd;
        /// @brief how many hearts he has
        ///
        int32 m_Hearts;
        /// @brief If he has an extra life or not
        ///
        int32 m_ExtraLife;
        /// @brief Hud Object used to display the hud
        ///
        CHUD* m_pHud;
        /// @brief Lua Reader for the Spawn
        ///
        CLuaReader* m_pSpawnLua;
        /// @brief Lua Reader for the Laser
        ///
        static CLuaReader* m_pLaserLua;
        /// @brief Game Points
        ///
        int32 m_Points;
        /// @brief Emitter for Bubbles
        ///
        CBubbleEmitter* m_pBubbleEmitter;
        /// @brief Camera used to display
        ///
        PuRe_Camera* m_pCamera;
        /// @brief Game specific Camera Object
        ///
        CGameCamera* m_pGameCamera;
        /// @brief Timer to handle Animations
        ///
        float32 m_Time;
        /// @brief Material used to display Bullets
        ///
        PuRe_IMaterial* m_pBulletMaterial;
        /// @brief Material used to display
        ///
        PuRe_IMaterial* m_pMaterial;
        /// @brief SpriteReader and Font Material
        ///
        PuRe_IMaterial* m_pFontMaterial;
        /// @brief Shield's Sprite
        ///
        PuRe_Sprite* m_pShieldSprite;
        /// @brief Player's Sprite
        ///
        PuRe_Sprite* m_pPlayerSprite;
        /// @brief Item's Sprite
        ///
        PuRe_Sprite* m_pItemSprite;
        /// @brief Player Array, in MainScene because we need access from Menu and Game
        ///
        CPlayer** m_ppPlayers;
        /// @brief Map in the Background
        ///
        CMap* m_pMap;
        /// @brief Lua Reader for the Players
        ///
        CLuaReader* m_pPlayerLua;
        /// @brief Sprite Reader for Bullet Sprites
        ///
        CSpriteReader* m_pBulletSprite;
        /// @brief Lua Reader for the Bullets
        ///
        static CLuaReader* m_pBulletLua;
        /// @brief Laser Array
        ///
        static PuRe_List<CLaser*> m_Lasers;
        /// @brief Bullet Array
        ///
        static PuRe_List<CBullet*> m_Bullets;
        /// @brief Enemy Array
        ///
        static PuRe_List<CEnemy*> m_Enemies;
        /// @brief Item Array
        ///
        static PuRe_List<CItem*> m_Items;
        /// @brief Enemy Lua Array
        ///
        static CLuaReader** m_ppEnemyLua;
        /// @brief Enemy's Sprite
        ///
        PuRe_Sprite** m_ppEnemySprite;

        bool m_DisplayUI;
    public:
        /// @brief Constructor to Initialize the GameScene
        ///
        /// @param Pointer to the Application to get more Informations
        /// @param Array of Players
        ///
        CGameScene(PuRe_Application* a_pWindow, CPlayer** a_ppPlayers);
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
        int Update(PuRe_IGraphics* a_pGraphics, PuRe_IInput* a_pInput, PuRe_Timer* a_pTimer);

        /// @brief Renders the scene.
        ///
        /// @param graphics The graphics interface.
        ///
        void Render(PuRe_IGraphics* a_pGraphics);

        /// @brief Exists the scene.
        ///
        void Exit();
    private:
        /// @brief Function to spawn a Laser
        ///
        /// @param LuaState
        ///
        static int CreateLaser(lua_State* a_pLuaState);
        /// @brief Function to spawn a Bullet
        ///
        /// @param LuaState
        ///
        static int CreateBullet(lua_State* a_pLuaState);
        /// @brief Function to spawn a Fish
        ///
        /// @param LuaState
        ///
        static int Spawn(lua_State* a_pLuaState);
        /// @brief Function to spawn an Item
        ///
        /// @param LuaState
        ///
        static int SpawnItem(lua_State* a_pLuaState);
    };

}

#endif /* _GAMESCENE_H_ */