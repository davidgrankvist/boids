#ifndef BoidSimulation_h
#define BoidSimulation_h

#include "boids.h"

class BoidSimulation
{
public:
    void Initialize();
    void Update(float deltaTime);
private:
    BoidState state;
    void InitializeSettings();
    void SpawnRandomBoids();
    void ApplyFlocking();
    void SteerFromBounds();
    void MoveBoids(float deltaTime);
    void Draw();
    static void DrawBoid(Boid boid);
};

#endif