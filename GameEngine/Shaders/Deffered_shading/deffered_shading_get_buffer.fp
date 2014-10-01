#version 330

in vec4 inter_position;
in vec3 inter_normal;
in vec2 inter_texCoord;

uniform vec4 diffuse_color;
uniform float diffuse_ratio;
uniform sampler2D diffuse_texture;

layout (location = 0) out vec4 diffuse_frag;
layout (location = 1) out vec4 normal_frag;

void main(void)
{
	//diffuse_frag = vec4(vec3(diffuse_color * diffuse_ratio), 1.0f);
	diffuse_frag = vec4(vec3(texture(diffuse_texture, inter_texCoord) + (diffuse_color * diffuse_ratio * 0.01f)), 1.0f);
	vec3 normal = inter_normal * 0.5f + 0.5f;
	normal_frag = vec4(normal, 1.0f);
}