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
  vec3 L = normalize(ex_LightPos - ex_V);   
  vec4 Idiff = vec4(1, 1, 1, 1) * max(dot(ex_N,L), 0.0);  
  Idiff = clamp(Idiff, 0.0, 1.0); 

  //gl_FragColor = texture2D(in_Texture, ex_Uv);
  //gl_FragColor = gl_FragColor - gl_FragColor;
  //gl_FragColor += Idiff;
  //gl_FragColor.w = 1.0;
  gl_FragColor = texture2D(in_Texture, ex_Uv) + Idiff;
}
