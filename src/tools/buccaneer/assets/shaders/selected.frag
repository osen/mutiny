#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;
uniform float in_Pulse;

varying vec3 ex_Normal;
varying vec2 ex_Uv;
varying vec3 ex_L;

void main()
{
  gl_FragColor = texture2D(in_Texture, ex_Uv);
  gl_FragColor.r += in_Pulse;
}
