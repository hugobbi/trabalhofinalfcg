#include "scene.h"

#define LASER_SPEED 1
#define LASER_RADIUS 0.025

void createLaser(Scene* scene, Player player, float animationTime)
{
    Laser laser;
    laser.state = true;
    laser.geometry.position = player.geometry.position;
    laser.direction = player.direction;
    laser.geometry.radius = LASER_RADIUS;
    laser.speed = LASER_SPEED;
    laser.obj_id = LASER;
    laser.animationTime = animationTime;
    scene->lasers.push_back(laser);
}