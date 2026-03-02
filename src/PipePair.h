#ifndef FLAPPY_BIRD_CPP_PIPEPAIR_H
#define FLAPPY_BIRD_CPP_PIPEPAIR_H
#include "raylib.h"
#include "Sprite.h"

struct PipePair
{
    Rectangle upRect;
    Rectangle downRect;
    float gapSize;
    Sprite upSpriteTop;
    Sprite upSpriteMid;
    Sprite downSpriteTop;
    Sprite downSpriteMid;

    void Spawn(float positionX, float upY, float downY, Texture2D* textureTop, Texture2D* textureMid);
    void MovePositionX(float offsetX);
    void Draw();
};

#endif //FLAPPY_BIRD_CPP_PIPEPAIR_H