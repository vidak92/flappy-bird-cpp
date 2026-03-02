#include "PipePair.h"
#include "Config.h"

void PipePair::Spawn(float positionX, float upY, float downY, Texture2D* textureTop, Texture2D* textureMid)
{
    upRect = Rectangle { positionX, 0, Config::PIPE_COLLIDER_WIDTH, upY };
    downRect = Rectangle { positionX, downY, Config::PIPE_COLLIDER_WIDTH, Config::SCREEN_HEIGHT - Config::GROUND_HEIGHT - upY };

    downSpriteTop.size = Vector2 { Config::PIPE_SPRITE_WIDTH, Config::PIPE_SPRITE_WIDTH };
    downSpriteTop.position = Vector2 { positionX, downRect.y };
    downSpriteTop.SetTexture(textureTop);

    downSpriteMid.size = Vector2 { Config::PIPE_SPRITE_WIDTH, downRect.height - Config::PIPE_SPRITE_WIDTH };
    downSpriteMid.position = Vector2 { positionX, downRect.y + Config::PIPE_SPRITE_WIDTH };
    downSpriteMid.SetTexture(textureMid);
    downSpriteMid.tilingSize.y = downSpriteMid.size.y;

    upSpriteTop.size = Vector2 { Config::PIPE_SPRITE_WIDTH, Config::PIPE_SPRITE_WIDTH };
    upSpriteTop.position = Vector2 { positionX, upRect.y + upRect.height - Config::PIPE_SPRITE_WIDTH};
    upSpriteTop.flipY = true;
    upSpriteTop.SetTexture(textureTop);

    upSpriteMid.size = Vector2 { Config::PIPE_SPRITE_WIDTH, upRect.height - Config::PIPE_SPRITE_WIDTH };
    upSpriteMid.position = Vector2{positionX, upRect.y};
    upSpriteMid.flipY = true;
    upSpriteMid.SetTexture(textureMid);
    upSpriteMid.tilingSize.y = -upSpriteMid.size.y;
}

void PipePair::MovePositionX(float offsetX)
{
    float positionX = upRect.x + offsetX;
    upRect.x = positionX;
    downRect.x = positionX;
    upSpriteTop.position.x = positionX;
    upSpriteMid.position.x = positionX;
    downSpriteTop.position.x = positionX;
    downSpriteMid.position.x = positionX;
}

void PipePair::Draw()
{
    upSpriteTop.Draw();
    upSpriteMid.Draw();
    downSpriteTop.Draw();
    downSpriteMid.Draw();

    if (Config::DEBUG_DRAW_ENABLED)
    {
        DrawRectangleLinesEx(upRect, 1.0f, MAGENTA);
        DrawRectangleLinesEx(downRect, 1.0f, MAGENTA);
    }
}
