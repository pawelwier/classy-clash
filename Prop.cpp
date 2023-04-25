#include "Prop.h"
#include "raymath.h"

Prop::Prop(Texture2D tex, Vector2 pos) :
    texture(tex),
    worldPos(pos)
{

};

void Prop::render(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);

    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}