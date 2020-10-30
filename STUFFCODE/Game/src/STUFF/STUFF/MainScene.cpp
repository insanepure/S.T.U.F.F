#include "include/MainScene.h"
#include "include/SpriteManager.h"
namespace Game
{
    float32 CSoundManager::m_MusicVolume;
    float32 CSoundManager::m_SoundVolume;
    PuRe_SoundPlayer* CSoundManager::m_pSoundPlayer;
    PuRe_IMaterial* CBackground::m_pMaterial;
    CSpriteReader* CBackground::m_pLights;
    CSpriteReader* CBackground::m_pBackground;
    CSpriteReader* CBackground::m_pKrakenSprite;


    CMainScene::CMainScene(PuRe_Application* a_pApplication)
    {
        this->m_ppPlayers = new CPlayer*[4];
        for (int32 i = 0; i<4; i++)
            this->m_ppPlayers[i] = new CPlayer(i);
        this->m_pLogoScene = new CLogoScene(a_pApplication);
        this->m_pMenuScene = new CMenuScene(a_pApplication, this->m_ppPlayers);
        this->m_pCreditScene = new CCreditScene(a_pApplication);
        this->m_pGameScene = new CGameScene(a_pApplication, this->m_ppPlayers);
        srand((uint32)time(NULL));
        this->m_LogPerformance = false;
        this->m_LogGame = false;
        this->m_GameStop = false;
    }

