#version 100

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

attribute vec4 vertexPosition;


void main()
{
    vec4 eyePosition = modelViewMatrix * vec4(vertexPosition.xyz, 1.0);
    gl_Position = projectionMatrix * eyePosition;
    
}
