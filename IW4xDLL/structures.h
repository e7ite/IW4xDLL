#pragma once

#include "stdafx.h"

using QWORD = unsigned __int64;

#pragma pack(push, 1)
namespace GameData
{
    struct UiContext
    {
        int contentIndex;                               // 0x00
    };

    struct ScreenPlacement
    {
        float scaleVirtualToReal[2];                    // 0x000
        float scaleVirtualToFull[2];                    // 0x008
        float scaleRealToVirtual[2];                    // 0x010
        float virtualViewableMin[2];                    // 0x018
        float virtualViewableMax[2];                    // 0x020
        float virtualTweakableMin[2];                   // 0x028
        float virtualTweakableMax[2];                   // 0x030
        float realViewportBase[2];                      // 0x038
        float realViewportSize[2];                      // 0x040
        float realViewportMid[2];                       // 0x048
        float realViewableMin[2];                       // 0x050
        float realViewableMax[2];                       // 0x058
        float realTweakableMin[2];                      // 0x060
        float realTweakableMax[2];                      // 0x068
        float subScreen[2];                             // 0x070
    }; // Size = 0x78

    struct refdef_s
    {
        unsigned int x;                                 // 0x00
        unsigned int y;                                 // 0x04
        unsigned int width;                             // 0x08
        unsigned int height;                            // 0x0C
        float        tanHalfFovX;                       // 0x10
        float        tanHalfFovY;                       // 0x14
        float        vieworg[3];                        // 0x18
        float        viewaxis[3][3];                    // 0x24
        char         pad00[0x3F48];                     // 0x48
    }; //Size = 0x3F90

    struct entityState_s
    {
        int  number;                                    // 0x00
        int  eType;                                     // 0x04
        int  eFlags;                                    // 0x08
        char pad00[0xC0];                               // 0x0C
        int  weapon;                                    // 0xCC
    }; //Size = 0xD0

    struct clientInfo_t
    {
        int  infoValid;                                 // 0x000
        int  nextValid;                                 // 0x004
        int  clientNum;                                 // 0x008
        char name[0x10];                                // 0x00C
        int  team;                                      // 0x01C
        int  oldteam;                                   // 0x020
        int  ffaTeam;                                   // 0x024
        char pad00[0x18];                               // 0x028
        char model[0x40];                               // 0x040
        char attachModelNames[6][0x40];                 // 0x080
        char attachTagNames[6][0x40];                   // 0x200
        char pad01[0x1AC];                              // 0x380
    }; //Size = 0x52C

    struct clientState_s
    {
        int clientIndex;                                // 0x00
    };

    struct snapshot_s
    {
        int           snapFlags;                        // 0x00000
        int           ping;                             // 0x00004
        int           serverTime;                       // 0x00008
        int           physicsTime;                      // 0x0000C
        char          pad00[0x33120];                   // 0x00010
        clientState_s clients[32];                      // 0x33130
    };

    struct cg_s
    {
        int          serverTime;                        // 0x00000
        char         pad00[0x5C];                       // 0x00004
        float        delta_angles[3];                   // 0x00060
        char         pad01[0x94];                       // 0x0006C
        float        viewangles[3];                     // 0x00100
        char         pad02[0x1B8];                      // 0x0010C
        float        aimSpreadScale;                    // 0x002C4
        char         pad03[0x3088];                     // 0x002C8
        int          clientNum;                         // 0x03350
        char         pad04[0x1C];                       // 0x03354
        snapshot_s  *snap;                              // 0x03370
        snapshot_s  *nextSnap;                          // 0x03374
        char         pad05[0x673E0];                    // 0x03378        
        int          time;                              // 0x6A758
        char         pad06[0x1C];                       // 0x6A75C
        refdef_s     refdef;                            // 0x6A778
        float        refdefViewAngles;                  // 0x6E708
        char         pad07[0x48F8];                     // 0x6E70C
        int          weaponSelect;                      // 0x73004
        char         pad08[0x83830];                    // 0x73008
        clientInfo_t clients[0x12];                     // 0xF6838
    };

