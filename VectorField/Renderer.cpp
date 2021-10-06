#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <fstream>


std::map<std::string, Shader>       Renderer::shaderManager;

Renderer::Renderer(glm::vec2 coordinateGrid[20][20], Vector vectorField[400], glm::vec3 ballInitialState) {
    this->initRenderData(coordinateGrid, vectorField, ballInitialState);
}
Renderer::~Renderer() {
}

// Load and Store Shaders and Initialize all Renderers
// ---------------------------------------------------
void Renderer::initRenderData(glm::vec2 coordinateGrid[20][20], Vector vectorField[400], glm::vec3 ballInitialState) {
    this->LoadShader("CoordinateGrid.vert", "CoordinateGrid.frag", nullptr, "coordinateGridShader");
    this->LoadShader("Vector.vert", "Vector.frag", nullptr, "vectorShader");
    this->LoadShader("Particle.vert", "Particle.frag", nullptr, "particleShader");

    this->initCoordinateGridRenderer(coordinateGrid);
    this->initVectorFieldRenderer(vectorField);
    this->initParticleRenderer(ballInitialState);
}


// Initialize and Draw Coordinate Grid
// -----------------------------------
void Renderer::initCoordinateGridRenderer(glm::vec2 coordinateGrid[20][20]) {
    float vertices[240];
    int cnt = 0;

    for (int col = 0; col < 20; col++) {
        vertices[cnt++] = coordinateGrid[0][col].x;
        vertices[cnt++] = coordinateGrid[0][col].y;
        vertices[cnt++] = 0.0f;

        vertices[cnt++] = coordinateGrid[19][col].x;
        vertices[cnt++] = coordinateGrid[19][col].y;
        vertices[cnt++] = 0.0f;
    }
    for (int row = 0; row < 20; row++) {
        vertices[cnt++] = coordinateGrid[row][0].x;
        vertices[cnt++] = coordinateGrid[row][0].y;
        vertices[cnt++] = 0.0f;

        vertices[cnt++] = coordinateGrid[row][19].x;
        vertices[cnt++] = coordinateGrid[row][19].y;
        vertices[cnt++] = 0.0f;
    }
    unsigned int VBO;
    glGenVertexArrays(1, &this->coordinateGridVAO);
    glGenBuffers(1, &VBO);
    // bind coordinateGridVAO
    glBindVertexArray(this->coordinateGridVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Renderer::DrawCoordinateGrid(glm::vec2 coordinateGrid[20][20]) {
    // prepare transformations
    this->shader = shaderManager["coordinateGridShader"];
    this->shader.Use();
    this->shader.SetMatrix4("projection", this->proj);
    this->shader.SetMatrix4("model", glm::mat4(1.0f));


    // draw coordinate grid
    glUseProgram(this->shader.ID);
    glBindVertexArray(this->coordinateGridVAO);
    glDrawArrays(GL_LINES, 0, 400);
    glBindVertexArray(0);
}


// Initialize, Draw, and Update Vector Field
// -----------------------------------------
void Renderer::initVectorFieldRenderer(Vector vectorField[400]) {

    this->UpdateVectorField(vectorField);

}
void Renderer::UpdateVectorField(Vector vectorField[400]) {
    // want to put vertices on heap since its so large
    size_t vertCnt = 2400;
    float* vertices = new float[vertCnt];
    int cnt = 0;

    for (int i = 0; i < 400; i++) {
        Vector vec = vectorField[i];
        glm::vec3 pos = vec.origin;
        glm::vec3 dir = vec.direction;
        float mag = vec.magnitute;
        vertices[cnt++] = pos.x;
        vertices[cnt++] = pos.y;
        vertices[cnt++] = pos.z;


        glm::vec3 end = (pos + mag * dir);

        vertices[cnt++] = end.x;
        vertices[cnt++] = end.y;
        vertices[cnt++] = end.z;
    }

    unsigned int VBO;
    glGenVertexArrays(1, &this->vectorFieldVAO);
    glGenBuffers(1, &VBO);
    // bind vectorFieldVAO
    glBindVertexArray(this->vectorFieldVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertCnt, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // since on heap, need to delete 
    delete[] vertices;
}
void Renderer::DrawVectorField(Vector vectorField[400]) {
    // prepare transformations
    this->shader = shaderManager["vectorShader"];
    this->shader.Use();
    this->shader.SetMatrix4("projection", this->proj);
    this->shader.SetMatrix4("model", glm::mat4(1.0f));


    // draw vector field
    glUseProgram(this->shader.ID);
    glBindVertexArray(this->vectorFieldVAO);
    glDrawArrays(GL_LINES, 0, 1600);
    glBindVertexArray(0);
}


// Initialize, Draw, and Update Particle
// -----------------------------------------
// TODO: This should be done in the frag shader; this makes it not smooth and wastes memory
void Renderer::initParticleRenderer(glm::vec3 ballInitialState) {
    this->particleTransformMatrix = glm::translate(this->particleTransformMatrix, glm::vec3(5.0f, 5.0f, 0.0f));
    float vertices[600];
    auto i = 0;
    auto x = 0.0f,
        y = x,
        z = x,
        r = 0.4f;

    auto numSides = 21;
    auto TWO_PI = 2.0f * 3.1415f;
    auto increment = TWO_PI / numSides;

    for (auto angle = 0.0f; angle <= TWO_PI; angle += increment) {
        vertices[i++] = r * cos(angle) + x;
        vertices[i++] = r * sin(angle) + y;
        vertices[i++] = 0.0f;

        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;

        vertices[i++] = r * cos(angle + increment) + x;
        vertices[i++] = r * sin(angle + increment) + y;
        vertices[i++] = 0.0f;
    }
    unsigned int VBO;
    glGenVertexArrays(1, &this->particleVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->particleVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 400, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
void Renderer::DrawParticle() {
    // prepare transformations
    this->shader = shaderManager["particleShader"];
    this->shader.Use();
    this->shader.SetMatrix4("projection", this->proj);
    this->shader.SetMatrix4("model", particleTransformMatrix);


    //// draw ball
    glUseProgram(this->shader.ID);
    glBindVertexArray(this->particleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 600);
    glBindVertexArray(0);
}
void Renderer::UpdateParticleTranslationMatrix(glm::vec3 newDir) {
    glm::mat4 mod = this->particleTransformMatrix;

    mod = glm::translate(mod, newDir);

    this->particleTransformMatrix = mod;
}
void Renderer::MoveParticle(double x, double y) {
    // Reset Particle TransformMatrix
    this->particleTransformMatrix = glm::mat4(1.0f);
    // Update the translation matrix with new x, y
    this->UpdateParticleTranslationMatrix(glm::vec3(x, y, 0.0f));
}


// Various Shader Utilities
// ------------------------
Shader Renderer::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}
Shader Renderer::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    shaderManager[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaderManager[name];
}