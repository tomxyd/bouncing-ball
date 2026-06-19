#ifndef SPHERE_H
#define SPHERE_H
#include <cmath>
#include <glm/glm.hpp>
#include <vector>

class Sphere {
private:
	int numVertices = 0;
	int numIndices = 0;
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	void init(int precision);
	float toRadians(float degrees);

public:
	Sphere() {}
	Sphere(int precision) { init(precision); }
	int getNumVertices() { return numVertices; }
	int getNumIndices() { return numIndices; }
	std::vector<int> getIndices() { return indices; }
	std::vector<glm::vec3> getVertices() { return vertices; }
	std::vector<glm::vec2> getTexCoords() { return texCoords; }
	std::vector<glm::vec3> getNormals() { return normals; }
};

#endif