#include "stdafx.h"
#include "detours.h"
#include "aimbot.h"
#include "esp.h"

namespace GameData
{
    void(__cdecl* CG_DrawNightVisionOverlay)(int localClientNum)
        = (void(__cdecl*)(int))CG_DrawNightVisionOverlay_a;
    void(__cdecl* Com_PrintMessage)(int channel, const char* msg, int error)
        = (void(__cdecl*)(int, const char*, int))Com_PrintMessage_a;
    void(__cdecl* Menu_PaintAll)(UiContext* dc)
        = (void(__cdecl*)(UiContext*))Menu_PaintAll_a;

    void CG_DrawNightVisionOverlayDetour(int localClientNum)
    {
        int target = Aimbot::GetTarget();
        if (target != -1)
        {
            float out[3];

            AimTarget_GetTagPos(*(WORD*)0x1AA2E04, &cg_entitiesArray[target], out);
            out[0] -= cgameGlob->refdef.vieworg[0];
            out[1] -= cgameGlob->refdef.vieworg[1];
            out[2] -= cgameGlob->refdef.vieworg[2];

            vectoangles(out, out);
            out[0] -= clientActive->delta_angles[0];
            out[1] -= clientActive->delta_angles[1];
            out[2] -= clientActive->delta_angles[2];

            clientActive->viewangles[0] = out[0];
            clientActive->viewangles[1] = out[1];
            clientActive->viewangles[2] = out[2];
        }

        for (int i = 0; i < 18; i++)
        {
            if (i != cgameGlob->clientNum && GameData::cg_entitiesArray[i].pose.eType)
            {
                float headOrigin[3];
                float headScreen[2], feetScreen[2];
                unsigned bone = GameData::SL_FindString("j_head", 0);
                GameData::AimTarget_GetTagPos(bone,
                    &GameData::cg_entitiesArray[i],
                    headOrigin);
                GameData::CG_WorldPosToScreenPosReal(0,
                    GameData::ScrPlace_GetActivePlacement(0), headOrigin, headScreen);
                    
                GameData::CG_WorldPosToScreenPosReal(0,
                    GameData::ScrPlace_GetActivePlacement(0),
                    GameData::cg_entitiesArray[i].pose.origin,
                        feetScreen);

                DrawBorderBox(headScreen, feetScreen, 
                    AimTarget_IsTargetVisible(0, bone, &GameData::cg_entitiesArray[i])
                        ? Color(255, 0, 0) : Color(0, 0, 255));
            }
        }

        CG_DrawNightVisionOverlay(localClientNum);
    }

    void Com_PrintMessageDetour(int channel, const char* msg, int error)
    {
        Com_PrintMessage(channel, msg, error);
    }

    void Menu_PaintAllDetour(UiContext* dc)
    {
        Menu_PaintAll(dc);
    }
}

void RemoveDetour(QWORD bytes)
{
    /* Split the 8 bytes into their 4 respective bytes to remove them */
    DWORD targetFunction = (bytes & ((QWORD)UINT_MAX << 32)) >> 32;
    DWORD detourFunction = bytes & UINT_MAX;

    /* Initiate detour transcation API */
    DetourTransactionBegin();

    /* Enlists current thread in transaction to appropriately update
       instruction pointers for that thread */
    DetourUpdateThread(GetCurrentThread());

    /* Deallocates the detour for the target function */
    DetourDetach((PVOID*)targetFunction, (PVOID*)detourFunction);

    /* Restores overwritten instructions of target function
       and restores target function pointer to point to original
       function */
    DetourTransactionCommit();
}

void InsertDetour(LPVOID targetFunction, LPVOID detourFunction)
{
    /* Use a vector of 8 bytes which contain the
       the target function in most significant 4 bytes
       and the detour function in least significant 4 bytes */
    detours.push_back(((QWORD)targetFunction << 32) | (QWORD)detourFunction);

    /* Initiate Detour Transcation API */
    DetourTransactionBegin();

    /* Enlists Current Thread in Transaction to Appropriately Update
       Instruction Pointers for That Thread */
    DetourUpdateThread(GetCurrentThread());

    /* Allocates the Detour for the Target Function */
    DetourAttach((PVOID*)targetFunction, (PVOID*)detourFunction);

    /* Overwrites the first instruction in the target function to jmp
       to Detour before returning to target function to restore program flow */
    DetourTransactionCommit();
}
