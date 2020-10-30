#include "include/LogoScene.h"
#include "include/SpriteManager.h"
namespace Game
{

    CLogoScene::CLogoScene(PuRe_Application* a_pApplication)
    {
    }

    // **************************************************************************
    // **************************************************************************
    void CLogoScene::Initialize(PuRe_IGraphics* a_pGraphics)
    {
        PuRe_GraphicsDescription gDesc = a_pGraphics->GetDescription();
        this->m_pMaterial = a_pGraphics->LoadMaterial("data/effects/default/default");
        this->m_pSTUFFLogo = new PuRe_Sprite(a_pGraphics, "data/textures/STUFF_Logo.dds");
        this->m_pGALogo = new PuRe_Sprite(a_pGraphics, "data/textures/GA_Logo.dds");
        this->m_pCamera = new PuRe_Camera(PuRe_Vector2F((float32)gDesc.ResolutionWidth, (float32)gDesc.ResolutionHeight), PuRe_Camera_Orthogonal);
        this->m_Time = 0.0f;
        this->m_IntroPlayed = false;
    }

    // **************************************************************************
    // **************************************************************************
    bool CLogoScene::Update(PuRe_IGraphics* a_pGraphics, PuRe_IInput* a_pInput, PuRe_Timer* a_pTimer)
    {
        float deltaTime = a_pTimer->GetDeltaTime();
        this->m_Time += deltaTime;
        if (this->m_Time > 3.0f)
        {
            if (!this->m_IntroPlayed)
            {
                this->m_IntroPlayed = true;
                CSoundManager::m_pSoundPlayer->PlaySound("logo", false, false, CSoundManager::m_MusicVolume*0.5f);
            }
            float32 Seconds = this->m_Time - 3.0f;
            float32 Speed = 100.0f;
            if (this->m_LogoRotation < 1080.0f)
            {
                this->m_LogoRotation = Seconds*900.0f;
                this->m_LogoSize.X = (800.0f * Seconds);
                this->m_LogoSize.Y = (800.0f * Seconds);
                this->m_LogoSize.Z = 1.0f;
            }
        }
        bool finishCondition = false;

        finishCondition = this->m_Time > 4.3f &&CSpriteManager::IsReady();

        if (finishCondition)
            return true;
        return false;
    }

    // **************************************************************************
    // **************************************************************************
    void CLogoScene::Render(PuRe_IGraphics* a_pGraphics)
    {
        PuRe_Color clear = PuRe_Color(0.0f, 0.0f, 0.0f);
        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();
        PuRe_Vector3F gsize = PuRe_Vector3F((float32)gdesc.ResolutionWidth / 2.0f, (float32)gdesc.ResolutionHeight / 2.0f, 0.0f);
        PuRe_Vector3F gpos = PuRe_Vector3F((float32)gdesc.ResolutionWidth / 4.0f, (float32)gdesc.ResolutionHeight / 4.0f, 0.0f);

        PuRe_BoundingBox viewport;
        viewport.m_Position = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
        viewport.m_Size = PuRe_Vector3F((float)gdesc.ResolutionWidth, (float)gdesc.ResolutionHeight, 0.0f);


        a_pGraphics->Clear(clear);
        a_pGraphics->Begin(viewport);
        if (this->m_Time < 3.0f)
            this->m_pGALogo->Draw(this->m_pCamera, this->m_pMaterial, gpos, gsize, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
        else
            this->m_pSTUFFLogo->Draw(this->m_pCamera, this->m_pMaterial, gpos, this->m_LogoSize, PuRe_Vector3F(0.0f, 0.0f, this->m_LogoRotation*0.0174532925f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
        a_pGraphics->End();
    }

    // **************************************************************************
    // **************************************************************************
    void CLogoScene::Exit()
    {
        SAFE_DELETE(this->m_pMaterial);
        SAFE_DELETE(this->m_pGALogo);
        SAFE_DELETE(this->m_pSTUFFLogo);
        SAFE_DELETE(this->m_pCamera);
    }
}
