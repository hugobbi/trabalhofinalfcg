// esfera-esfera: terra com asteroides: quao mais proximo, mais vermelho até amarelo então perde
// esfera-ponto: arma com asteroide (tiro viaja mais rápido q a luz)
// esfera-cubo: jogador com asteroide

#include <glm/vec4.hpp>
#include "scene.h"

float calculateDistanceBetweenPoints(glm::vec4 point1, glm::vec4 point2);
void pointSphereCollision(glm::vec4 point, glm::vec4 sphere_center);
bool sphereSphereCollision(Sphere sphere1, Sphere sphere2);
bool rectangleSphereCollision(Rectangle rectangle, Sphere sphere);