#ifndef _HUDEMITTER_H_
#define _HUDEMITTER_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SpriteReader.h"

// Declare namespace Game
namespace Game
{
    /// @brief A Particle
    ///
    struct SParticle
    {
        PuRe_Vector3F Position;
        float32 Speed;
        PuRe_Vector3F Size;
        float32 lifeTime;
    };
    /// @brief Hud Emitter which emits particles 
    ///
    class CHudEmitter
    {
    private:
        /// @brief All Particles
        ///
        PuRe_List<SParticle> m_Particles;
    public:
        /// @brief Initializes an Instance of HudEmitter
        ///
        CHudEmitter();
        /// @brief Destroyes an Instance of HudEmitter
        ///
        ~CHudEmitter();
    public:
        /// @brief Emits Particles
        ///
        /// @param At which Position he should emit
        /// @param Which Speed the Bubbles have
        /// @param How many Bubbles are spawned
        /// @param How long the bubbles life
        ///
        void Emit(PuRe_Vector3F a_Position, float32 a_Speed, int32 a_Amount, float32 a_lifeTime);
        /// @brief Updates Particles
        ///
        /// @param Delta Time
        ///
        void Update(float32 a_DeltaTime);
        /// @brief Draw Particles
        ///
        /// @param Delta Time
        /// @param SpriteObject
        ///
        void Draw(PuRe_Camera* a_pCamera, CSpriteReader* a_pSpriteReader);
    };
}
#endif /* _HUDEMITTER_H_*/