    struct playerState_s
    {
        int   commandTime;                              // 0x0000
        int   pm_type;                                  // 0x0004
        int   bobCycle;                                 // 0x0008
        int   pm_flags;                                 // 0x000C
        int   otherFlags;                               // 0x0010
        int   pm_time;                                  // 0x0014
        char  pad00[0x4];                               // 0x0018
        float origin[3];                                // 0x001C
    }; // Size = 0x28

    struct cpose_t
    {
        unsigned short lightingHandle;                  // 0x00
        char           eType;                           // 0x02
        char           eTypeUnion;                      // 0x03
        char           pad00[0x14];                     // 0x04
        float          origin[3];                       // 0x18
    }; // Size = 0x24

    struct centity_s
    {
        cpose_t       pose;                             // 0x000
        char          pad00[0xB8];                      // 0x024
        entityState_s nextState;                        // 0x0DC
        char          pad01[0x58];                      // 0x1AC
    }; // Size = 0x204

    struct usercmd_s
    {
        int            serverTime;                      // 0x00
        int            button_bits;                     // 0x04
        int            angles[3];                       // 0x08
        unsigned short weapon;                          // 0x14
        unsigned short offHandIndex;                    // 0x16
        char           pad00[0x2];                      // 0x18
        char           forwardmove;                     // 0x1A
        char           rightmove;                       // 0x1B
        char           pad01[0x5];                      // 0x1C
        char           selectedLocation[2];             // 0x21
        char           selectedYaw;                     // 0x23
        char           pad02[0x4];                      // 0x24
    }; // Size = 0x28

    struct clientActive_t
    {
        char      pad00[0x68];                          // 0x0000
        float     delta_angles[3];                      // 0x0068
        char      pad01[0x31A8];                        // 0x0074
        float     cgameViewangles[3];                   // 0x321C
        char      pad02[0x10];                          // 0x3228
        float     viewangles[3];                        // 0x3238
        usercmd_s cmds[0x80];                           // 0x3244
        int       cmdNumber;                            // 0x4644
    };

    struct WeaponVariantDef
    {
        const char *szInternalName;                     // 0x0000
    };

    struct WeaponDef
    {
        const char *szOverlayName;                      // 0x0000
    };

    struct hudelem_s
    {
        int   active;
        float x;
        float y;
        float z;
    }; // Size = 0xA8

    // Game structures
    extern cg_s           *cgameGlob;
    extern centity_s      *cg_entitiesArray;
    extern clientActive_t *clientActive;
    extern HWND           *hwnd;

    // Math functions
    extern void(__cdecl *vectoangles)(const float *vec, float *angles);
    extern float(__cdecl *Vec3DistanceSq)(const float *p1, const float *p2);
    extern bool(__cdecl *CG_WorldPosToScreenPosReal)(int localClientNum,
        ScreenPlacement *scrPlace, const float *worldPos, float *out);
    extern void(__cdecl *AngleVectors)(const float *angles, float *forward,
        float *right, float *up);
    extern float(__cdecl *__libm_sse2_sin)(float x);
    extern float(__cdecl *__libm_sse2_cos)(float x);
    extern float(__cdecl *__libm_sse2_tan)(float x);

    // Shader functions
    extern void*(__cdecl *Material_RegisterHandle)(const char *name, int imageTrack);
    extern void(__cdecl *CG_DrawRotatedPicPhysical)(ScreenPlacement *scrPlace, float x,
        float y, float width, float height, float angle, const float *color, void *material);
    extern ScreenPlacement*(__cdecl *ScrPlace_GetActivePlacement)(int localClientNum);
    
    // Weapon functions
    extern WeaponVariantDef*(__cdecl *BG_GetWeaponVariantDef)(int weaponIndex);
    extern WeaponDef*(__cdecl *BG_GetWeaponDef)(int weaponIndex);
    
