#include "stdafx.h"
#include "detours.h"

namespace GameData
{
    void(__cdecl *CG_DrawNightVisionOverlay)(int localClientNum)
        = (void(__cdecl*)(int))CG_DrawNightVisionOverlay_a;
    void(__cdecl *Menu_PaintAll)(UiContext *dc)
        = (void(__cdecl*)(UiContext*))Menu_PaintAll_a;
    void(__cdecl *CL_WritePacket)(int localClientNum) 
        = (void(__cdecl*)(int))CL_WritePacket_a;

    void CG_DrawNightVisionOverlayDetour(int localClientNum)
    {
        Aimbot& aimbot = Aimbot::GetInstance();

        int target = aimbot.SetTarget(aimbot.FindTarget());
        if (target != -1)
        {
            vec3_t out;
            AimTarget_GetTagPos(*(WORD*)0x1AA2E04, &cg_entitiesArray[target], out);
            aimbot.SetAngles(out);
            
            vectoangles(out - cgameGlob->refdef.vieworg, out);
            out -= clientActive->delta_angles;

            aimbot.SetAngles(out);
            //*(vec3_t*)clientActive->viewangles = out;
        }

        for (int i = 0; i < 18; i++)
        {
            if (i != cgameGlob->clientNum && GameData::cg_entitiesArray[i].pose.eType)
            {
                float headOrigin[3];
                float headScreen[2], feetScreen[2];
                unsigned bone = SL_FindString("j_head", 0);
                ScreenPlacement *scrPlace = ScrPlace_GetActivePlacement(0);

                AimTarget_GetTagPos(bone, &cg_entitiesArray[i], headOrigin);

                CG_WorldPosToScreenPosReal(0, scrPlace, headOrigin, headScreen);
                CG_WorldPosToScreenPosReal(0, scrPlace, cg_entitiesArray[i].pose.origin,
                        feetScreen);

                DrawBorderBox(headScreen, feetScreen, 
                    AimTarget_IsTargetVisible(0, bone, &cg_entitiesArray[i])
                        ? Color(255, 0, 0) : Color(0, 0, 255));
            }
        }

        CG_DrawNightVisionOverlay(localClientNum);
    }

    void Menu_PaintAllDetour(UiContext *dc)
    {
        Menu_PaintAll(dc);
    }

    void CL_WritePacketDetour(int localClientNum)
    {
        Aimbot& aimbot = Aimbot::GetInstance();
        usercmd_s *ocmd = &clientActive->cmds[clientActive->cmdNumber - 1 & 0x7F];
        usercmd_s *ccmd = &clientActive->cmds[clientActive->cmdNumber & 0x7F];

        *ocmd = *ccmd;
        ocmd->serverTime--;

        int target = aimbot.GetTarget();
        vec3_t targetAngles = aimbot.GetAngles();
        float oldAngle = ocmd->angles[1];
        if (target != -1)
        {
            for (int i = 0; i < 2; i++)
                ocmd->angles[i]
                    = (int)(targetAngles[i]
                        * 182.0444488525391f + 0.5f - 0.4999999990686774f) & 0xFFFF;

            ocmd->button_bits |= 1;
            ccmd->button_bits &= ~1;
        }

        // aimbot.FixMovement(ocmd, )
        
        CL_WritePacket(localClientNum);
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
