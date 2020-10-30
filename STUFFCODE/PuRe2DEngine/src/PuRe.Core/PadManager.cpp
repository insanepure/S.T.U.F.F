#define _CRT_SECURE_NO_WARNINGS
#include "include\PuReEngine\PadManager.h"
#include "include\PuReEngine\Pad_DInput.h"
#include "include\PuReEngine\Pad_XInput.h"

#include <algorithm> // remove and remove_if

namespace PuReEngine
{
    namespace Core
    {
        //-----------------------------------------------------------------------------
        // Enum each PNP device using WMI and check each device ID to see if it contains 
        // "IG_" (ex. "VID_045E&PID_028E&IG_00").  If it does, then it's an XInput device
        // Unfortunately this information can not be found by just using DirectInput 
        //-----------------------------------------------------------------------------
        BOOL IsXInputDevice(const GUID* pGuidProductFromDirectInput)
        {
            IWbemLocator*           pIWbemLocator = NULL;
            IEnumWbemClassObject*   pEnumDevices = NULL;
            IWbemClassObject*       pDevices[20] = { 0 };
            IWbemServices*          pIWbemServices = NULL;
            BSTR                    bstrNamespace = NULL;
            BSTR                    bstrDeviceID = NULL;
            BSTR                    bstrClassName = NULL;
            DWORD                   uReturned = 0;
            bool                    bIsXinputDevice = false;
            UINT                    iDevice = 0;
            VARIANT                 var;
            HRESULT                 hr;

            // CoInit if needed
            hr = CoInitialize(NULL);
            bool bCleanupCOM = SUCCEEDED(hr);

            // Create WMI
            hr = CoCreateInstance(__uuidof(WbemLocator),
                NULL,
                CLSCTX_INPROC_SERVER,
                __uuidof(IWbemLocator),
                (LPVOID*)&pIWbemLocator);
            if (FAILED(hr) || pIWbemLocator == NULL)
                goto LCleanup;

            bstrNamespace = SysAllocString(L"\\\\.\\root\\cimv2"); if (bstrNamespace == NULL) goto LCleanup;
            bstrClassName = SysAllocString(L"Win32_PNPEntity");   if (bstrClassName == NULL) goto LCleanup;
            bstrDeviceID = SysAllocString(L"DeviceID");          if (bstrDeviceID == NULL)  goto LCleanup;

            // Connect to WMI 
            hr = pIWbemLocator->ConnectServer(bstrNamespace, NULL, NULL, 0L,
                0L, NULL, NULL, &pIWbemServices);
            if (FAILED(hr) || pIWbemServices == NULL)
                goto LCleanup;

            // Switch security level to IMPERSONATE. 
            CoSetProxyBlanket(pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
                RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

            hr = pIWbemServices->CreateInstanceEnum(bstrClassName, 0, NULL, &pEnumDevices);
            if (FAILED(hr) || pEnumDevices == NULL)
                goto LCleanup;

            // Loop over all devices
            for (;; )
            {
                // Get 20 at a time
                hr = pEnumDevices->Next(10000, 20, pDevices, &uReturned);
                if (FAILED(hr))
                    goto LCleanup;
                if (uReturned == 0)
                    break;

                for (iDevice = 0; iDevice<uReturned; iDevice++)
                {
                    // For each device, get its device ID
                    hr = pDevices[iDevice]->Get(bstrDeviceID, 0L, &var, NULL, NULL);
                    if (SUCCEEDED(hr) && var.vt == VT_BSTR && var.bstrVal != NULL)
                    {
                        // Check if the device ID contains "IG_".  If it does, then it's an XInput device
                        // This information can not be found from DirectInput 
                        if (wcsstr(var.bstrVal, L"IG_"))
                        {
                            // If it does, then get the VID/PID from var.bstrVal
                            DWORD dwPid = 0, dwVid = 0;
                            WCHAR* strVid = wcsstr(var.bstrVal, L"VID_");
                            if (strVid && swscanf(strVid, L"VID_%4X", &dwVid) != 1)
                                dwVid = 0;
                            WCHAR* strPid = wcsstr(var.bstrVal, L"PID_");
                            if (strPid && swscanf(strPid, L"PID_%4X", &dwPid) != 1)
                                dwPid = 0;

                            // Compare the VID/PID to the DInput device
                            DWORD dwVidPid = MAKELONG(dwVid, dwPid);
                            if (dwVidPid == pGuidProductFromDirectInput->Data1)
                            {
                                bIsXinputDevice = true;
                                goto LCleanup;
                            }
                        }
                    }
                    
                    SAFE_RELEASE(pDevices[iDevice]);
                }
            }

        LCleanup:
            if (bstrNamespace)
                SysFreeString(bstrNamespace);
            if (bstrDeviceID)
                SysFreeString(bstrDeviceID);
            if (bstrClassName)
                SysFreeString(bstrClassName);
            for (iDevice = 0; iDevice<20; iDevice++)
                SAFE_RELEASE(pDevices[iDevice]);
            SAFE_RELEASE(pEnumDevices);
            SAFE_RELEASE(pIWbemLocator);
            SAFE_RELEASE(pIWbemServices);

            if (bCleanupCOM)
                CoUninitialize();

            return bIsXinputDevice;
        }
        //LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef
        BOOL CALLBACK DInputCallback(LPCDIDEVICEINSTANCE lpddi, void* pvRef)
        {
            HRESULT hr;
            CPadManager* padManager = (CPadManager*)pvRef;
            LPDIRECTINPUTDEVICE8 joystick;
            LPDIRECTINPUT8 directInput = (LPDIRECTINPUT8)padManager->m_lpDirectInput;

            //Check if it's an XInput Device or not
            if (IsXInputDevice(&lpddi->guidProduct))
            {
                return DIENUM_CONTINUE;
            }

            // Obtain an interface to the enumerated joystick.
            hr = directInput->CreateDevice(lpddi->guidInstance, &joystick, NULL);

            DIDEVCAPS capabilities;

            // Set the data format to "simple joystick" - a predefined data format 
            //
            // A data format specifies which controls on a device we are interested in,
            // and how they should be reported. This tells DInput that we will be
            // passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().
            if (FAILED(hr = joystick->SetDataFormat(&c_dfDIJoystick2)))
            {
                return hr;
            }

            // Set the cooperative level to let DInput know how this device should
            // interact with the system and with other DInput applications.
            if (FAILED(hr = joystick->SetCooperativeLevel(padManager->m_Hwnd, DISCL_EXCLUSIVE |  DISCL_FOREGROUND))) 
            {
                return hr;
            }

            // Determine how many axis the joystick has (so we don't error out setting
            // properties for unavailable axis)
            capabilities.dwSize = sizeof(DIDEVCAPS);
            if (FAILED(hr = joystick->GetCapabilities(&capabilities))) 
            {
                return hr;
            }
            padManager->CreateDInputPad(joystick);

            // If it failed, then we can't use this joystick. (Maybe the user unplugged
            // it while we were in the middle of enumerating it.)
            if (FAILED(hr)) 
            {
                return DIENUM_CONTINUE;
            }

            // Stop enumeration. Note: we're just taking the first joystick we get. You
            // could store all the enumerated joysticks and let the user pick.
            return DIENUM_STOP;
        }

        CPadManager::CPadManager(HWND hWnd) : m_Hwnd(hWnd)
        {
            XINPUT_STATE state;
            for (unsigned int i = 0; i < 10; i++)
            {
                if (XInputGetState(i, &state) == ERROR_SUCCESS)
                {
                    //XINPUT
                    m_Pads.push_back(new CXPAD(i));
                }
                else
                {
                    break;
                }
            }

            HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
            DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_lpDirectInput, NULL);
            LPDIRECTINPUT8 directInput = (LPDIRECTINPUT8)m_lpDirectInput;

            directInput->EnumDevices(DI8DEVCLASS_GAMECTRL, DInputCallback, this, DIEDFL_ATTACHEDONLY);
        }

