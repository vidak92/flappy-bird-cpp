#ifndef FLAPPY_BIRD_CPP_UTILS_H
#define FLAPPY_BIRD_CPP_UTILS_H
#include <string>
#include "raylib.h"

struct Utils
{
    static void SeedRandom();
    static float RandomRange(float min, float max);

    static Texture2D LoadTextureWithFilename(std::string filename);
    static Font LoadFontWithFilename(std::string filename, int fontSize);
};

#endif //FLAPPY_BIRD_CPP_UTILS_H