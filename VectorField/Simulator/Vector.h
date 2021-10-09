#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <string>
#include <stdio.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <math.h>


class Vector
{
public:
    glm::vec3 origin;
    glm::vec3 direction;
    float magnitute = 1.0f;
    // constructor
    Vector();
    Vector(glm::vec3 origin, glm::vec3 direction, float magnitude);
    void SetDerivative(glm::vec3 pos);
};

#endif