        CPadManager::~CPadManager()
        {
            for (unsigned int k = 0; k < m_Pads.size(); ++k)
            {
                IPAD* pad = m_Pads[k];
                delete pad;
            }
        }

        void CPadManager::CreateDInputPad(void* pad)
        {
            m_Pads.push_back(new CDPAD((LPDIRECTINPUTDEVICE8)pad));
        }

        int CPadManager::GetGamepads()
        {
            return m_Pads.size();
        }

        bool CPadManager::GamepadPressed(EGamepad a_Key, int32 index)
        {
            if (m_ActivePads[index] == nullptr || GetForegroundWindow() != this->m_Hwnd)
            {
                return false;
            }
            return m_ActivePads[index]->GamepadPressed(a_Key);
        }

        bool CPadManager::GamepadIsPressed(EGamepad a_Key, int32 index)
        {
            if (m_ActivePads[index] == nullptr || GetForegroundWindow() != this->m_Hwnd)
            {
                return false;
            }
            return m_ActivePads[index]->GamepadIsPressed(a_Key);
        }

        Vector2<float32> CPadManager::GetGamepadLeftThumb(int32 index)
        {
            if (m_ActivePads[index] == nullptr || GetForegroundWindow() != this->m_Hwnd)
            {
                return Vector2<float32>::Zero();
            }
            return m_ActivePads[index]->GetGamepadLeftThumb();
        }

