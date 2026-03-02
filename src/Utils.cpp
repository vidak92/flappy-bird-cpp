#include "Utils.h"
#include <cstdlib>
#include <ctime>

void Utils::SeedRandom()
{
    std::srand(std::time({}));
}

float Utils::RandomRange(float min, float max)
{
    float random01 = (float)std::rand() / (float)RAND_MAX;
    return min + random01 * (max - min);
}