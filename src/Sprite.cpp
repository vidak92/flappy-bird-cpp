#include "Sprite.h"

void Sprite::SetTexture(Texture2D *tex)
{
    texture = tex;
    tilingSize.x = (float)texture->width * (flipX ? -1.0f : 1.0f);
    tilingSize.y = (float)texture->height * (flipY ? -1.0f : 1.0f);
    tilingOffset = {};
}

void Sprite::Draw()
{
    Rectangle srcRect { tilingOffset.x, tilingOffset.y, tilingSize.x, tilingSize.y };
    Rectangle dstRect { position.x, position.y, size.x, size.y };
    Vector2 origin { size.x * anchor.x, size.y * anchor.y };
    DrawTexturePro(*texture, srcRect, dstRect, origin, rotation, WHITE);
}
