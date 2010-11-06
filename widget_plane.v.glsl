#version 110

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

varying vec2 texcoord;

attribute vec4 vertexPosition;
attribute vec4 normal;
attribute float shininess;
attribute vec4 specular;

varying vec3 fragmentPosition;
varying vec3 fragmentNormal;
varying float fragmentShininess;
varying vec4 fragmentSpecular;

void main()
{
    vec4 eyePosition = modelViewMatrix * vertexPosition;
    gl_Position = projectionMatrix * eyePosition;
    //gl_Position = projectionMatrix * modelViewMatrix * vertexPosition;

    texcoord = vertexPosition.xy * vec2(0.5) + vec2(0.5);
    
    fragmentPosition = eyePosition.xyz;
    fragmentNormal = (modelViewMatrix * normal).xyz;
    fragmentShininess = shininess;
    fragmentSpecular = specular;
}
