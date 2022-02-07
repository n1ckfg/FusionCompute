#pragma once

#include "GUIScene.h"
#include "SceneImpl.h"
#include "compute/PointCloudCompute.h"
#include "compute/PointCloudVis.h"
#include "cpuReference/IterativeClosestPointCPU.h"
#include "cpuReference/PointCloudCPU.h"
#include "ofMain.h"
#include "ofxKinect.h"

class PointCloudScene //: public SceneImpl
{
  public:
	PointCloudScene();
	void setup(ofxKinect& kinect);
	void update(bool kinectUpdate, ofxKinect& kinect);
	void draw(ofCamera& camera);
	void drawOutline();
	void drawTest(ofxKinect& kinect);

  private:
	PointCloudComp            m_pointCloudComp;
	PointCloudVis             m_pointCloudVis;
	PointCloudCPU             m_pointCloudCPU_0;
	PointCloudCPU             m_pointCloudCPU_1;
	IterativeClostestPointCPU m_icpCPU;
	ofTexture                 m_texDepthRaw;
	ofTexture*                m_texColorPtr;
	bool                      m_isPCL_0;
	glm::mat4x4               m_kinectView;
	glm::mat4x4               m_kinectProjection;
};
