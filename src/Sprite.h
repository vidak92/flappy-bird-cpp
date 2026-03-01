#ifndef FLAPPY_BIRD_CPP_SPRITE_H
#define FLAPPY_BIRD_CPP_SPRITE_H
#include "raylib.h"

struct Sprite
{
    Vector2 position {};
    Vector2 size {};

    float rotation = 0;
    bool flipX = false;
    bool flipY = false;
    Vector2 anchor {};
    Vector2 tilingOffset {};
    Vector2 tilingSize {};

    Texture2D *texture = nullptr;

    void SetTexture(Texture2D *texture);
    void Draw();
    Rectangle GetDefaultSrcTextureRect();
    bool ShouldUseDefaultSrcTextureRect();
};

#endif //FLAPPY_BIRD_CPP_SPRITE_H