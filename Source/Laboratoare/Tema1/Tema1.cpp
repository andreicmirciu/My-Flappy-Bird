// Mirciu Andrei-Constantin 336CB
#include "Tema1.h"
#include "MyObject2D.h"
#include "MyTransform2D.h"

#include <vector>
#include <iostream>
#include<stdlib.h>
#include <ctime>
#include<math.h>

#include <Core/Engine.h>

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// coordonatele de translatie ale pasarii
	translateX = resolution.x / 6.4f;
	translateY = resolution.y / 3.6f;

	angularStep = 0; // variabila folosita pentru rotatia pasarii
	
	// variabila ce imi spune cand translatia aripilor pasarii trebuie sa
	// "mearga" inainte sau inapoi
	getBack = 0;

	// coordonatele de translatie ale aripilor
	moveX = 0;
	moveY = 0;

	// variabila ce imi spune daca a avut loc o coliziune (1 pentru coliziune)
	collisionDetected = 0;

	score = 0;
	cout << endl << endl << "\t\t********  GAME STATISTICS  ********" << endl;
	cout << endl << "Current score is " << score << "." << endl;

	// variabile ce imi spune daca trebuie sa incrementez scorul
	increaseScore = 0;

	// variabila ce imi spune daca s-a terminat jocul
	gameOver = 0;

	// coordonatele de translatie initiale pentru soare si luna
	translateYsun = 0;
	translateYmoon = -1000;

	// coordonatele de translatie initiale pentru cele 5 obstacole
	translateXObstacle1 = (float)resolution.x;
	translateXObstacle2 = translateXObstacle1 + ((float)resolution.x / 3);
	translateXObstacle3 = translateXObstacle2 + ((float)resolution.x / 3);
	translateXObstacle4 = translateXObstacle3 + ((float)resolution.x / 3);
	translateXObstacle5 = translateXObstacle4 + ((float)resolution.x / 3);

	srand(static_cast<unsigned>(time(NULL)));

	// generarea random a factorului de scalare ale obstacolelor
	scaleYObstacle1up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
	randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle1up * 9) / 9) + 1;
	scaleYObstacle1down = (float) ((rand() % ((int)randomNumber + 1)) + 1);
	// in cazul in care nu este suficient loc pentru a permite trecerea pasarii, recalculez
	// factorii de scalare
	if ((float)resolution.y - (scaleYObstacle1down * 9 - scaleYObstacle1up * 9) < resolution.y / 6) {
		scaleYObstacle1up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
		randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle1up * 9) / 9) + 1;
		scaleYObstacle1down = (float)((rand() % ((int)randomNumber + 1)) + 1);
	}

	scaleYObstacle2up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
	randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle2up * 9) / 9) + 1;
	scaleYObstacle2down = (float)((rand() % ((int)randomNumber + 1)) + 1);
	if ((float)resolution.y - (scaleYObstacle2down * 9 - scaleYObstacle2up * 9) < resolution.y / 6) {
		scaleYObstacle2up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
		randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle2up * 9) / 9) + 1;
		scaleYObstacle2down = (float)((rand() % ((int)randomNumber + 1)) + 1);
	}

	scaleYObstacle3up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
	randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle3up * 9) / 9) + 1;
	scaleYObstacle3down = (float)((rand() % ((int)randomNumber + 1)) + 1);
	if ((float)resolution.y - (scaleYObstacle3down * 9 - scaleYObstacle3up * 9) < resolution.y / 6) {
		scaleYObstacle3up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
		randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle3up * 9) / 9) + 1;
		scaleYObstacle3down = (float)((rand() % ((int)randomNumber + 1)) + 1);
	}

	scaleYObstacle4up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
	randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle4up * 9) / 9) + 1;
	scaleYObstacle4down = (float)((rand() % ((int)randomNumber + 1)) + 1);
	if ((float)resolution.y - (scaleYObstacle4down * 9 - scaleYObstacle4up * 9) < resolution.y / 6) {
		scaleYObstacle4up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
		randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle4up * 9) / 9) + 1;
		scaleYObstacle4down = (float)((rand() % ((int)randomNumber + 1)) + 1);
	}

	scaleYObstacle5up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
	randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle5up * 9) / 9) + 1;
	scaleYObstacle5down = (float)((rand() % ((int)randomNumber + 1)) + 1);
	if ((float)resolution.y - (scaleYObstacle5down * 9 - scaleYObstacle5up * 9) < resolution.y / 6) {
		scaleYObstacle5up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
		randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle5up * 9) / 9) + 1;
		scaleYObstacle5down = (float)((rand() % ((int)randomNumber + 1)) + 1);
	}

	vector<VertexFormat> obstacleVertices
	{
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.59f, 0.98f, 0.59f)),
		VertexFormat(glm::vec3(5, 0, 0), glm::vec3(0.13, 0.54f, 0.13f)),
		VertexFormat(glm::vec3(5, 9, 0), glm::vec3(0.13, 0.54f, 0.13f)),
		VertexFormat(glm::vec3(0, 9, 0), glm::vec3(0.59f, 0.98f, 0.59f)),
	};

	vector<unsigned short> obstacleIndices
	{
			0, 1, 2,
			0, 2, 3,
	};

	vector<VertexFormat> wingsVertices
	{
		VertexFormat(glm::vec3(1, 5, 0), glm::vec3(1, 0.9, 0.8)),
		VertexFormat(glm::vec3(5, 6, 0), glm::vec3(1, 0.9, 0.8)),
		VertexFormat(glm::vec3(7, 1, 0), glm::vec3(1, 0.9, 0.8))
	};

	vector<unsigned short> wingsIndices = { 0, 1, 2 };

	vector<VertexFormat> groundVertices
	{
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.36f, 0.31f, 0.24f)),
		VertexFormat(glm::vec3(5, 0, 0), glm::vec3(0.36f, 0.31f, 0.24f)),
		VertexFormat(glm::vec3(5, 5, 0), glm::vec3(0.36f, 0.31f, 0.24f)),
		VertexFormat(glm::vec3(0, 5, 0), glm::vec3(0.34f, 0.25f, 0.14f)),
	};

	vector<unsigned short> groundIndices
	{
			0, 1, 2,
			0, 2, 3,
	};

	vector<VertexFormat> grassVertices
	{
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.49f, 0.78f, 0.31f)),
		VertexFormat(glm::vec3(5, 0, 0), glm::vec3(0.49f, 0.78f, 0.31f)),
		VertexFormat(glm::vec3(5, 5, 0), glm::vec3(0.49f, 0.78f, 0.31f)),
		VertexFormat(glm::vec3(0, 5, 0), glm::vec3(0.49f, 0.78f, 0.31f)),
	};

	vector<unsigned short> grassIndices
	{
			0, 1, 2,
			0, 2, 3,
	};

	// creez pasarea
	Mesh* pasare = MyObject2D::CreateBird("pasare");
	AddMeshToList(pasare);

	// creez aripile
	Mesh* aripi = MyObject2D::CreateTriangle("aripi", wingsVertices, wingsIndices);
	AddMeshToList(aripi);

	// creez obiectul de tip obstacol
	Mesh* obstacle = MyObject2D::CreateRectangle("obstacle", obstacleVertices, obstacleIndices);
	AddMeshToList(obstacle);

	// creez Soarele
	Mesh* sun = MyObject2D::CreateCircle("sun", glm::vec3(0, 0, 0), 100, glm::vec3(1, 1, 0.2f));
	AddMeshToList(sun);

	// creez Luna
	Mesh* moon = MyObject2D::CreateCircle("moon", glm::vec3(0, 0, 0), 60, glm::vec3(0.95f, 0.95f, 0.78f));
	AddMeshToList(moon);

	// creez pamantul
	Mesh* ground = MyObject2D::CreateRectangle("ground", groundVertices, groundIndices);
	AddMeshToList(ground);

	// creez iarba
	Mesh* grass = MyObject2D::CreateRectangle("grass", grassVertices, grassIndices);
	AddMeshToList(grass);

	// creez norul
	Mesh* cloud = MyObject2D::CreateCloud("cloud");
	AddMeshToList(cloud);

	// culorile initiale ale fundalului
	r = 0;
	g = 0.89;
	b = 1;
	
}

