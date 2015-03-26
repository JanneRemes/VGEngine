attribute highp vec2 attrPosition;

void main()
{
	gl_Position = vec4(attrPosition, 0.0, 1.0);
}