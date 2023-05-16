#include "Character.h"
#include "Prop.h"
#include "raylib.h"
#include "raymath.h"

int main()
{
    const int dimensions[2]{710, 710};
    InitWindow(dimensions[0], dimensions[1], "Classy clash");

    Texture2D map = LoadTexture("nature_tileset/map.png");
    Vector2 mapPos{0.0, 0.0};
    float mapScale{4.f};

    Character knight{dimensions[0], dimensions[1]};

    Texture2D rockTexture = LoadTexture("nature_tileset/Rock.png");
    Texture2D logTexture = LoadTexture("nature_tileset/Log.png");
    Prop rock{rockTexture, Vector2{400.f, 290.f}};

    Prop props[2]{
        Prop{rockTexture, Vector2{400.f, 290.f}},
        Prop{logTexture, Vector2{600.f, 440.f}},
    };
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        for (Prop prop : props)
        {
            prop.render(knight.getWorldPos());
        };

        knight.tick(GetFrameTime());
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x > map.width * mapScale - dimensions[0] ||
            knight.getWorldPos().y > map.height * mapScale - dimensions[1])
        {
            knight.undoMovement();
        }

        for (Prop prop : props)
        {
            if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        };

        EndDrawing();
    }
    UnloadTexture(map);
    UnloadTexture(knight.getTexture());
}
