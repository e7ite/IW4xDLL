#pragma once

#include "structures.h"

class Aimbot
{
private:
    _RTL_CRITICAL_SECTION critSection;
    vec3_t                targetAngles;
    int                   target = -1;

public:
    Aimbot() { GameData::InitializeCriticalSection(&this->critSection); }

    static Aimbot& GetInstance();
    int FindTarget();
    int GetTarget();
    vec3_t GetAngles();
    void SetAngles(const vec3_t& angles);
    int SetTarget(int target);
    float DegreesToRadians(float degrees);
    void FixMovement(GameData::usercmd_s *cmd, float currentAngle, float oldAngle,
        float oldForwardmove, float oldRightmove);
};
