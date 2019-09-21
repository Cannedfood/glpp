#include "Utils.hpp"

#include "thirdparty/tiny_obj_loader.h"
#include "thirdparty/stb_image.h"

#include <memory.h>


void Mesh::load(const char* path) {
	using namespace tinyobj;

	std::string error;
	attrib_t attribs;
	std::vector<shape_t> shapes;
	std::vector<material_t> materials;

	if(!LoadObj(&attribs, &shapes, &materials, &error, path))
		throw std::runtime_error("Failed loading " + std::string(path) + ": " + error);

	glm::vec3 const* positions = attribs.vertices.empty() ? nullptr : (glm::vec3 const*)attribs.vertices.data();
	glm::vec3 const* normals   = attribs.normals.empty() ? nullptr : (glm::vec3 const*)attribs.normals.data();
	glm::vec2 const* texcoords = attribs.texcoords.empty() ? nullptr : (glm::vec2 const*)attribs.texcoords.data();
	for(auto& shape : shapes) {
		for(auto& index : shape.mesh.indices) {
			if(positions) this->positions.emplace_back(positions[index.vertex_index]);
			if(normals)   this->normals.emplace_back(normals[index.normal_index]);
			if(texcoords) this->texcoords.emplace_back(texcoords[index.texcoord_index]);
			indices.emplace_back(this->positions.size() - 1);
		}
	}

	if(!normals) {
		calcNormals();
	}

	compress();
}

void Mesh::calcNormals() {
	normals.resize(positions.size());
	std::fill(std::begin(normals), std::end(normals), glm::vec3(0));

	for(size_t i = 0; i < positions.size(); i += 3) {
		auto& p0 = positions[i + 0];
		auto& p1 = positions[i + 1];
		auto& p2 = positions[i + 2];

		auto d1 = p1 - p0;
		auto d2 = p2 - p0;

		auto normal = glm::cross(d1, d2);
		normals[i + 0] += normal;
		normals[i + 1] += normal;
		normals[i + 2] += normal;
	}

	for(auto& n : normals) n = glm::normalize(n);
}

void Mesh::compress() {
	struct Vertex {
		glm::vec3 pos;
		glm::vec3 norm;
		glm::vec2 tex;

		inline
		bool operator<(Vertex const& v) const noexcept {
			return memcmp(this, &v, sizeof(Vertex)) < 0;
		}
	};

	std::map<Vertex, uint32_t> verts;

	this->indices.clear();
	this->indices.reserve(this->indices.size());

	Mesh md;

	Vertex v;
	for(size_t i = 0; i < this->positions.size(); i++) {
		v.pos = this->positions[i];
		if(!this->normals.empty())
			v.norm = this->normals[i];
		// if(!this->tangents.empty())
		// 	v.tan = this->tangents[i];
		if(!this->texcoords.empty())
			v.tex = this->texcoords[i];

		auto iter = verts.find(v);
		if(iter != verts.end()) {
			md.indices.emplace_back(iter->second);
		}
		else {
			uint32_t idx = verts.size();

			verts.emplace_hint(iter, v, idx);

			md.indices.emplace_back(idx);
			md.positions.emplace_back(v.pos);
			if(!normals.empty())
				md.normals.emplace_back(v.norm);
			// if(!mTangents.empty())
			// 	md.mTangents.emplace_back(v.tan);
			if(!texcoords.empty())
				md.texcoords.emplace_back(v.tex);
		}
	}

	*this = std::move(md);
}

bool Image::load(const char* path) {
	int x, y, c;
	auto data = std::unique_ptr<uint8_t, void(*)(void*)>(
		stbi_load(path, &x, &y, &c, STBI_default),
		stbi_image_free
	);

	if(!data) return false;

	this->data = std::move(data);
	width  = x;
	height = y;
	numComponents = c;

	return true;
}

#include <fstream>

std::vector<char> loadFileData(char const* path) {
	std::ifstream file(path);
	if(!file) throw std::runtime_error(std::string("Failed opening ") + path);
	file.seekg(0, std::ios::end);
	std::vector<char> result(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(result.data(), result.size());
	return result;
}
std::string       loadFileString(char const* path) {
	std::ifstream file(path);
	if(!file) throw std::runtime_error(std::string("Failed opening ") + path);
	file.seekg(0, std::ios::end);
	std::string result (file.tellg(), ' ');
	file.seekg(0, std::ios::beg);
	file.read(result.data(), result.size());
	return result;
}

#include <chrono>
using namespace std::chrono;
using namespace std::chrono_literals;

double now() {
	return duration_cast<duration<double>>(steady_clock::now().time_since_epoch()).count();
}
