// Mirciu Andrei-Constantin 336CB
#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace MyObject2D
{
	Mesh* CreateTriangle(std::string name, std::vector<VertexFormat> vertices, std::vector<unsigned short> indices);
	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color);
	Mesh* CreateBird(std::string name);
	Mesh* CreateRectangle(std::string name, std::vector<VertexFormat> vertices, std::vector<unsigned short> indices);
	Mesh* CreateCloud(std::string name);
}

