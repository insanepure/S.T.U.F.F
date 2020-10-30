#include "include/PuReEngine/Application.h"
#include "include/PuReEngine/ThreadManager.h"
#include "include/PuReEngine/Logger.h"
namespace PuReEngine
{
    namespace Core
    {
        // **************************************************************************
        // **************************************************************************
        CApplication::CApplication(IPlatform* a_pm_pPlatform, SApplicationDescription& a_rDescription)
        {
            this->m_Quit = false;
            this->m_pDescription = &a_rDescription;
            this->m_pPlatform = a_pm_pPlatform;
            CLogger::StartLogging();
        }

        CApplication::~CApplication()
        {
            CLogger::EndLogging();
        }
        // **************************************************************************
        // **************************************************************************
        void CApplication::Run(IScene* a_pScene)
        {
            CThreadManager& ThreadManager = CThreadManager::GetInstance();

            this->m_pSignalHandler = this->m_pPlatform->PlatformCreateSignalHandler();
            if (this->m_pSignalHandler == nullptr)
            {
                CLogger::Log("SignalHandler could not be initialized!", ELogType::LogError);
            }
            else
            {
                CLogger::Log("SignalHandler initialized!", ELogType::LogEngine);
            }
            // Create main Window
            this->m_pWindow = this->m_pPlatform->PlatformCreateWindow(this->m_pDescription->Window);
            if (this->m_pWindow == nullptr)
            {
                CLogger::Log("Window could not be initialized!", ELogType::LogError);
            }
            else
            {
                CLogger::Log("Window initialized!", ELogType::LogEngine);
            }
            this->m_pWindow->Show();

            // Create graphics module
            this->m_pGraphics = this->m_pPlatform->PlatformCreateGraphics(this->m_pWindow, this->m_pDescription->Graphics);
            if (this->m_pGraphics == nullptr)
            {
                CLogger::Log("Graphics could not be initialized!", ELogType::LogError);
            }
            else
            {
                CLogger::Log("Graphics initialized!", ELogType::LogEngine);
            }

            // Create input module
            this->m_pInput = this->m_pPlatform->PlatformCreateInput(this->m_pWindow);
            if (this->m_pInput == nullptr)
            {
                CLogger::Log("Input could not be initialized!", ELogType::LogError);
            }
            else
            {
                CLogger::Log("Input initialized!", ELogType::LogEngine);
            }
            //Set Cursor Lock
            if (this->m_pDescription->Window.LockCursor)
                this->m_pInput->LockCursor();
            else
                this->m_pInput->UnLockCursor();

            //start Time
            this->m_pTimer = new CTimer();
            if (this->m_pTimer == nullptr)
            {
                CLogger::Log("Timer could not be initialized!", ELogType::LogError);
            }
            else
            {
                CLogger::Log("Timer initialized!", ELogType::LogEngine);
            }
            this->m_pTimer->SetDeltaTime(this->m_pDescription->DeltaTime);

            //start Sound
            this->m_pSoundPlayer = new CSoundPlayer();
            if (this->m_pSoundPlayer == nullptr)
            {
                CLogger::Log("SoundPlayer could not be initialized!", ELogType::LogError);
            }
            else
            {
                CLogger::Log("SoundPlayer initialized!", ELogType::LogEngine);
            }

            a_pScene->Initialize(const_cast<CApplication*>(this));

            float32 accumulator = 0.0f;
            float32 dt = 0.0f;

            while (!this->m_Quit)
            {
                CLogger::Log("----------------", ELogType::LogPerformance);
                CLogger::Log("Start of Loop", ELogType::LogPerformance);

                //Check if Window Settings have been changed
                CLogger::Log("Start Window Update", ELogType::LogPerformance);
                this->m_pWindow->Update();
                CLogger::Log("End Window Update", ELogType::LogPerformance);

                //update Input
                CLogger::Log("Start Input Update", ELogType::LogPerformance);
                this->m_pInput->Update();
                CLogger::Log("End Input Update", ELogType::LogPerformance);

                this->m_Quit = this->m_pInput->CheckQuit();
                if (this->m_Quit)
                {
                    break;
                }

                CLogger::Log("Start Timer Update", ELogType::LogPerformance);
                this->m_pTimer->Update();
                CLogger::Log("End Timer Update", ELogType::LogPerformance);

                CLogger::Log("Start Sound Update", ELogType::LogPerformance);
                this->m_pSoundPlayer->Update();
                CLogger::Log("End Sound Update", ELogType::LogPerformance);

                accumulator += this->m_pTimer->GetElapsedSeconds();
                dt = this->m_pTimer->GetDeltaTime();

                while (accumulator >= dt)
                {
                    CLogger::Log("Start Scene Update", ELogType::LogPerformance);
                    this->m_Quit = a_pScene->Update(const_cast<CApplication*>(this)) == 0;
                    CLogger::Log("End Scene Update", ELogType::LogPerformance);

                    accumulator -= dt;
                }
                if (this->m_Quit)
                {
                    break;
                }

                this->m_pTimer->CalculateFPS();
                CLogger::Log("Start Scene Render", ELogType::LogPerformance);
                a_pScene->Render(const_cast<CApplication*>(this));
                CLogger::Log("End Scene Render", ELogType::LogPerformance);

                CLogger::Log("End of Loop", ELogType::LogPerformance);
            }

            a_pScene->Exit();

            SAFE_DELETE(this->m_pSoundPlayer);
            SAFE_DELETE(this->m_pSignalHandler);
            SAFE_DELETE(this->m_pTimer);
            SAFE_DELETE(this->m_pInput);
            SAFE_DELETE(this->m_pGraphics);
            SAFE_DELETE(this->m_pWindow);

        }

        // **************************************************************************
        // **************************************************************************
        IInput* CApplication::GetInput()
        {
            return this->m_pInput;
        }

        // **************************************************************************
        // **************************************************************************
        CSoundPlayer* CApplication::GetSoundPlayer()
        {
            return this->m_pSoundPlayer;
        }

        // **************************************************************************
        // **************************************************************************
        CTimer* CApplication::GetTimer()
        {
            return this->m_pTimer;
        }

        // **************************************************************************
        // **************************************************************************
        IWindow* CApplication::GetWindow()
        {
            return this->m_pWindow;
        }

        // **************************************************************************
        // **************************************************************************
        IGraphics* CApplication::GetGraphics()
        {
            return this->m_pGraphics;
        }

        // **************************************************************************
        // **************************************************************************
        IPlatform* CApplication::GetPlatform()
        {
            return this->m_pPlatform;
        }

    }
}
