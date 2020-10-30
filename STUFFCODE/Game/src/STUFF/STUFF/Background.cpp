#include "include/Background.h"

namespace Game
{

    // **************************************************************************
    // **************************************************************************
    CBackground::CBackground(PuRe_IGraphics* a_pGraphics, PuRe_Vector2F a_Resolution)
    {
        this->m_Resolution = a_Resolution;
        this->m_AnimationTime = 0.0f;
        this->m_Animation = 0;
        this->m_AnimationSpeed = 5.0f;
        PuRe_Vector3F KrakenPos;
        KrakenPos.X = std::rand() % (int32)a_Resolution.X - 800.0f;
        KrakenPos.Y = -(float32)(std::rand() % 2000);
        KrakenPos.Z = 11.5f;
        this->m_pKraken = new CKraken(10.0f, KrakenPos);
    }

    // **************************************************************************
    // **************************************************************************
    CBackground::~CBackground()
    {
        SAFE_DELETE(this->m_pKraken);
    }

    // **************************************************************************
    // **************************************************************************

    void CBackground::Update(float32 a_DeltaTime)
    {
        this->m_AnimationTime += (a_DeltaTime * this->m_AnimationSpeed);
        while(this->m_AnimationTime > 8.0f)
            this->m_AnimationTime = this->m_AnimationTime - 8.0f;
        this->m_Animation = (int32)std::floor(this->m_AnimationTime);
        //Update Kraken
        this->m_pKraken->Update(a_DeltaTime,this->m_Resolution);
    }

    // **************************************************************************
    // **************************************************************************
    void CBackground::Draw(PuRe_Camera* a_pCamera, PuRe_Vector3F a_CamPosition, PuRe_Vector2F a_MinMax_X, PuRe_Vector2F a_MinMax_Y)
    {
        a_MinMax_Y.X -= this->m_Resolution.Y/2;
        a_MinMax_Y.Y += this->m_Resolution.Y / 2;

        //Calculate at which % we are on the background
        PuRe_Vector3F PositionVar = a_CamPosition;
        PositionVar.X = (PositionVar.X + abs(a_MinMax_X.X)) / (abs(a_MinMax_X.X) + abs(a_MinMax_X.Y));
        PositionVar.Y = 1.0f-(PositionVar.Y + abs(a_MinMax_Y.X)) / (abs(a_MinMax_Y.X) + abs(a_MinMax_Y.Y));


        //CBackground::m_pMaterial->Apply();
        //printf("PositionValue: %f\n", PositionVar.Y);
        //CBackground::m_pMaterial->SetFloat(PositionVar.Y, "PositionValue");
        //CBackground::m_pMaterial->SetFloat(this->m_Resolution.Y, "Resolution");
        //Invert y axis
        PuRe_Vector3F Position;
        Position.X = a_CamPosition.X - ((4280.0f - this->m_Resolution.X) * PositionVar.X);
        Position.Y = a_CamPosition.Y + ((1806.0f - this->m_Resolution.Y) * PositionVar.Y);
        Position.Z = 13.0f;
        CBackground::m_pBackground->Draw(a_pCamera, "background-1", Position, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        PositionVar.Y = 1.0f - PositionVar.Y;
        Position.X = a_CamPosition.X - ((5120.0f - this->m_Resolution.X) * PositionVar.X);
        Position.Y = a_CamPosition.Y - ((2800.0f - this->m_Resolution.Y) * PositionVar.Y) + (this->m_Resolution.Y / 2.0f*PositionVar.Y);
        Position.Z = 12.0f;
        CBackground::m_pBackground->Draw(a_pCamera, "background-2", Position, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));

        this->m_pKraken->Draw(CBackground::m_pKrakenSprite,a_pCamera,a_CamPosition);

        Position.X = a_CamPosition.X - ((7680.0f - this->m_Resolution.X) * PositionVar.X);
        Position.Y = a_CamPosition.Y - ((3240.0f - this->m_Resolution.Y) * PositionVar.Y) + (this->m_Resolution.Y / 2.0f*PositionVar.Y);
        Position.Z = 11.0f;
        CBackground::m_pBackground->Draw(a_pCamera, "background-3", Position, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        Position.X = a_CamPosition.X - ((2730.0f - this->m_Resolution.X) * PositionVar.X);
        Position.Y = a_CamPosition.Y - ((2730.0f - this->m_Resolution.Y) * PositionVar.Y) + (this->m_Resolution.Y / 2.0f*PositionVar.Y);
        Position.Z = 10.0f;
        CBackground::m_pLights->Draw(a_pCamera, std::to_string(this->m_Animation + 1).c_str(), Position, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
/*        CBackground::m_pMaterial->Apply();
        CBackground::m_pMaterial->SetFloat(0.0f, "PositionValue");
        CBackground::m_pMaterial->SetFloat(0.0f, "Resolution")*/;
    }
    
}