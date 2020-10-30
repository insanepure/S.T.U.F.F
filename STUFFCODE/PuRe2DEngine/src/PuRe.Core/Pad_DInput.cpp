#include "include\PuReEngine\Pad_DInput.h"
#include <cmath>

namespace PuReEngine
{
    namespace Core
    {
        CDPAD::CDPAD(LPDIRECTINPUTDEVICE8 Pad) : m_Pad(Pad)
        {

        }

        bool CDPAD::GamepadPressed(EGamepad a_Key)
        {
            return this->m_GamepadPress[a_Key];
        }

        bool CDPAD::GamepadIsPressed(EGamepad a_Key)
        {
            return this->m_GamepadIsPress[a_Key];
        }

        Vector2<float32> CDPAD::GetGamepadLeftThumb()
        {
            return this->m_LeftStick;
        }

        Vector2<float32> CDPAD::GetGamepadRightThumb()
        {
            return this->m_RightStick;
        }

        float32 CDPAD::GetGamepadLeftTrigger()
        {
            return this->m_LeftTrigger;
        }

        float32 CDPAD::GetGamepadRightTrigger()
        {
            return this->m_RightTrigger;
        }

        void CDPAD::Update()
        {
            PuRe_CLEAR(this->m_GamepadPress);
            HRESULT     hr;
            DIJOYSTATE2 js;

            // Poll the device to read the current state
            hr = m_Pad->Poll();
            if (FAILED(hr)) 
            {
                // DInput is telling us that the input stream has been
                // interrupted. We aren't tracking any state between polls, so
                // we don't have any special reset that needs to be done. We
                // just re-acquire and try again.
                hr = m_Pad->Acquire();
                while (hr == DIERR_INPUTLOST) 
                {
                    hr = m_Pad->Acquire();
                }

                // If we encounter a fatal error, return failure.
                if ((hr == DIERR_INVALIDPARAM) || (hr == DIERR_NOTINITIALIZED)){
                    return;
                }

                // If another application has control of this device, return successfully.
                // We'll just have to wait our turn to use the joystick.
                if (hr == DIERR_OTHERAPPHASPRIO)
                {
                    return;
                }
            }
            m_Pad->GetDeviceState(sizeof(DIJOYSTATE2), &js);
            for (int i = 0; i < 12; i++)
            {
                bool State = (js.rgbButtons[i] & 0x80) != 0;
                switch (i)
                {
                case 0: //square
                    SetValue(EGamepad::Pad_X, State);
                    break;
                case 1: //x
                    SetValue(EGamepad::Pad_A, State);
                    break;
                case 2: //circle
                    SetValue(EGamepad::Pad_B, State);
                    break;
                case 3: //triangle
                    SetValue(EGamepad::Pad_Y, State);
                    break;
                case 4:
                    SetValue(EGamepad::Left_Shoulder, State);
                    break;
                case 5:
                    SetValue(EGamepad::Right_Shoulder, State);
                    break;
                case 8: //Select/Back
                    SetValue(EGamepad::Pad_Back, State);
                    break;
                case 9:
                    SetValue(EGamepad::Pad_Start, State);
                    break;
                case 10:
                    SetValue(EGamepad::Left_Thumb, State);
                    break;
                case 11:
                    SetValue(EGamepad::Right_Thumb, State);
                    break;
                }
            }

            
            this->m_LeftStick.X = ((float)js.lX - 32768) / 32768;
            this->m_LeftStick.Y = ((float)32768 - js.lY) / 32768;
            this->m_RightStick.X = ((float)js.lZ - 32768) / 32768;
            this->m_RightStick.Y = ((float)32768 - js.lRz) / 32768;
            this->m_LeftTrigger = js.lRx / 65536.0f;
            this->m_RightTrigger = js.lRy / 65536.0f;

            DWORD originDPAD = js.rgdwPOV[0];
            float dpad = 0.0f;
            float dpadY = 0.0f;
            float dpadX = 0.0f;
            if (originDPAD != -1)
            {
                dpad = (originDPAD + 9000) / 100.0f;
                dpad = (dpad * PuRe_DegToRad) - PuRe_PI;
                dpadY = sin((float)dpad);
                dpadX = cos((float)dpad);
            }
            if (dpadY > 0.1f)
            {
                SetValue(EGamepad::DPAD_Down, true);
            }
            else
            {
                SetValue(EGamepad::DPAD_Down, false);
            }
            if (dpadY < -0.1f)
            {
                SetValue(EGamepad::DPAD_Up, true);
            }
            else
            {
                SetValue(EGamepad::DPAD_Up, false);
            }
            if (dpadX > 0.1f)
            {
                SetValue(EGamepad::DPAD_Right, true);
            }
            else
            {
                SetValue(EGamepad::DPAD_Right, false);
            }
            if (dpadX < -0.1f)
            {
                SetValue(EGamepad::DPAD_Left, true);
            }
            else
            {
                SetValue(EGamepad::DPAD_Left, false);
            }
        }

        void CDPAD::SetValue(int32 Key, bool State)
        {
            if (State)
            {
                if (!this->m_GamepadIsPress[Key])
                {
                    this->m_GamepadPress[Key] = true;
                }
                this->m_GamepadIsPress[Key] = true;
            }
            else if(this->m_GamepadIsPress[Key])
            {
                this->m_GamepadIsPress[Key] = false;
            }
        }

        bool CDPAD::Validate()
        {
            // Poll the device to read the current state
            HRESULT hr = m_Pad->Poll();
            if (FAILED(hr))
            {
                hr = m_Pad->Acquire();
                if (hr == DIERR_INPUTLOST)
                {
                    return false;
                }
            }

            return true;
        }

        bool CDPAD::IsActive()
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

            return true;
        }

    }
}