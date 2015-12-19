#version 130

in vec3 inPoint;
in vec3 inColor;
in vec2 inCoords;
in vec3 inNormal;

out vec3 color;
out float perlinOut;

out vec3 point;
out vec3 eye;
out vec2 coord;
out vec3 normal;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float perlin;

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	
	point = inPoint;
	eye = vec3(viewMatrix * modelMatrix * vec4(inPoint, 1.0));
	coord = inCoords;
	normal = vec3(viewMatrix * modelMatrix * vec4(inNormal, 0.0));
	
	
	float n = rand(vec2(inPoint.x, inPoint.y));
//	if(inColor.r != 0){
	//	n *= 0.03;
	//}
	//else
	//{
	//	n = 0;
	//}
	
	//if(inPoint.z == 0){
		n = 0;
	//}
	

	perlinOut = perlin;
	color = inColor;
	//gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(inPoint, 1.0);
	//gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(inPoint.x, inPoint.y, inPoint.z, 1.0);
	gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(inPoint.x, inPoint.y, inPoint.z + n, 1.0);
}
