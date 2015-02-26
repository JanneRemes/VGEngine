attribute highp vec3 attrPosition;
attribute mediump vec2 attrTexCoord;

varying mediump vec2 varyTexCoord;

void main()
{
	varyTexCoord = attrTexCoord;
	gl_Position = vec4(attrPosition, 1.0);
}