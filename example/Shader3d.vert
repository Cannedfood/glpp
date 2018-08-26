#version 440

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out Vertex {
	vec3 position;
	vec2 texcoord;
	vec3 normal;
} vertex;

// uniform Camera {
// 	vec3 position;
// 	mat4 projection;
// 	mat4 view;
// 	mat4 viewProjection;
// } camera;

uniform float uTime          = 0;
uniform mat4 uViewProjection = mat4(1);
uniform mat4 uModel          = mat4(1);

void main() {
	vec3 p = position + normal * max(0, sin(uTime));

	vertex.position = (uModel * vec4(p, 1)).xyz;
	vertex.normal   = (uModel * vec4(normal, 0)).xyz;
	vertex.texcoord = texcoord;

	gl_Position  = uViewProjection * vec4(vertex.position, 1);
}