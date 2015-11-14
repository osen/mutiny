#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;
uniform float in_TexOffset;

varying vec2 ex_Uv;
varying vec3 ex_LightPos;

varying vec3 ex_V;
varying vec3 ex_N;

void main()
{
  vec3 L = ex_LightPos - ex_V;

  float brightness = dot(ex_N, L) / (length(L) * length(ex_N));
  brightness += 0.4;

//#ifdef GL_ES
//  brightness = clamp(brightness, 0, 1);
//#endif

  if(brightness > 1.0)
  {
    brightness = 1.0;
  }
  else if(brightness < 0.0)
  {
    brightness = 0.0;
  }

  //vec4 Idiff = vec4(1, 1, 1, 1) * max(dot(ex_N,L), 0.0);  
  //Idiff = clamp(Idiff, 0.0, 1.0); 

  //gl_FragColor = texture2D(in_Texture, ex_Uv);
  //gl_FragColor = gl_FragColor - gl_FragColor;
  //gl_FragColor += Idiff;
  //gl_FragColor.w = 1.0;
  vec4 tex = texture2D(in_Texture, vec2(ex_Uv.x, ex_Uv.y - in_TexOffset));
  //gl_FragColor = tex * brightness;
  //gl_FragColor.w = tex.w;
  gl_FragColor = tex;
}
