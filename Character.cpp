#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth),
    windowHeight(winWidth)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

void Character::tick(float deltaTime)
{
    if (IsKeyDown(KEY_A)) velocity.x -= 1;
    if (IsKeyDown(KEY_D)) velocity.x += 1;
    if (IsKeyDown(KEY_W)) velocity.y -= 1;
    if (IsKeyDown(KEY_S)) velocity.y += 1;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    Rectangle weaponCollisionRec{};

    if (rightLeft > 0)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        rotation = 35.f;
        weaponCollisionRec = {
            getScreenPos().x + offset.x, 
            getScreenPos().y + offset.y - weapon.height * scale, 
            weapon.width * scale, 
            weapon.height * scale
        };
    }
    else 
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        rotation = -35.f;
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale, 
            getScreenPos().y + offset.y - weapon.height * scale, 
            weapon.width * scale, 
            weapon.height * scale
        };
    }

    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(
        weaponCollisionRec.x,
        weaponCollisionRec.y,
        weaponCollisionRec.width,
        weaponCollisionRec.height,
        RED
    );
};

Vector2 Character::getScreenPos()
{
    return {
        static_cast<float>(windowWidth) / 2.f - 0.5f * scale * width,
        static_cast<float>(windowHeight) / 2.f - 0.5f * scale * height
    };
}