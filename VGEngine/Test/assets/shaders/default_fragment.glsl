varying lowp vec4 varyColor;
varying mediump vec2 varyTexCoord;
uniform lowp sampler2D unifTexture;

void main()
{
	gl_FragColor = varyColor;
	gl_FragColor *= texture2D(unifTexture, varyTexCoord);
}