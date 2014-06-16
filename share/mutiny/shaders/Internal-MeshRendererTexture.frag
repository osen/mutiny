#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;

varying vec2 ex_Uv;
varying vec3 ex_LightPos;

varying vec3 ex_V;
varying vec3 ex_N;

//#ifdef GL_ES
float mut_clamp(float x, float a, float b)
{
  return max(a, min(b, x));
}
//#endif

void main()
{
  vec3 L = ex_LightPos - ex_V;

  float brightness = dot(ex_N, L) / (length(L) * length(ex_N));
  brightness += 0.4;

  brightness = mut_clamp(brightness, 0.0, 1.0);

  vec4 tex = texture2D(in_Texture, ex_Uv);
  gl_FragColor = tex * brightness;
  gl_FragColor.w = tex.w;
}
