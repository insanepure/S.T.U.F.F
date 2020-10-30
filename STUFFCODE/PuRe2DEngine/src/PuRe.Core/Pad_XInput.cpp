#include "include\PuReEngine\Pad_XInput.h"

namespace PuReEngine
{
    namespace Core
    {
        CXPAD::CXPAD(int index) : m_Index(index)
        {
        }

        bool CXPAD::GamepadPressed(EGamepad a_Key)
        {
            return this->m_GamepadPress[a_Key];
        }

        bool CXPAD::GamepadIsPressed(EGamepad a_Key)
        {
            //GetForegroundWindow() == this->m_HWND called previously
            return this->m_GamepadIsPress[a_Key];
        }

        Vector2<float32> CXPAD::GetGamepadLeftThumb()
        {
            XINPUT_STATE state;
            Vector2<float32> thumb(0.0f, 0.0f);
            if (XInputGetState(this->m_Index, &state) == ERROR_SUCCESS)
            {
                thumb.X = fmaxf(-1, (float32)state.Gamepad.sThumbLX / 32767);
                thumb.Y = fmaxf(-1, (float32)state.Gamepad.sThumbLY / 32767);
            }
            return thumb;
        }

        Vector2<float32> CXPAD::GetGamepadRightThumb()
        {
            XINPUT_STATE state;
            Vector2<float32> thumb(0.0f, 0.0f);
            if (XInputGetState(this->m_Index, &state) == ERROR_SUCCESS)
            {
                thumb.X = fmaxf(-1, (float32)state.Gamepad.sThumbRX / 32767);
                thumb.Y = fmaxf(-1, (float32)state.Gamepad.sThumbRY / 32767);
            }
            return thumb;
        }

        float32 CXPAD::GetGamepadLeftTrigger()
        {
            XINPUT_STATE state;
            float32 trigger = 0.0f;
            if (XInputGetState(this->m_Index, &state) == ERROR_SUCCESS)
            {
                trigger = (float32)state.Gamepad.bLeftTrigger / 255;
            }
            return trigger;
        }

        float32 CXPAD::GetGamepadRightTrigger()
        {
            XINPUT_STATE state;
            float32 trigger = 0.0f;
            if (XInputGetState(this->m_Index, &state) == ERROR_SUCCESS)
            {
                trigger = (float32)state.Gamepad.bRightTrigger / 255;
            }
            return trigger;
        }

        bool CXPAD::Validate()
        {
            XINPUT_STATE state;
            if (XInputGetState(this->m_Index, &state) == ERROR_SUCCESS)
            {
                return true;
            }
            return false;
        }

        bool CXPAD::IsActive()
        {
            if (Validate())
            {
                for (int32 key = 0; key < 14; key++)
                {
                    if (this->m_GamepadIsPress[key])
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        void CXPAD::Update()
        {
            PuRe_CLEAR(this->m_GamepadPress);

            XINPUT_STATE state;
            ZeroMemory(&state, sizeof(XINPUT_STATE));
            if (XInputGetState(this->m_Index, &state) == ERROR_SUCCESS)
            {
                for (int32 key = 0; key < 14; key++)
                {
                    switch (key)
                    {
                    case EGamepad::Pad_A:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
                        {
                            if (!this->m_GamepadIsPress[key])
                                this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                        {
                            this->m_GamepadIsPress[key] = false;
                        }
                        break;
                    case EGamepad::Pad_B:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::Pad_X:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;;
                        break;
                    case EGamepad::Pad_Y:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::DPAD_Left:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::DPAD_Right:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::DPAD_Up:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::DPAD_Down:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::Left_Shoulder:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::Right_Shoulder:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::Pad_Back:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::Pad_Start:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::Left_Thumb:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    case EGamepad::Right_Thumb:
                        if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0)
                        {
                            if (!this->m_GamepadIsPress[key]) this->m_GamepadPress[key] = true;
                            this->m_GamepadIsPress[key] = true;
                        }
                        else
                            this->m_GamepadIsPress[key] = false;
                        break;
                    }
                }

            }
        }

    }
}