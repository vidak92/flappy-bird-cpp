#include "Game.h"
#include <format>
#include <iostream>
#include "Config.h"
#include "Utils.h"

void Game::Init()
{
    InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "Flappy Bird");
    SetTargetFPS(Config::TARGET_FPS);
    _state = NONE;

    _player.Init();

    _groundTextureTop = LoadTexture("../res/terrain_grass_block_top.png");
    SetTextureWrap(_groundTextureTop, TEXTURE_WRAP_REPEAT);
    float groundPositionYTop = (float)Config::SCREEN_HEIGHT - Config::GROUND_HEIGHT;
    InitGroundSprite(&_groundSpriteTop, &_groundTextureTop, groundPositionYTop);

    _groundTextureMid = LoadTexture("../res/terrain_grass_block_center.png");
    SetTextureWrap(_groundTextureMid, TEXTURE_WRAP_REPEAT);
    float groundPositionYMid = _groundSpriteTop.position.y + _groundSpriteTop.size.y;
    InitGroundSprite(&_groundSpriteMid, &_groundTextureMid, groundPositionYMid);

    _pipeTextureTop = LoadTexture("../res/terrain_dirt_vertical_top.png");
    _pipeTextureMid = LoadTexture("../res/terrain_dirt_vertical_middle.png");
    SetTextureWrap(_pipeTextureMid, TEXTURE_WRAP_REPEAT);

    _backgroundTextureBottom = LoadTexture("../res/background_fade_hills.png");
    _backgroundSpriteBottom.position = Vector2 { 0.0f, Config::SCREEN_HEIGHT - Config::GROUND_HEIGHT - Config::SCREEN_WIDTH };
    _backgroundSpriteBottom.size = Vector2 { (float)Config::SCREEN_WIDTH, (float)Config::SCREEN_WIDTH };
    _backgroundSpriteBottom.SetTexture(&_backgroundTextureBottom);

    _backgroundTextureTop = LoadTexture("../res/background_clouds.png");
    _backgroundSpriteTop.position = Vector2 { 0.0f, _backgroundSpriteBottom.position.y - Config::SCREEN_WIDTH };
    _backgroundSpriteTop.size = Vector2 { (float)Config::SCREEN_WIDTH, (float)Config::SCREEN_WIDTH };
    _backgroundSpriteTop.SetTexture(&_backgroundTextureTop);

    _buttonTexture = LoadTexture("../res/button_square_depth_flat.png");
    _font = LoadFontEx("../res/Kenney Future.ttf", 48, 0, 250);
}

void Game::Start()
{
    _state = NONE;
    _score = 0;

    _player.Start();

    _groundOffsetX = 0.0f;

    _lastPipePairIndex = 0;
    _nextPipePairIndex = 0;
    for (int i = 0; i < PIPE_PAIR_COUNT; i++)
    {
        float initialOffsetX = i == 0 ? (float)Config::SCREEN_WIDTH / 2.0f : 0.0f;
        SpawnPipePair(i, initialOffsetX);
    }
}

