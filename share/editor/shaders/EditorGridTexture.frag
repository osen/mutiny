#ifdef GL_ES
  precision highp float;
#endif

varying vec2 ex_Uv;

void main()
{
  gl_FragColor = vec4(ex_Uv, 0.0, 1.0);
}
