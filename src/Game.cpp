#include "Game.h"
#include "Config.h"

void Game::Init()
{
    InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "Flappy Bird");
    SetTargetFPS(Config::TARGET_FPS);
    _state = NONE;

    _player.Init();

    _groundTextureTop = LoadTexture("../res/terrain_dirt_block_top.png");
    float groundPositionYTop = (float)Config::SCREEN_HEIGHT - Config::GROUND_HEIGHT;
    InitGroundSprite(&_groundSpriteTop, &_groundTextureTop, groundPositionYTop);

    _groundTextureBottom = LoadTexture("../res/terrain_dirt_block_center.png");
    float groundPositionYBottom = _groundSpriteTop.position.y + _groundSpriteTop.size.y;
    InitGroundSprite(&_groundSpriteBottom, &_groundTextureBottom, groundPositionYBottom);
}

void Game::Start()
{
    _state = NONE;
    _score = 0;

    _player.Start();
    _groundOffsetX = 0.0f;
}

void Game::Update()
{
    float dt = GetFrameTime();

    // debug options
    if (IsKeyPressed(KEY_GRAVE))
    {
        Config::DEBUG_DRAW_ENABLED = !Config::DEBUG_DRAW_ENABLED;
    }
    if (IsKeyPressed(KEY_R))
    {
        Start();
    }

    bool jumpInput = IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE);
    switch (_state)
    {
        case NONE:
        {
            if (jumpInput)
            {
                _state = STARTED;
                _player.Update(jumpInput); // jump immediately
            }
            break;
        }
        case STARTED:
        {
            _groundOffsetX += Config::SCROLL_SPEED * dt;

            _player.Update(jumpInput);
            if (_player.IsOutOfBounds())
            {
                _state = OVER;
            }
            break;
        }
        case OVER:
        {
            break;
        }
    }

}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground(DARKGRAY);

    // ground
    _groundSpriteTop.tilingOffset.x = _groundOffsetX;
    _groundSpriteTop.Draw();

    _groundSpriteBottom.tilingOffset.x = _groundOffsetX;
    _groundSpriteBottom.Draw();

    if (Config::DEBUG_DRAW_ENABLED)
    {
        DrawRectangleLines(
            0,
            Config::SCREEN_HEIGHT - Config::GROUND_HEIGHT,
            Config::SCREEN_WIDTH,
            Config::GROUND_HEIGHT,
            WHITE);
    }

    _player.Draw();

    EndDrawing();
}

void Game::Cleanup()
{
    _player.Cleanup();
    UnloadTexture(_groundTextureTop);
    UnloadTexture(_groundTextureBottom);
}

void Game::InitGroundSprite(Sprite* sprite, Texture2D* texture, float positionY) {
    sprite->size = Vector2 { (float)Config::SCREEN_WIDTH, (float)texture->height };
    sprite->position = Vector2 { 0.0f, positionY };
    sprite->SetTexture(texture);
    sprite->tilingSize = Vector2 { (float)Config::SCREEN_WIDTH, (float)texture->height };
}
