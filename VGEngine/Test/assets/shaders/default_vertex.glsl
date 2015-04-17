attribute highp vec2 attrPosition;
attribute lowp vec4 attrColor;
attribute mediump vec2 attrTexCoord;

uniform mat4 unifProjection;
uniform mat4 unifView;
uniform mat4 unifWorld;
uniform float unifLayer;

varying lowp vec4 varyColor;
varying mediump vec2 varyTexCoord;

void main()
{
	varyColor = attrColor;
	varyTexCoord = attrTexCoord;
	gl_Position = unifProjection * unifView * unifWorld * vec4(attrPosition, unifLayer, 1.0);
}