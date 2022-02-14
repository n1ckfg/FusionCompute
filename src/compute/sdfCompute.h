#pragma once

#include "ofMain.h"

class SDFCompute
{
  public:
	SDFCompute(glm::vec3 origin, int resolution, float scale);
	void         setupTexture();
	void         compute(unsigned int pointCloudId, unsigned int pointCloudNormalId);
	unsigned int getTextureID();
	void drawOutline();

  private:
	ofShader     m_computeSDFShader;
	unsigned int m_texID;
	int          m_resolution;
	glm::vec3    m_origin;
	float        m_scale;
};