    // **************************************************************************
    // **************************************************************************
    void CMainScene::Initialize(PuRe_Application* a_pApplication)
    {
        PuRe_SoundPlayer* a_pSoundPlayer = a_pApplication->GetSoundPlayer();
        PuRe_IGraphics* a_pGraphics = a_pApplication->GetGraphics();
        //create Highscore
        CSoundManager::m_MusicVolume = 1.0f;
        CSoundManager::m_SoundVolume = 1.0f;
        CSoundManager::m_pSoundPlayer = a_pSoundPlayer;
        this->m_Scene = 0;
        this->m_pLogoScene->Initialize(a_pGraphics);

        // BACKGROUND MUSIC
        a_pSoundPlayer->LoadSound("data/audio/boss.wav", "boss");
        a_pSoundPlayer->LoadSound("data/audio/logo.mp3", "logo");
        a_pSoundPlayer->LoadSound("data/audio/intro.wav", "intro");
        a_pSoundPlayer->LoadSound("data/audio/level.wav", "level");
        a_pSoundPlayer->LoadSound("data/audio/outro.wav", "outro");
        // MENU SOUND
        a_pSoundPlayer->LoadSound("data/audio/menucancel.wav", "menucancel");
        a_pSoundPlayer->LoadSound("data/audio/menumovecursor.wav", "menumove");
        a_pSoundPlayer->LoadSound("data/audio/menupressstart.wav", "menustart");
        a_pSoundPlayer->LoadSound("data/audio/menuselectthing.wav", "menuselect");

        //game sound
        a_pSoundPlayer->LoadSound("data/audio/assembleship.wav", "assemble");
        a_pSoundPlayer->LoadSound("data/audio/dismantleship.wav", "dismantle");
        a_pSoundPlayer->LoadSound("data/audio/extralife.wav", "extralife");
        a_pSoundPlayer->LoadSound("data/audio/grabcoin.wav", "grabcoin");
        a_pSoundPlayer->LoadSound("data/audio/grabcoinlow.wav", "grabenemy");
        a_pSoundPlayer->LoadSound("data/audio/grabitem.wav", "grabitem");
        a_pSoundPlayer->LoadSound("data/audio/playerdead_2.wav", "dead");
        a_pSoundPlayer->LoadSound("data/audio/lostship.wav", "lostship");
        a_pSoundPlayer->LoadSound("data/audio/playerhit.wav", "hit");
        a_pSoundPlayer->LoadSound("data/audio/doublefirerate.wav", "doublefirerate");
        a_pSoundPlayer->LoadSound("data/audio/shieldonshort.wav", "shieldonshort");
        a_pSoundPlayer->LoadSound("data/audio/shieldhit.wav", "shieldhit");
        a_pSoundPlayer->LoadSound("data/audio/shielddestroyed.wav", "shielddestroyed");
        a_pSoundPlayer->LoadSound("data/audio/hitrock.wav", "hitrock");

        //lua sounds
        a_pSoundPlayer->LoadSound("data/audio/clustersingle.wav", "2");
        a_pSoundPlayer->LoadSound("data/audio/clustersingle_2.wav", "3");
        a_pSoundPlayer->LoadSound("data/audio/drecksackjump.wav", "6");
        a_pSoundPlayer->LoadSound("data/audio/drecksackmultishot.wav", "7");
        a_pSoundPlayer->LoadSound("data/audio/fishshotgeneric1.wav", "9");
        a_pSoundPlayer->LoadSound("data/audio/gasleak.wav", "12");
        a_pSoundPlayer->LoadSound("data/audio/impact1.wav", "13");
        a_pSoundPlayer->LoadSound("data/audio/impact2.wav", "14");
        a_pSoundPlayer->LoadSound("data/audio/impact3.wav", "15");
        a_pSoundPlayer->LoadSound("data/audio/lasercharge1.wav", "20");
        a_pSoundPlayer->LoadSound("data/audio/minelaunch.wav", "25");
        a_pSoundPlayer->LoadSound("data/audio/mineshort.wav", "26");
        a_pSoundPlayer->LoadSound("data/audio/rammfischengage.wav", "31");
        a_pSoundPlayer->LoadSound("data/audio/rammfischengine.wav", "32");
        a_pSoundPlayer->LoadSound("data/audio/rocketexplosion.wav", "33");
        a_pSoundPlayer->LoadSound("data/audio/rocketlaunch.wav", "34");
        a_pSoundPlayer->LoadSound("data/audio/shot1.wav", "39");
        a_pSoundPlayer->LoadSound("data/audio/shot2.wav", "40");
        a_pSoundPlayer->LoadSound("data/audio/shot3.wav", "41");
        a_pSoundPlayer->LoadSound("data/audio/shot4.wav", "42");
        a_pSoundPlayer->LoadSound("data/audio/toxicarrow.wav", "43");
        //Load static Background
        CBackground::m_pMaterial = a_pGraphics->LoadMaterial("data/effects/light/default");

        PuRe_Sprite* backgroundSprite = new PuRe_Sprite(a_pGraphics, "data/textures/background.dds");
        CSpriteManager::AddSprite("Background", backgroundSprite);
        PuRe_Sprite* lightsSprite = new PuRe_Sprite(a_pGraphics, "data/textures/lights.dds");
        CSpriteManager::AddSprite("Lights", lightsSprite);
        PuRe_Sprite* KrakenSprite = new PuRe_Sprite(a_pGraphics, "data/textures/kraken.dds");
        CSpriteManager::AddSprite("Kraken", KrakenSprite);

        CSpriteManager::AddSprite("Players", new PuRe_Sprite(a_pGraphics, "data/textures/miniuboot.dds"));
        CSpriteManager::AddSprite("Echsenfisch", new PuRe_Sprite(a_pGraphics, "data/textures/echsenfisch.dds"));
        CSpriteManager::AddSprite("Bubbles", new PuRe_Sprite(a_pGraphics, "data/textures/bubble.dds"));
        CSpriteManager::AddSprite("Menu", new PuRe_Sprite(a_pGraphics, "data/textures/menu.dds"));
        CSpriteManager::AddSprite("Tiles", new PuRe_Sprite(a_pGraphics, "data/textures/tiles.dds"));
        CSpriteManager::AddSprite("Falling", new PuRe_Sprite(a_pGraphics, "data/textures/fall.dds"));
        CSpriteManager::AddSprite("Stones", new PuRe_Sprite(a_pGraphics, "data/textures/stones.dds"));
        CSpriteManager::AddSprite("Towers", new PuRe_Sprite(a_pGraphics, "data/textures/destroyable.dds"));
        CSpriteManager::AddSprite("Ambient", new PuRe_Sprite(a_pGraphics, "data/textures/ambient.dds"));
        CSpriteManager::AddSprite("Items", new PuRe_Sprite(a_pGraphics, "data/textures/items.dds"));
        CSpriteManager::AddSprite("Shields", new PuRe_Sprite(a_pGraphics, "data/textures/shield.dds"));
        CSpriteManager::AddSprite("Bullets", new PuRe_Sprite(a_pGraphics, "data/textures/shots.dds"));
        CSpriteManager::AddSprite("Explosions", new PuRe_Sprite(a_pGraphics, "data/textures/explosion.dds"));
        CSpriteManager::AddSprite("HUD", new PuRe_Sprite(a_pGraphics, "data/textures/hud.dds"));

        CBackground::m_pBackground = new CSpriteReader(CBackground::m_pMaterial, backgroundSprite, "data/textures/background.txt");
        CBackground::m_pLights = new CSpriteReader(CBackground::m_pMaterial, lightsSprite, "data/textures/lights.txt");
        CBackground::m_pKrakenSprite = new CSpriteReader(CBackground::m_pMaterial, KrakenSprite, "data/textures/kraken.txt");
    }

