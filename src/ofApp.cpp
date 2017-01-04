#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//#ifdef TARGET_OPENGLES
//    EarthShader.load("shadersES2/shader");
//#else
//    if(ofIsGLProgrammableRenderer()){
//        EarthShader.load("shadersGL3/shader");
//    }else{
        EarthShader.load("shadersGL2/Earth/shader");
        AtmosphereShader.load("shadersGL2/Atmosphere/shader");
//    }
//#endif
    
    ofSetVerticalSync(true);
    ofBackground(20);
    ofEnableDepthTest();
    ofEnableLighting();

    cam.setDistance(20);
    cam.setNearClip(.1);
    
    ofSetSmoothLighting(true);
    
    sunPosition = ofVec3f(0, .235, 1);
    
    mainLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    mainLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    mainLight.setPosition(sunPosition);
    mainLight.setDirectional();
    mainLight.enable();
    
    rotateSpeed = .5;
    
    DayEarth.load("earth.png");
    DayEarth.mirror(1, 0);
    
    NightEarth.load("night_earth.jpg");
    NightEarth.mirror(1, 0);
    
    NormalEarth.load("earth_normal.png");
    NormalEarth.mirror(1, 0);
    
    SpecularEarth.load("earth_specular.jpg");
    SpecularEarth.mirror(1,0);
    
    CloudEarth.load("earth_clouds.jpg");
    CloudEarth.mirror(1,0);
    
    EarthMesh.setRadius( 10 );
    EarthMesh.setResolution(4);
    EarthMesh.setPosition(0,0,0);
    
    atmosphereMesh.setRadius( 10.25 );
    atmosphereMesh.setResolution(4);
    atmosphereMesh.setPosition(0, 0, 0);
    atmosphereMesh.enableTextures();
    
    EarthMesh.enableTextures();
    EarthMesh.mapTexCoordsFromTexture(DayEarth.getTexture());
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //EarthMesh.rotate(rotateSpeed*.025, 0, 1, 0);
    sunPosition.x = sin(ofGetFrameNum()*-.0025*rotateSpeed);
    sunPosition.z = cos(ofGetFrameNum()*-.0025*rotateSpeed);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    cam.begin();
        ofEnableDepthTest();
        initEarthShader();
        EarthShader.setUniformTexture("tex0", DayEarth.getTexture()  , 0);
        EarthShader.setUniformTexture("tex1", NightEarth.getTexture()   , 1);
        EarthShader.setUniformTexture("tex2", NormalEarth.getTexture()   , 2);
        EarthShader.setUniformTexture("tex3", SpecularEarth.getTexture()   , 3);
        EarthShader.setUniformTexture("tex4", CloudEarth.getTexture()   , 4);
    
        EarthShader.setUniform3f("sunDirection", sunPosition);
        EarthShader.setUniform3f("uEyePos", cam.getPosition());
        EarthShader.setUniform1f("frameCount", ofGetFrameNum());
        //cout << cam.getPosition() << endl;
            EarthMesh.draw();
        endEarthShader();
    
        AtmosphereShader.begin();
        AtmosphereShader.setUniform3f("uEyePos", cam.getPosition());
        AtmosphereShader.setUniform3f("sunDirection", sunPosition);
        AtmosphereShader.setUniform1f("frameCount", ofGetFrameNum());//("sunDirection", sunPosition);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        atmosphereMesh.draw();
        AtmosphereShader.end();
    cam.end();
    
}

void ofApp::initEarthShader(){
    DayEarth.getTexture().bind();
    NightEarth.getTexture().bind();
    NormalEarth.getTexture().bind();
    EarthShader.begin();
}

void ofApp::endEarthShader(){
    EarthShader.end();
    DayEarth.getTexture().unbind();
    NightEarth.getTexture().unbind();
    NormalEarth.getTexture().unbind();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ofShowCursor();
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
