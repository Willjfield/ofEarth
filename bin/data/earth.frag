  uniform sampler2D dayTexture;
  uniform sampler2D nightTexture;
  uniform sampler2D normalTexture;
  uniform sampler2D cloudTexture;
  uniform float texOffset;

  uniform vec3 sunDirection;

  varying vec2 vUv;
  varying vec3 vNormal;

  void main( void ) {

  		vec3 bumpDir = vec3(0.0,-0.2,1.0);
                  vec3 dayColor = texture2D( dayTexture, vUv ).rgb;
                  vec3 nightColor = texture2D( nightTexture, vUv ).rgb;
                  vec3 cloudColor = texture2D(cloudTexture, vUv+vec2(texOffset,0.0)).rgb; 
  		//RGB of our normal map
  		vec3 NormalMap = texture2D(normalTexture, vUv).rgb;

  		 //normalize our vectors
  		vec3 N = normalize(NormalMap * 2.0 - 1.0);
  		vec3 L = normalize(bumpDir * 2.0 - 1.0);
  		float Diffuse = (dot(N, L)-0.5)*.25;

  		// compute cosine sun to normal so -1 is away from sun and +1 is toward sun.
      float cosineAngleSunToNormal = dot(normalize(vNormal), sunDirection);

      // sharpen the edge beween the transition
      cosineAngleSunToNormal = clamp( cosineAngleSunToNormal * 10.0, -1.0, 1.0);

      // convert to 0 to 1 for mixing
      float mixAmount = cosineAngleSunToNormal*0.5 + 0.5;

      // Select day or night texture based on mix.
      vec3 color = mix( (nightColor+(cloudColor*.2)), (dayColor+cloudColor), mixAmount )+Diffuse;
      //the calculation which brings it all together
      gl_FragColor = vec4( color, 1.0 );
  }
  