    void CMainScene::ValidateLogging(PuRe_IInput* a_pInput)
    {
#ifdef _DEBUG
        if (!a_pInput->KeyPressed(PuReSpace::IInput::F2) && !a_pInput->KeyPressed(PuReSpace::IInput::F1))
        {
            return;
        }

        if (a_pInput->KeyPressed(PuReSpace::IInput::F1))
        {
            this->m_LogPerformance = !this->m_LogPerformance;
        }
        if (a_pInput->KeyPressed(PuReSpace::IInput::F2))
        {
            this->m_LogGame = !this->m_LogGame;
        }

        int LogType = PuRe_LogType::LogError | PuRe_LogType::LogWarning | PuRe_LogType::LogEngine;
        if (this->m_LogGame)
        {
            LogType = LogType | PuRe_LogType::LogGame;
        }
        if (this->m_LogPerformance)
        {
            LogType = LogType | PuRe_LogType::LogPerformance;
        }

        PuRe_Logger::SetLogging(LogType);
#endif
    }
    // **************************************************************************
    // **************************************************************************
    int CMainScene::Update(PuRe_Application* a_pApplication)
    {
        CSpriteManager::Update();

        PuRe_SoundPlayer* a_pSoundPlayer = a_pApplication->GetSoundPlayer();
        PuRe_IGraphics* a_pGraphics = a_pApplication->GetGraphics();
        PuRe_IInput* a_pInput = a_pApplication->GetInput();
        PuRe_Timer* a_pTimer = a_pApplication->GetTimer();
        PuRe_IWindow* a_pWindow = a_pApplication->GetWindow();

#ifdef _DEBUG
        this->ValidateLogging(a_pInput);
#endif

        if (a_pInput->KeyPressed(PuReSpace::IInput::F4))
        {
            this->m_GameStop = !this->m_GameStop;
        }

        if (this->m_GameStop)
        {
            return 1;
        }

        int32 state = 0;
        switch (this->m_Scene)
        {
        case 0:
            if (this->m_pLogoScene->Update(a_pGraphics, a_pInput, a_pTimer))
            {
                PuRe_Logger::Log("Start Menu Scene", PuRe_LogType::LogGame);
                this->m_pLogoScene->Exit();
                //Create STUFF Directory
                std::string userpath = std::getenv("USERPROFILE");
                userpath += "\\Documents\\S.T.U.F.F\\";
                a_pWindow->MakeDirectory(userpath.c_str());
                //Load Menu
                this->m_pMenuScene->Initialize(a_pGraphics);
                CSoundManager::PlayMainSound("intro",true,false,CSoundManager::m_MusicVolume*0.5f);
                this->m_Scene = 1;
            }
            break;
        case 1:
            state = this->m_pMenuScene->Update(a_pGraphics, a_pInput, a_pTimer);
            if (state == 0)
                return true;
            else if(state == 2)
            {
                PuRe_Logger::Log("Start Game Scene", PuRe_LogType::LogGame);
                this->m_pMenuScene->Exit();
                CSoundManager::StopMainSound();
                this->m_pGameScene->Initialize(a_pGraphics);
                CSoundManager::PlayMainSound("level", true, false, CSoundManager::m_MusicVolume*0.5f);
                this->m_Scene = 3;
            }
            else if (state == 3)
            {
                PuRe_Logger::Log("Start Credits Scene", PuRe_LogType::LogGame);
                this->m_pMenuScene->Exit();
                CSoundManager::StopMainSound();
                this->m_pCreditScene->Initialize(a_pGraphics);
                CSoundManager::PlayMainSound("outro", true, false, CSoundManager::m_MusicVolume*0.5f);
                this->m_Scene = 2;
            }
            break;
        case 2:
            if (this->m_pCreditScene->Update(a_pGraphics, a_pInput, a_pTimer))
            {
                PuRe_Logger::Log("Start Menu Scene", PuRe_LogType::LogGame);
                this->m_pCreditScene->Exit();
                CSoundManager::StopMainSound();
                this->m_pMenuScene->Initialize(a_pGraphics);
                CSoundManager::PlayMainSound("intro", true, false, CSoundManager::m_MusicVolume*0.5f);
                this->m_Scene = 1;
            }
            break;
        case 3:
            state = this->m_pGameScene->Update(a_pGraphics, a_pInput, a_pTimer);
            if (state == 0)
            {
                PuRe_Logger::Log("Start Menu Scene", PuRe_LogType::LogGame);
                this->m_pGameScene->Exit();
                CSoundManager::StopMainSound();
                this->m_pMenuScene->Initialize(a_pGraphics);
                CSoundManager::PlayMainSound("intro", true, false, CSoundManager::m_MusicVolume*0.5f);
                this->m_Scene = 1;
            }
            else if (state == 2)
            {
                PuRe_Logger::Log("Restart Game Scene", PuRe_LogType::LogGame);
                this->m_pGameScene->Exit();
                CSoundManager::StopMainSound();
                this->m_pGameScene->Initialize(a_pGraphics);
                CSoundManager::PlayMainSound("level", true, false, CSoundManager::m_MusicVolume*0.5f);
            }
            else if (state == 3)
            {
                PuRe_Logger::Log("Start Credits Scene", PuRe_LogType::LogGame);
                this->m_pGameScene->Exit();
                CSoundManager::StopMainSound();
                this->m_pCreditScene->Initialize(a_pGraphics);
                CSoundManager::PlayMainSound("outro", true, false, CSoundManager::m_MusicVolume*0.5f);
                this->m_Scene = 2;
            }
            break;
        };
        //Handle ESC Button
        if (a_pInput->KeyPressed(a_pInput->ESC))
            return 0;
        return 1;
    }

