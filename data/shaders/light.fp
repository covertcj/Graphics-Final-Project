#version 130

uniform sampler2D texture0;

uniform vec3 emissive;
uniform vec3 ambient;

in vec2 texCoord0;

out vec4 outColor;

void main(void)
{
	vec3 li = ambient + emissive;

	outColor = texture2D(texture0, texCoord0.st) * vec4(li, 1.0);
	gl_FragColor = texture2D(texture0, texCoord0.st) * vec4(li, 1.0);
}