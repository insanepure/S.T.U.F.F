#include "include/Explosion.h"

namespace Game
{
    CExplosion::CExplosion(float32 a_AnimationSpeed, PuRe_Vector3F a_Position, float32 a_Size) : 
        m_AnimationSpeed(a_AnimationSpeed), m_Position(a_Position), m_Size(a_Size)
    {
        this->m_AnimationTime = 0.0f;
        this->m_Animation = 0;
    }
    CExplosion::~CExplosion()
    {
    }

    // **************************************************************************
    // **************************************************************************

    bool CExplosion::Update(float32 a_Seconds)
    {
        this->m_AnimationTime += (a_Seconds * this->m_AnimationSpeed);
        this->m_Animation = (int32)this->m_AnimationTime;
        if (this->m_Animation > 18)
            return true;
        return false;
    }

    // **************************************************************************
    // **************************************************************************

    void CExplosion::Draw(CSpriteReader* a_pSprite, PuRe_Camera* a_pCamera)
    {
        a_pSprite->Draw(a_pCamera, std::to_string(this->m_Animation).c_str(), this->m_Position, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(this->m_Size, this->m_Size));
    }

}