#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;
uniform sampler2D in_Merge;

varying vec2 ex_Uv;

void main()
{
  gl_FragColor = texture2D(in_Texture, ex_Uv);
  // --
  //gl_FragColor = gl_FragColor / 2.0;
  //gl_FragColor.w = 1.0f;
  // --
  vec4 merge = texture2D(in_Merge, vec2(ex_Uv.x, 1.0 - ex_Uv.y));
  //merge = merge / 2.0;
  //merge.a = 1.0;
  //merge = merge / 1.5;

  //if(merge.x + merge.y + merge.z >= 1.0)
  //{
    gl_FragColor.x = gl_FragColor.x + merge.x;
    gl_FragColor.y = gl_FragColor.y + merge.y;
    gl_FragColor.z = gl_FragColor.z + merge.z;
  //}
}
