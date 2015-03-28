varying lowp vec4 varyColor;
varying mediump vec2 varyTexCoord;

uniform lowp sampler2D unifTexture;

void main()
{
	gl_FragColor = texture2D(unifTexture, varyTexCoord);
	gl_FragColor *= varyColor;
}