#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;

varying vec2 ex_Uv;

void main()
{
  gl_FragColor = texture2D(in_Texture, ex_Uv);
  //gl_FragColor.a = gl_FragColor.a / 1.5;
  //gl_FragColor = vec4(ex_Uv, 1.0, 1.0);
  //gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
