#ifndef _BUBBLEEMITTER_H_
#define _BUBBLEEMITTER_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SpriteReader.h"
#include "LuaReader.h"
#include "Player.h"

// Declare namespace Game
namespace Game
{
    /// @brief A Bubble
    ///
    struct SBubble
    {
        PuRe_Vector3F Position;
        float32 Angle;
        float32 Speed;
        PuRe_Vector3F Size;
        float32 lifeTime;
    };
    /// @brief Bubble Emitter which emits bubbles 
    ///
    class CBubbleEmitter
    {
    private:
        /// @brief All Bubbles
        ///
        PuRe_List<SBubble> m_Bubbles;
        /// @brief Sprite Object
        ///
        PuRe_Sprite* m_pBubbleSprite;
    public:
        /// @brief Initializes an Instance of BubbleEmitter
        ///
        /// @param Sprite object
        ///
        CBubbleEmitter(PuRe_Sprite* a_pBubbleSprite);
        /// @brief Destroyes an Instance of BubbleEmitter
        ///
        ~CBubbleEmitter();
    public:
        /// @brief Emits Bubbles
        ///
        /// @param At which Position he should emit
        /// @param At which Angle he should emit
        /// @param Which Speed the Bubbles have
        /// @param How many Bubbles are spawned
        /// @param How long the bubbles life
        /// @param size from 0 to 1
        ///
        void Emit(PuRe_Vector3F a_Position, float32 a_Angle, float32 a_Speed, int32 a_Amount, float32 a_lifeTime,float32 a_Size);
        /// @brief Updates Bubbles
        ///
        /// @param Delta Time
        ///
        void Update(float32 a_DeltaTime);
        /// @brief Updates Bubbles
        ///
        /// @param Delta Time
        ///
        void Draw(PuRe_Camera* a_pCamera, PuRe_IMaterial* a_pMaterial);
    };
}
#endif /* _BUBBLEEMITTER_H_ */