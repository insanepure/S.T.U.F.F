#ifndef _PADMANAGER_H_
#define _PADMANAGER_H_

#include "IPad.h"
#include <Windows.h>
#include <vector>
// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Class for Pad Managing
        ///
        class CPadManager
        {
        private:
            IPAD* m_ActivePads[4];
            std::vector<IPAD*> m_Pads;
        public:
            //Pointer to the DirectInput 8 object , LPDIRECTINPUT8
            void* m_lpDirectInput;
            HWND m_Hwnd;

        public:
            CPadManager(HWND hWnd);
            ~CPadManager();

            /// @brief Get the Amount of connected GamePads
            ///
            /// @returns int as the amount of connected gamepads
            ///
            int GetGamepads();
        public:
            void CreateDInputPad(void* Pad);

            /// @brief Returns whether a Gamepad is pressed once or not
            ///
            /// @param Checked Gamepad Key
            /// @param Gamepad index
            ///
            /// @returns Boolean if the Gamepad Key is still pressed 
            ///
            bool GamepadPressed(EGamepad a_Key, int32 index);

            /// @brief Returns whether a Gamepad is still pressed or not
            ///
            /// @param Checked Gamepad Key
            /// @param Gamepad index
            ///
            /// @returns Boolean if the Gamepad Key is still pressed
            ///
            bool GamepadIsPressed(EGamepad a_Key, int32 index);

            /// @brief Returns the Gamepad Left Thumb
            ///
            /// @param Gamepad index
            ///
            /// @returns Vector2 with the Gamepad Left Thumb
            ///
            Vector2<float32> GetGamepadLeftThumb(int32 index);

            /// @brief Returns the Gamepad Right Thumb
            ///
            /// @param Gamepad index
            ///
            /// @returns Vector2 with the Gamepad Right Thumb
            ///
            Vector2<float32> GetGamepadRightThumb(int32 index);

            /// @brief Returns the Gamepad Left Trigger at the shoulder
            ///
            /// @param Gamepad index
            ///
            /// @returns float32 with the Value of the Left Trigger at the shoulder
            ///
            float32 GetGamepadLeftTrigger(int32 index);

            /// @brief Returns the Gamepad Right Trigger at the shoulder
            ///
            /// @param Gamepad index
            ///
            /// @returns float32 with the Value of the Right Trigger at the shoulder
            ///
            float32 GetGamepadRightTrigger(int32 index);

            void Update();

            bool CheckIfActive(IPAD* Pad);
        };
    }
}

#endif /* _PADMANAGER_H_ */