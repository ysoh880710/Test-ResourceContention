#include <Windows.h>
#include <iostream>

#ifndef THREAD_COUNT
#define THREAD_COUNT (8ull)
#endif // !THREAD_COUNT

void* g_pThreads[THREAD_COUNT]{};
unsigned long g_pThreadIDs[THREAD_COUNT]{};

struct alignas(64ull) SThreadResource
{
    unsigned long long ullSharedValue;
    long long llLock;
    _RTL_CRITICAL_SECTION stCriticalSection;
};

SThreadResource g_pThreadResources[THREAD_COUNT]{};

using namespace std;

unsigned long __stdcall Thread(void* const _pParameter)
{
    const unsigned long long ullThreadIndex = reinterpret_cast<unsigned long long>(_pParameter);
    unsigned long long ullLocalValue = 0ull;

    while (true)
    {
        //// Non shared resource
        //++ullLocalValue;
        
        //// Shared resource
        //// Using lock (Interlock)
        //if (InterlockedCompareExchange64(&g_pThreadResources[ullThreadIndex].llLock, 1ll, 0ll) == 0ll)
        //{
        //    ++g_pThreadResources[ullThreadIndex].ullSharedValue;
        //    InterlockedExchange64(&g_pThreadResources[ullThreadIndex].llLock, 0ll);
        //}

        // Using critical section
        EnterCriticalSection(&g_pThreadResources[ullThreadIndex].stCriticalSection);
        ++g_pThreadResources[ullThreadIndex].ullSharedValue;
        LeaveCriticalSection(&g_pThreadResources[ullThreadIndex].stCriticalSection);
        
        // Using Mutex
    }

    return 0ul;
}

void CreateThreads()
{
    for (unsigned long long i = 0ull; i < THREAD_COUNT; ++i)
    {
        g_pThreads[i] = CreateThread(nullptr,
                                     0ull,
                                     &Thread,
                                     reinterpret_cast<void*>(i),
                                     0ul,
                                     &g_pThreadIDs[i]);
        if (g_pThreads[i] == nullptr)
        {
            // TODO : Rollback
        }
    }
}

int main()
{
    for (unsigned long long i = 0ull; i < THREAD_COUNT; ++i)
    {
        InitializeCriticalSection(&g_pThreadResources[i].stCriticalSection);
    }

    for (unsigned long long i = 0ull; i < THREAD_COUNT; ++i)
    {
        wcout << L"&g_pThreadResources[" << i << L"]\t" << &g_pThreadResources[i] << L"\t" << (reinterpret_cast<unsigned long long>(&g_pThreadResources[i]) / 64ull) << L"\t" << (reinterpret_cast<unsigned long long>(&g_pThreadResources[i]) % 64ull) << endl;
    }
    
    CreateThreads();

    Sleep(3000ul);

    for (unsigned long long i = 0ull; i < THREAD_COUNT; ++i)
    {
        DeleteCriticalSection(&g_pThreadResources[i].stCriticalSection);
    }

    sizeof(SThreadResource);

    return 0;
}