#version 130

uniform sampler2D texture0;
uniform vec3 ambientLight;

uniform vec3 light0Position;
uniform vec3 light0Ambient;
uniform vec3 light0Diffuse;
uniform float light0ConstantAttenuation;
uniform float light0LinearAttenuation;
uniform float light0QuadraticAttenuation;

varying vec3 normal;
varying vec3 toLightDir;
varying vec3 pos;

in vec2 texCoord0;

out vec4 outColor;

void main(void) {
	// setup the ambient light
	vec3 li = ambientLight + light0Ambient;
	
	// normalize the normal and 'to light' direction vector
	vec3 N = normalize(normal);
	vec3 L = normalize(normal);
	
	// calculate the diffuse term
	float d = clamp(dot(N, L), 0.0, 1.0);
	// calculate the attenuation factor
	float dist = length(toLightDir);
	float atten = 1.0 / (light0ConstantAttenuation + light0LinearAttenuation * dist + light0QuadraticAttenuation * dist * dist);
	
	li += d * light0Diffuse * atten;

	//Sample the texture
	outColor = texture(texture0, texCoord0.st) * vec4(li, 1.0);
}
