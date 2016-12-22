#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//#ifdef TARGET_OPENGLES
//    EarthShader.load("shadersES2/shader");
//#else
//    if(ofIsGLProgrammableRenderer()){
//        EarthShader.load("shadersGL3/shader");
//    }else{
        EarthShader.load("shadersGL2/shader");
//    }
//#endif
    
    ofSetVerticalSync(true);
    ofBackground(20);
    ofEnableDepthTest();
    ofEnableLighting();

    cam.setDistance(20);
    cam.setNearClip(.1);
    
    ofSetSmoothLighting(true);
    
    mainLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    mainLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    mainLight.setPosition(ofGetWidth(), ofGetHeight()*.5, 400);
    mainLight.setDirectional();
    mainLight.enable();
    
    DayEarth.load("earth.png");
    DayEarth.mirror(1, 0);
    
    NightEarth.load("night_earth.jpg");
    NightEarth.mirror(1, 0);
    
    EarthMesh.setRadius( 10 );
    EarthMesh.setResolution(4);
    EarthMesh.setPosition(0,0,0);
    
    EarthMesh.enableTextures();
    EarthMesh.mapTexCoordsFromTexture(DayEarth.getTexture());
    
    ofFbo::Settings settings;
    settings.numSamples = 8; // also try 8, if your GPU supports it
    settings.useDepth = true;
    settings.width = ofGetWidth();
    settings.height = ofGetHeight();
    
    postFbo.allocate(settings);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    EarthMesh.rotate(.1, 0, 1, 0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
   // postFbo.begin();
    cam.begin();
        ofBackground(0);
    
        ofSetColor( 255, 255, 255 );
    
        DayEarth.getTexture().bind();
        NightEarth.getTexture().bind();
        EarthShader.begin();
        EarthShader.setUniformTexture("tex0", DayEarth.getTexture()  , 0);
        EarthShader.setUniformTexture("tex1", NightEarth.getTexture()   , 1);
            EarthMesh.draw();
        EarthShader.end();
        DayEarth.getTexture().unbind();
        NightEarth.getTexture().unbind();
    
    cam.end();
    //postFbo.end();
    
    //postFbo.draw(ofVec2f(0,0));
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
