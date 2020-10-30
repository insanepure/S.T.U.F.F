#ifndef _IPAD_H_
#define _IPAD_H_

#include "Vector2.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief GamePad Keys
        ///
        enum EGamepad
        {
            Pad_A, Pad_B, Pad_X, Pad_Y, DPAD_Left, DPAD_Right, DPAD_Up, DPAD_Down, Left_Shoulder, Right_Shoulder, Pad_Back, Pad_Start, Left_Thumb, Right_Thumb
        };
        /// @brief Class for Pads
        ///
        struct IPAD
        {
        public:
            /// @brief Destroyes an instance of IMaterial
            ///
            virtual ~IPAD() {};
            /// @brief Returns whether a Gamepad is pressed once or not
            ///
            /// @param Checked Gamepad Key
            /// @param Gamepad index
            ///
            /// @returns Boolean if the Gamepad Key is still pressed 
            ///
            virtual bool GamepadPressed(EGamepad a_Key) = 0;

            /// @brief Returns whether a Gamepad is still pressed or not
            ///
            /// @param Checked Gamepad Key
            /// @param Gamepad index
            ///
            /// @returns Boolean if the Gamepad Key is still pressed
            ///
            virtual bool GamepadIsPressed(EGamepad a_Key) = 0;

            /// @brief Returns the Gamepad Left Thumb
            ///
            /// @param Gamepad index
            ///
            /// @returns Vector2 with the Gamepad Left Thumb
            ///
            virtual Vector2<float32> GetGamepadLeftThumb() = 0;

            /// @brief Returns the Gamepad Right Thumb
            ///
            /// @param Gamepad index
            ///
            /// @returns Vector2 with the Gamepad Right Thumb
            ///
            virtual Vector2<float32> GetGamepadRightThumb() = 0;

            /// @brief Returns the Gamepad Left Trigger at the shoulder
            ///
            /// @param Gamepad index
            ///
            /// @returns float32 with the Value of the Left Trigger at the shoulder
            ///
            virtual float32 GetGamepadLeftTrigger() = 0;

            /// @brief Returns the Gamepad Right Trigger at the shoulder
            ///
            /// @param Gamepad index
            ///
            /// @returns float32 with the Value of the Right Trigger at the shoulder
            ///
            virtual float32 GetGamepadRightTrigger() = 0;

            virtual void Update() = 0;

            virtual bool Validate() = 0;

            virtual bool IsActive() = 0;
        };
    }
}

#endif /* _IPAD_H_ */