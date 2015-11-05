attribute highp vec2 attrPosition;
attribute highp vec4 attrColor;
attribute highp vec2 attrTexCoord;

uniform highp mat4 unifProjection;
uniform highp mat4 unifModel;
uniform highp float unifLayer;

varying highp vec4 varyColor;
varying highp vec2 varyTexCoord;

void main()
{
	varyColor = attrColor;
	varyTexCoord = attrTexCoord;
	gl_Position = unifProjection * unifModel * vec4(attrPosition, unifLayer, 1.0);
}