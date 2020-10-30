#include <PuReEngine/Platform.h>
#include <PuReEngine/Core.h>
// Application specific includes
#include "include/MainScene.h"



int32 PURE_MAIN
{
    //Memory Leak detection
    //static unsigned int breakId = 4777;
    //_CrtSetBreakAlloc(breakId);
    PuRe_IPlatform* pplatform = PuRe_CreatePlatform();
    PuRe_ApplicationDescription description;
    description.Graphics.ResolutionWidth = 2560;
    description.Graphics.ResolutionHeight = 1440;
    description.Graphics.Module = PuRe_GraphicsModuleType::OpenGL;
    description.Window.Title = "S.T.U.F.F";
    description.Window.Width = 1440;
    description.Window.Height = 720;
    description.Window.X = 0;
    description.Window.Y = 0;
    description.Window.LockCursor = false;
    description.Window.ShowCursor = true;
    description.Window.CursorInWindow = false;
    description.DeltaTime = 1 / 60.0f;

#ifdef _DEBUG
    PuRe_Logger::SetLogging(PuRe_LogType::LogError | PuRe_LogType::LogWarning | PuRe_LogType::LogEngine);
#endif

    PuRe_Application* papplication = new PuRe_Application(pplatform, description);
    Game::CMainScene scene(papplication);

    papplication->Run(&scene);

    SAFE_DELETE(papplication);
    SAFE_DELETE(pplatform);
    //Print memory leak in output
    //_CrtDumpMemoryLeaks();
}
