#version 330

out vec4 color;

uniform float diameter;
uniform sampler2D diffuse_map;
in vec2 interpolated_texCoord;

// Gaussian coefficients
#define C0 (0.159999996 / 0.9800000106)
#define C1 (0.150000006 / 0.9800000106)
#define C2 (0.119999997 / 0.9800000106)
#define C3 (0.0900000036 / 0.9800000106)
#define C4 (0.0500000007 / 0.9800000106)

void main(void)
{
  float stp = diameter * (0.125 / 2.0);
  float y_pos = interpolated_texCoord.y;
  float x_pos = interpolated_texCoord.x - (4 * stp);

  color = C4 * (texture2D(diffuse_map, vec2(x_pos, y_pos)) - 1.0f);
  x_pos += stp;
  color += C3 * (texture2D(diffuse_map, vec2(x_pos, y_pos)) - 1.0f);
  x_pos += stp;
  color += C2 * (texture2D(diffuse_map, vec2(x_pos, y_pos)) - 1.0f);
  x_pos += stp;
  color += C1 * (texture2D(diffuse_map, vec2(x_pos, y_pos)) - 1.0f);
  x_pos += stp;
  color += C0 * (texture2D(diffuse_map, vec2(x_pos, y_pos)) - 1.0f);
  x_pos += stp;
  color += C1 * (texture2D(diffuse_map, vec2(x_pos, y_pos)) - 1.0f);
  x_pos += stp;
  color += C2 * (texture2D(diffuse_map, vec2(x_pos, y_pos)) - 1.0f);
  x_pos += stp;
  color += C3 * (texture2D(diffuse_map, vec2(x_pos, y_pos)) - 1.0f);
  x_pos += stp;
  color += C4 * (texture2D(diffuse_map, vec2(x_pos, y_pos)) - 1.0f);
}