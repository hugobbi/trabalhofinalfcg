#include "scene.h"

#define LASER_SPEED 20
#define LASER_RADIUS 0.2

#define ASTEROID_HWD glm::vec3(0.12, 0.1, 0.15)
#define ASTEROID_SPEED 0.0008

#define COW_SPEED 0.08

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

void createCow(Scene* scene, glm::vec3 cowHWD, float animationTime, float z_rand)
{
    Cow cow;
    cow.geometry.HWD = cowHWD;
    cow.state = true;
    cow.obj_id = COW;
    cow.speed = COW_SPEED;
    cow.animationTime = animationTime;

    // ajustar
    cow.bezierPoints[0] = glm::vec4(X_DIST,    Y_DIST,     1, 1);
    cow.bezierPoints[1] = glm::vec4(X_DIST-5, -1.2*Y_DIST, 1, 1);
    cow.bezierPoints[2] = glm::vec4(X_DIST-15, Y_DIST,     1, 1);
    cow.bezierPoints[3] = glm::vec4(0,         0,          1, 1);
    
    scene->cows.push_back(cow);
}

glm::vec4 calculateCowPositionBezier(Cow cow, float timeNow)
{
    float t = (timeNow - cow.animationTime) * COW_SPEED;

    //t = (sin(t) + 1)/2;

    glm::vec4 c12 = cow.bezierPoints[0] + t*(cow.bezierPoints[1] - cow.bezierPoints[0]);
    glm::vec4 c23 = cow.bezierPoints[1] + t*(cow.bezierPoints[2] - cow.bezierPoints[1]);
    glm::vec4 c34 = cow.bezierPoints[2] + t*(cow.bezierPoints[3] - cow.bezierPoints[2]);

    glm::vec4 c123 = c12 + t*(c23 - c12);
    glm::vec4 c234 = c23 + t*(c34 - c23);

    glm::vec4 c = c123 + t*(c234 - c123);

    return c;
}