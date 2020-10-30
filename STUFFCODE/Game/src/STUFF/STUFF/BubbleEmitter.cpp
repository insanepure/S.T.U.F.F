#include "include/BubbleEmitter.h"

namespace Game
{
    CBubbleEmitter::CBubbleEmitter(PuRe_Sprite* a_pBubbleSprite)
    {
        this->m_pBubbleSprite = a_pBubbleSprite;
    }

    // **************************************************************************
    // **************************************************************************

    CBubbleEmitter::~CBubbleEmitter()
    {
        this->m_Bubbles.clear();
    }

    // **************************************************************************
    // **************************************************************************

    void CBubbleEmitter::Update(float32 a_DeltaTime)
    {
        for (uint32 i = 0; i<this->m_Bubbles.size(); i++)
        {
            this->m_Bubbles[i].lifeTime -= a_DeltaTime;
            if (this->m_Bubbles[i].lifeTime < 0.0f)
            {
                if (this->m_Bubbles.begin() + i < this->m_Bubbles.end())
                    this->m_Bubbles.erase(this->m_Bubbles.begin() + i);
            }
            else
            {
                this->m_Bubbles[i].Position.X += (cos(this->m_Bubbles[i].Angle)*this->m_Bubbles[i].Speed)*a_DeltaTime*10.0f;
                this->m_Bubbles[i].Position.Y += (sin(this->m_Bubbles[i].Angle)*this->m_Bubbles[i].Speed)*a_DeltaTime*10.0f;
            }
        }
    }

    // **************************************************************************
    // **************************************************************************

    void CBubbleEmitter::Draw(PuRe_Camera* a_pCamera, PuRe_IMaterial* a_pMaterial)
    {
        for (uint32 i = 0; i<this->m_Bubbles.size();i++)
        {
            this->m_pBubbleSprite->Draw(a_pCamera, a_pMaterial,PuRe_Vector2F(0.0f,0.0f),PuRe_Vector2F(16.0f,16.0f), this->m_Bubbles[i].Position, this->m_Bubbles[i].Size, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
        }
    }

    // **************************************************************************

    void CBubbleEmitter::Emit(PuRe_Vector3F a_Position, float32 a_Angle, float32 a_Speed, int32 a_Amount, float32 a_lifeTime, float32 a_Size)
    {
        float32 Size = 0.0f;
        for (int32 i = 0; i < a_Amount; i++)
        {
            SBubble bubble;
            //set variables
            bubble.Angle = a_Angle + ((std::rand() % 50 - 25) * 0.0174532925f);
            bubble.Speed = a_Speed + std::rand() % 16 - 8;
            bubble.lifeTime = a_lifeTime + (float32)(std::rand() % 30 - 15);
            Size = 16.0f + (float32)(std::rand() % 8 - 4);
            bubble.Size = PuRe_Vector3F(Size*a_Size,Size*a_Size,0.0f);
            bubble.Position = a_Position;
            bubble.Position.Z = 9.0f;
            //add it
            this->m_Bubbles.push_back(bubble);
        }
    }
    // **************************************************************************
}