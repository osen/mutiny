#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;
uniform float in_Replace;

varying vec2 ex_Uv;

void main()
{
  gl_FragColor = texture2D(in_Texture, ex_Uv);

  if(gl_FragColor.r > gl_FragColor.g + gl_FragColor.b)
  {
    gl_FragColor.r = in_Replace;
  }
}