    // **************************************************************************
    // **************************************************************************
    void CMainScene::Render(PuRe_Application* a_pApplication)
    {
        PuRe_IGraphics* a_pGraphics = a_pApplication->GetGraphics();
        switch (this->m_Scene)
        {
        case 0:
            this->m_pLogoScene->Render(a_pGraphics);
            break;
        case 1:
            this->m_pMenuScene->Render(a_pGraphics);
            break;
        case 2:
            this->m_pCreditScene->Render(a_pGraphics);
            break;
        case 3:
            this->m_pGameScene->Render(a_pGraphics);
            break;
        };
    }

    // **************************************************************************
    // **************************************************************************
    void CMainScene::Exit()
    {
        switch (this->m_Scene)
        {
        case 0:
            this->m_pLogoScene->Exit();
            break;
        case 1:
            this->m_pMenuScene->Exit();;
            break;
        case 2:
            this->m_pCreditScene->Exit();;
            break;
        case 3:
            this->m_pGameScene->Exit();;
            break;
        };
        for (int32 i = 0; i<4; i++)
            SAFE_DELETE(this->m_ppPlayers[i]);
        SAFE_DELETE(this->m_ppPlayers);

        SAFE_DELETE(CBackground::m_pMaterial);
        SAFE_DELETE(CBackground::m_pBackground);
        SAFE_DELETE(CBackground::m_pLights);
        SAFE_DELETE(CBackground::m_pKrakenSprite);

        CSpriteManager::Clear();
    }
}
