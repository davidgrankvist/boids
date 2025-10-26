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
    void UpdateBoids(float deltaTime);
    void Draw();
    static void DrawBoid(Boid boid);
};

#endif