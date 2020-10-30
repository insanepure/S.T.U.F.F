#include "include/Hud.h"
#include "include/SpriteManager.h"

namespace Game
{
    // **************************************************************************
    // **************************************************************************
    CHUD::CHUD(PuRe_Vector2F a_Resolution, PuRe_IGraphics* a_pGraphics, PuRe_IMaterial* a_pFontMaterial, PuRe_IMaterial* a_pBulletMaterial)
    {
        m_pBulletMaterial = a_pBulletMaterial;
        m_pFontMaterial = a_pFontMaterial;
        this->m_pHudSprite = new CSpriteReader(a_pFontMaterial, CSpriteManager::GetSprite("HUD"), "data/textures/hud.txt"); //deleted by m_pHud
        this->m_pGameEndSprite = new PuRe_Sprite(a_pGraphics, "data/textures/game_over.dds");
        this->m_pParticleSprite = new PuRe_Sprite(a_pGraphics, "data/textures/revive.dds");
        this->m_pFont = new PuRe_Font(a_pGraphics, "data/textures/font.dds"); //deleted by m_pHud
        this->m_pDeactiveFont = new PuRe_Font(a_pGraphics, "data/textures/fontdark.dds"); //deleted by m_pHud
        this->m_pCamera = new PuRe_Camera(a_Resolution,PuRe_Camera_Orthogonal);
        this->m_pHudEmitter = new CHudEmitter();
        this->m_Resolution = a_Resolution;
        this->m_ExtraLifeTimer = 0.0f;
        this->m_ExtraLifeStart = false;
    }
    // **************************************************************************
    // **************************************************************************
    CHUD::~CHUD()
    {
        SAFE_DELETE(this->m_pHudEmitter);
        SAFE_DELETE(this->m_pParticleSprite);
        SAFE_DELETE(this->m_pGameEndSprite);
        SAFE_DELETE(this->m_pHudSprite);
        SAFE_DELETE(this->m_pFont);
        SAFE_DELETE(this->m_pDeactiveFont);
        SAFE_DELETE(this->m_pCamera);
    }
    // **************************************************************************
    // **************************************************************************
    void CHUD::Update(float32 a_DeltaTime)
    {
        this->m_pHudEmitter->Update(a_DeltaTime);
    }
    // **************************************************************************
    // **************************************************************************
    bool CHUD::ReviveUpdate(float32 a_DeltaTime)
    {
        this->m_ReviveTimer += a_DeltaTime;
        if (this->m_ReviveTimer > 4.0f)
            return true;
        else
            return false;
    }
    // **************************************************************************
    // **************************************************************************
    bool CHUD::ExtraLifeUpdate(float32 a_DeltaTime)
    {
        this->m_ExtraLifeTimer += a_DeltaTime;
        if (this->m_ExtraLifeTimer > 3.0f)
            return true;
        else
            return false;
    }
    // **************************************************************************
    // **************************************************************************
    void CHUD::Draw(int32 a_PauseWhere, PuRe_IMaterial* a_pMaterial, PuRe_IMaterial* a_pFontMaterial)
    {
        a_pMaterial->Apply();
        a_pMaterial->SetFloat(0.0f, "Gray");
        a_pFontMaterial->Apply();
        a_pFontMaterial->SetFloat(0.0f, "Gray");
        float32 y = this->m_Resolution.Y / 2.0f + 256.0f;
        PuRe_Vector3F pos = PuRe_Vector3F((this->m_Resolution.X / 2.0f) - 256.0f, y, 0.0f);
        if (a_PauseWhere != 3)
        {
            if (a_PauseWhere == 0)
                this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Resume Game", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            else
                this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Resume Game", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            pos.Y -= 100.0f;
            pos.X += 20.0f;
            if (a_PauseWhere == 1)
                this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Combolist", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            else
                this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Combolist", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            pos.Y -= 100.0f;
            pos.X += 10.0f;
            if (a_PauseWhere == 2)
                this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Quit Game", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            else
                this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Quit Game", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        }
        else
        {
            pos.Y += 64.0f;
            pos.X -= 384.0f;
            this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Y      (HOLD)      - Special Attack", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            pos.Y -= 64.0f;
            this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Y-X    (HOLD)      - Advanced Special Attack", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            pos.Y -= 64.0f;
            this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"YX-Y   (HOLD)      - Ultimate Special Attack", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            pos.Y -= 64.0f;
            this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"XXYY-X (HOLD)      - AOE Attack", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            pos.Y -= 64.0f;
            this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"XYYYX              - Sweep Attack", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            pos.Y -= 64.0f;
            this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"XXXYY              - Advanced Attack", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            pos.Y -= 64.0f;
            this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"XXXXY              - Ultimate Attack", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
            pos.Y -= 128.0f;
            pos.X += 256.0f;
            this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Press B to return", pos, PuRe_Vector3F(48.0f, 48.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 26.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
    // **************************************************************************
    // **************************************************************************
    void CHUD::Draw(float32 a_GameEndTime, PuRe_IMaterial* a_pMaterial, PuRe_IMaterial* a_pFontMaterial, bool a_Left)
    {
        a_pMaterial->Apply();
        a_pMaterial->SetFloat(0.0f, "Gray");
        a_pFontMaterial->Apply();
        a_pFontMaterial->SetFloat(0.0f, "Gray");
        float32 Seconds = 3.0f;
        if (a_GameEndTime > Seconds)
            a_GameEndTime = Seconds;
        float32 y = (this->m_Resolution.Y-1024.0f) * (Seconds + 1.0f - a_GameEndTime);
        PuRe_Vector3F pos = PuRe_Vector3F((this->m_Resolution.X / 2.0f) - 512.0f / 2.0f, y, 1.0f);
        this->m_pGameEndSprite->Draw(this->m_pCamera, this->m_pBulletMaterial, pos, PuRe_Vector3F(512.0f, 1024.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
        pos.X += 10.0f;
        pos.Y += 160.0f;
        pos.Z = 0.0f;
        if (a_Left)
            this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Restart", pos, PuRe_Vector3F(48.0f, 48.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 22.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        else
            this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Restart", pos, PuRe_Vector3F(48.0f, 48.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 22.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        pos.X += 320.0f;
        if (a_Left)
            this->m_pDeactiveFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Quit", pos, PuRe_Vector3F(48.0f, 48.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 22.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        else
            this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Quit", pos, PuRe_Vector3F(48.0f, 48.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 22.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        pos.X -= 240.0f;
        pos.Y += 400.0f;
        this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,"Game Over", pos, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
    }
    // **************************************************************************
    // **************************************************************************
    void CHUD::Draw(int32 a_Points, int32 a_Hearts, int32 BigLifes, bool a_ExtraLife, float32 a_Energy, float32 a_toEnergy, CPlayer** a_ppPlayers, PuRe_Sprite* a_pItemSprite, PuRe_IMaterial* a_pFontMaterial)
    {
        PuRe_Vector3F pos = PuRe_Vector3F((this->m_Resolution.X / 2.0f) - 555.0f / 2.0f, 20.0f, 1.0f);
        std::string color;
        pos.X += 12.0f;
        pos.Y += 145.0f;
        if (BigLifes < 1)
            this->m_pHudSprite->Draw(this->m_pCamera, "energie_player_grau", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        else
        {
            pos.X += 3.0f;
            pos.Y += 3.0f;
            this->m_pHudSprite->Draw(this->m_pCamera, "energie_player_gruen", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            pos.X -= 3.0f;
            pos.Y -= 3.0f;
        }
        pos.Y -= 100.0f;
        if (BigLifes < 3)
            this->m_pHudSprite->Draw(this->m_pCamera, "energie_player_grau", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        else
        {
            pos.X += 2.0f;
            pos.Y += 10.0f;
            this->m_pHudSprite->Draw(this->m_pCamera, "energie_player_rot", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            pos.X -= 2.0f;
            pos.Y -= 10.0f;
        }
        pos.X += 470.0f;
        if (BigLifes < 4)
            this->m_pHudSprite->Draw(this->m_pCamera, "energie_player_grau", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        else
        {
            pos.X -= 2.0f;
            pos.Y += 10.0f;
            this->m_pHudSprite->Draw(this->m_pCamera, "energie_player_blau", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            pos.X += 2.0f;
            pos.Y -= 10.0f;
        }
        pos.Y += 100.0f;
        if (BigLifes < 2)
            this->m_pHudSprite->Draw(this->m_pCamera, "energie_player_grau", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        else
        {
            pos.X -= 2.0f;
            pos.Y += 5.0f;
            this->m_pHudSprite->Draw(this->m_pCamera, "energie_player_gelb", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            pos.X += 2.0f;
            pos.Y -= 5.0f;
        }
        pos.Y -= 145.0f;
        pos.X -= 260.0f;
        PuRe_Vector3F reviveStartPos = pos;
        reviveStartPos.X += 58.0f;
        reviveStartPos.Y += 29.0f;
        if (a_ExtraLife)
            this->m_pHudSprite->Draw(this->m_pCamera, "extra_life_gruen", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        else
            this->m_pHudSprite->Draw(this->m_pCamera, "extra_life_grau", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        pos = PuRe_Vector3F((this->m_Resolution.X / 2.0f) - 555.0f / 2.0f, 20.0f, 0.9f);
        this->m_pHudSprite->Draw(this->m_pCamera, "energie_base", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        pos.Y += 70.0f;
        pos.X += 50.0f;
        pos.Z = 0.8f;
        float32 Size_X;
        if (a_Energy != a_toEnergy)
        {
            a_pFontMaterial->Apply();
            a_pFontMaterial->SetFloat(1.6f, "Time");
            Size_X = a_toEnergy / 100.0f;
            this->m_pHudSprite->Draw(this->m_pCamera, "energie_aufgeladen", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(Size_X, 1.0f), PuRe_Vector2F(Size_X, 1.0f));
            a_pFontMaterial->Apply();
            a_pFontMaterial->SetFloat(0.0f, "Time"); pos.Z = 1.0f;
        }
        Size_X = a_Energy / 100.0f;
        pos.Z = 0.7f;
        this->m_pHudSprite->Draw(this->m_pCamera, "energie_aufgeladen", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(Size_X, 1.0f), PuRe_Vector2F(Size_X, 1.0f));
        pos.X += Size_X * 450.0f - 2.0f;
        pos.Y += 25.0f;
        pos.Z = 0.6f;
        if (a_Energy != a_toEnergy)
        {
            this->m_pHudSprite->Draw(this->m_pCamera, "slider", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            this->m_pHudEmitter->Emit(pos,1.0f,1,1.0f);
        }
        this->m_pHudEmitter->Draw(this->m_pCamera, this->m_pHudSprite);
        pos.Y -= 10.0f;
        pos.X -= Size_X * 450.0f - 88.0f;
        pos.Z = 0.0f;
        if (this->m_ExtraLifeStart)
        {
            a_pFontMaterial->Apply();
            a_pFontMaterial->SetFloat(this->m_ExtraLifeTimer*2.0f, "Time");
        }
        for (int32 i = 0; i < 4; i++)
        {
            if (a_Hearts-i  > 0)
                this->m_pHudSprite->Draw(this->m_pCamera, "herz_bunt", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            else
                this->m_pHudSprite->Draw(this->m_pCamera, "herz_grau", pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            pos.X += 75.0f;
        }
        a_pFontMaterial->Apply();
        a_pFontMaterial->SetFloat(0.0f, "Time");



        pos.X = 50.0f;
        pos.Z = 1.0f;
        pos.Y = this->m_Resolution.Y - 200.0f;

        PuRe_Vector3F revivePlayer[4];
        for (int32 i = 0; i < 4; i++)
        {
            if (a_ppPlayers[i]->m_IsPlaying)
            {
                switch (a_ppPlayers[i]->m_Ship)
                {
                case 0:
                    color = "gruen_base";
                    break;
                case 1:
                    color = "gelb_base";
                    break;
                case 2:
                    color = "rot_base";
                    break;
                case 3:
                    color = "blau_base";
                    break;
                }
                this->m_pHudSprite->Draw(this->m_pCamera, color.c_str(), pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
                pos.X += 40.0f;
                pos.Y += 60.0f;
                revivePlayer[i] = pos;
                if (a_ppPlayers[i]->m_Item != 0)
                {
                    PuRe_Vector2F UVSize(64.0f, 64.0f);
                    PuRe_Vector2F UVPosition = PuRe_Vector2F(0.0f, (a_ppPlayers[i]->m_Item-1)*64.0f);
                    a_pItemSprite->Draw(this->m_pCamera, this->m_pFontMaterial, UVPosition, UVSize, pos, PuRe_Vector3F(UVSize.X, UVSize.Y, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
                }
                pos.X += 140.0f;
                pos.Y -= 50.0f;
                pos.Z = 0.0f;
                for (int32 j = 0; j < 3; j++)
                {
                    color = "life_" + std::to_string(j + 1);
                    int32 num = a_ppPlayers[i]->GetLifes() - (j * 3);
                    if (num >= 3)
                        color += "_gruen";
                    else if (num >= 2)
                        color += "_orange";
                    else if (num >= 1)
                        color += "_rot";
                    else
                        color += "_grau";
                    this->m_pHudSprite->Draw(this->m_pCamera, color.c_str(), pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
                    pos.X += 50.0f;
                }
                pos.X -= 220.0f;
                pos.Y += 50.0f;
                pos.Z = 0.0f;
                this->m_pFont->Draw(this->m_pCamera, this->m_pFontMaterial,std::to_string(a_ppPlayers[i]->m_Points).c_str(), pos, PuRe_Vector3F(36.0f, 36.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 22.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
                //Reset it for the next
                pos.Z = 1.0f;
                pos.Y -= 60.0f;
                pos.X += 290.0f;
                if (this->m_ReviveStart)
                {
                    PuRe_Vector3F particlepos = revivePlayer[i]-reviveStartPos;
                    float32 time = this->m_ReviveTimer/4.0f;
                    particlepos.X *= time;
                    particlepos.Y *= time;
                    particlepos += reviveStartPos;
                    this->m_pParticleSprite->Draw(this->m_pCamera, this->m_pFontMaterial, particlepos, PuRe_Vector3F(24.0f, 24.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f,0.0f,0.0f));
                }
            }
        }

    }
}