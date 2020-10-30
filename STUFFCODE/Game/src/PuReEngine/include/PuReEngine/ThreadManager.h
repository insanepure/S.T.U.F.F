#ifndef _THREADMANAGER_H_
#define _THREADMANAGER_H_
// Engine specific includes
#include "Defines.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <functional>
#include <queue>
#include <list>

namespace PuReEngine
{
    namespace Core
    {
        /// @brief Manager that holds all Threads
        ///
        class CThreadManager
        {
        private:
            std::queue<std::function<void()>> m_PendingJobs;
            std::list<std::thread*> m_Threads;
            std::atomic<int32> m_Jobs;
            std::mutex m_Mutex;
            bool m_End;

        public:
            static CThreadManager& GetInstance()
            {
                static CThreadManager    instance; // Guaranteed to be destroyed.
                                      // Instantiated on first use.
                return instance;
            }

        public:
            void AddJob(std::function<void()> Job);
        private:
            /// @brief Creates an instance of ThreadManager.
            ///
            CThreadManager();

            /// @brief Destroyes an instance of ThreadManager.
            ///
            ~CThreadManager();

            static void DoJob(CThreadManager* a_pSelf);
            bool GetJob();
        };
    }
}

#endif /* _THREADMANAGER_H_ */