void Game::Update()
{
    float dt = GetFrameTime();

    // debug options
    if (IsKeyPressed(KEY_GRAVE))
    {
        Config::DEBUG_DRAW_ENABLED = !Config::DEBUG_DRAW_ENABLED;
    }

    bool jumpInput = IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE);
    switch (_state)
    {
        case NONE:
        {
            if (jumpInput)
            {
                _state = STARTED;
                _player.Update(jumpInput, true); // jump immediately
            }
            break;
        }
        case STARTED:
        {
            _player.Update(jumpInput, true);
            if (_player.IsOutOfBounds())
            {
                _state = OVER;
            }

            _groundOffsetX += Config::SCROLL_SPEED * dt;

            for (int i = 0; i < PIPE_PAIR_COUNT; ++i)
            {
                _pipePairs[i].upRect.x -= Config::PIPE_SPEED * dt;
                _pipePairs[i].downRect.x -= Config::PIPE_SPEED * dt;
                _pipePairs[i].upSpriteTop.position.x = _pipePairs[i].downRect.x;
                _pipePairs[i].upSpriteMid.position.x = _pipePairs[i].downRect.x;
                _pipePairs[i].downSpriteTop.position.x = _pipePairs[i].downRect.x;
                _pipePairs[i].downSpriteMid.position.x = _pipePairs[i].downRect.x;

                if (_pipePairs[i].upRect.x < -Config::PIPE_COLLIDER_WIDTH)
                {
                    // respawn
                    SpawnPipePair(i, 0);
                }
                else if (
                    CheckCollisionCircleRec(_player.position, Config::PLAYER_COLLIDER_RADIUS, _pipePairs[i].upRect) ||
                    CheckCollisionCircleRec(_player.position, Config::PLAYER_COLLIDER_RADIUS, _pipePairs[i].downRect))
                {
                    _state = OVER;
                    break;
                }
            }

            if (_pipePairs[_nextPipePairIndex].upRect.x + Config::PIPE_COLLIDER_WIDTH / 2.0f < _player.position.x)
            {
                _score++;
                std::cout << "score: " << _score << "\n";

                _nextPipePairIndex++;
                if (_nextPipePairIndex >= PIPE_PAIR_COUNT)
                {
                    _nextPipePairIndex -= PIPE_PAIR_COUNT;
                }
            }
            break;
        }
        case OVER:
        {
            _player.Update(false, false);

            if (IsKeyPressed(KEY_R))
            {
                // restart
                for (int i = 0; i < PIPE_PAIR_COUNT; i++)
                {
                    // reset position
                    _pipePairs[i].upRect = Rectangle {};
                    _pipePairs[i].downRect = Rectangle {};
                }
                Start();
            }
            break;
        }
    }

}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground(DARKGRAY);

    // gameplay
    _backgroundSpriteBottom.Draw();
    _backgroundSpriteTop.Draw();

    for (int i = 0; i < PIPE_PAIR_COUNT; ++i)
    {
        _pipePairs[i].upSpriteTop.Draw();
        _pipePairs[i].upSpriteMid.Draw();
        _pipePairs[i].downSpriteTop.Draw();
        _pipePairs[i].downSpriteMid.Draw();

        if (Config::DEBUG_DRAW_ENABLED)
        {
            DrawRectangleLinesEx(_pipePairs[i].upRect, 1.0f, MAGENTA);
            DrawRectangleLinesEx(_pipePairs[i].downRect, 1.0f, MAGENTA);
        }
    }

    _groundSpriteTop.tilingOffset.x = _groundOffsetX;
    _groundSpriteTop.Draw();

    _groundSpriteMid.tilingOffset.x = _groundOffsetX;
    _groundSpriteMid.Draw();

    if (Config::DEBUG_DRAW_ENABLED)
    {
        DrawRectangleLines(
            0,
            Config::SCREEN_HEIGHT - Config::GROUND_HEIGHT,
            Config::SCREEN_WIDTH,
            Config::GROUND_HEIGHT, MAGENTA);
    }

    _player.Draw();

    // ui
    switch (_state)
    {
        case NONE:
        {
            DrawStartPanel();
            break;
        }
        case STARTED:
        {
            DrawScoreText();
            break;
        }
        case OVER:
        {
            DrawGameOverPanel();
            break;
        }
    }

    std::string versionText = std::format("v{}", Config::APP_VERSION);
    Vector2 versionTextPosition { 10.0f, (float)Config::SCREEN_HEIGHT - 24.0f };
    DrawTextEx(_font, versionText.c_str(), versionTextPosition, 18, 1, WHITE);

    EndDrawing();
}

void Game::Cleanup()
{
    _player.Cleanup();
    UnloadTexture(_groundTextureTop);
    UnloadTexture(_groundTextureMid);
    UnloadTexture(_pipeTextureTop);
    UnloadTexture(_pipeTextureMid);
    UnloadTexture(_backgroundTextureBottom);
    UnloadTexture(_backgroundTextureTop);
    UnloadTexture(_buttonTexture);
    UnloadFont(_font);
}

void Game::InitGroundSprite(Sprite* sprite, Texture2D* texture, float positionY)
{
    sprite->size = Vector2 { (float)Config::SCREEN_WIDTH, (float)texture->height };
    sprite->position = Vector2 { 0.0f, positionY };
    sprite->SetTexture(texture);
    sprite->tilingSize.x = (float)Config::SCREEN_WIDTH;;
}

