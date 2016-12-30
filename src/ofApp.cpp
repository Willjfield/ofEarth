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
    
    sunPosition = ofVec3f(0, 0, 1);
    
    mainLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    mainLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    mainLight.setPosition(sunPosition);
    mainLight.setDirectional();
    mainLight.enable();
    
    rotateSpeed = 1;
    
    DayEarth.load("earth.png");
    DayEarth.mirror(1, 0);
    
    NightEarth.load("night_earth.jpg");
    NightEarth.mirror(1, 0);
    
    NormalEarth.load("earth_normal.png");
    NormalEarth.mirror(1, 0);
    
    EarthMesh.setRadius( 10 );
    EarthMesh.setResolution(4);
    EarthMesh.setPosition(0,0,0);
    
    atmosphereMesh.setRadius( 10.25 );
    atmosphereMesh.setResolution(4);
    atmosphereMesh.setPosition(0, 0, 0);
    atmosphereMesh.enableTextures();
    
    EarthMesh.enableTextures();
    EarthMesh.mapTexCoordsFromTexture(DayEarth.getTexture());
    
    randomVec = ofVec3f(ofRandom(1), ofRandom(1), ofRandom(1));
    
//    ofFbo::Settings settings;
//    //settings.numSamples = 8; // also try 8, if your GPU supports it
//    settings.useDepth = false;
//    settings.useStencil = false;
//    settings.width = ofGetWidth();
//    settings.height = ofGetHeight();
    
    //postFbo.allocate(settings);
    //atmosphere.allocate(settings);
//    atmosphere.allocate(ofGetWidth(), ofGetHeight());
//    atmosphere.begin();
//    ofClear(255,255,255);
//    atmosphere.end();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //EarthMesh.rotate(rotateSpeed*.025, 0, 1, 0);
    sunPosition.x = sin(ofGetFrameNum()*-.0025*rotateSpeed);
    sunPosition.z = cos(ofGetFrameNum()*-.0025*rotateSpeed);
    float t = ofGetFrameNum() * 0.001;
    float Nx = ofNoise( t );
    float Ny = ofNoise( t + 100);
    float Nz = ofNoise( t + 1000);
    randomVec.x=(Nx/2);
    randomVec.y=1+(Ny/2);
    randomVec.z=(Nz/2);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    //postFbo.begin();
    
    cam.begin();
        ofEnableDepthTest();
        initEarthShader();
        EarthShader.setUniformTexture("tex0", DayEarth.getTexture()  , 0);
        EarthShader.setUniformTexture("tex1", NightEarth.getTexture()   , 1);
        EarthShader.setUniformTexture("tex2", NormalEarth.getTexture()   , 2);
        EarthShader.setUniform3f("sunDirection", sunPosition);
        EarthShader.setUniform3f("uEyePos", cam.getPosition());
        //cout << cam.getPosition() << endl;
            EarthMesh.draw();
        endEarthShader();
    
        AtmosphereShader.begin();
        AtmosphereShader.setUniform3f("uEyePos", cam.getPosition());
        AtmosphereShader.setUniform3f("sunDirection", sunPosition);
        AtmosphereShader.setUniform1f("frameCount", ofGetFrameNum());//("sunDirection", sunPosition);
        AtmosphereShader.setUniform3f("randomVec", randomVec);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        atmosphereMesh.draw();
        AtmosphereShader.end();
    cam.end();
    //postFbo.end();
    
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
