#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;
uniform float in_Pulse;

varying vec2 ex_Uv;

void main()
{
  gl_FragColor = texture2D(in_Texture, ex_Uv);
  gl_FragColor.r += in_Pulse;
}
