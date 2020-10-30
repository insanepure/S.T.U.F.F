#include "include/MenuFish.h"

namespace Game
{
    CMenuFish::CMenuFish(float32 a_AnimationSpeed) : m_AnimationSpeed(a_AnimationSpeed)
    {
        this->m_AnimationTime = 0.0f;
        this->m_Animation = 0;
        this->m_pBoundingBox = PuRe_BoundingBox(PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
    }
    CMenuFish::~CMenuFish()
    {
    }

    // **************************************************************************
    // **************************************************************************

    void CMenuFish::Update(float32 a_Seconds)
    {
        this->m_AnimationTime += (a_Seconds * this->m_AnimationSpeed);
        while (this->m_AnimationTime > 9.0f)
            this->m_AnimationTime = this->m_AnimationTime - 9.0f;
        this->m_Animation = (int32)this->m_AnimationTime;
    }

    // **************************************************************************
    // **************************************************************************

    void CMenuFish::Draw(PuRe_Sprite* a_pFishSprite, PuRe_Camera* a_pCamera, PuRe_Vector3F a_Position,bool a_Mirror, PuRe_IMaterial* a_pMaterial)
    {
        PuRe_Vector2F UVSize(256.0f,256.0f); 
        PuRe_Vector2F UVPosition = PuRe_Vector2F(UVSize.X*this->m_Animation,0.0f);
        float32 yRotation = 0.0f;
        if (a_Mirror)
            yRotation = 180.0f*0.0174532925f;
        a_pFishSprite->Draw(a_pCamera, a_pMaterial, UVPosition, UVSize, a_Position, PuRe_Vector3F(UVSize.X, UVSize.Y, 0.0f), PuRe_Vector3F(0.0f, yRotation, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
    }

}