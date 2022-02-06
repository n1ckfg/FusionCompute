#include "PointCloudScene.h"

#include "helper/dataStorageHelper.h"
#include "helper/fullScreenQuadRender.h"

//---------------------------------------------------
PointCloudScene::PointCloudScene()
    : m_pointCloudComp{}
    , m_pointCloudVis{}
    , m_pointCloudCPU{}
    , m_texDepthRaw{}
    , m_texColorPtr{}
{
}

//---------------------------------------------------
void PointCloudScene::setup(ofxKinect &kinect)
{
	m_pointCloudComp.registerKinectData(kinect.getZeroPlaneDistance(), kinect.getZeroPlanePixelSize());

	DataStorageHelper::loadData("depthRaw.bin", kinect.getRawDepthPixels().getData(), 640 * 480);
	m_texDepthRaw.allocate(kinect.getRawDepthPixels());
	m_texColorPtr = &kinect.getTexture();

	m_pointCloudComp.compute(m_texDepthRaw);
}

//---------------------------------------------------
void PointCloudScene::update(bool kinectUpdate, ofxKinect &kinect)
{
	if (kinectUpdate && GUIScene::s_computePointCloud)
	{
		m_texDepthRaw.loadData(kinect.getRawDepthPixels());
		m_pointCloudComp.compute(m_texDepthRaw);
	}
}

//---------------------------------------------------
void PointCloudScene::draw(ofCamera &camera)
{
	camera.begin();

	ofEnableDepthTest();

	drawOutline();

	constexpr float fovy       = glm::radians(62.0);
	glm::mat4x4     projection = glm::perspective(fovy, 4.0f / 3.0f, 0.1f, 200.0f);

	glm::vec3   kinectOrigin   = glm::vec3(0, 0, 0);
	glm::mat3x3 kinectRotation = glm::lookAt(kinectOrigin, kinectOrigin + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

	auto        ori = ofVec3f(kinectOrigin);
	auto        tar = ofVec3f(kinectOrigin + glm::vec3(0, 0, -1));
	auto        upv = ofVec3f(glm::vec3(0, 1, 0));
	ofMatrix4x4 view;
	view.makeLookAtViewMatrix(ori, tar, upv);
	ofMatrix4x4 persp          = ofMatrix4x4(projection);
	ofMatrix4x4 viewProjection = view * projection;

	ofVec3f testPosition = ofVec3f(1, 0, -10);
	auto    test         = testPosition * view;
	auto    test2        = testPosition * viewProjection;

	glm::vec4 origin = glm::vec4(0, 0, -10, 1);

	ofGetCurrentRenderer()->setFillMode(ofFillFlag::OF_OUTLINE);
	ofSetColor(255, 0, 0);
	ofDrawBox(origin, 1, 1, 1);

	int x = 160;
	int y = 240;

	float ndc_x = ((2.0 * x) - (2.0 * 0)) / 640 - 1.0;
	float ndc_y = ((2.0 * y) - (2.0 * 0)) / 480 - 1.0;
	float ndc_z = .9;

	ofVec3f output = ofVec3f(ndc_x, ndc_y, ndc_z) * glm::inverse(camera.getModelViewProjectionMatrix());
	ofDrawSphere(output, .01);

	if (GUIScene::s_drawPointCloud)
	{
		m_pointCloudVis.draw(m_pointCloudComp.getModelTextureID(), m_texColorPtr->getTextureData().textureID, false,
		                     camera.getModelViewProjectionMatrix(), 10.0f);
	}

	if (GUIScene::s_drawPointCloudNorm)
	{
		FullScreenQuadRender::get().draw(m_pointCloudComp.getNormalTextureID(), GL_TEXTURE_2D);
	}
	else if (GUIScene::s_drawPointCloudTex)
	{
		FullScreenQuadRender::get().draw(m_pointCloudComp.getModelTextureID(), GL_TEXTURE_2D);
	}

	camera.end();
}

void PointCloudScene::drawOutline()
{
	glm::vec3 origin    = glm::vec3(-10, -10, -20);
	float     scale     = 20;
	float     scalehalf = scale / 2;

	ofPushStyle();
	ofGetCurrentRenderer()->setFillMode(ofFillFlag::OF_OUTLINE);
	ofSetColor(255, 0, 0);
	ofDrawBox(glm::vec3(0, 0, 0), 1, 1, 1);
	ofSetColor(200, 100, 200);
	ofDrawBox(origin + glm::vec3(scalehalf, scalehalf, scalehalf), scale, scale, scale);
	ofPopStyle();
}