#include "raylib.h"
#include "BoidSimulation.h"

int main() 
{
    auto simulation = new BoidSimulation();
    simulation->Initialize();

    InitWindow(1000, 800, "Boids");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) 
    {
        simulation->Update(GetFrameTime());
    }

    CloseWindow();

    return 0;   
}