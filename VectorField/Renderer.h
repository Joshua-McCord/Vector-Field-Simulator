#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <set>
#include <algorithm>  // std::copy
#include <math.h>
#include <map>
#include <string>

#include "Shader.h"
#include "Vector.h"
class Renderer
{
public:
    // Common Variables
    glm::mat4 particleTransformMatrix = glm::mat4(1.0f);
    double particleX = 0;
    double particleY = 0;

    // Constructor/Destructor
    Renderer(glm::vec2 coordinateGrid[20][20], Vector vectorField[400], glm::vec3 particleInitialState);
    ~Renderer();

    // Draw the elements every frame
    void DrawVectorField(Vector vectorField[400]);
    void UpdateVectorField(Vector vectorField[400]);
    void DrawCoordinateGrid(glm::vec2 coordinateGrid[20][20]);
    void DrawParticle();

    // Update Particle Position
    void UpdateParticleTranslationMatrix(glm::vec3 newPos);
    void MoveParticle(double x, double y);

private:

    // Common Variables
    glm::mat4 proj = glm::ortho(-10.0f, +9.0f, -10.0f, +9.0f, -1.0f, 1.0f);
    
    
    // VAOS
    unsigned int coordinateGridVAO;
    unsigned int vectorFieldVAO;
    unsigned int particleVAO;

    // Render Data Initialization
    void initRenderData(glm::vec2 coordinateGrid[20][20], Vector vectorField[400], glm::vec3 particleInitialState);
    void initCoordinateGridRenderer(glm::vec2 coordinateGrid[20][20]);
    void initVectorFieldRenderer(Vector vectorField[400]);
    void initParticleRenderer(glm::vec3 particleInitialState);

    // Shader Management
    Shader shader;
    unsigned int shaderProgram;
    static std::map<std::string, Shader>    shaderManager;

    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);

};