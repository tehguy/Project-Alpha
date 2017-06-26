// CPP version of the Java reference implementation (COPYRIGHT 2002 KEN PERLIN.)

#pragma once

#include <vector>

class PerlinNoise {
public:
    static double Noise(double x, double y, double z);
    static double NoiseWithSeed(unsigned int seed, double x, double y, double z);

private:
    static double PNoise(double x, double y, double z);
    static double fade(double t);
    static double lerp(double t, double a, double b);
    static double grad(int hash, double x, double y, double z);

    static std::vector<int> p;

    static unsigned int _seed;
};