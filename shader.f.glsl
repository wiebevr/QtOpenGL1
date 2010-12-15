#version 100
precision mediump float;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform sampler2D texture;

varying vec2 texcoord;
varying vec3 fragmentPosition;
varying vec3 fragmentNormal;
varying float fragmentShininess;
varying vec4 fragmentSpecular;

//const vec3 lightDirection = vec3(0.408248, -0.816497, 0.408248);
const vec3 lightDirection = normalize(vec3(0.0, -1.0, -1.0));
const vec4 lightDiffuse = vec4(0.8, 0.8, 0.8, 0.0);
const vec4 lightAmbient = vec4(0.2, 0.2, 0.2, 1.0);
const vec4 lightSpecular = vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
    //vec3 modelViewLightDirection = (modelViewMatrix * vec4(lightDirection, 0.0)).xyz;
    vec3 modelViewLightDirection = lightDirection;
    vec3 normal = normalize(fragmentNormal);
    vec3 eye = normalize(fragmentPosition);
    vec3 reflection = reflect(modelViewLightDirection, normal);

    vec4 diffuseFactor = max(-dot(normal, modelViewLightDirection), 0.0) * lightDiffuse;
    vec4 ambientDiffuseFactor = diffuseFactor + lightAmbient;
    vec4 specularFactor = max(pow(-dot(reflection, eye), fragmentShininess), 0.0) * lightSpecular;
    
    //gl_FragColor = specularFactor  * fragmentSpecular + ambientDiffuseFactor * vec4(1.0, 1.0, 0.0, 0.0);
    //gl_FragColor = specularFactor  * fragmentSpecular + ambientDiffuseFactor * texture2D(texture, texcoord);


    gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);  
}
