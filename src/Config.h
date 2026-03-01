#ifndef FLAPPY_BIRD_CPP_GAMECONFIG_H
#define FLAPPY_BIRD_CPP_GAMECONFIG_H
#include "raylib.h"

struct Config
{
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    static const int TARGET_FPS;

    static const float SCROLL_SPEED;

    static const float GROUND_HEIGHT;

    static const float PLAYER_GRAVITY;
    static const float PLAYER_JUMP_FORCE;
    static const Vector2 PLAYER_START_POSITION;
    static const float PLAYER_COLLIDER_SIZE;
    static const float PLAYER_COLLIDER_RADIUS;
    static const float PLAYER_TEXTURE_SIZE;
    static const float PLAYER_ANIMATION_FRAME_DURATION;

    static bool DEBUG_DRAW_ENABLED;
};

#endif //FLAPPY_BIRD_CPP_GAMECONFIG_H