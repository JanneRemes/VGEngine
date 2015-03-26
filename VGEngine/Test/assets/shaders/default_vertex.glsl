attribute highp vec2 attrPosition;
varying lowp vec4 varyColor;

void main()
{
	varyColor = vec4(1.0, 0.0, 0.0, 1.0);
	gl_Position = vec4(attrPosition, 0.0, 0.0);
}