    // Miscellaneous functions
    extern int(__cdecl *SL_FindString)(const char *str, int inst);
    extern char*(__cdecl *va)(const char *fmt, ...);
    extern char(__cdecl *ClampChar)(signed int i);

    // Concurrency functions
    extern void(__stdcall *InitializeCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
    extern void(__stdcall *EnterCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
    extern void(__stdcall *LeaveCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
    
    void AimTarget_GetTagPos(unsigned int tagname, centity_s *cent, float *pos);
    void CG_BulletEndpos(int randSeed, const float spread, const float *start,
        float *end, float *dir, const float *forwardDir, const float *rightDir,
        const float *upDir, const float maxRange);
    bool AimTarget_IsTargetVisible(int localClientNum, int tagName, centity_s *cent);

    enum FuncAddresses
    {
        UI_DrawText_a                               = 0x49C0D0,
        UI_GetFontHandle_a                          = 0x4AEA60,
        ScrPlace_GetActivePlacement_a               = 0x4F8940,
        AimTarget_GetTagPos_a                       = 0x56A020,
        Com_GetClientDObj_a                         = 0x41FF50,
        BG_GetWeaponVariantDef_a                    = 0x44CE00,
        BG_GetWeaponDef_a                           = 0x440EB0,
        vectoangles_a                               = 0x4B5B50,
        CG_WorldPosToScreenPosReal_a                = 0x502F20,
        CG_BulletEndpos_a                           = 0x59D320,
        Material_RegisterHandle_a                   = 0x505E60,
        CG_DrawRotatedPicPhysical_a                 = 0x4E9500,
        SL_FindString_a                             = 0x4CDC10,
        Vec3DistanceSq_a                            = 0x4C1380,
        __libm_sse2_sin_a                           = 0x6B55D0,
        __libm_sse2_cos_a                           = 0x6B54A0,
        __libm_sse2_tan_a                           = 0x6B4A90,
        AimTarget_IsTargetVisible_a                 = 0x56AEC0,
        AngleVectors_a                              = 0x4691A0,
        Sys_Milliseconds_a                          = 0x42A660,
        va_a                                        = 0x4785B0,
        ClampChar_a                                 = 0x4439A0,
        CL_GetUserCmd_a                             = 0x434B10,
        InitializeCriticalSection_a                 = 0x6D7200,
        EnterCriticalSection_a                      = 0x6D7204,
        LeaveCriticalSection_a                      = 0x6D7208,
    };
}

struct vec3_t
{
    union
    {
        struct { float x, y, z; };
        struct { float pitch, yaw, roll; };
    };

    vec3_t(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : x(x), y(y), z(z) {}
    vec3_t(float *vec) { memcpy(this, vec, 0xC); }
    vec3_t(const vec3_t &vec) { memcpy(this, &vec, 0xC); }

    operator float*() { return (float*)this; }
    operator const float*() const { return (const float*)this; }

    vec3_t operator+(const vec3_t &vec) const;
    vec3_t operator+(float vec[3]) const;
    vec3_t operator-(const vec3_t &vec) const;
    vec3_t operator-(float vec[3]) const;
    vec3_t operator*(const vec3_t &vec) const;
    vec3_t operator*(float vec[3]) const;
    vec3_t& operator+=(const vec3_t &vec);
    vec3_t& operator+=(float vec[3]);
    vec3_t& operator-=(const vec3_t &vec);
    vec3_t& operator-=(float vec[3]);
    vec3_t& operator*=(const vec3_t &vec);
    vec3_t& operator*=(float vec[3]);
};

struct Font
{
    int index;
    const char *dir;
};

struct Color
{
    float r, g, b, a;

    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 255.0f)
        : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}
        
    operator float*() { return (float*)this; }
};

extern Font normalFont;
extern std::vector<QWORD> detours;
extern bool dvarsInitialized;
extern std::unordered_map<std::string, _RTL_CRITICAL_SECTION> critSections;

bool CopyTextToClipboard(const std::string &text);

#pragma pack(push, 1)