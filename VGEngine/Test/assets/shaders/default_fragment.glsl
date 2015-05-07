varying lowp vec4 varyColor;
varying mediump vec2 varyTexCoord;

uniform lowp sampler2D unifTexture;
uniform lowp float unifUsingAlphaTexture;

void main()
{
	// ES2.0 doesn't support booleans
	if (unifUsingAlphaTexture > 0.5)
	{
		mediump float alpha = texture2D(unifTexture, varyTexCoord).a;
		gl_FragColor = vec4(varyColor.rgb, alpha);
	}
	else
	{
		gl_FragColor = texture2D(unifTexture, varyTexCoord);
		gl_FragColor *= varyColor;
	}
}