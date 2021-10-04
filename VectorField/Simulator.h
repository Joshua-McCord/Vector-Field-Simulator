#pragma once

#include "Renderer.h"
#include "Vector.h"
#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/matrix_decompose.hpp>

enum SimulatorState {
	SIM_STATE_PAUSED,
	SIM_STATE_ANIMATING
};



class Simulator {
public:
	SimulatorState	State;
	bool			Keys[1024];
	int				Width, Height;
	glm::vec2		coordinateGrid[20][20];
	Vector			vectorField[400];
	glm::vec3		InitialBallState = glm::vec3(5.0f, 5.0f, 5.0f);
	glm::vec3		CurrentBallState = glm::vec3(5.0f, 5.0f, 0.0f);


	Simulator(unsigned int width, unsigned int height);
	~Simulator();

	// init sim
	// --------
	void init();

	// updating and rendering
	// ----------------------
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	// utilities
	// ---------
	glm::vec3 Function(glm::vec3 pos);
	glm::vec3 Euler_step(float h);
};