void Game::SpawnPipePair(int i, float offsetX)
{
    float lastPipePairPosX = _pipePairs[_lastPipePairIndex].upRect.x;
    float x = lastPipePairPosX + Config::PIPE_COLLIDER_WIDTH + Config::PIPE_GAP_SIZE_X + offsetX;

    float gapPosY = Utils::RandomRange(Config::PIPE_GAP_POS_Y_MIN, Config::PIPE_GAP_POS_Y_MAX);
    float pipeGapSizeY = Utils::RandomRange(Config::PIPE_GAP_SIZE_Y_MIN, Config::PIPE_GAP_SIZE_Y_MAX);
    float upY = gapPosY - pipeGapSizeY / 2.0f;
    float downY = gapPosY + pipeGapSizeY / 2.0f;

    _pipePairs[i].upRect = Rectangle { x, 0, Config::PIPE_COLLIDER_WIDTH, upY };
    _pipePairs[i].downRect = Rectangle { x, downY, Config::PIPE_COLLIDER_WIDTH, Config::SCREEN_HEIGHT - Config::GROUND_HEIGHT - upY };

    _pipePairs[i].downSpriteTop.size = Vector2 { Config::PIPE_SPRITE_WIDTH, Config::PIPE_SPRITE_WIDTH };
    _pipePairs[i].downSpriteTop.position = Vector2 { x, _pipePairs[i].downRect.y };
    _pipePairs[i].downSpriteTop.SetTexture(&_pipeTextureTop);

    _pipePairs[i].downSpriteMid.size = Vector2 { Config::PIPE_SPRITE_WIDTH, _pipePairs[i].downRect.height - Config::PIPE_SPRITE_WIDTH };
    _pipePairs[i].downSpriteMid.position = Vector2 { x, _pipePairs[i].downRect.y + Config::PIPE_SPRITE_WIDTH };
    _pipePairs[i].downSpriteMid.SetTexture(&_pipeTextureMid);
    _pipePairs[i].downSpriteMid.tilingSize.y = _pipePairs[i].downSpriteMid.size.y;

    _pipePairs[i].upSpriteTop.size = Vector2 { Config::PIPE_SPRITE_WIDTH, Config::PIPE_SPRITE_WIDTH };
    _pipePairs[i].upSpriteTop.position = Vector2 { x, _pipePairs[i].upRect.y + _pipePairs[i].upRect.height - Config::PIPE_SPRITE_WIDTH};
    _pipePairs[i].upSpriteTop.flipY = true;
    _pipePairs[i].upSpriteTop.SetTexture(&_pipeTextureTop);

    _pipePairs[i].upSpriteMid.size = Vector2 { Config::PIPE_SPRITE_WIDTH, _pipePairs[i].upRect.height - Config::PIPE_SPRITE_WIDTH };
    _pipePairs[i].upSpriteMid.position = Vector2{x, _pipePairs[i].upRect.y};
    _pipePairs[i].upSpriteMid.flipY = true;
    _pipePairs[i].upSpriteMid.SetTexture(&_pipeTextureMid);
    _pipePairs[i].upSpriteMid.tilingSize.y = -_pipePairs[i].upSpriteMid.size.y;

    _lastPipePairIndex = i;
}

void Game::DrawText(const char* text, float fontSize, Vector2 centerPosition)
{
    Vector2 textSize = MeasureTextEx(_font, text, fontSize, 1);
    Vector2 textPosition { centerPosition.x - textSize.x / 2.0f, centerPosition.y - textSize.y / 2.0f };
    DrawTextEx(_font, text, textPosition, fontSize, 1, DARKGRAY);

    if (Config::DEBUG_DRAW_ENABLED)
    {
        DrawRectangleLinesEx({ textPosition.x, textPosition.y, textSize.x, textSize.y }, 1.0f, MAGENTA);
    }
}

void Game::DrawPanelBackground(Rectangle rect)
{
    Rectangle buttonSrcRect { 0.0f, 0.0f, (float)_buttonTexture.width, (float)_buttonTexture.height };
    NPatchInfo nPatchInfo {  buttonSrcRect, 8, 8, 8, 8, NPATCH_NINE_PATCH };
    DrawTextureNPatch(_buttonTexture, nPatchInfo, rect, {}, 0, WHITE);
}

void Game::DrawPanelText(std::string string, float fontSize, Rectangle panelRect, float offsetY)
{
    const char* text = string.c_str();
    Vector2 textCenterPosition { panelRect.x + panelRect.width / 2.0f, panelRect.y + offsetY };
    DrawText(text, fontSize, textCenterPosition);
}

void Game::DrawScoreText()
{
    std::string scoreString = std::to_string(_score);
    const char* scoreText = scoreString.c_str();
    Vector2 scoreTextCenterPosition { Config::SCREEN_WIDTH / 2.0f, 32.0f };
    DrawText(scoreText, 48, scoreTextCenterPosition);
}

void Game::DrawStartPanel()
{
    Vector2 panelSize { Config::SCREEN_WIDTH - 100.0f, 200.0f };
    Vector2 panelPosition { Config::SCREEN_WIDTH / 2.0f - panelSize.x / 2.0f, Config::SCREEN_HEIGHT / 2.0f - panelSize.y / 2.0f };
    Rectangle panelRect { panelPosition.x, panelPosition.y, panelSize.x, panelSize.y };
    DrawPanelBackground(panelRect);

    std::string startString = "Press 'SPACE'\nor 'UP ARROW'\nto start";
    DrawPanelText(startString, 32, panelRect, 100.0f);
}

void Game::DrawGameOverPanel()
{
    Vector2 panelSize { Config::SCREEN_WIDTH - 100.0f, 280.0f };
    Vector2 panelPosition { Config::SCREEN_WIDTH / 2.0f - panelSize.x / 2.0f, Config::SCREEN_HEIGHT / 2.0f - panelSize.y / 2.0f };
    Rectangle panelRect { panelPosition.x, panelPosition.y, panelSize.x, panelSize.y };
    DrawPanelBackground(panelRect);

    std::string gameOverScoreString = std::format("Score: {}", _score);
    std::string gameOverRestartString = std::format("Press 'R' to\nrestart", _score);

    DrawPanelText("Game Over", 48, panelRect, 50.0f);
    DrawPanelText(gameOverScoreString, 32, panelRect, 130.0f);
    DrawPanelText(gameOverRestartString, 32, panelRect, 210.0f);
}

