varying vec4 varyColor;
varying vec2 varyTexCoord;

uniform sampler2D unifTexture;
uniform float unifNoTexture;
uniform float unifFontTexture;

void main()
{
	// ES2.0 doesn't support booleans or ints in fragment shader
	if (unifNoTexture > 0.5)
	{
		gl_FragColor = varyColor;
	}
	else 
	{
		if (unifFontTexture > 0.5)
		{
			float alpha = texture2D(unifTexture, varyTexCoord).a;
			gl_FragColor = vec4(1.0, 1.0, 1.0, alpha);
			gl_FragColor *= varyColor;
		}
		else
		{
			gl_FragColor = texture2D(unifTexture, varyTexCoord);
			gl_FragColor *= varyColor;
		}
	}
}