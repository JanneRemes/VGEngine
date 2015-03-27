attribute highp vec2 attrPosition;
attribute lowp vec4 attrColor;

varying lowp vec4 varyColor;

void main()
{
	varyColor = attrColor;
	gl_Position = vec4(attrPosition, 0.0, 1.0);
}