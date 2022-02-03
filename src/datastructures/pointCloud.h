#pragma once
#include <ofMain.h>
#include <ofxKinect.h>

class PointCloud
{
public: 
	PointCloud();

	void fillPointCloud(ofxKinect& kinect, int downsample, bool compNormals);

	void fillPointCloud(ofImage& depthImage, float maxDepth, int downsample = 0);

	void draw(bool drawNormals);

	glm::vec4* getPoints();
	int getSize();
	ofMesh& getMesh();

private:
	glm::vec4 points[640 * 480];
	glm::vec3 normals[640 * 480 * 2];
	int size;
	ofMesh meshPoints;
	ofMesh meshNormals;
	bool generated;
};

