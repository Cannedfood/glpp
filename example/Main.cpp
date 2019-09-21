#include <glpp.hpp>
#include <GLFW/glfw3.h>

#include "Utils.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

using namespace gl;

unsigned windowWidth  = 800;
unsigned windowHeight = 600;

void mainLoop(GLFWwindow* window) {
	gl::Program shader3d = {
		gl::VertexShader  (loadFileString("example/Shader3d.vert")),
		gl::FragmentShader(loadFileString("example/Shader3d.frag"))
	};

	gl::Program shaderFilter = {
		gl::VertexShader(loadFileString("example/EdgeFilter.vert")),
		gl::VertexShader(loadFileString("example/EdgeFilter.frag"))
	};
	// glReleaseShaderCompiler();

	Mesh meshdata;
	meshdata.load("example/res/suzanne_flat.obj");

	gl::VertexArray mesh;

	gl::ArrayBuffer positionBuffer;
	positionBuffer.data(gl::STATIC_DRAW, meshdata.positions);
	mesh.bindBuffer(0, positionBuffer, sizeof(glm::vec3));
	mesh.bindAttribute(0, shader3d.attribLocation("position"), gl::FLOAT32, 3);

	gl::ArrayBuffer normalBuffer;
	normalBuffer.data(gl::STATIC_DRAW, meshdata.normals);
	mesh.bindBuffer(1, normalBuffer, sizeof(glm::vec3));
	mesh.bindAttribute(1, shader3d.attribLocation("normal"), gl::FLOAT32, 3);

	gl::ArrayBuffer texcoordBuffer;
	texcoordBuffer.data(gl::STATIC_DRAW, meshdata.texcoords);
	mesh.bindBuffer(2, texcoordBuffer, sizeof(glm::vec2));
	mesh.bindAttribute(2, shader3d.attribLocation("texcoord"), gl::FLOAT32, 2);

	gl::ElementArrayBuffer indexBuffer;
	indexBuffer.data(gl::STATIC_DRAW, meshdata.indices);
	mesh.bindElements(indexBuffer);

	Image imagedata;
	assert(imagedata.load("example/res/colorful.png"));

	gl::Texture2D texture;
	texture.texStorage(1, RGB8, imagedata.width, imagedata.height);
	texture.texSubimage(0, 0, 0, imagedata.width, imagedata.height, RGB, UINT8, imagedata.data.get());

	texture.bindTextureUnit(0);

	enableDepthTest(true);
	enableCullFace(true);
	cullFace(BACK);
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader3d.use();
		mesh.bind();

		shader3d.uniform("uTime", now());
		shader3d.uniform("uViewProjection", glm::perspectiveFov(glm::radians(60.f), (float) windowWidth, (float) windowHeight, .1f, 100.f));
		shader3d.uniform("uModel", glm::translate(glm::vec3(0, 0, -3)) * glm::rotate((float)now(), glm::vec3(0, 1, 0)));

		drawElements(TRIANGLES, UINT16, meshdata.indices.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main(int argc, char const* argv[]) {
	glfwInit();

	glfwSetErrorCallback([](int level, const char* msg) {
		printf("[glfw](%i) %s\n", level, msg);
	});

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	// glfwWindowHint(GLFW_SAMPLES, 8);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Heyho", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) {
		windowWidth = w;
		windowHeight = h;
		glViewport(0, 0, w, h);
	});
	glfwMakeContextCurrent(window);

	glewInit();

	mainLoop(window);

	glfwDestroyWindow(window);

	glfwTerminate();
}
