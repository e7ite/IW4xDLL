#include "stdafx.h"

void WriteBytes(DWORD addr, const char *bytes, size_t len)
{
    DWORD curProtection;
    HANDLE curProcess = GetCurrentProcess();

    /* Make virtual page address have read/write/exec privledges
       and save old privledges to temporary */
    VirtualProtect((LPVOID)addr, len, PAGE_EXECUTE_READWRITE, &curProtection);

    WriteProcessMemory(curProcess, (LPVOID)addr, bytes, len, nullptr);

    // Restore old privledges from temporary to virtual page address
    VirtualProtect((LPVOID)addr, len, curProtection, nullptr);

    /* Run this to ensure instruction cache doesn't contain the instruction
       from the address you just modified, therefore running the same instruction
       you just removed */
    FlushInstructionCache(curProcess, (void*)addr, len);
}

void ReadBytes(DWORD addr, char* buf, size_t len)
{
    DWORD curProtection;
    VirtualProtect((LPVOID)addr, len, PAGE_EXECUTE_READWRITE, &curProtection);

    ReadProcessMemory(GetCurrentProcess(), (LPCVOID)addr, buf, len, 0);

    VirtualProtect((LPVOID)addr, len, curProtection, 0);
}
