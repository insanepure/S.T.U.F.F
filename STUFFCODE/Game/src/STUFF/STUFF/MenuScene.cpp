#include "include/MenuScene.h"
#include "include/SpriteManager.h"
namespace Game
{

    CMenuScene::CMenuScene(PuRe_Application* a_pApplication, CPlayer** a_ppPlayers)
    {
        this->m_ppPlayers = a_ppPlayers;
        this->m_DisplayUI = true;
    }

    // **************************************************************************
    // **************************************************************************
    void CMenuScene::Initialize(PuRe_IGraphics* a_pGraphics)
    {

        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();
        this->m_pFontMaterial = a_pGraphics->LoadMaterial("data/effects/font/default");

        this->m_pMap = new CMap("data/lua/map.lua", this->m_pFontMaterial, a_pGraphics, true);

        this->m_pActiveFont = new PuRe_Font(a_pGraphics, "data/textures/font.dds");
        this->m_pDeactiveFont = new PuRe_Font(a_pGraphics, "data/textures/fontdark.dds");

        this->m_pMenuSprite = new CSpriteReader(m_pFontMaterial, CSpriteManager::GetSprite("Menu"), "data/textures/menu.txt");
        this->m_pCamera = new PuRe_Camera(PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight), PuRe_Camera_Orthogonal);

        this->m_pPlayerSprite = CSpriteManager::GetSprite("Players");
        this->m_pFishSprite = CSpriteManager::GetSprite("Echsenfisch");

        this->m_pHighscore = new CHighscore("high.score");

        this->m_StartHeight = 2000.0f;

