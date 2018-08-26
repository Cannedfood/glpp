#version 440

out vec3 fragColor;

uniform float uTime = 0;

in Vertex {
	vec3 position;
	vec2 texcoord;
	vec3 normal;
} vertex;

struct Light {
	vec3 color;
	vec3 position;
};

layout(binding = 0)
uniform sampler2D diffuseTexture;

vec3 saturate(vec3 color, float to) {
	float highest = max(color.r, max(color.g, color.b));
	return color * (to / highest);
}

Light lights[] = Light[](
	Light(saturate(vec3(1, .2, 1), .3), vec3(0, 0, 0)),
	Light(saturate(vec3(1, 1, .2), .3), vec3(0, 10, 0))
);

vec3 N;
vec3 D;

vec3 calcLighting(Light light) {
	vec3 L = normalize(light.position - vertex.position);

	return D * max(0, dot(N, L));
}

void main() {
	N = normalize(vertex.normal);
	D = texture(diffuseTexture, vertex.texcoord + sin(uTime * .1)).rgb;
	// fragColor = N * .5 + .5;
	fragColor = vec3(0);
	for(int i = 0; i < lights.length(); i++) {
		fragColor += calcLighting(lights[i]);
	}
}