#version 110

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

attribute vec4 vertexPosition;
attribute vec4 normal;
attribute vec2 texcoord;
attribute float shininess;
attribute vec4 specular;

varying vec3 fragmentPosition;
varying vec3 fragmentNormal;
varying float fragmentShininess;
varying vec4 fragmentSpecular;

void main()
{
    vec4 eyePosition = modelViewMatrix * vec4(vertexPosition.xyz, 1.0);
    gl_Position = projectionMatrix * eyePosition;
    
    fragmentPosition = eyePosition.xyz;
    fragmentNormal = (modelViewMatrix * vec4(normal.xyz, 0.0)).xyz;
    fragmentShininess = shininess;
    fragmentSpecular = specular;
}
