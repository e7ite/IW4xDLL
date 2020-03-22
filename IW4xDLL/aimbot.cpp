#pragma once

#include "stdafx.h"
#include "aimbot.h"

Aimbot& Aimbot::GetInstance()
{
    static Aimbot aimbot;
    return aimbot;
}

int Aimbot::GetTarget()
{
    int result;
    GameData::EnterCriticalSection(&this->critSection);
    result = this->target;
    GameData::LeaveCriticalSection(&this->critSection);
    return result;
}

int Aimbot::SetTarget(int target)
{
    GameData::EnterCriticalSection(&this->critSection);
    this->target = target;
    GameData::LeaveCriticalSection(&this->critSection);
    return target;
}

vec3_t Aimbot::GetAngles()
{
    vec3_t result;
    GameData::EnterCriticalSection(&this->critSection);
    result = this->targetAngles;
    GameData::LeaveCriticalSection(&this->critSection);
    return result;
}

void Aimbot::SetAngles(const vec3_t& angles)
{
    GameData::EnterCriticalSection(&this->critSection);
    this->targetAngles = angles;
    GameData::LeaveCriticalSection(&this->critSection);
}

int Aimbot::FindTarget()
{
    float closestDistance = 99999999.0f;
    int closestTarget = -1;

    for (int i = 0; i < 18; i++)
    {
        GameData::centity_s* cent = &GameData::cg_entitiesArray[i];

        if (i != GameData::cgameGlob->clientNum
            && cent->pose.eType
            && GameData::AimTarget_IsTargetVisible(0,
                GameData::SL_FindString("j_head", 0), cent))
        {
            float distance 
                = GameData::Vec3DistanceSq(GameData::cg_entitiesArray[
                                    GameData::cgameGlob->clientNum
                                ].pose.origin,
                                cent->pose.origin);
            if (distance < closestDistance)
            {
                closestDistance = distance;
                closestTarget = i;
            }
        }
    }

    return closestTarget;
}

float Aimbot::DegreesToRadians(float degrees)
{
    return degrees * 3.14f / 180.0f;
}

void Aimbot::FixMovement(GameData::usercmd_s *cmd, float currentAngle, float oldAngle,
    float oldForwardmove, float oldRightmove)
{
    float deltaView = currentAngle - oldAngle, f1, f2;

    if (oldAngle < 0.f)
        f1 = 360.0f + oldAngle;
    else
        f1 = oldAngle;

    if (currentAngle < 0.0f)
        f2 = 360.0f + currentAngle;
    else
        f2 = currentAngle;

    if (f2 < f1)
        deltaView = abs(f2 - f1);
    else
        deltaView = 360.0f - abs(f1 - f2);

    deltaView = 360.0f - deltaView;

    float deltaRad = DegreesToRadians(deltaView);
    float rightDeltaRad = DegreesToRadians(deltaView + 90.f);
    cmd->forwardmove = GameData::ClampChar(
        int(GameData::__libm_sse2_cos(deltaRad) * oldForwardmove 
            + GameData::__libm_sse2_cos(rightDeltaRad) * oldRightmove
        ));
    cmd->rightmove = GameData::ClampChar(
        int(GameData::__libm_sse2_sin(deltaRad) * oldForwardmove 
            + GameData::__libm_sse2_sin(rightDeltaRad) * oldRightmove
        ));
}
