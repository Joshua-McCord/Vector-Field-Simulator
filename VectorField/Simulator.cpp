#include "Simulator.h"

Renderer* renderer;

Simulator::Simulator(unsigned int width, unsigned int height) : State(SIM_STATE_PAUSED), Keys(), Width(width), Height(height) {

}

Simulator::~Simulator() {
}

void Simulator::init() {
	// initialize the grid
	int row = -10;
	int col = -10;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			this->coordinateGrid[i][j] = glm::vec2(row, col);
			col+=1;
		}
		row += 1;
		col = -10;
	}

	int cnt = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			glm::vec3 pos = glm::vec3(this->coordinateGrid[i][j].x, this->coordinateGrid[i][j].y, 0.0f);
			glm::vec3 dir = glm::normalize(glm::vec3(0.0f) - pos);
			vectorField[cnt++] = Vector(
				pos,
				this->Function(dir),
				1.0f
			);
		}
	}

	renderer = new Renderer(this->coordinateGrid, this->vectorField, this->CurrentBallState);
}

void Simulator::Update(float dt) {
	//this->eulerSolver();
	

	renderer->UpdateBallTranslation(this->Euler_step(0.001f));
}

void Simulator::Render() {
	renderer->DrawCoordinateGrid(this->coordinateGrid);
	renderer->DrawVectorField(this->vectorField);
	renderer->DrawSimulatorBall();
	
}

glm::vec3 Simulator::Function(glm::vec3 dir) {
	float x = dir.x;
	float y = dir.y;
	float z = dir.z;

	return glm::vec3((x * x) - (y * y), 2*x*y, dir.z);
}

// Euler Solver
glm::vec3 Simulator::Euler_step(float h) {
	// Euler Step Defined as: x_(t+1) = x_t + h * f(x,t), where f is the derivative
	// vector field by definition gives derivative
	glm::vec3 ballCurrentState = this->CurrentBallState;
	glm::vec3 derivative = this->Function(ballCurrentState);

	// Calculate  h * f(x,t)
	glm::vec3 new_step = h * derivative;

	// Update x_(t+1) so we can use it in the next calculation
	this->CurrentBallState = ballCurrentState + new_step;

	// Return h * f(x,t) since the renderer is using a translation matrix
	return new_step;
}
