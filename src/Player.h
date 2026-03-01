#ifndef FLAPPY_BIRD_CPP_PLAYER_H
#define FLAPPY_BIRD_CPP_PLAYER_H

#include "raylib.h"
#include "Sprite.h"

struct Player
{
    void Init();
    void Start();
    void Update(bool shouldJump);
    void Draw();
    void Cleanup();
    bool IsOutOfBounds();

    Vector2 position;
    float velocityY;

    Sprite sprite;

private:
    Texture2D _texture1;
    Texture2D _texture2;
    float _animationTimer;
};

#endif //FLAPPY_BIRD_CPP_PLAYER_H