// Vertex Shader

uniform mat4 projectionMatrix;
uniform  mat4 modelViewMatrix;

attribute vec4 vertexPosition;
attribute vec4 normal;
attribute float shininess;
attribute  vec4 specular;

varying vec2 texcoord;
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

    texcoord = vec2(vertexPosition.x, vertexPosition.y) * vec2(0.5) + vec2(0.5);
}
