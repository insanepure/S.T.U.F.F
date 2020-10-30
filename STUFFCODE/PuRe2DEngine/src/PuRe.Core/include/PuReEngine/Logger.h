#ifndef _LOGGGER_H_
#define _LOGGGER_H_
// Engine specific includes
#include "Defines.h"
#include <string>

namespace PuReEngine
{
    namespace Core
    {
        enum ELogType
        {
            LogWarning = (1 << 0),
            LogError = (1 << 1),
            LogPerformance = (1 << 2),
            LogEngine = (1 << 3),
            LogGame = (1 << 4)
        };
        /// @brief Logger to write to a File
        ///
        class CLogger
        {
        public:
            static void StartLogging();
            static void Log(std::string Text, ELogType LogType);
            static void SetLogging(int LogType);
            static void EndLogging();
        };
    }
}
#endif /* _LOGGGER_H_ */