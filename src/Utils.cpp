#include "Utils.h"
#include <format>

void Utils::SeedRandom()
{
    std::srand(std::time({}));
}

float Utils::RandomRange(float min, float max)
{
    float random01 = (float)std::rand() / (float)RAND_MAX;
    return min + random01 * (max - min);
}

Texture2D Utils::LoadTextureWithFilename(std::string filename)
{
    std::string filePath = std::format("../res/textures/{}", filename);
    return LoadTexture(filePath.c_str());
}

Font Utils::LoadFontWithFilename(std::string filename, int fontSize)
{
    std::string filePath = std::format("../res/fonts/{}", filename);
    return LoadFontEx(filePath.c_str(), fontSize, nullptr, 250);
}
