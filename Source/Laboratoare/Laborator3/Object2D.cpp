#include "Object2D.h"

#include <Core/Engine.h>
#include <math.h>
#include <GL/glew.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateTriangle(std::string name, std::vector<VertexFormat> vertices, std::vector<unsigned short> indices)
{

	Mesh* triangle = new Mesh(name);
	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	float x, y, angle = 0;
	vertices.push_back(VertexFormat(center, color));

	while (angle <= 6.5) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		vertices.push_back(VertexFormat(glm::vec3(x, y, 0) + center, color));
		angle += 0.1f;
	}

	for (int i = 1; i < vertices.size() - 1; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	Mesh* circle = new Mesh(name);
	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Object2D::CreateBird(const char *name) 
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.9, 0.5, 1)),
		VertexFormat(glm::vec3(2, 0, 0), glm::vec3(1, 0.8, 0.2)),
		VertexFormat(glm::vec3(2, 2, 0), glm::vec3(1, 0.8, 0.2)),
		VertexFormat(glm::vec3(8, 1, 0), glm::vec3(1, 0.7, 0.4)),
		VertexFormat(glm::vec3(8, 3, 0), glm::vec3(1, 0.7, 0.4)),
		VertexFormat(glm::vec3(10, 3, 0), glm::vec3(1, 0.7, 0.4)),
		VertexFormat(glm::vec3(9, 4.8, 0), glm::vec3(1, 1, 0.9)),
		VertexFormat(glm::vec3(12, 6, 0), glm::vec3(0.7, 0, 0)),
		VertexFormat(glm::vec3(12, 4.5, 0), glm::vec3(0.7, 0, 0)),
		VertexFormat(glm::vec3(13.5, 5, 0), glm::vec3(0.7, 0, 0)),
		//VertexFormat(glm::vec3(1, 5, 0), glm::vec3(1, 0.9, 0.8)),
		//VertexFormat(glm::vec3(5, 6, 0), glm::vec3(1, 0.9, 0.8)),
		//VertexFormat(glm::vec3(7, 1, 0), glm::vec3(1, 0.9, 0.8)),
	};

	std::vector<unsigned short> indices = 
	{
		0, 1, 2,
		1, 2, 4,
		1, 3, 4,
		//10, 11, 12,
		3, 4, 6,
		3, 5, 6,
		5, 6, 8,
		6, 7, 8,
		7, 8, 9
	};

	Mesh* bird = new Mesh(name);
	bird->SetDrawMode(GL_TRIANGLES);
	bird->InitFromData(vertices, indices);
	return bird;
}

Mesh* Object2D::CreateRectangle(std::string name, std::vector<VertexFormat> vertices, std::vector<unsigned short> indices)
{
	Mesh* rectangle = new Mesh(name);
	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Object2D::CreateCloud(std::string name) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(2, 3, 0), glm::vec3(0.76f, 0.76f, 0.76f)),
		VertexFormat(glm::vec3(4, 4, 0), glm::vec3(0.95f, 0.95f, 0.95f)),
		VertexFormat(glm::vec3(5, 5, 0), glm::vec3(0.95f, 0.95f, 0.95f)),
		VertexFormat(glm::vec3(6, 4, 0), glm::vec3(0.76f, 0.76f, 0.76f)),
		VertexFormat(glm::vec3(7, 6, 0), glm::vec3(0.95f, 0.95f, 0.95f)),
		VertexFormat(glm::vec3(8, 6, 0), glm::vec3(0.95f, 0.95f, 0.95f)),
		VertexFormat(glm::vec3(9, 8, 0), glm::vec3(0.95f, 0.95f, 0.95f)),
		VertexFormat(glm::vec3(10, 7, 0), glm::vec3(0.95f, 0.95f, 0.95f)),
		VertexFormat(glm::vec3(11, 4, 0), glm::vec3(0.76f, 0.76f, 0.76f)),
		VertexFormat(glm::vec3(12, 3, 0), glm::vec3(0.88f, 0.88f, 0.88f)),
		VertexFormat(glm::vec3(13, 0, 0), glm::vec3(0.76f, 0.76f, 0.76f)),
		VertexFormat(glm::vec3(12, -1, 0), glm::vec3(0.76f, 0.76f, 0.76f)),
		VertexFormat(glm::vec3(13, -4, 0), glm::vec3(0.76f, 0.76f, 0.76f)),
		VertexFormat(glm::vec3(2, -4, 0), glm::vec3(0.88f, 0.88f, 0.88f)),
		VertexFormat(glm::vec3(1, -2, 0), glm::vec3(0.76f, 0.76f, 0.76f)),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8,9, 10, 11, 12, 13, 14
	};

	Mesh* cloud = new Mesh(name);
	cloud->SetDrawMode(GL_POLYGON);
	cloud->InitFromData(vertices, indices);
	return cloud;
}