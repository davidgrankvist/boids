    #include <random>
    #include "raylib.h"
    #include "raymath.h"
    #include "BoidSimulation.h"

    void BoidSimulation::Initialize()
    {
        state.bounds.boundsMin = {0, 0};
        state.bounds.boundsMax = {1000, 800};
        int numBoids = 1000;
        float boidSize = 5;
        float boidSpeed = 100;
        float boidAcceleration = 5;
        Color boidColor = BLACK;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(state.bounds.boundsMin.x, state.bounds.boundsMax.x);
        std::uniform_real_distribution<float> distY(state.bounds.boundsMin.x, state.bounds.boundsMax.y);
        std::uniform_real_distribution<float> distAngle(0.0, 2.0 * PI);

        state.boids.reserve(numBoids);
        for (int i = 0; i < numBoids; i++) 
        {
            Boid boid;
            boid.speed = boidSpeed;
            boid.acceleration = boidAcceleration;
            boid.size = {boidSize, boidSize};
            boid.color = boidColor;

            float x = distX(gen);
            float y = distY(gen);
            boid.position = {x, y};

            float angle = distAngle(gen);
            Vector2 v = {boid.speed, 0};
            Vector2 vRotated = Vector2Rotate(v, angle);
            boid.velocity = vRotated;

            state.boids.push_back(boid);
        }
    }

    void BoidSimulation::Update(float deltaTime)
    {
        UpdateBoids(deltaTime);
        Draw();
    }

    void BoidSimulation::UpdateBoids(float deltaTime)
    {

    }

    void BoidSimulation::Draw() 
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < state.boids.size(); i++)
        {
            DrawBoid(state.boids[i]);
        }

        EndDrawing();
    }

    void BoidSimulation::DrawBoid(Boid boid) {
        DrawRectangle(boid.position.x, boid.position.y, boid.size.x, boid.size.y, boid.color);
    }
