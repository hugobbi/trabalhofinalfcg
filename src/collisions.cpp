#include <iostream>
#include <cmath>
#include <algorithm>

#include <glm/vec4.hpp>
#include "collisions.h"
#include "scene.h"

float calculateDistanceBetweenPoints(glm::vec4 point1, glm::vec4 point2)
{    
    return sqrt(pow(point2.x - point1.x, 2) 
              + pow(point2.y - point1.y, 2) 
              + pow(point2.z - point1.z, 2));
}

// detecta colisão entre duas esferas, não foi utilizado na versão final
bool sphereSphereCollision(Sphere sphere1, Sphere sphere2)
{
    float distance_between_centers = calculateDistanceBetweenPoints(sphere1.position, sphere2.position);
    return distance_between_centers < (sphere1.radius + sphere2.radius);
}

// FONTE: https://stackoverflow.com/questions/27517250/sphere-cube-collision-detection-in-opengl
bool rectangleSphereCollision(Rectangle rectangle, Sphere sphere)
{    
    float xDistance = fabs(rectangle.position.x - sphere.position.x);
    float yDistance = fabs(rectangle.position.y - sphere.position.y);
    float zDistance = fabs(rectangle.position.z - sphere.position.z);

    if (xDistance >= (rectangle.bboxmax.x + sphere.radius))
        return false;
    if (yDistance >= (rectangle.bboxmax.y + sphere.radius))
        return false;
    if (zDistance >= (rectangle.bboxmax.z + sphere.radius))
        return false;

    if (xDistance < rectangle.bboxmax.x)
        return true;
    if (yDistance < rectangle.bboxmax.y)
        return true;
    if (zDistance < rectangle.bboxmax.z)
        return true;

    // corner detection
    float cornerDistance = (pow(xDistance-rectangle.bboxmax.x, 2))
                         + (pow(yDistance-rectangle.bboxmax.y, 2))
                         + (pow(zDistance-rectangle.bboxmax.z, 2));

    return (cornerDistance < pow(sphere.radius, 2));

    return false;
}

// detecta colisão entre dois retângulos 3D
bool rectangleRectangleCollision(Rectangle rectangle1, Rectangle rectangle2)
{
    float xDistance = fabs(rectangle1.position.x - rectangle2.position.x);
    float yDistance = fabs(rectangle1.position.y - rectangle2.position.y);
    float zDistance = fabs(rectangle1.position.z - rectangle2.position.z);

    if (xDistance >= (rectangle1.bboxmax.x + rectangle2.bboxmax.x))
        return false;
    if (yDistance >= (rectangle1.bboxmax.y + rectangle2.bboxmax.y))
        return false;
    if (zDistance >= (rectangle1.bboxmax.z + rectangle2.bboxmax.z))
        return false;

    if (xDistance < rectangle1.bboxmax.x)
        return true;
    if (yDistance < rectangle1.bboxmax.y)
        return true;
    if (zDistance < rectangle1.bboxmax.z)
        return true;

    return false;
}

// FONTE: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
bool rayRectangleCollision(Ray ray, Rectangle rectangle)
{
    glm::vec4 translationVector = rectangle.position - ORIGIN;
    glm::vec4 min = glm::vec4(rectangle.bboxmin, 1.0f) + translationVector;
    glm::vec4 max = glm::vec4(rectangle.bboxmax, 1.0f) + translationVector;
    
    float tmin = (min.x - ray.initialPosition.x) / ray.direction.x;
    float tmax = (max.x - ray.initialPosition.x) / ray.direction.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (min.y - ray.initialPosition.y) / ray.direction.y;
    float tymax = (max.y - ray.initialPosition.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;
    
    if (tymax < tmax)
        tmax = tymax;
    
    float tzmin = (min.z - ray.initialPosition.z) / ray.direction.z;
    float tzmax = (max.z - ray.initialPosition.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    
    if (tzmin > tmin)
        tmin = tzmin;
    
    if (tzmax < tmax)
        tmax = tzmax;

    if (tmin < 0 && tmax < 0)
        return false;

    return true;
}

// intersecção raio esfera usando discriminante
bool raySphereCollision(const Ray& ray, const Sphere& sphere, const glm::vec4& playerDirection)
{
    glm::vec4 dirRaySphere = normalize(ray.initialPosition - sphere.position);
    if (glm::dot(dirRaySphere, playerDirection) >= 0)
        return false;

    float px = ray.initialPosition.x;
    float py = ray.initialPosition.y;
    float pz = ray.initialPosition.z;

    float dx = ray.direction.x;
    float dy = ray.direction.y;
    float dz = ray.direction.z;

    float r2 = sphere.radius*sphere.radius;
    float cx = sphere.position.x;
    float cy = sphere.position.y;
    float cz = sphere.position.z;

    float a = dx*dx + dy*dy + dz*dz;
    float b = 2*(dx*(px - cx) + dy*(py - cy) + dz*(pz - cz));
    float c = px*px - 2*cx*px + cx*cx + py*py - 2*cy*py + cy*cy + pz*pz - 2*cz*pz + cz*cz - r2;

    float discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return false;

    return true; 
}

// controla colisões do jogador
bool playerCollision(Player* player, Scene scene, bool gamePaused)
{
    // verifica colisão com asteroides
    if (!gamePaused)
        for (Asteroid asteroid : scene.asteroids)
        {
            if (rectangleRectangleCollision(asteroid.geometry, player->geometry))
            {
                    player->state = false; // jogador morreu
                    return true;
            }
        }

    // verifica colisão com Terra
    if (rectangleSphereCollision(player->geometry, scene.earth->geometry))
    {
        return true;
    }

    return false;
}