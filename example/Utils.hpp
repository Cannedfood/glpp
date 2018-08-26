#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

struct Mesh {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<uint16_t>  indices;

	void load(const char* path);
	void calcNormals();
	void compress();
};

struct Image {
	std::unique_ptr<uint8_t, void(*)(void*)> data;
	unsigned width, height;
	unsigned numComponents;

	Image() : data(nullptr, nullptr) {}

	bool load(const char* path);
};

std::vector<char> loadFileData(char const* path);
std::string       loadFileString(char const* path);

double now();