        Vector2<float32> CPadManager::GetGamepadRightThumb(int32 index)
        {
            if (m_ActivePads[index] == nullptr || GetForegroundWindow() != this->m_Hwnd)
            {
                return Vector2<float32>::Zero();
            }
            return m_ActivePads[index]->GetGamepadRightThumb();
        }

        float32 CPadManager::GetGamepadLeftTrigger(int32 index)
        {
            if (m_ActivePads[index] == nullptr || GetForegroundWindow() != this->m_Hwnd)
            {
                return 0.f;
            }
            return m_ActivePads[index]->GetGamepadLeftTrigger();
        }

        float32 CPadManager::GetGamepadRightTrigger(int32 index)
        {
            if (m_ActivePads[index] == nullptr || GetForegroundWindow() != this->m_Hwnd)
            {
                return 0.f;
            }
            return m_ActivePads[index]->GetGamepadRightTrigger();
        }

        bool CPadManager::CheckIfActive(IPAD* Pad)
        {
            bool active = false;
            for (int j = 0; j < 4; ++j)
            {
                if (m_ActivePads[j] == Pad)
                {
                    active = true;
                }
            }
            return active;
        }

        void CPadManager::Update()
        {
            //reevaluate pads
            for (int i = 0; i < 4; ++i)
            {
                //so check if he still exists, if not, unset
                if (m_ActivePads[i] != nullptr && !m_ActivePads[i]->Validate())
                {
                    m_Pads.erase(std::remove(m_Pads.begin(), m_Pads.end(), m_ActivePads[i]), m_Pads.end());
                    delete m_ActivePads[i];
                    m_ActivePads[i] = nullptr;
                }

                //check if we have a pad for this slot
                if (m_ActivePads[i] == nullptr)
                {
                    bool padActive = false;
                    for (unsigned int k = 0; k < m_Pads.size(); ++k)
                    {
                        IPAD* pad = m_Pads[k];
                        //check if the pad is doing something and if that pad is not used yet
                        if (pad->IsActive() && !CheckIfActive(pad))
                        {
                            m_ActivePads[i] = pad;
                            padActive = true;
                            break;
                        }
                    }
                    //if we have no pad found, go to the next padSlot
                    if (!padActive)
                    {
                        continue;
                    }
                }

                m_ActivePads[i]->Update();
            }
        }
    }
}