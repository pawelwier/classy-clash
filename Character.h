#include "raylib.h"

class Character
{
    public:
        Character(int windowWidth, int windowHeight);
        Vector2 getWorldPos() { return worldPos; }
        Texture2D getTexture() { return texture; }
        void tick(float deltaTime);
        void undoMovement();

    private:
        Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
        Vector2 screenPos{};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{};
        float width{};
        float height{};
        float rightLeft{1.f};
        float runningTime{};
        float updateTime{1.f / 12.f};
        int frame{};
        int maxFrames{6};
        float speed{6.f};
        float scale{4.f};
};