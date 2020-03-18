#pragma once

#include "stdafx.h"
#include "aimbot.h"

namespace Aimbot
{
    int GetTarget()
    {
        float closestDistance = 99999999.0f;
        int closestTarget = -1;
        for (int i = 0; i < 18; i++)
        {
            GameData::clientInfo_t* ci = &GameData::cgameGlob->clients[i];
            GameData::centity_s* cent = &GameData::cg_entitiesArray[i];
            if (i != GameData::cgameGlob->clientNum 
                && cent->pose.eType 
                && GameData::AimTarget_IsTargetVisible(0, 
                    GameData::SL_FindString("j_head", 0),
                    cent))
                closestTarget = i;
        }
        return closestTarget;
    }
}
