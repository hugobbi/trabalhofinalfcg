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
#define COW 9
#define DEATHSTAR 10

#define ORIGIN glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)

#define ASTEROID_X_MIN 0
#define ASTEROID_X_MAX 10
#define ASTEROID_Y_MIN 0
#define ASTEROID_Y_MAX 10
#define ASTEROID_Z_MAX 15

#define ASTEROID_MAX_NUM 20

#define X_DIST 20
#define Y_DIST 10
#define COW_Z_MAX 10
#define COW_Z_MIN 0

#define LASER_MAX_RANGE 30
#define LASER_RENDER_THRESHOLD 0.5
#define LASER_RADIUS 0.08 

#define PLAYER_SPEED_PAUSED 1
#define PLAYER_SPEED 0.5
#define COW_SPEED 0.05
#define LASER_SPEED 200
#define ASTEROID_SPEED 1

struct Sphere
{
    glm::vec4 position;
    float radius;
};

struct Ray
{
    glm::vec4 initialPosition;
    glm::vec4 direction;
};

struct Rectangle
{
    glm::vec4 position;
    glm::vec3 bboxmax;
    glm::vec3 bboxmin;
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
    int cows_destroyed;
    int asteroids_destroyed;
    float speed;
    int ammo;
};

struct Laser
{
    Sphere geometry;
    Ray geometry_collision;
    int obj_id;
    float speed;
    bool state;
};

struct Asteroid
{
    Rectangle geometry;
    glm::vec4 direction;
    int obj_id;
    bool state;
    float speed;
};

struct Cow
{
    Rectangle geometry;
    int obj_id;
    bool state;
    float speed;
    float t;
    glm::vec4 bezierPoints[4];
};

struct Fulgor 
{
    Rectangle geometry;
    int obj_id;
};


struct Scene
{
    std::vector<Asteroid> asteroids;
    std::vector<Laser> lasers;
    std::vector<Cow> cows;
    Earth* earth;
    Fulgor* fulgor;
};

void createLaser(Scene* scene, Player player);
void createAsteroid(Scene* scene, glm::vec4 position, glm::vec3 bboxmax, glm::vec3 bboxmin);
void createCow(Scene* scene, glm::vec3 bboxmax, glm::vec3 bboxmin, float z_rand);
glm::vec4 calculateCowPositionBezier(Cow cow);