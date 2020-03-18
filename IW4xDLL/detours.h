#pragma once

#include "structures.h"

namespace GameData
{
    enum DetourAddresses : DWORD
    {
        CG_DrawNightVisionOverlay_a                 = 0x415660,
        Com_PrintMessage_a                          = 0x4AA830,
        Menu_PaintAll_a                             = 0x4EDF60,
    };

    extern void(__cdecl* CG_DrawNightVisionOverlay)(int localClientNum);
    extern void(__cdecl* Com_PrintMessage)(int channel, const char* msg, int error);
    extern void(__cdecl* Menu_PaintAll)(UiContext* dc);

    void CG_DrawNightVisionOverlayDetour(int localClientNum);
    void Com_PrintMessageDetour(int channel, const char* msg, int error);
    void Menu_PaintAllDetour(UiContext* dc);
}

void RemoveDetour(QWORD bytes);
void InsertDetour(LPVOID targetFunction, LPVOID detourFunction);
