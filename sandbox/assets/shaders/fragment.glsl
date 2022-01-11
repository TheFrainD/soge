#version 460 core

in vec4 v_color;
in vec2 v_tex_coords;
in float v_tex_id;

uniform sampler2D u_image[16];

out vec4 color;

void main(void) {
  int index = int(v_tex_id);
  color = texture(u_image[index], v_tex_coords) * v_color;
}