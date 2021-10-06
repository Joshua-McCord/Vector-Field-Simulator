#include "Simulator.h"

Renderer* renderer;

Simulator::Simulator(unsigned int width, unsigned int height) : CurrentFunctionState(FUNCTION_ONE), CurrentSolverState(EULER_SOLVER), Keys(), Width(width), Height(height) {
	PreviousFunctionState = CurrentFunctionState;

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

	// Create Vector Field
	int cnt = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			glm::vec3 pos = glm::vec3(this->coordinateGrid[i][j].x, this->coordinateGrid[i][j].y, 0.0f);
			glm::vec3 dir = glm::normalize(pos - glm::vec3(0.0f));
			vectorField[cnt++] = Vector(
				pos,
				this->Function(dir),
				1.0f
			);
		}
	}

	renderer = new Renderer(this->coordinateGrid, this->vectorField, this->CurrentParticleState);
}

void Simulator::Update(float dt) {
	switch (CurrentSolverState) {
		case EULER_SOLVER:
			renderer->UpdateParticleTranslationMatrix(this->Euler_step(0.01f));
			break;
		case MIDPOINT_SOLVER:
			renderer->UpdateParticleTranslationMatrix(this->Midpoint_Step(0.01f));
			break;
		case RUNGE_KUTTA_FOUR_SOLVER:
			renderer->UpdateParticleTranslationMatrix(this->Runge_Kutta_Four_Step(0.01f));
			break;
	}
}

void Simulator::Render() {
	renderer->DrawCoordinateGrid(this->coordinateGrid);
	renderer->DrawVectorField(this->vectorField);
	renderer->DrawParticle();	
}

void Simulator::ProcessInput(float dt) {
	PreviousFunctionState = CurrentFunctionState;
	if (this->Keys[GLFW_KEY_1]) 
		this->CurrentFunctionState = FUNCTION_ONE;
	if (this->Keys[GLFW_KEY_2])
		this->CurrentFunctionState = FUNCTION_TWO;
	if (this->Keys[GLFW_KEY_3])
		this->CurrentFunctionState = FUNCTION_THREE;
	if (this->Keys[GLFW_KEY_4])
		this->CurrentFunctionState = FUNCTION_FOUR;
	if (this->Keys[GLFW_KEY_5])
		this->CurrentFunctionState = FUNCTION_FIVE;
	if (this->Keys[GLFW_KEY_6])
		this->CurrentFunctionState = FUNCTION_SIX;
	if (this->Keys[GLFW_KEY_7])
		this->CurrentFunctionState = FUNCTION_SEVEN;
	if (this->Keys[GLFW_KEY_8])
		this->CurrentFunctionState = FUNCTION_EIGHT;
	if (this->Keys[GLFW_KEY_9])
		this->CurrentFunctionState = FUNCTION_NINE;
	if (this->Keys[GLFW_KEY_0])
		this->CurrentFunctionState = FUNCTION_ZERO;

	if (PreviousFunctionState != CurrentFunctionState) {
		this->UpdateVectorField();
	}

	if (this->Keys[GLFW_KEY_LEFT])
		this->CurrentSolverState = EULER_SOLVER;
	if (this->Keys[GLFW_KEY_UP])
		this->CurrentSolverState = MIDPOINT_SOLVER;
	if (this->Keys[GLFW_KEY_RIGHT])
		this->CurrentSolverState = RUNGE_KUTTA_FOUR_SOLVER;

}

// Utility Functions
// -----------------
void Simulator::UpdateVectorField() {
	// Create Vector Field
	int cnt = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			glm::vec3 pos = glm::vec3(this->coordinateGrid[i][j].x, this->coordinateGrid[i][j].y, 0.0f);
			glm::vec3 dir = glm::normalize(pos - glm::vec3(0.0f));
			vectorField[cnt++] = Vector(
				pos,
				this->Function(dir),
				1.0f
			);
		}
	}
	renderer->UpdateVectorField(this->vectorField);
}

glm::vec3 Simulator::Function(glm::vec3 dir) {
	float x = dir.x;
	float y = dir.y;
	float z = dir.z;

	switch (CurrentFunctionState) {
		case FUNCTION_ONE:
			return glm::vec3((x * x) - (y * y), 2 * x * y, z);
		case FUNCTION_TWO:
			return glm::vec3(y, -x + y, z);
		case FUNCTION_THREE:
			return glm::vec3(-x, -y, z);
		case FUNCTION_FOUR:
			return glm::vec3(0, x * x, z);
		case FUNCTION_FIVE:
			return glm::vec3(x, y, z);
		case FUNCTION_SIX:
			return glm::vec3(y-x, -x-y, z);
		case FUNCTION_SEVEN:
			return glm::vec3(-y, x, z);
		case FUNCTION_EIGHT:
			return glm::vec3(2 * x, -y, z);
		case FUNCTION_NINE:
			return glm::vec3(y, x, z);
		case FUNCTION_ZERO:
			return glm::vec3(x * x, y * y, z);
	}

}

// Euler Solver
glm::vec3 Simulator::Euler_step(float h) {
	// Euler Step Defined as: x_(t+1) = x_t + h * f(x,t), where f is the derivative
	// vector field by definition gives derivative
	glm::vec3 particleCurrentState = this->CurrentParticleState;
	glm::vec3 derivative = this->Function(particleCurrentState);

	// Calculate  h * f(x,t)
	glm::vec3 new_step = h * derivative;

	// Update x_(t+1) so we can use it in the next calculation
	this->CurrentParticleState = particleCurrentState + new_step;

	// Return h * f(x,t) since the renderer is using a translation matrix
	return new_step;
}
// Midpoint Solver
glm::vec3 Simulator::Midpoint_Step(float h) {
	// Midpoint Step defined as: x_(t+1) = x_t + h * f(x_t + h/2f(xt)) 
	glm::vec3 particleCurrentState = this->CurrentParticleState;
	glm::vec3 derivative = this->Function(particleCurrentState);

	// Calculate  h * f(x,t)
	glm::vec3 delta_x = h * derivative;

	glm::vec3 f_mid = Function(particleCurrentState + (delta_x / 2.0f));

	glm::vec3 new_step = h * f_mid;

	this->CurrentParticleState = particleCurrentState + new_step;

	return new_step;
}
// RK4 Solver
glm::vec3 Simulator::Runge_Kutta_Four_Step(float h) {
	glm::vec3 particleCurrentState = this->CurrentParticleState;

	// All lower order RKs
	glm::vec3 k_1 = h * Function(particleCurrentState);
	glm::vec3 k_2 = h / 2.0f * Function(particleCurrentState + k_1 / 2.0f);
	glm::vec3 k_3 = h / 2.0f * Function(particleCurrentState + k_2 / 2.0f);

	// Final 4th Order RK 
	glm::vec3 k_4 = h * Function(particleCurrentState + k_3 / 2.0f);
	glm::vec3 new_step = k_4;

	this->CurrentParticleState = particleCurrentState + new_step;

	return new_step;
}

void Simulator::ProcessMouseInput(double x, double y) {
	x = ((x - 500) / 100) * 2;
	y = - ((y - 500) / 100) * 2;
	this->CurrentParticleState = glm::vec3(x, y, 0.0f);
	renderer->MoveParticle(x, y);
}