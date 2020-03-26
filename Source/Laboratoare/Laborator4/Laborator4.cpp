#include "Laborator4.h"

#include <vector>
#include <string>
#include <iostream>
#include<cmath>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

Laborator4::Laborator4()
{
}

Laborator4::~Laborator4()
{
}

void Laborator4::Init()
{
	polygonMode = GL_FILL;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	// initialize tx, ty and tz (the translation steps)
	translateX = 0;
	translateY = 0;
	translateZ = 0;

	// initialize sx, sy and sz (the scale factors)
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	
	// initialize angularSteps
	angularStepOX = 0;
	angularStepOY = 0;
	angularStepOZ = 0;

	x = -2.5f;
	y = 0.5f;
	z = -1.5f;
	up = 0;
	jump = 0;
	back = 0;
	angle = 0;
	jumps = 0;
}

void Laborator4::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator4::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(x, y, z);
	modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0.0f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::Scale(scaleX, scaleY, scaleZ);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(2.5f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::RotateOX(angularStepOX);
	modelMatrix *= Transform3D::RotateOY(angularStepOY);
	modelMatrix *= Transform3D::RotateOZ(angularStepOZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	
	
	angle += 0.5 * deltaTimeSeconds;
	modelMatrix *= Transform3D::Translate(10*jumps, 0.0f, 0.0f);
	modelMatrix *= Transform3D::Translate(5.0f, 0.0f, 0.0f);
	modelMatrix *= Transform3D::RotateOZ(jump);
	modelMatrix *= Transform3D::Translate(-5.0f, 0.0f, 0.0f);
	//modelMatrix *= Transform3D::Translate(bonusX, jump, 0);
	//modelMatrix *= Transform3D::RotateOZ(angle);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Laborator4::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator4::OnInputUpdate(float deltaTime, int mods)
{
	// TODO
	if (window->KeyHold(GLFW_KEY_W)) {
		z -= 3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_A)) {
		x -= 3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_S)) {
		z += 3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_D)) {
		x += 3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_R)) {
		y += 3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_F)) {
		y -= 3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_1)) {
		scaleX += 2 * deltaTime;
		scaleY += 2 * deltaTime;
		scaleZ += 2 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_2)) {
		scaleX -= 2 * deltaTime;
		scaleY -= 2 * deltaTime;
		scaleZ -= 2 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_3)) {
		angularStepOX += 2 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_4)) {
		angularStepOX -= 2 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_5)) {
		angularStepOY += 2 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_6)) {
		angularStepOY -= 2 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_7)) {
		angularStepOZ += 2 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_8)) {
		angularStepOZ -= 2 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_9)) {
		if (jump <= M_PI * (-1)) {
			jump = 0;
			jumps++;
		}
		jump -= 0.67 *deltaTime;
	}

}

void Laborator4::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Laborator4::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator4::OnWindowResize(int width, int height)
{
}
