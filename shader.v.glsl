#version 100

uniform mediump mat4 projectionMatrix;
uniform mediump mat4 modelViewMatrix;

attribute mediump  vec4 vertexPosition;


void main()
{
    mediump vec4 eyePosition = modelViewMatrix * vec4(vertexPosition.xyz, 1.0);
    gl_Position = projectionMatrix * eyePosition;
    
}
