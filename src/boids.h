#ifndef boids_h
#define boids_h

#include <vector>

struct Boid 
{
    Vector2 position;
    Vector2 velocity;
    float speed;
    float acceleration;
    Vector2 size;

    Color color;
};

struct WorldBounds 
{
    Vector2 boundsMin;
    Vector2 boundsMax;
};

struct BoidState 
{
    std::vector<Boid> boids;
    WorldBounds bounds;
};

#endif