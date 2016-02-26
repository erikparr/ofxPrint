#include "ofxPrint.h"
//--------------------------------------------------------------
void ofxPrint::setup(){
    
    renderCam.disableMouseInput();
    //set cam viewports so they align and represent the same transform of 3d object
    viewCam.setPosition(0,0, 780);
    viewCam.setScale(1, -1, 1);
    //        cam.setOrientation(ofQuaternion(0,0,0,0));
    renderCam.setPosition(0, 0, 780);
    renderCam.setScale(1, -1, 1);
    renderCam.setOrientation(ofQuaternion(0,0,0,0));
}

////--------------------------------------------------------------
//void ofxPrint::update(){
//    ofFile f;
//    f.open(filename);
//    if(f.doesFileExist(filename)){
//        bExists=true;
//    }
//}
//--------------------------------------------------------------
void ofxPrint::drawMesh(bool render){
    
    glEnable(GL_DEPTH_TEST);
    //viewcam must be set this way
    viewCam.begin();
    viewCam.end();
    
    if (render)
        begin();
    
    renderCam.begin();
    //    drawLineMesh();
    ofSetColor(0);
    triangleMesh(render);
    renderCam.end();
    
    glDisable(GL_DEPTH_TEST);
    
    if (render)
        end();
}



void ofxPrint::begin(string filename, int width, int height){
        if(filename=="")
        filename = ofGetTimestampString();
    if(width==-1 || height==-1){
            width = ofGetWidth();
        height = ofGetHeight();
    }
        ofBeginSaveScreenAsPDF(filename+".pdf",false,false,ofRectangle(0,0,width,height));
    
}

void ofxPrint::end(Boolean bExit){
    ofEndSaveScreenAsPDF();
    if(bExit)
    ofExit();
}


void ofxPrint::triangleMesh(bool render){
    glPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    for(int i = 0; i < triangles.size(); i++ ) {
        
        ofSetPolyMode(OF_POLY_WINDING_ODD);
        ofBeginShape();
        for(int j = 0; j < 3; j++ ) {
            triangles[i].setVertex(j, triangles[i].getVertex(j)  );
            ofRectangle viewport;
            viewport = ofRectangle(0,0, ofGetWidth(), ofGetHeight());
            if(render)
                // need this viewport offset to render to pdf with correct placement
                viewport = ofRectangle(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
            
            ofVec3f vert = viewCam.worldToScreen(ofVec3f(triangles[i].getVertex(j).x, triangles[i].getVertex(j).y, triangles[i].getVertex(j).z), viewport);
            
                ofVertex(vert.x-ofGetWidth()/2, vert.y-ofGetHeight()/2); // add vertex
        }
            ofNoFill();
        ofEndShape(true);
    }
    
    glPopMatrix();
}

ofVec3f ofxPrint::getVertAsScreen(ofVec3f v){
    ofRectangle viewport;
    viewport = ofRectangle(0,0, ofGetWidth(), ofGetHeight());
    return viewCam.worldToScreen(v, viewport);

}
////--------------------------------------------------------------
void ofxPrint::meshNoiseDistort(float liquidness, float amplitude, float speedDampen){
    
    //modify mesh with some noise
    //    float liquidness = 2;
    //    float amplitude = mouseY/100.0;
    //    float speedDampen = 5;
    //    vector<ofVec3f>& verts = box.getMesh().getVertices();
    for(unsigned int i = 0; i < triangles.size(); i++){
        for (int j=0; j<3; j++) {
            triangles[i].setVertex(j,ofVec3f(
                                                   triangles[i].getVertex(j).x+ofSignedNoise(triangles[i].getVertex(j).x/liquidness, triangles[i].getVertex(j).y/liquidness,triangles[i].getVertex(j).z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude,
                                                   triangles[i].getVertex(j).y+ofSignedNoise(triangles[i].getVertex(j).z/liquidness, triangles[i].getVertex(j).x/liquidness,triangles[i].getVertex(j).y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude,
                                                   triangles[i].getVertex(j).z+ofSignedNoise(triangles[i].getVertex(j).y/liquidness, triangles[i].getVertex(j).z/liquidness,triangles[i].getVertex(j).x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude));
        }
    }
    
    
}

////--------------------------------------------------------------
//void ofxPrint::draw(){
//    begin();
//    ofSetColor(255, 52, 151);
//    ofCircle(ofGetWidth()/2, ofGetHeight()/2, 50);
//    end();
//    if(!bExists)
//        ofDrawBitmapString("file does not exist", 50,50);
//    else
//        ofDrawBitmapString("file: "+ofToString(filename)+" filesize: "+ofToString(filesize)+" timer: "+
//                           ofToString(statusTimer), 50,50);
//    
//}


vector<ofMeshFace> ofxPrint::getTrianglesFromMesh(ofMesh &pMesh){
    return triangles = pMesh.getUniqueFaces();
}

vector<ofMeshFace> ofxPrint::getTrianglesFromBoxPrimitive(ofBoxPrimitive &pBox){
    return triangles = pBox.getMesh().getUniqueFaces();
}

vector<ofMeshFace> ofxPrint::getTrianglesFromSpherePrimitive(ofSpherePrimitive &pSphere){
    return triangles = pSphere.getMesh().getUniqueFaces();
}

vector<ofMeshFace> ofxPrint::getTrianglesFromPlanePrimitive(ofPlanePrimitive &pPlane){
    return triangles = pPlane.getMesh().getUniqueFaces();
}

vector<ofMeshFace> ofxPrint::getTrianglesFromCylinderPrimitive(ofCylinderPrimitive &pCylinder){
    return triangles = pCylinder.getMesh().getUniqueFaces();
}

vector<ofMeshFace> ofxPrint::getTrianglesFromConePrimitive(ofConePrimitive &pCone){
    return triangles = pCone.getMesh().getUniqueFaces();
}

vector<ofMeshFace> ofxPrint::getTrianglesFromModel(ofxAssimpModelLoader &pModel){
    return triangles = pModel.getMesh(0).getUniqueFaces();
}

