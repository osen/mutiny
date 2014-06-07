#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;
uniform sampler2D in_Merge;

varying vec2 ex_Uv;

void main()
{
  gl_FragColor = texture2D(in_Texture, ex_Uv) + texture2D(in_Merge, vec2(ex_Uv.x, ex_Uv.y));
}
