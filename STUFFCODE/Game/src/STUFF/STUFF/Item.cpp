#include "include/Item.h"

namespace Game
{
    // **************************************************************************
    // **************************************************************************
    CItem::CItem(int32 a_Type, PuRe_Vector2F a_Position) : m_Type(a_Type)
    {
        this->m_Animation = 0;
        this->m_AnimationTime = 0.0f;
        this->m_AnimationSpeed = 20.0f;
        this->m_BoundingBox = PuRe_BoundingBox(PuRe_Vector3F(a_Position.X, a_Position.Y, 0.0f), PuRe_Vector3F(64.0f,64.0f,0.0f));
    }
    // **************************************************************************
    // **************************************************************************
    CItem::~CItem()
    {
    }
    // **************************************************************************
    // **************************************************************************
    void CItem::Update(float32 a_DeltaTime)
    {
        this->m_AnimationTime += (a_DeltaTime * this->m_AnimationSpeed);
        float32 frames = 8.0f;
        if (this->m_Type == 5)
            frames = 7.0f;
        while (this->m_AnimationTime > frames)
            this->m_AnimationTime = this->m_AnimationTime - frames;
        this->m_Animation = (int32)this->m_AnimationTime;
    }
    // **************************************************************************
    // **************************************************************************
    void CItem::Draw(PuRe_Camera* a_pCamera, PuRe_Sprite* a_pSprite, PuRe_IMaterial* a_pMaterial)
    {
        PuRe_Vector2F UVSize(64.0f, 64.0f);
        PuRe_Vector2F UVPosition = PuRe_Vector2F(UVSize.X*this->m_Animation, this->m_Type*64.0f);
        PuRe_Vector3F pos = this->m_BoundingBox.m_Position;
        pos.Z = 2.0f;
        a_pSprite->Draw(a_pCamera, a_pMaterial, UVPosition, UVSize, pos, PuRe_Vector3F(UVSize.X, UVSize.Y, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
    }
}