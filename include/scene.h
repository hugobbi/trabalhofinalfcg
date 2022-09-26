#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <vector>

// object ids
#define EARTH 0
#define PLANAR 1
#define PLANE 2
#define AIM 3
#define CUBEMAP 4
#define ASTEROID 5
#define TESTCUBE 6
#define PLAYER 7
#define LASER 8

#define ORIGIN glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)

#define ASTEROID_X_MIN 0
#define ASTEROID_X_MAX 10
#define ASTEROID_Y_MIN 0
#define ASTEROID_Y_MAX 10

#define ASTEROID_Z_MAX 10

struct Sphere
{
    glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    float radius;
};

struct Rectangle
{
    glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec3 HWD = glm::vec3(0.0f, 0.0f, 0.0f); // Height Width Depth
};

struct Earth
{
    Sphere geometry;
    int state;
    int obj_id;
};

struct Player
{
    Rectangle geometry;
    glm::vec4 direction;
    int obj_id;
    bool state;
    int asteroids_destroyed;
};

struct Laser
{
    Sphere geometry;
    glm::vec4 direction;
    int obj_id;
    float speed;
    float animationTime;
    bool state;
};

struct Asteroid
{
    Rectangle geometry;
    glm::vec4 direction;
    int obj_id;
    bool state;
    float speed;
    float animationTime;
};

struct Scene
{
    std::vector<Asteroid> asteroids;
    std::vector<Laser> lasers;
    Earth* earth;
};

void createLaser(Scene* scene, Player player, float animationTime);
void createAsteroid(Scene* scene, glm::vec4 position, float animationTime);