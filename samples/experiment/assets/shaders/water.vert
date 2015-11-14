uniform mat4 in_Projection;
uniform mat4 in_View;
uniform mat4 in_Model;
uniform mat4 in_NormalMatrix;
uniform float in_Offset;

attribute vec3 in_Position;
attribute vec2 in_Uv;
attribute vec3 in_Normal;

varying vec2 ex_Uv;
varying vec3 ex_LightPos;

varying vec3 ex_V;
varying vec3 ex_N;

void main()
{
  ex_N = normalize(in_NormalMatrix * vec4(in_Normal, 1)).xyz;
  ex_V = vec3(in_View * in_Model * vec4(in_Position, 1)); 
  ex_Uv = in_Uv;
  ex_LightPos = vec4(in_View * vec4(7, 10, 13, 1)).xyz;
  vec4 pos = vec4(in_Position, 1);
  pos.y += ((-pos.y * 2.0) * in_Offset);
  gl_Position = in_Projection * in_View * in_Model * pos;
}
