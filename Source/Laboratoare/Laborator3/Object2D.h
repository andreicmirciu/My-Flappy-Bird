#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateTriangle(std::string name, std::vector<VertexFormat> vertices, std::vector<unsigned short> indices);
	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color);
	Mesh* CreateBird(const char *name);
	Mesh* CreateRectangle(std::string name, std::vector<VertexFormat> vertices, std::vector<unsigned short> indices);
	Mesh* CreateCloud(std::string name);
}

