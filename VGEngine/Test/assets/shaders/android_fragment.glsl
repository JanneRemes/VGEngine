precission lowp float;

varying vec4 varyColor;
varying vec2 varyTexCoord;

uniform sampler2D unifTexture;
uniform float unifUsingAlphaTexture;

void main()
{
	// ES2.0 doesn't support booleans
	if (unifUsingAlphaTexture > 0.5)
	{
		float alpha = texture2D(unifTexture, varyTexCoord).a * varyColor.a;
		gl_FragColor = vec4(varyColor.rgb, alpha);
	}
	else
	{
		gl_FragColor = texture2D(unifTexture, varyTexCoord);
		gl_FragColor *= varyColor;
	}
}