// Mirciu Andrei-Constantin 336CB
#pragma once

#include <Component/SimpleScene.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	float translateX, translateY; // pentru pasare
	float angularStep; // pentru pasare
	int getBack; // pentru aripi
	float moveX; //pentru aripi
	float moveY; //pentru aripi

	float translateXObstacle1;
	float translateXObstacle2;
	float translateXObstacle3;
	float translateXObstacle4;
	float translateXObstacle5;

	float scaleYObstacle1up;
	float scaleYObstacle1down;
	float scaleYObstacle2up;
	float scaleYObstacle2down;
	float scaleYObstacle3up;
	float scaleYObstacle3down;
	float scaleYObstacle4up;
	float scaleYObstacle4down;
	float scaleYObstacle5up;
	float scaleYObstacle5down;

	float randomNumber;
	glm::ivec2 resolution;
	int collisionDetected; // 0 inseamna ca nu am coliziune, 1 inseamna coliziune
	int score; // scorul curent
	int increaseScore; // 0 inseamna ca scorul ramane acelasi, 1 inseamna ca trebuie sa incrementez
	float r, g, b; // pentru zi/noapte
	int changeColor;
	float translateYsun, translateYmoon;
	bool wings = true;
	int gameOver;
};
