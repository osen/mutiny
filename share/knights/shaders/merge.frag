#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;
uniform sampler2D in_Merge;

varying vec2 ex_Uv;

void main()
{
  gl_FragColor = texture2D(in_Texture, ex_Uv);
  vec2 tmpUv = ex_Uv;
  //tmpUv.y = 1.0 - tmpUv.y;
  vec4 merge = texture2D(in_Merge, ex_Uv);
  merge = merge / 2.0;
  gl_FragColor.x = gl_FragColor.x + merge.x;
  gl_FragColor.y = gl_FragColor.y + merge.y;
  gl_FragColor.z = gl_FragColor.z + merge.z;
}
