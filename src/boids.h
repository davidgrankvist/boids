#ifndef boids_h
#define boids_h

#include <vector>

struct Boid 
{
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
    Color color;
};

struct SimulationSettings 
{
    int maxBoids;
    Vector2 boundsMin;
    Vector2 boundsMax;

    float visibleRange;
    float protectiveRange;
    float avoidFactor;
    float matchingFactor;
    float centeringFactor;
    float turnFactor;

    float minSpeed;
    float maxSpeed;

    float boidSize;
    Color boidColor;
};

struct BoidState 
{
    std::vector<Boid> boids;
    std::vector<Boid> prevBoids;
    SimulationSettings settings;
};

#endif