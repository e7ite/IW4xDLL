#pragma once

#include "structures.h"
#include "detours.h"
#include "aimbot.h"
#include "esp.h"

namespace GameData
{
    enum DetourAddresses : DWORD
    {
        CG_DrawNightVisionOverlay_a                 = 0x415660,
        Menu_PaintAll_a                             = 0x4EDF60,
        CL_WritePacket_a                            = 0x411900,
    };

    extern void(__cdecl *CG_DrawNightVisionOverlay)(int localClientNum);
    extern void(__cdecl *Menu_PaintAll)(UiContext *dc);
    extern void(__cdecl *CL_WritePacket)(int localClientNum);

    void CG_DrawNightVisionOverlayDetour(int localClientNum);
    void Menu_PaintAllDetour(UiContext *dc);
    void CL_WritePacketDetour(int localClientNum);
}

void RemoveDetour(QWORD bytes);
void InsertDetour(LPVOID targetFunction, LPVOID detourFunction);
