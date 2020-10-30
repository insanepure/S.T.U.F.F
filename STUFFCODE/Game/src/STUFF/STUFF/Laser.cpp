#include "include/Laser.h"

namespace Game
{
    CLaser::CLaser(
        PuRe_BoundingBox a_BoundingBox,
        PuRe_Vector3F a_Position,
        int32 a_Image_B,
        int32 a_Image_MS,
        int32 a_Image_ML,
        int32 a_Image_E,
        float32 a_Image_B_Width,
        float32 a_Image_MS_Width,
        float32 a_Image_ML_Width,
        float32 a_Image_E_Width,
        int32 a_PlayerNum,
        float32 a_LifeTime,
        float32 a_Damage,
        bool a_HitPlayer,
        int32 a_Length) :
        m_BoundingBox(a_BoundingBox),
        m_Position(a_Position),
        m_Image_B(a_Image_B),
        m_Image_MS(a_Image_MS),
        m_Image_ML(a_Image_ML),
        m_Image_E(a_Image_E),
        m_Image_B_Width(a_Image_B_Width),
        m_Image_MS_Width(a_Image_MS_Width),
        m_Image_ML_Width(a_Image_ML_Width),
        m_Image_E_Width(a_Image_E_Width),
        m_PlayerNum(a_PlayerNum),
        m_LifeTime(a_LifeTime),
        m_Damage(a_Damage),
        m_HitPlayer(a_HitPlayer),
        m_Length(a_Length)
    {

    }
    // **************************************************************************
    // **************************************************************************
    CLaser::~CLaser()
    {

    }
    // **************************************************************************
    // **************************************************************************
    PuRe_BoundingBox& CLaser::GetBoundingBox()
    {
        return this->m_BoundingBox;
    }
    // **************************************************************************
    // **************************************************************************
    bool CLaser::Update(PuRe_Vector3F a_Position, float32 a_DeltaTime)
    {
        //change Position
        PuRe_Vector3F diffPosition = this->m_Position;
        this->m_Position = a_Position;
        diffPosition = this->m_Position - diffPosition;
        this->m_BoundingBox.m_Position += diffPosition;

        this->m_LifeTime -= a_DeltaTime;
        if (this->m_LifeTime < 0.0f)
            return true;
        else
            return false;

    }
    // **************************************************************************
    // **************************************************************************
    int32 CLaser::GetPlayer()
    {
        return this->m_PlayerNum;
    }
    // **************************************************************************
    // **************************************************************************
    float32 CLaser::GetDamage()
    {
        return this->m_Damage;
    }
    // **************************************************************************
    // **************************************************************************
    void CLaser::Draw(PuRe_Camera* a_pCamera, CSpriteReader* a_pSprite, PuRe_IMaterial* a_pMaterial)
    {
        PuRe_Vector3F pos = this->m_Position;
         pos.Z = 2.0f;
        a_pSprite->Draw(a_pCamera, std::string("l_" + std::to_string(this->m_Image_B)).c_str(), pos,PuRe_Vector3F(0.0f,0.0f,0.0f),PuRe_Vector2F(1.0f,1.0f));
        pos.X += this->m_Image_B_Width;
        a_pSprite->Draw(a_pCamera, std::string("l_" + std::to_string(this->m_Image_MS)).c_str(), pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
        pos.X += this->m_Image_MS_Width;
        for (int32 i = 0; i < this->m_Length; i++)
        {
            a_pSprite->Draw(a_pCamera, std::string("l_" + std::to_string(this->m_Image_ML)).c_str(), pos, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            pos.X += this->m_Image_ML_Width;
        }
    }
}