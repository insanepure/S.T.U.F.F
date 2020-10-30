#include "include/Kraken.h"

namespace Game
{
    CKraken::CKraken(float32 a_AnimationSpeed, PuRe_Vector3F a_Position) :
        m_AnimationSpeed(a_AnimationSpeed), m_Position(a_Position)
    {
        this->m_AnimationTime = 0.0f;
        this->m_Animation = 0;
    }
    CKraken::~CKraken()
    {
    }

    // **************************************************************************
    // **************************************************************************

    void CKraken::Update(float32 a_Seconds, PuRe_Vector2F a_Resolution)
    {
        this->m_AnimationTime += (a_Seconds * this->m_AnimationSpeed);
        while (this->m_AnimationTime > 20.0f)
            this->m_AnimationTime -= 20.0f;
        this->m_Animation = (int32)this->m_AnimationTime;
        if (this->m_Animation >= 16 || this->m_Animation <= 2)
        {
            this->m_Position.Y += 200.0f*a_Seconds;
            if (this->m_Position.Y-800.0f > a_Resolution.Y)
            {
                this->m_Position.Y = -(float32)(std::rand() % 2000);
                this->m_Position.X = std::rand() %  (int32)a_Resolution.X - 800.0f;
            }
        }

    }

    // **************************************************************************
    // **************************************************************************

    void CKraken::Draw(CSpriteReader* a_pSprite, PuRe_Camera* a_pCamera,PuRe_Vector3F a_CamPosition)
    {
        a_pSprite->Draw(a_pCamera, std::to_string(this->m_Animation+1).c_str(), this->m_Position+a_CamPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f,1.0f));
    }

}