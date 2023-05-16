#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character(int windowWidth, int windowHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
    screenPos = {
        static_cast<float>(windowWidth) / 2.f - 0.5f * scale * width,
        static_cast<float>(windowHeight) / 2.f - 0.5f * scale * height
    };
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);

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
};
