uniform mat4 in_Projection;

attribute vec2 in_Position;
attribute vec2 in_Uv;

varying vec2 ex_Uv;

void main()
{
  gl_Position = in_Projection * vec4(in_Position, 0, 1);
  ex_Uv = in_Uv;
}
