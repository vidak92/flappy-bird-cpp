#ifndef FLAPPY_BIRD_CPP_GAME_H
#define FLAPPY_BIRD_CPP_GAME_H

#include <string>

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
    Sprite upSpriteTop;
    Sprite upSpriteMid;
    Sprite downSpriteTop;
    Sprite downSpriteMid;
};

struct Game
{
    void Init();
    void Start();
    void Update();
    void Draw();
    void Cleanup();

private:
    GameState _state;
    int _score;

    Sprite _backgroundSpriteTop;
    Sprite _backgroundSpriteBottom;
    Texture2D _backgroundTextureTop;
    Texture2D _backgroundTextureBottom;

    Player _player;

    Texture2D _groundTextureTop;
    Texture2D _groundTextureMid;
    float _groundOffsetX;
    Sprite _groundSpriteTop;
    Sprite _groundSpriteMid;

    static const int PIPE_PAIR_COUNT = 5;
    PipePair _pipePairs[PIPE_PAIR_COUNT];
    int _lastPipePairIndex;
    int _nextPipePairIndex;
    Texture2D _pipeTextureTop;
    Texture2D _pipeTextureMid;

    Texture2D _buttonTexture;
    Font _font;

    void InitGroundSprite(Sprite *sprite, Texture2D *texture, float positionY);
    void SpawnPipePair(int i, float offsetX);

    void DrawText(const char *text, float fontSize, Vector2 centerPosition);
    void DrawPanelBackground(Rectangle rect);
    void DrawPanelText(std::string string, float fontSize, Rectangle panelRect, float offsetY);
    void DrawScoreText();
    void DrawStartPanel();
    void DrawGameOverPanel();
};

#endif //FLAPPY_BIRD_CPP_GAME_H