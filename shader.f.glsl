// Fragment Shader
#version 100

uniform mediump mat4 projectionMatrix;
uniform mediump mat4 modelViewMatrix;
uniform mediump sampler2D texture;

varying highp vec2 texcoord;
varying mediump vec3 fragmentPosition;
varying mediump vec3 fragmentNormal;
varying mediump float fragmentShininess;
varying mediump vec4 fragmentSpecular;

//const vec3 lightDirection = vec3(0.408248, -0.816497, 0.408248);
const mediump vec3 lightDirection = normalize(vec3(0.0, -1.0, -1.0));
const mediump vec4 lightDiffuse = vec4(0.8, 0.8, 0.8, 0.0);
const mediump vec4 lightAmbient = vec4(0.2, 0.2, 0.2, 1.0);
const mediump vec4 lightSpecular = vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
    //vec3 modelViewLightDirection = (modelViewMatrix * vec4(lightDirection, 0.0)).xyz;
    mediump vec3 modelViewLightDirection = lightDirection;
    mediump vec3 normal = normalize(fragmentNormal);
    mediump vec3 eye = normalize(fragmentPosition);
    mediump vec3 reflection = reflect(modelViewLightDirection, normal);

    mediump vec4 diffuseFactor = max(-dot(normal, modelViewLightDirection), 0.0) * lightDiffuse;
    mediump vec4 ambientDiffuseFactor = diffuseFactor + lightAmbient;
    mediump vec4 specularFactor = max(pow(-dot(reflection, eye), fragmentShininess), 0.0) * lightSpecular;
    
    //gl_FragColor = specularFactor  * fragmentSpecular + ambientDiffuseFactor * vec4(1.0, 1.0, 0.0, 0.0);
    gl_FragColor = specularFactor  * fragmentSpecular + ambientDiffuseFactor * texture2D(texture, texcoord);


    //gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);  
}
