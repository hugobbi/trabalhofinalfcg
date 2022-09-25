#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
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

struct Sphere
{
    glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    float radius;
    int obj_id;
};

struct Rectangle
{
    glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec3 HWD = glm::vec3(0.0f, 0.0f, 0.0f); // Height Width Depth
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
    glm::vec4 position;
    glm::vec4 direction;
    int obj_id;
    float speed;
    float radius;
    bool state;
};

struct Asteroid
{
    Rectangle geometry;
    glm::vec4 direction;
    int obj_id;
    bool state;
};

struct Scene
{
    std::vector<Asteroid> asteroids;
    std::vector<Laser> lasers;
    Sphere earth;
};

void createLaser(Scene* scene, Player player);