        this->m_pMenuFish = new CMenuFish(20.0f);
        this->m_FishPosition = PuRe_Vector3F(-256.0f, 256.0f, 2.0f);
        //Create Bubble Emitter
        this->m_pBubbleEmitter = new CBubbleEmitter(CSpriteManager::GetSprite("Bubbles"));
        this->m_FishAppear = 0;
        this->m_Time = 0.0f;
        this->m_Option = 0;
        this->m_Screen = 0;
        this->m_MenuPosition = 0;
        for (int32 i = 0; i < 4; i++)
        {
            this->m_ppPlayers[i]->m_Ready = false;
            this->m_ppPlayers[i]->m_IsPlaying = false;
        }
    }

    // **************************************************************************
    // **************************************************************************
    int32 CMenuScene::Update(PuRe_IGraphics* a_pGraphics, PuRe_IInput* a_pInput, PuRe_Timer* a_pTimer)
    {
        float32 Seconds = a_pTimer->GetDeltaTime();
        this->m_Time += Seconds;
        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();

        if (a_pInput->KeyPressed(PuReSpace::IInput::F3))
        {
            this->m_DisplayUI = !this->m_DisplayUI;
        }
        //Random Fish
        this->m_pMenuFish->Update(Seconds);
        if (std::rand() % 100 > 90 && this->m_FishAppear == 0)
        {
            this->m_FishAppear = (std::rand() % 5) + 1;
            switch (this->m_FishAppear)
            {
            case 1:
                this->m_FishMirror = false;
                this->m_FishPosition = PuRe_Vector3F(-256.0f, 256.0f, 4.0f);
                break;
            case 2:
                this->m_FishMirror = true;
                this->m_FishAppear = 3;
                this->m_FishPosition = PuRe_Vector3F((float32)gdesc.ResolutionWidth, 256.0f, 4.0f);
                break;
            case 3:
                this->m_FishMirror = false;
                this->m_FishAppear = 5;
                this->m_FishPosition = PuRe_Vector3F(-256.0f, 768.0f, 4.0f);
                break;
            case 4:
                this->m_FishMirror = true;
                this->m_FishAppear = 6;
                this->m_FishPosition = PuRe_Vector3F((float32)gdesc.ResolutionWidth, 512.0f, 4.0f);
                break;
            case 5:
                this->m_FishMirror = false;
                this->m_FishAppear = 7;
                this->m_FishPosition = PuRe_Vector3F(-256.0f, 1024.0f, 4.0f);
                break;
            }
        }
        else
        {
            switch (this->m_FishAppear)
            {
            case 1:
                this->m_FishPosition.X += Seconds*50.0f;
                if (this->m_FishPosition.X > -64.0f)
                    this->m_FishAppear = 2;
                break;
            case 2:
                this->m_FishPosition.X -= Seconds*200.0f;
                if (this->m_FishPosition.X < -256.0f)
                    this->m_FishAppear = 0;
                break;
            case 3:
                this->m_FishPosition.X -= Seconds*50.0f;
                if (this->m_FishPosition.X < (float32)gdesc.ResolutionWidth - 192.0f)
                    this->m_FishAppear = 4;
                break;
            case 4:
                this->m_FishPosition.X += Seconds*200.0f;
                if (this->m_FishPosition.X >(float32)gdesc.ResolutionWidth)
                    this->m_FishAppear = 0;
                break;
            case 5:
                this->m_FishPosition.X += Seconds*300.0f;
                if (this->m_FishPosition.X > (float32)gdesc.ResolutionWidth)
                    this->m_FishAppear = 0;
                break;
            case 6:
                this->m_FishPosition.X -= Seconds*300.0f;
                if (this->m_FishPosition.X < -256.0f)
                    this->m_FishAppear = 0;
                break;
            case 7:
                this->m_FishPosition.X += Seconds*300.0f;
                if (this->m_FishPosition.X >(float32)gdesc.ResolutionWidth)
                    this->m_FishAppear = 0;
                break;
            }
        }

        //Start going down
        if (this->m_StartHeight > 0.0f)
        {
            this->m_StartHeight -= Seconds*1000.0f;
            if (this->m_StartHeight < 0.0f)
                this->m_StartHeight = 0.0f;
        }
        else
        {
            if (this->m_Screen == 0) //A not pressed yet, go through menu
            {
                //go through menu with Y
                if (a_pInput->GetGamepadLeftThumb(0).Y < 0.2f && a_pInput->GetGamepadLeftThumb(0).Y > -0.2f)
                    this->m_MenuSwitch = false;

                if (a_pInput->GetGamepadLeftThumb(0).Y > 0.9f&&this->m_MenuPosition > 0 && !this->m_MenuSwitch)
                {
                    this->m_MenuPosition--;
                    CSoundManager::m_pSoundPlayer->PlaySound("menumove",false,false,CSoundManager::m_SoundVolume);
                    this->m_MenuSwitch = true;
                }
                else if (a_pInput->GetGamepadLeftThumb(0).Y < -0.9f&&this->m_MenuPosition < 4 && !this->m_MenuSwitch)
                {
                    this->m_MenuPosition++;
                    CSoundManager::m_pSoundPlayer->PlaySound("menumove", false, false, CSoundManager::m_SoundVolume);
                    this->m_MenuSwitch = true;
                }
                //if he pressed A on one button
                if (this->m_MenuPosition == 0 && a_pInput->GamepadPressed(PuReSpace::Pad_A, 0))
                {
                    CSoundManager::m_pSoundPlayer->PlaySound("menuselect", false, false, CSoundManager::m_SoundVolume);
                    this->m_Screen = 1;
                }
                else if (this->m_MenuPosition == 1 && a_pInput->GamepadPressed(PuReSpace::Pad_A, 0))
                {
                    CSoundManager::m_pSoundPlayer->PlaySound("menuselect", false, false, CSoundManager::m_SoundVolume);
                    this->m_Screen = 2;
                }
                else if (this->m_MenuPosition == 2 && a_pInput->GamepadPressed(PuReSpace::Pad_A, 0))
                {
                    CSoundManager::m_pSoundPlayer->PlaySound("menuselect", false, false, CSoundManager::m_SoundVolume);
                    this->m_Screen = 3;
                }
                else if (this->m_MenuPosition == 3 && a_pInput->GamepadPressed(PuReSpace::Pad_A, 0))
                {
                    CSoundManager::m_pSoundPlayer->PlaySound("menuselect", false, false, CSoundManager::m_SoundVolume);
                    return 3;
                }
                else if (this->m_MenuPosition == 4 && a_pInput->GamepadPressed(PuReSpace::Pad_A, 0) && this->m_Screen == 0)
                {
                    CSoundManager::m_pSoundPlayer->PlaySound("menuselect", false, false, CSoundManager::m_SoundVolume);
                    return 0;
                }
            }
            else if (this->m_Screen == 1) //player choose screen
            {
                //if we can start or not
                bool allready = true;
                bool someoneplaying = false;

                if (a_pInput->GamepadIsPressed(PuReSpace::Pad_B, 0) && !this->m_ppPlayers[0]->m_IsPlaying)
                {
                    CSoundManager::m_pSoundPlayer->PlaySound("menucancel", false, false, CSoundManager::m_SoundVolume);
                    //player one pressed b, go offscreen
                    for (int32 i = 0; i < 4; i++)
                    {
                        this->m_ppPlayers[i]->m_Ready = false;
                        this->m_ppPlayers[i]->m_IsPlaying = false;
                    }
                    this->m_Screen = 0;
                }

                //go through all players and handle their input
                for (int32 i = 0; i < 4; i++)
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying&&!this->m_ppPlayers[i]->m_Ready)
                    {
                        //reset switchShip so another ship is picked
                        if (a_pInput->GetGamepadLeftThumb(i).X < 0.2f && a_pInput->GetGamepadLeftThumb(i).X > -0.2f)
                            this->m_switchShip[i] = false;
                        else if (a_pInput->GetGamepadLeftThumb(i).X > 0.9f&&!this->m_switchShip[i] || a_pInput->GetGamepadLeftThumb(i).X < -0.9f&&!this->m_switchShip[i])
                        {
                            this->m_switchShip[i] = true;
                            //now get new ship
                            bool hasShip = false;
                            //if he is at the ship he had before (so all picked), that is gonna be picked
                            while (!hasShip)
                            {
                                hasShip = true;
                                if (a_pInput->GetGamepadLeftThumb(i).X > 0.9f)
                                    this->m_ppPlayers[i]->m_Ship++;
                                else
                                    this->m_ppPlayers[i]->m_Ship--;
                                if (this->m_ppPlayers[i]->m_Ship > 3) // or == 4
                                    this->m_ppPlayers[i]->m_Ship = 0;
                                else if (this->m_ppPlayers[i]->m_Ship < 0) // or == 4
                                    this->m_ppPlayers[i]->m_Ship = 3;
                                //go through players
                                for (int32 j = 0; j < 4; j++)
                                {
                                    //if it is not self
                                    if (i != j)
                                    {
                                        if (this->m_ppPlayers[j]->m_IsPlaying&&this->m_ppPlayers[j]->m_Ship == this->m_ppPlayers[i]->m_Ship)
                                        {
                                            hasShip = false;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    //check if all players
                    if (this->m_ppPlayers[i]->m_IsPlaying&&!this->m_ppPlayers[i]->m_Ready)
                        allready = false;
                    if (this->m_ppPlayers[i]->m_IsPlaying)
                        someoneplaying = true;
                    //handle if he is ready or start playing
                    if (a_pInput->GamepadPressed(PuReSpace::Pad_A, i) && this->m_ppPlayers[i]->m_IsPlaying)
                        this->m_ppPlayers[i]->m_Ready = true;
                    else if (a_pInput->GamepadPressed(PuReSpace::Pad_B, i) && this->m_ppPlayers[i]->m_Ready)
                        this->m_ppPlayers[i]->m_Ready = false;
                    else if (a_pInput->GamepadPressed(PuReSpace::Pad_B, i) && this->m_ppPlayers[i]->m_IsPlaying)
                        this->m_ppPlayers[i]->m_IsPlaying = false;
                    else if (a_pInput->GamepadPressed(PuReSpace::Pad_A, i))
                    {
                        this->m_ppPlayers[i]->m_IsPlaying = true;
                        this->m_ppPlayers[i]->m_Ship = 0;
                        //set the ship of the Player to an untaken ship
                        bool hasShip = false;
                        while (!hasShip)
                        {
                            hasShip = true;
                            //go through players
                            for (int32 j = 0; j < 4; j++)
                            {
                                //if it is not self
                                if (i != j)
                                {
                                    if (this->m_ppPlayers[j]->m_IsPlaying&&this->m_ppPlayers[j]->m_Ship == this->m_ppPlayers[i]->m_Ship)
                                    {
                                        hasShip = false;
                                        break;
                                    }
                                }
                            }
                            if (!hasShip)
                                this->m_ppPlayers[i]->m_Ship++;
                        }
                    }
                }
                //if all picked and are ready to start, check if someone pressed A and start
                if (allready&&someoneplaying)
                {
                    for (int32 i = 0; i < 4; i++)
                    {
                        if (a_pInput->GamepadPressed(PuReSpace::Pad_A, i) && this->m_ppPlayers[i]->m_Ready)
                        {
                            CSoundManager::m_pSoundPlayer->PlaySound("menustart", false, true, CSoundManager::m_SoundVolume);
                            return 2;
                        }
                    }
                }
            }
            else if (this->m_Screen == 2) //option screen
            {
                if (this->m_Option == 0)
                {
                    if (a_pInput->GetGamepadLeftThumb(0).X > 0.9f&&CSoundManager::m_MusicVolume != 1.0f)
                    {
                        CSoundManager::m_MusicVolume += Seconds;
                        if (CSoundManager::m_MusicVolume > 1.0f)
                            CSoundManager::m_MusicVolume = 1.0f;
                        CSoundManager::m_pSoundPlayer->SetVolume(0,CSoundManager::m_MusicVolume*0.5f);
                    }
                    else if (a_pInput->GetGamepadLeftThumb(0).X < -0.9f&&CSoundManager::m_MusicVolume != 0.0f)
                    {
                        CSoundManager::m_MusicVolume -= Seconds;
                        if (CSoundManager::m_MusicVolume < 0.0f)
                            CSoundManager::m_MusicVolume = 0.0f;
                        CSoundManager::m_pSoundPlayer->SetVolume(0, CSoundManager::m_MusicVolume*0.5f);
                    }

                }
                else if (this->m_Option == 1)
                {
                    if (a_pInput->GetGamepadLeftThumb(0).X > 0.9f&&CSoundManager::m_SoundVolume != 1.0f)
                    {
                        CSoundManager::m_SoundVolume += Seconds;
                        if (CSoundManager::m_SoundVolume > 1.0f)
                            CSoundManager::m_SoundVolume = 1.0f;
                    }
                    else if (a_pInput->GetGamepadLeftThumb(0).X < -0.9f&&CSoundManager::m_SoundVolume != 0.0f)
                    {
                        CSoundManager::m_SoundVolume -= Seconds;
                        if (CSoundManager::m_SoundVolume < 0.0f)
                            CSoundManager::m_SoundVolume = 0.0f;
                    }

                }
                //switch music/sound
                if (a_pInput->GetGamepadLeftThumb(0).Y > 0.9f)
                    this->m_Option = 0;
                if (a_pInput->GetGamepadLeftThumb(0).Y < -0.9f)
                    this->m_Option = 1;
                if (a_pInput->GamepadPressed(PuReSpace::Pad_B, 0))
                {
                    CSoundManager::m_pSoundPlayer->PlaySound("menucancel", false, false, CSoundManager::m_SoundVolume);
                    this->m_Screen = 0;
                }
            }
            else if (this->m_Screen == 3) //Quit
            {
                if (a_pInput->GamepadPressed(PuReSpace::Pad_B, 0))
                {
                    CSoundManager::m_pSoundPlayer->PlaySound("menucancel", false, false, CSoundManager::m_SoundVolume);
                    this->m_Screen = 0;
                }
            }
        }
        this->m_pMap->Update(Seconds, this->m_pBubbleEmitter, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight));
        //Update Bubbles
        this->m_pBubbleEmitter->Update(Seconds);
        return 1;
    }

    // **************************************************************************
    // **************************************************************************
    void CMenuScene::Render(PuRe_IGraphics* a_pGraphics)
    {
        PuRe_Color clear = PuRe_Color(0.0f, 0.4f, 1.0f);
        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();

        PuRe_BoundingBox viewport;
        viewport.m_Position = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
        viewport.m_Size = PuRe_Vector3F((float)gdesc.ResolutionWidth, (float)gdesc.ResolutionHeight, 0.0f);


        a_pGraphics->Clear(clear);
        a_pGraphics->Begin(viewport);

        //Z-Index: 13-5
        this->m_pMap->Draw(this->m_pCamera, 0, 100, -100 * 64, 100 * 64, PuRe_Vector3F(0.0f, -600.0f, 0.0f));

        ////// DRAW Bubbles /////
        //Z-Index: 9
        this->m_pBubbleEmitter->Draw(this->m_pCamera, this->m_pFontMaterial);

        PuRe_Vector3F startPosition(0.0f, (float32)gdesc.ResolutionHeight + this->m_StartHeight, 4.0f);

        if (this->m_FishAppear != 0)
            this->m_pMenuFish->Draw(this->m_pFishSprite,  this->m_pCamera, this->m_FishPosition, this->m_FishMirror, this->m_pFontMaterial);
        if (this->m_FishAppear == 7)
            this->m_pMenuFish->Draw(this->m_pFishSprite, this->m_pCamera, PuRe_Vector3F(this->m_FishPosition.X,this->m_FishPosition.Y/2.0f, this->m_FishPosition.Z), this->m_FishMirror, this->m_pFontMaterial);

        if (!this->m_DisplayUI)
        {
            a_pGraphics->End();
            return;
        }

        startPosition -= PuRe_Vector3F(-190.0f, 100.0f, 1.0f); // 3
        this->m_pMenuSprite->Draw(this->m_pCamera, "chain02", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f),PuRe_Vector2F(1.0f,1.0f));
        startPosition -= PuRe_Vector3F(190.0f, 150.0f, 1.0f); // 2
        this->m_pMenuSprite->Draw(this->m_pCamera, "screen_small01", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));

        startPosition -= PuRe_Vector3F(-65.0f, -80.0f, 1.0f); // 1
        if (this->m_MenuPosition == 0)
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "PLAY STUFF", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        else
            this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "PLAY STUFF", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        startPosition += PuRe_Vector3F(-65.0f, -80.0f, 3.0f); // 4

        if (this->m_Screen == 1) // Player Screen
        {
            startPosition += PuRe_Vector3F(330.0f, 100.0f, -1.0f); //3
            this->m_pMenuSprite->Draw(this->m_pCamera, "chain01", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            startPosition += PuRe_Vector3F(340.0f, -100.0f, -1.0f); // 2
            this->m_pMenuSprite->Draw(this->m_pCamera, "screen_small01", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            startPosition += PuRe_Vector3F(90.0f, 80.0f, -1.0f); // 1
            this->m_pFontMaterial->Apply();
            bool allready = true;
            for (int32 i = 0; i < 4; i++)
            {
                if (this->m_ppPlayers[i]->m_IsPlaying&&!this->m_ppPlayers[i]->m_Ready)
                    allready = false;
            }
            if (allready)
            {
                this->m_pFontMaterial->SetFloat(this->m_Time, "Time");
                this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "START", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
            }
            else
                this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "START", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
            this->m_pFontMaterial->Apply();
            this->m_pFontMaterial->SetFloat(0.0f, "Time");
            startPosition -= PuRe_Vector3F(90.0f, 80.0f, -3.0f); // 4

            startPosition += PuRe_Vector3F(190.0f, -50.0f, -1.0f); // 3
            this->m_pMenuSprite->Draw(this->m_pCamera, "chain02", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            startPosition += PuRe_Vector3F(-450.0f, -690.0f, -1.0f); // 2
            this->m_pMenuSprite->Draw(this->m_pCamera, "screen_playstuff", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            startPosition -= PuRe_Vector3F(-450.0f, -690.0f, 0.0f);

            startPosition -= PuRe_Vector3F(400.0f, 150.0f, 1.0f); // 1
            for (int32 i = 0; i < 4; i++)
            {
                std::string player = "Player " + std::to_string(i + 1);
                PuRe_Vector3F nextPosition = PuRe_Vector3F((i % 2)*430.0f, -(float32)((int32)(i / 2))*275.0f, 0.0f);
                startPosition += nextPosition;

                this->m_pMenuSprite->Draw(this->m_pCamera, "player_ctl_out", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
                startPosition += PuRe_Vector3F(10.0f, 40.0f, -1.0f); // 0
                if (this->m_ppPlayers[i]->m_Ready)
                    this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "A", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
                else
                    this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "A", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
                startPosition += PuRe_Vector3F(170.0f, 0.0f, 0.0f);
                if (this->m_ppPlayers[i]->m_IsPlaying)
                    this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, player.c_str(), startPosition, PuRe_Vector3F(42.0f, 42.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 16.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
                else
                    this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, player.c_str(), startPosition, PuRe_Vector3F(42.0f, 42.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 16.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
                startPosition -= PuRe_Vector3F(180.0f, 40.0f, 0.0f); // 0

                if (this->m_ppPlayers[i]->m_IsPlaying)
                {
                    startPosition -= PuRe_Vector3F(-50.0f, 150.0f, 0.0f);
                    PuRe_Vector2F size = PuRe_Vector2F(128.0f, 128.0f);
                    this->m_pPlayerSprite->Draw(
                        this->m_pCamera, this->m_pFontMaterial, PuRe_Vector2F((this->m_ppPlayers[i]->m_Ship % 2)*128.0f, (float32)((int32)(this->m_ppPlayers[i]->m_Ship / 2))*128.0f),
                        size, startPosition, PuRe_Vector3F(size.X, size.Y, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
                    startPosition += PuRe_Vector3F(-50.0f, 150.0f, 0.0f);
                }

                startPosition -= nextPosition;
                startPosition.Z = 1;

            }
            startPosition += PuRe_Vector3F(-460.0f, 200.0f, 3.0f); // 4
        }

        startPosition -= PuRe_Vector3F(-190.0f, 65.0f, 1.0f); // 3
        this->m_pMenuSprite->Draw(this->m_pCamera, "chain02", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        startPosition -= PuRe_Vector3F(190.0f, 145.0f, 1.0f); // 2
        this->m_pMenuSprite->Draw(this->m_pCamera, "screen_small02", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));

        startPosition -= PuRe_Vector3F(-90.0f, -80, 1.0f); // 1
        if (this->m_MenuPosition == 1)
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "OPTIONS", startPosition, PuRe_Vector3F(56.0f, 56.0f , 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        else
            this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "OPTIONS", startPosition, PuRe_Vector3F(56.0f, 56.0f , 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        startPosition += PuRe_Vector3F(-90.0f, -80, 3.0f); // 4

        if (this->m_Screen == 2) // Option Screen
        {
            startPosition += PuRe_Vector3F(330.0f, 0.0f, -1.0f); // 3
            this->m_pMenuSprite->Draw(this->m_pCamera, "chain_03", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            startPosition += PuRe_Vector3F(280.0f, -200.0f, -1.0f); // 2
            this->m_pMenuSprite->Draw(this->m_pCamera, "screen_options", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));

            startPosition += PuRe_Vector3F(40.0f, 350.0f, -1.0f); // 1
            if (this->m_Option == 0)
                this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "MUSIC", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
            else
                this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "MUSIC", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
            startPosition += PuRe_Vector3F(150.0f, 0.0f, -1.0f); // 0

            startPosition += PuRe_Vector3F(270.0f * CSoundManager::m_MusicVolume , 0.0f, 0.0f);
            this->m_pMenuSprite->Draw(this->m_pCamera, "ctl_sound", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            startPosition -= PuRe_Vector3F(270.0f * CSoundManager::m_MusicVolume, 0.0f, 0.0f);

            this->m_pMenuSprite->Draw(this->m_pCamera, "line_sound", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            startPosition -= PuRe_Vector3F(190.0f, 350.0f, -1.0f); // 1


            startPosition += PuRe_Vector3F(40.0f, 150.0f, 0.0f);
            if (this->m_Option == 1)
                this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "SOUND", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
            else
                this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "SOUND", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
            startPosition += PuRe_Vector3F(150.0f, 0.0f, -1.0f); // 0
            startPosition += PuRe_Vector3F(270.0f * CSoundManager::m_SoundVolume, 0.0f, 0.0f);
            this->m_pMenuSprite->Draw(this->m_pCamera, "ctl_sound", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            startPosition -= PuRe_Vector3F(270.0f * CSoundManager::m_SoundVolume, 0.0f, 0.0f);

            this->m_pMenuSprite->Draw(this->m_pCamera, "line_sound", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            startPosition -= PuRe_Vector3F(800.0f, -50.0f, -4.0f); // 4
        }



        startPosition -= PuRe_Vector3F(-190.0f, 65.0f, 1.0f); // 3
        this->m_pMenuSprite->Draw(this->m_pCamera, "chain02", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        startPosition -= PuRe_Vector3F(190.0f, 145.0f, 1.0f); // 2
        this->m_pMenuSprite->Draw(this->m_pCamera, "screen_small03", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));

        startPosition -= PuRe_Vector3F(-70.0f, -80.0f, 1.0f); // 1
        if (this->m_MenuPosition == 2)
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "HIGHSCORE", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        else
            this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "HIGHSCORE", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        startPosition += PuRe_Vector3F(-70.0f, -80.0f, 3.0f); // 4



        if (this->m_Screen == 3) //Highscore Screen
        {
            startPosition += PuRe_Vector3F(330.0f, 0.0f, -1.0f); // 3
            this->m_pMenuSprite->Draw(this->m_pCamera, "chain_03", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            startPosition += PuRe_Vector3F(310.0f, -300.0f, -1.0f); // 2
            this->m_pHighscore->Draw(this->m_pMenuSprite, this->m_pActiveFont, this->m_pCamera, startPosition, this->m_pFontMaterial);
            startPosition -= PuRe_Vector3F(640.0f, -300.0f, -2.0f); // 4
        }

        startPosition -= PuRe_Vector3F(-190.0f, 65.0f, 1.0f); // 3
        this->m_pMenuSprite->Draw(this->m_pCamera, "chain02", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        startPosition -= PuRe_Vector3F(190.0f, 145.0f, 1.0f); // 2
        this->m_pMenuSprite->Draw(this->m_pCamera, "screen_small04", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));

        startPosition -= PuRe_Vector3F(-100.0f, -80.0f, 1.0f); // 1
        if (this->m_MenuPosition == 3)
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "CREDITS", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        else
            this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "CREDITS", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        startPosition += PuRe_Vector3F(-100.0f, -80.0f, 3.0f); // 4

        startPosition -= PuRe_Vector3F(-190.0f, 65.0f, 1.0f); // 3
        this->m_pMenuSprite->Draw(this->m_pCamera, "chain02", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        startPosition -= PuRe_Vector3F(190.0f, 145.0f, 1.0f); // 2
        this->m_pMenuSprite->Draw(this->m_pCamera, "screen_small05", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));

        startPosition -= PuRe_Vector3F(-120.0f, -80.0f, 1.0f); // 1
        if (this->m_MenuPosition == 4)
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "QUIT", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        else
            this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "QUIT", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        startPosition += PuRe_Vector3F(-120.0f, -80.0f, 3.0f); // 4

        startPosition -= PuRe_Vector3F(-150.0f, 65.0f, -1.0f); // 3
        this->m_pMenuSprite->Draw(this->m_pCamera, "anchor", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));

        a_pGraphics->End();
    }

    // **************************************************************************
    // **************************************************************************
    void CMenuScene::Exit()
    {
        SAFE_DELETE(this->m_pBubbleEmitter);
        SAFE_DELETE(this->m_pMap);
        SAFE_DELETE(this->m_pMenuFish);
        SAFE_DELETE(this->m_pHighscore);
        SAFE_DELETE(this->m_pDeactiveFont);
        SAFE_DELETE(this->m_pActiveFont);
        SAFE_DELETE(this->m_pCamera);
        SAFE_DELETE(this->m_pFontMaterial);
        SAFE_DELETE(this->m_pMenuSprite);
    }
}
