#include "scene.h"

#define LASER_SPEED 1.5
#define LASER_RADIUS 0.05

#define ASTEROID_HWD glm::vec3(0.12, 0.1, 0.15)
#define ASTEROID_SPEED 0.0008

#define COW_SPEED 0.007

void createLaser(Scene* scene, Player player, float animationTime)
{
    Laser laser;
    laser.state = true;
    laser.geometry.position = player.geometry.position+player.direction;
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

void createCow(Scene* scene, glm::vec4 position, float bezierPoints[4], glm::vec3 cowHWD, float animationTime)
{
    Cow cow;
    cow.geometry.HWD = cowHWD;
    cow.geometry.position = position;
    cow.state = true;
    cow.obj_id = COW;
    cow.speed = COW_SPEED;
    cow.animationTime = animationTime;
    scene->cows.push_back(cow);
}