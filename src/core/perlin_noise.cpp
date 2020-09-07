// CPP version of the Java reference implementation (COPYRIGHT 2002 KEN PERLIN.)

#include "perlin_noise.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>

float PerlinNoise::GenNoiseWithSeed(unsigned int seed, float x, float y, float z) {
    if (this->seed != seed) {
        p.resize(256);

        // Fill p with values from 0 to 255
        std::iota(p.begin(), p.end(), 0);

        // Initialize a random engine with seed
        std::default_random_engine engine(seed);

        // Suffle  using the above random engine
        std::shuffle(p.begin(), p.end(), engine);

        // Duplicate the permutation vector
        p.insert(p.end(), p.begin(), p.end());
    }

    return PNoise(x, y, z);
}

float PerlinNoise::PNoise(float x, float y, float z) {

    // Find the unit cube that contains the point
    int X = (int) std::floor(x) & 255;
    int Y = (int) std::floor(y) & 255;
    int Z = (int) std::floor(z) & 255;

    // Find relative x, y,z of point in cube
    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    // Compute fade curves for each of x, y, z
    float u = fade(x);
    float v = fade(y);
    float w = fade(z);

    // Hash coordinates of the 8 cube corners
    int A = p[X] + Y;
    int AA = p[A] + Z;
    int AB = p[A + 1] + Z;
    int B = p[X + 1] + Y;
    int BA = p[B] + Z;
    int BB = p[B + 1] + Z;

    // Add blended results from 8 corners of cube
    float res = lerp(w,
                      lerp(v,
                           lerp(u,
                                grad(p[AA], x, y, z),
                                grad(p[BA], x-1, y, z)),
                           lerp(u, grad(p[AB], x, y-1, z),
                                grad(p[BB], x-1, y-1, z))),
                      lerp(v, lerp(u, grad(p[AA+1], x, y, z-1),
                                   grad(p[BA+1], x-1, y, z-1)),
                           lerp(u, grad(p[AB+1], x, y-1, z-1),	grad(p[BB+1], x-1, y-1, z-1))));
    return static_cast<float>((res + 1.0) / 2.0);
}

float PerlinNoise::fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::lerp(float t, float a, float b) {
    return a + t * (b - a);
}

float PerlinNoise::grad(int hash, float x, float y, float z) {
    int h = hash & 15;

    // Convert lower 4 bits of hash into 12 gradient directions
    double u = h < 8 ? x : y,
            v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return static_cast<float>(((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v));
}
