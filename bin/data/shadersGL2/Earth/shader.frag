#version 120
#extension GL_ARB_texture_rectangle : enable 
// this is how we receive the texture
varying vec2 texCoord;  

uniform sampler2DRect tex0, tex1, tex2;  

varying vec3 vNormal;

uniform vec3 sunDirection;

uniform vec3 uEyePos;

void main()
{
    vec3 bumpDir = vec3(0.0,.0,1.); 
    //RGB of our normal map
    vec3 NormalMap = texture2DRect(tex2, texCoord*.5).rgb;
    //NormalMap.g*=-1.;
    //normalize our vectors
    vec3 N = normalize(NormalMap * 2.0 - 1.0);
    vec3 L = normalize(bumpDir) * 2.0 - 1.0;

    //Calculate Diffuse
    float Diffuse = (dot(N, L)-0.5)*.25;

	//Load Textures
	vec4 dayColor = texture2DRect(tex0, texCoord);
    //dayColor.rgb*=.8;
	vec4 nightColor = texture2DRect(tex1, texCoord*2.);

	// compute cosine sun to normal so -1 is away from sun and +1 is toward sun.
    float cosineAngleSunToNormal = dot(normalize(vNormal), sunDirection);
    // sharpen the edge beween the transition
    //cosineAngleSunToNormal = clamp( cosineAngleSunToNormal*5., -1.0, 1.0);
    cosineAngleSunToNormal*=3.;
    // convert to 0 to 1 for mixing
    float mixAmount = cosineAngleSunToNormal*0.5 + 1.;

    float dotSun = 1.-dot(normalize(sunDirection),vNormal)*2-1;
    vec3 reflected_sunlight = reflect(-normalize(sunDirection),normalize(vNormal));
    float specular = clamp(pow(dot(reflected_sunlight,normalize(uEyePos)),32.),0.,.35)*dotSun;

    vec4 color = mix(dayColor,vec4(nightColor.rgb*.5,1.0),mixAmount)+Diffuse+specular;
    //the calculation which brings it all together
    color.a = 1.;
    gl_FragColor = color;
}