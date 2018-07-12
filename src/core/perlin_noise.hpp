// CPP version of the Java reference implementation (COPYRIGHT 2002 KEN PERLIN.)

#pragma once

#include <vector>

class PerlinNoise {
public:
    static PerlinNoise & Instance() {
        static PerlinNoise instance;
        return instance;
    }

    PerlinNoise(PerlinNoise const&) = delete;
    void operator=(PerlinNoise const&) = delete;

    float GenNoiseWithSeed(unsigned int seed, float x, float y, float z);

private:
    PerlinNoise() = default;

    float PNoise(float x, float y, float z);
    float fade(float t);
    float lerp(float t, float a, float b);
    float grad(int hash, float x, float y, float z);

    unsigned int seed = 0;

    std::vector<int> p;
};