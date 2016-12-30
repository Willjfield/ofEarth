#version 120
#extension GL_ARB_texture_rectangle : enable 
// this is how we receive the texture
varying vec2 texCoord;  

varying vec3 vNormal;

uniform vec3 sunDirection;

uniform vec3 uEyePos;

uniform float frameCount;
uniform vec3 randomVec;

void main()
{

    vec3 north = vec3(0.,1.,0.);
    //vec3 randomVec = vec3(.2,.6,.3);
    float dotRandom = pow(abs(dot(randomVec,vNormal)),16.);//*2.-1.;

    float dotPoles = pow(abs(dot(north,vNormal)),16.);
    
    float dotSun = 1.-dot(normalize(sunDirection),vNormal)*2-1;
    float dotCam = dot(normalize(uEyePos),vNormal)*2-1;
    float opacity = pow(.5-abs(dotCam-.35),2.)*dotSun;

    //vec4 aurora = vec4(auroraColor,dotPoles*.5);
    vec4 airColor = vec4(.4,.5,1.,opacity);
    float psudo_random_opacity = 1.-clamp(dotRandom*abs(cos(abs(dotPoles*dotRandom*.7+frameCount/1000.)-5.)+abs(abs(sin(dotRandom*.25+frameCount/500.)))),.3,.4);
    float noise_opacity = dotRandom;
    vec4 auroraColor = vec4(.2,1.,.2,psudo_random_opacity);

    vec4 air_aurora_mix = mix(airColor,auroraColor,dotPoles);

    //vec4 color = vec4(air_aurora_mix);
    gl_FragColor = air_aurora_mix;
}