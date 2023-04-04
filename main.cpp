#include <raylib.h>
#include <raymath.h>

class Character
{
    public:
        Vector2 getWorldPos() { return worldPos; }
        Texture2D getTexture() { return texture; }
        void setScreenPos(int windowWidth, int windowHeight);
        void tick(float deltaTime);
    private:
        Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
        Vector2 screenPos{};
        Vector2 worldPos{};
        float rightLeft{1.f};
        float runningTime{};
        const float updateTime{1.f / 12.f};
        int frame{};
        const int maxFrames{6};
        const float speed{4.f};
        const float knightScale{4.f};
};

    void Character::setScreenPos(int windowWidth, int windowHeight)
    {
        screenPos = {
            (float)windowWidth / 2.f - 0.5f * knightScale * texture.width / 6.f,
            (float)windowHeight / 2.f - 0.5f * knightScale * texture.height
        };
    };

    void Character::tick(float deltaTime)
    {
        Vector2 direction{};

        if (IsKeyDown(KEY_A)) direction.x -= 1;
        if (IsKeyDown(KEY_D)) direction.x += 1;
        if (IsKeyDown(KEY_W)) direction.y -= 1;
        if (IsKeyDown(KEY_S)) direction.y += 1;

        bool isMoving{Vector2Length(direction) != 0.0};

        if (isMoving)
        {
            worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1 : rightLeft = 1;
            texture = run;
        }
        else
            texture = idle;

        runningTime += deltaTime;
        if (runningTime >= updateTime)
        {
            frame > maxFrames ? frame = 0 : frame++;
            runningTime = 0;
        }

        Rectangle knightSource{(float)texture.width * frame / 6.f, 0.f, rightLeft * texture.width / 6.f, float(texture.height)};
        Rectangle knightDest{screenPos.x, screenPos.y, knightScale * texture.width / 6.f, knightScale * texture.height};
        DrawTexturePro(texture, knightSource, knightDest, Vector2{}, 0.0, WHITE);
    };

int main()
{
    const int dimensions[2]{768, 768};
    InitWindow(dimensions[0], dimensions[1], "Classy clash");

    Texture2D map = LoadTexture("nature_tileset/map.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight;

    knight.setScreenPos(dimensions[0], dimensions[1]);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(map);
    UnloadTexture(knight.getTexture());
}
