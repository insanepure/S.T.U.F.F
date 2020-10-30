#ifndef _PAD_XINPUT_H_
#define _PAD_XINPUT_H_

#include "IPad.h"
#include <Windows.h>
#include <Xinput.h>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Class for Pads
        ///
        class CXPAD : public IPAD
        {
        public:
            CXPAD(int index);
            /// @brief Returns whether a Gamepad is pressed once or not
            ///
            /// @param Checked Gamepad Key
            /// @param Gamepad index
            ///
            /// @returns Boolean if the Gamepad Key is still pressed 
            ///
            bool GamepadPressed(EGamepad a_Key);

            /// @brief Returns whether a Gamepad is still pressed or not
            ///
            /// @param Checked Gamepad Key
            /// @param Gamepad index
            ///
            /// @returns Boolean if the Gamepad Key is still pressed
            ///
            bool GamepadIsPressed(EGamepad a_Key);

            /// @brief Returns the Gamepad Left Thumb
            ///
            /// @param Gamepad index
            ///
            /// @returns Vector2 with the Gamepad Left Thumb
            ///
            Vector2<float32> GetGamepadLeftThumb();

            /// @brief Returns the Gamepad Right Thumb
            ///
            /// @param Gamepad index
            ///
            /// @returns Vector2 with the Gamepad Right Thumb
            ///
            Vector2<float32> GetGamepadRightThumb();

            /// @brief Returns the Gamepad Left Trigger at the shoulder
            ///
            /// @param Gamepad index
            ///
            /// @returns float32 with the Value of the Left Trigger at the shoulder
            ///
            float32 GetGamepadLeftTrigger();

            /// @brief Returns the Gamepad Right Trigger at the shoulder
            ///
            /// @param Gamepad index
            ///
            /// @returns float32 with the Value of the Right Trigger at the shoulder
            ///
            float32 GetGamepadRightTrigger();

            void Update();

            bool Validate();

            bool IsActive();
        private:
            /// @brief Gamepad pressed once
            ///
            bool m_GamepadPress[14];
            /// @brief Gamepad pressed
            ///
            bool m_GamepadIsPress[14];

            int m_Index;
        };
    }
}

#endif /* _PAD_XINPUT_H_ */
