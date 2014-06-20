#ifdef GL_ES
  precision highp float;
#endif

varying vec2 ex_Uv;

void main()
{
  float x = float(int(ex_Uv.x * 100.0));
  float cx = ex_Uv.x * 100.0;

  float y = float(int(ex_Uv.y * 100.0));
  float cy = ex_Uv.y * 100.0;

  if(cx - x > 0.05 && cy - y > 0.05)
  {
    discard;
  }

  gl_FragColor = vec4(1.0, 1.0, 1.0, 0.5);
}
