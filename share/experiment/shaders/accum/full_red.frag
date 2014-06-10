#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;

varying vec2 ex_Uv;
varying vec3 ex_LightPos;

varying vec3 ex_V;
varying vec3 ex_N;

void main()
{
  vec3 L = ex_LightPos - ex_V;

  float brightness = dot(ex_N, L) / (length(L) * length(ex_N));
  brightness = clamp(brightness, 0, 1);

  //vec4 Idiff = vec4(1, 1, 1, 1) * max(dot(ex_N,L), 0.0);  
  //Idiff = clamp(Idiff, 0.0, 1.0); 

  //gl_FragColor = texture2D(in_Texture, ex_Uv);
  //gl_FragColor = gl_FragColor - gl_FragColor;
  //gl_FragColor += Idiff;
  //gl_FragColor.w = 1.0;
  vec4 tex = texture2D(in_Texture, ex_Uv);

  if(tex.r < tex.g + tex.b)
  {
    gl_FragColor = tex * brightness;
    gl_FragColor.w = tex.w;
  }
  else
  {
    gl_FragColor = vec4(1, 0, 0, 1);
  }
}
