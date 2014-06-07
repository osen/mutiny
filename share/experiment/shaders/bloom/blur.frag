#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;
uniform float in_Direction;

varying vec2 ex_Uv;

vec2 gaussFilter[7];

void main()
{
	gaussFilter[0].x = -3.0; gaussFilter[0].y = 0.015625;
	gaussFilter[1].x = -2.0; gaussFilter[1].y = 0.09375;
	gaussFilter[2].x = -1.0; gaussFilter[2].y = 0.234375;
	gaussFilter[3].x = 0.0; gaussFilter[3].y = 0.3125;
	gaussFilter[4].x = 1.0; gaussFilter[4].y = 0.234375;
	gaussFilter[5].x = 2.0; gaussFilter[5].y = 0.09375;
	gaussFilter[6].x = 3.0; gaussFilter[6].y = 0.015625;

	vec4 color = vec4(0, 0, 0, 0);

  vec2 scale;

  if(in_Direction == 0.0)
  {
    scale = vec2(0, 1.0 / 200.0);
  }
  else
  {
    scale = vec2(1.0 / 200.0, 0);
  }

	for( int i = 0; i < 7; i++ )
	{
		color += texture2D(in_Texture, vec2(ex_Uv.x+gaussFilter[i].x*scale.x, ex_Uv.y+gaussFilter[i].x*scale.y)) * gaussFilter[i].y;
	}

  gl_FragColor = color;
  //gl_FragColor.a = gl_FragColor.a / 1.5;
  //gl_FragColor = vec4(ex_Uv, 1.0, 1.0);
  //gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
