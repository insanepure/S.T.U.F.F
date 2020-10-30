#include "include/CreditScene.h"
#include "include/SpriteManager.h"
namespace Game
{

    CCreditScene::CCreditScene(PuRe_Application* a_pApplication)
    {
        srand((uint32)time(NULL));
    }

    // **************************************************************************
    // **************************************************************************
    void CCreditScene::Initialize(PuRe_IGraphics* a_pGraphics)
    {
        PuRe_GraphicsDescription gDesc = a_pGraphics->GetDescription();
        this->m_pMaterial = a_pGraphics->LoadMaterial("data/effects/default/default");
        this->m_pFontMaterial = a_pGraphics->LoadMaterial("data/effects/credits/default");

        this->m_pMenuSprite = new CSpriteReader(m_pFontMaterial, CSpriteManager::GetSprite("Menu"), "data/textures/menu.txt");

        this->m_pActiveFont = new PuRe_Font(a_pGraphics, "data/textures/font.dds");
        this->m_pCamera = new PuRe_Camera(PuRe_Vector2F((float32)gDesc.ResolutionWidth, (float32)gDesc.ResolutionHeight), PuRe_Camera_Orthogonal);
        this->m_pCrossHairSprite = new PuRe_Sprite(a_pGraphics, "data/textures/crosshair.dds");
        this->m_pExplosionSprite = new CSpriteReader(this->m_pFontMaterial, CSpriteManager::GetSprite("Explosions"),"data/textures/explosion.txt");

        this->m_pFishSprite = CSpriteManager::GetSprite("Echsenfisch");
        this->m_Time = 0.0f;
        this->m_DisplayTime = 0.0f;

        this->m_pHighscore = new CHighscore("high.score");

        for (int32 i=0;i<4;i++)
        {
            this->m_CrossHairPosition[i] = PuRe_Vector3F(-1280.0f, -1280.0f, 1.0f);
            this->m_ShotTime[i] = 0.0f;
        }

        this->m_pMap = new CMap("data/lua/map.lua", this->m_pFontMaterial, a_pGraphics, true);
        //Create Bubble Emitter
        this->m_pBubbleEmitter = new CBubbleEmitter(CSpriteManager::GetSprite("Bubbles"));

    }

