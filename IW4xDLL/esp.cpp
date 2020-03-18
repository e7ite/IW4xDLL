#include "stdafx.h"
#include "esp.h"

void DrawBorderBox(float head[2], float foot[2], const float *color)
{
    float boxHeight = (foot[1] - head[1]);
    float boxWidth = boxHeight / 2.2f;
    float x = (foot[0] - (boxWidth / 2));
    float y = foot[1] - boxHeight;
    void* material = GameData::Material_RegisterHandle("white", 0);
    GameData::ScreenPlacement* scrPlace = GameData::ScrPlace_GetActivePlacement(0);
    
    GameData::CG_DrawRotatedPicPhysical(scrPlace,
        x, y, boxWidth, 1, 0, color, material); //top
    GameData::CG_DrawRotatedPicPhysical(scrPlace,
        x, foot[1], boxWidth, 1, 0, color, material); //bottom
    GameData::CG_DrawRotatedPicPhysical(scrPlace,
        x, y, 1, boxHeight, 0, color, material); //left
    GameData::CG_DrawRotatedPicPhysical(scrPlace,
        foot[0] + boxWidth / 2, y, 1, boxHeight, 0, color, material); //right
}
