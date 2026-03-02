#include "Config.h"

const int Config::SCREEN_WIDTH = 480;
const int Config::SCREEN_HEIGHT = 720;
const int Config::TARGET_FPS = 60;

const float Config::SCROLL_SPEED = 100.0f;

const float Config::GROUND_HEIGHT = 100.0f;

const float Config::PLAYER_GRAVITY = 50 * TARGET_FPS;
const float Config::PLAYER_JUMP_FORCE = 600 * TARGET_FPS;
const Vector2 Config::PLAYER_START_POSITION { 100, 220 };
const float Config::PLAYER_COLLIDER_SIZE = 28.0f;
const float Config::PLAYER_COLLIDER_RADIUS = PLAYER_COLLIDER_SIZE / 2.0f;
const float Config::PLAYER_SPRITE_SIZE = 48.0f;
const float Config::PLAYER_ANIMATION_FRAME_DURATION = 1.0f / 8.0f;

const float Config::PIPE_SPEED = 100.0f;
const float Config::PIPE_COLLIDER_WIDTH = 100.0f;
const float Config::PIPE_SPRITE_WIDTH = 100.0f;
const float Config::PIPE_GAP_SIZE_X = 200.0f;
const float Config::PIPE_GAP_SIZE_Y_MIN = 160.0f;
const float Config::PIPE_GAP_SIZE_Y_MAX = 220.0f;
const float Config::PIPE_GAP_POS_Y_MIN = 200.0f;
const float Config::PIPE_GAP_POS_Y_MAX = SCREEN_HEIGHT - GROUND_HEIGHT - 200.0f;

bool Config::DEBUG_DRAW_ENABLED = false;
