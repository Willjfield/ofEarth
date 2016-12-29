#version 120
#extension GL_ARB_texture_rectangle : enable 
// this is how we receive the texture
varying vec2 texCoord;  

varying vec3 vNormal;

uniform vec3 sunDirection;

uniform vec3 uEyePos;

void main()
{
    float opacity = .45-pow(dot(normalize(uEyePos),vNormal),4.);

    vec4 color = vec4(.4,.7,1.,opacity);
    gl_FragColor = color;
}