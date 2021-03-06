#version 120
//  Simplex 3D Noise 
//  by Ian McEwan, Ashima Arts
//
vec4 permute(vec4 x){return mod(((x*34.0)+1.0)*x, 289.0);}
vec4 taylorInvSqrt(vec4 r){return 1.79284291400159 - 0.85373472095314 * r;}

float snoise(vec3 v){ 
  const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
  const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);

// First corner
  vec3 i  = floor(v + dot(v, C.yyy) );
  vec3 x0 =   v - i + dot(i, C.xxx) ;

// Other corners
  vec3 g = step(x0.yzx, x0.xyz);
  vec3 l = 1.0 - g;
  vec3 i1 = min( g.xyz, l.zxy );
  vec3 i2 = max( g.xyz, l.zxy );

  //  x0 = x0 - 0. + 0.0 * C 
  vec3 x1 = x0 - i1 + 1.0 * C.xxx;
  vec3 x2 = x0 - i2 + 2.0 * C.xxx;
  vec3 x3 = x0 - 1. + 3.0 * C.xxx;

// Permutations
  i = mod(i, 289.0 ); 
  vec4 p = permute( permute( permute( 
             i.z + vec4(0.0, i1.z, i2.z, 1.0 ))
           + i.y + vec4(0.0, i1.y, i2.y, 1.0 )) 
           + i.x + vec4(0.0, i1.x, i2.x, 1.0 ));

// Gradients
// ( N*N points uniformly over a square, mapped onto an octahedron.)
  float n_ = 1.0/7.0; // N=7
  vec3  ns = n_ * D.wyz - D.xzx;

  vec4 j = p - 49.0 * floor(p * ns.z *ns.z);  //  mod(p,N*N)

  vec4 x_ = floor(j * ns.z);
  vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)

  vec4 x = x_ *ns.x + ns.yyyy;
  vec4 y = y_ *ns.x + ns.yyyy;
  vec4 h = 1.0 - abs(x) - abs(y);

  vec4 b0 = vec4( x.xy, y.xy );
  vec4 b1 = vec4( x.zw, y.zw );

  vec4 s0 = floor(b0)*2.0 + 1.0;
  vec4 s1 = floor(b1)*2.0 + 1.0;
  vec4 sh = -step(h, vec4(0.0));

  vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
  vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;

  vec3 p0 = vec3(a0.xy,h.x);
  vec3 p1 = vec3(a0.zw,h.y);
  vec3 p2 = vec3(a1.xy,h.z);
  vec3 p3 = vec3(a1.zw,h.w);

//Normalise gradients
  vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
  p0 *= norm.x;
  p1 *= norm.y;
  p2 *= norm.z;
  p3 *= norm.w;

// Mix final noise value
  vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
  m = m * m;
  return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1), 
                                dot(p2,x2), dot(p3,x3) ) );
}

float map(float value, float inMin, float inMax, float outMin, float outMax) {
  return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

#extension GL_ARB_texture_rectangle : enable 
// this is how we receive the texture
varying vec2 texCoord;  

uniform sampler2DRect tex0, tex1, tex2, tex3, tex4;  

varying vec3 vNormal;

uniform vec3 sunDirection;

uniform vec3 uEyePos;

uniform float frameCount;

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
    float Diffuse = (dot(N, L)-0.5)*.01;

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

    //Calculate specular
    float dotSun = 1.-dot(normalize(sunDirection),vNormal)*2-1;
    vec3 reflected_sunlight = reflect(-normalize(sunDirection),normalize(vNormal));
    float sun_amount = dot(normalize(reflected_sunlight),normalize(uEyePos));
    //sun_amount = clamp(sun_amount,.8,1.);
    sun_amount = clamp(sun_amount,-1.,-.9)*-1;
    sun_amount = map(sun_amount, .9, 1., .0, .5);
    sun_amount = pow(sun_amount,2.);
    //float specular = clamp(pow(),8.),0.,.4)*dotSun;
    float specular = sun_amount*dotSun;
    
    //map specular to image
    vec4 specularMap = texture2DRect(tex3, texCoord*2.);
    specular*=(1.-specularMap.r);

    //Get clouds
    float noise_scale = 3.;
    vec2 texCoord_moved = texCoord+(25.*vec2(snoise(vec3((vNormal.x+vNormal.y)*noise_scale,(frameCount/1000.),(vNormal.z+vNormal.y)*noise_scale)),snoise(vec3((vNormal.x+vNormal.y)*noise_scale,((frameCount+500)/1000.),(vNormal.z+vNormal.y)*noise_scale))));
    texCoord_moved.x-=frameCount/10.;
    texCoord_moved.x = mod(texCoord_moved.x,4096.);

    vec4 cloudMap = texture2DRect(tex4, texCoord_moved*2.);
    cloudMap*=dotSun*.5;

    vec4 color = mix(dayColor,vec4(nightColor.rgb*.5,1.0),mixAmount)+Diffuse+specular+cloudMap;
    //the calculation which brings it all together
    color.a = 1.;
    gl_FragColor = color;
}