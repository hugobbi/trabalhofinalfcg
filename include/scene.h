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

struct Scene
{
    std::vector<Rectangle> asteroids;
    Sphere earth;
};