#include "include/TestScene.h"
#include <cstdio>
namespace Game
{
     
    CTestScene::CTestScene(PuRe_Application*)
    {
    }

    // **************************************************************************
    // **************************************************************************
    void CTestScene::Initialize(PuRe_Application* a_pApplication)
    {
        PuRe_GraphicsDescription gdesc = a_pApplication->GetGraphics()->GetDescription();
        m_pBackground = new PuRe_Sprite(a_pApplication->GetGraphics(), "../data/textures/background.dds");
        PuRe_Sprite* test = nullptr;
        test = new PuRe_Sprite(a_pApplication->GetGraphics(), "../data/textures/background.dds");
        this->m_pCamera = new PuRe_Camera(PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight), PuRe_Camera_Orthogonal);
        this->m_pMaterial = a_pApplication->GetGraphics()->LoadMaterial("../data/effects/default/default");

        

    }

    // **************************************************************************
    // **************************************************************************
    int CTestScene::Update(PuRe_Application* a_pApplication)
    {
        PuRe_IInput* a_pInput = a_pApplication->GetInput();
        if (a_pInput->GamepadPressed(PuReEngine::Core::Pad_A, 0) )
        {
            printf("Pressed!\n");
        }
        PuRe_Timer* a_pTimer = a_pApplication->GetTimer();
        this->m_Time += a_pTimer->GetDeltaTime();
        printf("Time: %f Absolute: %f\n", this->m_Time, a_pTimer->GetTotalElapsedSeconds());

        return 1;
    }

    // **************************************************************************
    // **************************************************************************
    void CTestScene::Render(PuRe_Application* a_pApplication)
    {
        PuRe_Color PuRe_CLEAR = PuRe_Color(0.0f, 0.4f, 1.0f, 1.0f);

        PuRe_IGraphics* graphics = a_pApplication->GetGraphics();
        PuRe_GraphicsDescription gdesc = graphics->GetDescription();
        PuRe_Vector3F gsize = PuRe_Vector3F((float32)gdesc.ResolutionWidth / 2.0f, (float32)gdesc.ResolutionHeight / 2.0f, 0.0f);
        PuRe_Vector3F gpos = PuRe_Vector3F((float32)gdesc.ResolutionWidth / 4.0f, (float32)gdesc.ResolutionHeight / 4.0f, 0.0f);

        PuRe_BoundingBox viewport;
        viewport.m_Position = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
        viewport.m_Size = PuRe_Vector3F((float)gdesc.ResolutionWidth, (float)gdesc.ResolutionHeight, 0.0f);


        graphics->Clear(PuRe_Color(0.0f, 0.4f, 1.0f));
        graphics->Begin(viewport);
        
        this->m_pBackground->Draw(this->m_pCamera, this->m_pMaterial, gpos, gsize, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));

        graphics->End();


        ///////////////// END FINAL PASS ////////////////////
    }

    // **************************************************************************
    // **************************************************************************
    void CTestScene::Exit()
    {
      
    }
}
