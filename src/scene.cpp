#include "scene.h"

void createLaser(Scene* scene, Player player)
{
    Laser laser;
    laser.state = true;
    laser.geometry.position = player.geometry.position;
    laser.geometry_collision.initialPosition = player.geometry.position;
    laser.geometry_collision.direction = glm::normalize(player.direction);
    laser.geometry.radius = LASER_RADIUS;
    laser.speed = LASER_SPEED;
    laser.obj_id = LASER;
    scene->lasers.push_back(laser);
}

void createAsteroid(Scene* scene, glm::vec4 position, glm::vec3 bboxmax, glm::vec3 bboxmin)
{
    Asteroid asteroid;
    asteroid.geometry.position = position;
    asteroid.direction = glm::normalize(ORIGIN - position);
    asteroid.state = true;
    asteroid.obj_id = ASTEROID;
    asteroid.speed = ASTEROID_SPEED;
    asteroid.geometry.bboxmax = glm::vec4(bboxmax, 1);
    asteroid.geometry.bboxmin = glm::vec4(bboxmin, 1);
    scene->asteroids.push_back(asteroid);
}

void createCow(Scene* scene, glm::vec3 bboxmax, glm::vec3 bboxmin, float z_rand)
{
    Cow cow;
    cow.geometry.bboxmax = glm::vec4(bboxmax, 1);
    cow.geometry.bboxmin = glm::vec4(bboxmin, 1);
    cow.state = true;
    cow.obj_id = COW;
    cow.speed = COW_SPEED;
    cow.t = 0;

    // ajustar
    cow.bezierPoints[0] = glm::vec4(X_DIST,    Y_DIST,     z_rand, 1);
    cow.bezierPoints[1] = glm::vec4(X_DIST-5, -1.2*Y_DIST, z_rand, 1);
    cow.bezierPoints[2] = glm::vec4(X_DIST-15, Y_DIST,     z_rand, 1);
    cow.bezierPoints[3] = glm::vec4(0,         0,          1,      1);

    scene->cows.push_back(cow);
}

glm::vec4 calculateCowPositionBezier(Cow cow)
{
    //cow.t = (sin(cow.t) + 1)/2;

    glm::vec4 c12 = cow.bezierPoints[0] + cow.t*(cow.bezierPoints[1] - cow.bezierPoints[0]);
    glm::vec4 c23 = cow.bezierPoints[1] + cow.t*(cow.bezierPoints[2] - cow.bezierPoints[1]);
    glm::vec4 c34 = cow.bezierPoints[2] + cow.t*(cow.bezierPoints[3] - cow.bezierPoints[2]);

    glm::vec4 c123 = c12 + cow.t*(c23 - c12);
    glm::vec4 c234 = c23 + cow.t*(c34 - c23);

    glm::vec4 c = c123 + cow.t*(c234 - c123);

    return c;
}