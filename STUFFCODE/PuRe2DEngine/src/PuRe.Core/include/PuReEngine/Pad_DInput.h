#ifndef _PAD_DINPUT_H_
#define _PAD_DINPUT_H_

#include "IPad.h"

#define DIRECTINPUT_VERSION 0x0800 
#include <dinput.h>

#include <wbemidl.h>
#include <oleauto.h>
#include <cstdio>
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) \
   if(x != NULL)        \
   {                    \
      x->Release();     \
      x = NULL;         \
   }
#endif


#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Class for Pads
        ///
        class CDPAD : public IPAD
        {
        public:
            CDPAD(LPDIRECTINPUTDEVICE8 Pad);
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

            void SetValue(int32 Key, bool State);
        private:
            LPDIRECTINPUTDEVICE8 m_Pad;
            /// @brief Gamepad pressed once
            ///
            bool m_GamepadPress[14];
            /// @brief Gamepad pressed
            ///
            bool m_GamepadIsPress[14];

            float32 m_LeftTrigger;
            float32 m_RightTrigger;
            Vector2<float32> m_LeftStick;
            Vector2<float32> m_RightStick;

        };
    }
}

#endif /* _PAD_XINPUT_H_ */