    // **************************************************************************
    // **************************************************************************
    bool CCreditScene::Update(PuRe_IGraphics* a_pGraphics, PuRe_IInput* a_pInput, PuRe_Timer* a_pTimer)
    {
        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();
        float32 Seconds = a_pTimer->GetDeltaTime();
        this->m_Time += Seconds;

        int32 spawnChance = std::rand() % 1000;
        //Spawn Fish
        if (spawnChance > 950 && this->m_Time < 40.0f)
        {
            CMenuFish* fish = new CMenuFish(20.0f);
            //Set Fish Values
            int32 y = std::rand() % gdesc.ResolutionHeight;
            fish->m_pBoundingBox.m_Size = PuRe_Vector3F(125.0f,64.0f,0.0f);
            int32 right = std::rand() % 2;

            if (right == 0)
            {
                fish->m_SwimRight = false;
                fish->m_Position = PuRe_Vector3F((float32)gdesc.ResolutionWidth, (float32)y, 1.0f);
            }
            else
            {
                fish->m_SwimRight = true;
                fish->m_Position = PuRe_Vector3F(-256.0, (float32)y, 1.0f);
            }
            fish->m_pBoundingBox.m_Position = fish->m_Position + PuRe_Vector3F(50.0f, 100.0f, -1.0f);
            this->m_Fishs.push_back(fish);
        }
        //Update Fishs
        for (uint32 i = 0; i < this->m_Fishs.size(); i++)
        {
            this->m_Fishs[i]->Update(Seconds);
            float32 Speed = Seconds*100.0f;
            if (!this->m_Fishs[i]->m_SwimRight)
                Speed = -Speed;
            this->m_Fishs[i]->m_Position += PuRe_Vector3F(Speed, 0.0f, 0.0f);
            this->m_Fishs[i]->m_pBoundingBox.m_Position = this->m_Fishs[i]->m_Position + PuRe_Vector3F(50.0f, 100.0f, -1.0f);
            if (this->m_Fishs[i]->m_Position.X > gdesc.ResolutionWidth || this->m_Fishs[i]->m_Position.X < -256.0f)
            {
                SAFE_DELETE(this->m_Fishs[i]);
                if (this->m_Fishs.begin() + i < this->m_Fishs.end())
                    this->m_Fishs.erase(this->m_Fishs.begin() + i);
            }
        }
        //Update Explosions
        for (uint32 i = 0; i < this->m_Explosions.size(); i++)
        {
            bool dead = this->m_Explosions[i]->Update(Seconds);
            if (dead)
            {
                SAFE_DELETE(this->m_Explosions[i]);
                if (this->m_Explosions.begin() + i < this->m_Explosions.end())
                    this->m_Explosions.erase(this->m_Explosions.begin() + i);
            }
        }

        //Skip Credirs
        if (a_pInput->GamepadPressed(PuReSpace::Pad_Start, 0))
            this->m_Time += 5.0f;
        //Credit end
        if (this->m_Time > 50.0f)
            return true;
        //Displaytime
        this->m_DisplayTime = (float32)((int32)this->m_Time % 10) + (this->m_Time - (int32)this->m_Time);
        //Speed of the Crosshair
        float32 Speed = Seconds*1000.0f;
        //Handle Crosshair
        for (int32 i = 0; i<4; i++)
        {
            //Handle Movement
            PuRe_Vector2F leftThumb = a_pInput->GetGamepadLeftThumb(i);
            if (leftThumb.X > 0.25f || leftThumb.X < -0.25f || leftThumb.Y > 0.25f || leftThumb.Y < -0.25f)
            {
                if (this->m_CrossHairPosition[i].X == -1280.0f&&this->m_CrossHairPosition[i].Y == -1280.0f)
                    this->m_CrossHairPosition[i] = PuRe_Vector3F((float32)gdesc.ResolutionWidth / 2, (float32)gdesc.ResolutionHeight/2,0.0f);
                this->m_CrossHairPosition[i] += PuRe_Vector3F(leftThumb.X*Speed, leftThumb.Y*Speed, 0.0f);
                //Set max range
                if (this->m_CrossHairPosition[i].X + 64.0f > gdesc.ResolutionWidth)
                    this->m_CrossHairPosition[i].X = gdesc.ResolutionWidth - 64.0f;
                else if (this->m_CrossHairPosition[i].X < 0.0f)
                    this->m_CrossHairPosition[i].X = 0.0f;
                //Set max range
                if (this->m_CrossHairPosition[i].Y + 64.0f > gdesc.ResolutionHeight)
                    this->m_CrossHairPosition[i].Y = gdesc.ResolutionHeight - 64.0f;
                else if (this->m_CrossHairPosition[i].Y < 0.0f)
                    this->m_CrossHairPosition[i].Y = 0.0f;
            }
            //Handle Press A
            if (a_pInput->GamepadPressed(PuReSpace::Pad_A, i) && this->m_ShotTime[i] <= 0.0f)
            {
                PuRe_Vector3F explosionPosition = this->m_CrossHairPosition[i];
                explosionPosition.X -= 64.0f;
                explosionPosition.Y -= 64.0f;
                explosionPosition.Z = 1.0f;
                CExplosion* explosion = new CExplosion(20.0f, explosionPosition,1.0f);
                this->m_Explosions.push_back(explosion);
                //Check if he hit one
                PuRe_BoundingBox box(this->m_CrossHairPosition[i],PuRe_Vector3F(128.0f,128.0f,0.0f));
                for (uint32 j = 0; j < this->m_Fishs.size(); j++)
                {
                    if (this->m_Fishs[j]->m_pBoundingBox.Intersect(box))
                    {
                        SAFE_DELETE(this->m_Fishs[j]);
                        if (this->m_Fishs.begin() + j < this->m_Fishs.end())
                            this->m_Fishs.erase(this->m_Fishs.begin() + j);
                    }
                }

                if (this->m_CrossHairPosition[i].X == -1280.0f&&this->m_CrossHairPosition[i].Y == -1280.0f)
                    this->m_CrossHairPosition[i] = PuRe_Vector3F((float32)gdesc.ResolutionWidth / 2, (float32)gdesc.ResolutionHeight / 2, 0.0f);
                this->m_ShotTime[i] = 0.5f;
            }
            if (this->m_ShotTime[i] > 0.0f)
                this->m_ShotTime[i] -= Seconds;
        }
        this->m_pMap->Update(Seconds, this->m_pBubbleEmitter, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight));
        //Update Bubbles
        this->m_pBubbleEmitter->Update(Seconds);
        return false;
    }

    // **************************************************************************
    // **************************************************************************
    void CCreditScene::Render(PuRe_IGraphics* a_pGraphics)
    {
        PuRe_Color clear = PuRe_Color(0.0f, 0.4f, 1.0f);
        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();

        PuRe_BoundingBox viewport;
        viewport.m_Position = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
        viewport.m_Size = PuRe_Vector3F((float)gdesc.ResolutionWidth, (float)gdesc.ResolutionHeight, 0.0f);


        a_pGraphics->Clear(clear);
        a_pGraphics->Begin(viewport);
        //Dont use Material
        this->m_pFontMaterial->Apply();
        this->m_pFontMaterial->SetFloat(5.0f, "Time");
        this->m_pFontMaterial->SetFloat(10.0f, "DisplayTime");
        //Render Fishs
        for (uint32 i = 0; i<this->m_Fishs.size(); i++)
            this->m_Fishs[i]->Draw(this->m_pFishSprite, this->m_pCamera, this->m_Fishs[i]->m_Position, !this->m_Fishs[i]->m_SwimRight, this->m_pFontMaterial);
        //Render Explosions
        for (uint32 i = 0; i<this->m_Explosions.size(); i++)
            this->m_Explosions[i]->Draw(this->m_pExplosionSprite, this->m_pCamera);
        //Render crosshair
        for (int32 i = 0; i<4; i++)
        {
            PuRe_Vector3F size(128.0f, 128.0f, 0.0f);
            PuRe_Vector3F Position = this->m_CrossHairPosition[i];
            if (this->m_ShotTime[i] > 0.0f)
            {
                float val = ((0.5f - this->m_ShotTime[i]) * 64.0f);
                size = PuRe_Vector3F(val + 64.0f, val + 64.0f, 0.0f);
                Position.X += 16.0f;
                Position.Y += 16.0f;
                Position.X += this->m_ShotTime[i] * 32.0f;
                Position.Y += this->m_ShotTime[i] * 32.0f;
            }
            Position.Z += 1.0f;
            PuRe_Vector2F UVPosition = PuRe_Vector2F((i % 2)*128.0f, (float32)((int32)(i / 2))*128.0f);
            this->m_pCrossHairSprite->Draw(this->m_pCamera, this->m_pFontMaterial, UVPosition, PuRe_Vector2F(128.0f, 128.0f), Position,
                size, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
        }
        //Use displaytext so its fading
        this->m_pFontMaterial->Apply();
        this->m_pFontMaterial->SetFloat(this->m_DisplayTime, "Time");
        this->m_pFontMaterial->SetFloat(10.0f, "DisplayTime");
        //Draw Text
        if (this->m_Time < 10.0f)
        {
            PuRe_Vector3F Position(((float32)gdesc.ResolutionWidth / 2) - 350.0f, ((float32)gdesc.ResolutionHeight / 2) + 256.0f, -0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Game Designer", Position, PuRe_Vector3F(96.0f, 96.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 45.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(-100.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Gerald Krison", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(0.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Philipp Los", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        }
        else if (this->m_Time > 10.0f&&this->m_Time < 20.0f)
        {
            PuRe_Vector3F Position(((float32)gdesc.ResolutionWidth / 2) - 300.0f, ((float32)gdesc.ResolutionHeight / 2) + 256.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Game Artists", Position, PuRe_Vector3F(96.0f, 96.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 45.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(-50.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Alina Gottbrecht", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(0.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Kathi Wulz", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(0.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Mike Hommel", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(0.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Nadine Uzoglu", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(0.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Tamina Bach", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(0.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Tom Busscher", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        }
        else if (this->m_Time > 20.0f&&this->m_Time < 30.0f)
        {
            PuRe_Vector3F Position(((float32)gdesc.ResolutionWidth / 2) - 400.0f, ((float32)gdesc.ResolutionHeight / 2) + 256.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Game Programmer", Position, PuRe_Vector3F(96.0f, 96.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 45.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(-150.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Andre Braun", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        }
        else if (this->m_Time < 40.0f)
        {
            PuRe_Vector3F Position(((float32)gdesc.ResolutionWidth / 2) - 800.0f, ((float32)gdesc.ResolutionHeight / 2) + 256.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "All Music Composed and arranged by Krys H Kozlowski", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(-100.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "All Sound Designed by Krys H Kozlowski", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(150.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Mixing and Audio post production @Basement Loft Studios", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(-400.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "Frankfurt am Main, Germany", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            Position -= PuRe_Vector3F(-50.0f, 100.0f, 0.0f);
            this->m_pActiveFont->Draw(this->m_pCamera, this->m_pFontMaterial, "All rights reserved", Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        }
        else
        {
            //Highscore
            this->m_pFontMaterial->Apply();
            this->m_pFontMaterial->SetFloat(5.0f, "Time");
            PuRe_Vector3F Position(((float32)gdesc.ResolutionWidth / 2) - 500.0f, ((float32)gdesc.ResolutionHeight / 2)-256.0f, 0.0f);
            this->m_pHighscore->Draw(this->m_pMenuSprite, this->m_pActiveFont, this->m_pCamera, Position, this->m_pFontMaterial);
        }
        this->m_pFontMaterial->Apply();
        this->m_pFontMaterial->SetFloat(5.0f, "Time");
        this->m_pMap->Draw(this->m_pCamera, 0, 100, -100 * 64, 100 * 64, PuRe_Vector3F(0.0f, -500.0f, 0.0f));
        a_pGraphics->End();
    }

    // **************************************************************************
    // **************************************************************************
    void CCreditScene::Exit()
    {
        for (uint32 i = 0; i<this->m_Explosions.size(); i++)
            SAFE_DELETE(this->m_Explosions[i]);
        for (uint32 i = 0; i<this->m_Fishs.size(); i++)
            SAFE_DELETE(this->m_Fishs[i]);
        this->m_Explosions.clear();
        this->m_Fishs.clear();
        SAFE_DELETE(this->m_pBubbleEmitter);
        SAFE_DELETE(this->m_pMap);
        SAFE_DELETE(this->m_pExplosionSprite);
        SAFE_DELETE(this->m_pCrossHairSprite);
        SAFE_DELETE(this->m_pMenuSprite);
        SAFE_DELETE(this->m_pHighscore);
        SAFE_DELETE(this->m_pActiveFont);
        SAFE_DELETE(this->m_pFontMaterial);
        SAFE_DELETE(this->m_pMaterial);
        SAFE_DELETE(this->m_pCamera);
    }
}
