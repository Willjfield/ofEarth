#version 120

// this is coming from our C++ code
//uniform vec3 sunDirection;
 
varying vec2 texCoord;  
varying vec3 vNormal;
//varying vec3 sunDir;

void main()
{

    texCoord = vec2(gl_MultiTexCoord0);

    vNormal = gl_Normal;

    //sunDir = sunDirection;
    // send the vertices to the fragment shader
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}