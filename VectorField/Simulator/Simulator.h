#pragma once

#include "../Renderer/Renderer.h"
#include "Vector.h"
#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/matrix_decompose.hpp>

enum FunctionState {
	FUNCTION_ONE,
	FUNCTION_TWO, 
	FUNCTION_THREE,
	FUNCTION_FOUR, 
	FUNCTION_FIVE,
	FUNCTION_SIX,
	FUNCTION_SEVEN,
	FUNCTION_EIGHT,
	FUNCTION_NINE,
	FUNCTION_ZERO,
};

enum SolverState {
	EULER_SOLVER,
	MIDPOINT_SOLVER,
	RUNGE_KUTTA_FOUR_SOLVER,
};



class Simulator {
public:
	FunctionState	CurrentFunctionState;
	FunctionState	PreviousFunctionState;
	SolverState		CurrentSolverState;
	bool			Keys[1024];
	int				Width, Height;
	glm::vec2		coordinateGrid[20][20];
	Vector			vectorField[400];
	glm::vec3		InitialParticleState = glm::vec3(5.0f, 5.0f, 5.0f);
	glm::vec3		CurrentParticleState = glm::vec3(5.0f, 5.0f, 0.0f);


	Simulator(unsigned int width, unsigned int height);
	~Simulator();

	// init sim
	// --------
	void init();

	// updating and rendering
	// ----------------------
	void ProcessInput(float dt);
	void ProcessMouseInput(double x, double y);
	void Update(float dt);
	void Render();

	// utilities
	// ---------
	glm::vec3 Function(glm::vec3 pos);
	glm::vec3 Euler_step(float h);
	glm::vec3 Midpoint_Step(float h);
	glm::vec3 Runge_Kutta_Four_Step(float h);
	void UpdateVectorField();
};