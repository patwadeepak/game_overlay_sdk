#ifndef MONITOR
#define MONITOR

#define _WIN32_DCOM

#include <windows.h>

#include <logger\spdlog.h>

class Monitor
{
    public:
        static std::shared_ptr<spdlog::logger> monitorLogger;
        static void SetLogLevel (int level);

        Monitor (char *processName, char *dllLoc);
        ~Monitor ();

        bool StartMonitor ();
        bool StopMonitor ();
        void Callback (int pid, char *pName);

    private:
        volatile HANDLE thread;
        volatile HANDLE createEvent;
        volatile HANDLE stopEvent;
        volatile char processName[1024];
        volatile char dllLoc[1024];

        bool RegisterCreationCallback ();
        static DWORD WINAPI ThreadProc (LPVOID lpParameter);
        void WorkerThread ();
        int GetArchitecture (int pid);

};

#endif