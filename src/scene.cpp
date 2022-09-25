#include "scene.h"

#define LASER_SPEED 10
#define LASER_RADIUS 0.25

void createLaser(Scene* scene, Player player)
{
    Laser laser;
    laser.state = true;
    laser.position = player.geometry.position;
    laser.direction = player.direction;
    laser.radius = LASER_RADIUS;
    laser.speed = LASER_SPEED;
    laser.obj_id = LASER;
    scene->lasers.push_back(laser);
}