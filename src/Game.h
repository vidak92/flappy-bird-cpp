#ifndef FLAPPY_BIRD_CPP_GAME_H
#define FLAPPY_BIRD_CPP_GAME_H

#include "Player.h"
#include "raylib.h"

enum GameState
{
    NONE,
    STARTED,
    OVER
};

struct PipePair
{
    Rectangle upRect;
    Rectangle downRect;
    float gapSize;
};

struct Game
{
    void Init();
    void Start();
    void Update();
    void Draw();
    void Cleanup();
    void InitGroundSprite(Sprite *sprite, Texture2D *texture, float positionY);

private:
    GameState _state;
    int _score;

    Player _player;

    Texture2D _groundTextureTop;
    Texture2D _groundTextureBottom;
    float _groundOffsetX;
    Sprite _groundSpriteTop;
    Sprite _groundSpriteBottom;
};

#endif //FLAPPY_BIRD_CPP_GAME_H