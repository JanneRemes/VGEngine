varying mediump vec2 varyTexCoord;
uniform lowp sampler2D unifTexture;

void main()
{
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	gl_FragColor = texture2D(unifTexture, varyTexCoord);
}