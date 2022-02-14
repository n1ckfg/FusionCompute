#pragma once

#include "compute/PointCloudCompute.h"
#include "compute/PointCloudVis.h"
#include "ofMain.h"
#include "ofxKinect.h"
#include "scenes/GUIScene.h"
#include "scenes/PointCloudScene.h"
#include "scenes/PreprocessDepthScene.h"
#include "scenes/SDFScene.h"

class ofApp : public ofBaseApp
{

  public:
	ofApp();

	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

  private:
	void drawKinectPointCloud(ofxKinect& kinect);
	void drawFullScreenImage(ofImage& image);

  private:
	GUIScene             m_guiScene;
	PointCloudScene      m_pointCloudScene;
	PreprocessDepthScene m_blurScene;
	SDFScene             m_sdfScene;

	glm::mat4x4 m_kinectWorldToView;
	glm::mat4x4 m_kinectViewToWorld;
	glm::mat4x4 m_kinectProjection;

	ofxKinect m_kinect;
	ofImage   m_depthImage; // grayscale depth image
	ofEasyCam m_camera;

	ofImage m_screenShotImage;
};
