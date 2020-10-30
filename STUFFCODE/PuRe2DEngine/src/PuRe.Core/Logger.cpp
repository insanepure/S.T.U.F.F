#include "include/PuReEngine/Logger.h"
#include <time.h>
#include <cstdio>
#include <chrono>

#define Time std::chrono::high_resolution_clock::time_point
#define Time_Now std::chrono::high_resolution_clock::now()
#define Time_Diff std::chrono::duration<int64, std::nano>
#define Convert_Time(x) std::chrono::duration_cast<std::chrono::duration<int64, std::milli>>(x).count()

namespace PuReEngine
{
    namespace Core
    {
        static const char* LOGFILE = "LOG.txt";
        static int LogType;
        static FILE* File;
        static Time LastUpdateTime;

        void CLogger::StartLogging()
        {
            fopen_s(&File, LOGFILE, "w");
        }
        void CLogger::EndLogging()
        {
            fclose(File);
        }

        void CLogger::SetLogging(int a_LogType)
        {
            LogType = a_LogType;
        }

        void CLogger::Log(std::string Text, ELogType a_LogType)
        {
            if (!(LogType & a_LogType))
            {
                return;
            }
            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            localtime_s(&tstruct, &now);

            strftime(buf, sizeof(buf), "[%d.%m.%Y %X]", &tstruct);

            std::string outText = "";
            switch (a_LogType)
            {
            case LogWarning:
                outText = "[WARNING]: ";
                break;
            case LogError:
                outText = "[ERROR]: ";
                break;
            case LogEngine:
                outText = "[ENGINE]: ";
                break;
            case LogGame:
                outText = "[GAME]: ";
                break;
            case LogPerformance:
                auto currentTime = std::chrono::steady_clock::now();
                auto elapsed = Time_Now - LastUpdateTime;
                LastUpdateTime = currentTime;
                int64 secondsTook =  Convert_Time(elapsed);

                outText = "[PERFORMANCE][" + std::to_string(secondsTook) + "]: ";
                break;
            }
            outText = buf + outText + Text + "\n";

            fwrite(outText.c_str(), sizeof(char), outText.size(), File);
        }
    }
}