uniform mat4 in_Projection;
uniform mat4 in_View;
uniform mat4 in_Model;

attribute vec3 in_Position;
attribute vec3 in_Normal;
attribute vec2 in_Uv;

varying vec3 ex_Normal;
varying vec2 ex_Uv;
varying vec3 ex_L;

void main()
{
  ex_L = normalize(vec3(0, -1, 0) - vec3(in_View * in_Model * vec4(in_Position, 1))); 
  gl_Position = in_Projection * in_View * in_Model * vec4(in_Position, 1);
  ex_Normal = in_Normal;
  ex_Uv = in_Uv;
}
