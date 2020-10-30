#include "include/PuReEngine/ThreadManager.h"

namespace PuReEngine
{
    namespace Core
    {
        // **************************************************************************
        // **************************************************************************
        CThreadManager::CThreadManager()
        {
            this->m_End = false;
            uint32 threadAmount = std::thread::hardware_concurrency() - 1;
            for (uint32 i = 0; i < threadAmount; ++i)
            {
                std::thread* newThread = new std::thread(&CThreadManager::DoJob, this);
                this->m_Threads.push_back(newThread);
            }
        }

        // **************************************************************************
        // **************************************************************************

        CThreadManager::~CThreadManager()
        {
            this->m_End = true;

            this->m_Jobs = 0;

            m_Mutex.lock();
            this->m_PendingJobs.empty();
            m_Mutex.unlock();

            while (this->m_Threads.size() != 0)
            {
                std::thread* thread = this->m_Threads.front();
                this->m_Threads.pop_front();
                thread->join();
                delete thread;
            }
        }

        // **************************************************************************
        // **************************************************************************

        void CThreadManager::AddJob(std::function<void()> Job)
        {
            m_PendingJobs.push(Job);
            m_Jobs++;
        }

        // **************************************************************************
        // **************************************************************************

        void CThreadManager::DoJob(CThreadManager* a_pSelf)
        {
            //Thread's "Loop".
            while (!a_pSelf->m_End)
            {
                if (!a_pSelf->GetJob())
                    std::this_thread::yield(); //we have nothing to do, wait until there is work to do
            }
        }
        
        bool CThreadManager::GetJob()
        {
            //if there are still jobs to do
            if (m_Jobs > 0)
            {
                if (--m_Jobs < 0)
                {
                    m_Jobs++;
                    return false;
                }

                m_Mutex.lock();
                std::function<void()> ProcessJob = m_PendingJobs.front();
                m_PendingJobs.pop();
                m_Mutex.unlock();

                ProcessJob();
                return true;
            }

            return false;
        }

    }
}