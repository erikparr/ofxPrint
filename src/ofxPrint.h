#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
class ofxPrint {
    
    
public:
    void setup();
    void update();
    void begin(string filename="", int width=-1, int height=-1);
    void end(Boolean bExit=false);
    
    vector<ofMeshFace> getTrianglesFromMesh(ofMesh &pMesh);
    vector<ofMeshFace> getTrianglesFromBoxPrimitive(ofBoxPrimitive &pBox);
    vector<ofMeshFace> getTrianglesFromSpherePrimitive(ofSpherePrimitive &pSphere);
    vector<ofMeshFace> getTrianglesFromPlanePrimitive(ofPlanePrimitive &pPlane);
    vector<ofMeshFace> getTrianglesFromCylinderPrimitive(ofCylinderPrimitive &pCylinder);
    vector<ofMeshFace> getTrianglesFromConePrimitive(ofConePrimitive &pCone);
    vector<ofMeshFace> getTrianglesFromModel(ofxAssimpModelLoader &pModel);
    
    void triangleMesh(bool render);
    void drawMesh(bool render);
    void meshNoiseDistort(float liquidness, float amplitude, float speedDampen);
    ofVec3f getVertAsScreen(ofVec3f v);
    
    vector<ofMeshFace> triangles;

    ofEasyCam viewCam, renderCam;

};
