#include "Config.h"

const int Config::SCREEN_WIDTH = 480;
const int Config::SCREEN_HEIGHT = 720;
const int Config::TARGET_FPS = 60;

const float Config::SCROLL_SPEED = 100.0f;

const float Config::GROUND_HEIGHT = 100.0f;

const float Config::PLAYER_GRAVITY = 50 * TARGET_FPS;
const float Config::PLAYER_JUMP_FORCE = 600 * TARGET_FPS;
const Vector2 Config::PLAYER_START_POSITION { 100, 240 };
const float Config::PLAYER_COLLIDER_SIZE = 36.0f;
const float Config::PLAYER_COLLIDER_RADIUS = PLAYER_COLLIDER_SIZE / 2.0f;
const float Config::PLAYER_TEXTURE_SIZE = 48.0f;
const float Config::PLAYER_ANIMATION_FRAME_DURATION = 10.0f / 60.0f;

bool Config::DEBUG_DRAW_ENABLED = false;
