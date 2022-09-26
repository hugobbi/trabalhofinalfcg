#include "scene.h"

#define LASER_SPEED 1
#define LASER_RADIUS 0.025

#define ASTEROID_HWD glm::vec3(0.12, 0.1, 0.15)
#define ASTEROID_SPEED 0.0008

void createLaser(Scene* scene, Player player, float animationTime)
{
    Laser laser;
    laser.state = true;
    laser.geometry.position = player.geometry.position;
    laser.direction = player.direction;
    laser.geometry.radius = LASER_RADIUS;
    laser.speed = LASER_SPEED;
    laser.obj_id = LASER;
    laser.animationTime = animationTime;
    scene->lasers.push_back(laser);
}

void createAsteroid(Scene* scene, glm::vec4 position, float animationTime)
{
    Asteroid asteroid;
    asteroid.geometry.HWD = ASTEROID_HWD;
    asteroid.geometry.position = position;
    asteroid.direction = ORIGIN - position;
    asteroid.state = true;
    asteroid.obj_id = ASTEROID;
    asteroid.speed = ASTEROID_SPEED;
    asteroid.animationTime = animationTime;
    scene->asteroids.push_back(asteroid);
}