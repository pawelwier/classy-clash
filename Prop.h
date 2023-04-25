#include "raylib.h"

class Prop 
{
public:
    Prop(Texture2D tex, Vector2 pos);
    void render(Vector2 knightPos);
private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};
};