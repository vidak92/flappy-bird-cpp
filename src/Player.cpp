#include "Player.h"
#include "Config.h"
#include "raymath.h"

void Player::Init()
{
    _texture1 = LoadTexture("../res/bee_a.png");
    _texture2 = LoadTexture("../res/bee_b.png");
    _animationTimer = Config::PLAYER_ANIMATION_FRAME_DURATION;
}

void Player::Start()
{
    position = Config::PLAYER_START_POSITION;
    velocityY = 0;

    sprite.position = position;
    sprite.rotation = 0;
    sprite.size = Vector2 { Config::PLAYER_TEXTURE_SIZE, Config::PLAYER_TEXTURE_SIZE };
    sprite.flipX = true;
    sprite.anchor = Vector2 { 0.5f, 0.5f };
    sprite.SetTexture(&_texture1);
}

void Player::Update(bool shouldJump)
{
    float dt = GetFrameTime();

    if (shouldJump)
    {
        velocityY = -Config::PLAYER_JUMP_FORCE * dt;
    }
    // std::cout << "gravity: " << Config::PLAYER_GRAVITY * dt << "\n";
    velocityY += Config::PLAYER_GRAVITY * dt;
    // std::cout << "velocity y: " << velocityY << "\n";
    position.y += velocityY * dt;

    float rotation = Normalize(velocityY, -500.0f, 1000.0f); // @TODO config
    rotation = Lerp(-30, 45, rotation);

    sprite.position = position;
    sprite.rotation = rotation;

    _animationTimer -= dt;
    if (_animationTimer <= 0.0f)
    {
        _animationTimer = Config::PLAYER_ANIMATION_FRAME_DURATION;
        // @TODO proper sprite sheet animation instead of toggling texture
        Texture2D *newTexture = (sprite.texture == &_texture1) ? &_texture2 : &_texture1;
        sprite.SetTexture(newTexture);
    }
}

void Player::Draw()
{
    sprite.Draw();

    if (Config::DEBUG_DRAW_ENABLED)
    {
        DrawCircleLines(position.x, position.y, Config::PLAYER_COLLIDER_RADIUS, WHITE);
    }
}

void Player::Cleanup()
{
    UnloadTexture(_texture1);
    UnloadTexture(_texture2);
}

bool Player::IsOutOfBounds()
{
    float minPositionY = -Config::PLAYER_COLLIDER_RADIUS;
    float maxPositionY = Config::SCREEN_HEIGHT - Config::GROUND_HEIGHT - Config::PLAYER_COLLIDER_RADIUS;
    return position.y >= maxPositionY || position.y <= minPositionY;
}
