#include "stdafx.h"
#include "structures.h"
#include "detours.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        FILE* file;
		AllocConsole(); 
		SetConsoleTitle("IW4xDLL");
		freopen_s(&file, "CONOUT$", "w", stdout);
		
        InsertDetour(&GameData::Com_PrintMessage, 
            GameData::Com_PrintMessageDetour);
        InsertDetour(&GameData::Menu_PaintAll, GameData::Menu_PaintAllDetour);
        InsertDetour(&GameData::CG_DrawNightVisionOverlay,
            GameData::CG_DrawNightVisionOverlayDetour);
        break;
	case DLL_PROCESS_DETACH:
		FreeConsole();

        std::vector<QWORD>::iterator it = detours.begin();
        while (it != detours.end())
        {    
            RemoveDetour(*it);
            it = detours.erase(it);
        }
		break;
    }
    return TRUE;
}

