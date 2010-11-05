#version 110

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

varying vec3 fragmentPosition;
varying vec3 fragmentNormal;
varying float fragmentShininess;
varying vec4 fragmentSpecular;

const vec3 lightDirection = vec3(0.408248, -0.816497, 0.408248);
const vec4 lightDiffuse = vec4(0.8, 0.8, 0.8, 0.0);
const vec4 lightAmbient = vec4(0.2, 0.2, 0.2, 1.0);
const vec4 lightSpecular = vec4(1.0, 1.0, 1.0, 1.0);



void main()
{
    gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);  
}
