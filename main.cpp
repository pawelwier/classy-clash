#include <raylib.h>
#include <raymath.h>

int main()
{
    const int dimensions[2]{768, 768};
    InitWindow(dimensions[0], dimensions[1], "Classy clash");

    Texture2D map = LoadTexture("nature_tileset/map.png");
    Vector2 mapPos{0.0, 0.0};
    float speed{6.0};

    Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knightRunning = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight{};
    float knightScale{4.};
    float KnightWidth{(float)knightIdle.width / 6.f};
    float KnightHeight{(float)knightIdle.height};

    float rightLeft{1.f};

    float runningTime{};
    const float updateTime{1.f / 12.f};
    int frame;
    const int maxFrames{6};

    Vector2 knightPos{
        dimensions[0] / 2.f - 0.5f * knightScale * KnightWidth,
        dimensions[1] / 2.f - 0.5f * knightScale * KnightHeight};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);
        Vector2 direction{};

        if (IsKeyDown(KEY_A))
            direction.x -= 1;
        if (IsKeyDown(KEY_D))
            direction.x += 1;
        if (IsKeyDown(KEY_W))
            direction.y -= 1;
        if (IsKeyDown(KEY_S))
            direction.y += 1;

        bool isMoving{Vector2Length(direction) != 0.0};

        if (isMoving)
        {
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1 : rightLeft = 1;
            knight = knightRunning;
        }
        else
            knight = knightIdle;

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        runningTime += dT;
        if (runningTime >= updateTime)
        {
            frame > maxFrames ? frame = 0 : frame++;
            runningTime = 0;
        }

        Rectangle knightSource{KnightWidth * frame, 0.f, rightLeft * KnightWidth, KnightHeight};
        Rectangle knightDest{knightPos.x, knightPos.y, knightScale * KnightWidth, knightScale * KnightHeight};
        DrawTexturePro(knight, knightSource, knightDest, Vector2{}, 0.0, WHITE);

        EndDrawing();
    }
    UnloadTexture(map);
    UnloadTexture(knight);
}
