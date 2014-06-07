uniform mat4 in_Projection;
uniform mat4 in_View;
uniform mat4 in_Model;

attribute vec2 in_Position;
attribute vec2 in_Uv;

varying vec2 ex_Uv;

void main()
{
  gl_Position = in_Projection * in_View * in_Model * vec4(in_Position, 0, 1);
  ex_Uv = in_Uv;
}
