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
    return false;
}

// weapon aim and asteroid collision
bool pointRectangleCollision2D(glm::vec4 point, Rectangle rectangle)
{
    return false;
}


