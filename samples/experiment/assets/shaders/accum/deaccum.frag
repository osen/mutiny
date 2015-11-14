#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;
uniform float in_TimeDelta;

varying vec2 ex_Uv;

void main()
{
  gl_FragColor = texture2D(in_Texture, vec2(ex_Uv.x, 1.0 - ex_Uv.y));

  gl_FragColor = gl_FragColor - ((vec4(1, 1, 1, 1) * 3.0) * in_TimeDelta);
  gl_FragColor.w = 1.0;
}
