#include "include/HudEmitter.h"

namespace Game
{
    CHudEmitter::CHudEmitter()
    {
    }

    // **************************************************************************
    // **************************************************************************

    CHudEmitter::~CHudEmitter()
    {
        this->m_Particles.clear();
    }

    // **************************************************************************
    // **************************************************************************

    void CHudEmitter::Update(float32 a_DeltaTime)
    {
        for (uint32 i = 0; i<this->m_Particles.size(); i++)
        {
            this->m_Particles[i].lifeTime -= a_DeltaTime;
            if (this->m_Particles[i].lifeTime < 0.0f)
            {
                if (this->m_Particles.begin() + i < this->m_Particles.end())
                    this->m_Particles.erase(this->m_Particles.begin() + i);
            }
            else
            {
                this->m_Particles[i].Position.X -= this->m_Particles[i].Speed*a_DeltaTime*10.0f;
            }
        }
    }

    // **************************************************************************
    // **************************************************************************

    void CHudEmitter::Draw(PuRe_Camera* a_pCamera, CSpriteReader* a_pSpriteReader)
    {
        for (uint32 i = 0; i<this->m_Particles.size(); i++)
        {
            a_pSpriteReader->Draw(a_pCamera, "partikel", this->m_Particles[i].Position, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(this->m_Particles[i].Size.X, this->m_Particles[i].Size.Y));
        }
    }

    // **************************************************************************

    void CHudEmitter::Emit(PuRe_Vector3F a_Position, float32 a_Speed, int32 a_Amount, float32 a_lifeTime)
    {
        float32 Size = 0.0f;
        for (int32 i = 0; i < a_Amount; i++)
        {
            SParticle particle;
            //set variables
            particle.Speed = a_Speed + std::rand() % 4;
            particle.lifeTime = a_lifeTime + (float32)(std::rand() % 10)/20.0f;
            Size = 8.0f + (float32)(std::rand() % 8 - 4);
            Size /= 8.0f;
            particle.Size = PuRe_Vector3F(Size, Size, 0.0f);
            particle.Position = a_Position;
            particle.Position.Y += 50;
            particle.Position.Y += (float32)(std::rand() % 40 - 40);
            particle.Position.Z = 0.5f;
            //add it
            this->m_Particles.push_back(particle);
        }
    }
    // **************************************************************************
}