

#include "pch.h"
#include "initialization.h"

#include <MinHook.h>
#include <string>
#include "TlHelp32.h"

namespace hks
{
    uintptr_t baseAddress;

    void InitializeApi()
    {
        MH_Initialize();
        baseAddress = GetBaseAddress();
    }

    // Get the base address of the Black Ops 3 process, Thanks porter
    uintptr_t GetBaseAddress()
    {
        PROCESSENTRY32 Entry;
        Entry.dwSize = sizeof(PROCESSENTRY32);
        HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        if (Process32First(Snapshot, &Entry) == TRUE)
        {
            do
            {
                auto processName = std::wstring(Entry.szExeFile);
                if (processName == L"BlackOps3.exe")
                {
                    HANDLE Bo3Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Entry.th32ProcessID);
                    MODULEENTRY32 moduleData;
                    moduleData.dwSize = sizeof(MODULEENTRY32);
                    if (!Module32First(Bo3Snapshot, &moduleData))
                    {
                        CloseHandle(Bo3Snapshot);
                        return NULL;
                    }
                    uintptr_t MainModuleAddress = (uintptr_t)moduleData.modBaseAddr;
                    CloseHandle(Bo3Snapshot);

                    return MainModuleAddress;
                }

            } while (Process32Next(Snapshot, &Entry));
        }
        CloseHandle(Snapshot);

        return NULL;
    }
}

