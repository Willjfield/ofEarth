#version 120

// this is coming from our C++ code
//uniform float mouseX;
 
varying vec2 texCoord;  
//varying vec4 gl_TexCoord[2];

varying vec3 vNormal;

void main()
{

    // vec2 texcoord0 = gl_MultiTexCoord0.xy;
    // // here we move the texture coordinates
    // texCoordVarying0 = vec2(texcoord0.x, texcoord0.y);

    // vec2 texcoord1 = gl_MultiTexCoord1.xy;
    // // here we move the texture coordinates
    // texCoordVarying1 = vec2(texcoord1.x, texcoord1.y);
    //texCoordVarying[0] = texcoord[0];
    //texCoordVarying[1] = texcoord[1];

    texCoord = vec2(gl_MultiTexCoord0);

    vNormal = gl_Normal;

    // send the vertices to the fragment shader
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;;
}