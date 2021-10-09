#include "Vector.h"

#include <iostream>

Vector::Vector() {
	this->origin = glm::vec3(0.0f);
	this->direction = glm::vec3(1.0f);
	this->magnitute = 1.0f;
}

Vector::Vector(glm::vec3 origin, glm::vec3 direction, float magnitude) {
	this->origin = origin;
	this->direction = direction;//glm::vec3(dir.x * dir.x - dir.y * dir.y,  2 * dir.x * dir.y,  dir.z);
	this->magnitute = glm::distance(origin, glm::vec3(0.0f)) / 5.0f;

}

void Vector::SetDerivative(glm::vec3 derivative)
{
	this->direction = derivative;
}


