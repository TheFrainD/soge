#version 330 core
layout (location=0) in vec2 a_pos;
layout (location=1) in vec4 a_color;
layout (location=2) in vec2 a_tex_coords;
layout (location=3) in float a_tex_id;

uniform mat4 u_proj;
uniform mat4 u_view;

out vec4 v_color;
out vec2 v_tex_coords;
out float v_tex_id;

void main(void) {
  v_color = a_color;
  v_tex_coords = a_tex_coords;
  v_tex_id = a_tex_id;
  gl_Position = u_proj * u_view * vec4(a_pos, 0.0, 1.0);
}