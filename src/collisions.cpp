#include <iostream>
#include <cmath>

#include <glm/vec4.hpp>
#include "collisions.h"
#include "scene.h"

// all distances and points in world coordinates

float calculateDistanceBetweenPoints(glm::vec4 point1, glm::vec4 point2)
{    
    return sqrt(pow(point2.x - point1.x, 2) 
              + pow(point2.y - point1.y, 2) 
              + pow(point2.z - point1.z, 2));
}

// FONTE: https://stackoverflow.com/questions/27517250/sphere-cube-collision-detection-in-opengl
bool rectangleSphereCollision(Rectangle rectangle, Sphere sphere)
{    
    float xDistance = fabs(rectangle.position.x - sphere.position.x);
    float yDistance = fabs(rectangle.position.y - sphere.position.y);
    float zDistance = fabs(rectangle.position.z - sphere.position.z);

    if (xDistance >= (rectangle.HWD.x + sphere.radius))
        return false;
    if (yDistance >= (rectangle.HWD.y + sphere.radius))
        return false;
    if (zDistance >= (rectangle.HWD.z + sphere.radius))
        return false;

    if (xDistance < rectangle.HWD.x)
        return true;
    if (yDistance < rectangle.HWD.y)
        return true;
    if (zDistance < rectangle.HWD.z)
        return true;

    // corner detection
    float cornerDistance = (pow(xDistance-rectangle.HWD.x, 2))
                         + (pow(yDistance-rectangle.HWD.y, 2))
                         + (pow(zDistance-rectangle.HWD.z, 2));

    return (cornerDistance < pow(sphere.radius, 2));

    return false;
}

bool sphereSphereCollision(Sphere sphere1, Sphere sphere2)
{
    float distance_between_centers = calculateDistanceBetweenPoints(sphere1.position, sphere2.position);
    return distance_between_centers < (sphere1.radius + sphere2.radius);
}

bool rectangleRectangleCollision(Rectangle rectangle1, Rectangle rectangle2)
{
    float xDistance = fabs(rectangle1.position.x - rectangle2.position.x);
    float yDistance = fabs(rectangle1.position.y - rectangle2.position.y);
    float zDistance = fabs(rectangle1.position.z - rectangle2.position.z);

    if (xDistance >= (rectangle1.HWD.x + rectangle2.HWD.x))
        return false;
    if (yDistance >= (rectangle1.HWD.y + rectangle2.HWD.y))
        return false;
    if (zDistance >= (rectangle1.HWD.z + rectangle2.HWD.z))
        return false;

    if (xDistance < rectangle1.HWD.x)
        return true;
    if (yDistance < rectangle1.HWD.y)
        return true;
    if (zDistance < rectangle1.HWD.z)
        return true;
    
    return false;
}

bool playerCollision(Player* player, Scene scene)
{
    // verifica colisão com asteroides
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

int laserCollision(Scene* scene, Laser laser)
{
    for (auto asteroid = scene->asteroids.begin(); asteroid != scene->asteroids.end(); asteroid++)
    {
        if (rectangleSphereCollision(asteroid->geometry, laser.geometry))
        {
            asteroid->state = false;
            scene->asteroids.erase(asteroid--);
            return 1;
        }
    }
    if (sphereSphereCollision(scene->earth->geometry, laser.geometry))
    {
        scene->earth->state = 2;
        return 2;
    }

    return 0;
}


