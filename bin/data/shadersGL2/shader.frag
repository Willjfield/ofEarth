#version 120
#extension GL_ARB_texture_rectangle : enable 
// this is how we receive the texture
varying vec2 texCoord;  
uniform sampler2DRect tex0, tex1;  

varying vec3 vNormal;

void main()
{

	vec3 sunDirection = vec3(1.0,0.23,0.0);
	vec4 dayColor = texture2DRect(tex0, texCoord);
	vec4 nightColor = texture2DRect(tex1, texCoord*2.);

	// compute cosine sun to normal so -1 is away from sun and +1 is toward sun.
    float cosineAngleSunToNormal = dot(normalize(vNormal), sunDirection);
    // sharpen the edge beween the transition
    cosineAngleSunToNormal = clamp( cosineAngleSunToNormal * 5.0, -1.0, 1.0);
    // convert to 0 to 1 for mixing
    float mixAmount = cosineAngleSunToNormal*0.5 + 0.5;

    vec4 color = mix(dayColor,vec4(nightColor.rgb*.5,1.0),mixAmount);
    //the calculation which brings it all together
    gl_FragColor = color;
    
    //gl_FragColor = texture2DRect(tex0, texCoordVarying);
}