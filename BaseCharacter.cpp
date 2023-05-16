#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame > maxFrames ? frame = 0 : frame++;
        runningTime = 0;
    }

    Rectangle source{width * frame, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0, WHITE);
}