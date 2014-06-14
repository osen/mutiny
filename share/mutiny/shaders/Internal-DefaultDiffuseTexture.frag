#ifdef GL_ES
  precision highp float;
#endif

varying vec3 ex_LightPos;
varying vec3 ex_V;
varying vec3 ex_N;

void main()
{
  vec3 L = ex_LightPos - ex_V;

  float brightness = dot(ex_N, L) / (length(L) * length(ex_N));
  brightness += 0.4;

#ifndef GL_ES
  brightness = clamp(brightness, 0, 1);
#endif

  vec4 tex = vec4(0.5, 0.5, 0.5, 1.0);
  gl_FragColor = tex * brightness;
  gl_FragColor.w = tex.w;
}
