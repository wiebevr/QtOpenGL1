// Vertex Shader

uniform mediump mat4 projectionMatrix;
uniform mediump mat4 modelViewMatrix;

attribute highp vec4 vertexPosition;
attribute highp vec4 normal;
attribute mediump float shininess;
attribute mediump vec4 specular;

varying highp vec2 texcoord;
varying mediump vec3 fragmentPosition;
varying mediump vec3 fragmentNormal;
varying mediump float fragmentShininess;
varying mediump vec4 fragmentSpecular;

void main()
{
    highp vec4 eyePosition = modelViewMatrix * vec4(vertexPosition.xyz, 1.0);
    gl_Position = projectionMatrix * eyePosition;
    
    fragmentPosition = eyePosition.xyz;
    fragmentNormal = (modelViewMatrix * vec4(normal.xyz, 0.0)).xyz;
    fragmentShininess = shininess;
    fragmentSpecular = specular;

    texcoord = vec2(vertexPosition.x, vertexPosition.y) * vec2(0.5) + vec2(0.5);
}