void Tema1::FrameStart()
{
	glClearColor(r, g, b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{

	if (changeColor == 0) { // trebuie sa fac noapte
		r += 0.02f * deltaTimeSeconds * 0.2f;
		g -= 0.10f * deltaTimeSeconds * 0.2f;
		b -= 0.09f * deltaTimeSeconds * 0.2f;
	}
	if (changeColor == 1) { // trebuie sa fac zi
		r -= 0.02f * deltaTimeSeconds * 0.2f;
		g += 0.10f * deltaTimeSeconds * 0.2f;
		b += 0.09f * deltaTimeSeconds * 0.2f;
	}
	if (r >= 0.14 && g <= 0.18 && b <= 0.34) { // trebuie sa fac zi
		r -= 0.02f * deltaTimeSeconds * 0.2f;
		g += 0.10f * deltaTimeSeconds * 0.2f;
		b += 0.09f * deltaTimeSeconds * 0.2f;
		changeColor = 1;
	}
	if (r <= 0 && g >= 0.89 && b >= 1) { // trebuie sa fac noapte
		r += 0.02f * deltaTimeSeconds * 0.2f;
		g -= 0.10f * deltaTimeSeconds * 0.2f;
		b -= 0.09f * deltaTimeSeconds * 0.2f;
		changeColor = 0;
	}

	// verific daca pasarea se loveste de marginile ecranului
	if (translateY > resolution.y - 30 || translateY < 0) {
		collisionDetected = 1;
		if (gameOver == 0) {
			cout << endl << "\t\t********  GAME OVER! Score: " << score << "  ********" << endl;
			gameOver = 1;
		}
	}

	// translatiile pe Oy pentru Soare/Luna
	translateYsun += 35 * deltaTimeSeconds;
	translateYmoon += 35 * deltaTimeSeconds;

	// conditiile de reaparitie in ecran pentru Soare/Luna
	if (translateYsun > translateYmoon + resolution.y / 1.2f && translateYsun > resolution.y + resolution.y / 3.6f) {
		translateYsun = translateYmoon - resolution.y - resolution.y / 2.57f;
	}

	if (translateYmoon > resolution.y + resolution.y / 2.4f) {
		translateYmoon = translateYsun - resolution.y - resolution.y / 2.57f;
	}

	// daca nu am coliziune, animatiile functioneaza normal
	if (collisionDetected != 1) {
		translateY -= deltaTimeSeconds * 190; // pasarea cade
		angularStep -= deltaTimeSeconds * 0.4f; // pasarea tinde sa se rastoarne
		// limita pana la care se poate inclina pasarea
		if (angularStep < -M_PI / 4) {
			angularStep += deltaTimeSeconds * 2;
		}
		if (wings) {
			wings = false;
		}
		else {
			if (getBack == 0) {
				moveX += deltaTimeSeconds * 10;
				moveY += deltaTimeSeconds * 10;
			}
			else {
				moveX -= deltaTimeSeconds * 10;
				moveY -= deltaTimeSeconds * 10;
			}
		}

		if (moveX > 0.8f) {
			getBack = 1;
		}

		if (moveX < 0) {
			getBack = 0;
		}

		// modificarea dificultatii jocului in functie de scor
		if (score <= 10) {
			translateXObstacle1 -= deltaTimeSeconds * 150;
			translateXObstacle2 -= deltaTimeSeconds * 150;
			translateXObstacle3 -= deltaTimeSeconds * 150;
			translateXObstacle4 -= deltaTimeSeconds * 150;
			translateXObstacle5 -= deltaTimeSeconds * 150;
		}

		if (score > 10 && score <= 20) {
			translateXObstacle1 -= deltaTimeSeconds * 200;
			translateXObstacle2 -= deltaTimeSeconds * 200;
			translateXObstacle3 -= deltaTimeSeconds * 200;
			translateXObstacle4 -= deltaTimeSeconds * 200;
			translateXObstacle5 -= deltaTimeSeconds * 200;
		}

		if (score > 20) {
			translateXObstacle1 -= deltaTimeSeconds * 250;
			translateXObstacle2 -= deltaTimeSeconds * 250;
			translateXObstacle3 -= deltaTimeSeconds * 250;
			translateXObstacle4 -= deltaTimeSeconds * 250;
			translateXObstacle5 -= deltaTimeSeconds * 250;
		}
	}

	// desenarea aripilor
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateX, translateY);
	modelMatrix *= Transform2D::Scale(5, 7);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(-7.5, -2.5); // centrul de greutate
	modelMatrix *= Transform2D::Translate(moveX, moveY);
	RenderMesh2D(meshes["aripi"], shaders["VertexColor"], modelMatrix);
	
	// desenarea pasarii
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateX, translateY);
	modelMatrix *= Transform2D::Scale(5, 7);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(-7.5, -2.5); // centrul de greutate
	RenderMesh2D(meshes["pasare"], shaders["VertexColor"], modelMatrix);

	// daca pasarea a trecut cu succes de obstacol si acesta a disparut din scena,
	// il resetez si recalculez factorii de scalare
	if (translateXObstacle1 < -((float)resolution.x / 35) * 5 && increaseScore == 1) {
		score++;
		cout << "Current score is " << score << "." << endl;
		increaseScore = 0;
		srand(static_cast <unsigned>(time(NULL)));
		translateXObstacle1 = translateXObstacle5 + ((float)resolution.x / 3);
		scaleYObstacle1up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
		randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle1up * 9) / 9) + 1;
		scaleYObstacle1down = (float)((rand() % ((int)randomNumber + 1)) + 1);
		if ((float)resolution.y - (scaleYObstacle1down * 9 - scaleYObstacle1up * 9) < resolution.y / 6) {
			randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle1up * 9) / 9) + 1;
			scaleYObstacle1down = (float)((rand() % ((int)randomNumber + 1)) + 1);
		}
	}

	// verific daca are loc o coliziune
 	if ((resolution.x / 6.4f >= translateXObstacle1 - 30) &&
		(resolution.x / 6.4f <= translateXObstacle1 + (resolution.x / 35) * 9 - 100) &&
		(translateY +25 > resolution.y + 9 * scaleYObstacle1up ||
			translateY < 9 * scaleYObstacle1down)) {
		collisionDetected = 1;
		if (gameOver == 0) {
			cout << endl << "\t\t********  GAME OVER! Score: " << score << "  ********" << endl;
			gameOver = 1;
		}
	}

	// verific daca trebuie incrementat scorul
	if ((resolution.x / 6.4f >= translateXObstacle1 - 30) &&
		(resolution.x / 6.4f <= translateXObstacle1 + (resolution.x / 35) * 9 - 100) && collisionDetected != 1) {
		increaseScore = 1;
	}

	if (translateXObstacle2 < -((float)resolution.x / 35) * 5 && increaseScore == 1) {
		score++;
		cout << "Current score is " << score << "." << endl;
		increaseScore = 0;
		srand(static_cast <unsigned>(time(NULL)));
		translateXObstacle2 = translateXObstacle1 + ((float)resolution.x / 3);
		scaleYObstacle2up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
		randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle2up * 9) / 9) + 1;
		scaleYObstacle2down = (float) ((rand() % ((int)randomNumber + 1)) + 1);
		if ((float)resolution.y - (scaleYObstacle2down * 9 - scaleYObstacle2up * 9) < resolution.y / 6) {
			randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle2up * 9) / 9) + 1;
			scaleYObstacle2down = (float) ((rand() % ((int)randomNumber + 1)) + 1);
		}
	}
	if ((resolution.x / 6.4f >= translateXObstacle2 - 30) &&
		(resolution.x / 6.4f <= translateXObstacle2 + (resolution.x / 35) * 9 - 100) &&
		(translateY + 25 > resolution.y + 9 * scaleYObstacle2up || 
			translateY < 9 * scaleYObstacle2down)) {
		collisionDetected = 1;
		if (gameOver == 0) {
			cout << endl << "\t\t********  GAME OVER! Score: " << score << "  ********" << endl;
			gameOver = 1;
		}
	}

	if ((resolution.x / 6.4f >= translateXObstacle2 - 30) &&
		(resolution.x / 6.4f <= translateXObstacle2 + (resolution.x / 35) * 9 - 100) && collisionDetected != 1) {
		increaseScore = 1;
	}

	if (translateXObstacle3 < -((float)resolution.x / 35) * 5 && increaseScore == 1) {
		score++;
		cout << "Current score is " << score << "." << endl;
		increaseScore = 0;
		srand(static_cast <unsigned>(time(NULL)));
		translateXObstacle3 = translateXObstacle2 + ((float)resolution.x / 3);
		scaleYObstacle3up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
		randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle3up * 9) / 9) + 1;
		scaleYObstacle3down = (float)((rand() % ((int)randomNumber + 1)) + 1);
		if ((float)resolution.y - (scaleYObstacle3down * 9 - scaleYObstacle3up * 9) < resolution.y / 6) {
			randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle3up * 9) / 9) + 1;
			scaleYObstacle3down = (float)((rand() % ((int)randomNumber + 1)) + 1);
		}
	}

	if ((resolution.x / 6.4f >= translateXObstacle3 - 30) &&
		(resolution.x / 6.4f <= translateXObstacle3 + (resolution.x / 35) * 9 - 100) &&
		(translateY + 25 > resolution.y + 9 * scaleYObstacle3up ||
			translateY < 9 * scaleYObstacle3down)) {
		collisionDetected = 1;
		if (gameOver == 0) {
			cout << endl << "\t\t********  GAME OVER! Score: " << score << "  ********" << endl;
			gameOver = 1;
		}
	}

	if ((resolution.x / 6.4f >= translateXObstacle3 - 30) &&
		(resolution.x / 6.4f <= translateXObstacle3 + (resolution.x / 35) * 9 - 100) && collisionDetected != 1) {
		increaseScore = 1;
	}

	if (translateXObstacle4 < -((float)resolution.x / 35) * 5 && increaseScore == 1) {
		score++;
		cout << "Current score is " << score << "." << endl;
		increaseScore = 0;
		srand(static_cast <unsigned>(time(NULL)));
		translateXObstacle4 = translateXObstacle3 + ((float)resolution.x / 3);
		scaleYObstacle4up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
		randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle4up * 9) / 9) + 1;
		scaleYObstacle4down = (float)((rand() % ((int)randomNumber + 1)) + 1);
		if ((float)resolution.y - (scaleYObstacle4down * 9 - scaleYObstacle4up * 9) < resolution.y / 6) {
			randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle4up * 9) / 9) + 1;
			scaleYObstacle4down = (float)((rand() % ((int)randomNumber + 1)) + 1);
		}
	}

	if ((resolution.x / 6.4f >= translateXObstacle4 - 30) &&
		(resolution.x / 6.4f <= translateXObstacle4 + (resolution.x / 35) * 9 - 100) &&
		(translateY + 25 > resolution.y + 9 * scaleYObstacle4up ||
			translateY < 9 * scaleYObstacle4down)) {
		collisionDetected = 1;
		if (gameOver == 0) {
			cout << endl << "\t\t********  GAME OVER! Score: " << score << "  ********" << endl;
			gameOver = 1;
		}
	}

	if ((resolution.x / 6.4f >= translateXObstacle4 - 30) &&
		(resolution.x / 6.4f <= translateXObstacle4 + (resolution.x / 35) * 9 - 100) && collisionDetected != 1) {
		increaseScore = 1;
	}

	if (translateXObstacle5 < -((float)resolution.x / 35) * 5 && increaseScore == 1) {
		score++;
		cout << "Current score is " << score << "." << endl;
		increaseScore = 0;
		srand(static_cast <unsigned>(time(NULL)));
		translateXObstacle5 = translateXObstacle4 + ((float)resolution.x / 3);
		scaleYObstacle5up = -((float)((rand() % ((resolution.y - resolution.y / 6) / 9 + 1)) + 1));
		randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle5up * 9) / 9) + 1;
		scaleYObstacle5down = (float)((rand() % ((int)randomNumber + 1)) + 1);
		if ((float)resolution.y - (scaleYObstacle5down * 9 - scaleYObstacle5up * 9) < resolution.y / 6) {
			randomNumber = (((float)resolution.y - resolution.y / 6 + scaleYObstacle5up * 9) / 9) + 1;
			scaleYObstacle5down = (float)((rand() % ((int)randomNumber + 1)) + 1);
		}
	}

	if ((resolution.x / 6.4f >= translateXObstacle5 - 30) &&
		(resolution.x / 6.4f <= translateXObstacle5 + (resolution.x / 35) * 9 - 100) &&
		(translateY + 25 > resolution.y + 9 * scaleYObstacle5up ||
			translateY < 9 * scaleYObstacle5down)) {
		collisionDetected = 1;
		if (gameOver == 0) {
			cout << endl << "\t\t********  GAME OVER! Score: " << score << "  ********" << endl;
			gameOver = 1;
		}
	}

	if ((resolution.x / 6.4f >= translateXObstacle5 - 30) &&
		(resolution.x / 6.4f <= translateXObstacle5 + (resolution.x / 35) * 9 - 100) && collisionDetected != 1) {
		increaseScore = 1;
	}

	//----------------------------------- Prima pereche de obstacole
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXObstacle1, (float)resolution.y);
	modelMatrix *= Transform2D::Scale((float)resolution.x / 35, scaleYObstacle1up);
	RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXObstacle1, 0);
	modelMatrix *= Transform2D::Scale((float)resolution.x / 35, scaleYObstacle1down);
	RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
	
	//----------------------------------- A doua pereche de obstacole
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXObstacle2, (float)resolution.y);
	modelMatrix *= Transform2D::Scale((float)resolution.x / 35, scaleYObstacle2up);
	RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXObstacle2, 0);
	modelMatrix *= Transform2D::Scale((float)resolution.x / 35, scaleYObstacle2down);
	RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);

	//----------------------------------- A treia pereche de obstacole
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXObstacle3, (float)resolution.y);
	modelMatrix *= Transform2D::Scale((float)resolution.x / 35, scaleYObstacle3up);
	RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXObstacle3, 0);
	modelMatrix *= Transform2D::Scale((float)resolution.x / 35, scaleYObstacle3down);
	RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);

	//----------------------------------- A patra pereche de obstacole
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXObstacle4, (float)resolution.y);
	modelMatrix *= Transform2D::Scale((float)resolution.x / 35, scaleYObstacle4up);
	RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXObstacle4, 0);
	modelMatrix *= Transform2D::Scale((float)resolution.x / 35, scaleYObstacle4down);
	RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);

	//----------------------------------- A cincea pereche de obstacole
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXObstacle5, (float)resolution.y);
	modelMatrix *= Transform2D::Scale((float)resolution.x / 35, scaleYObstacle5up);
	RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXObstacle5, 0);
	modelMatrix *= Transform2D::Scale((float)resolution.x / 35, scaleYObstacle5down);
	RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
	
	// desenez cei trei nori
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x / 2.56f, resolution.y / 1.44f);
	modelMatrix *= Transform2D::Scale(20, 10);
	RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x / 8.5f, resolution.y / 1.6f);
	modelMatrix *= Transform2D::Scale(20, 10);
	RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x / 1.347f, resolution.y / 1.8f);
	modelMatrix *= Transform2D::Scale(20, 10);
	RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

	// desenez Soarele
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x / 1.82f, translateYsun);
	modelMatrix *= Transform2D::Scale(2, 2);
	RenderMesh2D(meshes["sun"], shaders["VertexColor"], modelMatrix);

	// desenez Luna
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x / 1.82f, translateYmoon);
	modelMatrix *= Transform2D::Scale(2, 2);
	RenderMesh2D(meshes["moon"], shaders["VertexColor"], modelMatrix);

	// desenez pamantul
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, 0);
	modelMatrix *= Transform2D::Scale(resolution.x, 3);
	RenderMesh2D(meshes["ground"], shaders["VertexColor"], modelMatrix);

	// desenez iarba
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, 3);
	modelMatrix *= Transform2D::Scale(resolution.x, 8);
	RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);
}

void Tema1::FrameEnd()
{
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (window -> KeyHold(GLFW_KEY_SPACE)) {
		// ma pot misca atat timp cat nu am coliziune
		if (collisionDetected != 1) {
			translateY += deltaTime * 540; // pasarea urca
			angularStep += deltaTime * 2; // pasarea tinde sa urce
			// pasarea nu se poate inclina mai mult de atat
			if (angularStep > M_PI / 30) {
				angularStep -= deltaTime * 2;
			}
		}
	}
};

void Tema1::OnKeyPress(int key, int mods)
{
	// key press event
};

void Tema1::OnKeyRelease(int key, int mods)
{
	// key release event
};

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// mouse move event
};

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// mouse button press event
};

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// mouse scroll event
}

void Tema1::OnWindowResize(int width, int height)
{
	// window resize event
}