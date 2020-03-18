#include "stdafx.h"
#include "structures.h"

namespace GameData
{
    cg_s*           cgameGlob        = (cg_s*)0x7F0F78;
    centity_s*      cg_entitiesArray = (centity_s*)0x8F3CA8;
    clientActive_t* clientActive     = (clientActive_t*)0xB2C698;
    HWND*           hwnd             = (HWND*)0x64A3AD0;

    void(__cdecl* vectoangles)(const float* vec, float* angles)
        = (void(__cdecl*)(const float*, float*))vectoangles_a;
    bool(__cdecl* CG_WorldPosToScreenPosReal)(int localClientNum,
        ScreenPlacement* scrPlace, const float* worldPos, float *out)
        = (bool(__cdecl*)(int, ScreenPlacement*,
            const float*, float*))CG_WorldPosToScreenPosReal_a;
    void*(__cdecl* Material_RegisterHandle)(const char* name, int imageTrack)
        = (void*(__cdecl*)(const char*, int))Material_RegisterHandle_a;
    void(__cdecl* CG_DrawRotatedPicPhysical)(ScreenPlacement* scrPlace, float x,
        float y, float width, float height, float angle, const float* color, void* material)
        = (void(__cdecl*)(ScreenPlacement*, float, float, float, float, float,
            const float*, void*))CG_DrawRotatedPicPhysical_a;
    ScreenPlacement*(__cdecl* ScrPlace_GetActivePlacement)(int localClientNum)
        = (ScreenPlacement*(__cdecl*)(int))ScrPlace_GetActivePlacement_a;
    int(__cdecl* SL_FindString)(const char* str, int inst) = (int(_cdecl*)(
        const char*, int))SL_FindString_a;
    float(__cdecl* Vec3DistanceSq)(const float* p1, const float* p2)
        = (float(__cdecl*)(const float*, const float*))Vec3DistanceSq_a;

    void AimTarget_GetTagPos(unsigned int tagname, centity_s* cent, float *pos)
    {
        DWORD addr = AimTarget_GetTagPos_a;
        __asm
        {
            mov         edi, tagname
            mov         esi, cent
            push        pos
            call        addr
            add         esp, 4
        }
    }

    void CG_BulletEndpos(int randSeed, const float spread, const float* start,
        float* end, float* dir, const float* forwardDir, const float* rightDir, 
        const float* upDir, const float maxRange)
    {
        DWORD addr = CG_BulletEndpos_a;
        __asm
        {
            mov         esi, randSeed
            mov         ebx, start
            mov         edi, end
            push        maxRange
            push        upDir
            push        rightDir
            push        forwardDir
            push        dir
            push        spread
            call        addr
            add         esp, 18h
        }
    }

    bool AimTarget_IsTargetVisible(int localClientNum, int tagName, centity_s* cent)
    {
        DWORD addr = AimTarget_IsTargetVisible_a;
        bool result;
        __asm
        {
            mov         eax, tagName
            mov         ecx, cent
            push        localClientNum
            call        addr
            add         esp, 4
            mov         result, al    
        }
        return result;
    }
}

std::vector<QWORD> detours;
Font normalFont;
bool dvarsInitialized;

bool CopyTextToClipboard(const std::string &text)
{
    HGLOBAL hg;
    bool state = false;
    size_t len = text.size();

    if (!OpenClipboard(*GameData::hwnd))
        return false;
    if (!EmptyClipboard())
        return false;

    hg = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    if (!hg)
    {
        state = false;
        goto end;
    }
    memcpy(static_cast<LPSTR>(GlobalLock(hg)), text.c_str(), len);
    GlobalUnlock(hg);
    state = SetClipboardData(CF_TEXT, hg);

end:
    CloseClipboard();
    GlobalFree(hg);
    return state;
}
