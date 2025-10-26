    #include <random>
    #include "raylib.h"
    #include "raymath.h"
    #include "BoidSimulation.h"

    void BoidSimulation::Initialize()
    {
        SimulationSettings settings;

        // Bounds
        settings.maxBoids = 1000;
        settings.boundsMin = {0, 0};
        settings.boundsMax = {1000, 800};

        // Simulation parameters
        settings.protectiveRange = 15;
        settings.visibleRange = 40;
        settings.avoidFactor = 0.05;
        settings.matchingFactor = 0.05;
        settings.centeringFactor = 0.0005;
        settings.turnFactor = 0.2;
        settings.minSpeed = 3;
        settings.maxSpeed = 6;

        state.settings = settings;

        float boidSize = 5;
        Color boidColor = BLACK;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(state.settings.boundsMin.x, state.settings.boundsMax.x);
        std::uniform_real_distribution<float> distY(state.settings.boundsMin.x, state.settings.boundsMax.y);
        std::uniform_real_distribution<float> distAngle(0.0, 2.0 * PI);

        state.boids.reserve(state.settings.maxBoids);
        state.prevBoids.reserve(state.settings.maxBoids);

        for (int i = 0; i < state.settings.maxBoids; i++)
        {
            Boid boid;
            boid.size = {boidSize, boidSize};
            boid.color = boidColor;

            float x = distX(gen);
            float y = distY(gen);
            boid.position = {x, y};

            float angle = distAngle(gen);
            Vector2 v = {settings.minSpeed, 0};
            Vector2 vRotated = Vector2Rotate(v, angle);
            boid.velocity = vRotated;

            state.boids.push_back(boid);
            state.prevBoids.push_back(boid);
        }
    }

    void BoidSimulation::Update(float deltaTime)
    {
        UpdateBoids(deltaTime);
        Draw();
    }

    void BoidSimulation::UpdateBoids(float deltaTime)
    {
        // back up values
        for (int i = 0; i < state.settings.maxBoids; i++) 
        {
            state.prevBoids[i] = state.boids[i];
        }

        // separation, alignment, cohesion
        for (int i = 0; i < state.boids.size(); i++)
        {
            auto boid = &state.boids[i];
            Vector2 closeDelta = {0, 0};

            Vector2 neighborVelAvg = {0, 0};
            Vector2 neighborPosAvg = {0, 0};
            int neighborCount = 0;

            // Naive pairwise check for now. Could use a spatial index here to find nearby boids.
            for (int j = 0; j < state.boids.size(); j++)
            {
                if (i == j)
                {
                    continue;
                }

                auto otherBoid = &state.prevBoids[j];

                float distance = Vector2Distance(boid->position, otherBoid->position);
                if (distance < state.settings.protectiveRange)
                {
                    // separation
                    auto diff = Vector2Subtract(boid->position, otherBoid->position);
                    closeDelta = Vector2Add(closeDelta, diff);
                }
                else if (distance < state.settings.visibleRange) 
                {
                    // alignment
                    neighborVelAvg = Vector2Add(neighborVelAvg, otherBoid->velocity);
                    
                    // cohesion
                    neighborPosAvg = Vector2Add(neighborPosAvg, otherBoid->position);
                    
                    neighborCount++;
                }
            }

            if (neighborCount > 0)
            {
                // alignment
                neighborVelAvg = Vector2Scale(neighborVelAvg, 1.0 / neighborCount);
                auto diff = Vector2Subtract(neighborVelAvg, boid->velocity);
                auto alignment = Vector2Scale(diff, state.settings.matchingFactor);
                
                // cohesion
                neighborPosAvg = Vector2Scale(neighborPosAvg, 1.0 / neighborCount);
                diff = Vector2Subtract(neighborPosAvg, boid->position);
                auto cohesion = Vector2Scale(diff, state.settings.centeringFactor);

                boid->velocity = Vector2Add(boid->velocity, alignment);
                boid->velocity = Vector2Add(boid->velocity, cohesion);
            }
            // separation
            boid->velocity = Vector2Add(boid->velocity, Vector2Scale(closeDelta, state.settings.avoidFactor));
        }

        // turning from screen edges
        for (int i = 0; i < state.boids.size(); i++)
        {
            auto boid = &state.boids[i];
            
            // turn x
            if (boid->position.x < state.settings.boundsMin.x) 
            {
                boid->velocity.x = boid->velocity.x + state.settings.turnFactor; 
            }
            else if (boid->position.x > state.settings.boundsMax.x) 
            {
                boid->velocity.x = boid->velocity.x - state.settings.turnFactor; 
            }

            // turn y
            if (boid->position.y < state.settings.boundsMin.y) 
            {
                boid->velocity.y = boid->velocity.y + state.settings.turnFactor; 
            }
            else if (boid->position.y > state.settings.boundsMax.y) 
            {
                boid->velocity.y = boid->velocity.y - state.settings.turnFactor; 
            }
        }

        // general movement
        for (int i = 0; i < state.boids.size(); i++)
        {
            auto boid = &state.boids[i];

            // keep speed within limits
            auto speed = Vector2Length(boid->velocity);
            if (speed > state.settings.maxSpeed)
            {
                boid->velocity = Vector2Scale(boid->velocity, state.settings.maxSpeed / speed);
            }
            else if (speed < state.settings.minSpeed) 
            {
                boid->velocity = Vector2Scale(boid->velocity, state.settings.minSpeed / speed);
            }

            // Could use delta time here, but that requires tuning of the parameters.
            float timeScaling = 1;
            boid->position = Vector2Add(boid->position, Vector2Scale(boid->velocity, timeScaling));
        }
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

    void BoidSimulation::DrawBoid(Boid boid)
    {
        DrawRectangle(boid.position.x, boid.position.y, boid.size.x, boid.size.y, boid.color);
    }
