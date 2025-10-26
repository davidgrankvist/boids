# boids

Boids simulation.

## About

[Boids](https://en.wikipedia.org/wiki/Boids) simulates flock behavior of birds. Instead of letting each individual boid having complex behavior, there are some simple local rules that result in flock like movements.

The flocking movement is captured with three main mechanisms:
- separation - moving away when too close to other boids
- alignment - following the general direction of nearby boids
- cohesion - staying close to the center (average position) of nearby boids

## Acknowledgements

Big thanks to V. Hunter Adams for [this writeup](https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html).